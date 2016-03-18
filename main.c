#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "gfx.h"
#include "usbcfg.h"
#include "usb_shell.h"
#include "app.h"


/*
 * Erases the whole SDRAM bank.
 */
static void sdram_bulk_erase(void) {

  volatile uint8_t *p = (volatile uint8_t *)SDRAM_BANK_ADDR;
  volatile uint8_t *end = p + SDRAM_SIZE;
  while (p < end)
    *p++ = 0xff;
}

/*
 * Red LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker1");
  while (TRUE) {
    palClearPad(GPIOC, GPIOC_LED_R);
    chThdSleepMilliseconds(400);
    palSetPad(GPIOC, GPIOC_LED_R);
    chThdSleepMilliseconds(400);
  }
}

/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {

  (void)arg;
  chRegSetThreadName("blinker2");
  while (TRUE) {
    palClearPad(GPIOC, GPIOC_LED_B);
    chThdSleepMilliseconds(333);
    palSetPad(GPIOC, GPIOC_LED_B);
    chThdSleepMilliseconds(800);
  }
}

static QEIConfig qeicfg = {
  QEI_MODE_QUADRATURE,
  QEI_BOTH_EDGES,
  QEI_DIRINV_FALSE,
};


/*===========================================================================*/
/* Initialization and main thread.                                           */
/*===========================================================================*/
/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  driversInit();

  palClearPad(GPIOD, GPIOD_LCD_DISP);
  palClearPad(GPIOI, GPIOI_LCD_BLCTRL);

  sdram_bulk_erase();

  /*
   * Activates the LCD-related drivers.
   */
  palSetPad(GPIOD, GPIOD_LCD_DISP);
  palSetPad(GPIOI, GPIOI_LCD_BLCTRL);

  palSetPadMode(GPIOB, GPIOB_TIM2_CH4, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOB, GPIOB_TIM2_CH4);

  /*
   * Activates the QEI driver.
   */
  qeiStart(&QEID4, &qeicfg);
  qeiEnable(&QEID4);

  gfxInit();

  /*
   * Creating the blinker threads.
   */
//  chThdCreateStatic(waThread1, sizeof(waThread1), LOWPRIO,
//                    Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), LOWPRIO,
                    Thread2, NULL);

  app_init();

  /*
   * Shell manager initialization.
   */
  usb_shell_init();
  usb_shell_start();

  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1000);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /*
   * Normal main() thread activity, in this demo it just performs
   * a shell respawn upon its termination.
   */
  while (TRUE) {
    if (SDU1.config->usbp->state == USB_ACTIVE) {
      usb_shell_create();
      usb_shell_wait();               /* Waiting termination.             */
    }
    chThdSleepMilliseconds(1000);
  }
}
