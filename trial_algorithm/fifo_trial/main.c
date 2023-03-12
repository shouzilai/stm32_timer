#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "fifo/ring_buffer_fifo.h"

buffer_fifo_t read_fifo = {0};
void *function_1(void *argument)
{
    uint8_t p_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

    printf("fun 1 running...\n");
    while (1)
    {
        if (&read_fifo != NULL)
        {
            buffer_fifo_write(&read_fifo, p_data, sizeof(p_data) / sizeof(uint8_t));
        }
        usleep(2);
    }
}

void *function_2(void *argument)
{
    uint8_t p_buff[128] = {0};
    int count = 0, ret = 0;

    printf("fun 2 running...\n");
    // while (1) {
    //     memset(p_buff, 0x0, sizeof(p_buff));
    //     if (buffer_fifo_read(&read_fifo, p_buff, 1) != -1) {
    //         printf("%x ", p_buff[0]);
    //     }
    //     usleep(12);
    // }
    while (1)
    {
        memset(p_buff, 0x0, sizeof(p_buff));
        if (buffer_fifo_read(&read_fifo, p_buff, 1) != -1)
        {
            count = ring_fifo_data_number(&read_fifo);
            buffer_fifo_read(&read_fifo, &p_buff[1], count);
            for (int i = 0; i < count + 1; i++)
            { // 这里自己竟然没注意到 i 未初始化，呆了耗时大概半小时！！！？ 并且count 没有加一导致最后一个数据丢失，切记哟
                printf("%d ", p_buff[i]);
            }
            printf("\n");
        }
        usleep(2);
    }
    // while (1)
    // {
    //     memset(p_buff, 0x0, sizeof(p_buff));
    //     count = ring_fifo_data_number(&read_fifo);
    //     if (count > 0) {
    //         buffer_fifo_read(&read_fifo, &p_buff[0], count);
    //         for (int i = 0; i < count; i++)
    //         {
    //             printf("%d ", p_buff[i]);
    //         }
    //         printf("\n");
    //     }
    //     usleep(2);
    // }
}

void *function_3(void *argument)
{
    printf("fun 3 running...\n");
}

// gcc main.c ThreadPool.c -o trial -pthread
int main()
{
    pthread_t th1, th2;

    buffer_fifo_init(&read_fifo, 128);
    pthread_create(&th1, NULL, function_1, NULL);
    pthread_create(&th2, NULL, function_2, NULL);

    while (1)
    {
        usleep(100);
    }

    return 0;
}