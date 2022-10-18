// #include "cmds_parse.h"


// int parse_cmd(uint8_t cmd, uint8_t *data, cmd_p cmd_ptr)
// {
//     printf("parse cmd is %d\n", cmd);
//     if (cmd == 0x00) {
//         return 0;

//     } else if (cmd > 0x00 && cmd <= 0x04) {
//         printf("led cmd implement......%x\n", cmd);
//         set_led_cmd(cmd, &cmd_ptr->led_cmds);
//         return 1;

//     } else if (cmd >= 0x04 && cmd <= 0x8) {
//         printf("inet cmd implement......%x\n", cmd);
//         set_inet_cmd(cmd, data, &cmd_ptr->inet_cmds);
//         return 3;

//     } else {
//         printf("uart cmd implement......%x\n", cmd);
//         set_uart_cmd(cmd, &cmd_ptr->uart_cmds);
//         return 2;
//     }
// }

// int set_led_cmd(uint8_t cmd, led_cmd_p led_p)
// {
//     printf("set_led_cmd cmd is %d\n", cmd);
//     switch (cmd)
//     {
//     case 0x01:
//         printf("led cmd 1 success\n\n");
//         led_p->led_num[0] = EM_HL_LED_GREEN;
//         led_p->led_mode[0] = LED_MODE_LIGHT;
//         led_p->ctrl_num = 1;
//         led_p->val[0] = 0;
//         return 1;
//         break;
    
//     case 0x02:
//         printf("led cmd 2 success\n");
//         led_p->led_num[0] = EM_HL_LED_GREEN;
//         led_p->led_mode[0] = LED_MODE_LIGHT;
//         led_p->ctrl_num = 1;
//         led_p->val[0] = 1;
//         return 1;
//         break;

//     case 0x03:
//         led_p->led_num[0] = EM_HL_LED_GREEN;
//         led_p->led_mode[0] = LED_MODE_TRIGGER;
//         led_p->ctrl_num = 1;
//         led_p->val[0] = 3;
//         return 1;
//         break;

//     case 0x04:
//         led_p->led_num[0] = EM_HL_LED_GREEN;
//         led_p->led_mode[0] = LED_MODE_TRIGGER;
//         led_p->ctrl_num = 1;
//         led_p->val[0] = 1;
//         return 1;
//         break;

//     default:
//         return 0;
//         break;
//     }
// }

// static int is_addr_equal(struct sockaddr_in *a_addr, struct sockaddr_in *b_addr)
// {
//     char ip_a[16], ip_b[16];

//     inet_ntop(AF_INET, &a_addr->sin_addr.s_addr, ip_a, sizeof(ip_a));
//     inet_ntop(AF_INET, &b_addr->sin_addr.s_addr, ip_b, sizeof(ip_b));
//     for (int i = 0; i < sizeof(ip_a); i++) {
//         if (ip_a[i] != ip_b[i]) {
//             return -1;
//         }
//     }
//     return 0;
// }

// #if INET_TCP_SERVER
// int set_inet_server_cmd(uint8_t cmd, uint8_t *data, inet_cmd_p inet_p)
// {

// }
// #else
// int set_inet_client_cmd(uint8_t cmd, uint8_t *data, inet_cmd_p inet_p)
// {
//     // EM_HIP_CMD_DETECT_REQUEST = 0x05,
//     // EM_HIP_CMD_USER_LOGIN,
//     // EM_HIP_CMD_KEEP_ALIVE,
//     // EM_HIP_CMD_UART_PASS_THROUGH
//     switch(cmd)
//     {
//         case EM_HIP_CMD_DETECT_REQUEST:
//         break;

//         case EM_HIP_CMD_USER_LOGIN:
//         break;

//         case EM_HIP_CMD_KEEP_ALIVE:
//         break;
        
//         case EM_HIP_CMD_UART_PASS_THROUGH:
//         break;
//     }

// }
// #endif


// int set_inet_cmd(uint8_t cmd, uint8_t *data, inet_cmd_p inet_p)
// {
// #if INET_TCP_SERVER
//     set_inet_server_cmd
// #else
//     set_inet_client_cmd
// #endif
// }

// int set_uart_cmd(uint8_t cmd, uart_cmd_p uart_ptr)
// {

// }




