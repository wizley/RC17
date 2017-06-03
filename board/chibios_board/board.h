/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

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
 * Setup for M2 Robocon STM32F429I MainBoard 2015 board.
 */

/*
 * Board identifier.
 */
#define BOARD_MB2015
#define BOARD_NAME                  "M2 Robocon STM32F429I MainBoard 2015"


/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300

/*
 * MCU type as defined in the ST header.
 */
#define STM32F429xx

/*
 * IO pins assignments.
 */
#define GPIOA_ADC3_IN0              0
#define GPIOA_ADC3_IN1              1
#define GPIOA_ADC3_IN2              2
#define GPIOA_ADC3_IN3              3
#define GPIOA_DAC_OUT1              4
#define GPIOA_ADC1_IN5              5
#define GPIOA_ADC1_IN6              6
#define GPIOA_ADC1_IN7              7
#define GPIOA_TIM1_CH1              8
#define GPIOA_TIM1_CH2              9
#define GPIOA_TIM1_CH3              10
#define GPIOA_TIM1_CH4              11
#define GPIOA_T_IRQ                 12
#define GPIOA_SWDIO                 13
#define GPIOA_SWCLK                 14
#define GPIOA_BUZZER                15

#define GPIOB_TIM3_CH3              0
#define GPIOB_TIM3_CH4              1
#define GPIOB_BUT2                  2
#define GPIOB_SWO                   3
#define GPIOB_TIM3_CH1              4
#define GPIOB_TIM3_CH2              5
#define GPIOB_USART1_TX             6
#define GPIOB_USART1_RX             7
#define GPIOB_I2C1_SCL              8
#define GPIOB_I2C1_SDA              9
#define GPIOB_TIM2_CH3              10
#define GPIOB_TIM2_CH4              11
#define GPIOB_PB12                  12
#define GPIOB_OTG_HS_VBUS           13
#define GPIOB_OTG_HS_DM             14
#define GPIOB_OTG_HS_DP             15

#define GPIOC_ADC3_IN10             0
#define GPIOC_ADC3_IN11             1
#define GPIOC_FMC_SDNE0             2
#define GPIOC_FMC_SDCKE0            3
#define GPIOC_ADC1_IN14             4
#define GPIOC_ADC1_IN15             5
#define GPIOC_BUT8                  6
#define GPIOC_LCD_G6                7
#define GPIOC_SDIO_D0               8
#define GPIOC_SDIO_D1               9
#define GPIOC_SDIO_D2               10
#define GPIOC_SDIO_D3               11
#define GPIOC_SDIO_CK               12
#define GPIOC_LED_R                 13
#define GPIOC_LED_G                 14
#define GPIOC_LED_B                 15

#define GPIOD_FMC_D2                0
#define GPIOD_FMC_D3                1
#define GPIOD_SDIO_CMD              2
#define GPIOD_LCD_G7                3
#define GPIOD_BUT7                  4
#define GPIOD_USART2_TX             5
#define GPIOD_USART2_RX             6
#define GPIOD_LCD_DISP              7
#define GPIOD_FMC_D13               8
#define GPIOD_FMC_D14               9
#define GPIOD_FMC_D15               10
#define GPIOD_DIP                   11
#define GPIOD_TIM4_CH1              12
#define GPIOD_TIM4_CH2              13
#define GPIOD_FMC_D0                14
#define GPIOD_FMC_D1                15

#define GPIOE_FMC_NBL0              0
#define GPIOE_FMC_NBL1              1
#define GPIOE_BUT4                  2
#define GPIOE_BUT6                  3
#define GPIOE_LCD_B0                4
#define GPIOE_LCD_G0                5
#define GPIOE_LCD_G1                6
#define GPIOE_FMC_D4                7
#define GPIOE_FMC_D5                8
#define GPIOE_FMC_D6                9
#define GPIOE_FMC_D7                10
#define GPIOE_FMC_D8                11
#define GPIOE_FMC_D9                12
#define GPIOE_FMC_D10               13
#define GPIOE_FMC_D11               14
#define GPIOE_FMC_D12               15

#define GPIOF_FMC_A0                0
#define GPIOF_FMC_A1                1
#define GPIOF_FMC_A2                2
#define GPIOF_FMC_A3                3
#define GPIOF_FMC_A4                4
#define GPIOF_FMC_A5                5
#define GPIOF_SPI5_CS               6
#define GPIOF_SPI5_SCK              7
#define GPIOF_SPI5_MISO             8
#define GPIOF_SPI5_MOSI             9
#define GPIOF_LCD_DE                10
#define GPIOF_FMC_SDNRAS            11
#define GPIOF_FMC_A6                12
#define GPIOF_FMC_A7                13
#define GPIOF_FMC_A8                14
#define GPIOF_FMC_A9                15

#define GPIOG_FMC_A10               0
#define GPIOG_FMC_A11               1
#define GPIOG_FMC_A12               2
#define GPIOG_BUT3                  3
#define GPIOG_FMC_BA0               4
#define GPIOG_FMC_BA1               5
#define GPIOG_LCD_R7                6
#define GPIOG_LCD_CLK               7
#define GPIOG_FMC_SDCLK             8
#define GPIOG_USART6_RX             9
#define GPIOG_LCD_B2                10
#define GPIOG_LCD_B3                11
#define GPIOG_LCD_B1                12
#define GPIOG_USART1_EN             13
#define GPIOG_USART6_TX             14
#define GPIOG_FMC_SDNCAS            15

#define GPIOH_OSC_IN                0
#define GPIOH_OSC_OUT               1
#define GPIOH_LCD_R0                2
#define GPIOH_LCD_R1                3
#define GPIOH_BUT5                  4
#define GPIOH_FMC_SDNWE             5
#define GPIOH_TIM12_CH1             6
#define GPIOH_BUT1                  7
#define GPIOH_LCD_R2                8
#define GPIOH_LCD_R3                9
#define GPIOH_LCD_R4                10
#define GPIOH_LCD_R5                11
#define GPIOH_LCD_R6                12
#define GPIOH_LCD_G2                13
#define GPIOH_LCD_G3                14
#define GPIOH_LCD_G4                15

#define GPIOI_LCD_G5                0
#define GPIOI_SPI2_SCK              1
#define GPIOI_SPI2_MISO             2
#define GPIOI_SPI2_MOSI             3
#define GPIOI_LCD_B4                4
#define GPIOI_LCD_B5                5
#define GPIOI_LCD_B6                6
#define GPIOI_LCD_B7                7
#define GPIOI_LCD_BLCTRL            8
#define GPIOI_LCD_VSYNC             9
#define GPIOI_LCD_HSYNC             10
#define GPIOI_SPI2_CS               11
#define GPIOI_PIN12                 12
#define GPIOI_PIN13                 13
#define GPIOI_PIN14                 14
#define GPIOI_PIN15                 15

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2))
#define PIN_OSPEED_25M(n)           (1U << ((n) * 2))
#define PIN_OSPEED_50M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_100M(n)          (3U << ((n) * 2))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

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
                                     PIN_MODE_OUTPUT(GPIOA_T_IRQ) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_BUZZER))
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
                                     PIN_OTYPE_PUSHPULL(GPIOA_BUZZER))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_100M(GPIOA_ADC3_IN0) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC3_IN1) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC3_IN2) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC3_IN3) |      \
                                     PIN_OSPEED_100M(GPIOA_DAC_OUT1) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC1_IN5) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC1_IN6) |      \
                                     PIN_OSPEED_100M(GPIOA_ADC1_IN7) |      \
                                     PIN_OSPEED_100M(GPIOA_TIM1_CH1) |      \
                                     PIN_OSPEED_100M(GPIOA_TIM1_CH2) |      \
                                     PIN_OSPEED_100M(GPIOA_TIM1_CH3) |      \
                                     PIN_OSPEED_100M(GPIOA_TIM1_CH4) |      \
                                     PIN_OSPEED_2M(GPIOA_T_IRQ) |           \
                                     PIN_OSPEED_100M(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_100M(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_2M(GPIOA_BUZZER))
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
                                     PIN_PUPDR_PULLDOWN(GPIOA_T_IRQ) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_BUZZER))
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
                                     PIN_ODR_LOW(GPIOA_T_IRQ) |            \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_LOW(GPIOA_BUZZER))
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
                                     PIN_AFIO_AF(GPIOA_BUZZER, 1))

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
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_100M(GPIOB_TIM3_CH3) |      \
                                     PIN_OSPEED_100M(GPIOB_TIM3_CH4) |      \
                                     PIN_OSPEED_2M(GPIOB_BUT2) |            \
                                     PIN_OSPEED_100M(GPIOB_SWO) |           \
                                     PIN_OSPEED_100M(GPIOB_TIM3_CH1) |      \
                                     PIN_OSPEED_100M(GPIOB_TIM3_CH2) |      \
                                     PIN_OSPEED_100M(GPIOB_USART1_TX) |     \
                                     PIN_OSPEED_100M(GPIOB_USART1_RX) |     \
                                     PIN_OSPEED_100M(GPIOB_I2C1_SCL) |      \
                                     PIN_OSPEED_100M(GPIOB_I2C1_SDA) |      \
                                     PIN_OSPEED_100M(GPIOB_TIM2_CH3) |      \
                                     PIN_OSPEED_100M(GPIOB_TIM2_CH4) |      \
                                     PIN_OSPEED_2M(GPIOB_PB12) |            \
                                     PIN_OSPEED_2M(GPIOB_OTG_HS_VBUS) |     \
                                     PIN_OSPEED_100M(GPIOB_OTG_HS_DM) |     \
                                     PIN_OSPEED_100M(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_TIM3_CH3) |   \
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
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_100M(GPIOC_ADC3_IN10) |     \
                                     PIN_OSPEED_100M(GPIOC_ADC3_IN11) |     \
                                     PIN_OSPEED_100M(GPIOC_FMC_SDNE0) |     \
                                     PIN_OSPEED_100M(GPIOC_FMC_SDCKE0) |    \
                                     PIN_OSPEED_100M(GPIOC_ADC1_IN14) |     \
                                     PIN_OSPEED_100M(GPIOC_ADC1_IN15) |     \
                                     PIN_OSPEED_2M(GPIOC_BUT8) |            \
                                     PIN_OSPEED_100M(GPIOC_LCD_G6) |        \
                                     PIN_OSPEED_100M(GPIOC_SDIO_D0) |       \
                                     PIN_OSPEED_100M(GPIOC_SDIO_D1) |       \
                                     PIN_OSPEED_100M(GPIOC_SDIO_D2) |       \
                                     PIN_OSPEED_100M(GPIOC_SDIO_D3) |       \
                                     PIN_OSPEED_100M(GPIOC_SDIO_CK) |       \
                                     PIN_OSPEED_2M(GPIOC_LED_R) |           \
                                     PIN_OSPEED_2M(GPIOC_LED_G) |           \
                                     PIN_OSPEED_2M(GPIOC_LED_B))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_ADC3_IN10) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC3_IN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_FMC_SDNE0) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_FMC_SDCKE0) | \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC1_IN14) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC1_IN15) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_BUT8) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_LCD_G6) |     \
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
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_100M(GPIOD_FMC_D2) |        \
                                     PIN_OSPEED_100M(GPIOD_FMC_D3) |        \
                                     PIN_OSPEED_100M(GPIOD_SDIO_CMD) |      \
                                     PIN_OSPEED_100M(GPIOD_LCD_G7) |        \
                                     PIN_OSPEED_2M(GPIOD_BUT7) |            \
                                     PIN_OSPEED_100M(GPIOD_USART2_TX) |     \
                                     PIN_OSPEED_100M(GPIOD_USART2_RX) |     \
                                     PIN_OSPEED_2M(GPIOD_LCD_DISP) |        \
                                     PIN_OSPEED_100M(GPIOD_FMC_D13) |       \
                                     PIN_OSPEED_100M(GPIOD_FMC_D14) |       \
                                     PIN_OSPEED_100M(GPIOD_FMC_D15) |       \
                                     PIN_OSPEED_2M(GPIOD_DIP) |             \
                                     PIN_OSPEED_100M(GPIOD_TIM4_CH1) |      \
                                     PIN_OSPEED_100M(GPIOD_TIM4_CH2) |      \
                                     PIN_OSPEED_100M(GPIOD_FMC_D0) |        \
                                     PIN_OSPEED_100M(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_SDIO_CMD) |   \
                                     PIN_PUPDR_PULLUP(GPIOD_LCD_G7) |     \
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
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_100M(GPIOE_FMC_NBL0) |      \
                                     PIN_OSPEED_100M(GPIOE_FMC_NBL1) |      \
                                     PIN_OSPEED_2M(GPIOE_BUT4) |            \
                                     PIN_OSPEED_2M(GPIOE_BUT6) |            \
                                     PIN_OSPEED_100M(GPIOE_LCD_B0) |        \
                                     PIN_OSPEED_100M(GPIOE_LCD_G0) |        \
                                     PIN_OSPEED_100M(GPIOE_LCD_G1) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D4) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D5) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D6) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D7) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D8) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D9) |        \
                                     PIN_OSPEED_100M(GPIOE_FMC_D10) |       \
                                     PIN_OSPEED_100M(GPIOE_FMC_D11) |       \
                                     PIN_OSPEED_100M(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_BUT4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_BUT6) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_LCD_B0) |     \
                                     PIN_PUPDR_PULLUP(GPIOE_LCD_G0) |     \
                                     PIN_PUPDR_PULLUP(GPIOE_LCD_G1) |     \
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
                                     PIN_MODE_ALTERNATE(GPIOF_LCD_DE) |        \
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
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_100M(GPIOF_FMC_A0) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A1) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A2) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A3) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A4) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A5) |        \
                                     PIN_OSPEED_100M(GPIOF_SPI5_CS) |       \
                                     PIN_OSPEED_100M(GPIOF_SPI5_SCK) |      \
                                     PIN_OSPEED_100M(GPIOF_SPI5_MISO) |     \
                                     PIN_OSPEED_100M(GPIOF_SPI5_MOSI) |     \
                                     PIN_OSPEED_100M(GPIOF_LCD_DE) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_SDNRAS) |    \
                                     PIN_OSPEED_100M(GPIOF_FMC_A6) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A7) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A8) |        \
                                     PIN_OSPEED_100M(GPIOF_FMC_A9))
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
                                     PIN_PUPDR_PULLUP(GPIOF_LCD_DE) |     \
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
                                     PIN_AFIO_AF(GPIOF_LCD_DE, 14) |         \
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
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_100M(GPIOG_FMC_A10) |       \
                                     PIN_OSPEED_100M(GPIOG_FMC_A11) |       \
                                     PIN_OSPEED_100M(GPIOG_FMC_A12) |       \
                                     PIN_OSPEED_2M(GPIOG_BUT3) |            \
                                     PIN_OSPEED_100M(GPIOG_FMC_BA0) |       \
                                     PIN_OSPEED_100M(GPIOG_FMC_BA1) |       \
                                     PIN_OSPEED_100M(GPIOG_LCD_R7) |        \
                                     PIN_OSPEED_100M(GPIOG_LCD_CLK) |       \
                                     PIN_OSPEED_100M(GPIOG_FMC_SDCLK) |     \
                                     PIN_OSPEED_100M(GPIOG_USART6_RX) |     \
                                     PIN_OSPEED_100M(GPIOG_LCD_B2) |        \
                                     PIN_OSPEED_100M(GPIOG_LCD_B3) |        \
                                     PIN_OSPEED_100M(GPIOG_LCD_B1) |        \
                                     PIN_OSPEED_100M(GPIOG_USART1_EN) |     \
                                     PIN_OSPEED_100M(GPIOG_USART6_TX) |     \
                                     PIN_OSPEED_100M(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_BUT3) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA0) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA1) |    \
                                     PIN_PUPDR_PULLUP(GPIOG_LCD_R7) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_LCD_CLK) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDCLK) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_USART6_RX) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_LCD_B2) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_LCD_B3) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_LCD_B1) |     \
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
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_100M(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_100M(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_100M(GPIOH_LCD_R0) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_R1) |        \
                                     PIN_OSPEED_2M(GPIOH_BUT5) |            \
                                     PIN_OSPEED_100M(GPIOH_FMC_SDNWE) |     \
                                     PIN_OSPEED_100M(GPIOH_TIM12_CH1) |     \
                                     PIN_OSPEED_2M(GPIOH_BUT1) |            \
                                     PIN_OSPEED_100M(GPIOH_LCD_R2) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_R3) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_R4) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_R5) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_R6) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_G2) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_G3) |        \
                                     PIN_OSPEED_100M(GPIOH_LCD_G4))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R0) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R1) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_BUT5) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_SDNWE) |  \
                                     PIN_PUPDR_FLOATING(GPIOH_TIM12_CH1) |  \
                                     PIN_PUPDR_FLOATING(GPIOH_BUT1) |       \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R2) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R3) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R4) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R5) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_R6) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_G2) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_G3) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_LCD_G4))
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
 * PI11 - SPI1_CS                   (output pushpull maximum).
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
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_100M(GPIOI_LCD_G5) |        \
                                     PIN_OSPEED_100M(GPIOI_SPI2_SCK) |      \
                                     PIN_OSPEED_100M(GPIOI_SPI2_MISO) |     \
                                     PIN_OSPEED_100M(GPIOI_SPI2_MOSI) |     \
                                     PIN_OSPEED_100M(GPIOI_LCD_B4) |        \
                                     PIN_OSPEED_100M(GPIOI_LCD_B5) |        \
                                     PIN_OSPEED_100M(GPIOI_LCD_B6) |        \
                                     PIN_OSPEED_100M(GPIOI_LCD_B7) |        \
                                     PIN_OSPEED_100M(GPIOI_LCD_BLCTRL) |    \
                                     PIN_OSPEED_100M(GPIOI_LCD_VSYNC) |     \
                                     PIN_OSPEED_100M(GPIOI_LCD_HSYNC) |     \
                                     PIN_OSPEED_100M(GPIOI_SPI2_CS) |       \
                                     PIN_OSPEED_2M(GPIOI_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOI_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOI_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_LCD_G5) |     \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MOSI) |  \
                                     PIN_PUPDR_PULLUP(GPIOI_LCD_B4) |     \
                                     PIN_PUPDR_PULLUP(GPIOI_LCD_B5) |     \
                                     PIN_PUPDR_PULLUP(GPIOI_LCD_B6) |     \
                                     PIN_PUPDR_PULLUP(GPIOI_LCD_B7) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOI_LCD_BLCTRL) |   \
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
                                     PIN_ODR_LOW(GPIOI_LCD_BLCTRL) |       \
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
