#include "led.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    //‘ –ÌGPIOµƒ ±÷”
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LED_GPIO, &GPIO_InitStructure);
}


