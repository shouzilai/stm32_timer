#ifndef __IIC_H__
#define __IIC_H__

#include "stm32f10x.h"

#define IIC_PIN_SCL         GPIO_Pin_6
#define IIC_PIN_SDA         GPIO_Pin_7

void OLED_IIC_Init(void);
void IIC_WriteCmd(unsigned char I2C_Command);
void IIC_WriteData(unsigned char I2C_Data);

#endif
