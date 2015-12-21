/*
 * usb_shell.c
 *
 *  Created on: Jun 20, 2015
 *      Author: u564
 */
#include "ch.h"
#include "test.h"
#include "drivers.h"
#include "usbcfg.h"
#include "usb_shell.h"
#include "shell.h"
#include "chprintf.h"

#include "ps4.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

static thread_t *shelltp = NULL;

/* Virtual serial port over USB.*/
SerialUSBDriver SDU1;

void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: mem\r\n");
      return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreGetStatusX());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: threads\r\n");
      return;
  }
  chprintf(chp, "                     name    addr    stack prio refs     state time\r\n");
  tp = chRegFirstThread();
  do {
      chprintf(chp, "%25s %.8lx %.8lx %4lu %4lu %9s\r\n",
    		   tp->p_name,
               (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
               (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
               states[tp->p_state]);
      tp = chRegNextThread(tp);
  } while (tp != NULL);
}

void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: test\r\n");
      return;
  }
  tp = chThdCreateFromHeap(NULL, TEST_WA_SIZE, chThdGetPriorityX(),
                           TestThread, chp);
  if (tp == NULL) {
      chprintf(chp, "out of memory\r\n");
      return;
  }
  chThdWait(tp);
}

void cmd_reset(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: reset\r\n");
      return;
  }

  chprintf(chp, "Will reset in 200ms\r\n");
  chThdSleepMilliseconds(200);
  NVIC_SystemReset();
}

void cmd_write(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint32_t counter = 0;
  uint8_t ubWritedata_8b = 0x3C;
  uint32_t uwReadwritestatus = 0;
  time_measurement_t tm;


  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: write\r\n");
      return;
  }

  chTMObjectInit(&tm);

  chTMStartMeasurementX(&tm);

  /* Write data value to all SDRAM memory */
  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
    {
      *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
    }

  chTMStopMeasurementX(&tm);
  uint32_t write_ms = RTC2MS(10000, tm.last);

  if (!uwReadwritestatus) {
      chprintf(chp, "SDRAM written in %dms.\r\n", write_ms);
  }

}

void cmd_erase(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint32_t counter = 0;
  uint32_t uwReadwritestatus = 0;
  time_measurement_t tm;


  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: erase\r\n");
      return;
  }

  chTMObjectInit(&tm);

  //XXX tmStartMeasurement(&tm);

  /* Write data value to all SDRAM memory */
  /* Erase SDRAM memory */
  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
    {
      *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
    }

  //XXX tmStopMeasurement(&tm);
  uint32_t write_ms = 0;//XXX RTT2MS(tm.last);

  if (!uwReadwritestatus) {
      chprintf(chp, "SDRAM erased in %dms.\r\n", write_ms);
  }

}

void cmd_selfrefresh(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;

  if (argc > 0) {
      chprintf(chp, "Usage: selfrefresh\r\n");
      return;
  }

  /* Program a self-refresh mode command */
  FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_Selfrefresh;
  FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank1;
  FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;

  /* Send the command */
  FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

  /* Wait until the SDRAM controller is ready */
  while(FMC_GetFlagStatus(FMC_Bank1_SDRAM, FMC_FLAG_Busy) != RESET) {
  }

  /* Check the bank mode status */
  if(FMC_GetModeStatus(FMC_Bank1_SDRAM) != FMC_SelfRefreshMode_Status) {
      chprintf(chp, "SDRAM is not in self refresh mode, command FAILED.\r\n");
  } else {
      chprintf(chp, "SDRAM is in self refresh mode.\r\n");
  }

}

void cmd_normal(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;

  if (argc > 0) {
      chprintf(chp, "Usage: normal\r\n");
      return;
  }

  /* Program a self-refresh mode command */
  FMC_SDRAMCommandStructure.FMC_CommandMode = FMC_Command_Mode_normal;
  FMC_SDRAMCommandStructure.FMC_CommandTarget = FMC_Command_Target_bank1;
  FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;

  /* Send the command */
  FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

  /* Wait until the SDRAM controller is ready */
  while(FMC_GetFlagStatus(FMC_Bank1_SDRAM, FMC_FLAG_Busy) != RESET) {
  }

  /* Check the bank mode status */
  if(FMC_GetModeStatus(FMC_Bank1_SDRAM) != FMC_NormalMode_Status) {
      chprintf(chp, "SDRAM is not in normal mode, command FAILED.\r\n");
  } else {
      chprintf(chp, "SDRAM is in normal mode.\r\n");
  }

}

void cmd_check(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint32_t counter = 0;
  uint8_t ubWritedata_8b = 0x3C, ubReaddata_8b = 0;
  uint32_t uwReadwritestatus = 0;
  time_measurement_t tm;


  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: check\r\n");
      return;
  }

  chTMObjectInit(&tm);

  chTMStartMeasurementX(&tm);

  /* Read back SDRAM memory and check content correctness*/
  counter = 0;
  uwReadwritestatus = 0;
  while ((counter < IS42S16400J_SIZE) && (uwReadwritestatus == 0))
    {
      ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);
      if ( ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))
	{
	  uwReadwritestatus = 1;
	  chprintf(chp, "Error at %d, expected %d but read %d.\r\n", counter, ubWritedata_8b + counter, ubReaddata_8b);
	}
      counter++;
    }

  chTMStopMeasurementX(&tm);
  uint32_t check_ms = RTC2MS(10000, tm.last);

  //FIXME time this
  if (!uwReadwritestatus) {
      chprintf(chp, "SDRAM read and check completed successfully in %dms.\r\n", check_ms);
  }

}

void cmd_sdram(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint32_t counter = 0;
  uint8_t ubWritedata_8b = 0x3C, ubReaddata_8b = 0;
  uint32_t uwReadwritestatus = 0;
  time_measurement_t tm;


  (void)argv;
  if (argc > 0) {
      chprintf(chp, "Usage: sdram\r\n");
      return;
  }

  chTMObjectInit(&tm);

  chTMStartMeasurementX(&tm);

  //  /* Erase SDRAM memory */
  //  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
  //  {
  //    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
  //  }

  /* Write data value to all SDRAM memory */
  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
    {
      *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
    }

  chTMStopMeasurementX(&tm);
  uint32_t write_ms = RTC2MS(10000, tm.last);

  chTMStartMeasurementX(&tm);

  /* Read back SDRAM memory */
  counter = 0;
  while ((counter < IS42S16400J_SIZE))
    {
      ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);
      counter++;
    }

  chTMStopMeasurementX(&tm);
  uint32_t read_ms = RTC2MS(10000, tm.last);

  /* Read back SDRAM memory and check content correctness*/
  counter = 0;
  uwReadwritestatus = 0;
  while ((counter < IS42S16400J_SIZE) && (uwReadwritestatus == 0))
    {
      ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);
      if ( ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))
	{
	  uwReadwritestatus = 1;
	  chprintf(chp, "Error at %d, expected %d but read %d.\r\n", counter, ubWritedata_8b + counter, ubReaddata_8b);
	}
      counter++;
    }

  if (!uwReadwritestatus) {
      chprintf(chp, "SDRAM test completed successfully, writing entire memory took %dms, reading it took %dms.\r\n", write_ms, read_ms);
  }

}

void cmd_debug(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  (void)argc;

  uint16_t qei_old_count = qeiGetCount(&QEID4);

  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
    chprintf(chp, "%d %d %d\r\n", qeiGetCount(&QEID4) - qei_old_count, (int16_t)(qeiGetCount(&QEID4) - qei_old_count), qei_old_count);
    qei_old_count = qeiGetCount(&QEID4);
    chThdSleepMilliseconds(100);
  }
  chprintf(chp, "\r\n\nstopped\r\n");

}

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
  {"debug", cmd_debug},
  {"ps4", cmd_ps4},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

void usb_shell_init(void){
  shellInit();
  /*
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
}

void usb_shell_start(void){
  sduStart(&SDU1, &serusbcfg);
  if(shelltp == NULL)
    shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
}

void usb_shell_stop(void){
  chThdTerminate(shelltp);
  chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
  shelltp = NULL;           /* Triggers spawning of a new shell.        */
  shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
}

bool usb_shell_is_running(void){
  return chThdTerminatedX(shelltp);
}
