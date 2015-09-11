/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH			800
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT			480
#endif


#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
