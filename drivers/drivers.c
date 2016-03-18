/*
 * drivers.c
 *
 *  Created on: Jun 10, 2015
 *      Author: u564
 */

#include "drivers.h"

void driversInit(void) {
#if defined(DRIVER_USE_DAC) && DRIVER_USE_DAC
  dacInit();
#endif

#if defined(DRIVER_USE_QEI) && DRIVER_USE_QEI
  qeiInit();
#endif

  SDRAM_Init();
}
