#include "hup.h"

static uint8_t data[128];
static struct hup_protocol_assist assistance = {0, EM_HUP_STATE_HDR_H, 0, 0};
static hup_protocol_type_t hup_frame_reply;

static void hup_parse_assist_reset()
{
    printf("reset hup_parse !!!\r\n");
    assistance.is_response = 0;
    assistance.state = EM_HUP_STATE_HDR_H;
    assistance.read_len = 0;
    assistance.xor8 = 0;
}

int hup_init(hup_protocol_type_p hup_p, int buf_size, void (*hup_success_handle_func)(hup_protocol_type_p))
{
    if (NULL == hup_p || NULL == hup_success_handle_func) {
        return -1;
    }

    hup_parse_assist_reset();
    assistance.hup_success_handle_func = hup_success_handle_func;
    hup_p->data_addr = (uint8_t *)malloc(sizeof(int)*buf_size);
    memset(hup_p->data_addr, 0x0, sizeof(hup_p->data_addr));
}

int hup_deinit(hup_protocol_type_p hup_p)
{
    if(NULL == hup_p){
        return -1;
    }
    assistance.hup_success_handle_func = NULL;
    free(hup_p->data_addr);
    return 0;
}

static int hup_xor8_calculate(hup_protocol_type_p hup_frame)
{
    if (hup_frame == NULL) {
        return -1;
    }
    uint8_t xor8_result = 0;
    uint8_t hdr_h = hup_frame->hdr_h;
    uint8_t hdr_l = hup_frame->hdr_l;
    uint8_t cmd = hup_frame->cmd;
    uint8_t data_len = hup_frame->data_len;
    uint8_t *temp = hup_frame->data_addr;

    xor8_result = hdr_h ^ hdr_l ^ cmd ^ data_len;
    for (int i = 0; i < data_len; i++) {
        xor8_result ^= temp[i];
    }
    hup_frame->xor8 = xor8_result;

    return 0;
}

static int hup_pack_sort(hup_protocol_type_em sort, hup_protocol_type_p hup_frame)
{
    if (sort != EM_HUP_TYPE_REQ  && sort != EM_HUP_TYPE_ACK) {
        printf("hup pack sort is wrong!!!\r\n");
        return -1;
    }
    switch(sort)
    {
        case EM_HUP_TYPE_REQ:
            {
                hup_frame_reply.hdr_h = HUP_REQ_HDR_H;
                hup_frame_reply.hdr_l = HUP_REQ_HDR_L;
            }
            break;

        case EM_HUP_TYPE_ACK:
            {
                hup_frame_reply.hdr_h = HUP_ACK_HDR_H;
                hup_frame_reply.hdr_l = HUP_ACK_HDR_L;
            }
            break;

        default:
            break;
    }
    hup_xor8_calculate(&hup_frame_reply);

    return 0;
}

hup_protocol_type_p hup_pack(hup_protocol_type_em sort, int cmd, int len, uint8_t* addr)
{
    if (NULL == addr || len < 0 || len > 1500) {
        return NULL;
    }
    hup_frame_reply.data_addr = data;
    memset(hup_frame_reply.data_addr, 0x0, sizeof(data));
    
    hup_frame_reply.cmd = cmd;
    hup_frame_reply.data_len = len;
    for (int i = 0; i < len; i++) {
        hup_frame_reply.data_addr[i] = addr[i];
    }
    if (hup_pack_sort(sort, &hup_frame_reply) == -1) {
        return NULL;
    }
    
    printf("pack hup frame success\r\n");
    return &hup_frame_reply;
}

int hup_parse(hup_protocol_type_p hup_frame_ask, uint8_t data)
{
    if (hup_frame_ask == NULL) {
        printf("hup parse is NULL!!!\r\n");
        return -1;
    }
    switch(assistance.state)
    {
        case EM_HUP_STATE_HDR_H:            // ???????????? hup ?????????????????????
            if (HUP_REQ_HDR_H == data) {
                printf("parsing head hign \r\n");
                hup_frame_ask->hdr_h = data;
                assistance.is_response = 0;
                assistance.state = EM_HUP_STATE_HDR_L;
                assistance.xor8 ^= data;
            } else if (HUP_ACK_HDR_H == data) {
                printf("parsing head hign \r\n");
                hup_frame_ask->hdr_h = data;
                assistance.is_response = 1;
                assistance.state = EM_HUP_STATE_HDR_L;
                assistance.xor8 ^= data;
            } else {
                printf("parsing failure, throw data then retry to parse \r\n");
                hup_parse_assist_reset();
            }
            break;
         
        case EM_HUP_STATE_HDR_L:            // ???????????? hup ????????????????????? 
            if (HUP_REQ_HDR_L == data) {
                printf("parsing head low \r\n");
                hup_frame_ask->hdr_l = data;
                assistance.is_response = 0;
                assistance.state = EM_HUP_STATE_CMD;
                assistance.xor8 ^= data;
            } else if (HUP_ACK_HDR_L == data) {
                printf("parsing head low \r\n");
                hup_frame_ask->hdr_l = data;
                assistance.is_response = 1;
                assistance.state = EM_HUP_STATE_CMD;
                assistance.xor8 ^= data;
            } else{
                printf("parsing failure, throw data then retry to parse \r\n");
                hup_parse_assist_reset();
            }
            break;

        case EM_HUP_STATE_CMD:
            printf("parsing cmd \r\n");
            hup_frame_ask->cmd = data;
            assistance.state = EM_HUP_STATE_DATA_LEN;
            assistance.xor8 ^= data;
            break;

        case EM_HUP_STATE_DATA_LEN:
            printf("parsing data length \r\n");
            hup_frame_ask->data_len = data;
            memset(hup_frame_ask->data_addr, 0x0, sizeof(hup_frame_ask->data_addr));
            printf("data_len: %d\r\n", data);
            assistance.state = EM_HUP_STATE_DATA;
            assistance.xor8 ^= data;
            break;

        case EM_HUP_STATE_DATA:
            printf("parsing data part \r\n");
            hup_frame_ask->data_addr[assistance.read_len++] = data;
            assistance.xor8 ^= data;
            if (assistance.read_len == hup_frame_ask->data_len) {
                assistance.state = EM_HUP_STATE_CRC;
            }
            break;

        case EM_HUP_STATE_CRC:
            printf("parsing data recycle check \r\n");
            hup_frame_ask->xor8 = data;
            if (hup_frame_ask->xor8 == assistance.xor8) {
                if (assistance.is_response) {
                    printf("parse response frame successfully !!!\r\n\r\n");
                } else {
                    printf("parse request frame successfully !!!\r\n\r\n");
                    printf("hup_parse:%d, %s\r\n", hup_frame_ask->cmd, hup_frame_ask->data_addr);
                    if (assistance.hup_success_handle_func == NULL) {
                        printf("assistance.hup_success_handle_func is NULL\r\n");
                    }
                    assistance.hup_success_handle_func(hup_frame_ask);
                    hup_parse_assist_reset();
                    return 10;
                }
            }
            printf("CRC wrong!!!\r\n\r\n");
            hup_parse_assist_reset();
            break;

        default:
            break;
    }
    return 0;
    
}

