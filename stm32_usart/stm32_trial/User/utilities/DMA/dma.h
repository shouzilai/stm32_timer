#ifndef __DMA_H__
#define __DMA_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
#include <stdint.h>


#define USART1_DR_Base  0x40013804		// 0x40013800 + 0x04 = 0x40013804
#define SENDBUFF_SIZE   500

void DMA_Config(void);

int dma_send_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx);

int dma_send_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx);

int dma_send_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx);

int dma_send_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx);

#endif // __DMA_H__