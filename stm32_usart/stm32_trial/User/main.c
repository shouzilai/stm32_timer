#include <stdio.h>

#include "stm32f10x.h"
#include "led/led.h"
#include "key/key.h"
#include "usart/usart.h"
#include "utilities/hup/hup.h"
#include "utilities/timer/timer.h"
// #include "utilities/dma/dma.h"
#include "utilities/fifo/ring_buffer_fifo.h"
#include "common.h"

typedef struct message1 {
    uint8_t command;
    uint8_t commit_message[128];
} message_t, *message_p;

typedef struct app {
    message_t message_usart;
    usart_t usart;
} app_t, *app_p;

static void hup_frame_printf(hup_protocol_type_p hup_p)
{
    uint8_t* tep = (uint8_t*)hup_p;
    printf("\r\nhup frame data is ");
    for (int i = 0; i < 4; i++) {
        printf("0x%x ", *tep++);
    }
    tep = hup_p->data_addr;
    for (int i = 0; i < hup_p->data_len; i++) {
        printf("0x%x ", *tep++);
    }
    printf("0x%x ", hup_p->xor8);
    printf("\r\n");
}

void Delay1(__IO u32 nCount)// 简单的延时函数
{
    for ( ;nCount != 0; nCount--);
}



int main(void)
{
    int ret = 0;
    app_t app;
    uint8_t usart_data[20] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
    
    usartx_init(&app.usart, USART1, (void*)&app.message_usart);
    usartx_start(&app.usart);
    /*填充将要发送的数据*/
    usart_send(&app.usart, EM_HUP_TYPE_REQ, 0x31, (uint8_t*)usart_data, 9);

    /*串口向DMA发出请求*/
    // USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    
    /*在DMA尚未传送完成时，CPU继续执行main函数中的代码*/
    /*点亮了LED灯*/
    /*而同时DMA在向串口运送数据，当DMA发送完成时，在中断函数关闭LED灯*/
    LED1(ON);
    // Delay1(0xffff);
    // usart_send(&usart, EM_HUP_TYPE_REQ, 0x36, (uint8_t*)usart_data, 9);
    
    while (1) {
        Delay1(0xfffffe);
        uint8_t data;
        // printf("message data is ");
        // for (int i = 0; i < 36; i++) {
        //     printf("0x%x ");
        // }
        printf("\n");


        // usart_send(&usart, EM_HUP_TYPE_REQ, 0x36, (uint8_t*)usart_data, 9);
        // ret = buffer_fifo_read(&app.usart.r_fifo, &data, 1);
        // if (ret != -1) {
        //     printf("0x%x  ", data);
        // }
        
    }

    return 0;
}

uint16_t i;

int main_dma(void)
{
    uint8_t usart_data[20] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
    usart_t usart;
    
    // usartx_init(&usart, USART1);
    usartx_start(&usart);
    // dma_send_init(RCC_AHBPeriph_DMA1, DMA1_Channel4_IRQn, USART1_DR_Base, (u32)SendBuff, 500, DMA1_Channel4);

    // printf("this is a demo for usart init dam program\r\n");
    /*填充将要发送的数据*/
    usart_send(&usart, EM_HUP_TYPE_REQ, 0x01, (uint8_t*)usart_data, 9);


    /*串口向DMA发出请求*/
    // USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    
    /*在DMA尚未传送完成时，CPU继续执行main函数中的代码*/
    /*点亮了LED灯*/
    /*而同时DMA在向串口运送数据，当DMA发送完成时，在中断函数关闭LED灯*/
    LED1(ON);
    
    while(1);

    return 0;
}


int main_usart()
{
    usart_t usart;
    
    // usartx_init(&usart, USART1);
    usartx_start(&usart);

    printf("this is a demo for usart program\r\n");

    while (1) {
        LED_ON;
        Delay1(0xffffef);
        LED_OFF;
        Delay1(0xfffef);
    }
     
    return 0;
}

int main_fifo(void)
{
    uint8_t ret = 0;
    uint8_t* tep;
    hup_protocol_type_p temp;
    hup_protocol_type_t trial_hup;
    buffer_fifo_t fifo;
    uint8_t usart_data[20] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9};

    usart_t usart;
    // usartx_init(&usart, USART1);
    usartx_start(&usart);
 
    printf("--\r\n");

    // hup_init(&trial_hup, 256, &hup_success_handle);
    buffer_fifo_init(&fifo, 256);

    temp = hup_pack(EM_HUP_TYPE_REQ, 0x01, 9, usart_data);
    tep = (uint8_t*)temp;
    buffer_fifo_write(&fifo, tep, sizeof(trial_hup));

    // printf("copy xor8 is 0x%x\r\n", trial_hup.xor8);
    buffer_fifo_read(&fifo, usart_data, sizeof(trial_hup));


    while (1) {
      if (ret++ < 1) {
            hup_frame_printf((hup_protocol_type_p)usart_data);
            USART_SendData(USART1, 0x32); // 串口上只能显示ASCII中可显示字符，其他都是空格
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        } else {
            break;
        }
    }

    while (1);
    return 0;
    return 0;
}


static void led_state(KEY_TYPE *key_type)
{
    static u8 short_count = 0;
    switch(*key_type)
        {
            case SHORT_KEY:
                if (short_count == 0) {
                    led_stop();
                    led_start();
                    led_speed_set(300);               // 慢闪
                    printf("slowly\n");
                } else {
                    led_stop();
                    led_start();
                    led_speed_set(200);               // 快闪
                    printf("quickly\n");
                }
                short_count = (short_count + 1) % 2;
                *key_type = 0;		            // 状态回到空
                break;

            case LONG_KEY:
                led_stop();
                LED_OFF;
                printf("longly\n");
                *key_type = 0;		            // 状态回到空
                break;

            default:
                break;
        }
}

int main_led_key()
{
    KEY_TYPE cur_key_type;

    led_config_init(RCC_APB2_LED, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);
    key_config_init(RCC_APB2_KEY, GPIOA_KEY_PIN, GPIO_Mode_IPU, GPIOA);
    
    key_scan_start();

    while(1)
    {
        cur_key_type = key_scan_return();
        led_state(&cur_key_type);
    }
}

