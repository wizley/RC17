/*
 ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
 2011,2012 Giovanni Di Sirio.

 This file is part of ChibiOS/RT.

 ChibiOS/RT is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 ChibiOS/RT is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file    qei.c
 * @brief   QEI Driver code.
 *
 * @addtogroup QEI
 * @{
 */

#include "ch.h"
#include "hal.h"
#include "drivers.h"

#if DRIVER_USE_QEI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   QEI Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void qeiInit(void) {

	qei_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p QEIDriver structure.
 *
 * @param[out] qeip     pointer to the @p QEIDriver object
 *
 * @init
 */
void qeiObjectInit(QEIDriver *qeip) {

	qeip->state = QEI_STOP;
	qeip->last = 0;
	qeip->config = NULL;
}

/**
 * @brief   Configures and activates the QEI peripheral.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 * @param[in] config    pointer to the @p QEIConfig object
 *
 * @api
 */
void qeiStart(QEIDriver *qeip, const QEIConfig *config) {

	chDbgCheck((qeip != NULL) && (config != NULL));

	chSysLock();
	chDbgAssert((qeip->state == QEI_STOP) || (qeip->state == QEI_READY),
			"invalid state");
	qeip->config = config;
	qei_lld_start(qeip);
	qeip->state = QEI_READY;
	chSysUnlock();
}

/**
 * @brief   Deactivates the QEI peripheral.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 *
 * @api
 */
void qeiStop(QEIDriver *qeip) {

	chDbgCheck(qeip != NULL);

	chSysLock();
	chDbgAssert((qeip->state == QEI_STOP) || (qeip->state == QEI_READY),
			"invalid state");
	qei_lld_stop(qeip);
	qeip->state = QEI_STOP;
	chSysUnlock();
}

/**
 * @brief   Enables the quadrature encoder interface.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 *
 * @api
 */
void qeiEnable(QEIDriver *qeip) {

	chDbgCheck(qeip != NULL);

	chSysLock();
	chDbgAssert(qeip->state == QEI_READY, "invalid state");
	qei_lld_enable(qeip);
	qeip->state = QEI_ACTIVE;
	chSysUnlock();
}

/**
 * @brief   Disables the quadrature encoder interface.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 *
 * @api
 */
void qeiDisable(QEIDriver *qeip) {

	chDbgCheck(qeip != NULL);

	chSysLock();
	chDbgAssert((qeip->state == QEI_READY) || (qeip->state == QEI_ACTIVE),
			"invalid state");
	qei_lld_disable(qeip);
	qeip->state = QEI_READY;
	chSysUnlock();
}

/**
 * @brief   Returns the counter value.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 * @return              The current counter value.
 *
 * @api
 */
qeicnt_t qeiGetCount(QEIDriver *qeip) {
	qeicnt_t cnt;

	chSysLock();
	cnt = qeiGetCountI(qeip);
	chSysUnlock();

	return cnt;
}

/**
 * @brief   Returns the counter delta from last reading.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 * @return              The delta from last read.
 *
 * @api
 */
qeidelta_t qeiUpdate(QEIDriver *qeip) {
	qeicnt_t diff;

	chSysLock();
	diff = qeiUpdateI(qeip);
	chSysUnlock();

	return diff;
}

/**
 * @brief   Returns the counter delta from last reading.
 *
 * @param[in] qeip      pointer to the @p QEIDriver object
 * @return              The delta from last read.
 *
 * @iclass
 */
qeidelta_t qeiUpdateI(QEIDriver *qeip) {
	qeicnt_t cnt;
	qeidelta_t delta;

	chDbgCheckClassI();
	chDbgCheck(qeip != NULL);
	chDbgAssert((qeip->state == QEI_READY) || (qeip->state == QEI_ACTIVE),
			"invalid state");

	cnt = qei_lld_get_count(qeip);
	delta = cnt - qeip->last;
	qeip->last = cnt;

	return delta;
}

#endif /* DRIVER_USE_QEI */

/** @} */
