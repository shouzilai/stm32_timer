#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2018-2022 Vasily Evseenko <svpcom@p2ptech.org>

#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; version 3.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

import sys
import time
import json
import os
import re
import hashlib

from itertools import groupby
from twisted.python import log, failure
from twisted.python.logfile import LogFile
from twisted.internet import reactor, defer, main as ti_main
from twisted.internet.protocol import ProcessProtocol, DatagramProtocol, Protocol, Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet.error import ReactorNotRunning
from twisted.internet.serialport import SerialPort

from .common import abort_on_crash, exit_status, df_sleep
from .proxy import UDPProxyProtocol, SerialProxyProtocol, ARMProtocol, call_and_check_rc, ExecError
from .tuntap import TUNTAPProtocol, TUNTAPTransport
from .conf import settings, cfg_files

connect_re = re.compile(r'^connect://(?P<addr>[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+):(?P<port>[0-9]+)$', re.IGNORECASE)
listen_re = re.compile(r'^listen://(?P<addr>[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+):(?P<port>[0-9]+)$', re.IGNORECASE)
serial_re = re.compile(r'^serial:(?P<dev>[a-z0-9\-\_/]+):(?P<baud>[0-9]+)$', re.IGNORECASE)


class BadTelemetry(Exception):
    pass


class WFBFlags(object):
    LINK_LOST = 1
    LINK_JAMMED = 2


class StatisticsProtocol(Protocol):
    def connectionMade(self):
        self.factory.sessions.append(self)

    def dataReceived(self, data):
        pass

    def connectionLost(self, reason):
        self.factory.sessions.remove(self)

    def send_stats(self, data):
        self.transport.write(json.dumps(data).encode('utf-8') + b'\n')


class AntennaFactory(Factory):
    noisy = False
    protocol = StatisticsProtocol

    def __init__(self, p_in, p_tx_l):
        self.p_in = p_in
        self.p_tx_l = p_tx_l
        self.tx_sel = 0
        self.tx_sel_delta = settings.common.tx_sel_delta

        # Select antenna #0 by default
        if p_in is not None and p_tx_l is not None:
            p_in.peer = p_tx_l[0]

        # tcp sockets for UI
        self.sessions = []

    def select_tx_antenna(self, ant_rssi):
        wlan_rssi = {}
        for k, grp in groupby(sorted(((int(ant_id, 16) >> 8) & 0xff, rssi_avg) \
                                     for ant_id, (pkt_s, rssi_min, rssi_avg, rssi_max) in ant_rssi.items()),
                              lambda x: x[0]):
            # Select max average rssi from all wlan's antennas
            wlan_rssi[k] = max(rssi for _, rssi in grp)

        tx_max = None
        for k, v in wlan_rssi.items():
            if tx_max is None or k != tx_max and v > wlan_rssi[tx_max]:
                tx_max = k

        if tx_max is None or wlan_rssi[tx_max] <= wlan_rssi.get(self.tx_sel, -200) + self.tx_sel_delta:
            return

        log.msg('Swith TX antenna from %d to %d' % (self.tx_sel, tx_max))
        self.tx_sel = tx_max
        self.p_in.peer = self.p_tx_l[tx_max]

    def update_stats(self, rx_id, packet_stats, ant_rssi):
        mav_rssi = []
        flags = 0

        for i, (k, v) in enumerate(sorted(ant_rssi.items())):
            pkt_s, rssi_min, rssi_avg, rssi_max = v
            mav_rssi.append(rssi_avg)

        rssi = (max(mav_rssi) if mav_rssi else -128) % 256

        if not mav_rssi:
            flags |= WFBFlags.LINK_LOST
        elif packet_stats['dec_ok'] == 0:
            flags |= WFBFlags.LINK_JAMMED

        if self.p_in:
            if ant_rssi: self.select_tx_antenna(ant_rssi)
            # Send mavlink packet with radio rssi
            _idx = 0 if settings.common.mavlink_err_rate else 1
            rx_errors = min(packet_stats['dec_err'][_idx] + packet_stats['bad'][_idx] + packet_stats['lost'][_idx], 65535)
            rx_fec = min(packet_stats['fec_rec'][_idx], 65535)
            self.p_in.send_rssi(rssi, rx_errors, rx_fec, flags)

        if settings.common.debug:
            log.msg('%s rssi %s tx#%d %s %s' % (rx_id, max(mav_rssi) if mav_rssi else 'N/A', self.tx_sel, packet_stats, ant_rssi))

        for s in self.sessions:
            s.send_stats(dict(id=rx_id, tx_ant=self.tx_sel, packets=packet_stats, rssi=ant_rssi))


class AntennaProtocol(LineReceiver):
    delimiter = b'\n'

    def __init__(self, antenna_f, rx_id):
        self.antenna_f = antenna_f
        self.rx_id = rx_id
        self.ant = {}
        self.count_all = None

    def lineReceived(self, line):
        cols = line.decode('utf-8').strip().split('\t')
        try:
            if len(cols) < 2:
                raise BadTelemetry()

            #ts = int(cols[0])
            cmd = cols[1]

            if cmd == 'ANT':
                if len(cols) != 4:
                    raise BadTelemetry()
                self.ant[cols[2]] = tuple(int(i) for i in cols[3].split(':'))
            elif cmd == 'PKT':
                if len(cols) != 3:
                    raise BadTelemetry()

                p_all, p_dec_err, p_dec_ok, p_fec_rec, p_lost, p_bad = list(int(i) for i in cols[2].split(':'))

                if not self.count_all:
                    self.count_all = (p_all, p_dec_ok, p_fec_rec, p_lost, p_dec_err, p_bad)
                else:
                    self.count_all = tuple((a + b) for a, b in zip((p_all, p_dec_ok, p_fec_rec, p_lost, p_dec_err, p_bad), self.count_all))

                stats = dict(zip(('all', 'dec_ok', 'fec_rec', 'lost', 'dec_err', 'bad'),
                                 zip((p_all, p_dec_ok, p_fec_rec, p_lost, p_dec_err, p_bad),
                                     self.count_all)))

                self.antenna_f.update_stats(self.rx_id, stats, dict(self.ant))
                self.ant.clear()
            else:
                raise BadTelemetry()
        except BadTelemetry:
            log.msg('Bad telemetry [%s]: %s' % (self.rx_id, line), isError=1)


class DbgProtocol(LineReceiver):
    delimiter = b'\n'

    def __init__(self, rx_id):
        self.rx_id = rx_id

    def lineReceived(self, line):
        log.msg('%s: %s' % (self.rx_id, line.decode('utf-8')))


class RXProtocol(ProcessProtocol):
    def __init__(self, antenna_stat, cmd, rx_id):
        self.cmd = cmd
        self.rx_id = rx_id
        self.ant = AntennaProtocol(antenna_stat, rx_id) if antenna_stat is not None else None
        self.dbg = DbgProtocol(rx_id)
        self.df = defer.Deferred()

    def connectionMade(self):
        log.msg('Started %s' % (self.rx_id,))

    def outReceived(self, data):
        if self.ant is not None:
            self.ant.dataReceived(data)

    def errReceived(self, data):
        self.dbg.dataReceived(data)

    def processEnded(self, status):
        rc = status.value.exitCode
        log.msg('Stopped RX %s with code %s' % (self.rx_id, rc))

        if rc == 0:
            self.df.callback(str(status.value))
        else:
            self.df.errback(status)

    def start(self):
        df = defer.maybeDeferred(reactor.spawnProcess, self, self.cmd[0], self.cmd, env=os.environ, childFDs={0: "w", 1: "r", 2: "r"})
        return df.addCallback(lambda _: self.df)


class TXProtocol(ProcessProtocol):
    def __init__(self, cmd, tx_id):
        self.cmd = cmd
        self.tx_id = tx_id
        self.dbg = DbgProtocol(tx_id)
        self.df = defer.Deferred()

    def connectionMade(self):
        log.msg('Started %s' % (self.tx_id,))

    def outReceived(self, data):
        self.dbg.dataReceived(data)

    def errReceived(self, data):
        self.dbg.dataReceived(data)

    def processEnded(self, status):
        rc = status.value.exitCode
        log.msg('Stopped TX %s with code %s' % (self.tx_id, rc))

        if rc == 0:
            self.df.callback(str(status.value))
        else:
            self.df.errback(status)

    def start(self):
        df = defer.maybeDeferred(reactor.spawnProcess, self, self.cmd[0], self.cmd, env=os.environ,
                                 childFDs={0: "w", 1: "r", 2: "r"})
        return df.addCallback(lambda _: self.df)


@defer.inlineCallbacks
def init_wlans(profile, wlans):
    max_bw = max(getattr(getattr(settings, '%s_mavlink' % profile), 'bandwidth'),
                 getattr(getattr(settings, '%s_video' % profile), 'bandwidth'))

    if max_bw == 20:
        ht_mode = 'HT20'
    elif max_bw == 40:
        ht_mode = 'HT40+'
    else:
        raise Exception('Unsupported bandwith %d MHz' % (max_bw,))

    try:
        yield call_and_check_rc('iw', 'reg', 'set', settings.common.wifi_region)
        for wlan in wlans:
            if settings.common.set_nm_unmanaged and os.path.exists('/usr/bin/nmcli'):
                device_status = yield call_and_check_rc('nmcli', 'device', 'show', wlan, log_stdout=False)
                if not b'(unmanaged)' in device_status:
                    log.msg('Switch %s to unmanaged state' % (wlan,))
                    yield call_and_check_rc('nmcli', 'device', 'set', wlan, 'managed', 'no')
                    yield df_sleep(1)

            yield call_and_check_rc('ip', 'link', 'set', wlan, 'down')
            yield call_and_check_rc('iw', 'dev', wlan, 'set', 'monitor', 'otherbss')
            yield call_and_check_rc('ip', 'link', 'set', wlan, 'up')
            yield call_and_check_rc('iw', 'dev', wlan, 'set', 'channel', str(settings.common.wifi_channel), ht_mode)
            if settings.common.wifi_txpower:
                yield call_and_check_rc('iw', 'dev', wlan, 'set', 'txpower', 'fixed', str(settings.common.wifi_txpower))
    except ExecError as v:
        if v.stdout:
            log.msg(v.stdout, isError=1)
        if v.stderr:
            log.msg(v.stderr, isError=1)
        raise

def init(profile, wlans):
    def _init_services(_):
        link_id = int.from_bytes(hashlib.sha1(settings.common.link_id.encode('utf-8')).digest()[:3], 'big')
        return defer.gatherResults([defer.maybeDeferred(init_mavlink, profile, wlans, link_id),
                                    defer.maybeDeferred(init_video, profile, wlans, link_id),
                                    defer.maybeDeferred(init_tunnel, profile, wlans, link_id)])\
                    .addErrback(lambda f: f.trap(defer.FirstError) and f.value.subFailure)

    return defer.maybeDeferred(init_wlans, profile, wlans).addCallback(_init_services)


def init_mavlink(profile, wlans, link_id):
    cfg = getattr(settings, '%s_mavlink' % (profile,))

    cmd_rx = ('%s -p %d -u %d -K %s -k %d -n %d -i %d' % \
              (os.path.join(settings.path.bin_dir, 'wfb_rx'), cfg.stream_rx,
               cfg.port_rx, os.path.join(settings.path.conf_dir, cfg.keypair), cfg.fec_k, cfg.fec_n, link_id)).split() + wlans

    cmd_tx = ('%s -p %d -u %d -K %s -B %d -G %s -S %d -L %d -M %d -k %d -n %d -T %d -i %d' % \
              (os.path.join(settings.path.bin_dir, 'wfb_tx'),
               cfg.stream_tx, cfg.port_tx, os.path.join(settings.path.conf_dir, cfg.keypair),
               cfg.bandwidth, "short" if cfg.short_gi else "long", cfg.stbc, cfg.ldpc, cfg.mcs_index,
               cfg.fec_k, cfg.fec_n, cfg.fec_timeout, link_id)).split() + wlans

    listen = None
    connect = None
    serial = None
    mirror = None

    if connect_re.match(cfg.peer):
        m = connect_re.match(cfg.peer)
        connect = m.group('addr'), int(m.group('port'))
        log.msg('Connect telem stream %d(RX), %d(TX) to %s:%d' % (cfg.stream_rx, cfg.stream_tx, connect[0], connect[1]))

    elif listen_re.match(cfg.peer):
        m = listen_re.match(cfg.peer)
        listen = m.group('addr'), int(m.group('port'))
        log.msg('Listen for telem stream %d(RX), %d(TX) on %s:%d' % (cfg.stream_rx, cfg.stream_tx, listen[0], listen[1]))

    elif serial_re.match(cfg.peer):
        m = serial_re.match(cfg.peer)
        serial = m.group('dev'), int(m.group('baud'))
        log.msg('Open serial port %s on speed %d' % (serial[0], serial[1]))

    else:
        raise Exception('Unsupport peer address: %s' % (cfg.peer,))

    if cfg.mirror is not None and connect_re.match(cfg.mirror):
        m = connect_re.match(cfg.mirror)
        mirror = m.group('addr'), int(m.group('port'))
        log.msg('Mirror telem stream to %s:%d' % (mirror[0], mirror[1]))

    if cfg.call_on_arm or cfg.call_on_disarm:
        arm_proto = ARMProtocol(cfg.call_on_arm, cfg.call_on_disarm)
    else:
        arm_proto = None

    if serial:
        p_in = SerialProxyProtocol(agg_max_size=settings.common.radio_mtu,
                                   agg_timeout=settings.common.mavlink_agg_timeout,
                                   inject_rssi=cfg.inject_rssi,
                                   arm_proto=arm_proto,
                                   mavlink_sys_id=cfg.mavlink_sys_id,
                                   mavlink_comp_id=cfg.mavlink_comp_id)
    else:
        # The first argument is not None only if we initiate mavlink connection
        p_in = UDPProxyProtocol(connect, agg_max_size=settings.common.radio_mtu,
                                agg_timeout=settings.common.mavlink_agg_timeout,
                                inject_rssi=cfg.inject_rssi,
                                mirror=mirror,
                                arm_proto=arm_proto,
                                mavlink_sys_id=cfg.mavlink_sys_id,
                                mavlink_comp_id=cfg.mavlink_comp_id)

    p_tx_l = [UDPProxyProtocol(('127.0.0.1', cfg.port_tx + i)) for i, _ in enumerate(wlans)]
    p_rx = UDPProxyProtocol(arm_proto=arm_proto)
    p_rx.peer = p_in

    if serial:
        serial_port = SerialPort(p_in, os.path.join('/dev', serial[0]), reactor, baudrate=serial[1])
        serial_port._serial.exclusive = True
        sockets = []

    else:
        serial_port = None
        sockets = [ reactor.listenUDP(listen[1] if listen else 0, p_in) ]

    sockets += [ reactor.listenUDP(cfg.port_rx, p_rx) ]
    sockets += [ reactor.listenUDP(0, p_tx) for p_tx in p_tx_l ]

    log.msg('Telem RX: %s' % (' '.join(cmd_rx),))
    log.msg('Telem TX: %s' % (' '.join(cmd_tx),))

    ant_f = AntennaFactory(p_in, p_tx_l)
    if cfg.stats_port:
        reactor.listenTCP(cfg.stats_port, ant_f)

    dl = [RXProtocol(ant_f, cmd_rx, 'telem rx').start(),
          TXProtocol(cmd_tx, 'telem tx').start()]

    def _cleanup(x):
        if serial_port is not None:
            serial_port.loseConnection()
            serial_port.connectionLost(failure.Failure(ti_main.CONNECTION_DONE))

        for s in sockets:
            s.stopListening()

        return x

    return defer.gatherResults(dl, consumeErrors=True).addBoth(_cleanup)\
                                                      .addErrback(lambda f: f.trap(defer.FirstError) and f.value.subFailure)

def init_video(profile, wlans, link_id):
    cfg = getattr(settings, '%s_video' % (profile,))

    if listen_re.match(cfg.peer):
        m = listen_re.match(cfg.peer)
        listen = m.group('addr'), int(m.group('port'))
        log.msg('Listen for video stream %d on %s:%d' % (cfg.stream, listen[0], listen[1]))

        # We don't use TX diversity for video streaming due to only one transmitter on the vehichle
        cmd = ('%s -p %d -u %d -K %s -B %d -G %s -S %d -L %d -M %d -k %d -n %d -T %d -i %d %s' % \
               (os.path.join(settings.path.bin_dir, 'wfb_tx'), cfg.stream,
                listen[1], os.path.join(settings.path.conf_dir, cfg.keypair),
                cfg.bandwidth, "short" if cfg.short_gi else "long", cfg.stbc, cfg.ldpc, cfg.mcs_index,
                cfg.fec_k, cfg.fec_n, cfg.fec_timeout, link_id, wlans[0])).split()

        df = TXProtocol(cmd, 'video tx').start()
    elif connect_re.match(cfg.peer):
        m = connect_re.match(cfg.peer)
        connect = m.group('addr'), int(m.group('port'))
        log.msg('Send video stream %d to %s:%d' % (cfg.stream, connect[0], connect[1]))

        ant_f = AntennaFactory(None, None)
        if cfg.stats_port:
            reactor.listenTCP(cfg.stats_port, ant_f)

        cmd = ('%s -p %d -c %s -u %d -K %s -k %d -n %d -i %d' % \
               (os.path.join(settings.path.bin_dir, 'wfb_rx'),
                cfg.stream, connect[0], connect[1],
                os.path.join(settings.path.conf_dir, cfg.keypair),
                cfg.fec_k, cfg.fec_n, link_id)).split() + wlans

        df = RXProtocol(ant_f, cmd, 'video rx').start()
    else:
        raise Exception('Unsupport peer address: %s' % (cfg.peer,))

    log.msg('Video: %s' % (' '.join(cmd),))
    return df

def init_tunnel(profile, wlans, link_id):
    cfg = getattr(settings, '%s_tunnel' % (profile,))

    cmd_rx = ('%s -p %d -u %d -K %s -k %d -n %d -i %d' % \
              (os.path.join(settings.path.bin_dir, 'wfb_rx'), cfg.stream_rx,
               cfg.port_rx, os.path.join(settings.path.conf_dir, cfg.keypair), cfg.fec_k, cfg.fec_n, link_id)).split() + wlans

    cmd_tx = ('%s -p %d -u %d -K %s -B %d -G %s -S %d -L %d -M %d -k %d -n %d -T %d -i %d' % \
              (os.path.join(settings.path.bin_dir, 'wfb_tx'),
               cfg.stream_tx, cfg.port_tx, os.path.join(settings.path.conf_dir, cfg.keypair),
               cfg.bandwidth, "short" if cfg.short_gi else "long", cfg.stbc, cfg.ldpc, cfg.mcs_index,
               cfg.fec_k, cfg.fec_n, cfg.fec_timeout, link_id)).split() + wlans

    p_in = TUNTAPProtocol()
    p_tx_l = [UDPProxyProtocol(('127.0.0.1', cfg.port_tx + i)) for i, _ in enumerate(wlans)]
    p_rx = UDPProxyProtocol()
    p_rx.peer = p_in

    tun_ep = TUNTAPTransport(reactor, p_in, cfg.ifname, cfg.ifaddr, mtu=settings.common.radio_mtu)
    sockets = [ reactor.listenUDP(cfg.port_rx, p_rx) ]
    sockets += [ reactor.listenUDP(0, p_tx) for p_tx in p_tx_l ]

    log.msg('Tunnel RX: %s' % (' '.join(cmd_rx),))
    log.msg('Tunnel TX: %s' % (' '.join(cmd_tx),))

    ant_f = AntennaFactory(p_in, p_tx_l)

    if cfg.stats_port:
        reactor.listenTCP(cfg.stats_port, ant_f)

    dl = [RXProtocol(ant_f, cmd_rx, 'tunnel rx').start(),
          TXProtocol(cmd_tx, 'tunnel tx').start()]

    def _cleanup(x):
        tun_ep.loseConnection()
        for s in sockets:
            s.stopListening()
        return x

    return defer.gatherResults(dl, consumeErrors=True).addBoth(_cleanup)\
                                                      .addErrback(lambda f: f.trap(defer.FirstError) and f.value.subFailure)

def main():
    if settings.common.log_file:
        log.startLogging(LogFile(settings.common.log_file,
                                 settings.path.log_dir,
                                 rotateLength=1024*1024,
                                 maxRotatedFiles=10))
    else:
        log.startLogging(sys.stdout)

    log.msg('WFB version %s-%s' % (settings.common.version, settings.common.commit[:8]))
    profile, wlans = sys.argv[1], list(wlan for arg in sys.argv[2:] for wlan in arg.split())
    uname = os.uname()
    log.msg('Run on %s/%s @%s, profile %s using %s' % (uname[4], uname[2], uname[1], profile, ', '.join(wlans)))
    log.msg('Using cfg files:\n%s' % ('\n'.join(cfg_files),))

    reactor.callWhenRunning(lambda: defer.maybeDeferred(init, profile, wlans)\
                            .addErrback(abort_on_crash))
    reactor.run()

    rc = exit_status()
    log.msg('Exiting with code %d' % rc)
    sys.exit(rc)


if __name__ == '__main__':
    main()
