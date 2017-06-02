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

#define BRIGHTNESS_UPPER_LIMIT (100)
#define BRIGHTNESS_LOWER_LIMIT (0)
#define BRIGHTNESS_INCREMENT_STEP (3)

GHandle brightness_bar;

void backlight_main(void* params){
  (void) params;
  ui_event *evt = NULL;
  GHandle pageContainer;
  pageContainer = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);
  gwinShow(pageContainer);
  gwinClear(pageContainer);
  brightness_bar = createProgressBarInContainer(&pageContainer,"LCD Backlight Brightness", 200, 120, 400, 60);
  gwinProgressbarSetRange(brightness_bar, BRIGHTNESS_LOWER_LIMIT, BRIGHTNESS_UPPER_LIMIT);
  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
  gwinRedraw(brightness_bar);
    while(TRUE){

      if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

        switch(evt->type){
          case UI_INPUT_BUTTON:
            if(evt->data.button_state == UI_BUTTON_BACK){
              return;
            }else if(evt->data.button_state == UI_BUTTON_UP){
              if (gwinProgressbarGetPosition(brightness_bar) < BRIGHTNESS_UPPER_LIMIT && gwinProgressbarGetPosition(brightness_bar) > BRIGHTNESS_LOWER_LIMIT){
                  uint8_t nbgn = gdispGetBacklight()+5;
                  gdispSetBacklight(nbgn);
                  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
                  gwinRedraw(brightness_bar);
              }
              //TODO: eeprom to save the brightness
            }else if(evt->data.button_state == UI_BUTTON_DOWN){
              if (gwinProgressbarGetPosition(brightness_bar) < BRIGHTNESS_UPPER_LIMIT && gwinProgressbarGetPosition(brightness_bar) > BRIGHTNESS_LOWER_LIMIT){
                  uint8_t nbgn = gdispGetBacklight()-5;
                  gdispSetBacklight(nbgn);
                  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
                  gwinRedraw(brightness_bar);
              }
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

