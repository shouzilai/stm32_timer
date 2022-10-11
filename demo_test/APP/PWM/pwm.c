#include "pwm.h"

void PWM_Init(u16 arr)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    //允许GPIO的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //创建结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //使能TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
	//初始化定时器TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;                         //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;                       //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);                 //根据指定的参数初始化TIMx的时间基数单位
    
    //PWM模式配置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    		//配置为PWM模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	    //当定时器计数值小于CCR1_Val时为低电平
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);	 					//使能通道
    
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);				//使能预装载	
    TIM_ARRPreloadConfig(TIM4, ENABLE);			 					//使能TIM重载寄存器ARR
    TIM_SetCompare4(TIM4,0);
    
	//定时器TIM3使能
	TIM_Cmd(TIM4,ENABLE);
}


