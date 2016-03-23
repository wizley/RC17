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
#define DRIVER_USE_DAC                  FALSE
#endif

/**
 * @brief   Enables the QEI subsystem.
 */
#if !defined(DRIVER_USE_QEI) || defined(__DOXYGEN__)
#define DRIVER_USE_QEI                  TRUE
#endif

#if !defined(DRIVER_USE_EEPROM) || defined(__DOXYGEN__)
#define DRIVER_USE_EEPROM               TRUE
#endif

#if !defined(DRIVER_USE_CRC) || defined(__DOXYGEN__)
#define DRIVER_USE_CRC                  FALSE
#endif

#if !defined(DRIVER_USE_USBH) || defined(__DOXYGEN__)
#define DRIVER_USE_USBH                 TRUE
#endif

/*
 * QEI driver system settings.
 */
#define STM32_QEI_USE_TIM1              FALSE
#define STM32_QEI_USE_TIM2              FALSE
#define STM32_QEI_USE_TIM3              FALSE
#define STM32_QEI_USE_TIM4              TRUE
#define STM32_QEI_USE_TIM5              FALSE
#define STM32_QEI_USE_TIM8              FALSE

/*
 * EEPROM driver system settings.
 */
#define EEPROM_DRV_USE_25XX             TRUE
#define EEPROM_DRV_USE_24XX             FALSE

/*
 * CRC driver system settings.
 */
#define STM32_CRC_USE_CRC1              TRUE
#define CRC_USE_DMA                     TRUE
#define CRC_USE_MUTUAL_EXCLUSION        TRUE
#define CRCSW_USE_CRC1                  FALSE
#define CRCSW_CRC32_TABLE               TRUE
#define CRCSW_CRC16_TABLE               TRUE
#define CRCSW_PROGRAMMABLE              TRUE
#define STM32_CRC_CRC1_DMA_PRIORITY     2
#define STM32_CRC_CRC1_DMA_IRQ_PRIORITY 2
#define STM32_CRC_CRC1_DMA_STREAM       STM32_DMA_STREAM_ID(1, 2)
#define STM32_CRC_DMA_ERROR_HOOK(crcp)  osalSysHalt("DMA failure")

/*===========================================================================*/
/* USBH driver related settings.                                         */
/*===========================================================================*/

/* main driver */
#define DRIVER_USBH_PORT_DEBOUNCE_TIME             200
#define DRIVER_USBH_PORT_RESET_TIMEOUT             500
#define DRIVER_USBH_DEVICE_ADDRESS_STABILIZATION   20

/* MSD */
#define DRIVER_USBH_USE_MSD                  FALSE

#define DRIVER_USBHMSD_MAX_LUNS              1
#define DRIVER_USBHMSD_MAX_INSTANCES         1

/* FTDI */
#define DRIVER_USBH_USE_FTDI                 FALSE

#define DRIVER_USBHFTDI_MAX_PORTS            1
#define DRIVER_USBHFTDI_MAX_INSTANCES        1
#define DRIVER_USBHFTDI_DEFAULT_SPEED        9600
#define DRIVER_USBHFTDI_DEFAULT_FRAMING      (USBHFTDI_FRAMING_DATABITS_8 | USBHFTDI_FRAMING_PARITY_NONE | USBHFTDI_FRAMING_STOP_BITS_1)
#define DRIVER_USBHFTDI_DEFAULT_HANDSHAKE    USBHFTDI_HANDSHAKE_NONE
#define DRIVER_USBHFTDI_DEFAULT_XON          0x11
#define DRIVER_USBHFTDI_DEFAULT_XOFF         0x13


/* IAD */
#define DRIVER_USBH_USE_IAD                  FALSE

/* UVC */
#define DRIVER_USBH_USE_UVC                  FALSE

#define DRIVER_USBHUVC_MAX_INSTANCES         1
#define DRIVER_USBHUVC_MAX_MAILBOX_SZ        70
#define DRIVER_USBHUVC_WORK_RAM_SIZE         20000
#define DRIVER_USBHUVC_STATUS_PACKETS_COUNT  10

/* DS4 */
#define DRIVER_USBH_USE_DS4                  TRUE
#define DRIVER_USBHDS4_MAX_INSTANCES         1

/* HUB */
#define DRIVER_USBH_USE_HUB                FALSE
#define DRIVER_USBHHUB_MAX_INSTANCES       1
#define DRIVER_USBHHUB_MAX_PORTS           6


/* debug */
#define USBH_DEBUG_ENABLE               TRUE
#define USBH_DEBUG_USBHD                USBHD2
#define USBH_DEBUG_SD                   SD2
#define USBH_DEBUG_BUFFER               25000

#define USBH_DEBUG_ENABLE_TRACE         FALSE
#define USBH_DEBUG_ENABLE_INFO          FALSE
#define USBH_DEBUG_ENABLE_WARNINGS      TRUE
#define USBH_DEBUG_ENABLE_ERRORS        TRUE

#define USBH_LLD_DEBUG_ENABLE_TRACE     FALSE
#define USBH_LLD_DEBUG_ENABLE_INFO      FALSE
#define USBH_LLD_DEBUG_ENABLE_WARNINGS  TRUE
#define USBH_LLD_DEBUG_ENABLE_ERRORS    TRUE

#define USBHHUB_DEBUG_ENABLE_TRACE      FALSE
#define USBHHUB_DEBUG_ENABLE_INFO       TRUE
#define USBHHUB_DEBUG_ENABLE_WARNINGS   TRUE
#define USBHHUB_DEBUG_ENABLE_ERRORS     TRUE

#define USBHMSD_DEBUG_ENABLE_TRACE      FALSE
#define USBHMSD_DEBUG_ENABLE_INFO       TRUE
#define USBHMSD_DEBUG_ENABLE_WARNINGS   TRUE
#define USBHMSD_DEBUG_ENABLE_ERRORS     TRUE

#define USBHUVC_DEBUG_ENABLE_TRACE      FALSE
#define USBHUVC_DEBUG_ENABLE_INFO       TRUE
#define USBHUVC_DEBUG_ENABLE_WARNINGS   TRUE
#define USBHUVC_DEBUG_ENABLE_ERRORS     TRUE

#define USBHFTDI_DEBUG_ENABLE_TRACE     FALSE
#define USBHFTDI_DEBUG_ENABLE_INFO      TRUE
#define USBHFTDI_DEBUG_ENABLE_WARNINGS  TRUE
#define USBHFTDI_DEBUG_ENABLE_ERRORS    TRUE

#define USBHDS4_DEBUG_ENABLE_TRACE     FALSE
#define USBHDS4_DEBUG_ENABLE_INFO      FALSE
#define USBHDS4_DEBUG_ENABLE_WARNINGS  TRUE
#define USBHDS4_DEBUG_ENABLE_ERRORS    TRUE

/*
 * USBH driver system settings.
 */

#define STM32_OTG1_CHANNELS_NUMBER    8
#define STM32_OTG2_CHANNELS_NUMBER    12

#define STM32_USBH_USE_OTG1         FALSE
#define STM32_OTG1_RXFIFO_SIZE      1024
#define STM32_OTG1_PTXFIFO_SIZE     128
#define STM32_OTG1_NPTXFIFO_SIZE    128

#define STM32_USBH_USE_OTG2         TRUE
#define STM32_OTG2_RXFIFO_SIZE      1024
#define STM32_OTG2_PTXFIFO_SIZE     128
#define STM32_OTG2_NPTXFIFO_SIZE    128

#define STM32_USBH_MIN_QSPACE       4
#define STM32_USBH_CHANNELS_NP      4

#endif /* _DRIVERS_CONF_H */
