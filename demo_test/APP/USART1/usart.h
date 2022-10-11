#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "FIFO/ring_buffer_fifo.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#define TX_GPIO    GPIOA
#define TX_PIN     GPIO_Pin_9
#define RX_GPIO    GPIOA
#define RX_PIN     GPIO_Pin_10

void USART1_Init(void);
void Usart_Send(uint8_t *addr,uint16_t len);

#endif
