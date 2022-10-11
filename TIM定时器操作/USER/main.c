/***************************************
 * �ļ���  ��main.c
 * ����    ��LED1��500ms��Ƶ����˸(��ʱ�� TIM2 ������ʱ)��         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * ��汾  ��ST3.0.0   *

*********************************************************/	

#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms ��ʱ����


int main(void)
{
	  
	SystemInit(); /* ����ϵͳʱ��Ϊ 72M */	
	
	LED_GPIO_Config();/* led �˿����� */ 
	
	TIM2_NVIC_Configuration(); /* TIM2 ��ʱ���� */
    TIM2_Configuration(); 	
	START_TIME;	 /* TIM2 ��ʼ��ʱ */
	
  while(1)
  {
    if ( time == 500 ) /* 500ms ʱ�䵽 */
    {
      time = 0;				     
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)))); /* LED1 ȡ�� */ 
    }        
  }
}


