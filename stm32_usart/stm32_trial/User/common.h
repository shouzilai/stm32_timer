#ifndef __COMMOM_H__
#define __COMMOM_H__

#include "stm32f10x.h"
#include "usart/usart.h"

#define GPIOC_LED_PIN       GPIO_Pin_13     // PC13
#define RCC_APB2_LED        RCC_APB2Periph_GPIOC

#define GPIOA_KEY_PIN       GPIO_Pin_0      // PA0
#define RCC_APB2_KEY        RCC_APB2Periph_GPIOA

#define RCC_APB1_TIM2       RCC_APB1Periph_TIM2
#define RCC_APB1_TIM3       RCC_APB1Periph_TIM3
#define RCC_APB1_TIM4       RCC_APB1Periph_TIM4


#endif // __COMMOM_H__