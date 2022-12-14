#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led/led.h"
#include "../utilities/hup/hup.h"
// #include "utilities/DMA/dma.h"
#include "../utilities/timer/timer.h"
#include "../utilities/fifo/ring_buffer_fifo.h"
#include "../common.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>


#define USART1_DR_Base  0x40013804		// 0x40013800 + 0x04 = 0x40013804

#define USART_FIFO_SIZE 256
#define USART_HUP_SIZE  256
#define USART_SEND_BUFFER_SIZE 136
#define USART_RECV_BUFFER_SIZE 136

#define USART1_DR_Base  0x40013804		// 0x40013800 + 0x04 = 0x40013804
#define SENDBUFF_SIZE   500

typedef struct usart {

    USART_TypeDef* usartx;
    GPIO_TypeDef* gpiox;
    unsigned short int tx_pin;
    unsigned short int rx_pin;
    unsigned int rcc_apb2periph[2];
    FunctionalState rcc_enable[2];

    hup_protocol_type_t hup_frame;

    buffer_fifo_t r_fifo;
    buffer_fifo_t w_fifo;

} usart_t, *usart_p;


int usartx_init(usart_p usart, USART_TypeDef* usartx, void* message_ptr);

int usartx_deinit(usart_p usart);

int usartx_start(usart_p usart);

int usartx_stop(usart_p usart);

int usart_send(usart_p usart, hup_protocol_type_em sort, int cmd, uint8_t* addr, int addr_len);




void USART1_Config(void);

int fputc(int ch, FILE*f);

// void USART1_printf(USART_TypeDef* USARTx, uint8_t* Data, ……);


#endif // __USART_H__