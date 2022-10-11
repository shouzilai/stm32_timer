#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x.h"

#define SPI_CMD             0
#define SPI_DAT             1

#define SPI_RES_H           GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define SPI_RES_L           GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define SPI_DC_H            GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define SPI_DC_L            GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define SPI_CS_H            GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define SPI_CS_L            GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define SPI_PIN_CLK         GPIO_Pin_5
#define SPI_PIN_MOSI        GPIO_Pin_7
#define SPI_PIN_RES         GPIO_Pin_0
#define SPI_PIN_DC          GPIO_Pin_10
#define SPI_PIN_CS          GPIO_Pin_11

void OLED_SPI_Init(void);
void OLED_SPI_WR_Byte(unsigned char data,unsigned char cmd);

#endif
