/*
 * ps4.c
 *
 *  Created on: Jun 21, 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ps4.h"

PS4_status_t ps4_status1, ps4_status2;

uint8_t ps4_received1 = 0;
uint8_t ps4_received2 = 0;

static void rxend6(UARTDriver *uartp) {
  (void)uartp;
  ps4_received1 = 1;
}

static void rxend2(UARTDriver *uartp) {
  (void)uartp;
  ps4_received2 = 1;
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uart_cfg_6 = {
  NULL,
  NULL,
  rxend6,
  NULL,
  NULL,
  115200UL,
  0,
  0,
  0
};

static UARTConfig uart_cfg_2 = {
  NULL,
  NULL,
  rxend2,
  NULL,
  NULL,
  115200UL,
  0,
  0,
  0
};

void cmd_ps4(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;
	(void)argc;
	uartStart(&UARTD6, &uart_cfg_6);
	uartStopReceive(&UARTD6);
	uartStartReceive(&UARTD6, sizeof(ps4_status1), &ps4_status1);
	uartStart(&UARTD2, &uart_cfg_2);
	uartStopReceive(&UARTD2);
	uartStartReceive(&UARTD2, sizeof(ps4_status2), &ps4_status2);
	while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
		if (ps4_received1 == 1) {
			chprintf(chp, "1 %d %d %d %d %f\r\n", ps4_status1.cross, ps4_status1.l2, ps4_status1.down, ps4_status1.finger0_x, ps4_status1.pitch);
			ps4_received1 = 0;
			uartStopReceive(&UARTD6);
			uartStartReceive(&UARTD6, sizeof(ps4_status1), &ps4_status1);
		}
		if (ps4_received2 == 1) {
			chprintf(chp, "2 %d %d %d %d %f\r\n", ps4_status2.cross, ps4_status2.l2, ps4_status2.down, ps4_status2.finger0_x, ps4_status2.pitch);
			ps4_received2 = 0;
			uartStopReceive(&UARTD2);
			uartStartReceive(&UARTD2, sizeof(ps4_status2), &ps4_status2);
		}
	}
	uartStopReceive(&UARTD6);
	uartStopReceive(&UARTD2);
}
