#include "pwm.h"

void PWM_Init(u16 arr)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    //����GPIO��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //�����ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //ʹ��TIM3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
	//��ʼ����ʱ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;                         //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;                       //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);                 //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    
    //PWMģʽ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    		//����ΪPWMģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	    //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);	 					//ʹ��ͨ��
    
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);				//ʹ��Ԥװ��	
    TIM_ARRPreloadConfig(TIM4, ENABLE);			 					//ʹ��TIM���ؼĴ���ARR
    TIM_SetCompare4(TIM4,0);
    
	//��ʱ��TIM3ʹ��
	TIM_Cmd(TIM4,ENABLE);
}


