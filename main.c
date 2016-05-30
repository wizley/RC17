
#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "gfx.h"
#include "rtt_shell.h"
#include "app.h"
#include "analog.h"
#include "ps4_usbhost.h"
#include "driving.h"
#include "usage.h"
#include "ARTracker.h"

#define SDRAM_SIZE  0x1000000
/*
 * Erases the whole SDRAM bank.
 */
static void sdram_bulk_erase(void) {

  volatile uint8_t *p = (volatile uint8_t *)SDRAM_BANK_ADDR;
  volatile uint8_t *end = p + SDRAM_SIZE;
  while (p < end)
    *p++ = 0x0;
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

/*
 * I2C1 config.
 */
static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

static gdispImage myImage;


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
//  palSetPad(GPIOI, GPIOI_LCD_BLCTRL);

  palSetPadMode(GPIOB, GPIOB_TIM2_CH4, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOB, GPIOB_TIM2_CH4);

  /*
   * Activates the QEI driver.
   */
  qeiStart(&QEID4, &qeicfg);
  qeiEnable(&QEID4);

  i2cStart(&I2CD1, &i2cfg1);

  gfxInit();

  gdispImageOpenFile(&myImage, "m2logo.gif");
  gdispImageCache(&myImage);
  gdispImageDraw(&myImage, 40, 180, myImage.width, myImage.height, 0, 0);
  gdispImageClose(&myImage);

  chThdSleepMilliseconds(1000);

  /*
   * Creating the blinker threads.
   */
//  chThdCreateStatic(waThread1, sizeof(waThread1), LOWPRIO,
//                    Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), LOWPRIO,
                    Thread2, NULL);

  app_init();
  cpu_usage_init();

  /*
   * Shell manager initialization.
   */
  rtt_shell_init();
  rtt_shell_start();

  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
//  usbDisconnectBus(serusbcfg.usbp);
//  chThdSleepMilliseconds(1000);
//  usbStart(serusbcfg.usbp, &usbcfg);
//  usbConnectBus(serusbcfg.usbp);
  adc_init();
  ps4_usbhost_init();
  ActivateDriving();
  artracker_init();

  /*
   * Normal main() thread activity, in this demo it just performs
   * a shell respawn upon its termination.
   */
  while (TRUE) {
    if (rtt_is_active()) {
      rtt_shell_create();
      rtt_shell_wait();               /* Waiting termination.             */
    }
    chThdSleepMilliseconds(1000);
  }
}
