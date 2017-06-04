/*
 * distancesensor.c
 *
 *  Created on: 3 Mar, 2017
 *      Author: Lau
 */


/*
 *  Distance.c
 *  Proximity sensor range: ~ 3cm to 2m
 *  4 bytes data: S - 1st byte - 2nd byte - E
 *  Created on: Feb 3, 2017
 *      Author: Paul
 */

#include "ch.h"
#include "hal.h"
#include "distancesensor.h"
#include <string.h>

uint8_t distance_received = 0;
uint8_t rx_buffer[4];
uint16_t temp;
DistanceSensor dSensor;

static void rxend3(UARTDriver *uartp) {
    (void)uartp;
    uint8_t i;
    switch(dSensor.rx_state){
    case distance_rx_init:
        dSensor.distance_mm  = rx_buffer[2] << 8;
        dSensor.distance_mm += rx_buffer[1];
        dSensor.rx_state = distance_rx_active;
        dSensor.error_rapid = 0;
        break;
    case distance_rx_active:
        temp  = rx_buffer[2] << 8;
        temp += rx_buffer[1];
        if ( abs(dSensor.distance_mm - temp) < dSensor.rate_constraint ){
            dSensor.distance_mm_pre = dSensor.distance_mm;
            dSensor.distance_mm = temp;
            dSensor.error_rapid = 0;
        } else  dSensor.error_rapid = 1;
        break;
    case distance_rx_error:
    default:
        dSensor.rx_state = distance_rx_error;
        break;
    }
    distance_received = 1; // buffer enable
}

static UARTConfig uart_cfg_3 = {NULL, NULL, rxend3, NULL, NULL, 115200UL, 0, 0, 0};

static THD_WORKING_AREA(waDistance, 256);
static THD_FUNCTION(distance, arg) {
    (void)arg;
    uartStart(&UARTD6, &uart_cfg_3);
    uartStopReceive(&UARTD6);
    uartStartReceive(&UARTD6, sizeof(uint32_t), &rx_buffer);
//    for(int i = dSensor.data_count-1; i > 1; i--) {
//    	dSensor.distance[i] = dSensor.distance[i-1];
//    }
//    dSensor.distance[0] = dSensor.distance_mm;
//    for (int i = 0; i < dSensor.data_count; i++) {
//    	dSensor.distance_smoothened += dSensor.distance[i] ;
//    }
//    dSensor.distance_smoothened;
    dSensor.rx_state = distance_rx_init;

    while (!chThdShouldTerminateX()) {
        if (distance_received == 1) {
            distance_received = 0;
            uartStopReceive(&UARTD6);
            uartStartReceive(&UARTD6, sizeof(uint32_t), &rx_buffer);
        }
        chThdSleepMilliseconds(5);
    }
    uartStopReceive(&UARTD6);
}

void distance_init(void){
	dSensor.data_count = 10;
    dSensor.rate_constraint = 100;
    chThdCreateStatic(waDistance, sizeof(waDistance), LOWPRIO, distance, NULL);
}
