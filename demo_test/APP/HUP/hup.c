#include "hup.h"

hup_protocol_type_t hup_frame;

static void _hup_protocol_success(void)
{
    if(!strncmp((char *)hup_frame.data_addr,"OPEN",4)){
        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
        Usart_Send("OPENED!\n",8);
    }
    else if(!strncmp((char *)hup_frame.data_addr,"CLOSE",5)){
        GPIO_SetBits(GPIOB,GPIO_Pin_8);
        Usart_Send("CLOSED!\n",8);
    }
}

//AADD01044F50454E66
int hup_protocol_decode(uint8_t data_byte)
{
    static uint8_t state = EM_HUP_STATE_HDR_H;
    static uint8_t read_len = 0;
    static uint8_t xor8 = 0;
    switch(state)
    {
        case EM_HUP_STATE_HDR_H:
            if(HUP_REQ_HDR_H == data_byte) {
                hup_frame.hdr_h = data_byte;
                state = EM_HUP_STATE_HDR_L;
                xor8 ^= data_byte;
            }
            break;
        case EM_HUP_STATE_HDR_L:
            if(HUP_REQ_HDR_L == data_byte){
                hup_frame.hdr_l = data_byte;
                state = EM_HUP_STATE_CMD;
                xor8 ^= data_byte;
            }
            else{
                state = EM_HUP_STATE_HDR_H;
                xor8 = 0;
            }
            break;
        case EM_HUP_STATE_CMD:
            hup_frame.cmd = data_byte;
            state = EM_HUP_STATE_DATA_LEN;
            xor8 ^= data_byte;
            break;
        case EM_HUP_STATE_DATA_LEN:
            hup_frame.data_len = data_byte;
            state = EM_HUP_STATE_DATA;
            xor8 ^= data_byte;
            break;
        case EM_HUP_STATE_DATA:
            hup_frame.data_addr[read_len++] = data_byte;
            xor8 ^= data_byte;
            if(read_len == hup_frame.data_len){
                state = EM_HUP_STATE_CRC;
            }
            break;
        case EM_HUP_STATE_CRC:
            hup_frame.xor8 = data_byte;
            state = EM_HUP_STATE_HDR_H;
            if(hup_frame.xor8 == xor8){
                _hup_protocol_success();
            }
            else{
                return -1;
            }
            read_len = 0;
            xor8 = 0;
            break;
        default:
            break;
    }
    return 0;
}

