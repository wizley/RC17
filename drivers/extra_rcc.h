/*
 * extra_rcc.h
 *
 *  Created on: Jun 10, 2015
 *      Author: u564
 */

#ifndef EXTRA_RCC_H_
#define EXTRA_RCC_H_

#include "stm32_rcc.h"

/**
 * @name    LTDC peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the LTDC peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableLTDC(lp) rccEnableAPB2(RCC_APB2ENR_LTDCEN, lp)

/**
 * @brief   Disables the LTDC peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccDisableLTDC(lp) rccDisableAPB2(RCC_APB2ENR_LTDCEN, lp)

/**
 * @brief   Resets the LTDC peripheral.
 *
 * @api
 */
#define rccResetLTDC() rccResetAPB2(RCC_APB2RSTR_LTDCRST)
/** @} */

/**
 * @name    DMA2D peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the DMA2D peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableDMA2D(lp) rccEnableAHB1(RCC_AHB1ENR_DMA2DEN, lp)

/**
 * @brief   Disables the DMA2D peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccDisableDMA2D(lp) rccDisableAHB1(RCC_AHB1ENR_DMA2DEN, lp)

/**
 * @brief   Resets the DMA2D peripheral.
 *
 * @api
 */
#define rccResetDMA2D() rccResetAHB1(RCC_AHB1RSTR_DMA2DRST)

#endif /* EXTRA_RCC_H_ */
