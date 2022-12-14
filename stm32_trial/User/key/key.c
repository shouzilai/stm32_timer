#include "key.h"


static void Delay(__IO u32 nCount)
{
    for(; nCount != 0; nCount--);
}

void key_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, GPIOMode_TypeDef gpio_mode, GPIO_TypeDef *gpiox)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(rcc_apb2_periph_gpiox, ENABLE); //开启按键端口PB的时钟
    
    GPIO_InitStructure.GPIO_Pin = gpio_pinx;

    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_InitStructure.GPIO_Mode = gpio_mode;
    
    GPIO_Init(gpiox, &GPIO_InitStructure);
}

u8 Key_Scan(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    /*检测是否有按键按下*/
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
        /*延时消抖*/
        Delay(10000);
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
            /*等待按键释放*/
            while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {

            }
            return KEY_ON;
        }
        else {
            return KEY_OFF;
        }
    } else {
        return KEY_OFF;
    }
}