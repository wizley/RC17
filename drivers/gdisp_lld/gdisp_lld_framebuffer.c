/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"
#include "stm32_dma2d.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_STM32_LTDC_DMA2D
#include "gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"
#include "drivers.h"

#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

/*===========================================================================*/
/* LTDC related.                                                             */
/*===========================================================================*/

static uint8_t screen[800 * 480 * 2] __attribute__((section(".sdram")));
//static uint8_t fb[800 * 480 * 2] __attribute__((section(".sdram")));


//static uint8_t view_buffer[800 * 480]__attribute__((section(".sdram")));

//extern const ltdc_color_t wolf3d_palette[256];

static const ltdc_window_t ltdc_fullscreen_wincfg = {
    0,
    800 - 1,
    0,
    480 - 1
};

/*static const ltdc_frame_t ltdc_view_frmcfg1 = {
  view_buffer,
  800,
  480,
  800 * sizeof(uint8_t),
  LTDC_FMT_L8
};*/

/*static const ltdc_laycfg_t ltdc_view_laycfg1 = {
  &ltdc_view_frmcfg1,
  &ltdc_fullscreen_wincfg,
  LTDC_COLOR_RED,
  0xFF,
  0,//0x980088,
  wolf3d_palette,
  256,
  LTDC_BLEND_FIX1_FIX2,
  LTDC_LEF_ENABLE //| LTDC_LEF_PALETTE
};*/

static const ltdc_frame_t ltdc_screen_frmcfg1 = {
    screen,
    800,
    480,
    800 * 2,
	LTDC_FMT_RGB565
};

static const ltdc_laycfg_t ltdc_bg_laycfg1 = {
    &ltdc_screen_frmcfg1,
    &ltdc_fullscreen_wincfg,
    LTDC_COLOR_RED,
    0xFF,
    0x980088,//0x980088,
    NULL,
    0,
    LTDC_BLEND_FIX1_FIX2,
    LTDC_LEF_ENABLE
};

static const LTDCConfig ltdc_cfg = {
    /* Display specifications.*/
    800,                              /**< Screen pixel width.*/
    480,                              /**< Screen pixel height.*/
    256,                               /**< Horizontal sync pixel width.*/
    45,                                /**< Vertical sync pixel height.*/
    0,                               /**< Horizontal back porch pixel width.*/
    0,                                /**< Vertical back porch pixel height.*/
    0,                               /**< Horizontal front porch pixel width.*/
    0,                                /**< Vertical front porch pixel height.*/
    0,                                /**< Driver configuration flags.*/

    /* ISR callbacks.*/
    NULL,                             /**< Line Interrupt ISR, or @p NULL.*/
    NULL,                             /**< Register Reload ISR, or @p NULL.*/
    NULL,                             /**< FIFO Underrun ISR, or @p NULL.*/
    NULL,                             /**< Transfer Error ISR, or @p NULL.*/

    /* Color and layer settings.*/
    LTDC_COLOR_BLUE,
    NULL,//&ltdc_view_laycfg1,
    &ltdc_bg_laycfg1
};

extern LTDCDriver LTDCD1;



//static uint8_t fb[800 * 480 * 3] __attribute__((section(".sdram")));
//static uint8_t *buff_pt_ltdc;

static dma2d_laycfg_t dma2d_frame_laycfg = {
  screen,
  0,
  DMA2D_FMT_RGB565,
  DMA2D_COLOR_AQUA,
  0xFF,
  NULL
};

static const DMA2DConfig dma2d_cfg = {
    /* ISR callbacks.*/
    NULL,     /**< Configuration error, or @p NULL.*/
    NULL,     /**< Palette transfer done, or @p NULL.*/
    NULL,     /**< Palette access error, or @p NULL.*/
    NULL,     /**< Transfer watermark, or @p NULL.*/
    NULL,     /**< Transfer complete, or @p NULL.*/
    NULL      /**< Transfer error, or @p NULL.*/
};

/*static const dma2d_palcfg_t dma2d_palcfg = {
  wolf3d_palette,
  256,
  DMA2D_FMT_ARGB8888
};

static const dma2d_laycfg_t dma2d_bg_laycfg = {
  view_buffer,
  0,
  DMA2D_FMT_L8,
  DMA2D_COLOR_RED,
  0xFF,
  &dma2d_palcfg
};*/

/*static const dma2d_laycfg_t dma2d_fg_laycfg = {
  (void *)wolf3d_vgagraph_chunk87,
  0,
  DMA2D_FMT_L8,
  DMA2D_COLOR_LIME,
  0xFF,
  &dma2d_palcfg
};*/

/*static const dma2d_laycfg_t dma2d_frame_laycfg = {
  frame_buffer,
  0,
  DMA2D_FMT_RGB888,
  DMA2D_COLOR_BLUE,
  0xFF,
  NULL
};*/

/*===========================================================================*/
/* Driver local routines    .                                                */
/*===========================================================================*/
#define PIXIL_POS(g, x, y)		((y) * 800 * 2 + (x) * 2)
#define PIXEL_ADDR(g, pos)		((LLDCOLOR_TYPE *)((uint8_t *)screen+pos))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {

  /* No board interface and no private driver area */
  	g->priv = g->board = 0;

  	/* Initialise the GDISP structure */
  	g->g.Width = GDISP_SCREEN_WIDTH;
  	g->g.Height = GDISP_SCREEN_HEIGHT;
  	g->g.Orientation = GDISP_ROTATE_180;
  	g->g.Powermode = powerOn;
  	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
  	g->g.Contrast = GDISP_INITIAL_CONTRAST;

  	ltdcStart(&LTDCD1, &ltdc_cfg);

  	/*
    * Activates the DMA2D-related drivers.
    */
  	dma2dStart(&DMA2DD1, &dma2d_cfg);

  	DMA2DDriver *const dma2dp = &DMA2DD1;
//
  	dma2d_frame_laycfg.bufferp = screen;//buff_pt_ltdc;
  	dma2dOutSetConfig(dma2dp, &dma2d_frame_laycfg);
//
//  	dma2d_frame_laycfg.bufferp = fb;
//  	dma2dFgSetConfig(dma2dp, &dma2d_frame_laycfg);
//  	dma2dJobSetMode(dma2dp, DMA2D_JOB_COPY);
//  	dma2dJobSetSize(dma2dp, 800, 480);

  	return TRUE;
}


#if GDISP_HARDWARE_DRAWPIXEL
LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {

	if(g->p.x > g->g.Width - 1 || g->p.y > g->g.Height - 1) return;

  unsigned	pos;
  pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);
  PIXEL_ADDR(g, pos)[0] = gdispColor2Native(g->p.color);
}
#endif

#if GDISP_HARDWARE_FILLS
LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {

	DMA2DDriver *const dma2dp = &DMA2DD1;
	dma2dAcquireBus(dma2dp);

//	dma2dFgSetConfig(dma2dp, &dma2d_fg_laycfg);
	dma2dJobSetMode(dma2dp, DMA2D_JOB_CONST);
	dma2dOutSetDefaultColor(dma2dp, gdispColor2Native(g->p.color));
	dma2dOutSetAddress(dma2dp, dma2dComputeAddress(
			screen, 800*2, DMA2D_FMT_RGB565,
			800 - g->p.x - g->p.cx,
			480 - g->p.y - g->p.cy
	));
	dma2dOutSetWrapOffset(dma2dp, 800 - g->p.cx);
	dma2dJobSetSize(dma2dp, g->p.cx, g->p.cy);
	dma2dJobExecute(dma2dp);

	dma2dReleaseBus(dma2dp);
	//g->flags |= GDISP_FLG_DRIVER;
}
#endif

#if GDISP_HARDWARE_BITFILLS
LLDSPEC void gdisp_lld_blit_area(GDisplay* g) {
	DMA2DDriver *const dma2dp = &DMA2DD1;
	dma2dAcquireBus(dma2dp);

	dma2d_frame_laycfg.bufferp = g->p.ptr;
	dma2d_frame_laycfg.wrap_offset = 800 - g->p.cx;
	dma2dFgSetConfig(dma2dp, &dma2d_frame_laycfg);
	dma2dJobSetMode(dma2dp, DMA2D_JOB_COPY);
	//dma2dOutSetDefaultColor(dma2dp, gdispColor2Native(g->p.color));
	dma2dOutSetAddress(dma2dp, dma2dComputeAddress(
			screen, 800*2, DMA2D_FMT_RGB565,
			GDISP_SCREEN_WIDTH - g->p.x - g->p.cx,
			GDISP_SCREEN_HEIGHT - g->p.y - g->p.cy
	));
	dma2dOutSetWrapOffset(dma2dp, 800 - g->p.cx);
	dma2dJobSetSize(dma2dp, g->p.cx, g->p.cy);
	dma2dJobExecute(dma2dp);

	dma2d_frame_laycfg.wrap_offset = 0;

	dma2dReleaseBus(dma2dp);
	//g->flags |= GDISP_FLG_DRIVER;
}

#endif

#if GDISP_HARDWARE_PIXELREAD
LLDSPEC color_t gdisp_lld_get_pixel_color(GDisplay *g) {
  unsigned    pos;
  LLDCOLOR_TYPE color;

  pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);

  color = PIXEL_ADDR(g, pos)[0];
  return gdispNative2Color(color);
}
#endif

#if GDISP_HARDWARE_FLUSH
LLDSPEC void gdisp_lld_flush(GDisplay *g) {
  (void) g;
//  DMA2DDriver *const dma2dp = &DMA2DD1;
//  dma2dAcquireBus(dma2dp);
//
//  dma2d_frame_laycfg.bufferp = screen;
//  dma2dOutSetConfig(dma2dp, &dma2d_frame_laycfg);
//
//  dma2d_frame_laycfg.bufferp = fb;
//  dma2dFgSetConfig(dma2dp, &dma2d_frame_laycfg);
//  dma2dJobSetMode(dma2dp, DMA2D_JOB_COPY);
//  dma2dJobSetSize(dma2dp, 800, 480);
//  dma2dJobExecute(dma2dp);
//  dma2dReleaseBus(dma2dp);
}
#endif

#if GDISP_NEED_SCROLL && GDISP_HARDWARE_SCROLL
LLDSPEC void gdisp_lld_vertical_scroll(GDisplay *g) {
	rect.bottom = g->g.Height - g->p.y;
	rect.top = rect.bottom-g->p.cy;
	rect.right = g->g.Width - g->p.x;
	rect.left = rect.right-g->p.cx;
	lines = g->p.y1;
}
#endif

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC void gdisp_lld_write_start(GDisplay* g) {
	acquire_bus(g);
	set_viewport(g);
}
LLDSPEC void gdisp_lld_write_color(GDisplay* g) {
	write_data(g, gdispColor2Native(g->p.color));
}
LLDSPEC void gdisp_lld_write_stop(GDisplay* g) {
	release_bus(g);
}
LLDSPEC void gdisp_lld_write_pos(GDisplay* g) {
	set_cursor(g);
}
#endif

#if GDISP_HARDWARE_STREAM_READ
LLDSPEC void gdisp_lld_read_start(GDisplay* g) {
	acquire_bus(g);
	set_viewport(g);
	set_cursor(g);
	setreadmode(g);
	dummy_read(g);
}
LLDSPEC color_t gdisp_lld_read_color(GDisplay* g) {
	uint16_t	data;

	data = read_data(g);
	return gdispNative2Color(data);
}
LLDSPEC void gdisp_lld_read_stop(GDisplay* g) {
	setwritemode(g);
	release_bus(g);
}
#endif



#endif /* GFX_USE_GDISP */
