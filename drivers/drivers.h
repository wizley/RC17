//<<<<<< HEAD
#ifndef DRIVERS_H
#define DRIVERS_H

#include "hardware_conf.h"
#include "hal.h"
#include "drivers_conf.h"
#if BOARD_VERSION == 1
#include "stm32f4xx_fmc.h"
#elif BOARD_VERSION == 2
#include "stm32f746xx_fmc.h"
#endif
#include "qei.h"
#include "sdram_driver.h"
#include "crc.h"
#include "usbh.h"
#include "eeprom_driver.h"
#include "eeprom_format.h"

#ifdef __cplusplus
extern "C" {
#endif
  void driversInit(void);
#ifdef __cplusplus
}
#endif

#endif
//=======
//#ifndef DRIVERS_H
//#define DRIVERS_H
//
//#include "hal.h"
//#include "drivers_conf.h"
//#include "stm32f4xx_fmc.h"
//#include "qei.h"
//#include "sdram_driver.h"
//#include "crc.h"
//#include "usbh.h"
//#include "eeprom_driver.h"
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//  void driversInit(void);
//#ifdef __cplusplus
//}
//#endif
//
//#endif
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
