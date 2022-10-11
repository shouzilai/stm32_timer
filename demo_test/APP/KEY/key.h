#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "DELAY/delay.h"

#define KEY1_GPIO    GPIOC
#define KEY1_PIN     GPIO_Pin_1
#define KEY2_GPIO    GPIOC
#define KEY2_PIN     GPIO_Pin_2

#define KEY1        GPIO_ReadInputDataBit(KEY1_GPIO, KEY1_PIN)
#define KEY2        GPIO_ReadInputDataBit(KEY2_GPIO, KEY2_PIN)

void KEY_Init(void);
int Get_Key(char mode);

#endif
