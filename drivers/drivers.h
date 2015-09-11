#ifndef DRIVERS_H
#define DRIVERS_H

#include "hal.h"
#include "drivers_conf.h"
#include "stm32_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32_ltdc.h"
#include "qei.h"
#include "sdram_driver.h"

#ifdef __cplusplus
extern "C" {
#endif
  void driversInit(void);
#ifdef __cplusplus
}
#endif

#endif
