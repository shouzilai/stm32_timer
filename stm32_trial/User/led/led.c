#include "led.h"


void led_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, 
        GPIOMode_TypeDef gpio_mode, GPIOSpeed_TypeDef gpio_speed, GPIO_TypeDef *gpiox)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启GPIOC的外设时钟*/
    RCC_APB2PeriphClockCmd(rcc_apb2_periph_gpiox, ENABLE);

    /*选择要控制的GPIOC引脚*/
    GPIO_InitStructure.GPIO_Pin = gpio_pinx;

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = gpio_mode;

    /*设置引脚速率为50MHz*/
    GPIO_InitStructure.GPIO_Speed = gpio_speed;

    /*调用库函数，初始化GPIOC*/
    GPIO_Init(gpiox, &GPIO_InitStructure);

    /*关闭所有LED灯*/
    GPIO_SetBits(gpiox, gpio_pinx);
}












