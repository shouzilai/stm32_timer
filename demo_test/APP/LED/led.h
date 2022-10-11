#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

#define LED_GPIO    GPIOB
#define LED_PIN     GPIO_Pin_8

void LED_Init(void);

#endif
