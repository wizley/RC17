//<<<<<<< HEAD
//
//#include "ch.h"
//#include "hal.h"
//#include "rtt_shell.h"
//#include "RTTchannel.h"
//#include "shell.h"
//#include "chprintf.h"
//
//#include "drivers.h"
//#include "usage.h"
//
//#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
//
//static thread_t *shelltp = NULL;
//
//
//void cmd_debug(BaseSequentialStream *chp, int argc, char *argv[]) {
//  (void)argv;
//  (void)argc;
//
//  uint16_t qei_old_count = qeiGetCount(&QEID4);
//
//  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
//    chprintf(chp, "%d %d %d\r\n", qeiGetCount(&QEID4) - qei_old_count, (int16_t)(qeiGetCount(&QEID4) - qei_old_count), qei_old_count);
//    qei_old_count = qeiGetCount(&QEID4);
//    chThdSleepMilliseconds(100);
//  }
//  chprintf(chp, "\r\n\nstopped\r\n");
//
//}
//
//#include "usbh/dev/ds4.h"
//
//void cmd_ds4(BaseSequentialStream *chp, int argc, char *argv[]) {
//  (void)argv;
//  (void)argc;
//
//  DS4_status_t data;
//
//  USBHDS4Driver *const ds4p = &USBHDS4[0];
//  usbhds4Start(ds4p);
//
//  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
//    if(DS4_ReadTimeOut(ds4p, &data, MS2ST(1000)))
//      chprintf((BaseSequentialStream *) chp, "%5d %5d %5d\r",
//                  data.hat_left_x,
//                  data.r2_trigger,
//                  data.cross
//                  );
//    else
//      chprintf(chp, "RIP\r\n");
//    chThdSleepMilliseconds(100);
//  }
//  chprintf(chp, "\r\n\nstopped\r\n");
//
//}
//
//
//
//void cmd_eeprom(BaseSequentialStream *chp, int argc, char *argv[]) {
//  (void)argv;
//  (void)argc;
//
//  I2CEepromFileStream file;
//
//  static uint8_t buf[10] = {0};
//
//  static I2CEepromFileConfig eepcfg = {
//    0,
//    _24LC02_SIZE_,
//    _24LC02_SIZE_,
//    _24LC024H_PAGESIZE_,
//    MS2ST(5),
//    &I2CD1,
//    0b1010000,
//    buf
//  };
//
//  I2CEepromFileOpen(&file, &eepcfg, EepromFindDevice("24XX"));
//
//  eepfs_lseek(&file, 0);
//
//  // write test pattern
//  chprintf(chp, "Write test pattern to eeprom...\r\n");
//  for(uint16_t i = 0; i < _24LC02_SIZE_; i++){
//    if(EepromWriteByte((EepromFileStream *)&file, i) != 1){
//      chprintf(chp, "WRITE FAILED\r\n");
//    }
//  }
//
//  chThdSleepMilliseconds(100);
//
//  eepfs_lseek(&file, 0);
//
//  // print stored data value
//  chprintf(chp, "\r\neeprom data\r\n");
//  chprintf(chp, "ADDR 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
//  for (uint16_t i = 0; i < _24LC02_SIZE_; i++) {
//    if (i % 16 == 0)
//      chprintf(chp, "\r\n  %02X ", i);
//    uint8_t buf = EepromReadByte((EepromFileStream *) &file);
//    chprintf(chp, "%02X ", buf);
//  }
//
//  eepfs_close((EepromFileStream *)&file);
//
//  chprintf(chp, "\r\n");
//
//}
//
//void cmd_usage(BaseSequentialStream *chp, int argc, char *argv[]) {
//  (void)argv;
//  (void)argc;
//
//  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
//    chprintf(chp, "%.2f\r\n", cpu_usage_get_recent());
//    chThdSleepMilliseconds(300);
//  }
//}
//
//static const ShellCommand commands[] = {
//  {"debug", cmd_debug},
//  //{"ps4", cmd_ps4},
//  {"ds4", cmd_ds4},
//  {"eeprom", cmd_eeprom},
//  {"usage", cmd_usage},
//  {NULL, NULL}
//};
//
//static const ShellConfig shell_cfg1 = {
//  (BaseSequentialStream *)&RTT_S0,
//  commands
//};
//
//void rtt_shell_init(void){
//  shellInit();
//  RTTchannelObjectInit(&RTT_S0);
//  /*
//   * Initializes a serial-over-USB CDC driver.
//   */
////  sduObjectInit(&SDU1);
//}
//
//void rtt_shell_start(void){
////  sduStart(&SDU1, &serusbcfg);
////  sdStart(&SD2, NULL);
//}
//
//void rtt_shell_create(void){
//  if(shelltp == NULL)
//    shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
//                                  "shell", NORMALPRIO+1,
//                                  shellThread, (void *)&shell_cfg1);
//}
//
//void rtt_shell_wait(void){
//  chThdWait(shelltp);
//  shelltp = NULL;
//}
//
//bool rtt_is_active(void){
////  return SDU1.config->usbp->state == USB_ACTIVE;
//  return true;
//}
//=======

#include "ch.h"
#include "hal.h"
#include "rtt_shell.h"
#include "RTTchannel.h"
#include "shell.h"
#include "chprintf.h"

#include "drivers.h"
#include "usage.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static thread_t *shelltp = NULL;


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
  {"debug", cmd_debug},
  //{"ps4", cmd_ps4},
  {"ds4", cmd_ds4},
  {"eeprom", cmd_eeprom},
  {"usage", cmd_usage},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&RTT_S0,
  commands
};

void rtt_shell_init(void){
  shellInit();
  RTTchannelObjectInit(&RTT_S0);
  /*
   * Initializes a serial-over-USB CDC driver.
   */
//  sduObjectInit(&SDU1);
}

void rtt_shell_start(void){
//  sduStart(&SDU1, &serusbcfg);
//  sdStart(&SD2, NULL);
}

void rtt_shell_create(void){
  if(shelltp == NULL)
    shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                  "shell", NORMALPRIO + 1,
                                  shellThread, (void *)&shell_cfg1);
}

void rtt_shell_wait(void){
  chThdWait(shelltp);
  shelltp = NULL;
}

bool rtt_is_active(void){
//  return SDU1.config->usbp->state == USB_ACTIVE;
  return true;
}
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
