/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for M2 Robocon STM32F746I MainBoard 2017 board.
 */

/*
 * Board identifier.
 */
#define BOARD_MB2017
#define BOARD_NAME                  "M2 Robocon STM32F746I MainBoard 2017"

/*
 * Ethernet PHY type.
 */
#define BOARD_PHY_ID                
#define BOARD_PHY_RMII

/*
 * The board has an ULPI USB PHY.
 */
//#define BOARD_OTG2_USES_ULPI

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F746xx

/*
 * IO pins assignments.
 */
#define GPIOA_ADC3_IN0              0U
#define GPIOA_ADC3_IN1              1U
#define GPIOA_ADC3_IN2              2U
#define GPIOA_ADC3_IN3              3U
#define GPIOA_DAC_OUT1              4U
#define GPIOA_ADC1_IN5              5U
#define GPIOA_ADC1_IN6              6U
#define GPIOA_ADC1_IN7              7U
#define GPIOA_TIM1_CH1              8U
#define GPIOA_TIM1_CH2              9U
#define GPIOA_TIM1_CH3              10U
#define GPIOA_TIM1_CH4              11U
#define GPIOA_T_IRQ                 12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_T_BUSY                15U

#define GPIOB_TIM3_CH3              0U
#define GPIOB_TIM3_CH4              1U
#define GPIOB_BUT2                  2U
#define GPIOB_SWO                   3U
#define GPIOB_TIM3_CH1              4U
#define GPIOB_TIM3_CH2              5U
#define GPIOB_USART1_TX             6U
#define GPIOB_USART1_RX             7U
#define GPIOB_I2C1_SCL              8U
#define GPIOB_I2C1_SDA              9U
#define GPIOB_TIM2_CH3              10U
#define GPIOB_TIM2_CH4              11U
#define GPIOB_PB12                  12U
#define GPIOB_OTG_HS_VBUS           13U
#define GPIOB_OTG_HS_DM             14U
#define GPIOB_OTG_HS_DP             15U

#define GPIOC_ADC3_IN10             0U
#define GPIOC_ADC3_IN11             1U
#define GPIOC_FMC_SDNE0             2U
#define GPIOC_FMC_SDCKE0            3U
#define GPIOC_ADC1_IN14             4U
#define GPIOC_ADC1_IN15             5U
#define GPIOC_BUT8                  6U
#define GPIOC_LCD_G6                7U
#define GPIOC_SDIO_D0               8U
#define GPIOC_SDIO_D1               9U
#define GPIOC_SDIO_D2               10U
#define GPIOC_SDIO_D3               11U
#define GPIOC_SDIO_CK               12U
#define GPIOC_LED_R                 13U
#define GPIOC_LED_G                 14U
#define GPIOC_LED_B                 15U

#define GPIOD_FMC_D2                0U
#define GPIOD_FMC_D3                1U
#define GPIOD_SDIO_CMD              2U
#define GPIOD_LCD_G7                3U
#define GPIOD_BUT7                  4U
#define GPIOD_USART2_TX             5U
#define GPIOD_USART2_RX             6U
#define GPIOD_LCD_DISP              7U
#define GPIOD_FMC_D13               8U
#define GPIOD_FMC_D14               9U
#define GPIOD_FMC_D15               10U
#define GPIOD_DIP                   11U
#define GPIOD_TIM4_CH1              12U
#define GPIOD_TIM4_CH2              13U
#define GPIOD_FMC_D0                14U
#define GPIOD_FMC_D1                15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_BUT4                  2U
#define GPIOE_BUT6                  3U
#define GPIOE_LCD_B0                4U
#define GPIOE_LCD_G0                5U
#define GPIOE_LCD_G1                6U
#define GPIOE_FMC_D4                7U
#define GPIOE_FMC_D5                8U
#define GPIOE_FMC_D6                9U
#define GPIOE_FMC_D7                10U
#define GPIOE_FMC_D8                11U
#define GPIOE_FMC_D9                12U
#define GPIOE_FMC_D10               13U
#define GPIOE_FMC_D11               14U
#define GPIOE_FMC_D12               15U

#define GPIOF_FMC_A0                0U
#define GPIOF_FMC_A1                1U
#define GPIOF_FMC_A2                2U
#define GPIOF_FMC_A3                3U
#define GPIOF_FMC_A4                4U
#define GPIOF_FMC_A5                5U
#define GPIOF_SPI5_CS               6U
#define GPIOF_SPI5_SCK              7U
#define GPIOF_SPI5_MISO             8U
#define GPIOF_SPI5_MOSI             9U
#define GPIOF_LCD_DE                10U
#define GPIOF_FMC_SDNRAS            11U
#define GPIOF_FMC_A6                12U
#define GPIOF_FMC_A7                13U
#define GPIOF_FMC_A8                14U
#define GPIOF_FMC_A9                15U

#define GPIOG_FMC_A10               0U
#define GPIOG_FMC_A11               1U
#define GPIOG_FMC_A12               2U
#define GPIOG_BUT3                  3U
#define GPIOG_FMC_BA0               4U
#define GPIOG_FMC_BA1               5U
#define GPIOG_LCD_R7                6U
#define GPIOG_LCD_CLK               7U
#define GPIOG_FMC_SDCLK             8U
#define GPIOG_USART6_RX             9U
#define GPIOG_LCD_B2                10U
#define GPIOG_LCD_B3                11U
#define GPIOG_LCD_B1                12U
#define GPIOG_USART1_EN             13U
#define GPIOG_USART6_TX             14U
#define GPIOG_FMC_SDNCAS            15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_LCD_R0                2U
#define GPIOH_LCD_R1                3U
#define GPIOH_BUT5                  4U
#define GPIOH_FMC_SDNWE             5U
#define GPIOH_TIM12_CH1             6U
#define GPIOH_BUT1                  7U
#define GPIOH_LCD_R2                8U
#define GPIOH_LCD_R3                9U
#define GPIOH_LCD_R4                10U
#define GPIOH_LCD_R5                11U
#define GPIOH_LCD_R6                12U
#define GPIOH_LCD_G2                13U
#define GPIOH_LCD_G3                14U
#define GPIOH_LCD_G4                15U

#define GPIOI_LCD_G5                0U
#define GPIOI_SPI2_SCK              1U
#define GPIOI_SPI2_MISO             2U
#define GPIOI_SPI2_MOSI             3U
#define GPIOI_LCD_B4                4U
#define GPIOI_LCD_B5                5U
#define GPIOI_LCD_B6                6U
#define GPIOI_LCD_B7                7U
#define GPIOI_LCD_BLCTRL            8U
#define GPIOI_LCD_VSYNC             9U
#define GPIOI_LCD_HSYNC             10U
#define GPIOI_SPI2_CS               11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

#define GPIOJ_PIN0                  0U
#define GPIOJ_PIN1                  1U
#define GPIOJ_PIN2                  2U
#define GPIOJ_PIN3                  3U
#define GPIOJ_PIN4                  4U
#define GPIOJ_PIN5                  5U
#define GPIOJ_PIN6                  6U
#define GPIOJ_PIN7                  7U
#define GPIOJ_PIN8                  8U
#define GPIOJ_PIN9                  9U
#define GPIOJ_PIN10                 10U
#define GPIOJ_PIN11                 11U
#define GPIOJ_PIN12                 12U
#define GPIOJ_PIN13                 13U
#define GPIOJ_PIN14                 14U
#define GPIOJ_PIN15                 15U

#define GPIOK_PIN0                  0U
#define GPIOK_PIN1                  1U
#define GPIOK_PIN2                  2U
#define GPIOK_PIN3                  3U
#define GPIOK_PIN4                  4U
#define GPIOK_PIN5                  5U
#define GPIOK_PIN6                  6U
#define GPIOK_PIN7                  7U
#define GPIOK_PIN8                  8U
#define GPIOK_PIN9                  9U
#define GPIOK_PIN10                 10U
#define GPIOK_PIN11                 11U
#define GPIOK_PIN12                 12U
#define GPIOK_PIN13                 13U
#define GPIOK_PIN14                 14U
#define GPIOK_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_ADC3_IN0               PAL_LINE(GPIOA, 0U)
#define LINE_ADC3_IN1               PAL_LINE(GPIOA, 1U)
#define LINE_ADC3_IN2               PAL_LINE(GPIOA, 2U)
#define LINE_ADC3_IN3               PAL_LINE(GPIOA, 3U)
#define LINE_DAC_OUT1               PAL_LINE(GPIOA, 4U)
#define LINE_ADC1_IN5               PAL_LINE(GPIOA, 5U)
#define LINE_ADC1_IN6               PAL_LINE(GPIOA, 6U)
#define LINE_ADC1_IN7               PAL_LINE(GPIOA, 7U)
#define LINE_TIM1_CH1               PAL_LINE(GPIOA, 8U)
#define LINE_TIM1_CH2               PAL_LINE(GPIOA, 9U)
#define LINE_TIM1_CH3               PAL_LINE(GPIOA, 10U)
#define LINE_TIM1_CH4               PAL_LINE(GPIOA, 11U)
#define LINE_T_IRQ                  PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_T_BUSY                 PAL_LINE(GPIOA, 15U)

#define LINE_TIM3_CH3               PAL_LINE(GPIOB, 0U)
#define LINE_TIM3_CH4               PAL_LINE(GPIOB, 1U)
#define LINE_BUT2                   PAL_LINE(GPIOB, 2U)
#define LINE_SWO                    PAL_LINE(GPIOB, 3U)
#define LINE_TIM3_CH1               PAL_LINE(GPIOB, 4U)
#define LINE_TIM3_CH2               PAL_LINE(GPIOB, 5U)
#define LINE_USART1_TX              PAL_LINE(GPIOB, 6U)
#define LINE_USART1_RX              PAL_LINE(GPIOB, 7U)
#define LINE_I2C1_SCL               PAL_LINE(GPIOB, 8U)
#define LINE_I2C1_SDA               PAL_LINE(GPIOB, 9U)
#define LINE_TIM2_CH3               PAL_LINE(GPIOB, 10U)
#define LINE_TIM2_CH4               PAL_LINE(GPIOB, 11U)
#define LINE_PB12                   PAL_LINE(GPIOB, 12U)
#define LINE_OTG_HS_VBUS            PAL_LINE(GPIOB, 13U)
#define LINE_OTG_HS_DM              PAL_LINE(GPIOB, 14U)
#define LINE_OTG_HS_DP              PAL_LINE(GPIOB, 15U)

#define LINE_ADC3_IN10              PAL_LINE(GPIOC, 0U)
#define LINE_ADC3_IN11              PAL_LINE(GPIOC, 1U)
#define LINE_FMC_SDNE0              PAL_LINE(GPIOC, 2U)
#define LINE_FMC_SDCKE0             PAL_LINE(GPIOC, 3U)
#define LINE_ADC1_IN14              PAL_LINE(GPIOC, 4U)
#define LINE_ADC1_IN15              PAL_LINE(GPIOC, 5U)
#define LINE_BUT8                   PAL_LINE(GPIOC, 6U)
#define LINE_LCD_G6                 PAL_LINE(GPIOC, 7U)
#define LINE_SDIO_D0                PAL_LINE(GPIOC, 8U)
#define LINE_SDIO_D1                PAL_LINE(GPIOC, 9U)
#define LINE_SDIO_D2                PAL_LINE(GPIOC, 10U)
#define LINE_SDIO_D3                PAL_LINE(GPIOC, 11U)
#define LINE_SDIO_CK                PAL_LINE(GPIOC, 12U)
#define LINE_LED_R                  PAL_LINE(GPIOC, 13U)
#define LINE_LED_G                  PAL_LINE(GPIOC, 14U)
#define LINE_LED_B                  PAL_LINE(GPIOC, 15U)

#define LINE_FMC_D2                 PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3                 PAL_LINE(GPIOD, 1U)
#define LINE_SDIO_CMD               PAL_LINE(GPIOD, 2U)
#define LINE_LCD_G7                 PAL_LINE(GPIOD, 3U)
#define LINE_BUT7                   PAL_LINE(GPIOD, 4U)
#define LINE_USART2_TX              PAL_LINE(GPIOD, 5U)
#define LINE_USART2_RX              PAL_LINE(GPIOD, 6U)
#define LINE_LCD_DISP               PAL_LINE(GPIOD, 7U)
#define LINE_FMC_D13                PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14                PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15                PAL_LINE(GPIOD, 10U)
#define LINE_DIP                    PAL_LINE(GPIOD, 11U)
#define LINE_TIM4_CH1               PAL_LINE(GPIOD, 12U)
#define LINE_TIM4_CH2               PAL_LINE(GPIOD, 13U)
#define LINE_FMC_D0                 PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1                 PAL_LINE(GPIOD, 15U)

#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_BUT4                   PAL_LINE(GPIOE, 2U)
#define LINE_BUT6                   PAL_LINE(GPIOE, 3U)
#define LINE_LCD_B0                 PAL_LINE(GPIOE, 4U)
#define LINE_LCD_G0                 PAL_LINE(GPIOE, 5U)
#define LINE_LCD_G1                 PAL_LINE(GPIOE, 6U)
#define LINE_FMC_D4                 PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5                 PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6                 PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7                 PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8                 PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9                 PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10                PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11                PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12                PAL_LINE(GPIOE, 15U)

#define LINE_FMC_A0                 PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1                 PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2                 PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3                 PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4                 PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5                 PAL_LINE(GPIOF, 5U)
#define LINE_SPI5_CS                PAL_LINE(GPIOF, 6U)
#define LINE_SPI5_SCK               PAL_LINE(GPIOF, 7U)
#define LINE_SPI5_MISO              PAL_LINE(GPIOF, 8U)
#define LINE_SPI5_MOSI              PAL_LINE(GPIOF, 9U)
#define LINE_LCD_DE                 PAL_LINE(GPIOF, 10U)
#define LINE_FMC_SDNRAS             PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6                 PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7                 PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8                 PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9                 PAL_LINE(GPIOF, 15U)

#define LINE_FMC_A10                PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11                PAL_LINE(GPIOG, 1U)
#define LINE_FMC_A12                PAL_LINE(GPIOG, 2U)
#define LINE_BUT3                   PAL_LINE(GPIOG, 3U)
#define LINE_FMC_BA0                PAL_LINE(GPIOG, 4U)
#define LINE_FMC_BA1                PAL_LINE(GPIOG, 5U)
#define LINE_LCD_R7                 PAL_LINE(GPIOG, 6U)
#define LINE_LCD_CLK                PAL_LINE(GPIOG, 7U)
#define LINE_FMC_SDCLK              PAL_LINE(GPIOG, 8U)
#define LINE_USART6_RX              PAL_LINE(GPIOG, 9U)
#define LINE_LCD_B2                 PAL_LINE(GPIOG, 10U)
#define LINE_LCD_B3                 PAL_LINE(GPIOG, 11U)
#define LINE_LCD_B1                 PAL_LINE(GPIOG, 12U)
#define LINE_USART1_EN              PAL_LINE(GPIOG, 13U)
#define LINE_USART6_TX              PAL_LINE(GPIOG, 14U)
#define LINE_FMC_SDNCAS             PAL_LINE(GPIOG, 15U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)
#define LINE_LCD_R0                 PAL_LINE(GPIOH, 2U)
#define LINE_LCD_R1                 PAL_LINE(GPIOH, 3U)
#define LINE_BUT5                   PAL_LINE(GPIOH, 4U)
#define LINE_FMC_SDNWE              PAL_LINE(GPIOH, 5U)
#define LINE_TIM12_CH1              PAL_LINE(GPIOH, 6U)
#define LINE_BUT1                   PAL_LINE(GPIOH, 7U)
#define LINE_LCD_R2                 PAL_LINE(GPIOH, 8U)
#define LINE_LCD_R3                 PAL_LINE(GPIOH, 9U)
#define LINE_LCD_R4                 PAL_LINE(GPIOH, 10U)
#define LINE_LCD_R5                 PAL_LINE(GPIOH, 11U)
#define LINE_LCD_R6                 PAL_LINE(GPIOH, 12U)
#define LINE_LCD_G2                 PAL_LINE(GPIOH, 13U)
#define LINE_LCD_G3                 PAL_LINE(GPIOH, 14U)
#define LINE_LCD_G4                 PAL_LINE(GPIOH, 15U)

#define LINE_LCD_G5                 PAL_LINE(GPIOI, 0U)
#define LINE_SPI2_SCK               PAL_LINE(GPIOI, 1U)
#define LINE_SPI2_MISO              PAL_LINE(GPIOI, 2U)
#define LINE_SPI2_MOSI              PAL_LINE(GPIOI, 3U)
#define LINE_LCD_B4                 PAL_LINE(GPIOI, 4U)
#define LINE_LCD_B5                 PAL_LINE(GPIOI, 5U)
#define LINE_LCD_B6                 PAL_LINE(GPIOI, 6U)
#define LINE_LCD_B7                 PAL_LINE(GPIOI, 7U)
#define LINE_LCD_BLCTRL             PAL_LINE(GPIOI, 8U)
#define LINE_LCD_VSYNC              PAL_LINE(GPIOI, 9U)
#define LINE_LCD_HSYNC              PAL_LINE(GPIOI, 10U)
#define LINE_SPI2_CS                PAL_LINE(GPIOI, 11U)



/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - ADC3_IN0                  (analog).
 * PA1  - ADC3_IN1                  (analog).
 * PA2  - ADC3_IN2                  (analog).
 * PA3  - ADC3_IN3                  (analog).
 * PA4  - DAC_OUT1                  (analog).
 * PA5  - ADC1_IN5                  (analog).
 * PA6  - ADC1_IN6                  (analog).
 * PA7  - ADC1_IN7                  (analog).
 * PA8  - TIM1_CH1                  (alternate 1).
 * PA9  - TIM1_CH2                  (alternate 1).
 * PA10 - TIM1_CH3                  (alternate 1).
 * PA11 - TIM1_CH4                  (alternate 1).
 * PA12 - T_IRQ                     (input floating).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - T_BUSY                    (input floating).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_ADC3_IN0) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC3_IN1) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC3_IN2) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC3_IN3) |      \
                                     PIN_MODE_ANALOG(GPIOA_DAC_OUT1) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC1_IN5) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC1_IN6) |      \
                                     PIN_MODE_ANALOG(GPIOA_ADC1_IN7) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_TIM1_CH1) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_TIM1_CH2) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_TIM1_CH3) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_TIM1_CH4) |   \
                                     PIN_MODE_INPUT(GPIOA_T_IRQ) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_T_BUSY))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_ADC3_IN0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC3_IN1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC3_IN2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC3_IN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_DAC_OUT1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC1_IN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC1_IN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC1_IN7) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TIM1_CH1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TIM1_CH2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TIM1_CH3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TIM1_CH4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_T_IRQ) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_T_BUSY))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_ADC3_IN0) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC3_IN1) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC3_IN2) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC3_IN3) |      \
                                     PIN_OSPEED_HIGH(GPIOA_DAC_OUT1) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC1_IN5) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC1_IN6) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ADC1_IN7) |      \
                                     PIN_OSPEED_HIGH(GPIOA_TIM1_CH1) |      \
                                     PIN_OSPEED_HIGH(GPIOA_TIM1_CH2) |      \
                                     PIN_OSPEED_HIGH(GPIOA_TIM1_CH3) |      \
                                     PIN_OSPEED_HIGH(GPIOA_TIM1_CH4) |      \
                                     PIN_OSPEED_VERYLOW(GPIOA_T_IRQ) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_VERYLOW(GPIOA_T_BUSY))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_ADC3_IN0) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_ADC3_IN1) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_ADC3_IN2) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_ADC3_IN3) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_DAC_OUT1) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_ADC1_IN5) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_ADC1_IN6) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_ADC1_IN7) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_TIM1_CH1) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_TIM1_CH2) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_TIM1_CH3) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_TIM1_CH4) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_T_IRQ) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_T_BUSY))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_ADC3_IN0) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC3_IN1) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC3_IN2) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC3_IN3) |         \
                                     PIN_ODR_HIGH(GPIOA_DAC_OUT1) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC1_IN5) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC1_IN6) |         \
                                     PIN_ODR_HIGH(GPIOA_ADC1_IN7) |         \
                                     PIN_ODR_HIGH(GPIOA_TIM1_CH1) |         \
                                     PIN_ODR_HIGH(GPIOA_TIM1_CH2) |         \
                                     PIN_ODR_HIGH(GPIOA_TIM1_CH3) |         \
                                     PIN_ODR_HIGH(GPIOA_TIM1_CH4) |         \
                                     PIN_ODR_HIGH(GPIOA_T_IRQ) |            \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_T_BUSY))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_ADC3_IN0, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC3_IN1, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC3_IN2, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC3_IN3, 0) |       \
                                     PIN_AFIO_AF(GPIOA_DAC_OUT1, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC1_IN5, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC1_IN6, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ADC1_IN7, 0))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_TIM1_CH1, 1) |       \
                                     PIN_AFIO_AF(GPIOA_TIM1_CH2, 1) |       \
                                     PIN_AFIO_AF(GPIOA_TIM1_CH3, 1) |       \
                                     PIN_AFIO_AF(GPIOA_TIM1_CH4, 1) |       \
                                     PIN_AFIO_AF(GPIOA_T_IRQ, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_T_BUSY, 0))

/*
 * GPIOB setup:
 *
 * PB0  - TIM3_CH3                  (alternate 2).
 * PB1  - TIM3_CH4                  (alternate 2).
 * PB2  - BUT2                      (input floating).
 * PB3  - SWO                       (alternate 0).
 * PB4  - TIM3_CH1                  (alternate 2).
 * PB5  - TIM3_CH2                  (alternate 2).
 * PB6  - USART1_TX                 (alternate 7).
 * PB7  - USART1_RX                 (alternate 7).
 * PB8  - I2C1_SCL                  (alternate 4).
 * PB9  - I2C1_SDA                  (alternate 4).
 * PB10 - TIM2_CH3                  (alternate 1).
 * PB11 - TIM2_CH4                  (alternate 1).
 * PB12 - PB12                      (input floating).
 * PB13 - OTG_HS_VBUS               (input floating).
 * PB14 - OTG_HS_DM                 (alternate 12).
 * PB15 - OTG_HS_DP                 (alternate 12).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_TIM3_CH3) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_TIM3_CH4) |   \
                                     PIN_MODE_INPUT(GPIOB_BUT2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_TIM3_CH1) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_TIM3_CH2) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_USART1_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_USART1_RX) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_TIM2_CH3) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_TIM2_CH4) |   \
                                     PIN_MODE_INPUT(GPIOB_PB12) |           \
                                     PIN_MODE_INPUT(GPIOB_OTG_HS_VBUS) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_TIM3_CH3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TIM3_CH4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BUT2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TIM3_CH1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TIM3_CH2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART1_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART1_RX) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TIM2_CH3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TIM2_CH4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB12) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_VBUS) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_TIM3_CH3) |      \
                                     PIN_OSPEED_HIGH(GPIOB_TIM3_CH4) |      \
                                     PIN_OSPEED_VERYLOW(GPIOB_BUT2) |       \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_HIGH(GPIOB_TIM3_CH1) |      \
                                     PIN_OSPEED_HIGH(GPIOB_TIM3_CH2) |      \
                                     PIN_OSPEED_HIGH(GPIOB_USART1_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOB_USART1_RX) |     \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA) |      \
                                     PIN_OSPEED_HIGH(GPIOB_TIM2_CH3) |      \
                                     PIN_OSPEED_HIGH(GPIOB_TIM2_CH4) |      \
                                     PIN_OSPEED_VERYLOW(GPIOB_PB12) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_OTG_HS_VBUS) |\
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_TIM3_CH3) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_TIM3_CH4) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_BUT2) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_TIM3_CH1) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_TIM3_CH2) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_USART1_TX) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_USART1_RX) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SCL) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SDA) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_TIM2_CH3) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_TIM2_CH4) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PB12) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_VBUS) |\
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_TIM3_CH3) |         \
                                     PIN_ODR_HIGH(GPIOB_TIM3_CH4) |         \
                                     PIN_ODR_HIGH(GPIOB_BUT2) |             \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_TIM3_CH1) |         \
                                     PIN_ODR_HIGH(GPIOB_TIM3_CH2) |         \
                                     PIN_ODR_HIGH(GPIOB_USART1_TX) |        \
                                     PIN_ODR_HIGH(GPIOB_USART1_RX) |        \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA) |         \
                                     PIN_ODR_HIGH(GPIOB_TIM2_CH3) |         \
                                     PIN_ODR_HIGH(GPIOB_TIM2_CH4) |         \
                                     PIN_ODR_HIGH(GPIOB_PB12) |             \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_VBUS) |      \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_DM) |        \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_TIM3_CH3, 2) |       \
                                     PIN_AFIO_AF(GPIOB_TIM3_CH4, 2) |       \
                                     PIN_AFIO_AF(GPIOB_BUT2, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SWO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_TIM3_CH1, 2) |       \
                                     PIN_AFIO_AF(GPIOB_TIM3_CH2, 2) |       \
                                     PIN_AFIO_AF(GPIOB_USART1_TX, 7) |      \
                                     PIN_AFIO_AF(GPIOB_USART1_RX, 7))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_I2C1_SCL, 4) |       \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA, 4) |       \
                                     PIN_AFIO_AF(GPIOB_TIM2_CH3, 1) |       \
                                     PIN_AFIO_AF(GPIOB_TIM2_CH4, 1) |       \
                                     PIN_AFIO_AF(GPIOB_PB12, 0) |           \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_VBUS, 0) |    \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_DM, 12) |     \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_DP, 12))

/*
 * GPIOC setup:
 *
 * PC0  - ADC3_IN10                 (analog).
 * PC1  - ADC3_IN11                 (analog).
 * PC2  - FMC_SDNE0                 (alternate 12).
 * PC3  - FMC_SDCKE0                (alternate 12).
 * PC4  - ADC1_IN14                 (analog).
 * PC5  - ADC1_IN15                 (analog).
 * PC6  - BUT8                      (input floating).
 * PC7  - LCD_G6                    (alternate 14).
 * PC8  - SDIO_D0                   (alternate 12).
 * PC9  - SDIO_D1                   (alternate 12).
 * PC10 - SDIO_D2                   (alternate 12).
 * PC11 - SDIO_D3                   (alternate 12).
 * PC12 - SDIO_CK                   (alternate 12).
 * PC13 - LED_R                     (output pushpull minimum).
 * PC14 - LED_G                     (output pushpull minimum).
 * PC15 - LED_B                     (output pushpull minimum).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ANALOG(GPIOC_ADC3_IN10) |     \
                                     PIN_MODE_ANALOG(GPIOC_ADC3_IN11) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_FMC_SDNE0) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_FMC_SDCKE0) | \
                                     PIN_MODE_ANALOG(GPIOC_ADC1_IN14) |     \
                                     PIN_MODE_ANALOG(GPIOC_ADC1_IN15) |     \
                                     PIN_MODE_INPUT(GPIOC_BUT8) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_LCD_G6) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D0) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D1) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D2) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D3) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_CK) |    \
                                     PIN_MODE_OUTPUT(GPIOC_LED_R) |         \
                                     PIN_MODE_OUTPUT(GPIOC_LED_G) |         \
                                     PIN_MODE_OUTPUT(GPIOC_LED_B))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_ADC3_IN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC3_IN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_FMC_SDNE0) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_FMC_SDCKE0) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC1_IN14) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC1_IN15) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_BUT8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LCD_G6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_CK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_R) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_G) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_B))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_ADC3_IN10) |     \
                                     PIN_OSPEED_HIGH(GPIOC_ADC3_IN11) |     \
                                     PIN_OSPEED_HIGH(GPIOC_FMC_SDNE0) |     \
                                     PIN_OSPEED_HIGH(GPIOC_FMC_SDCKE0) |    \
                                     PIN_OSPEED_HIGH(GPIOC_ADC1_IN14) |     \
                                     PIN_OSPEED_HIGH(GPIOC_ADC1_IN15) |     \
                                     PIN_OSPEED_VERYLOW(GPIOC_BUT8) |       \
                                     PIN_OSPEED_HIGH(GPIOC_LCD_G6) |        \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D0) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D1) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D2) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D3) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_CK) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_R) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_G) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_B))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_ADC3_IN10) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC3_IN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_FMC_SDNE0) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_FMC_SDCKE0) | \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC1_IN14) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC1_IN15) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_BUT8) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_LCD_G6) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D0) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D1) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D2) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D3) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_CK) |    \
                                     PIN_PUPDR_PULLUP(GPIOC_LED_R) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_LED_G) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_LED_B))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_ADC3_IN10) |        \
                                     PIN_ODR_HIGH(GPIOC_ADC3_IN11) |        \
                                     PIN_ODR_HIGH(GPIOC_FMC_SDNE0) |        \
                                     PIN_ODR_HIGH(GPIOC_FMC_SDCKE0) |       \
                                     PIN_ODR_HIGH(GPIOC_ADC1_IN14) |        \
                                     PIN_ODR_HIGH(GPIOC_ADC1_IN15) |        \
                                     PIN_ODR_HIGH(GPIOC_BUT8) |             \
                                     PIN_ODR_HIGH(GPIOC_LCD_G6) |           \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D0) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D1) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D2) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D3) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_CK) |          \
                                     PIN_ODR_HIGH(GPIOC_LED_R) |            \
                                     PIN_ODR_HIGH(GPIOC_LED_G) |            \
                                     PIN_ODR_HIGH(GPIOC_LED_B))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_ADC3_IN10, 0) |      \
                                     PIN_AFIO_AF(GPIOC_ADC3_IN11, 0) |      \
                                     PIN_AFIO_AF(GPIOC_FMC_SDNE0, 12) |     \
                                     PIN_AFIO_AF(GPIOC_FMC_SDCKE0, 12) |    \
                                     PIN_AFIO_AF(GPIOC_ADC1_IN14, 0) |      \
                                     PIN_AFIO_AF(GPIOC_ADC1_IN15, 0) |      \
                                     PIN_AFIO_AF(GPIOC_BUT8, 0) |           \
                                     PIN_AFIO_AF(GPIOC_LCD_G6, 14))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SDIO_D0, 12) |       \
                                     PIN_AFIO_AF(GPIOC_SDIO_D1, 12) |       \
                                     PIN_AFIO_AF(GPIOC_SDIO_D2, 12) |       \
                                     PIN_AFIO_AF(GPIOC_SDIO_D3, 12) |       \
                                     PIN_AFIO_AF(GPIOC_SDIO_CK, 12) |       \
                                     PIN_AFIO_AF(GPIOC_LED_R, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED_G, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED_B, 0))

/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2                    (alternate 12).
 * PD1  - FMC_D3                    (alternate 12).
 * PD2  - SDIO_CMD                  (alternate 12).
 * PD3  - LCD_G7                    (alternate 14).
 * PD4  - BUT7                      (input floating).
 * PD5  - USART2_TX                 (alternate 7).
 * PD6  - USART2_RX                 (alternate 7).
 * PD7  - LCD_DISP                  (output pushpull minimum).
 * PD8  - FMC_D13                   (alternate 12).
 * PD9  - FMC_D14                   (alternate 12).
 * PD10 - FMC_D15                   (alternate 12).
 * PD11 - DIP                       (input floating).
 * PD12 - TIM4_CH1                  (alternate 2).
 * PD13 - TIM4_CH2                  (alternate 2).
 * PD14 - FMC_D0                    (alternate 12).
 * PD15 - FMC_D1                    (alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_SDIO_CMD) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_LCD_G7) |     \
                                     PIN_MODE_INPUT(GPIOD_BUT7) |           \
                                     PIN_MODE_ALTERNATE(GPIOD_USART2_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_USART2_RX) |  \
                                     PIN_MODE_OUTPUT(GPIOD_LCD_DISP) |      \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15) |    \
                                     PIN_MODE_INPUT(GPIOD_DIP) |            \
                                     PIN_MODE_ALTERNATE(GPIOD_TIM4_CH1) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_TIM4_CH2) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SDIO_CMD) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LCD_G7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_BUT7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART2_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART2_RX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LCD_DISP) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_DIP) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOD_TIM4_CH1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_TIM4_CH2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3) |        \
                                     PIN_OSPEED_HIGH(GPIOD_SDIO_CMD) |      \
                                     PIN_OSPEED_HIGH(GPIOD_LCD_G7) |        \
                                     PIN_OSPEED_VERYLOW(GPIOD_BUT7) |       \
                                     PIN_OSPEED_HIGH(GPIOD_USART2_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOD_USART2_RX) |     \
                                     PIN_OSPEED_VERYLOW(GPIOD_LCD_DISP) |   \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_DIP) |        \
                                     PIN_OSPEED_HIGH(GPIOD_TIM4_CH1) |      \
                                     PIN_OSPEED_HIGH(GPIOD_TIM4_CH2) |      \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_SDIO_CMD) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_LCD_G7) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_BUT7) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_USART2_TX) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_USART2_RX) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_LCD_DISP) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_DIP) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_TIM4_CH1) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_TIM4_CH2) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D3) |           \
                                     PIN_ODR_HIGH(GPIOD_SDIO_CMD) |         \
                                     PIN_ODR_HIGH(GPIOD_LCD_G7) |           \
                                     PIN_ODR_HIGH(GPIOD_BUT7) |             \
                                     PIN_ODR_HIGH(GPIOD_USART2_TX) |        \
                                     PIN_ODR_HIGH(GPIOD_USART2_RX) |        \
                                     PIN_ODR_LOW(GPIOD_LCD_DISP) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D14) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D15) |          \
                                     PIN_ODR_HIGH(GPIOD_DIP) |              \
                                     PIN_ODR_HIGH(GPIOD_TIM4_CH1) |         \
                                     PIN_ODR_HIGH(GPIOD_TIM4_CH2) |         \
                                     PIN_ODR_HIGH(GPIOD_FMC_D0) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12) |        \
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12) |        \
                                     PIN_AFIO_AF(GPIOD_SDIO_CMD, 12) |      \
                                     PIN_AFIO_AF(GPIOD_LCD_G7, 14) |        \
                                     PIN_AFIO_AF(GPIOD_BUT7, 0) |           \
                                     PIN_AFIO_AF(GPIOD_USART2_TX, 7) |      \
                                     PIN_AFIO_AF(GPIOD_USART2_RX, 7) |      \
                                     PIN_AFIO_AF(GPIOD_LCD_DISP, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12) |       \
                                     PIN_AFIO_AF(GPIOD_DIP, 0) |            \
                                     PIN_AFIO_AF(GPIOD_TIM4_CH1, 2) |       \
                                     PIN_AFIO_AF(GPIOD_TIM4_CH2, 2) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12) |        \
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12))

/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - BUT4                      (input floating).
 * PE3  - BUT6                      (input floating).
 * PE4  - LCD_B0                    (alternate 14).
 * PE5  - LCD_G0                    (alternate 14).
 * PE6  - LCD_G1                    (alternate 14).
 * PE7  - FMC_D4                    (alternate 12).
 * PE8  - FMC_D5                    (alternate 12).
 * PE9  - FMC_D6                    (alternate 12).
 * PE10 - FMC_D7                    (alternate 12).
 * PE11 - FMC_D8                    (alternate 12).
 * PE12 - FMC_D9                    (alternate 12).
 * PE13 - FMC_D10                   (alternate 12).
 * PE14 - FMC_D11                   (alternate 12).
 * PE15 - FMC_D12                   (alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1) |   \
                                     PIN_MODE_INPUT(GPIOE_BUT4) |           \
                                     PIN_MODE_INPUT(GPIOE_BUT6) |           \
                                     PIN_MODE_ALTERNATE(GPIOE_LCD_B0) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_LCD_G0) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_LCD_G1) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_BUT4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_BUT6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_LCD_B0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_LCD_G0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_LCD_G1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0) |      \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_BUT4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_BUT6) |       \
                                     PIN_OSPEED_HIGH(GPIOE_LCD_B0) |        \
                                     PIN_OSPEED_HIGH(GPIOE_LCD_G0) |        \
                                     PIN_OSPEED_HIGH(GPIOE_LCD_G1) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_BUT4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_BUT6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_LCD_B0) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_LCD_G0) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_LCD_G1) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0) |         \
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1) |         \
                                     PIN_ODR_HIGH(GPIOE_BUT4) |             \
                                     PIN_ODR_HIGH(GPIOE_BUT6) |             \
                                     PIN_ODR_HIGH(GPIOE_LCD_B0) |           \
                                     PIN_ODR_HIGH(GPIOE_LCD_G0) |           \
                                     PIN_ODR_HIGH(GPIOE_LCD_G1) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D4) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D5) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D7) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D8) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D9) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D10) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D11) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12) |      \
                                     PIN_AFIO_AF(GPIOE_BUT4, 0) |           \
                                     PIN_AFIO_AF(GPIOE_BUT6, 0) |           \
                                     PIN_AFIO_AF(GPIOE_LCD_B0, 14) |        \
                                     PIN_AFIO_AF(GPIOE_LCD_G0, 14) |        \
                                     PIN_AFIO_AF(GPIOE_LCD_G1, 14) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 12))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12) |        \
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12))

/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0                    (alternate 12).
 * PF1  - FMC_A1                    (alternate 12).
 * PF2  - FMC_A2                    (alternate 12).
 * PF3  - FMC_A3                    (alternate 12).
 * PF4  - FMC_A4                    (alternate 12).
 * PF5  - FMC_A5                    (alternate 12).
 * PF6  - SPI5_CS                   (output pushpull maximum).
 * PF7  - SPI5_SCK                  (alternate 5).
 * PF8  - SPI5_MISO                 (alternate 5).
 * PF9  - SPI5_MOSI                 (alternate 5).
 * PF10 - LCD_DE                    (alternate 14).
 * PF11 - FMC_SDNRAS                (alternate 12).
 * PF12 - FMC_A6                    (alternate 12).
 * PF13 - FMC_A7                    (alternate 12).
 * PF14 - FMC_A8                    (alternate 12).
 * PF15 - FMC_A9                    (alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5) |     \
                                     PIN_MODE_OUTPUT(GPIOF_SPI5_CS) |       \
                                     PIN_MODE_ALTERNATE(GPIOF_SPI5_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOF_SPI5_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOF_SPI5_MOSI) |  \
                                     PIN_MODE_ALTERNATE(GPIOF_LCD_DE) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_SDNRAS) | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_CS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_LCD_DE) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_SDNRAS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5) |        \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_CS) |       \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_SCK) |      \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOF_LCD_DE) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_SDNRAS) |    \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5) |     \
                                     PIN_PUPDR_PULLUP(GPIOF_SPI5_CS) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_LCD_DE) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_SDNRAS) | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A1) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A2) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A3) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A4) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A5) |           \
                                     PIN_ODR_HIGH(GPIOF_SPI5_CS) |          \
                                     PIN_ODR_HIGH(GPIOF_SPI5_SCK) |         \
                                     PIN_ODR_HIGH(GPIOF_SPI5_MISO) |        \
                                     PIN_ODR_HIGH(GPIOF_SPI5_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOF_LCD_DE) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_SDNRAS) |       \
                                     PIN_ODR_HIGH(GPIOF_FMC_A6) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A7) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A8) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12) |        \
                                     PIN_AFIO_AF(GPIOF_SPI5_CS, 0) |        \
                                     PIN_AFIO_AF(GPIOF_SPI5_SCK, 5))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_SPI5_MISO, 5) |      \
                                     PIN_AFIO_AF(GPIOF_SPI5_MOSI, 5) |      \
                                     PIN_AFIO_AF(GPIOF_LCD_DE, 14) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_SDNRAS, 12) |    \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12) |        \
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12))

/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10                   (alternate 12).
 * PG1  - FMC_A11                   (alternate 12).
 * PG2  - FMC_A12                   (alternate 12).
 * PG3  - BUT3                      (input floating).
 * PG4  - FMC_BA0                   (alternate 12).
 * PG5  - FMC_BA1                   (alternate 12).
 * PG6  - LCD_R7                    (alternate 14).
 * PG7  - LCD_CLK                   (alternate 14).
 * PG8  - FMC_SDCLK                 (alternate 12).
 * PG9  - USART6_RX                 (alternate 8).
 * PG10 - LCD_B2                    (alternate 14).
 * PG11 - LCD_B3                    (alternate 14).
 * PG12 - LCD_B1                    (alternate 14).
 * PG13 - USART1_EN                 (output pushpull maximum).
 * PG14 - USART6_TX                 (alternate 8).
 * PG15 - FMC_SDNCAS                (alternate 12).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12) |    \
                                     PIN_MODE_INPUT(GPIOG_BUT3) |           \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA0) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA1) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_LCD_R7) |     \
                                     PIN_MODE_ALTERNATE(GPIOG_LCD_CLK) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDCLK) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_USART6_RX) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_LCD_B2) |     \
                                     PIN_MODE_ALTERNATE(GPIOG_LCD_B3) |     \
                                     PIN_MODE_ALTERNATE(GPIOG_LCD_B1) |     \
                                     PIN_MODE_OUTPUT(GPIOG_USART1_EN) |     \
                                     PIN_MODE_ALTERNATE(GPIOG_USART6_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_BUT3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_LCD_R7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_LCD_CLK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDCLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_USART6_RX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_LCD_B2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_LCD_B3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_LCD_B1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_USART1_EN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_USART6_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_BUT3) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA0) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA1) |       \
                                     PIN_OSPEED_HIGH(GPIOG_LCD_R7) |        \
                                     PIN_OSPEED_HIGH(GPIOG_LCD_CLK) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDCLK) |     \
                                     PIN_OSPEED_HIGH(GPIOG_USART6_RX) |     \
                                     PIN_OSPEED_HIGH(GPIOG_LCD_B2) |        \
                                     PIN_OSPEED_HIGH(GPIOG_LCD_B3) |        \
                                     PIN_OSPEED_HIGH(GPIOG_LCD_B1) |        \
                                     PIN_OSPEED_HIGH(GPIOG_USART1_EN) |     \
                                     PIN_OSPEED_HIGH(GPIOG_USART6_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_BUT3) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA0) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA1) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_LCD_R7) |     \
                                     PIN_PUPDR_FLOATING(GPIOG_LCD_CLK) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDCLK) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_USART6_RX) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_LCD_B2) |     \
                                     PIN_PUPDR_FLOATING(GPIOG_LCD_B3) |     \
                                     PIN_PUPDR_FLOATING(GPIOG_LCD_B1) |     \
                                     PIN_PUPDR_FLOATING(GPIOG_USART1_EN) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_USART6_TX) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A11) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A12) |          \
                                     PIN_ODR_HIGH(GPIOG_BUT3) |             \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA0) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA1) |          \
                                     PIN_ODR_HIGH(GPIOG_LCD_R7) |           \
                                     PIN_ODR_HIGH(GPIOG_LCD_CLK) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDCLK) |        \
                                     PIN_ODR_HIGH(GPIOG_USART6_RX) |        \
                                     PIN_ODR_HIGH(GPIOG_LCD_B2) |           \
                                     PIN_ODR_HIGH(GPIOG_LCD_B3) |           \
                                     PIN_ODR_HIGH(GPIOG_LCD_B1) |           \
                                     PIN_ODR_LOW(GPIOG_USART1_EN) |         \
                                     PIN_ODR_HIGH(GPIOG_USART6_TX) |        \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12) |       \
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12) |       \
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12) |       \
                                     PIN_AFIO_AF(GPIOG_BUT3, 0) |           \
                                     PIN_AFIO_AF(GPIOG_FMC_BA0, 12) |       \
                                     PIN_AFIO_AF(GPIOG_FMC_BA1, 12) |       \
                                     PIN_AFIO_AF(GPIOG_LCD_R7, 14) |        \
                                     PIN_AFIO_AF(GPIOG_LCD_CLK, 14))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_FMC_SDCLK, 12) |     \
                                     PIN_AFIO_AF(GPIOG_USART6_RX, 8) |      \
                                     PIN_AFIO_AF(GPIOG_LCD_B2, 14) |        \
                                     PIN_AFIO_AF(GPIOG_LCD_B3, 14) |        \
                                     PIN_AFIO_AF(GPIOG_LCD_B1, 14) |        \
                                     PIN_AFIO_AF(GPIOG_USART1_EN, 0) |      \
                                     PIN_AFIO_AF(GPIOG_USART6_TX, 8) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_SDNCAS, 12))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - LCD_R0                    (alternate 14).
 * PH3  - LCD_R1                    (alternate 14).
 * PH4  - BUT5                      (input floating).
 * PH5  - FMC_SDNWE                 (alternate 12).
 * PH6  - TIM12_CH1                 (alternate 9).
 * PH7  - BUT1                      (input floating).
 * PH8  - LCD_R2                    (alternate 14).
 * PH9  - LCD_R3                    (alternate 14).
 * PH10 - LCD_R4                    (alternate 14).
 * PH11 - LCD_R5                    (alternate 14).
 * PH12 - LCD_R6                    (alternate 14).
 * PH13 - LCD_G2                    (alternate 14).
 * PH14 - LCD_G3                    (alternate 14).
 * PH15 - LCD_G4                    (alternate 14).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R0) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R1) |     \
                                     PIN_MODE_INPUT(GPIOH_BUT5) |           \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_SDNWE) |  \
                                     PIN_MODE_ALTERNATE(GPIOH_TIM12_CH1) |  \
                                     PIN_MODE_INPUT(GPIOH_BUT1) |           \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R2) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R3) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R4) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R5) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_R6) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_G2) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_G3) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_LCD_G4))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_BUT5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_SDNWE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_TIM12_CH1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_BUT1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_R6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_G2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_G3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LCD_G4))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R0) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R1) |        \
                                     PIN_OSPEED_VERYLOW(GPIOH_BUT5) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_SDNWE) |     \
                                     PIN_OSPEED_HIGH(GPIOH_TIM12_CH1) |     \
                                     PIN_OSPEED_VERYLOW(GPIOH_BUT1) |       \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R2) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R3) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R4) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R5) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_R6) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_G2) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_G3) |        \
                                     PIN_OSPEED_HIGH(GPIOH_LCD_G4))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R0) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R1) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_BUT5) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_SDNWE) |  \
                                     PIN_PUPDR_FLOATING(GPIOH_TIM12_CH1) |  \
                                     PIN_PUPDR_FLOATING(GPIOH_BUT1) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R2) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R3) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R4) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R5) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_R6) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_G2) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_G3) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_LCD_G4))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_LCD_R0) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_R1) |           \
                                     PIN_ODR_HIGH(GPIOH_BUT5) |             \
                                     PIN_ODR_HIGH(GPIOH_FMC_SDNWE) |        \
                                     PIN_ODR_HIGH(GPIOH_TIM12_CH1) |        \
                                     PIN_ODR_HIGH(GPIOH_BUT1) |             \
                                     PIN_ODR_HIGH(GPIOH_LCD_R2) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_R3) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_R4) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_R5) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_R6) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_G2) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_G3) |           \
                                     PIN_ODR_HIGH(GPIOH_LCD_G4))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R0, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R1, 14) |        \
                                     PIN_AFIO_AF(GPIOH_BUT5, 0) |           \
                                     PIN_AFIO_AF(GPIOH_FMC_SDNWE, 12) |     \
                                     PIN_AFIO_AF(GPIOH_TIM12_CH1, 9) |      \
                                     PIN_AFIO_AF(GPIOH_BUT1, 0))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_LCD_R2, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R3, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R4, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R5, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_R6, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_G2, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_G3, 14) |        \
                                     PIN_AFIO_AF(GPIOH_LCD_G4, 14))

/*
 * GPIOI setup:
 *
 * PI0  - LCD_G5                    (alternate 14).
 * PI1  - SPI2_SCK                  (alternate 5).
 * PI2  - SPI2_MISO                 (alternate 5).
 * PI3  - SPI2_MOSI                 (alternate 5).
 * PI4  - LCD_B4                    (alternate 14).
 * PI5  - LCD_B5                    (alternate 14).
 * PI6  - LCD_B6                    (alternate 14).
 * PI7  - LCD_B7                    (alternate 14).
 * PI8  - LCD_BLCTRL                (output pushpull maximum).
 * PI9  - LCD_VSYNC                 (alternate 14).
 * PI10 - LCD_HSYNC                 (alternate 14).
 * PI11 - SPI2_CS                   (output pushpull maximum).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_ALTERNATE(GPIOI_LCD_G5) |     \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_MOSI) |  \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_B4) |     \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_B5) |     \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_B6) |     \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_B7) |     \
                                     PIN_MODE_OUTPUT(GPIOI_LCD_BLCTRL) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_VSYNC) |  \
                                     PIN_MODE_ALTERNATE(GPIOI_LCD_HSYNC) |  \
                                     PIN_MODE_OUTPUT(GPIOI_SPI2_CS) |       \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_LCD_G5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_B4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_B5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_B6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_B7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_BLCTRL) | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_VSYNC) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOI_LCD_HSYNC) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_CS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_LCD_G5) |        \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_SCK) |      \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_B4) |        \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_B5) |        \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_B6) |        \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_B7) |        \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_BLCTRL) |    \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_VSYNC) |     \
                                     PIN_OSPEED_HIGH(GPIOI_LCD_HSYNC) |     \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_CS) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_LCD_G5) |     \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_B4) |     \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_B5) |     \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_B6) |     \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_B7) |     \
                                     PIN_PUPDR_PULLUP(GPIOI_LCD_BLCTRL) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_VSYNC) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_LCD_HSYNC) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_CS) |    \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_LCD_G5) |           \
                                     PIN_ODR_HIGH(GPIOI_SPI2_SCK) |         \
                                     PIN_ODR_HIGH(GPIOI_SPI2_MISO) |        \
                                     PIN_ODR_HIGH(GPIOI_SPI2_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOI_LCD_B4) |           \
                                     PIN_ODR_HIGH(GPIOI_LCD_B5) |           \
                                     PIN_ODR_HIGH(GPIOI_LCD_B6) |           \
                                     PIN_ODR_HIGH(GPIOI_LCD_B7) |           \
                                     PIN_ODR_HIGH(GPIOI_LCD_BLCTRL) |       \
                                     PIN_ODR_HIGH(GPIOI_LCD_VSYNC) |        \
                                     PIN_ODR_HIGH(GPIOI_LCD_HSYNC) |        \
                                     PIN_ODR_HIGH(GPIOI_SPI2_CS) |          \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_LCD_G5, 14) |        \
                                     PIN_AFIO_AF(GPIOI_SPI2_SCK, 5) |       \
                                     PIN_AFIO_AF(GPIOI_SPI2_MISO, 5) |      \
                                     PIN_AFIO_AF(GPIOI_SPI2_MOSI, 5) |      \
                                     PIN_AFIO_AF(GPIOI_LCD_B4, 14) |        \
                                     PIN_AFIO_AF(GPIOI_LCD_B5, 14) |        \
                                     PIN_AFIO_AF(GPIOI_LCD_B6, 14) |        \
                                     PIN_AFIO_AF(GPIOI_LCD_B7, 14))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_LCD_BLCTRL, 0) |     \
                                     PIN_AFIO_AF(GPIOI_LCD_VSYNC, 14) |     \
                                     PIN_AFIO_AF(GPIOI_LCD_HSYNC, 14) |     \
                                     PIN_AFIO_AF(GPIOI_SPI2_CS, 0) |        \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0))

/*
 * GPIOJ setup:
 *
 * PJ0  - PIN0                      (input floating).
 * PJ1  - PIN1                      (input floating).
 * PJ2  - PIN2                      (input floating).
 * PJ3  - PIN3                      (input floating).
 * PJ4  - PIN4                      (input floating).
 * PJ5  - PIN5                      (input floating).
 * PJ6  - PIN6                      (input floating).
 * PJ7  - PIN7                      (input floating).
 * PJ8  - PIN8                      (input floating).
 * PJ9  - PIN9                      (input floating).
 * PJ10 - PIN10                     (input floating).
 * PJ11 - PIN11                     (input floating).
 * PJ12 - PIN12                     (input floating).
 * PJ13 - PIN13                     (input floating).
 * PJ14 - PIN14                     (input floating).
 * PJ15 - PIN15                     (input floating).
 */
#define VAL_GPIOJ_MODER             (PIN_MODE_INPUT(GPIOJ_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN15))
#define VAL_GPIOJ_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOJ_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN15))
#define VAL_GPIOJ_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOJ_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN15))
#define VAL_GPIOJ_PUPDR             (PIN_PUPDR_FLOATING(GPIOJ_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN15))
#define VAL_GPIOJ_ODR               (PIN_ODR_HIGH(GPIOJ_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN15))
#define VAL_GPIOJ_AFRL              (PIN_AFIO_AF(GPIOJ_PIN0, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN1, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN2, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN3, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN4, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN5, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN6, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN7, 14))
#define VAL_GPIOJ_AFRH              (PIN_AFIO_AF(GPIOJ_PIN8, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN9, 14) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN10, 14) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN11, 14) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN13, 14) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN14, 14) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN15, 14))

/*
 * GPIOK setup:
 *
 * PK0  - PIN0                      (input floating).
 * PK1  - PIN1                      (input floating).
 * PK2  - PIN2                      (input floating).
 * PK3  - PIN3                      (input floating).
 * PK4  - PIN4                      (input floating).
 * PK5  - PIN5                      (input floating).
 * PK6  - PIN6                      (input floating).
 * PK7  - PIN7                      (input floating).
 * PK8  - PIN8                      (input floating).
 * PK9  - PIN9                      (input floating).
 * PK10 - PIN10                     (input floating).
 * PK11 - PIN11                     (input floating).
 * PK12 - PIN12                     (input floating).
 * PK13 - PIN13                     (input floating).
 * PK14 - PIN14                     (input floating).
 * PK15 - PIN15                     (input floating).
 */
#define VAL_GPIOK_MODER             (PIN_MODE_INPUT(GPIOK_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN15))
#define VAL_GPIOK_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOK_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN15))
#define VAL_GPIOK_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOK_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN15))
#define VAL_GPIOK_PUPDR             (PIN_PUPDR_FLOATING(GPIOK_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN15))
#define VAL_GPIOK_ODR               (PIN_ODR_HIGH(GPIOK_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN2) |             \
                                     PIN_ODR_LOW(GPIOK_PIN3) |              \
                                     PIN_ODR_HIGH(GPIOK_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN15))
#define VAL_GPIOK_AFRL              (PIN_AFIO_AF(GPIOK_PIN0, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN1, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN2, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOK_PIN4, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN5, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN6, 14) |          \
                                     PIN_AFIO_AF(GPIOK_PIN7, 14))
#define VAL_GPIOK_AFRH              (PIN_AFIO_AF(GPIOK_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOK_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOK_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOK_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOK_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOK_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOK_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOK_PIN15, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
