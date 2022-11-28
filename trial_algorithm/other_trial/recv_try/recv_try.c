#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <signal.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8887

int client_flag = 0;

void show_inet_info(struct sockaddr_in* addr, char* source)
{
    char addr_ip[16];
    unsigned short addr_port;

    inet_ntop(AF_INET, &addr->sin_addr.s_addr, addr_ip, sizeof(addr_ip));
    addr_port = ntohs(addr->sin_port);

    printf("%s  addr IP is %s, port is %d\n", source, addr_ip, addr_port);
    return;
}

static int client_alive(int clients[])
{
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += clients[i];
    }
    if (sum <= 0) {
        client_flag = 0;
        return -1;
    }
    
    return 0;
}

void* handle_clients(void *argc)
{
    int index = 0;
    char buffer[128];
    char message[] = "welcome";
    int *clients_fd = (int*)argc;

    // 接受客户端数据
    while (client_flag)
    {
        if (clients_fd[index] == -1) {
            index = (index + 1) % 9;
            continue;
        } else {
            memset(buffer, 0x0, sizeof(buffer));
            int ret = recv(clients_fd[index], buffer, sizeof(buffer), MSG_DONTWAIT);      // 非阻塞地接受客户端数据
            if (ret == -1) { 
                if (errno == EWOULDBLOCK || errno == ENOTSOCK) {
                    // The file descriptor sockfd does not refer to a socket.
                } else {
                    perror("recv");
                }

            } else if (ret == 0) {
                clients_fd[index] = -1;
                printf("client offline, scoket is %d, position is %d\n", clients_fd[index], index);
                client_alive(clients_fd);

            } else {
                sleep(1);
                printf("client %d, recive data is %s\t", clients_fd[index], buffer);
                ret = send(clients_fd[index], message, sizeof(message), 0);
                if (ret == -1) {
                    perror("server send");
                } else {
                    printf("send success\n");
                }
            }
        }
        index = (index + 1) % 9;
    }
    printf("\ncommunicate pthread deinit!!!\n");
}

int communicate_start_pthread(int clients_fd[], pthread_t ser_tid)
{
    client_flag = 1;
    int ret = pthread_create(&ser_tid, NULL, &handle_clients, clients_fd);
    pthread_detach(ser_tid);
    if (ret == -1) {
        perror("pthread_create");
        return -1;
    } else {
        printf("communicate_pthread create success!!!\n");
        return 0;
    }
}   


int main()
{
    int l_fd = -1, ret = -1, pos = 0;
    int clients_fd[10] = {-1};
    pthread_t comm_tid = -1;

    // 创建网络监听的socket
    l_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("listen socket is %d\n", l_fd);

    // 绑定IP和端口号
    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0x0, sizeof(struct sockaddr_in));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htons(INADDR_ANY);
    // inet_pton(AF_INET, "192.168.41.62", &ser_addr.sin_addr.s_addr);
    ser_addr.sin_port = htons(PORT);

    bind(l_fd, (struct sockaddr*)(&ser_addr), sizeof(struct sockaddr_in));// 绑定的sizeof(ser_addr.sin_addr)？？？
    show_inet_info(&ser_addr, "server");

    //  设置网络监听socket属性
    ret = listen(l_fd, 12);
    if (ret < 0) {
        printf("thread start failure\n");
    }

    fd_set temp_fds, readfds;
    struct sockaddr_in clients_addr;
    int len = sizeof(clients_addr);
    FD_ZERO(&readfds);
    FD_SET(l_fd, &readfds);

    int max_fd = l_fd, c_fd = -1;

    // 循环监听事件发生
    while (1) {
        temp_fds = readfds;
        printf("select blocking......\n");
        ret = select(max_fd + 1, &temp_fds, NULL, NULL, NULL);
        printf("select ret is %d\n", ret);
        if (ret == -1) {
            perror("select");
        } else {
            if (FD_ISSET(l_fd, &temp_fds)) {
                printf("ret is %d", ret);
                c_fd = accept(l_fd, (struct sockaddr*)&clients_addr, &len);
                if (c_fd == -1) {
                    perror("accept");
                } else {
                    communicate_start_pthread(clients_fd, comm_tid);
                    show_inet_info(&clients_addr, "client entry");
                    FD_SET(c_fd, &readfds);
                    max_fd = max_fd < c_fd ? c_fd : max_fd;
                    clients_fd[pos++] = max_fd;
                    pos = pos % 9;
                }
            }
            
        }
    }

    return 0;
}

// gcc -o recv_try recv_try.c -pthread