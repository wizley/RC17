//<<<<<<< HEAD
///*
// * ARTracker.c
// *
// *  Created on: May 30, 2016
// *      Author: Melvin
// */
//#include "ch.h"
//#include "hal.h"
//#include "ARTracker.h"
//
//ARTracker_status_t ARTracker_status;
//int tracker_received = 0;
//
//static void rxend2(UARTDriver *uartp) {
//  (void)uartp;
//  tracker_received++;
//}
//
//bool check_tracker_data(ARTracker_status_t * a){
//     if (a->a == 'A' && a->angle <= 40.0 && a->angle >= -40.0){
//       return TRUE;
//     }else{
//       return FALSE;
//     }
//}
//
///*
// * UART driver configuration structure.
// */
//static UARTConfig uart_cfg_2 = {
//  NULL,
//  NULL,
//  rxend2,
//  NULL,
//  NULL,
//  115200UL,
//  0,
//  0,
//  0
//};
//
//static THD_WORKING_AREA(waTracker, 512);
//static THD_FUNCTION(tracker,arg) {
//    (void)arg;
//    uartStart(&UARTD6, &uart_cfg_2);
//    uartStopReceive(&UARTD6);
//    uartStartReceive(&UARTD6, sizeof(ARTracker_status), &ARTracker_status);
//
//    while (!chThdShouldTerminateX()) {
//        if (tracker_received == 1) {
//            tracker_received = 0;
//            uartStopReceive(&UARTD6);
//            uartStartReceive(&UARTD6, sizeof(ARTracker_status), &ARTracker_status);
//        }
//        chThdSleepMilliseconds(70);
//    }
//    uartStopReceive(&UARTD6);
//}
//
//void artracker_init(void){
//  chThdCreateStatic(waTracker, sizeof(waTracker), LOWPRIO, tracker, NULL);
//}
//
//
//=======
/*
 * ARTracker.c
 *
 *  Created on: May 30, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "ARTracker.h"

ARTracker_status_t ARTracker_status;
int tracker_received = 0;

static void rxend2(UARTDriver *uartp) {
  (void)uartp;
  tracker_received++;
}

bool check_tracker_data(ARTracker_status_t * a){
     if (a->a == 'A' && a->angle <= 40.0 && a->angle >= -40.0){
       return TRUE;
     }else{
       return FALSE;
     }
}

/*
 * UART driver configuration structure.
 */
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

static THD_WORKING_AREA(waTracker, 512);
static THD_FUNCTION(tracker,arg) {
    (void)arg;
    uartStart(&UARTD6, &uart_cfg_2);
    uartStopReceive(&UARTD6);
    uartStartReceive(&UARTD6, sizeof(ARTracker_status), &ARTracker_status);

    while (!chThdShouldTerminateX()) {
        if (tracker_received == 1) {
            tracker_received = 0;
            uartStopReceive(&UARTD6);
            uartStartReceive(&UARTD6, sizeof(ARTracker_status), &ARTracker_status);
        }
        chThdSleepMilliseconds(70);
    }
    uartStopReceive(&UARTD6);
}

void artracker_init(void){
  chThdCreateStatic(waTracker, sizeof(waTracker), LOWPRIO, tracker, NULL);
}


//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
