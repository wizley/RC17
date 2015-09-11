/*
 * drivers.c
 *
 *  Created on: Jun 10, 2015
 *      Author: u564
 */

#include "drivers.h"

void driversInit(void)
{
#if defined(DRIVER_USE_DAC) && DRIVER_USE_DAC
  dacInit();
#endif

#if defined(DRIVER_USE_LTDC) && DRIVER_USE_LTDC
  ltdcInit();
#endif

#if defined(DRIVER_USE_DMA2D) && DRIVER_USE_DMA2D
  dma2dInit();
#endif

#if defined(DRIVER_USE_QEI) && DRIVER_USE_QEI
  qeiInit();
#endif

  SDRAM_Init();
}
