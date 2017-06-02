/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define CTRL_PORT GPIOI
#define CTRL_PIN  GPIOI_LCD_BLCTRL

static const ltdcConfig driverCfg = {
	800, 480,								// Width, Height (pixels)
	300, 100,									// Horizontal, Vertical sync (pixels)
	0, 0,									// Horizontal, Vertical back porch (pixels)
	0, 0,									// Horizontal, Vertical front porch (pixels)
	0,										// Sync flags
	0x000000,								// Clear color (RGB888)

	{										// Background layer config
		(LLDCOLOR_TYPE *)0xC0000000,	// Frame buffer address
		800, 480,							// Width, Height (pixels)
		800 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		800, 480,							// Size of virtual layer (cx, cy)
		LTDC_COLOR_FUCHSIA,					// Default color (ARGB8888)
		0x980088,							// Color key (RGB888)
		LTDC_BLEND_FIX1_FIX2,				// Blending factors
		0,									// Palette (RGB888, can be NULL)
		0,									// Palette length
		0xFF,								// Constant alpha factor
		LTDC_LEF_ENABLE						// Layer configuration flags
	},

	LTDC_UNUSED_LAYER_CONFIG				// Foreground layer config
};

static GFXINLINE void init_board(GDisplay* g) {

	// As we are not using multiple displays we set g->board to NULL as we don't use it.
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:											// Set up for Display 0
	  /* PLLSAI activation.*/
//    RCC->PLLSAICFGR = STM32_PLLSAIN | STM32_PLLSAIR | STM32_PLLSAIQ;
//    RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | STM32_PLLSAIR_POST;
//    RCC->CR |= RCC_CR_PLLSAION;
		break;

	}
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void)g;
	/* EasyScale setup */
  chThdSleepMicroseconds(100);
  palSetPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(200);
  palClearPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(500);
  palSetPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(100);
}

static GFXINLINE void easyscale_sendhigh(void)
{
  palClearPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(20);
  palSetPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(80);
}

static GFXINLINE void easyscale_sendlow(void)
{
  palClearPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(80);
  palSetPad(CTRL_PORT, CTRL_PIN);
  chThdSleepMicroseconds(20);
}

static GFXINLINE void set_backlight_lld(GDisplay* g, uint8_t percent)
{
	(void)g;
	uint8_t data = percent / 3.22f;
	if(data == 0) data = 1;

	chThdSleepMicroseconds(10);
  //fixed device address:
	easyscale_sendlow();
	easyscale_sendhigh();
	easyscale_sendhigh();
	easyscale_sendhigh();
  easyscale_sendlow();
  easyscale_sendlow();
  easyscale_sendhigh();
  easyscale_sendlow();

  palClearPad(CTRL_PORT, CTRL_PIN);//Teos
  chThdSleepMicroseconds(100);
  palSetPad(CTRL_PORT, CTRL_PIN);//Tstart
  chThdSleepMicroseconds(10);

  easyscale_sendlow();//rfa
  easyscale_sendlow();//a1
  easyscale_sendlow();//a0

  for (int i = 4; i >= 0; i--) {  //msb to lsb
    if (data & (0x1 << i)) { //bitread: 0 is lsb
      easyscale_sendhigh();
    }
    else {easyscale_sendlow();
    }
  }

  palClearPad(CTRL_PORT, CTRL_PIN); //Teos
  chThdSleepMicroseconds(100);
  palSetPad(CTRL_PORT, CTRL_PIN);//Tstart
  chThdSleepMicroseconds(10);
}

#endif /* _GDISP_LLD_BOARD_H */
