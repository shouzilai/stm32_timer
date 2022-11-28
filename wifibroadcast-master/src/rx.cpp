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

#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <pcap/pcap.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <linux/random.h>

extern "C"
{
#include "ieee80211_radiotap.h"
#include "fec.h"
}

#include <string>
#include <memory>

#include "wifibroadcast.hpp"
#include "rx.hpp"

using namespace std;

static wfb_mng_rx_p wfb_mng_ptr = NULL;

Receiver::Receiver(const char *wlan, int wlan_idx, uint32_t channel_id, BaseAggregator *agg) : wlan_idx(wlan_idx), agg(agg)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    ppcap = pcap_create(wlan, errbuf);

    if (ppcap == NULL){
        throw runtime_error(string_format("Unable to open interface %s in pcap: %s", wlan, errbuf));
    }

    if (pcap_set_snaplen(ppcap, 4096) !=0) throw runtime_error("set_snaplen failed");
    if (pcap_set_promisc(ppcap, 1) != 0) throw runtime_error("set_promisc failed");
    if (pcap_set_timeout(ppcap, -1) !=0) throw runtime_error("set_timeout failed");
    if (pcap_set_immediate_mode(ppcap, 1) != 0) throw runtime_error(string_format("pcap_set_immediate_mode failed: %s", pcap_geterr(ppcap)));
    if (pcap_activate(ppcap) !=0) throw runtime_error(string_format("pcap_activate failed: %s", pcap_geterr(ppcap)));
    if (pcap_setnonblock(ppcap, 1, errbuf) != 0) throw runtime_error(string_format("set_nonblock failed: %s", errbuf));

    int link_encap = pcap_datalink(ppcap);
    struct bpf_program bpfprogram;
    string program;

    if (link_encap != DLT_IEEE802_11_RADIO) {
        throw runtime_error(string_format("unknown encapsulation on %s", wlan));
    }

    program = string_format("ether[0x0a:2]==0x5742 && ether[0x0c:4] == 0x%08x", channel_id);

    if (pcap_compile(ppcap, &bpfprogram, program.c_str(), 1, 0) == -1) {
        throw runtime_error(string_format("Unable to compile %s: %s", program.c_str(), pcap_geterr(ppcap)));
    }

    if (pcap_setfilter(ppcap, &bpfprogram) == -1) {
        throw runtime_error(string_format("Unable to set filter %s: %s", program.c_str(), pcap_geterr(ppcap)));
    }

    pcap_freecode(&bpfprogram);
    fd = pcap_get_selectable_fd(ppcap);
}


Receiver::~Receiver()
{
    close(fd);
    pcap_close(ppcap);
}


void Receiver::loop_iter(void)
{
    int count = 0;
    // for(;;) // loop while incoming queue is not empty
    // {
    struct pcap_pkthdr hdr;
    // /* 自定义头部在把数据包保存到文件中也被使用 */
    // struct pcap_pkthdr
    // {
    //    struct timeval ts; /* 捕获时间戳 */
    //    bpf_u_int32 caplen; /* 捕获到数据包的长度 */
    //    bpf_u_int32 len; /* 数据包的真正长度 */
    // };
    const uint8_t* pkt = pcap_next(ppcap, &hdr);///根据ppcap句柄，接收一个数据包立即返回，pkt 将为接收到的 数据包地址
    if (pkt == NULL || count++ > 2) {
        return;
    }

    int pktlen = hdr.caplen;
    int ant_idx = 0;
    // int pkt_rate = 0
    uint8_t antenna[RX_ANT_MAX];
    int8_t rssi[RX_ANT_MAX];
    uint8_t flags = 0;
    wfb_mng_ptr->pcap_data_buffer = pkt;
    wfb_mng_ptr->pcap_data_len = pktlen;
    struct ieee80211_radiotap_iterator iterator;
    int ret = ieee80211_radiotap_iterator_init(&iterator, (ieee80211_radiotap_header*)pkt, pktlen, NULL);

    printf("\n\ncircle start~~~~~~\n");// 1479   1479
    printf("[fengshou-%s()-%d]--- hdr.caplen:%d, pktlen:%d\n", __FUNCTION__, __LINE__, hdr.caplen, pktlen);
    ///printf("[yjl-%s()-%d]--- hdr.caplen:%d, pktlen:%d\n", __FUNCTION__, __LINE__, hdr.caplen, pktlen);
    // Fill all antenna slots with 0xff (unused)
    memset(antenna, 0xff, sizeof(antenna));
    memset(rssi, SCHAR_MIN, sizeof(rssi));
    // Fill all rssi slots with minimum value

    while (ret == 0 && ant_idx < RX_ANT_MAX) {
        ret = ieee80211_radiotap_iterator_next(&iterator);

        if (ret)
            continue;

        /* see if this argument is something we can use */

        switch (iterator.this_arg_index)
        {
            /*
                * You must take care when dereferencing iterator.this_arg
                * for multibyte types... the pointer is not aligned.  Use
                * get_unaligned((type *)iterator.this_arg) to dereference
                * iterator.this_arg for type "type" safely on all arches.
                */

            // case IEEE80211_RADIOTAP_RATE:
            //     /* radiotap "rate" u8 is in
            //      * 500kbps units, eg, 0x02=1Mbps
            //      */
            //     pkt_rate = (*(uint8_t*)(iterator.this_arg))/2;
            //     break;

        case IEEE80211_RADIOTAP_ANTENNA:
            // FIXME
            // In case of multiple antenna stats in one packet this index will be irrelivant
            antenna[ant_idx] = *(uint8_t*)(iterator.this_arg);
            ant_idx += 1;
            break;

        case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
            // Some cards can provide rssi for multiple antennas in one packet, so we should select maximum value
            rssi[ant_idx] = *(int8_t*)(iterator.this_arg);
            break;

        case IEEE80211_RADIOTAP_FLAGS:
            flags = *(uint8_t*)(iterator.this_arg);
            break;

        default:
            break;
        }
    }  /* while more rt headers */

    if (ret != -ENOENT && ant_idx < RX_ANT_MAX){
        fprintf(stderr, "Error parsing radiotap header!\n");
        // continue;
    }

    if (flags & IEEE80211_RADIOTAP_F_FCS)
    {
        pktlen -= 4;
    }

    if (flags & IEEE80211_RADIOTAP_F_BADFCS)
    {
        fprintf(stderr, "Got packet with bad fsc\n");
        // continue;
    }

    /* discard the radiotap header part */
    pkt += iterator._max_length;
    pktlen -= iterator._max_length;
    ///printf("[yjl-%s()-%d]--- discard the radiotap header part, iterator._max_length:%d, pktlen:%d\n", __FUNCTION__, __LINE__, iterator._max_length, pktlen);
                                                                            // 35  1440
    printf("[fengshou-%s()-%d]--- discard the radiotap header part, iterator._max_length:%d, pktlen:%d\n", __FUNCTION__, __LINE__, iterator._max_length, pktlen);

    if (pktlen > (int)sizeof(ieee80211_header))
    {
        /* discard the ieee80211_header header part */
        pkt += sizeof(ieee80211_header);
        pktlen -= sizeof(ieee80211_header);
        ///printf("[yjl-%s()-%d]--- discard the radiotap header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
                                                                            //  1416
        printf("[fengshou-%s()-%d]--- discard the radiotap header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);

        /* discard the LLC header part */
        pkt += 4;
        pktlen -= 4;
        ///printf("[yjl-%s()-%d]--- discard the LLC header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
                                //  此处数据长度为 1412 意味着，成功将 负载数据长度计算出来了。
        printf("[fengshou-%s()-%d]--- discard the LLC header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);

        // agg->process_packet(pkt, pktlen, wlan_idx, antenna, rssi, NULL);
        //agg->process_packet(pkt + sizeof(ieee80211_header), pktlen - sizeof(ieee80211_header), wlan_idx, antenna, rssi, NULL);
        printf("[fengshou-%s()-%d]---agg->process_packet\n", __FUNCTION__, __LINE__);
    } else {
        fprintf(stderr, "Short packet (ieee header)\n");
        // continue;
    }
    // 接收成功的回调函数
    wfb_mng_ptr->wfb_recive_success_handle_func(wfb_mng_ptr->pcap_data_buffer, &wfb_mng_ptr->pcap_data_len);
}

// void Receiver::loop_iter(void)
// {
//     int count = 0;
//     // for(;;) // loop while incoming queue is not empty
//     // {
//     struct pcap_pkthdr hdr;
//     // /* 自定义头部在把数据包保存到文件中也被使用 */
//     // struct pcap_pkthdr
//     // {
//     //    struct timeval ts; /* 捕获时间戳 */
//     //    bpf_u_int32 caplen; /* 捕获到数据包的长度 */
//     //    bpf_u_int32 len; /* 数据包的真正长度 */
//     // };
//     const uint8_t* pkt = pcap_next(ppcap, &hdr);///根据ppcap句柄，接收一个数据包立即返回，pkt 将为接收到的 数据包地址
//     if (pkt == NULL || count++ > 2) {
//         printf("\n\ncircle over~~~~~~\n[fengshou-%s()-%d]--- branch of loop_iter: break\n", __FUNCTION__, __LINE__);
//         return;
//         // break;
//     }
//     int pktlen = hdr.caplen;
//     // int pkt_rate = 0
//     int ant_idx = 0;
//     uint8_t antenna[RX_ANT_MAX];
//     int8_t rssi[RX_ANT_MAX];
//     uint8_t flags = 0;
//     struct ieee80211_radiotap_iterator iterator;
//     int ret = ieee80211_radiotap_iterator_init(&iterator, (ieee80211_radiotap_header*)pkt, pktlen, NULL);
//     printf("\n\ncircle start~~~~~~\n");// 1479   1479
//     printf("[fengshou-%s()-%d]--- hdr.caplen:%d, pktlen:%d\n", __FUNCTION__, __LINE__, hdr.caplen, pktlen);
//     ///printf("[yjl-%s()-%d]--- hdr.caplen:%d, pktlen:%d\n", __FUNCTION__, __LINE__, hdr.caplen, pktlen);
//     // Fill all antenna slots with 0xff (unused)
//     memset(antenna, 0xff, sizeof(antenna));
//     // Fill all rssi slots with minimum value
//     memset(rssi, SCHAR_MIN, sizeof(rssi));
//     while (ret == 0 && ant_idx < RX_ANT_MAX) {
//         ret = ieee80211_radiotap_iterator_next(&iterator);
//         if (ret)
//             continue;
//         /* see if this argument is something we can use */
//         switch (iterator.this_arg_index)
//         {
//             /*
//                 * You must take care when dereferencing iterator.this_arg
//                 * for multibyte types... the pointer is not aligned.  Use
//                 * get_unaligned((type *)iterator.this_arg) to dereference
//                 * iterator.this_arg for type "type" safely on all arches.
//                 */
//             // case IEEE80211_RADIOTAP_RATE:
//             //     /* radiotap "rate" u8 is in
//             //      * 500kbps units, eg, 0x02=1Mbps
//             //      */
//             //     pkt_rate = (*(uint8_t*)(iterator.this_arg))/2;
//             //     break;
//         case IEEE80211_RADIOTAP_ANTENNA:
//             // FIXME
//             // In case of multiple antenna stats in one packet this index will be irrelivant
//             antenna[ant_idx] = *(uint8_t*)(iterator.this_arg);
//             ant_idx += 1;
//             break;
//         case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
//             // Some cards can provide rssi for multiple antennas in one packet, so we should select maximum value
//             rssi[ant_idx] = *(int8_t*)(iterator.this_arg);
//             break;
//         case IEEE80211_RADIOTAP_FLAGS:
//             flags = *(uint8_t*)(iterator.this_arg);
//             break;
//         default:
//             break;
//         }
//     }  /* while more rt headers */
//     if (ret != -ENOENT && ant_idx < RX_ANT_MAX){
//         fprintf(stderr, "Error parsing radiotap header!\n");
//         // continue;
//     }
//     if (flags & IEEE80211_RADIOTAP_F_FCS)
//     {
//         pktlen -= 4;
//     }
//     if (flags & IEEE80211_RADIOTAP_F_BADFCS)
//     {
//         fprintf(stderr, "Got packet with bad fsc\n");
//         // continue;
//     }
//     /* discard the radiotap header part */
//     pkt += iterator._max_length;
//     pktlen -= iterator._max_length;
//     ///printf("[yjl-%s()-%d]--- discard the radiotap header part, iterator._max_length:%d, pktlen:%d\n", __FUNCTION__, __LINE__, iterator._max_length, pktlen);
//                                                                             // 35  1440
//     printf("[fengshou-%s()-%d]--- discard the radiotap header part, iterator._max_length:%d, pktlen:%d\n", __FUNCTION__, __LINE__, iterator._max_length, pktlen);
//     if (pktlen > (int)sizeof(ieee80211_header))
//     {
//         /* discard the ieee80211_header header part */
//         pkt += sizeof(ieee80211_header);
//         pktlen -= sizeof(ieee80211_header);
//         ///printf("[yjl-%s()-%d]--- discard the radiotap header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
//                                                                             //  1416
//         printf("[fengshou-%s()-%d]--- discard the radiotap header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
//         /* discard the LLC header part */
//         pkt += 4;
//         pktlen -= 4;
//         ///printf("[yjl-%s()-%d]--- discard the LLC header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
//                                 //  此处数据长度为 1412 意味着，成功将 负载数据长度计算出来了。
//         printf("[fengshou-%s()-%d]--- discard the LLC header part, pktlen:%d\n", __FUNCTION__, __LINE__, pktlen);
//         // agg->process_packet(pkt, pktlen, wlan_idx, antenna, rssi, NULL);
//         //agg->process_packet(pkt + sizeof(ieee80211_header), pktlen - sizeof(ieee80211_header), wlan_idx, antenna, rssi, NULL);
//         printf("[fengshou-%s()-%d]---agg->process_packet\n", __FUNCTION__, __LINE__);
//     } else {
//         fprintf(stderr, "Short packet (ieee header)\n");
//         // continue;
//     }
//     // 接收成功的回调函数
//     wfb_mng_ptr->wfb_recive_success_handle_func(wfb_mng_ptr);
// }
// }


Aggregator::Aggregator(const string &client_addr, int client_port, int k, int n, const string &keypair, uint64_t epoch, uint32_t channel_id) : \
    fec_k(k), fec_n(n), seq(0), rx_ring_front(0), rx_ring_alloc(0),
    last_known_block((uint64_t)-1), epoch(epoch), channel_id(channel_id),
    count_p_all(0), count_p_dec_err(0), count_p_dec_ok(0), count_p_fec_recovered(0),
    count_p_lost(0), count_p_bad(0), count_p_override(0)
{
    sockfd = open_udp_socket_for_tx(client_addr, client_port);
    fec_p = fec_new(fec_k, fec_n);
    memset(session_key, '\0', sizeof(session_key));

    for(int ring_idx = 0; ring_idx < RX_RING_SIZE; ring_idx++)
    {
        rx_ring[ring_idx].block_idx = 0;
        rx_ring[ring_idx].fragment_to_send_idx = 0;
        rx_ring[ring_idx].has_fragments = 0;
        rx_ring[ring_idx].fragments = new uint8_t*[fec_n];
        for(int i=0; i < fec_n; i++)
        {
            rx_ring[ring_idx].fragments[i] = new uint8_t[MAX_FEC_PAYLOAD];
        }
        rx_ring[ring_idx].fragment_map = new uint8_t[fec_n];
        memset(rx_ring[ring_idx].fragment_map, '\0', fec_n * sizeof(uint8_t));
    }

    FILE *fp;
    if((fp = fopen(keypair.c_str(), "r")) == NULL)
    {
        throw runtime_error(string_format("Unable to open %s: %s", keypair.c_str(), strerror(errno)));
    }
    if (fread(rx_secretkey, crypto_box_SECRETKEYBYTES, 1, fp) != 1)
    {
        fclose(fp);
        throw runtime_error(string_format("Unable to read rx secret key: %s", strerror(errno)));
    }
    if (fread(tx_publickey, crypto_box_PUBLICKEYBYTES, 1, fp) != 1)
    {
        fclose(fp);
        throw runtime_error(string_format("Unable to read tx public key: %s", strerror(errno)));
    }
    fclose(fp);
}


Aggregator::~Aggregator()
{

    for(int ring_idx = 0; ring_idx < RX_RING_SIZE; ring_idx++)
    {
        delete rx_ring[ring_idx].fragment_map;
        for(int i=0; i < fec_n; i++)
        {
            delete rx_ring[ring_idx].fragments[i];
        }
        delete rx_ring[ring_idx].fragments;
    }

    fec_free(fec_p);
    close(sockfd);
}


Forwarder::Forwarder(const string &client_addr, int client_port)
{
    sockfd = open_udp_socket_for_tx(client_addr, client_port);
}


void Forwarder::process_packet(const uint8_t *buf, size_t size, uint8_t wlan_idx, const uint8_t *antenna, const int8_t *rssi, sockaddr_in *sockaddr)
{
    wrxfwd_t fwd_hdr = { .wlan_idx = wlan_idx };

    memcpy(fwd_hdr.antenna, antenna, RX_ANT_MAX * sizeof(uint8_t));
    memcpy(fwd_hdr.rssi, rssi, RX_ANT_MAX * sizeof(int8_t));

    struct iovec iov[2] = {{ .iov_base = (void*)&fwd_hdr,
                             .iov_len = sizeof(fwd_hdr)},
                           { .iov_base = (void*)buf,
                             .iov_len = size }};

    struct msghdr msghdr = { .msg_name = NULL,
                             .msg_namelen = 0,
                             .msg_iov = iov,
                             .msg_iovlen = 2,
                             .msg_control = NULL,
                             .msg_controllen = 0,
                             .msg_flags = 0};

    sendmsg(sockfd, &msghdr, MSG_DONTWAIT);
}


Forwarder::~Forwarder()
{
    close(sockfd);
}

int Aggregator::rx_ring_push(void)
{
    if(rx_ring_alloc < RX_RING_SIZE)
    {
        ///printf("[yjl-%s()-%d]--- rx_ring_front:%d, rx_ring_alloc:%d\n", __FUNCTION__, __LINE__, rx_ring_front, rx_ring_alloc);
        int idx = modN(rx_ring_front + rx_ring_alloc, RX_RING_SIZE);
        rx_ring_alloc += 1;
        return idx;
    }

    /*
      Ring overflow. This means that there are more unfinished blocks than ring size
      Possible solutions:
      1. Increase ring size. Do this if you have large variance of packet travel time throught WiFi card or network stack.
         Some cards can do this due to packet reordering inside, diffent chipset and/or firmware or your RX hosts have different CPU power.
      2. Reduce packet injection speed or try to unify RX hardware.
    */

#if 0
    fprintf(stderr, "Override block 0x%" PRIx64 " flush %d fragments\n", rx_ring[rx_ring_front].block_idx, rx_ring[rx_ring_front].has_fragments);
#endif

    count_p_override += 1;

    for(int f_idx = rx_ring[rx_ring_front].fragment_to_send_idx; f_idx < fec_k; f_idx++)
    {
        if(rx_ring[rx_ring_front].fragment_map[f_idx])
        {
            printf("[yjl-%s()-%d]--- 44444444444444444\n", __FUNCTION__, __LINE__);
            send_packet(rx_ring_front, f_idx);
        }
    }

    // override last item in ring
    int ring_idx = rx_ring_front;
    rx_ring_front = modN(rx_ring_front + 1, RX_RING_SIZE);
    return ring_idx;
}


int Aggregator::get_block_ring_idx(uint64_t block_idx)
{
    // check if block is already in the ring   block_idx = 1005 rx_ring_front= 1005，rx_ring_alloc = 0
    printf("[fengshou-%s()-%d]--- rx_ring_front:%d, rx_ring_alloc:%d last_known_block:%d\n", __FUNCTION__, __LINE__, rx_ring_front, rx_ring_alloc, last_known_block);
    for(int i = rx_ring_front, c = rx_ring_alloc; c > 0; i = modN(i + 1, RX_RING_SIZE), c--)
    {
        ///printf("[yjl-%s()-%d]--- rx_ring[i].block_idx:%llu, block_idx:%llu\n", __FUNCTION__, __LINE__, rx_ring[i].block_idx, block_idx);
        if (rx_ring[i].block_idx == block_idx) return i;
    }

    // printf("[yjl-%s()-%d]--- 5555555555555555\n", __FUNCTION__, __LINE__);
    // check if block is already known and not in the ring then it is already processed
    // if (last_known_block != ((uint64_t)-1 && block_idx <= last_known_block))
    // {
    //     return -1;
    // }

    ///printf("[yjl-%s()-%d]--- block_idx:%llu, last_known_block:%llu\n", __FUNCTION__, __LINE__, block_idx, last_known_block);
    printf("[fengshou-%s()-%d]--- block_idx:%d, last_known_block:%d\n", __FUNCTION__, __LINE__, block_idx, last_known_block);
    int new_blocks = (int)min(last_known_block != (uint64_t)-1 ? block_idx - last_known_block : 1, (uint64_t)RX_RING_SIZE);
    assert (new_blocks > 0);

    last_known_block = block_idx;
    int ring_idx = -1;
    ///printf("[yjl-%s()-%d]--- new_blocks:%d\n", __FUNCTION__, __LINE__, new_blocks);
    printf("[fengshou-%s()-%d]--- new_blocks:%d\n", __FUNCTION__, __LINE__, new_blocks);
    for(int i = 0; i < new_blocks; i++)
    {
        ring_idx = rx_ring_push();
        rx_ring[ring_idx].block_idx = block_idx + i + 1 - new_blocks;
        rx_ring[ring_idx].fragment_to_send_idx = 0;
        rx_ring[ring_idx].has_fragments = 0;
        memset(rx_ring[ring_idx].fragment_map, '\0', fec_n * sizeof(uint8_t));
    }
    return ring_idx;
}

void Aggregator::dump_stats(FILE *fp)
{
    //timestamp in ms
    uint64_t ts = get_time_ms();

    for(antenna_stat_t::iterator it = antenna_stat.begin(); it != antenna_stat.end(); it++)
    {
        fprintf(fp, "%" PRIu64 "\tANT\t%" PRIx64 "\t%d:%d:%d:%d\n", ts, it->first, it->second.count_all, it->second.rssi_min, it->second.rssi_sum / it->second.count_all, it->second.rssi_max);
    }
    antenna_stat.clear();

    fprintf(fp, "%" PRIu64 "\tPKT\t%u:%u:%u:%u:%u:%u\n", ts, count_p_all, count_p_dec_err, count_p_dec_ok, count_p_fec_recovered, count_p_lost, count_p_bad);
    fflush(fp);// 及时输出需要的内容

    if(count_p_override)
    {
        fprintf(stderr, "%u block overrides\n", count_p_override);
    }

    if(count_p_lost)
    {
        fprintf(stderr, "%u packets lost\n", count_p_lost);
    }

    count_p_all = 0;
    count_p_dec_err = 0;
    count_p_dec_ok = 0;
    count_p_fec_recovered = 0;
    count_p_lost = 0;
    count_p_bad = 0;
    count_p_override = 0;
}


void Aggregator::log_rssi(const sockaddr_in *sockaddr, uint8_t wlan_idx, const uint8_t *ant, const int8_t *rssi)
{
    for(int i = 0; i < RX_ANT_MAX && ant[i] != 0xff; i++)
    {
        // key: addr + port + wlan_idx + ant
        uint64_t key = 0;
        if (sockaddr != NULL && sockaddr->sin_family == AF_INET)
        {
            key = ((uint64_t)ntohl(sockaddr->sin_addr.s_addr) << 32 | (uint64_t)ntohs(sockaddr->sin_port) << 16);
        }

        key |= ((uint64_t)wlan_idx << 8 | (uint64_t)ant[i]);

        antenna_stat[key].log_rssi(rssi[i]);
    }
}


void Aggregator::process_packet(const uint8_t *buf, size_t size, uint8_t wlan_idx, const uint8_t *antenna, const int8_t *rssi, sockaddr_in *sockaddr)
{
    wsession_data_t new_session_data;
    count_p_all += 1;/// 统计一次读事件共接收多少包数据

    if(size == 0) return;

    if (size > MAX_FORWARDER_PACKET_SIZE)
    {
        fprintf(stderr, "Long packet (fec payload)\n");
        count_p_bad += 1;///统计一次读事件中有多少包数据"存在异常"
        return;
    }

    ///printf("[yjl-%s()-%d]--- Aggregator::process_packet start, size:%d, buf[0]:%d, wlan_idx:%d\n", __FUNCTION__, __LINE__, size, buf[0], wlan_idx);
                                                                    // 1412 1 0
    printf("[fengshou-%s()-%d]--- Aggregator::process_packet start, size:%d, buf[0]:%d, wlan_idx:%d\n", __FUNCTION__, __LINE__, size, buf[0], wlan_idx);
    switch(buf[0])
    {
        case WFB_PACKET_DATA:
            if(size < sizeof(wblock_hdr_t) + sizeof(wpacket_hdr_t))
            {
                fprintf(stderr, "Short packet (fec header)\n");
                count_p_bad += 1;///统计一次读事件中有多少包数据存在异常
                return;
            }
            ///printf("[yjl-%s()-%d]--- parse WFB_PACKET_DATA\n");
            break;

        case WFB_PACKET_KEY:
            if(size != sizeof(wsession_hdr_t) + sizeof(wsession_data_t) + crypto_box_MACBYTES)
            {
                fprintf(stderr, "Invalid session key packet\n");
                count_p_bad += 1;
                return;
            }

            if(crypto_box_open_easy((uint8_t*)&new_session_data,
                                    buf + sizeof(wsession_hdr_t),
                                    sizeof(wsession_data_t) + crypto_box_MACBYTES,
                                    ((wsession_hdr_t*)buf)->session_nonce,
                                    tx_publickey, rx_secretkey) != 0)
            {
                fprintf(stderr, "Unable to decrypt session key\n");
                count_p_dec_err += 1;
                return;
            }

            if (be64toh(new_session_data.epoch) < epoch)
            {
                fprintf(stderr, "Session epoch doesn't match\n");
                count_p_dec_err += 1;
                return;
            }

            if (be32toh(new_session_data.channel_id) != channel_id)
            {
                fprintf(stderr, "Session channel_id doesn't match\n");
                count_p_dec_err += 1;
                return;
            }

            if (new_session_data.k != fec_k ||
                new_session_data.n != fec_n ||
                new_session_data.fec_type != WFB_FEC_VDM_RS)
            {
                fprintf(stderr, "Session FEC settings doesn't match\n");
                count_p_dec_err += 1;
                return;
            }

            count_p_dec_ok += 1;
            epoch = be64toh(new_session_data.epoch);

            if (memcmp(session_key, new_session_data.session_key, sizeof(session_key)) != 0)
            {
                fprintf(stderr, "New session detected\n");
                memcpy(session_key, new_session_data.session_key, sizeof(session_key));

                rx_ring_front = 0;
                rx_ring_alloc = 0;
                last_known_block = (uint64_t)-1;
                seq = 0;
                for(int ring_idx = 0; ring_idx < RX_RING_SIZE; ring_idx++)
                {
                    rx_ring[ring_idx].block_idx = 0;
                    rx_ring[ring_idx].fragment_to_send_idx = 0;
                    rx_ring[ring_idx].has_fragments = 0;
                    memset(rx_ring[ring_idx].fragment_map, '\0', fec_n * sizeof(uint8_t));
                }
            }
            return;

        default:
            fprintf(stderr, "Unknown packet type 0x%x\n", buf[0]);
            count_p_bad += 1;
            return;
    }

    ///uint8_t decrypted[MAX_FEC_PAYLOAD];
    ///long long unsigned int decrypted_len = 0;
    wblock_hdr_t *block_hdr = (wblock_hdr_t*)buf;
    // typedef struct {
    //     uint8_t packet_type;
    //     uint64_t data_nonce;  // big endian, data_nonce = (block_idx << 8) + fragment_idx
    // }  __attribute__ ((packed)) wblock_hdr_t; 
    /*
    if (crypto_aead_chacha20poly1305_decrypt(decrypted, &decrypted_len,
                                             NULL,
                                             buf + sizeof(wblock_hdr_t), size - sizeof(wblock_hdr_t),
                                             buf,
                                             sizeof(wblock_hdr_t),
                                             (uint8_t*)(&(block_hdr->data_nonce)), session_key) != 0)
    {
        fprintf(stderr, "Unable to decrypt packet #0x%" PRIx64 "\n", be64toh(block_hdr->data_nonce));
        count_p_dec_err += 1;
        return;
    }
    */

    count_p_dec_ok += 1;///统计一次读事件中有多少包数据"无异常"
    log_rssi(sockaddr, wlan_idx, antenna, rssi);

    ///assert(decrypted_len <= MAX_FEC_PAYLOAD);

    uint64_t block_idx = be64toh(block_hdr->data_nonce) >> 8;///获取当前数据包是属于第几组
    uint8_t fragment_idx = (uint8_t)(be64toh(block_hdr->data_nonce) & 0xff);///获取当前数据包是属于第几组、第几包
    // 此二者一开始打印结果是 1005， 1；

    ///printf("[yjl-%s()-%d]--- block_idx:%llu, fragment_idx:%d\n", __FUNCTION__, __LINE__, block_idx, fragment_idx);
                                // 20098   6   7fffffffffffffff
    printf("[fegnshou-%s()-%d]--- block_idx:%llu, fragment_idx:%d  %llx\n", __FUNCTION__, __LINE__, block_idx, fragment_idx, MAX_BLOCK_IDX);

    // Should never happend due to generating new session key on tx side
    if (block_idx > MAX_BLOCK_IDX)
    {
        fprintf(stderr, "block_idx overflow\n");
        count_p_bad += 1;
        return;
    }

    if (fragment_idx >= fec_n) // >= 12
    {
        fprintf(stderr, "Invalid fragment_idx: %d\n", fragment_idx);
        count_p_bad += 1;
        return;
    }

    int ring_idx = get_block_ring_idx(block_idx);
    printf("[fengshou-%s()-%d]--- %d get_block_ring_idx: \n", __FUNCTION__, __LINE__, ring_idx);            

    //ignore already processed blocks
    if (ring_idx < 0) return;

    rx_ring_item_t *p = &rx_ring[ring_idx];

    //ignore already processed fragments
    if (p->fragment_map[fragment_idx]) return;

    memset(p->fragments[fragment_idx], '\0', MAX_FEC_PAYLOAD);
    ///memcpy(p->fragments[fragment_idx], decrypted, decrypted_len);
    memcpy(p->fragments[fragment_idx], buf + sizeof(wblock_hdr_t), size - sizeof(wblock_hdr_t));///去掉wblock_hdr_t

    p->fragment_map[fragment_idx] = 1;///表示一组12个包中，收到了序号为fragment_idx的包
    p->has_fragments += 1;

    // Check if we use current (oldest) block
    // then we can optimize and don't wait for all K fragments
    // and send packets if there are no gaps in fragments from the beginning of this block
    ///printf("[yjl-%s()-%d]--- block_idx:%llu, ring_idx:%d, rx_ring_front:%d\n", __FUNCTION__, __LINE__, block_idx, ring_idx, rx_ring_front);
    ///printf("[yjl-%s()-%d]--- p->fragment_to_send_idx:%d, p->fragment_map[p->fragment_to_send_idx]:%d\n", __FUNCTION__, __LINE__, p->fragment_to_send_idx, p->fragment_map[p->fragment_to_send_idx]);
    if(ring_idx == rx_ring_front)
    {
        printf("rx_ring_front: %d, ring_idx: %d fec_k: %d\n", ring_idx, rx_ring_front);
        printf("[fengshou-%s()-%d]--- fragment to send idx: %d, fragment_map[to send idx]: %d \n", __FUNCTION__, __LINE__, p->fragment_to_send_idx, p->fragment_map[p->fragment_to_send_idx]);            
        // check if any packets without gaps
        while(p->fragment_to_send_idx < fec_k && p->fragment_map[p->fragment_to_send_idx])
        {
            printf("[fengshou-%s()-%d]--- ############1111111111############\n", __FUNCTION__, __LINE__);
            ///printf("[yjl-%s()-%d]--- ############1111111111############\n", __FUNCTION__, __LINE__);
            send_packet(ring_idx, p->fragment_to_send_idx);
            p->fragment_to_send_idx += 1;
        }

        // remove block if full
        if(p->fragment_to_send_idx == fec_k)
        {
            printf("[fengshou-%s()-%d]--- branch of process_packet: else \n", __FUNCTION__, __LINE__);
            rx_ring_front = modN(rx_ring_front + 1, RX_RING_SIZE);
            rx_ring_alloc -= 1;
            assert(rx_ring_alloc >= 0);
            ///printf("[yjl-%s()-%d]--- remove block if full############\n", __FUNCTION__, __LINE__);
            ///printf("[yjl-%s()-%d]--- 1---rx_ring_front:%d, rx_ring_alloc:%d\n", __FUNCTION__, __LINE__, rx_ring_front, rx_ring_alloc);
            return;
        }
    }

    // 1. This is not the oldest block but with sufficient number of fragments (K) to decode
    // 2. This is the oldest block but with gaps and total number of fragments is K
    ///printf("[yjl-%s()-%d]--- p->fragment_to_send_idx:%d, p->has_fragments:%d\n", __FUNCTION__, __LINE__, p->fragment_to_send_idx, p->has_fragments);
    if(p->fragment_to_send_idx < fec_k && p->has_fragments == fec_k)
    {
        // send all queued packets in all unfinished blocks before and remove them
        int nrm = modN(ring_idx - rx_ring_front, RX_RING_SIZE);

        while(nrm > 0)
        {
            for(int f_idx = rx_ring[rx_ring_front].fragment_to_send_idx; f_idx < fec_k; f_idx++)
            {
                if(rx_ring[rx_ring_front].fragment_map[f_idx])
                {
                    printf("[yjl-%s()-%d]--- ############2222222222############\n", __FUNCTION__, __LINE__);
                    send_packet(rx_ring_front, f_idx);
                }
            }
            rx_ring_front = modN(rx_ring_front + 1, RX_RING_SIZE);
            rx_ring_alloc -= 1;
            nrm -= 1;
        }

        assert(rx_ring_alloc > 0);
        assert(ring_idx == rx_ring_front);

        // Search for missed data fragments and apply FEC only if needed
        for(int f_idx = p->fragment_to_send_idx; f_idx < fec_k; f_idx++)
        {
            if(! p->fragment_map[f_idx])
            {
                //Recover missed fragments using FEC
                ///printf("[yjl-%s()-%d]--- Recover missed fragments using FEC\n", __FUNCTION__, __LINE__);
                apply_fec(ring_idx);

                // Count total number of recovered fragments
                for(; f_idx < fec_k; f_idx++)
                {
                    if(! p->fragment_map[f_idx])
                    {
                        count_p_fec_recovered += 1;
                    }
                }
                break;
            }
        }

        while(p->fragment_to_send_idx < fec_k)
        {
            printf("[fengshou-%s()-%d]--- ************333333333************\n", __FUNCTION__, __LINE__);
            printf("[fengshou-%s()-%d]--- fragment to send idx: %d \n", __FUNCTION__, __LINE__, p->fragment_to_send_idx);            
            ///printf("[yjl-%s()-%d]--- ************333333333************\n", __FUNCTION__, __LINE__);
            send_packet(ring_idx, p->fragment_to_send_idx);
            p->fragment_to_send_idx += 1;
        }

        // remove block
        rx_ring_front = modN(rx_ring_front + 1, RX_RING_SIZE);
        rx_ring_alloc -= 1;
        assert(rx_ring_alloc >= 0);
        ///printf("[yjl-%s()-%d]--- 3---rx_ring_front:%d, rx_ring_alloc:%d\n", __FUNCTION__, __LINE__, rx_ring_front, rx_ring_alloc);
    }
}

void Aggregator::send_packet(int ring_idx, int fragment_idx)
{
    wpacket_hdr_t* packet_hdr = (wpacket_hdr_t*)(rx_ring[ring_idx].fragments[fragment_idx]);
    uint8_t *payload = (rx_ring[ring_idx].fragments[fragment_idx]) + sizeof(wpacket_hdr_t);
    uint8_t flags = packet_hdr->flags;
    uint16_t packet_size = be16toh(packet_hdr->packet_size);
    uint32_t packet_seq = rx_ring[ring_idx].block_idx * fec_k + fragment_idx;
    ///int *hlCount = (int *)payload;
    hl_wbcast_header_t *pstWbcastHead = (hl_wbcast_header_t *)payload;

    static uint32_t u32ExpSeq = 1;
    static uint32_t u32TotalPack = 0, u32TotalLost = 0;/// 总收包数，总丢包数
    static uint32_t u32PackLast = 0, u32PackPs = 0, u32LostPs = 0;/// 上一秒时刻的收包数，每秒收包数量，每秒丢包数量
    static int32_t u32CurtTime = 0, u32LastTime = 0;/// 当前时间戳，上次时间戳

    ///printf("[yjl-%s()-%d]--- ring_idx:%d, fragment_idx:%d\n", __FUNCTION__, __LINE__, ring_idx, fragment_idx);
    ///printf("[yjl-%s()-%d]--- curt seq:%d, expect seq:%d\n", __FUNCTION__, __LINE__, packet_seq, seq + 1);
    if (packet_seq > seq + 1)
    {
        count_p_lost += (packet_seq - seq - 1);
    }

    seq = packet_seq;
    printf("\n\n[fengshou-%s()-%d]--- %d %d %d branch of send_packet: if \n\n", __FUNCTION__, __LINE__, packet_size, MAX_PAYLOAD_SIZE, seq); 
    if (packet_size > MAX_PAYLOAD_SIZE) {
        fprintf(stderr, "Corrupted packet %u\n", seq);
        count_p_bad += 1;
    } else if (!(flags & WFB_PACKET_FEC_ONLY)) {
        ///printf("[yjl-%s()-%d]--- recv-packet-size:%u, recv-seq:%u\n", __FUNCTION__, __LINE__, pstWbcastHead->u32Len, pstWbcastHead->u32Seq);
        ///send(sockfd, payload, packet_size, MSG_DONTWAIT);
        
        if (pstWbcastHead->u32Seq != u32ExpSeq) {
            u32TotalLost += pstWbcastHead->u32Seq - u32ExpSeq;
            u32LostPs += pstWbcastHead->u32Seq - u32ExpSeq;
            printf("[yjl-%s()-%d]--- recv seq:%u, expect seq:%u, loss pack:%u\n", __FUNCTION__, __LINE__, 
                pstWbcastHead->u32Seq, u32ExpSeq, pstWbcastHead->u32Seq - u32ExpSeq);
        }
        u32ExpSeq = pstWbcastHead->u32Seq + 1;
        u32TotalPack = pstWbcastHead->u32Seq;

        u32CurtTime = get_time_ms();
        if (u32CurtTime - u32LastTime >= 1000) {///每秒打印一次丢包率
            u32PackPs = u32TotalPack - u32PackLast;///当前时刻收包数 - 前一秒时刻的收包数 = 一秒内的收包数量
            printf("[yjl-%s()-%d]--- u32PackPs:%u, u32LostPs:%u, LossRatePs:%u\n", __FUNCTION__, __LINE__, 
                u32PackPs, u32LostPs, u32LostPs / u32PackPs);
            printf("[yjl-%s()-%d]--- u32TotalPack:%u, u32TotalLost:%u, TotalLossRate:%u\n", __FUNCTION__, __LINE__, 
                u32TotalPack, u32TotalLost, u32TotalLost / u32TotalPack);
            u32PackPs = 0;
            u32LostPs = 0;
            u32PackLast = u32TotalPack;///更新上个时刻的收包数量
            u32LastTime = u32CurtTime;
        }
    }
}

void Aggregator::apply_fec(int ring_idx)
{
    unsigned index[fec_k];
    uint8_t *in_blocks[fec_k];
    uint8_t *out_blocks[fec_n - fec_k];
    int j = fec_k;
    int ob_idx = 0;

    for(int i=0; i < fec_k; i++)
    {
        if(rx_ring[ring_idx].fragment_map[i])
        {
            in_blocks[i] = rx_ring[ring_idx].fragments[i];
            index[i] = i;
        }else
        {
            for(;j < fec_n; j++)
            {
                if(rx_ring[ring_idx].fragment_map[j])
                {
                    in_blocks[i] = rx_ring[ring_idx].fragments[j];
                    out_blocks[ob_idx++] = rx_ring[ring_idx].fragments[i];
                    index[i] = j;
                    j++;
                    break;
                }
            }
        }
    }
    fec_decode(fec_p, (const uint8_t**)in_blocks, out_blocks, index, MAX_FEC_PAYLOAD);
}

void radio_loop(wfb_mng_rx_p wfb_mng_rx, int log_interval)
{
    int nfds = wfb_mng_rx->need_mintor_fds;/// nfds是有多少个网卡要监听
    // int nfds = min(optind, MAX_RX_INTERFACES);/// nfds是有多少个网卡要监听
    uint64_t log_send_ts = wfb_mng_rx->log_send_ts;
    struct pollfd *fds = wfb_mng_rx->fds;
    Receiver** rx = wfb_mng_rx->rx;
    // for(int i = 0; i < nfds; i++)/// 为每个网卡创建对应的接收通道
    // {
    //     rx[i] = new Receiver(argv[optind + i], i, channel_id, agg.get());/// 对pcap接口进行初始化
    //     fds[i].fd = rx[i]->getfd();/// get pcap 的 fd
    //     fds[i].events = POLLIN;
    // }

    for(;;)
    {
        uint64_t cur_ts = get_time_ms();
        int rc = poll(fds, nfds, log_send_ts > cur_ts ? log_send_ts - cur_ts : 0);

        if (rc < 0){
            if (errno == EINTR || errno == EAGAIN) continue;
            throw runtime_error(string_format("Poll error: %s", strerror(errno)));
        }

        cur_ts = get_time_ms();

        if (cur_ts >= log_send_ts)
        {
            wfb_mng_rx->agg->dump_stats(stdout);
            log_send_ts = get_time_ms() + log_interval;// 系统绝对时间 + 1000
        }

        if (rc == 0) continue; // timeout expired

        for(int i = 0; rc > 0 && i < nfds; i++)
        {
            if (fds[i].revents & (POLLERR | POLLNVAL))
            {
                throw runtime_error("socket error!");
            }
            if (fds[i].revents & POLLIN){
                rx[i]->loop_iter();
                rc -= 1;
            }
        }
    }
}

// void radio_loop(int argc, char* const *argv, int optind, uint32_t channel_id, shared_ptr<BaseAggregator> agg, int log_interval)
// {
//     int nfds = min((argc - optind), MAX_RX_INTERFACES);/// nfds是有多少个网卡要监听
//     // int nfds = min(optind, MAX_RX_INTERFACES);/// nfds是有多少个网卡要监听
//     uint64_t log_send_ts = 0;
//     struct pollfd fds[MAX_RX_INTERFACES];
//     Receiver* rx[MAX_RX_INTERFACES];
//     memset(fds, '\0', sizeof(fds));
//     printf("[yjl-%s()-%d]--- argc:%d, optind:%d, nfds:%d\n", __FUNCTION__, __LINE__, argc, optind, nfds);
//     for(int i = 0; i < nfds; i++)/// 为每个网卡创建对应的接收通道
//     {
//         rx[i] = new Receiver(argv[optind + i], i, channel_id, agg.get());/// 对pcap接口进行初始化
//         fds[i].fd = rx[i]->getfd();/// get pcap 的 fd
//         fds[i].events = POLLIN;
//     }
//     for(;;)
//     {
//         uint64_t cur_ts = get_time_ms();
//         int rc = poll(fds, nfds, log_send_ts > cur_ts ? log_send_ts - cur_ts : 0);
//         if (rc < 0){
//             if (errno == EINTR || errno == EAGAIN) continue;
//             throw runtime_error(string_format("Poll error: %s", strerror(errno)));
//         }
//         cur_ts = get_time_ms();
//         if (cur_ts >= log_send_ts)
//         {
//             agg->dump_stats(stdout);
//             log_send_ts = get_time_ms() + log_interval;
//         }
//         if (rc == 0) continue; // timeout expired
//         for(int i = 0; rc > 0 && i < nfds; i++)
//         {
//             if (fds[i].revents & (POLLERR|POLLNVAL))
//             {
//                 throw runtime_error("socket error!");
//             }
//             if (fds[i].revents & POLLIN){
//                 rx[i]->loop_iter();
//                 rc -= 1;
//             }
//         }
//     }
// }

void network_loop(int srv_port, Aggregator &agg, int log_interval)
{
    wrxfwd_t fwd_hdr;
    struct sockaddr_in sockaddr;
    uint8_t buf[MAX_FORWARDER_PACKET_SIZE];

    uint64_t log_send_ts = 0;
    struct pollfd fds[1];
    int fd = open_udp_socket_for_rx(srv_port);

    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        throw runtime_error(string_format("Unable to set socket into nonblocked mode: %s", strerror(errno)));
    }

    memset(fds, '\0', sizeof(fds));
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    for(;;)
    {
        uint64_t cur_ts = get_time_ms();
        int rc = poll(fds, 1, log_send_ts > cur_ts ? log_send_ts - cur_ts : 0);

        if (rc < 0){
            if (errno == EINTR || errno == EAGAIN) continue;
            throw runtime_error(string_format("poll error: %s", strerror(errno)));
        }

        cur_ts = get_time_ms();

        if (cur_ts >= log_send_ts)
        {
            agg.dump_stats(stdout);
            log_send_ts = get_time_ms() + log_interval;
        }

        if (rc == 0) continue; // timeout expired

        // some events detected
        if (fds[0].revents & (POLLERR | POLLNVAL))
        {
            throw runtime_error(string_format("socket error: %s", strerror(errno)));
        }

        if (fds[0].revents & POLLIN)
        {
            for(;;) // process pending rx
            {
                memset((void*)&sockaddr, '\0', sizeof(sockaddr));

                struct iovec iov[2] = {{ .iov_base = (void*)&fwd_hdr,
                                         .iov_len = sizeof(fwd_hdr)},
                                       { .iov_base = (void*)buf,
                                         .iov_len = sizeof(buf) }};

                struct msghdr msghdr = { .msg_name = (void*)&sockaddr,
                                         .msg_namelen = sizeof(sockaddr),
                                         .msg_iov = iov,
                                         .msg_iovlen = 2,
                                         .msg_control = NULL,
                                         .msg_controllen = 0,
                                         .msg_flags = 0};

                ssize_t rsize = recvmsg(fd, &msghdr, 0);
                if (rsize < 0)
                {
                    break;
                }

                if (rsize < (ssize_t)sizeof(wrxfwd_t))
                {
                    fprintf(stderr, "Short packet (rx fwd header)\n");
                    continue;
                }
                agg.process_packet(buf, rsize - sizeof(wrxfwd_t), fwd_hdr.wlan_idx, fwd_hdr.antenna, fwd_hdr.rssi, &sockaddr);
            }
            if(errno != EWOULDBLOCK) throw runtime_error(string_format("Error receiving packet: %s", strerror(errno)));
        }
    }
}



// /tmp/firmware/wfb_rx_trial -p 1 -u 5600 -K /tmp/firmware/gs.key wlan0 &
// count is 1, argc is 8, optarg is 1                                       radio_port = 1
// count is 1, argc is 8, optarg is 5600                                    client_port = 5600
// count is 1, argc is 8, optarg is /tmp/firmware/gs.key                    keypair = "/tmp/firmware/gs.key"
static int wfb_rx_getopt(wfb_mng_rx_p wfb_mng_rx, int argc, char *const *argv, const char * str)
{
    int opt, count = 1, i = 0;

    while ((opt = getopt(argc, argv, str)) != -1) {
        printf("\n\noptind is %d, argc is %d, optarg is %s argv is %s\n\n", optind, argc, optarg, *argv);
        switch (opt) {
        case 'K':
            wfb_mng_rx->keypair = optarg;
            break;
        case 'f':
            wfb_mng_rx->rx_mode = FORWARDER;
            break;
        case 'a':
            wfb_mng_rx->rx_mode = AGGREGATOR;
            wfb_mng_rx->srv_port = atoi(optarg);
            break;
        case 'k':
            wfb_mng_rx->k = atoi(optarg);
            break;
        case 'n':
            wfb_mng_rx->n = atoi(optarg);
            break;
        case 'c':
            wfb_mng_rx->client_addr = string(optarg);
            break;
        case 'u':
            wfb_mng_rx->client_port = atoi(optarg);
            break;
        case 'p':
            wfb_mng_rx->radio_port = atoi(optarg);
            break;
        case 'l':
            wfb_mng_rx->log_interval = atoi(optarg);
            break;
        case 'i':
            wfb_mng_rx->link_id = ((uint32_t)atoi(optarg)) & 0xffffff;
            break;
        case 'e':
            wfb_mng_rx->epoch = atoll(optarg);
            break;
        default: /* '?' */
        show_usage:
            fprintf(stderr, "Local receiver: %s [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-p radio_port] [-l log_interval] [-e epoch] [-i link_id] interface1 [interface2] ...\n", argv[0]);
            fprintf(stderr, "Remote (forwarder): %s -f [-c client_addr] [-u client_port] [-p radio_port] [-i link_id] interface1 [interface2] ...\n", argv[0]);
            fprintf(stderr, "Remote (aggregator): %s -a server_port [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-l log_interval] [-p radio_port] [-e epoch] [-i link_id]\n", argv[0]);
            fprintf(stderr, "Default: K='%s', k=%d, n=%d, connect=%s:%d, link_id=0x%06x, radio_port=%u, epoch=%" PRIu64 ", log_interval=%d\n", wfb_mng_rx->keypair.c_str(), wfb_mng_rx->k, wfb_mng_rx->n, wfb_mng_rx->client_addr.c_str(), wfb_mng_rx->client_port, wfb_mng_rx->link_id, wfb_mng_rx->radio_port, wfb_mng_rx->epoch, wfb_mng_rx->log_interval);
            fprintf(stderr, "WFB-ng version " WFB_VERSION "\n");
            fprintf(stderr, "WFB-ng home page: <http://wfb-ng.org>\n");
            exit(1);
        }
    }
    wfb_mng_rx->optind = optind;
    printf("%s\n", argv[optind]);
    
    return SUCCESS;
}


static int wfb_rx_mng_init(wfb_mng_rx_p wfb_mng_rx, uint8_t radio_port, int client_port, string keypair)
{
    if (wfb_mng_rx == NULL) {
        return FAILURE;
    }

    // 1.作者的getopt()的赋值结果
    wfb_mng_rx->radio_port = radio_port;
    wfb_mng_rx->client_port = client_port;
    wfb_mng_rx->keypair = keypair;

    // 2.作者测试主函数内的赋值成员
    wfb_mng_rx->k = 8;
    wfb_mng_rx->n = 12;
    // wfb_mng_rx->radio_port = 0;
    wfb_mng_rx->link_id = 0;
    wfb_mng_rx->epoch = 0;
    wfb_mng_rx->log_interval = 1000;
    // wfb_mng_rx->client_port = 5600;
    wfb_mng_rx->srv_port = 0;
    wfb_mng_rx->client_addr = HL_WFB_RX_CLIENT_ADDR;
    wfb_mng_rx->rx_mode = LOCAL;
    // wfb_mng_rx->keypair = "rx.key";
    wfb_mng_rx->optind = 0;

    return SUCCESS;
}

static int wfb_rx_random_check(const char* file_path)
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

static int wfb_rx_mode_chose(wfb_mng_rx_p wfb_mng_rx, int count_wlan, char *const *argv)
{
    if (wfb_mng_rx == NULL) {
        return FAILURE;
    }
    wfb_mng_rx->channel_id = (wfb_mng_rx->link_id << 8) + wfb_mng_rx->radio_port;

    if (wfb_mng_rx->rx_mode == LOCAL || wfb_mng_rx->rx_mode == FORWARDER)
    {
        // if (wfb_mng_rx->optind >= count_wlan) {
        //     goto show_usage;
        // }

        // shared_ptr<BaseAggregator> temp_agg;
        if (wfb_mng_rx->rx_mode == LOCAL) {
            wfb_mng_rx->agg = shared_ptr<Aggregator>(new Aggregator(wfb_mng_rx->client_addr, wfb_mng_rx->client_port, wfb_mng_rx->k, wfb_mng_rx->n, wfb_mng_rx->keypair, wfb_mng_rx->epoch, wfb_mng_rx->channel_id));
        } else {
            wfb_mng_rx->agg = shared_ptr<Forwarder>(new Forwarder(wfb_mng_rx->client_addr, wfb_mng_rx->client_port));
        }

        printf("[yjl-%s()-%d]--- start radio loop...\n", __FUNCTION__, __LINE__);
        // radio_loop(count_wlan, argv, wfb_mng_rx->optind, wfb_mng_rx->channel_id, wfb_mng_rx->agg, wfb_mng_rx->log_interval);


    } else if (wfb_mng_rx->rx_mode == AGGREGATOR) {
        // shared_ptr<BaseAggregator> temp_agg;
        // if (wfb_mng_rx->optind > count_wlan) {
        //     goto show_usage;
        // }
        Aggregator temp_agg(wfb_mng_rx->client_addr, wfb_mng_rx->client_port, wfb_mng_rx->k, wfb_mng_rx->n, wfb_mng_rx->keypair, wfb_mng_rx->epoch, wfb_mng_rx->channel_id);
        // wfb_mng_rx->agg = shared_ptr<Aggregator> (new Aggregator(wfb_mng_rx->client_addr, wfb_mng_rx->client_port, wfb_mng_rx->k, wfb_mng_rx->n, wfb_mng_rx->keypair, wfb_mng_rx->epoch, wfb_mng_rx->channel_id));

        network_loop(wfb_mng_rx->srv_port, temp_agg, wfb_mng_rx->log_interval);
    } else {
        throw runtime_error(string_format("Unknown rx_mode=%d", wfb_mng_rx->rx_mode));
    }
    return SUCCESS;
show_usage:
{
    fprintf(stderr, "Local receiver: %s [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-p radio_port] [-l log_interval] [-e epoch] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    fprintf(stderr, "Remote (forwarder): %s -f [-c client_addr] [-u client_port] [-p radio_port] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    fprintf(stderr, "Remote (aggregator): %s -a server_port [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-l log_interval] [-p radio_port] [-e epoch] [-i link_id]\n", argv[0]);
    fprintf(stderr, "Default: K='%s', k=%d, n=%d, connect=%s:%d, link_id=0x%06x, radio_port=%u, epoch=%" PRIu64 ", log_interval=%d\n", wfb_mng_rx->keypair.c_str(), wfb_mng_rx->k, wfb_mng_rx->n, wfb_mng_rx->client_addr.c_str(), wfb_mng_rx->client_port, wfb_mng_rx->link_id, wfb_mng_rx->radio_port, wfb_mng_rx->epoch, wfb_mng_rx->log_interval);
    fprintf(stderr, "WFB-ng version " WFB_VERSION "\n");
    fprintf(stderr, "WFB-ng home page: <http://wfb-ng.org>\n");
    exit(1);
}
    
}

static int wfb_rx_recive_init(wfb_mng_rx_p wfb_mng_rx, int count_waln, char *const wlan_set[])
{ 
    if (wfb_mng_rx == NULL) {
        return FAILURE;
    }

    struct pollfd *fds = wfb_mng_rx->fds;
    Receiver** rx = wfb_mng_rx->rx;

    wfb_mng_rx->need_mintor_fds = count_waln;/// nfds是有多少个网卡要监听
    wfb_mng_rx->log_send_ts = 0;

    memset(fds, '\0', sizeof(wfb_mng_rx->fds));

    for(int i = 0; i < wfb_mng_rx->need_mintor_fds; i++)/// 为每个网卡创建对应的接收通道
    {
        rx[i]           = new Receiver(wlan_set[i], i, wfb_mng_rx->channel_id, wfb_mng_rx->agg.get());/// 对pcap接口进行初始化
        fds[i].fd       = rx[i]->getfd();/// get pcap 的 fd
        fds[i].events   = POLLIN;
    }

    return SUCCESS;
}



int wfb_rx_init(wfb_mng_rx_p wfb_mng_rx, int count_wlan, char *const wlan_set[], void (*wfb_recive_success_handle_func)(const uint8_t* data_buffer, int* data_len))
{   
    int ret = -1;

    // if ( !wfb_rx_getopt(wfb_mng_rx, argc, argv, HL_WFB_RX_GETOPT) ) {
    //     fprintf(stderr, "wfb rx getopt failed!!!\n");
    // }
    if ( wfb_rx_mng_init(wfb_mng_rx, 1, 5600, "/tmp/firmware/gs.key") != 0) {
        fprintf(stderr, "wfb rx mng_init failed!!!\n");
    }

    if ( wfb_rx_random_check(HL_WFB_RX_RANDOM_FLIE) != 0) {
        fprintf(stderr, "wfb rx random failed!!!\n");
    }

    if ( sodium_init() < 0) {
        fprintf(stderr, "wfb rx sodium failed!!!\n");
    }
    
    if ( wfb_rx_mode_chose(wfb_mng_rx, count_wlan, wlan_set) != 0) {
        fprintf(stderr, "wfb rx mode chose failed!!!\n");
    }

    if ( wfb_rx_recive_init(wfb_mng_rx, count_wlan, wlan_set) != 0) {
        fprintf(stderr, "wfb rx recive init failed!!!\n");
    }

    wfb_mng_ptr = wfb_mng_rx;
    wfb_mng_rx->wfb_recive_success_handle_func = wfb_recive_success_handle_func;

    return SUCCESS;
}

int wfb_rx_deinit(wfb_mng_rx_p wfb_mng_rx)
{
    return SUCCESS;
}

int wfb_rx_recive(wfb_mng_rx_p wfb_mng_rx, const uint8_t* data_buffer, int* data_len)
{
    int count = 0;
    int nfds = wfb_mng_rx->need_mintor_fds;/// nfds是有多少个网卡要监听
    struct pollfd *fds = wfb_mng_rx->fds;
    Receiver** rx = wfb_mng_rx->rx;
    static uint64_t log_send_ts = wfb_mng_rx->log_send_ts;
    static uint64_t cur_ts;
    static int response_nums;
    // for(int i = 0; i < nfds; i++)/// 为每个网卡创建对应的接收通道
    // {
    //     rx[i] = new Receiver(argv[optind + i], i, channel_id, agg.get());/// 对pcap接口进行初始化
    //     fds[i].fd = rx[i]->getfd();/// get pcap 的 fd <<<<<<<<---------
    //     fds[i].events = POLLIN;
    // }

    cur_ts = get_time_ms();
    response_nums = poll(fds, nfds, -1);

    if (response_nums < 0) {
        if (errno == EINTR || errno == EAGAIN) {
            
        } else {
            throw runtime_error(string_format("Poll error: %s", strerror(errno)));
        }
    }

    wfb_mng_rx->agg->dump_stats(stdout);

    if (response_nums == 0) {
        // timeout expired
    } 

    for(int i = 0, count = response_nums; response_nums > 0 && i < nfds; i++) {
        if (fds[i].revents & (POLLERR | POLLNVAL)) {
            throw runtime_error("socket error!");
        }
        if (fds[i].revents & POLLIN) {  // 第 i 个网卡 存在读事件
            response_nums -= 1;
            rx[i]->loop_iter();
            // printf("handle about pcap recive data...\n\n");
            // usleep(100000);
            // printf("handle about pcap recive data...\n\n");
            // usleep(100000);
            // printf("handle about pcap recive data...\n\n");
            return SUCCESS;
        }
    }
    if (count > 0) {
        data_buffer = wfb_mng_rx->pcap_data_buffer;
        data_buffer = *wfb_mng_rx->data_len;
        return SUCCESS;
    } else {
        data_buffer = NULL;
        data_buffer = NULL;
        return FAILURE;
    }
}

void wfb_recive_success_handle_func(const uint8_t* data_buffer, int* data_len)
{
    int ret = 0;
    if (NULL == data_buffer) {
        printf("wfb mng rx is NULL callback!!!\n");
        return ;
    }
    printf("recive data is :");
    for (int i = 0; i < *data_len; i++)
    {
        printf("%x", data_buffer[i]);
    }
    printf("\n");
}



int main(int argc, char* const *argv)
{
    int count = 0;
    wfb_mng_rx_t wfb_mng_rx;
    wfb_mng_rx_p wfb_mng_rx_ptr =  &wfb_mng_rx;
    int count_wlan = 1;
    char *const wlan_set[] = {"wlan0", "wlan1"};

    wfb_rx_init(wfb_mng_rx_ptr, count_wlan, wlan_set, wfb_recive_success_handle_func);

    while (count++ < 10) {
        if ( !wfb_rx_recive(wfb_mng_rx_ptr)) {
            // 成功接收到数据

        }
    }

    wfb_rx_deinit(wfb_mng_rx_ptr);

    return 0;



    // wfb_mng_rx_ptr->k = 8;
    // wfb_mng_rx_ptr->n = 12;
    // wfb_mng_rx_ptr->radio_port = 0;
    // wfb_mng_rx_ptr->link_id = 0;
    // wfb_mng_rx_ptr->epoch = 0;
    // wfb_mng_rx_ptr->log_interval = 1000;
    // wfb_mng_rx_ptr->client_port = 5600;
    // wfb_mng_rx_ptr->srv_port = 0;
    // wfb_mng_rx_ptr->client_addr = HL_WFB_RX_CLIENT_ADDR;
    // wfb_mng_rx_ptr->rx_mode = LOCAL;
    // wfb_mng_rx_ptr->keypair = HL_WFB_RX_KEYPAIR;

    


    // int opt;
    // uint8_t k = 8, n = 12, radio_port = 0;
    // uint32_t link_id = 0;
    // uint64_t epoch = 0;
    // int log_interval = 1000;
    // int client_port = 5600;
    // int srv_port = 0;
    // string client_addr = "127.0.0.1";
    // rx_mode_t rx_mode = LOCAL;
    // string keypair = "rx.key";


// ### wifibroadcast接收 /tmp/firmware/wfb_rx_trial -p 1 -u 5600 -K /tmp/firmware/gs.key wlan0 &
    // while ((opt = getopt(argc, argv, "K:fa:k:n:c:u:p:l:i:e:")) != -1) {
    //     switch (opt) {
    //     case 'K':
    //         keypair = optarg;
    //         break;
    //     case 'f':
    //         rx_mode = FORWARDER;
    //         break;
    //     case 'a':
    //         rx_mode = AGGREGATOR;
    //         srv_port = atoi(optarg);
    //         break;
    //     case 'k':
    //         k = atoi(optarg);
    //         break;
    //     case 'n':
    //         n = atoi(optarg);
    //         break;
    //     case 'c':
    //         client_addr = string(optarg);
    //         break;
    //     case 'u':
    //         client_port = atoi(optarg);
    //         break;
    //     case 'p':
    //         radio_port = atoi(optarg);
    //         break;
    //     case 'l':
    //         log_interval = atoi(optarg);
    //         break;
    //     case 'i':
    //         link_id = ((uint32_t)atoi(optarg)) & 0xffffff;
    //         break;
    //     case 'e':
    //         epoch = atoll(optarg);
    //         break;
    //     default: /* '?' */
    //     show_usage:
    //         fprintf(stderr, "Local receiver: %s [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-p radio_port] [-l log_interval] [-e epoch] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    //         fprintf(stderr, "Remote (forwarder): %s -f [-c client_addr] [-u client_port] [-p radio_port] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    //         fprintf(stderr, "Remote (aggregator): %s -a server_port [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-l log_interval] [-p radio_port] [-e epoch] [-i link_id]\n", argv[0]);
    //         fprintf(stderr, "Default: K='%s', k=%d, n=%d, connect=%s:%d, link_id=0x%06x, radio_port=%u, epoch=%" PRIu64 ", log_interval=%d\n", keypair.c_str(), k, n, client_addr.c_str(), client_port, link_id, radio_port, epoch, log_interval);
    //         fprintf(stderr, "WFB-ng version " WFB_VERSION "\n");
    //         fprintf(stderr, "WFB-ng home page: <http://wfb-ng.org>\n");
    //         exit(1);
    //     }
    // }
    // while ((opt = getopt(argc, argv, "K:fa:k:n:c:u:p:l:i:e:")) != -1) {
    //     switch (opt) {
    //     case 'K':
    //         wfb_mng_rx->keypair = optarg;
    //         break;
    //     case 'f':
    //         wfb_mng_rx->rx_mode = FORWARDER;
    //         break;
    //     case 'a':
    //         wfb_mng_rx->rx_mode = AGGREGATOR;
    //         wfb_mng_rx->srv_port = atoi(optarg);
    //         break;
    //     case 'k':
    //         wfb_mng_rx->k = atoi(optarg);
    //         break;
    //     case 'n':
    //         wfb_mng_rx->n = atoi(optarg);
    //         break;
    //     case 'c':
    //         wfb_mng_rx->client_addr = string(optarg);
    //         break;
    //     case 'u':
    //         wfb_mng_rx->client_port = atoi(optarg);
    //         break;
    //     case 'p':
    //         wfb_mng_rx->radio_port = atoi(optarg);
    //         break;
    //     case 'l':
    //         wfb_mng_rx->log_interval = atoi(optarg);
    //         break;
    //     case 'i':
    //         wfb_mng_rx->link_id = ((uint32_t)atoi(optarg)) & 0xffffff;
    //         break;
    //     case 'e':
    //         wfb_mng_rx->epoch = atoll(optarg);
    //         break;
    //     default: /* '?' */
    //     show_usage:
    //         fprintf(stderr, "Local receiver: %s [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-p radio_port] [-l log_interval] [-e epoch] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    //         fprintf(stderr, "Remote (forwarder): %s -f [-c client_addr] [-u client_port] [-p radio_port] [-i link_id] interface1 [interface2] ...\n", argv[0]);
    //         fprintf(stderr, "Remote (aggregator): %s -a server_port [-K rx_key] [-k RS_K] [-n RS_N] [-c client_addr] [-u client_port] [-l log_interval] [-p radio_port] [-e epoch] [-i link_id]\n", argv[0]);
    //         fprintf(stderr, "Default: K='%s', k=%d, n=%d, connect=%s:%d, link_id=0x%06x, radio_port=%u, epoch=%" PRIu64 ", log_interval=%d\n", keypair.c_str(), k, n, client_addr.c_str(), client_port, link_id, radio_port, epoch, log_interval);
    //         fprintf(stderr, "WFB-ng version " WFB_VERSION "\n");
    //         fprintf(stderr, "WFB-ng home page: <http://wfb-ng.org>\n");
    //         exit(1);
    //     }
    // }

    // wfb_rx_getopt(wfb_mng_rx, argc, argv);
    // wfb_rx_random_check();
    // if ( sodium_init() < 0) {
    //     fprintf(stderr, "wfb rx sodium failed!!!\n");
    // }
    // wfb_rx_mode_chose(wfb_mng_rx);

    // {
    //     int fd;
    //     int c;
    // 
    //     if ((fd = open("/dev/random", O_RDONLY)) != -1) {
    //         if (ioctl(fd, RNDGETENTCNT, &c) == 0 && c < 160) {
    //             fprintf(stderr, "This system doesn't provide enough entropy to quickly generate high-quality random numbers.\n"
    //                     "Installing the rng-utils/rng-tools, jitterentropy or haveged packages may help.\n"
    //                     "On virtualized Linux environments, also consider using virtio-rng.\n"
    //                     "The service will not start until enough entropy has been collected.\n");
    //         }
    //         (void) close(fd);
    //     }
    // }

    // if (sodium_init() < 0)
    // {
    //     fprintf(stderr, "Libsodium init failed\n");
    //     return 1;
    // }

    // try
    // {
    //     uint32_t channel_id = (link_id << 8) + radio_port;
    //     if (rx_mode == LOCAL || rx_mode == FORWARDER)
    //     {
    //         if (optind >= argc) goto show_usage;
    //         shared_ptr<BaseAggregator> agg;
    //         if (rx_mode == LOCAL) {
    //             agg = shared_ptr<Aggregator>(new Aggregator(client_addr, client_port, k, n, keypair, epoch, channel_id));
    //         } else {
    //             agg = shared_ptr<Forwarder>(new Forwarder(client_addr, client_port));
    //         }
    //         printf("[yjl-%s()-%d]--- start radio loop...\n", __FUNCTION__, __LINE__);
    //         radio_loop(argc, argv, optind, channel_id, agg, log_interval);
    //     }else if(rx_mode == AGGREGATOR)
    //     {
    //         if (optind > argc) goto show_usage;
    //         Aggregator agg(client_addr, client_port, k, n, keypair, epoch, channel_id);
    //         network_loop(srv_port, agg, log_interval);
    //     }else{
    //         throw runtime_error(string_format("Unknown rx_mode=%d", rx_mode));
    //     }
    // }catch(runtime_error &e)
    // {
    //     fprintf(stderr, "Error: %s\n", e.what());
    //     exit(1);
    // }
    
    
}


int wfb_rx_recive_trial(wfb_mng_rx_p wfb_mng_rx)
{
    int nfds = wfb_mng_rx->need_mintor_fds;/// nfds是有多少个网卡要监听
    struct pollfd *fds = wfb_mng_rx->fds;
    Receiver** rx = wfb_mng_rx->rx;
    static uint64_t log_send_ts = wfb_mng_rx->log_send_ts;
    static uint64_t cur_ts;
    static int response_nums;
    // for(int i = 0; i < nfds; i++)/// 为每个网卡创建对应的接收通道
    // {
    //     rx[i] = new Receiver(argv[optind + i], i, channel_id, agg.get());/// 对pcap接口进行初始化
    //     fds[i].fd = rx[i]->getfd();/// get pcap 的 fd <<<<<<<<---------
    //     fds[i].events = POLLIN;
    // }

    cur_ts = get_time_ms();
    response_nums = poll(fds, nfds, log_send_ts > cur_ts ? log_send_ts - cur_ts : 0);

    if (response_nums < 0) {
        if (errno == EINTR || errno == EAGAIN) {
            
        } else {
            throw runtime_error(string_format("Poll error: %s", strerror(errno)));
        }
    }

    cur_ts = get_time_ms();
    if (cur_ts >= log_send_ts) {
        wfb_mng_rx->agg->dump_stats(stdout);
        log_send_ts = get_time_ms() + wfb_mng_rx->log_interval;// 系统绝对时间 + 1000
    }
    if (response_nums == 0) {
         // timeout expired
    } 

    for(int i = 0; response_nums > 0 && i < nfds; i++) {
        if (fds[i].revents & (POLLERR | POLLNVAL)) {
            throw runtime_error("socket error!");
        }
        if (fds[i].revents & POLLIN) {
            response_nums -= 1;
            rx[i]->loop_iter();
            return SUCCESS;
        }
    }
    return FAILURE;
}
