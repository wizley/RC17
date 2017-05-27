/*
 * motor_test_page.c
 *
 *  Created on: Aug 21, 2016
 *      Author: Melvin
 */

#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#include "motor_test_page_gui.h"
#include "stdio.h"
#include "motor.h"
#include "custom_draw.h"
#include "widgets.h"
#include "status_bar.h"
#include "encoder.h"
#include "loop_stats.h"
#include "log.h"
#include "ds4.h"

void motor_test_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  //guiCreate();

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_IMMEDIATE) == MSG_OK){

      switch(evt->type){
        case UI_DS4_BUTTON:
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){

          } else {

          }
          break;
        case UI_STATUSBAR_TICK:
           status_bar_redraw();
          break;
        default:

          break;
      }
    }
    //guiUpdate();
    chThdSleepMilliseconds(60);
  }

}


application motor_test_app = {
    .name = "Motor Test",
    .main = motor_test_main
};
