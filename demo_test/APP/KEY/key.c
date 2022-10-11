#include "key.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    //‘ –ÌGPIOµƒ ±÷”
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
    GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);
}

int Get_Key(char mode)
{
    static char key_up=1;
    if(mode){
        key_up=1;
    }
    if(key_up==1&&(KEY1==0||KEY2==0)){
        delay_ms(20);
        key_up=0;
        if(KEY1==0){
            return 1;
        }
        else if(KEY2==0){
            return 2;
        }
    }
    else if(KEY1==1&&KEY2==1){
        key_up=1;
    }
 	return 0;
}

