#ifndef __OLED_IIC_H
#define __OLED_IIC_H 

#include "stm32f10x.h"
#include "DELAY/delay.h"
#include "IIC/iic.h"
#include "stdlib.h"

#define OLED_CMD            0	//Ð´ÃüÁî
#define OLED_DATA           1	//Ð´Êý¾Ý

void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_Init(void);

#endif

