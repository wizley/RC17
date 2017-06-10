/*
 * uart_log.h
 *
 *  Created on: March 8, 2017
 *      Author: Paul
 */

#ifndef MODULES_UART_LOG_UART_LOG_H_
#define MODULES_UART_LOG_UART_LOG_H_

typedef enum {
    uart_inti = 0,
    uart_active = 1,
    uart_error = 4
} Uart_log_state_e;

typedef struct __attribute__ ((packed)) {
    uint8_t S; //the start bit, default = 0x53
    uint8_t key; //tx default: from 0 to 15, rx no default
    int32_t value;
} Tx_data;

//rx data has a similar structure as DS4_status_t in ds4.h
//providing basic operation in using ps4 controller
//typedef struct __attribute__ ((packed)) {
//    uint8_t hat_left_x;
//    uint8_t hat_left_y;
//    uint8_t hat_right_x;
//    uint8_t hat_right_y;
//
//    uint8_t triangle :1;
//    uint8_t circle :1;
//    uint8_t cross :1;
//    uint8_t square :1;
//    uint8_t dpad_code :4;
//
//    uint8_t tpad_click :1;
//    uint8_t ps :1;
//    uint8_t r3 :1;
//    uint8_t l3 :1;
//    uint8_t r2 :1;
//    uint8_t l2 :1;
//    uint8_t r1 :1;
//    uint8_t l1 :1;
//
//    uint8_t l2_trigger;
//    uint8_t r2_trigger;
//
//    uint8_t tpad_x;
//    uint8_t tpad_y;
//
//    uint8_t commands:6;
//    uint8_t share:1;
//    uint8_t options:1;
//
//    float roll;
//    float pitch;
//    float weight_L;
//    float weight_R;
//    float distance;
//} Rx_data_ps4;

typedef struct __attribute__ ((packed)) {
    uint8_t hat_left_x;
    uint8_t hat_left_y;
    uint8_t hat_right_x;
    uint8_t hat_right_y;

    uint8_t triangle;
    uint8_t circle;
    uint8_t cross;
    uint8_t square;
    uint8_t dpad_code;

    uint8_t tpad_click;
    uint8_t ps;
    uint8_t r3;
    uint8_t l3;
    uint8_t r2;
    uint8_t l2;
    uint8_t r1;
    uint8_t l1;

    uint8_t l2_trigger;
    uint8_t r2_trigger;

    uint8_t tpad_x;
    uint8_t tpad_y;

    uint8_t commands;
    uint8_t share;
    uint8_t options;
} Rx_data_ps4;

typedef struct __attribute__ ((packed)) {
   float roll;
   float pitch;
   float weight_L;
   float weight_R;
   float distance;
} Rx_data;

typedef struct __attribute__ ((packed)) {
    Rx_data_ps4 rx;
    Tx_data tx[16]; //sending 16 data set out for apps interface
    Uart_log_state_e state;
} Uart_log;

extern Uart_log uart_log;
void uart_log_init(void);

#endif
