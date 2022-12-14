#ifndef __TIMER_KEY_H__
#define __TIMER_KEY_H__

#include "stm32f10x.h"

#define AUTO_RELOAD_VAL   1000
#define PRE_SCALE_VAL     72


int timer_init(uint16_t timx_irqn, uint16_t preempt_prior_val, uint16_t sub_prior_val, 
        TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx);

int timer_deinit(void);

int timer_start(TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx);

int timer_stop(TIM_TypeDef *timx, uint32_t rcc_apb1periph_timx);


#endif // __TIMER_KEY_H__