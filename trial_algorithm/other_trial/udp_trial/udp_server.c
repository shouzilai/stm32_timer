/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-09     Administrator       the first version
 */
/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : lzh
* Version            : V1.0.0
* Date               : 2021/09/09
* Description        : udp program body.
*******************************************************************************/
// #include "ch32v30x.h"
// #include <rtthread.h>
// #include <rthw.h>
// #include "drivers/pin.h"
// #include <board.h>

// #include <rtdevice.h>
#include <sys/socket.h>
#include "netdb.h"
// #include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
/* Global typedef */

/* Global define */
#define UDP_LOCAL_IP_ADDRESS       "192.168.60.213"
#define UDP_SERVER_PORT            8080


#define UDP_THREAD_PRIORITY        25
#define UDP_THREAD_STACK_SIZE      2048
#define UDP_THREAD_TIMESLICE       5
#define UDP_BUFF_LEN               1024

/* Global Variable */
extern int sock_visual_to_mcu;
extern struct sockaddr_in serveraddr;

static rt_thread_t rcv_thread_fd = RT_NULL;
static int socket_fd = 0;

/* Local Function */
// 接收处理
static void udp_rcv_thread(void *parameter)
{
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
    char *p_buff = RT_NULL;

    rt_kprintf("%s start\n",__FUNCTION__);
    p_buff = rt_malloc(UDP_BUFF_LEN);
    while(1) {
        memset(p_buff, 0, UDP_BUFF_LEN);
        len = sizeof(clent_addr);
        count = recvfrom(socket_fd, p_buff, UDP_BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count == -1) {
            rt_kprintf("recieve data fail!\n");
            break;
        }
        p_buff[count] = '\0';
        rt_kprintf("udp rcv len:%d :%s\n",count, p_buff);  //打印client发过来的信息
        // sendto(socket_fd, "udp server send data test!!!", strlen("udp server send data test!!!"), 0, (struct sockaddr*)&clent_addr, sizeof(clent_addr));
        sendto(sock_visual_to_mcu, p_buff, count, 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    }

    closesocket(socket_fd);
    rt_kprintf("%s end\n",__FUNCTION__);
}


/* Global Function */
// 初始化
int udp_server_init(void)
{
    int ret;

    rt_kprintf("\n %s start \n",__FUNCTION__);

    // 1、 创建一个socket，协议簇为AT Socket 协议栈，类型是SOCK_DGRAM，UDP类型
    socket_fd = socket(AF_INET,SOCK_DGRAM,0);
    if (socket_fd  == -1)
    {
        rt_kprintf("Socket error\n");
        return -1;
    }

    // 2、绑定本地的相关信息，如果不绑定，则系统会随机分配一个端口号
    struct sockaddr_in local_addr = {0};
    local_addr.sin_family = AF_INET;                                //使用IPv4地址
    local_addr.sin_addr.s_addr = inet_addr(UDP_LOCAL_IP_ADDRESS);         //本机IP地址
    local_addr.sin_port = htons(UDP_SERVER_PORT);                              //端口
    ret = bind(socket_fd, (struct sockaddr*)&local_addr, sizeof(local_addr));//将套接字和IP、端口绑定
    if(ret < 0) {
        rt_kprintf("socket bind fail!\n");
        return -2;
    }

    /* 创建线程1，名称是thread1，线程入口函数是thread1_entry */
    rcv_thread_fd = rt_thread_create("udp_rcv_thread",
                                   udp_rcv_thread,
                                   RT_NULL,
                                   UDP_THREAD_STACK_SIZE,
                                   UDP_THREAD_PRIORITY,
                                   UDP_THREAD_TIMESLICE);

    if(rcv_thread_fd != RT_NULL) {
        rt_thread_startup(rcv_thread_fd);
    } else {
        rt_kprintf("error: udp_rcv_thread == RT_NULL \n");
    }

    rt_kprintf("%s end \n",__FUNCTION__);
}
