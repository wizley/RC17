/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

/*
 * uGFX port used:  ChibiOS/RT
 *
 * SCK:             GPIOI, 1
 * MISO:            GPIOI, 2
 * MOSI:            GPIOI, 3
 * CS:              GPIOI, 11
 * IRQ:             GPIOA, 12
 *
 * Note that you can tweak the SPI bus speed
 */
static const SPIConfig spicfg = { 0, GPIOI, GPIOI_SPI2_CS,
/*SPI_CR1_BR_2 |*/SPI_CR1_BR_1 | SPI_CR1_BR_0, };

static bool_t init_board(GMouse* m, unsigned driverinstance) {
	(void) m;

	if (driverinstance)
		return FALSE;
	spiStart(&SPID2, &spicfg);
	return TRUE;
}

static inline bool_t getpin_pressed(GMouse* m) {
	(void) m;
	return (!palReadPad(GPIOA, GPIOA_T_IRQ));
}

static inline void aquire_bus(GMouse* m) {
	(void) m;
	spiAcquireBus(&SPID2);
	spiSelect(&SPID2);
}

static inline void release_bus(GMouse* m) {
	(void) m;
	spiUnselect(&SPID2);
	spiReleaseBus(&SPID2);
}

static inline uint16_t read_value(GMouse* m, uint16_t port) {
	static uint8_t txbuf[3] = { 0 };
	static uint8_t rxbuf[3] = { 0 };
	(void) m;

	txbuf[0] = port;

	spiExchange(&SPID2, 3, txbuf, rxbuf);

	return ((uint16_t) rxbuf[1] << 5) | (rxbuf[2] >> 3);
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
