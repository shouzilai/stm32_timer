#include "timer.h"


static int timer_nvic_config(uint16_t timx_irqn, uint16_t preempt_prior_val, uint16_t sub_prior_val)
{
    NVIC_InitTypeDef NVIC_InitStructure;                        /* TIM2中断优先级配置  TIM2_NVIC_Configuration*/
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    NVIC_InitStructure.NVIC_IRQChannel = timx_irqn;             // TIM3_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preempt_prior_val;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_prior_val;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    // printf("timer NVIC config success!!!\n");
    return 0;
}

static int timer_detail_config(TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;             /*中断周期为1ms TIM2_Configuration*/

    RCC_APB1PeriphClockCmd(rcc_apb1periph_timx, ENABLE);
    TIM_DeInit(timx);

    TIM_TimeBaseStructure.TIM_Period = AUTO_RELOAD_VAL - 1;	                    //自动重装载寄存器周期的值(计数值) 
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler = PRE_SCALE_VAL - 1;	                //时钟预分频数 72M/72
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //向上计数模式
    TIM_TimeBaseInit(timx, &TIM_TimeBaseStructure);

    TIM_ClearFlag(timx, TIM_FLAG_Update);	                    // 清除溢出中断标志
    TIM_ITConfig(timx, TIM_IT_Update, ENABLE);

    TIM_Cmd(timx, ENABLE);	                                    // 开启时钟
    RCC_APB1PeriphClockCmd(rcc_apb1periph_timx, DISABLE);	    //先关闭等待使用

    // printf("timer config success!!!\n");
    return 0;
}

int timer_init(uint16_t timx_irqn, uint16_t preempt_prior_val, uint16_t sub_prior_val, 
                TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx)
{
    int ret = -1;

    ret = timer_nvic_config(timx_irqn, preempt_prior_val, sub_prior_val);
    ret += timer_detail_config(timx, rcc_apb1periph_timx);
    if (ret < 0) {
        printf("timer init faliure\n");
        return -1;
    }
    
    return 0;
}

int timer_deinit(void)
{
    return 0;
}

int timer_start(TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx)
{
    RCC_APB1PeriphClockCmd(rcc_apb1periph_timx, ENABLE);
    TIM_Cmd(timx, ENABLE);
    
    return 0;
}

int timer_stop(TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx)
{
    TIM_Cmd(timx, DISABLE);
    RCC_APB1PeriphClockCmd(rcc_apb1periph_timx, DISABLE);
    
    return 0;
}

