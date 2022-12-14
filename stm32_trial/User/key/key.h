#ifndef __KEY_H__
#define __KEY_H__


#include "stm32f10x.h"

#define KEY_ON	0
#define KEY_OFF	1

void key_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, GPIOMode_TypeDef gpio_mode, GPIO_TypeDef *gpiox);

u8 Key_Scan(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);



#endif // __KEY_H__