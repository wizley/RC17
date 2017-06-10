/*
 *  uart_log.c
 *  Created on: March 8, 2017
 *      Author: Paul
 */

#include "ch.h"
#include "hal.h"
#include "uart_log.h"

Uart_log uart_log;
uint8_t uart_log_received = 0;
uint8_t uart_log_sent = 0;

void uart_log_rxend(UARTDriver *uartp) {
    (void)uartp;
    uart_log_received = 1;
}

void uart_log_txend(UARTDriver *uartp) {
    (void)uartp;
    uart_log_sent = 1;
}

UARTConfig ulog_uart_cfg = {
        NULL,
        uart_log_txend,
        uart_log_rxend,
        NULL,
        NULL,
        115200UL,
        0,
        0,
        0
};

static THD_WORKING_AREA(uart_log_wa, 256);
static THD_FUNCTION(uart_log_process, arg) {
    (void)arg;

    uart_log.state = uart_inti;
    uartStart(&UARTD6, &ulog_uart_cfg);
    uartStopReceive(&UARTD6);
    uartStopSend(&UARTD6);
    uartStartReceive(&UARTD6, sizeof(Rx_data_ps4), &uart_log.rx);
    uartStartSend(&UARTD6, sizeof(Tx_data)*16, &uart_log.tx);
    uart_log.state = uart_active;

    while (!chThdShouldTerminateX()) {
        if (uart_log_received == 1) {
            uart_log_received = 0;
            uartStopReceive(&UARTD6);
            uartStartReceive(&UARTD6, sizeof(Rx_data_ps4), &uart_log.rx);
        }
        if (uart_log_sent == 1) {
            uart_log_sent = 0;
            uartStopSend(&UARTD6);
            uartStartSend(&UARTD6, sizeof(Tx_data)*16, &uart_log.tx);
        }
        chThdSleepMilliseconds(8);
    }
    uartStopReceive(&UARTD6);
}

void uart_log_init(void){
    chThdCreateStatic(uart_log_wa, sizeof(uart_log_wa), NORMALPRIO, uart_log_process, NULL);
    for (int i=0 ; i<16 ; i++)  {
        uart_log.tx[i].S = 0x53; //setting all tx start bit to 0x53
        uart_log.tx[i].key = i;   //setting all key according to the index
        uart_log.tx[i].value = 0;
    }
}
