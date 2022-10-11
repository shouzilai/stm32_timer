#ifndef __HUP_H__
#define __HUP_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
#include "LED/led.h"
#include "USART1/usart.h"

#define HUP_REQ_HDR_H 0xAA
#define HUP_REQ_HDR_L 0xDD
#define HUP_ACK_HDR_H 0xBB
#define HUP_ACK_HDR_L 0xDD

typedef struct{
    uint8_t hdr_h;
    uint8_t hdr_l;
    uint8_t cmd;
    uint8_t data_len;
    uint8_t data_addr[512];
    uint8_t xor8;
}hup_protocol_type_t,*hup_protocol_type_p;

typedef enum{
    EM_HUP_STATE_HDR_H,
    EM_HUP_STATE_HDR_L,
    EM_HUP_STATE_CMD,
    EM_HUP_STATE_DATA_LEN,
    EM_HUP_STATE_DATA,
    EM_HUP_STATE_CRC,
}hup_protocol_state_em;

typedef enum{
    EM_HUP_TYPE_REQ,
    EM_HUP_TYPE_ACK,
}hup_protocol_type_em;

int hup_protocol_decode(uint8_t data_byte);

#endif
