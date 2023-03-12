#include <stdio.h>  //printf
#include <stdlib.h> //exit
#include <sys/types.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  //htons	inet_addr
#include <unistd.h>     //close
#include <string.h>
#include "fifo/ring_buffer_fifo.h"
#include <pthread.h>


struct sock_udp {
    int sock_fd;
    struct sockaddr_in local_addr;
    struct sockaddr_in server_addr;
};

static struct sock_udp sock_visual_to_mcu, sock_visual_to_switcher;
struct sockaddr_in serveraddr;
// buffer_fifo_t read_fifo, write_fifo;

static int sock_xxx_to_xxx_init(struct sock_udp *sock_fd, char* local_ip, int local_port, char* server_ip, int server_port)
{
    uint8_t *p_buff = (uint8_t*)malloc(1024);

    if ((sock_fd->sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("fail to socket");
        exit(1);
    }
    printf("sockfd = %d\nlocal_ip: %s, local_port: %d\nserver_ip: %s, server_port: %d\n", sock_fd->sock_fd, local_ip, local_port, server_ip, server_port);

    // 填充 本地IP和端口                        （虚拟机）
    sock_fd->local_addr.sin_family = AF_INET;
    sock_fd->local_addr.sin_addr.s_addr = inet_addr(local_ip);
    sock_fd->local_addr.sin_port = htons(local_port);
    bind(sock_fd->sock_fd, (struct sockaddr*)&sock_fd->local_addr, sizeof(sock_fd->local_addr));

    // 第二步：填充 服务器网络信息结构体	     （单片机）         sockaddr_in（一般不需要，系统会自动分配）
    // memset(&(sock_fd->server_addr), 0x0, sizeof(struct sockaddr_in));
    sock_fd->server_addr.sin_family = AF_INET;                            // 协议族	AF_INET:ipv4网络协议
    sock_fd->server_addr.sin_addr.s_addr = inet_addr(server_ip);          // ip地址
    sock_fd->server_addr.sin_port = htons(server_port);
    // socklen_t addrlen = sizeof(serveraddr);

    return 0;
}

#define  VISUAL_LOCAL_IP_ADDR       "192.168.60.79"
#define  VISUAL_LOCAL_PROT          59168
#define  MCU_IP_ADDR                "192.168.60.240"
#define  MCU_PROT                   59168
#define  SWITCHER_IP_ADDR           "192.168.60.150"
#define  SWITCHER_PROT              9910


static void visual_to_mcu_thread(void *argument)
{
    struct sock_udp * sock_p = (struct sock_udp*)argument; // sock_visual_to_mcu
    uint8_t *p_buff = (uint8_t*)malloc(1024);
    socklen_t addrlen_l = sizeof(sock_p->local_addr);
    socklen_t addrlen_s = sizeof(sock_p->server_addr);

    while (1)
    {
        memset(p_buff, 0x0, 1024);
        printf("visual_to_mcu_thread blocking...\n");
        int count = recvfrom(sock_p->sock_fd, p_buff, 1024, 
            0, (struct sockaddr*)&sock_p->server_addr, &addrlen_s);  //recvfrom是拥塞函数，没有数据就一直拥塞

        printf("v_to_m recv:");
        for (int i = 0; i < count; i++) {
            printf("%x ", p_buff[i]);
        }
        printf("\n");
        printf("v_to_m send, count %d\n", count);
        sendto(sock_p->sock_fd, p_buff, count, 0, (struct sockaddr *)&sock_p->server_addr, addrlen_s);
        // if (sendto(sockfd_switcher, p_buff, count, 0, (struct sockaddr *)&serveraddr, addrlen));
        // {
        //     perror("fail to sendto");
        //     exit(1);
        // }
    }
    // 第四步：关闭套接字文件描述符
    // close(sock_visual_to_mcu);
    free(p_buff);   
    return ;
}

static void visual_to_switcher_thread(void *argument)
{
    struct sock_udp * sock_p = (struct sock_udp*)argument;
    uint8_t *p_buff = (uint8_t*)malloc(1024);
    int sock_fd = sock_p->sock_fd;
    socklen_t addrlen_l = sizeof(sock_p->local_addr);
    socklen_t addrlen_s = sizeof(sock_p->server_addr);

    while (1)
    {
        memset(p_buff, 0x0, 1024);
        printf("visual_to_switcher_thread blocking...\n");
        int count = recvfrom(sock_fd, p_buff, 1024, 
            0, (struct sockaddr*)&sock_p->server_addr, &addrlen_s);  //recvfrom是拥塞函数，没有数据就一直拥塞

        printf("v_to_switcher recv:");
        for (int i = 0; i < count; i++) {
            printf("%x ", p_buff[i]);
        }
        printf("\n");
        printf("v_to_switcher send, count %d\n", count);
        sendto(sock_fd, p_buff, count, 0, (struct sockaddr *)&sock_p->server_addr, addrlen_s);
        // if (sendto(sockfd_switcher, p_buff, count, 0, (struct sockaddr *)&serveraddr, addrlen));
        // {
        //     perror("fail to sendto");
        //     exit(1);
        // }
    }
    // 第四步：关闭套接字文件描述符
    // close(sock_visual_to_mcu); 
    free(p_buff);   
    return ;
}

int main()
{
    pthread_t th1, th2;

    sock_xxx_to_xxx_init(&sock_visual_to_mcu, VISUAL_LOCAL_IP_ADDR, VISUAL_LOCAL_PROT, MCU_IP_ADDR, MCU_PROT);
    sock_xxx_to_xxx_init(&sock_visual_to_switcher, VISUAL_LOCAL_IP_ADDR, VISUAL_LOCAL_PROT, SWITCHER_IP_ADDR, SWITCHER_PROT);

    pthread_create(&th1, NULL, (void*)visual_to_mcu_thread, (void*)&sock_visual_to_mcu);
    pthread_create(&th2, NULL, (void*)visual_to_switcher_thread, (void*)&sock_visual_to_switcher);

    pthread_detach(th1);
    pthread_detach(th2);

    while(1);

    return 0;
}
