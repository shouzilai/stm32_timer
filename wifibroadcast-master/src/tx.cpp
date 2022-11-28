// -*- C++ -*-
//
// Copyright (C) 2017 - 2022 Vasily Evseenko <svpcom@p2ptech.org>

/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 3.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <sys/resource.h>
#include <pcap/pcap.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <linux/random.h>
#include <inttypes.h>

#include <string>
#include <memory>
#include <vector>

extern "C"
{
#include "fec.h"
}

#include "wifibroadcast.hpp"
#include "tx.hpp"

using namespace std;

Transmitter::Transmitter(int k, int n, const string &keypair, uint64_t epoch, uint32_t channel_id) : \
    fec_k(k), fec_n(n), block_idx(0),
    fragment_idx(0),
    max_packet_size(0),
    epoch(epoch),
    channel_id(channel_id)
{
    fec_p = fec_new(fec_k, fec_n);

    block = new uint8_t*[fec_n];
    for(int i=0; i < fec_n; i++)
    {
        block[i] = new uint8_t[MAX_FEC_PAYLOAD];
    }

    FILE *fp;
    if((fp = fopen(keypair.c_str(), "r")) == NULL)
    {
        throw runtime_error(string_format("Unable to open %s: %s", keypair.c_str(), strerror(errno)));
    }
    if (fread(tx_secretkey, crypto_box_SECRETKEYBYTES, 1, fp) != 1)
    {
        fclose(fp);
        throw runtime_error(string_format("Unable to read tx secret key: %s", strerror(errno)));
    }
    if (fread(rx_publickey, crypto_box_PUBLICKEYBYTES, 1, fp) != 1)
    {
        fclose(fp);
        throw runtime_error(string_format("Unable to read rx public key: %s", strerror(errno)));
    }
    fclose(fp);

    make_session_key();
}

Transmitter::~Transmitter()
{
    for(int i=0; i < fec_n; i++)
    {
        delete block[i];
    }
    delete block;

    fec_free(fec_p);
}


void Transmitter::make_session_key(void)
{
    // init session key
    randombytes_buf(session_key, sizeof(session_key));

    // fill packet header
    wsession_hdr_t *session_hdr = (wsession_hdr_t *)session_key_packet;
    session_hdr->packet_type = WFB_PACKET_KEY;

    randombytes_buf(session_hdr->session_nonce, sizeof(session_hdr->session_nonce));

    // fill packet contents
    wsession_data_t session_data = { .epoch = htobe64(epoch),
                                     .channel_id = htobe32(channel_id),
                                     .fec_type = WFB_FEC_VDM_RS,
                                     .k = (uint8_t)fec_k,
                                     .n = (uint8_t)fec_n,
                                   };

    memcpy(session_data.session_key, session_key, sizeof(session_key));

    if (crypto_box_easy(session_key_packet + sizeof(wsession_hdr_t),
                        (uint8_t*)&session_data, sizeof(session_data),
                        session_hdr->session_nonce, rx_publickey, tx_secretkey) != 0)
    {
        throw runtime_error("Unable to make session key!");
    }
}


PcapTransmitter::PcapTransmitter(int k, int n, const string &keypair, uint64_t epoch, uint32_t channel_id, const vector<string> &wlans) : \
    Transmitter(k, n, keypair, epoch, channel_id),
    channel_id(channel_id),
    current_output(0),
    ieee80211_seq(0)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    for(auto it = wlans.begin(); it != wlans.end(); it++)
    {
        pcap_t *p = pcap_create(it->c_str(), errbuf);
        if (p == NULL){
            throw runtime_error(string_format("Unable to open interface %s in pcap: %s", it->c_str(), errbuf));
        }
        if (pcap_set_snaplen(p, 4096) !=0) throw runtime_error("set_snaplen failed");

        if (pcap_set_promisc(p, 1) != 0) throw runtime_error("set_promisc failed");

        //if (pcap_set_rfmon(p, 1) !=0) throw runtime_error("set_rfmon failed");

        if (pcap_set_timeout(p, -1) !=0) throw runtime_error("set_timeout failed");

        //if (pcap_set_buffer_size(p, 2048) !=0) throw runtime_error("set_buffer_size failed");

        if (pcap_set_immediate_mode(p, 1) != 0) throw runtime_error(string_format("pcap_set_immediate_mode failed: %s", pcap_geterr(p)));

        if (pcap_activate(p) !=0) throw runtime_error(string_format("pcap_activate failed: %s", pcap_geterr(p)));

        //if (pcap_setnonblock(p, 1, errbuf) != 0) throw runtime_error(string_format("set_nonblock failed: %s", errbuf));

        ppcap.push_back(p);
    }
}

void PcapTransmitter::inject_rts_packet()
{
    uint8_t txbuf[MAX_PACKET_SIZE];
    uint8_t *p = txbuf;

    // radiotap header
    memcpy(p, radiotap_header, sizeof(radiotap_header));
    p += sizeof(radiotap_header);

    // ieee80211 header
    memcpy(p, ieee80211_header_rts, sizeof(ieee80211_header_rts));

    // channel_id
    uint32_t channel_id_be = htobe32(channel_id);
    ///memcpy(p + SRC_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));
    ///memcpy(p + DST_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));
    ///memcpy(p + 6, &channel_id_be, sizeof(uint32_t));

    // sequence number
    ///p[FRAME_SEQ_LB] = ieee80211_seq & 0xff;
    ///p[FRAME_SEQ_HB] = (ieee80211_seq >> 8) & 0xff;
    ///ieee80211_seq += 16;
    p += sizeof(ieee80211_header_rts);

    ///printf("[yjl-%s()-%d]--- p - txbuf:%d, size:%d\n", __FUNCTION__, __LINE__, p - txbuf, size);
    if (pcap_inject(ppcap[current_output], txbuf, p - txbuf) != p - txbuf)
    {
        throw runtime_error(string_format("Unable to inject packet"));
    }
}

void PcapTransmitter::inject_cts_packet()
{
    uint8_t txbuf[MAX_PACKET_SIZE];
    uint8_t *p = txbuf;

    // radiotap header
    memcpy(p, radiotap_header, sizeof(radiotap_header));
    p += sizeof(radiotap_header);

    // ieee80211 header
    memcpy(p, ieee80211_header_cts, sizeof(ieee80211_header_cts));

    // channel_id
    uint32_t channel_id_be = htobe32(channel_id);
    ///memcpy(p + SRC_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));
    ///memcpy(p + DST_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));
    ///memcpy(p + 6, &channel_id_be, sizeof(uint32_t));

    // sequence number
    ///p[FRAME_SEQ_LB] = ieee80211_seq & 0xff;
    ///p[FRAME_SEQ_HB] = (ieee80211_seq >> 8) & 0xff;
    ///ieee80211_seq += 16;
    p += sizeof(ieee80211_header_cts);

    ///printf("[yjl-%s()-%d]--- p - txbuf:%d, size:%d\n", __FUNCTION__, __LINE__, p - txbuf, size);
    if (pcap_inject(ppcap[current_output], txbuf, p - txbuf) != p - txbuf)
    {
        throw runtime_error(string_format("Unable to inject packet"));
    }
}

void PcapTransmitter::inject_packet(const uint8_t *buf, size_t size)
{
    uint8_t txbuf[MAX_PACKET_SIZE];// 1510
    uint8_t *data_buf = txbuf;

    assert(size <= MAX_FORWARDER_PACKET_SIZE);

    // radiotap header
    memcpy(data_buf, radiotap_header, sizeof(radiotap_header));
    data_buf += sizeof(radiotap_header);

    // ieee80211 header
    memcpy(data_buf, ieee80211_header, sizeof(ieee80211_header));

    // channel_id
    uint32_t channel_id_be = htobe32(channel_id);
    memcpy(data_buf + SRC_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));// 6 个字节
    memcpy(data_buf + DST_MAC_THIRD_BYTE, &channel_id_be, sizeof(uint32_t));// 6 个字节

    // sequence number
    data_buf[FRAME_SEQ_LB] = ieee80211_seq & 0xff;
    data_buf[FRAME_SEQ_HB] = (ieee80211_seq >> 8) & 0xff;
    ieee80211_seq += 16;                                 // 此处应该是 +14 的，尚未清楚为何 +16
    data_buf += sizeof(ieee80211_header);

    // LLC header
    memset(data_buf, 0, 4);
    data_buf += 4;

    // FEC data
    memcpy(data_buf, buf, size);
    data_buf += size;

    ///printf("[yjl-%s()-%d]--- p - txbuf:%d, size:%d\n", __FUNCTION__, __LINE__, p - txbuf, size);
    if (pcap_inject(ppcap[current_output], txbuf, data_buf - txbuf) != data_buf - txbuf) // 已偏移距离 - 首地址 == 需求发送数据的长度 
    {
        throw runtime_error(string_format("Unable to inject packet"));
    }
}

PcapTransmitter::~PcapTransmitter()
{
    for(auto it=ppcap.begin(); it != ppcap.end(); it++){
        pcap_close(*it);
    }
}


void Transmitter::send_block_fragment(size_t packet_size)
{
    uint8_t ciphertext[MAX_FORWARDER_PACKET_SIZE];
    wblock_hdr_t *block_hdr = (wblock_hdr_t*)ciphertext;
    // typedef struct {
    //     uint8_t packet_type;
    //     uint64_t data_nonce;  // big endian, data_nonce = (block_idx << 8) + fragment_idx
    // }  __attribute__ ((packed)) wblock_hdr_t;
    int ciphertext_len;

    if (sizeof(ciphertext) == MAX_PACKET_SIZE - sizeof(radiotap_header) - sizeof(ieee80211_header)) {
        printf("allocate success!!!\n");
    }
    memset(ciphertext, 0, sizeof(ciphertext));
    assert(packet_size <= MAX_FEC_PAYLOAD);

    block_hdr->packet_type = WFB_PACKET_DATA;
    block_hdr->data_nonce = htobe64(((block_idx & BLOCK_IDX_MASK) << 8) + fragment_idx);
    ciphertext_len += sizeof(wblock_hdr_t);

    // encrypted payload
    /*
    if (crypto_aead_chacha20poly1305_encrypt(ciphertext + sizeof(wblock_hdr_t), &ciphertext_len,
                                             block[fragment_idx], packet_size,
                                             (uint8_t*)block_hdr, sizeof(wblock_hdr_t),
                                             NULL, (uint8_t*)(&(block_hdr->data_nonce)), session_key) < 0)
    {
        throw runtime_error("Unable to encrypt packet!");
    }
    */
    // printf("ciphertext_len is %d\n fragment_idx is %d packet_size is %d", ciphertext_len, this->fragment_idx, packet_size);
    memcpy(&ciphertext[ciphertext_len], block[fragment_idx], packet_size);
    ciphertext_len += packet_size;
    ///printf("[yjl-%s()-%d]--- packet_size:%d, ciphertext_len:%d---", packet_size, ciphertext_len);
    printf("[fengshou-%s()-%d]--- ready to inject packet_size:%d, ciphertext_len:%d---", packet_size, ciphertext_len);
    inject_packet(ciphertext, ciphertext_len);
}

void Transmitter::send_session_key(void)
{
    //fprintf(stderr, "Announce session key\n");
    inject_packet((uint8_t*)session_key_packet, sizeof(session_key_packet));
}

void Transmitter::send_packet(const uint8_t *buf, size_t size, uint8_t flags)
{
    wpacket_hdr_t packet_hdr;
    // typedef struct {
    //     uint8_t flags;
    //     uint16_t packet_size; // big endian
    // }  __attribute__ ((packed)) wpacket_hdr_t;
    assert(size <= MAX_PAYLOAD_SIZE);

    // FEC-only packets are only for closing already opened blocks
    if(fragment_idx == 0 && flags & WFB_PACKET_FEC_ONLY)
    {
        printf("[yjl-%s()-%d]--- FEC-only packets are only for closing already opened blocks\n", __FUNCTION__, __LINE__);
        return;
    }

    packet_hdr.packet_size = htobe16(size);     // 数据包大小确定
    packet_hdr.flags = flags;                   // 数据包标志确定
    memset(block[fragment_idx], '\0', MAX_FEC_PAYLOAD);
    memcpy(block[fragment_idx], &packet_hdr, sizeof(packet_hdr));
    memcpy(block[fragment_idx] + sizeof(packet_hdr), buf, size);

    send_block_fragment(sizeof(packet_hdr) + size);
    max_packet_size = max(max_packet_size, sizeof(packet_hdr) + size);// 0 和 包头+，选大值
    fragment_idx += 1;                          // 数据包数量 + 1

    if (fragment_idx < fec_k)  return;          // 数据包小于 8 ，返回，暂不发纠错包
/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/
    fec_encode(fec_p, (const uint8_t**)block, block + fec_k, max_packet_size);
    while (fragment_idx < fec_n)
    {
        ///printf("[yjl-%s()-%d]--- fragment_idx:%d, fec_n:%d, max_packet_size:%d\n", __FUNCTION__, __LINE__, fragment_idx, fec_n, max_packet_size);
        inject_rts_packet();
        inject_cts_packet();
        send_block_fragment(max_packet_size);
        fragment_idx += 1;
    }
    // 当数据包序号等于 12 ,大的数据块序号 + 1，其他的均置 0 （数据报序号、最大包大小）
    block_idx += 1;
    fragment_idx = 0;
    max_packet_size = 0;

    // Generate new session key after MAX_BLOCK_IDX blocks
    ///printf("[yjl-%s()-%d]--- block_idx:%llu, max_block_idx:%llu\n", __FUNCTION__, __LINE__, block_idx, MAX_BLOCK_IDX);
    if (block_idx > MAX_BLOCK_IDX) 
    {   // 发包数量超过0x7ffffffffffffff后，重新生成新的会话密匙
        make_session_key();
        send_session_key();
        block_idx = 0;
    }
}

#define HL_WBCAST_RATE_TEST 1
#if HL_WBCAST_RATE_TEST
void data_source(shared_ptr<Transmitter> &t, vector<int> &rx_fd, int poll_timeout, int s32Rate, int s32TestTime)
{
    uint8_t u8SendBuf[1400];
    u_int32_t u32SendInterval;
    u_int32_t u32RunTime;
    hl_wbcast_header_t *pstWbcastHead = (hl_wbcast_header_t *)u8SendBuf;
    // typedef struct _hl_wbcast_header {
    // uint32_t u32Seq;
    // uint32_t u32Len;
    // } __attribute__ ((packed)) hl_wbcast_header_t;
    int32_t u32CurtTime = 0, u32LastTime = 0;/// 当前时间戳，上次时间戳

    if (s32Rate < 1 || s32TestTime < 1) {
        printf("[yjl-%s()-%d]--- input param error\n", __FUNCTION__, __LINE__);
        return;
    }

    memset(u8SendBuf, 0, sizeof(u8SendBuf));                              // 负载数据均为 0
    pstWbcastHead->u32Seq = 1;
    pstWbcastHead->u32Len = 1400;
    u32SendInterval = (1400 * 1000 * 1000) / (s32Rate * 1024 * 1024 / 8); // 10681
    u32RunTime = s32TestTime * 1000;
    printf("[yjl-%s()-%d]--- s32Rate:%dMbps, s32TestTime:%ds, u32SendInterval:%d, u32RunTime:%d\n", __FUNCTION__, __LINE__, 
        s32Rate, s32TestTime, u32SendInterval, u32RunTime);
    u32CurtTime = get_time_ms();
    u32LastTime = u32CurtTime;

    
    while (1) {
        ///printf("[yjl-%s()-%d]--- pstWbcastHead->u32Seq:%d\n", __FUNCTION__, __LINE__, pstWbcastHead->u32Seq);
        // printf("[fengshou-%s()-%d]--- pstWbcastHead->u32Seq:%d\n", __FUNCTION__, __LINE__, pstWbcastHead->u32Seq);
        t->send_packet(u8SendBuf, 1400, 0);

        // 到点打印一句话
        u32CurtTime = get_time_ms();
        if (u32CurtTime - u32LastTime >= 1000) {
            printf("[yjl-%s()-%d]--- SendSeq:%d\n", __FUNCTION__, __LINE__, pstWbcastHead->u32Seq);
            u32LastTime = u32CurtTime;
        }
        pstWbcastHead->u32Seq++;
        usleep(u32SendInterval);
    }
}
#else
void data_source(shared_ptr<Transmitter> &t, vector<int> &rx_fd, int poll_timeout)
{
    int nfds = rx_fd.size();
    struct pollfd fds[nfds];
    unsigned char hlTestBuf[1024];
    unsigned int *hlCount = (unsigned int *)hlTestBuf;
    memset(hlTestBuf, '\0', sizeof(hlTestBuf));
    memset(fds, '\0', sizeof(fds));
    *hlCount = 1;
    memcpy(hlTestBuf + 4, "packe\0", 6);
    printf("[yjl-%s()-%d]--- send:%u-%s\n", __FUNCTION__, __LINE__, *hlCount, hlTestBuf+4);

    int i = 0;
    for(auto it=rx_fd.begin(); it != rx_fd.end(); it++, i++)
    {
        int fd = *it;
        if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
        {
            throw runtime_error(string_format("Unable to set socket into nonblocked mode: %s", strerror(errno)));
        }

        fds[i].fd = fd;
        fds[i].events = POLLIN;
    }

    ///uint64_t session_key_announce_ts = 0;

    for(;;)
    {
#if 1
        printf("[yjl-%s()-%d]--- send:%u-%s\n", __FUNCTION__, __LINE__, *hlCount, hlTestBuf+4);
        t->send_packet(hlTestBuf, 1024, 0);
        (*hlCount)++;
        usleep(1000*1000);
#else
        int rc = poll(fds, nfds, poll_timeout > 0 ? poll_timeout : -1);

        if (rc < 0){
            if (errno == EINTR || errno == EAGAIN) continue;
            throw runtime_error(string_format("poll error: %s", strerror(errno)));
        }

        if (rc == 0) // timeout expired
        {
            t->send_packet(NULL, 0, WFB_PACKET_FEC_ONLY);
            continue;
        }

        for(i = 0; i < nfds; i++)
        {
            // some events detected
            if (fds[i].revents & (POLLERR | POLLNVAL))
            {
                throw runtime_error(string_format("socket error: %s", strerror(errno)));
            }

            if (fds[i].revents & POLLIN)
            {
                uint8_t buf[MAX_PAYLOAD_SIZE];
                ssize_t rsize;
                int fd = rx_fd[i];

                t->select_output(i);
                while((rsize = recv(fd, buf, sizeof(buf), 0)) >= 0)
                {
                    uint64_t cur_ts = get_time_ms();
                    if (cur_ts >= session_key_announce_ts)
                    {
                        // Announce session key
                        t->send_session_key();
                        session_key_announce_ts = cur_ts + SESSION_KEY_ANNOUNCE_MSEC;
                    }
                    t->send_packet(buf, rsize, 0);
                }
                if(errno != EWOULDBLOCK) throw runtime_error(string_format("Error receiving packet: %s", strerror(errno)));
            }
        }
#endif        
    }
}
#endif

static int wfb_tx_mng_init(wfb_mng_tx_p wfb_mng_tx, uint8_t radio_port, int udp_port, string keypair)
{
    if (wfb_mng_tx == NULL) {
        return FAILURE;
    }

    // 1.作者的getopt()的赋值结果
    wfb_mng_tx->radio_port = radio_port;
    wfb_mng_tx->udp_port = udp_port;
    wfb_mng_tx->keypair = keypair;

    // 2.作者测试主函数内的赋值成员
    int opt;
    wfb_mng_tx->k = 8, wfb_mng_tx->n = 12;
    // wfb_mng_tx->radio_port = 0;
    wfb_mng_tx->link_id = 0x0;
    wfb_mng_tx->epoch = 0;
    // wfb_mng_tx->udp_port = 5600;
    // string keypair = "tx.key";

    wfb_mng_tx->bandwidth = 20;
    wfb_mng_tx->short_gi = 0;
    wfb_mng_tx->stbc = 0;
    wfb_mng_tx->ldpc = 0;
    wfb_mng_tx->mcs_index = 2;
    wfb_mng_tx->debug_port = 0;
    wfb_mng_tx->poll_timeout = 0;

    wfb_mng_tx->s32_Rate = 1;
    wfb_mng_tx->s32_TestTime = 1;

    return SUCCESS;
}

static int wfb_tx_random_check(const char* file_path)
{
    int fd;
    int c;

    if ((fd = open(file_path, O_RDONLY)) != -1) {
        if (ioctl(fd, RNDGETENTCNT, &c) == 0 && c < 160) {
            fprintf(stderr, "This system doesn't provide enough entropy to quickly generate high-quality random numbers.\n"
                    "Installing the rng-utils/rng-tools, jitterentropy or haveged packages may help.\n"
                    "On virtualized Linux environments, also consider using virtio-rng.\n"
                    "The service will not start until enough entropy has been collected.\n");
        }
        (void) close(fd);
        return FAILURE;
    }
    return SUCCESS;
}

static int wfb_tx_set_flags(wfb_mng_tx_p wfb_mng_tx)
{
    if (wfb_mng_tx == NULL) {
        return FAILURE;
    }
    
    uint8_t flags = 0;

    switch(wfb_mng_tx->bandwidth) 
    {
    case 20:
        flags |= IEEE80211_RADIOTAP_MCS_BW_20;
        break;
    case 40:
        flags |= IEEE80211_RADIOTAP_MCS_BW_40;
        break;
    default:
        fprintf(stderr, "Unsupported bandwidth: %d\n", wfb_mng_tx->bandwidth);
        return FAILURE;
        // exit(1);
    }

    if(wfb_mng_tx->short_gi)
    {
        flags |= IEEE80211_RADIOTAP_MCS_SGI;
    }

    switch(wfb_mng_tx->stbc) {
    case 0:
        break;
    case 1:
        flags |= (IEEE80211_RADIOTAP_MCS_STBC_1 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
        break;
    case 2:
        flags |= (IEEE80211_RADIOTAP_MCS_STBC_2 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
        break;
    case 3:
        flags |= (IEEE80211_RADIOTAP_MCS_STBC_3 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
        break;
    default:
        fprintf(stderr, "Unsupported STBC type: %d\n", wfb_mng_tx->stbc);
        return FAILURE;
        // exit(1);
    }

    if(wfb_mng_tx->ldpc)
    {
        flags |= IEEE80211_RADIOTAP_MCS_FEC_LDPC;
    }

    wfb_mng_tx->flags = flags;
    radiotap_header[MCS_FLAGS_OFF] = flags;
    radiotap_header[MCS_IDX_OFF] = wfb_mng_tx->mcs_index;

    return SUCCESS;
}

static int wfb_tx_send_init(wfb_mng_tx_p wfb_mng_tx, int count_wlan, char *const wlan_set[])
{
    if (wfb_mng_tx == NULL) {
        return FAILURE;
    }

    int fd = -1;
    int debug_port_tmp = wfb_mng_tx->debug_port;

    for(int i = 0; i < count_wlan; i++)
    {
        fd = open_udp_socket_for_rx(wfb_mng_tx->udp_port + i);
        fprintf(stderr, "Listen on %d for %s\n", wfb_mng_tx->udp_port + i, wlan_set[i]);

        wfb_mng_tx->rx_fd.push_back(fd);
        wfb_mng_tx->wlans.push_back(string(wlan_set[i]));
    }

    wfb_mng_tx->channel_id = (wfb_mng_tx->link_id << 8) + wfb_mng_tx->radio_port;

    if(debug_port_tmp)
    {
        fprintf(stderr, "Using %zu ports from %d for wlan emulation\n", wfb_mng_tx->wlans.size(), debug_port_tmp);
        wfb_mng_tx->t = shared_ptr<UdpTransmitter>(new UdpTransmitter(wfb_mng_tx->k, wfb_mng_tx->n, wfb_mng_tx->keypair, 
                HL_WFB_TX_CLIENT_ADDR, debug_port_tmp, wfb_mng_tx->epoch, wfb_mng_tx->channel_id));
    } else {
        wfb_mng_tx->t = shared_ptr<PcapTransmitter>(new PcapTransmitter(wfb_mng_tx->k, wfb_mng_tx->n, wfb_mng_tx->keypair,
                 wfb_mng_tx->epoch, wfb_mng_tx->channel_id, wfb_mng_tx->wlans));
    }

    return SUCCESS;
}

int wfb_tx_init(wfb_mng_tx_p wfb_mng_tx, int count_wlan, char *const wlan_set[] )
{
    if (wfb_mng_tx == NULL) {
        return FAILURE;
    }

    int ret = -1;

    if ( wfb_tx_mng_init(wfb_mng_tx, 1, 5600, "/tmp/firmware/gs.key") != 0 ) {
        fprintf(stderr, "wfb rx mng_init failed!!!\n");
    }

    if ( wfb_tx_random_check(HL_WFB_TX_RANDOM_FLIE) != 0 ) {
        fprintf(stderr, "wfb rx random failed!!!\n");
    }

    if ( sodium_init() < 0 ) {
        fprintf(stderr, "Libsodium init failed!!!\n");
    }

    if ( wfb_tx_set_flags(wfb_mng_tx) != 0 ) {
        fprintf(stderr, "wfb tx set flags failed!!!\n");
    }

    if ( wfb_tx_send_init(wfb_mng_tx, count_wlan, wlan_set) != 0) {
        fprintf(stderr, "wfb tx send init failed!!!\n");        
    }

    return SUCCESS;
}

int wfb_tx_deinit(wfb_mng_tx_p wfb_mng_tx)
{
    if (wfb_mng_tx == NULL) {
        return FAILURE;
    }
}

int wfb_tx_send_with_block(wfb_mng_tx_p wfb_mng_tx, const uint8_t** data_block, int* data_len_array, int* data_flags_array)
{
    if (wfb_mng_tx == NULL || data_block == NULL || data_len_array == NULL || data_flags_array == NULL) {
        return FAILURE;
    }

    for (int index = 0; (index < wfb_mng_tx->n) && (data_len_array[index] > -1); index++) {
        wfb_mng_tx->t->send_packet(data_block[index], data_len_array[index], data_flags_array[index]);
    }

    return SUCCESS;
}

int wfb_tx_send_with_fragment(wfb_mng_tx_p wfb_mng_tx, const uint8_t* data_buff, int data_len, int data_flags)
{
    if (wfb_mng_tx == NULL || data_buff == NULL || data_len < 0) {
        return FAILURE;
    }

    wfb_mng_tx->t->send_packet(data_buff, data_len, data_flags);

    return SUCCESS;
}


int main(int argc, char * const *argv)
{
    int count = 0;
    wfb_mng_tx_t wfb_mng_tx;
    wfb_mng_tx_p wfb_mng_tx_ptr = &wfb_mng_tx;
    int count_wlan = 1;
    const uint8_t u8SendBuf[30] = {1, 2, 3, 4, 5, 6, 7, 8};
    char *const wlan_set[] = {"wlan0", "wlan1"};

    hl_wbcast_header_t *pstWbcastHead = (hl_wbcast_header_t *)u8SendBuf;

    // memset(u8SendBuf, 0, sizeof(u8SendBuf));                              // 负载数据均为 0
    pstWbcastHead->u32Seq = 1;
    pstWbcastHead->u32Len = 1400;

    wfb_tx_init(wfb_mng_tx_ptr, count_wlan, wlan_set);
    printf("111111\n");

    try {
        for (int i = 0; i < 12; i++) {
        if (wfb_tx_send_with_fragment(wfb_mng_tx_ptr, (const uint8_t*)u8SendBuf, 30, 0) == 0) {
            printf("send success\n");
        }
    }
    } catch(runtime_error &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    
    }

    wfb_tx_deinit(wfb_mng_tx_ptr);


    // try {
    //     ///data_source(t, rx_fd, poll_timeout);
    //     data_source(wfb_mng_tx_ptr->t, wfb_mng_tx_ptr->rx_fd, wfb_mng_tx_ptr->poll_timeout, 
    //             wfb_mng_tx_ptr->s32_Rate, wfb_mng_tx_ptr->s32_TestTime);

    // } catch(runtime_error &e) {
    //     fprintf(stderr, "Error: %s\n", e.what());
    //     exit(1);
    
    // }

    return 0;
}

int main1(int argc, char * const *argv)
{
    int opt;
    uint8_t k = 8, n = 12, radio_port = 0;
    uint32_t link_id = 0x0;
    uint64_t epoch = 0;
    int udp_port = 5600;

    int bandwidth = 20;
    int short_gi = 0;
    int stbc = 0;
    int ldpc = 0;
    int mcs_index = 2;
    int debug_port = 0;
    int poll_timeout = 0;

    int s32Rate = 1;
    int s32TestTime = 1;

    string keypair = "tx.key";
    // /tmp/firmware/wfb_tx -p 1 -u 5600 -K drone.key wlan0 &
    // argv[2] = -p, optarg: 1                          radio_port = 1
    // argv[3] = -u, optarg: 5600                       udp_port = 5600
    // argv[5] = -K, optarg: /tmp/firmware/drone.key    key_pair = "/tmp/firmware/drone.key"
    while ((opt = getopt(argc, argv, "K:k:n:u:r:p:B:G:S:L:M:D:T:i:e:R:t:")) != -1) {
        switch (opt) {
        case 'K':
            keypair = optarg;
            break;
        case 'k':
            k = atoi(optarg);
            break;
        case 'n':
            n = atoi(optarg);
            break;
        case 'u':
            udp_port = atoi(optarg);
            break;
        case 'p':
            radio_port = atoi(optarg);
            break;
        case 'B':
            bandwidth = atoi(optarg);
            break;
        case 'G':
            short_gi = (optarg[0] == 's' || optarg[0] == 'S') ? 1 : 0;
            break;
        case 'S':
            stbc = atoi(optarg);
            break;
        case 'L':
            ldpc = atoi(optarg);
            break;
        case 'M':
            mcs_index = atoi(optarg);
            break;
        case 'D':
            debug_port = atoi(optarg);
            break;
        case 'T':
            poll_timeout = atoi(optarg);
            break;
        case 'i':
            link_id = ((uint32_t)atoi(optarg)) & 0xffffff;
            break;
        case 'e':
            epoch = atoll(optarg);
            break;
        case 'R':///码流大小
            s32Rate = atoll(optarg);
            break;
        case 't':///测试时间
            s32TestTime = atoll(optarg);
            break;
        default: /* '?' */
        show_usage:
            fprintf(stderr, "Usage: %s [-K tx_key] [-k RS_K] [-n RS_N] [-u udp_port] [-p radio_port] [-B bandwidth] [-G guard_interval] [-S stbc] [-L ldpc] [-M mcs_index] [-T poll_timeout] [-e epoch] [-i link_id] interface1 [interface2] ...\n",
                    argv[0]);
            fprintf(stderr, "Default: K='%s', k=%d, n=%d, udp_port=%d, link_id=0x%06x, radio_port=%u, epoch=%" PRIu64 ", bandwidth=%d guard_interval=%s stbc=%d ldpc=%d mcs_index=%d, poll_timeout=%d\n",
                    keypair.c_str(), k, n, udp_port, link_id, radio_port, epoch, bandwidth, short_gi ? "short" : "long", stbc, ldpc, mcs_index, poll_timeout);
            fprintf(stderr, "Radio MTU: %lu\n", (unsigned long)MAX_PAYLOAD_SIZE);
            fprintf(stderr, "WFB-ng version " WFB_VERSION "\n");
            fprintf(stderr, "WFB-ng home page: <http://wfb-ng.org>\n");
            exit(1);
        }
    }

    if (optind >= argc) {
        goto show_usage;
    }

    // Set flags in radiotap header
    {
        uint8_t flags = 0;
        switch(bandwidth) {
        case 20:
            flags |= IEEE80211_RADIOTAP_MCS_BW_20;
            break;
        case 40:
            flags |= IEEE80211_RADIOTAP_MCS_BW_40;
            break;
        default:
            fprintf(stderr, "Unsupported bandwidth: %d\n", bandwidth);
            exit(1);
        }

        if(short_gi)
        {
            flags |= IEEE80211_RADIOTAP_MCS_SGI;
        }

        switch(stbc) {
        case 0:
            break;
        case 1:
            flags |= (IEEE80211_RADIOTAP_MCS_STBC_1 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
            break;
        case 2:
            flags |= (IEEE80211_RADIOTAP_MCS_STBC_2 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
            break;
        case 3:
            flags |= (IEEE80211_RADIOTAP_MCS_STBC_3 << IEEE80211_RADIOTAP_MCS_STBC_SHIFT);
            break;
        default:
            fprintf(stderr, "Unsupported STBC type: %d\n", stbc);
            exit(1);
        }

        if(ldpc)
        {
            flags |= IEEE80211_RADIOTAP_MCS_FEC_LDPC;
        }

        radiotap_header[MCS_FLAGS_OFF] = flags;
        radiotap_header[MCS_IDX_OFF] = mcs_index;
    }

    {
        int fd;
        int c;

        if ((fd = open("/dev/random", O_RDONLY)) != -1) {
            if (ioctl(fd, RNDGETENTCNT, &c) == 0 && c < 160) {
                fprintf(stderr, "This system doesn't provide enough entropy to quickly generate high-quality random numbers.\n"
                        "Installing the rng-utils/rng-tools, jitterentropy or haveged packages may help.\n"
                        "On virtualized Linux environments, also consider using virtio-rng.\n"
                        "The service will not start until enough entropy has been collected.\n");
            }
            (void) close(fd);
        }
    }

    if (sodium_init() < 0)
    {
        fprintf(stderr, "Libsodium init failed\n");
        return 1;
    }

    try
    {
        vector<int> rx_fd;
        vector<string> wlans;
        for(int i = 0; optind + i < argc; i++)
        {
            int fd = open_udp_socket_for_rx(udp_port + i);
            fprintf(stderr, "Listen on %d for %s\n", udp_port + i, argv[optind + i]);
            rx_fd.push_back(fd);
            wlans.push_back(string(argv[optind + i]));
        }

        shared_ptr<Transmitter> t;

        uint32_t channel_id = (link_id << 8) + radio_port;

        if(debug_port)
        {
            fprintf(stderr, "Using %zu ports from %d for wlan emulation\n", wlans.size(), debug_port);
            t = shared_ptr<UdpTransmitter>(new UdpTransmitter(k, n, keypair, "127.0.0.1", debug_port, epoch, channel_id));
        } else {
            t = shared_ptr<PcapTransmitter>(new PcapTransmitter(k, n, keypair, epoch, channel_id, wlans));
        }

        ///data_source(t, rx_fd, poll_timeout);
        data_source(t, rx_fd, poll_timeout, s32Rate, s32TestTime);
    }catch(runtime_error &e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
    return 0;
}

