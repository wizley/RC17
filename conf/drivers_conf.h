/*
 * drivers_conf.h
 *
 *  Created on: Jun 10, 2015
 *      Author: u564
 */

#ifndef _DRIVERS_CONF_H
#define _DRIVERS_CONF_H

/**
 * @brief   Enables the Drivers.
 */
#if !defined(DRIVER_USE_DAC) || defined(__DOXYGEN__)
#define DRIVER_USE_DAC              FALSE
#endif

/**
 * @brief   Enables the QEI subsystem.
 */
#if !defined(DRIVER_USE_QEI) || defined(__DOXYGEN__)
#define DRIVER_USE_QEI              TRUE
#endif

#if !defined(DRIVER_USE_EEPROM) || defined(__DOXYGEN__)
#define DRIVER_USE_EEPROM           TRUE
#endif

/*
 * QEI driver system settings.
 */
#define STM32_QEI_USE_TIM1                  FALSE
#define STM32_QEI_USE_TIM2                  FALSE
#define STM32_QEI_USE_TIM3                  FALSE
#define STM32_QEI_USE_TIM4                  TRUE
#define STM32_QEI_USE_TIM5                  FALSE
#define STM32_QEI_USE_TIM8                  FALSE

/*
 * EEPROM driver system settings.
 */
#define EEPROM_DRV_USE_25XX              TRUE
#define EEPROM_DRV_USE_24XX              FALSE

#endif /* _DRIVERS_CONF_H */
