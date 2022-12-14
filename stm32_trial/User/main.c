#include "stm32f10x.h"
#include "led/led.h"
#include "key/key.h"
#include "exti.h"
#include "timer/timer.h"
#include "common.h"

#define CLI() __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)		/* 开放总中断 */ 

volatile u32 time = 0; // ms 计时变量

void Delay(__IO u32 nCount);


int main(void)
{
    // SystemInit(); /* 配置系统时钟为 72M */	
    
    led_config_init(RCC_APB2Periph_GPIOC, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);/* led 端口配置 */ 
    
    TIM2_NVIC_Configuration(); /* TIM2 定时配置 */
    TIM2_Configuration();
    START_TIME;	 /* TIM2 开始计时 */
    
    while(1)
    {
        printf("time off %d\n", time);
        if ( time >= 50 ) /* 500ms 时间到 */
        {
            time = 0;
            printf("time on %d\n", time);
            GPIO_WriteBit(GPIOC, GPIOC_LED_PIN, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOC, GPIOC_LED_PIN)))); /* LED1 取反 */ 
        }
    }
    return 0;
}

int main_exti_key(void)
{
    /* config the led */
    // LED_GPIO_Config();
    // led_config_init(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC | GPIOF);
    uint32_t rcc_integration = RCC_APB2Periph_GPIOC;
    GPIO_TypeDef *gpiox_integration = GPIOC;
    
    led_config_init(RCC_APB2Periph_GPIOC, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);
    LED_OFF;
    Delay(50000);
    LED_ON;
    
    CLI();
    SEI();
    
    /* exti line config */
    EXTI_PA0_Config(); 
    
    /* wait interrupt */
    while (1) {
        Delay(0xffffef);
        printf(" ^ - ^ \n");
    }
}

int main_key(void)
{
    /*config the led*/
    led_config_init(RCC_APB2Periph_GPIOC, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);
    LED1(ON);

    /*config key*/
    key_config_init(RCC_APB2Periph_GPIOA, GPIOA_KEY_PIN, GPIO_Mode_IPU, GPIOA);

    while (1) {
        if (Key_Scan(GPIOA, GPIOA_KEY_PIN) == KEY_ON) {
            /*LED1反转*/
            printf("key trigger......\n");
            GPIO_WriteBit(GPIOC, GPIOC_LED_PIN, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOC, GPIOC_LED_PIN))));
        }
    }
    return 0;
}

int main_led(void)
{
    /*LED端口初始化*/
    led_config_init(RCC_APB2Periph_GPIOC, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);

    while (1) {
        printf(" - - \n");
        LED1(ON);	// 亮 GPIO_SetBits(GPIOC, GPIO_Pin_3);
        Delay(0x0FFFEF);
        LED1(OFF);	// 灭 GPIO_ResetBits(GPIOC, GPIO_Pin_3);
        
        LED1(ON);
        Delay(0x0FFFEF);
        LED1(OFF);

        LED1(ON);
        Delay(0x0FFFEF);
        LED1(OFF);
    }
}

void Delay(__IO u32 nCount)// 简单的延时函数
{
    for ( ;nCount != 0; nCount--);
}
