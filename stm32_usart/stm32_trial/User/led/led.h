#ifndef __LED_H__
#define __LED_H__


#include "stm32f10x.h"
#include "led/led.h"
#include "utilities/timer/timer.h"
#include "common.h"

#define ON 0
#define OFF 1
// 带参宏，可以像内联函数一样使用
#define LED1(a) if(a) GPIO_SetBits(GPIOC, GPIOC_LED_PIN);\
else\
 GPIO_ResetBits(GPIOC, GPIOC_LED_PIN)

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p, i)			{p->BSRR = i;}			//设置为高电平		
#define digitalLo(p, i)			{p->BRR	= i;}			//输出低电平
#define digitalToggle(p, i)		{p->ODR ^= i;}			//输出反转状态

/* 定义控制IO的宏 */
#define LED_TOGGLE	GPIO_WriteBit(GPIOC, GPIOC_LED_PIN, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOC, GPIOC_LED_PIN))));
                                                                // digitalToggle(GPIOC, GPIOC_LED_PIN)
#define LED_OFF		GPIO_SetBits(GPIOC, GPIOC_LED_PIN);     // digitalHi(GPIOC, GPIOC_LED_PIN)
#define LED_ON		GPIO_ResetBits(GPIOC, GPIOC_LED_PIN);   // digitalLo(GPIOC, GPIOC_LED_PIN)

int led_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, 
        GPIOMode_TypeDef gpio_mode, GPIOSpeed_TypeDef gpio_speed, GPIO_TypeDef *gpiox);

int led_deinit(void);

int led_start(void);

int led_stop(void);

void led_speed_set(int c_times);

void TIM2_IRQHandler(void);

#endif // __LED_H__