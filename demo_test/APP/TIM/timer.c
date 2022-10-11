#include "timer.h"

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM_Configuration(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //‘ –ÌTIM2µƒ ±÷”
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseStructure.TIM_Period=(1000-1);
	TIM_TimeBaseStructure.TIM_Prescaler=(7200-1);
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);						 
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}


