#ifndef __KEY_H__
#define __KEY_H__


#include "stm32f10x.h"
#include "utilities/timer/timer.h"
#include "../common.h"

#define KEY_ON	0
#define KEY_OFF	1
#define KEY_IO_RCC        RCC_APB2Periph_GPIOA      
#define KEY_IO_PORT       GPIOA
#define KEY_IO_PIN        GPIO_Pin_0

#define Key  GPIO_ReadInputDataBit(KEY_IO_PORT, KEY_IO_PIN)     // Key: 1:高电平，按键未按下， 0：低电平，按键按下


typedef enum EM_KEY_STATE {
    KEY_CHECK = 0,
    KEY_COMFIRM = 1,
    KEY_RELEASE = 2
} KEY_STATE;

typedef enum EM_KEY_TYPE {
    NULL_KEY = 0,
    SHORT_KEY = 1,
    LONG_KEY
} KEY_TYPE;

int key_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, GPIOMode_TypeDef gpio_mode, 
        GPIO_TypeDef *gpiox);

int key_config_deinit(void);

int key_scan_start(void);

int key_sacn_stop(void);

KEY_TYPE key_scan_return(void);


void TIM3_IRQHandler(void);


#endif // __KEY_H__