#include "hip.h"


static void reset_hip_state(hip_protocol_handle_p hip)
{
    hip->state                   = EM_HIP_STATE_VER;
    hip->read_len                = 0;
    hip->dev_type                = HIP_DEV_TYPE;
    hip->dev_id                  = HIP_DEV_ID;
    hip->cur_seq                 = 0;
    memset(hip->hip_frame.payload, 0x0, sizeof(HIP_PAYLOAD_SIZE));
    
    return;
}

int hip_init(hip_protocol_handle_p hip, void (*hip_success_handle_func)(hip_protocol_type_p))
{
    if (NULL == hip || NULL == hip_success_handle_func) {
        return -1;
    }

    hip->state                   = EM_HIP_STATE_VER;
    hip->read_len                = 0;
    hip->dev_type                = HIP_DEV_TYPE;
    hip->dev_id                  = HIP_DEV_ID;
    hip->cur_seq                 = 0;
    hip->hip_success_handle_func = hip_success_handle_func;
    hip->hip_frame.payload       = (uint8_t*)malloc(sizeof(uint8_t) * HIP_PAYLOAD_SIZE);
    memset(hip->hip_frame.payload, 0x0, sizeof(HIP_PAYLOAD_SIZE));

    return 0;
}

int hip_deinit(hip_protocol_handle_p hip)
{
    if (NULL == hip || NULL == hip->hip_frame.payload) {
        return -1;
    }
    reset_hip_state(hip);

    hip->hip_success_handle_func = NULL;
    free(hip->hip_frame.payload);
    hip->hip_frame.payload = NULL;
    
    return 0;
}

int hip_pack(hip_protocol_handle_p hip, hip_protocol_cmd_em cmd, uint8_t* frame_buf,
                                uint8_t frame_len, uint8_t* data_addr, uint8_t data_len)
{
    if ((NULL == hip) | (NULL == frame_buf) | (NULL == data_addr)) {
        printf("[ERROR] hip pack arg\n");
        return -1;
    }
    if (frame_len < (data_len + 16)) {
        printf("[ERROR] hip pack frame_len\n");
        return -1;
    }

    memset(frame_buf, 0x0, frame_len);

    frame_buf[0] = HIP_VERSION;
    frame_buf[1] = cmd;
    frame_buf[2] = data_len + 16;
    frame_buf[3] = hip->dev_type;

    for (int i = 0; i < 8; i++) {
        frame_buf[4 + i] = hip->dev_id >> (8 * (7 - i));  // 00 // 00 // 12 // 34 // 56 // 78 // ab // cd     
    } // ????????????hip????????????

    for (int i = 0; i < 4; i++) {
        frame_buf[12 + i] = hip->cur_seq >> (8 * (3 - i)); // 00 // 00 // 00 // 00
    } // ????????????hip????????????

    memcpy(&frame_buf[17], data_addr, data_len); // ????????????????????????frame_buf???????????????

    return data_len + 17;
} 

int hip_parse(hip_protocol_handle_p hip, uint8_t data_byte)
{
    if (NULL == hip) {
        printf("[ERROR] hip parse arg\n");
        return -1;
    }
    uint8_t i = 0;

    switch (hip->state) {
    case EM_HIP_STATE_VER:
        if (HIP_VERSION == data_byte) {
            hip->read_len = 0;
            hip->hip_frame.version = data_byte;
            hip->state = EM_HIP_STATE_CMD;
        }
        break;

    case EM_HIP_STATE_CMD:
        hip->hip_frame.command = data_byte;
        hip->state = EM_HIP_STATE_LEN;
        break;

    case EM_HIP_STATE_LEN:
        hip->hip_frame.length = data_byte;
        hip->state = EM_HIP_STATE_DEV_TYPE;
        break;

    case EM_HIP_STATE_DEV_TYPE:
        hip->hip_frame.device_type = data_byte;
        hip->state = EM_HIP_STATE_DEV_ID;
        break;

    case EM_HIP_STATE_DEV_ID:
        hip->read_len++;
        hip->hip_frame.device_id |= (data_byte << (8 - hip->read_len)); // ?????????uint8_t????????????????????????uint64_t????????????????????????
        if (hip->read_len == 8) {
            hip->state = EM_HIP_STATE_SEQ;
            hip->read_len = 0;
        }
        break;

    case EM_HIP_STATE_SEQ:
        hip->read_len++;
        hip->hip_frame.seq |= (data_byte << (4 - hip->read_len)); // ?????????uint8_t????????????????????????uint32_t????????????????????????
        if (hip->read_len == 4) {
            if (hip->hip_frame.length == 0) { // hip????????????????????????????????????????????????????????????
                hip->state = EM_HIP_STATE_VER;
                hip->hip_success_handle_func(&hip->hip_frame);
                return 1;
                break;
            } else { // ????????????????????????????????????????????????
                hip->state = EM_HIP_STATE_PL;
                hip->read_len = 0;
            }
        }
        break;

    case EM_HIP_STATE_PL:
        hip->hip_frame.payload[hip->read_len++] = data_byte;
        if (hip->read_len == (hip->hip_frame.length - 16)) {
            hip->hip_success_handle_func(&hip->hip_frame);
            hip->state = EM_HIP_STATE_VER;
            return 1;
            break;
        }
        break;

    default:
        break;
    }
    return 0;
}
