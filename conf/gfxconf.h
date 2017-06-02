#ifndef _GFXCONF_H
#define _GFXCONF_H


///////////////////////////////////////////////////////////////////////////
// GOS - One of these must be defined, preferably in your Makefile       //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_OS_CHIBIOS                           TRUE


// Options that (should where relevant) apply to all operating systems
#define GFX_NO_OS_INIT                           TRUE


///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP                                TRUE

#define GDISP_NEED_AUTOFLUSH                         FALSE
#define GDISP_NEED_TIMERFLUSH                        FALSE
//#define GDISP_NEED_VALIDATION                        TRUE
#define GDISP_NEED_CLIP                              TRUE
#define GDISP_NEED_CIRCLE                            TRUE
//#define GDISP_NEED_ELLIPSE                           FALSE
//#define GDISP_NEED_ARC                               FALSE
//#define GDISP_NEED_ARCSECTORS                        FALSE
//#define GDISP_NEED_CONVEX_POLYGON                    FALSE
#define GDISP_NEED_SCROLL                            TRUE
#define GDISP_NEED_PIXELREAD                         TRUE
#define GDISP_NEED_CONTROL                           TRUE
//#define GDISP_NEED_QUERY                             FALSE
//#define GDISP_NEED_STREAMING                         FALSE
#define GDISP_NEED_MULTITHREAD                       TRUE
#define GDISP_DEFAULT_ORIENTATION GDISP_ROTATE_180
//#define GDISP_LINEBUF_SIZE                           128

#define GDISP_STARTUP_COLOR                          HTML2COLOR(0x00499C)
#define GDISP_NEED_STARTUP_LOGO                      FALSE
#define GFX_USE_GFILE                                TRUE
#define GFILE_NEED_ROMFS                             TRUE

/********************************************************/
/* Font stuff                                           */
/********************************************************/
#define GDISP_NEED_TEXT                              TRUE
#define GDISP_NEED_ANTIALIAS                         TRUE
//    #define GDISP_NEED_UTF8                          FALSE
#define GDISP_NEED_TEXT_KERNING                      TRUE
//    #define GDISP_INCLUDE_FONT_UI1                   FALSE
#define GDISP_INCLUDE_FONT_UI2                       TRUE		// The smallest preferred font.
//    #define GDISP_INCLUDE_FONT_LARGENUMBERS          FALSE
//#define GDISP_INCLUDE_FONT_DEJAVUSANS10              TRUE
//#define GDISP_INCLUDE_FONT_DEJAVUSANS12              TRUE
//#define GDISP_INCLUDE_FONT_DEJAVUSANS16              TRUE
//#define GDISP_INCLUDE_FONT_DEJAVUSANS20              TRUE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12      FALSE
//    #define GDISP_INCLUDE_FONT_FIXED_10X20           FALSE
//    #define GDISP_INCLUDE_FONT_FIXED_7X14            FALSE
//    #define GDISP_INCLUDE_FONT_FIXED_5X8             FALSE
#define GDISP_INCLUDE_FONT_DEJAVUSANS12_AA             TRUE
#define GDISP_INCLUDE_FONT_DEJAVUSANS16_AA             TRUE
#define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA             TRUE
#define GDISP_INCLUDE_FONT_DEJAVUSANS24_AA             TRUE
#define GDISP_INCLUDE_FONT_DEJAVUSANS32_AA             TRUE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12_AA   FALSE
#define GDISP_INCLUDE_USER_FONTS                       TRUE

#define GDISP_NEED_IMAGE                               TRUE
    #define GDISP_NEED_IMAGE_NATIVE                    FALSE
    #define GDISP_NEED_IMAGE_GIF                       TRUE
    #define GDISP_NEED_IMAGE_BMP                       FALSE
//        #define GDISP_NEED_IMAGE_BMP_1               FALSE
//        #define GDISP_NEED_IMAGE_BMP_4               FALSE
//        #define GDISP_NEED_IMAGE_BMP_4_RLE           FALSE
//        #define GDISP_NEED_IMAGE_BMP_8               FALSE
//        #define GDISP_NEED_IMAGE_BMP_8_RLE           FALSE
//        #define GDISP_NEED_IMAGE_BMP_16              FALSE
//        #define GDISP_NEED_IMAGE_BMP_24              FALSE
//        #define GDISP_NEED_IMAGE_BMP_32              FALSE
    #define GDISP_NEED_IMAGE_JPG                       FALSE
    #define GDISP_NEED_IMAGE_PNG                       FALSE
//    #define GDISP_NEED_IMAGE_ACCOUNTING              FALSE

#define GDISP_NEED_PIXMAP                            FALSE
//    #define GDISP_NEED_PIXMAP_IMAGE                  FALSE


/********************************************************/
/* GWIN stuff                                           */
/********************************************************/
#define GFX_USE_GWIN TRUE

#define GWIN_NEED_WINDOWMANAGER TRUE
    #define GWIN_REDRAW_IMMEDIATE TRUE
    #define GWIN_REDRAW_SINGLEOP TRUE

#define GWIN_NEED_CONSOLE TRUE
    #define GWIN_CONSOLE_USE_HISTORY TRUE
        #define GWIN_CONSOLE_HISTORY_AVERAGING TRUE
        #define GWIN_CONSOLE_HISTORY_ATCREATE TRUE
    #define GWIN_CONSOLE_ESCSEQ TRUE
    #define GWIN_CONSOLE_USE_BASESTREAM FALSE
    #define GWIN_CONSOLE_USE_FLOAT TRUE

#define GWIN_NEED_WIDGET TRUE
    #define GWIN_NEED_LABEL TRUE
        #define GWIN_LABEL_ATTRIBUTE FALSE
    #define GWIN_NEED_CHECKBOX TRUE
    #define GWIN_NEED_BUTTON TRUE
        #define GWIN_BUTTON_LAZY_RELEASE FALSE
    #define GWIN_NEED_SLIDER TRUE
    #define GWIN_FLAT_STYLING FALSE

    #define GWIN_NEED_PROGRESSBAR TRUE
        #define GWIN_PROGRESSBAR_AUTO FALSE
#define GWIN_NEED_CONTAINERS TRUE
    #define GWIN_NEED_CONTAINER TRUE
    #define GWIN_NEED_FRAME FALSE
    #define GWIN_NEED_TABSET FALSE


/********************************************************/
/* GTIMER stuff                                         */
/********************************************************/
#define GFX_USE_GTIMER TRUE

#define GTIMER_THREAD_PRIORITY NORMAL_PRIORITY
#define GTIMER_THREAD_WORKAREA_SIZE 2048

/********************************************************/
/* GINPUT stuff                                         */
/********************************************************/
#define GFX_USE_GINPUT TRUE

#define GINPUT_NEED_TOGGLE  FALSE
#define GINPUT_NEED_MOUSE TRUE
#define GINPUT_TOUCH_USER_CALIBRATION_LOAD FALSE
#define GINPUT_TOUCH_NOCALIBRATE_GUI       TRUE


/********************************************************/
/* GEVENT stuff                                         */
/********************************************************/
#define GFX_USE_GEVENT TRUE

#define GEVENT_ASSERT_NO_RESOURCE FALSE
#define GEVENT_MAXIMUM_SIZE 32
#define GEVENT_MAX_SOURCE_LISTENERS 32


/********************************************************/
/* GEVENT stuff                                         */
/********************************************************/
#define GFX_USE_GQUEUE TRUE

#define GQUEUE_NEED_ASYNC TRUE

#define GDISP_TOTAL_DISPLAYS    1
#define GDISP_TOTAL_CONTROLLERS   1

//#define GDISP_PIXELFORMAT GDISP_PIXELFORMAT_RGB565

//#define GDISP_TOTAL_DISPLAYS                         1
//
//#define GDISP_DRIVER_LIST                            GDISPVMT_STM32_LTDC_DMA2D
//    #ifdef GDISP_DRIVER_LIST
//        // For code and speed optimization define as TRUE or FALSE if all controllers have the same capability
//        #define GDISP_HARDWARE_STREAM_WRITE          FALSE
//        #define GDISP_HARDWARE_STREAM_READ           FALSE
//        #define GDISP_HARDWARE_STREAM_POS            FALSE
//        #define GDISP_HARDWARE_DRAWPIXEL             TRUE
//        #define GDISP_HARDWARE_CLEARS                FALSE
//        #define GDISP_HARDWARE_FILLS                 TRUE
//        #define GDISP_HARDWARE_BITFILLS              TRUE
//        #define GDISP_HARDWARE_SCROLL                FALSE
//        #define GDISP_HARDWARE_PIXELREAD             TRUE
//        #define GDISP_HARDWARE_CONTROL               FALSE
//        #define GDISP_HARDWARE_QUERY                 FALSE
//        #define GDISP_HARDWARE_CLIP                  FALSE
//        #define GDISP_HARDWARE_FLUSH                 FALSE
//
//        #define GDISP_PIXELFORMAT                    GDISP_PIXELFORMAT_RGB565
//    #endif
#define GOS_NEED_X_THREADS                             FALSE
#define GOS_NEED_X_HEAP                                FALSE

#endif /* _GFXCONF_H */
