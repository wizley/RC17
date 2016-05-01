#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "gfx.h"
//#include "usbcfg.h"
#include "usb_shell.h"
#include "app.h"
#include "driving.h"
#include "usage.h"

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


static THD_WORKING_AREA(waUSBHOST, 1024);
static THD_FUNCTION(USBHOST, arg) {

  (void)arg;
  chRegSetThreadName("USB Host Thread");
  while (TRUE) {
    usbhMainLoop(&USBHD2);
    chThdSleepMilliseconds(100);
  }
}

#include "usbh/dev/ds4.h"
#include "chprintf.h"

static THD_WORKING_AREA(waDS4, 1024);
static THD_FUNCTION(DS4, arg) {

  (void)arg;
  chRegSetThreadName("DS4 Thread");

  DS4_status_t data;
  DS4_command_t cmd = {0};
  cmd.led_r = 255;
  cmd.led_g = 20;
  cmd.led_b = 147;

  USBHDS4Driver *const ds4p = &USBHDS4[0];

#if USBHDS4_DEBUG_ENABLE_INFO
  chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "Waiting for connection...\r\n");
#endif

  while (TRUE) {
    switch (ds4p->state) {
    case USBHDS4_STATE_UNINIT:
    case USBHDS4_STATE_STOP:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD,
          "DS4 Disconnected or Stopped.\r\n");
#endif
      chThdSleepMilliseconds(500);
      break;
    case USBHDS4_STATE_ACTIVE:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 started.\r\n");
#endif
      usbhds4Start(ds4p);
      chThdSleepMilliseconds(20);
      DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      chThdSleepMilliseconds(500);
      break;
    case USBHDS4_STATE_READY:
      if (DS4_ReadTimeOut(ds4p, &data, MS2ST(50))){
//        chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "%5d %5d %5d\r",
//            data.hat_left_x,
//            data.r2_trigger,
//            data.cross
//            );
      }else{
#if USBHDS4_DEBUG_ENABLE_INFO
        chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 Read Timeout\r\n");
#endif
      }
//      cmd.led_r = data.l2_trigger;
//      cmd.led_g = data.r2_trigger;
//      if(data.cross)
//        DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      chThdSleepMilliseconds(10);
    }
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

  ActivateDriving();

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
//  usbDisconnectBus(serusbcfg.usbp);
//  chThdSleepMilliseconds(1000);
//  usbStart(serusbcfg.usbp, &usbcfg);
//  usbConnectBus(serusbcfg.usbp);
  usbhStart(&USBHD2);

  chThdCreateStatic(waUSBHOST, sizeof(waUSBHOST), NORMALPRIO,
                      USBHOST, NULL);

  usbhds4ObjectInit(&USBHDS4[0]);
  chThdCreateStatic(waDS4, sizeof(waDS4), NORMALPRIO,
                        DS4, NULL);

  /*
   * Normal main() thread activity, in this demo it just performs
   * a shell respawn upon its termination.
   */
  while (TRUE) {
    if (usb_is_active()) {
      usb_shell_create();
      usb_shell_wait();               /* Waiting termination.             */
    }
    chThdSleepMilliseconds(1000);
  }
}
