#ifndef __APP_H__
#define __APP_H__

#include "usart/usart.h"


typedef struct message1 {
    uint8_t command;
    uint8_t commit_message[128];
} message_t, *message_p;

typedef struct app {
    message_t message_usart;
    usart_t usart;
} app_t, *app_p;





#endif // __APP_H__