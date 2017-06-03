/*
 * backlight.c
 *
 *  Created on: Apr 30, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#include "widgets.h"
#include "status_bar.h"
#include "drivers.h"

#define BRIGHTNESS_UPPER_LIMIT (100)
#define BRIGHTNESS_LOWER_LIMIT (0)
#define BRIGHTNESS_INCREMENT_STEP (3)

GHandle brightness_bar;

void backlight_main(void* params){
  (void) params;
  I2CEepromFileStream file;

  static uint8_t buf[10] = {0};

  static I2CEepromFileConfig eepcfg = {
    0,
    _24LC02_SIZE_,
    _24LC02_SIZE_,
    _24LC024H_PAGESIZE_,
    MS2ST(5),
    &I2CD1,
    0b1010000,
    buf
  };

  I2CEepromFileOpen(&file, &eepcfg, EepromFindDevice("24XX"));

  ui_event *evt = NULL;
  GHandle pageContainer;
  pageContainer = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);
  gwinShow(pageContainer);
  gwinClear(pageContainer);
  brightness_bar = createProgressBarInContainer(&pageContainer,"brightness", 200, 120, 400, 60);
  gwinProgressbarSetRange(brightness_bar, BRIGHTNESS_LOWER_LIMIT, BRIGHTNESS_UPPER_LIMIT);
  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
  gwinRedraw(brightness_bar);
    while(TRUE){

      if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

        switch(evt->type){
          case UI_INPUT_BUTTON:
            if(evt->data.button_state == UI_BUTTON_BACK){
              eepfs_lseek(&file, _PROM_LCD_BRIGHTNESS);
              if (EepromWriteByte((EepromFileStream *)&file, gdispGetBacklight()) == 1){
                eepfs_close((EepromFileStream *)&file);
                return;}
            }else if(evt->data.button_state == UI_BUTTON_UP){
                  uint8_t nbgn = gdispGetBacklight()+BRIGHTNESS_INCREMENT_STEP;
                  gdispSetBacklight(nbgn);
                  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
                  gwinRedraw(brightness_bar);
              //TODO: eeprom to save the brightness
            }else if(evt->data.button_state == UI_BUTTON_DOWN){
                  uint8_t nbgn = gdispGetBacklight()-BRIGHTNESS_INCREMENT_STEP;
                  gdispSetBacklight(nbgn);
                  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
                  gwinRedraw(brightness_bar);
              //TODO: eeprom to save the brightness
            }
            break;
          case UI_STATUSBAR_TICK:
               status_bar_redraw();
            break;
          default:
            break;
        }
      }
    }

}

application set_backlight = { .name="Set backlight", .main=backlight_main};

