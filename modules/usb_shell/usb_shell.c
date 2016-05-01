/*
 * usb_shell.c
 *
 *  Created on: Jun 20, 2015
 *      Author: u564
 */
#include "ch.h"
#include "drivers.h"
#include "usage.h"
//#include "usbcfg.h"
#include "usb_shell.h"
#include "shell.h"
#include "chprintf.h"

//#include "ps4.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static thread_t *shelltp = NULL;

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
  for (counter = 0; counter < SDRAM_SIZE; counter++)
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
  for (counter = 0; counter < SDRAM_SIZE; counter++)
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
  while ((counter < SDRAM_SIZE) && (uwReadwritestatus == 0))
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
  //  for (counter = 0; counter < SDRAM_SIZE; counter++)
  //  {
  //    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
  //  }

  /* Write data value to all SDRAM memory */
  for (counter = 0; counter < SDRAM_SIZE; counter++)
    {
      *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
    }

  chTMStopMeasurementX(&tm);
  uint32_t write_ms = RTC2MS(10000, tm.last);

  chTMStartMeasurementX(&tm);

  /* Read back SDRAM memory */
  counter = 0;
  while ((counter < SDRAM_SIZE))
    {
      ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);
      counter++;
    }

  chTMStopMeasurementX(&tm);
  uint32_t read_ms = RTC2MS(10000, tm.last);

  /* Read back SDRAM memory and check content correctness*/
  counter = 0;
  uwReadwritestatus = 0;
  while ((counter < SDRAM_SIZE) && (uwReadwritestatus == 0))
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

#include "usbh/dev/ds4.h"

void cmd_ds4(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  (void)argc;

  DS4_status_t data;

  USBHDS4Driver *const ds4p = &USBHDS4[0];
  usbhds4Start(ds4p);

  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
    if(DS4_ReadTimeOut(ds4p, &data, MS2ST(1000)))
      chprintf((BaseSequentialStream *) &SD2, "%5d %5d %5d\r",
                  data.hat_left_x,
                  data.r2_trigger,
                  data.cross
                  );
    else
      chprintf(chp, "RIP\r\n");
    chThdSleepMilliseconds(100);
  }
  chprintf(chp, "\r\n\nstopped\r\n");

}

#define _24LC02_SIZE_      256
//#define _24LC02_PAGESIZE_  8
#define _24LC024H_PAGESIZE_  16

void cmd_eeprom(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  (void)argc;

  I2CEepromFileStream file;

  static uint8_t buf[10] = {0};

  static I2CEepromFileConfig eepcfg = {
    0,
    _24LC02_SIZE_,
    _24LC02_SIZE_,
    _24LC024H_PAGESIZE_,
    MS2ST(5),
    &I2CD1,
    0b1010000,
    buf
  };

  I2CEepromFileOpen(&file, &eepcfg, EepromFindDevice("24XX"));

  eepfs_lseek(&file, 0);

  /* write test pattern */
  chprintf(chp, "Write test pattern to eeprom...\r\n");
  for(uint16_t i = 0; i < _24LC02_SIZE_; i++){
    if(EepromWriteByte((EepromFileStream *)&file, i) != 1){
      chprintf(chp, "WRITE FAILED\r\n");
    }
  }

  chThdSleepMilliseconds(100);

  eepfs_lseek(&file, 0);

  /* print stored data value */
  chprintf(chp, "\r\neeprom data\r\n");
  chprintf(chp, "ADDR 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
  for (uint16_t i = 0; i < _24LC02_SIZE_; i++) {
    if (i % 16 == 0)
      chprintf(chp, "\r\n  %02X ", i);
    uint8_t buf = EepromReadByte((EepromFileStream *) &file);
    chprintf(chp, "%02X ", buf);
  }

  eepfs_close((EepromFileStream *)&file);

  chprintf(chp, "\r\n");
}

void cmd_usage(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  (void)argc;

  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
    chprintf(chp, "%.2f\r\n", cpu_usage_get_recent());
    chThdSleepMilliseconds(300);
  }
}

static const ShellCommand commands[] = {
  {"write", cmd_write},
  {"check", cmd_check},
  {"erase", cmd_erase},
  {"selfrefresh", cmd_selfrefresh},
  {"normal", cmd_normal},
  {"debug", cmd_debug},
  //{"ps4", cmd_ps4},
  {"ds4", cmd_ds4},
  {"eeprom", cmd_eeprom},
  {"usage", cmd_usage},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD2,
  commands
};

void usb_shell_init(void){
  shellInit();
  /*
   * Initializes a serial-over-USB CDC driver.
   */
//  sduObjectInit(&SDU1);
}

void usb_shell_start(void){
//  sduStart(&SDU1, &serusbcfg);
  sdStart(&SD2, NULL);
}

void usb_shell_create(void){
  if(shelltp == NULL)
    shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                  "shell", NORMALPRIO + 1,
                                  shellThread, (void *)&shell_cfg1);
}

void usb_shell_wait(void){
  chThdWait(shelltp);
  shelltp = NULL;
}

bool usb_is_active(void){
//  return SDU1.config->usbp->state == USB_ACTIVE;
  return true;
}
