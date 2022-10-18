// #ifndef __CMDS_PARSE_H__
// #define __CMDS_PARSE_H__

// #include <stdint.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>

// #include "../utility/led/led.h"
// #include "../utility/hip/hip.h"

// typedef struct led_cmd {
//     led_num_em led_num[LED_NUMBER_COUNT]; 
//     led_cmd_mode_em led_mode[LED_NUMBER_COUNT];
//     int ctrl_num;
//     int val[LED_NUMBER_COUNT];
// }led_cmd_t, *led_cmd_p;

// typedef struct uart_cmd {
//     int ret_cmd;
// }uart_cmd_t, *uart_cmd_p;

// typedef struct inet_cmd {
//     hip_protocol_cmd_em hip_cmd_em;
//     int target_fd;
// }inet_cmd_t, *inet_cmd_p;

// typedef struct cmd {
//     led_cmd_t led_cmds;
//     uart_cmd_t uart_cmds;
//     inet_cmd_t inet_cmds;
// }cmd_t, *cmd_p;


// int parse_cmd(uint8_t cmd, uint8_t *data, cmd_p cmd_ptr);

// int set_led_cmd(uint8_t cmd, led_cmd_p led_ptr);

// int set_uart_cmd(uint8_t cmd, uart_cmd_p urat_ptr);

// int set_inet_cmd(uint8_t cmd, uint8_t *data, inet_cmd_p inet_p);

// #endif // __CMDS_PARSE_H__