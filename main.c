#include "ch.h"
#include "hal.h"
#include "drivers.h"

#include "chprintf.h"
#include "shell.h"
#include "usbcfg.h"
#include "ps4.h"
#include "usb_shell.h"

#include "gfx.h"
//#include <stdio.h>
//#include <string.h>

#include "app.h"
#include "bubbles.h"

#define QEI_DRIVER              QEID4

//GEventMouse	ev;



/*
 * Erases the whole SDRAM bank.
 */
static void sdram_bulk_erase(void) {

  volatile uint8_t *p = (volatile uint8_t *)SDRAM_BANK_ADDR;
  volatile uint8_t *end = p + IS42S16400J_SIZE;
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
      //palClearPad(GPIOC, GPIOC_LED_R);
//	  palClearPad(GPIOB, GPIOB_TIM2_CH4);
//    gdispFillArea(0, 0, 800, 480, Blue);
      chThdSleepMilliseconds(400);
      //palSetPad(GPIOC, GPIOC_LED_R);
//      palSetPad(GPIOB, GPIOB_TIM2_CH4);
//      gdispFillArea(0, 0, 800, 480, Red);
      chThdSleepMilliseconds(400);
  }
}

/*
 * Green LED blinker thread, times are in milliseconds.
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

/*===========================================================================*/
/* QEI related.                                                              */
/*===========================================================================*/

static QEIConfig qeicfg = {
    QEI_MODE_QUADRATURE,
    QEI_BOTH_EDGES,
    QEI_DIRINV_FALSE,
};

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

/* Virtual serial port over USB.*/
SerialUSBDriver SDU1;


//static PWMConfig pwmcfg = {
//  16000000,                                    /* 60kHz PWM clock frequency.   */
//  4000,                                    /* Initial PWM period 1S.       */
//  NULL,
//  {
//   {PWM_OUTPUT_DISABLED, NULL},
//   {PWM_OUTPUT_DISABLED, NULL},
//   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
//   {PWM_OUTPUT_DISABLED, NULL}
//  },
//  0,
//  0
//};
//
//static void cmd_debug(BaseSequentialStream *chp, int argc, char *argv[]) {
//  (void)argv;
//  (void)argc;
//
//  pwmEnableChannel(&PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, atoi((char*)argv[0])));
//
//}

static const ShellCommand commands[] = {
    {"mem", cmd_mem},
    {"threads", cmd_threads},
    {"test", cmd_test},
    {"sdram", cmd_sdram},
    {"reset", cmd_reset},
    {"write", cmd_write},
    {"check", cmd_check},
    {"erase", cmd_erase},
    {"selfrefresh", cmd_selfrefresh},
    {"normal", cmd_normal},
    //{"debug", cmd_debug},
    {"ps4", cmd_ps4},
    {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SDU1,
    commands
};

/*===========================================================================*/
/* Initialization and main thread.                                           */
/*===========================================================================*/
/*
 * Application entry point.
 */
int main(void) {
  thread_t *shelltp = NULL;

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
   * Shell manager initialization.
   */
  shellInit();

  /*
   * Activates the ADC1 driver and the temperature sensor.
   */
//  adcStart(&ADCD1, NULL);
//  adcSTM32EnableTSVREFE();
//  /*
//   * Starts an ADC continuous conversion.
//   */
//  adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);


  //pwmStart(&PWMD3, &pwmcfg);
  //pwmEnableChannel(&PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 5000));

//  buzzer_init();

  //#if HAL_USE_SERIAL_USB
  /*
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);



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
  qeiStart(&QEI_DRIVER, &qeicfg);
  qeiEnable(&QEI_DRIVER);

//  buzzer_init();

//  buzzer_tone_t tone[3] = {
//    {4000, 150},
//	{0, 150},
//	{0, 0}
//  };
  //buzzer_play(tone, 3);
//  chThdSleepMilliseconds(1500);
//  buzzer_stop();
//  buzzer_play(tone, 6);

  gfxInit();

  /*
   * Creating the blinker threads.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), LOWPRIO,
                    Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), LOWPRIO,
                    Thread2, NULL);

//  chThdCreateStatic(wabubbles, sizeof(wabubbles), LOWPRIO, bubbles_thread, NULL);

  app_init();

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
      if (!shelltp) {
		  if (SDU1.config->usbp->state == USB_ACTIVE) {
			  /* Spawns a new shell.*/
			  shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, LOWPRIO);
		  }
      }
      else {
		  /* If the previous shell exited.*/
		  if (chThdTerminatedX(shelltp)) {
			  /* Recovers memory of the previous shell.*/
			  chThdRelease(shelltp);
			  shelltp = NULL;
		  }
      }
      chThdSleepMilliseconds(200);
  }
}
