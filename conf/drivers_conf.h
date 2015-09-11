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

#if !defined(DRIVER_USE_LTDC) || defined(__DOXYGEN__)
#define DRIVER_USE_LTDC             TRUE
#endif

#if !defined(DRIVER_USE_DMA2D) || defined(__DOXYGEN__)
#define DRIVER_USE_DMA2D            TRUE
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
 * LTDC driver system settings.
 */
#define STM32_SAISRC_NOCLOCK    (0 << 23)   /**< No clock.                  */
#define STM32_SAISRC_PLL        (1 << 23)   /**< SAI_CKIN is PLL.           */
#define STM32_SAIR_DIV2         (0 << 16)   /**< R divided by 2.            */
#define STM32_SAIR_DIV4         (1 << 16)   /**< R divided by 4.            */
#define STM32_SAIR_DIV8         (2 << 16)   /**< R divided by 8.            */
#define STM32_SAIR_DIV16        (3 << 16)   /**< R divided by 16.           */

#define STM32_SAISRC                        STM32_SAISRC_PLL
#define STM32_PLLSAIN_VALUE                 250
#define STM32_PLLSAIQ_VALUE                 7
#define STM32_PLLSAIR_VALUE                 2
#define STM32_PLLSAIR_POST                  STM32_SAIR_DIV4

/*
* PLLSAI enable check.
*/
#if (STM32_SAISRC == STM32_SAISRC_PLL) || defined(__DOXYGEN__)
/**
* @brief   PLL activation flag.
*/
#define STM32_ACTIVATE_PLLSAI       TRUE
#else
#define STM32_ACTIVATE_PLLSAI       FALSE
#endif

/**
* @brief   STM32_PLLSAIN field.
*/
#if ((STM32_PLLSAIN_VALUE >= 49) && (STM32_PLLSAIN_VALUE <= 432)) ||       \
  defined(__DOXYGEN__)
#define STM32_PLLSAIN               (STM32_PLLSAIN_VALUE << 6)
#else
#error "invalid STM32_PLLSAIN_VALUE value specified"
#endif

/**
* @brief   STM32_PLLSAIQ field.
*/
#if ((STM32_PLLSAIQ_VALUE >= 2) && (STM32_PLLSAIQ_VALUE <= 15)) ||           \
  defined(__DOXYGEN__)
#define STM32_PLLSAIQ               (STM32_PLLSAIQ_VALUE << 24)
#else
#error "invalid STM32_PLLSAIR_VALUE value specified"
#endif

/**
* @brief   STM32_PLLSAIR field.
*/
#if ((STM32_PLLSAIR_VALUE >= 2) && (STM32_PLLSAIR_VALUE <= 7)) ||           \
  defined(__DOXYGEN__)
#define STM32_PLLSAIR               (STM32_PLLSAIR_VALUE << 28)
#else
#error "invalid STM32_PLLSAIR_VALUE value specified"
#endif
//#define STM32_LTDC_USE_LTDC                 TRUE
#define STM32_LTDC_EV_IRQ_PRIORITY          11
#define STM32_LTDC_ER_IRQ_PRIORITY          11

/*
 * DMA2D driver system settings.
 */
//#define STM32_DMA2D_USE_DMA2D               TRUE
#define STM32_DMA2D_IRQ_PRIORITY            11

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
