/*
 * ARTracker.c
 *
 *  Created on: May 30, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "ARTracker.h"
#include <string.h>

volatile ARTracker_status_t ARTracker_status, dummy;
int tracker_received = 0;

static void rxend2(UARTDriver *uartp) {
  (void)uartp;
  tracker_received++;

  palClearPad(GPIOC, GPIOC_LED_R);
}

bool check_tracker_data(ARTracker_status_t * a) {

if (a->anglex <= 40.0 && a->anglex >= -40.0 && a->d == 'D')
  {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uart_cfg_2 = {NULL, NULL, rxend2, NULL, NULL, 115200UL, 0, 0,
                                0};

static THD_WORKING_AREA(waTracker, 512);
static THD_FUNCTION(tracker,arg) {
  (void)arg;
  //uartStart(&UARTD6, &uart_cfg_2);
  //uartStopReceive(&UARTD6);
  //uartStartReceive(&UARTD6, sizeof(ARTracker_status), &ARTracker_status);

  while (!chThdShouldTerminateX()) {
//    if (sdAsynchronousRead(&SD2, &dummy, sizeof(dummy))
//        == sizeof(ARTracker_status)) {
    if (sdReadTimeout(&SD2, &dummy, sizeof(dummy), MS2ST(100)) == sizeof(dummy)){
      //if (check_tracker_data(&dummy)) {
        //memcpy ( &ARTracker_status, &dummy, sizeof(dummy));
        ARTracker_status.d = dummy.d;
        if (dummy.d=='D') {
          ARTracker_status.anglex = dummy.anglex;
          ARTracker_status.angley = -dummy.angley;
          ARTracker_status.distance = dummy.distance;
          ARTracker_status.pitch = -dummy.pitch;
        }
        else{
          ARTracker_status.anglex = 0;
          ARTracker_status.angley = 0;
          ARTracker_status.distance = 0;
          ARTracker_status.pitch = 0;
        }

      //}
    }
    chThdSleepMilliseconds(70);
  }
  //uartStopReceive(&UARTD6);
}

void artracker_init(void) {
  sdStart(&SD2, NULL);
  chThdCreateStatic(waTracker, sizeof(waTracker), LOWPRIO, tracker, NULL);
}

