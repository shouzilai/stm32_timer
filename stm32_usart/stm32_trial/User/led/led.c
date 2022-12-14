#include "led.h"


static int cur_time = 0;
static int count_times = 50;

static void led_gpio_config(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, 
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

int led_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, 
        GPIOMode_TypeDef gpio_mode, GPIOSpeed_TypeDef gpio_speed, GPIO_TypeDef *gpiox)
{
    led_gpio_config(rcc_apb2_periph_gpiox, gpio_pinx, gpio_mode, gpio_speed, gpiox);

    timer_init(TIM2_IRQn, 0, 0, TIM2, RCC_APB1_TIM2);

    return 0;
}

int led_deinit(void)
{
    timer_deinit();
    return 0;
}

int led_start(void)
{
    timer_start(TIM2, RCC_APB1_TIM2);
    return 0;
}

int led_stop(void)
{
    timer_stop(TIM2, RCC_APB1_TIM2);
    return 0;
}

void led_speed_set(int c_times)
{
    cur_time = 0;
    count_times = c_times * 10;
}

void TIM2_IRQHandler(void)
{
    int count = 5000, portation = 1;

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {	
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);  
        cur_time += 10;
        if ( cur_time >= count_times) /* 500ms 时间到 */
        {
            cur_time = 0;
            // printf("cur_time on %d\n", cur_time);
            GPIO_WriteBit(GPIOC, GPIOC_LED_PIN, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOC, GPIOC_LED_PIN)))); /* LED1 取反 */ 
        }
        
    }
}

