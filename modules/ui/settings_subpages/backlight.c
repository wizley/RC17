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

GHandle brightness_bar;

void backlight_main(void* params){
  (void) params;
  ui_event *evt = NULL;
  brightness_bar = createProgressBar(NULL, 200, 120, 400, 60);
  gwinProgressbarSetRange(brightness_bar, 0, 100);
  gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
    while(TRUE){

      if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

        switch(evt->type){
          case UI_INPUT_BUTTON:
            if(evt->data.button_state == UI_BUTTON_BACK){
              return;
            }else if(evt->data.button_state == UI_BUTTON_UP){
              uint8_t nbgn = gdispGetBacklight()+5;
              gdispSetBacklight(nbgn);
              gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
              //TODO: eeprom to save the brightness
            }else if(evt->data.button_state == UI_BUTTON_DOWN){
              uint8_t nbgn = gdispGetBacklight()-5;
              gdispSetBacklight(nbgn);
              gwinProgressbarSetPosition(brightness_bar, gdispGetBacklight());
              //TODO: eeprom to save the brightness
            }
            break;
          default:
            break;
        }
      }
    }

}

application set_backlight = { .name="Set backlight", .main=backlight_main, .syn_flg = no_sync };

