#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <pthread.h>


void show_inet_info(struct sockaddr_in* addr, char* source)
{
    char addr_ip[16];
    unsigned short addr_port;

    inet_ntop(AF_INET, &addr->sin_addr.s_addr, addr_ip, sizeof(addr_ip));
    addr_port = ntohs(addr->sin_port);

    printf("%s  addr IP is %s, port is %d\n", source, addr_ip, addr_port);
    return;
}

int main()
{
    int comm_fd = -1, ret = -1;
    comm_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (comm_fd == -1) {
        perror("socket");
    } else {
        printf("client socket is %d\n", comm_fd);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8887);
    inet_pton(AF_INET, "192.168.41.62", &server_addr.sin_addr.s_addr);
    // show_inet_info(&server_addr, "connect server");

    // struct sockaddr_in client_addr;
    ret = connect(comm_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("connect");
        exit(-1);
    } else {
        show_inet_info(&server_addr, "client");
    }

// 30      07      20      01
// 00      00      12      34
// 56      78      ab      cd
// 00      00      00      00
// 04      31      39      32
// 2e      31      36      38
// 2e      34      31      2e
// 36      32      00      00
// 00
    uint8_t message[33];
    message[0] = 0x30;
    message[1] = 0x7;
    message[2] = 0x20;
    message[3] = 0x1;
    message[4] = 0x0;
    message[5] = 0x0;
    message[6] = 0x12;
    message[7] = 0x34;   
    message[8] = 0x56;
    message[9] = 0x78;
    message[10] = 0xab;
    message[11] = 0xcd;
    message[12] = 0x0;
    message[13] = 0x0;
    message[14] = 0x0;
    message[15] = 0x0;
    message[16] = 0x4;
    message[17] = 0x31;
    message[18] = 0x39;
    message[19] = 0x32;
    message[20] = 0x2e;
    message[21] = 0x31;
    message[22] = 0x36;
    message[23] = 0x38;
    message[24] = 0x2e;
    message[25] = 0x34;
    message[26] = 0x31;
    message[27] = 0x2e;
    message[28] = 0x36;
    message[29] = 0x32;
    message[30] = 0x00;
    message[31] = 0x00;
    message[32] = 0x00;


    char buffer[128];
    while (1) {
        memset(buffer, 0x0, sizeof(buffer));
        send(comm_fd, message, sizeof(message), 0);
        recv(comm_fd, buffer, sizeof(buffer), 0);
        printf("server message is %s\n\n", buffer);
        sleep(1);
    }

}

// gcc -o client_try client_try.c -pthread