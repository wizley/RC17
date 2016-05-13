/*
 * start_robot_main_page.c
 *
 *  Created on: 21 Dec 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"

#include "gui.h"

#include "stdio.h"
#include "usage.h"
#include "encoder.h"
#include "custom_draw.h"


static void guiUpdate(void){
  static char buf[8];
  snprintf(buf, 8, "%+05d", encoder1_2.delta_count[0]);
  gwinSetText(ghLabelE1_count, buf, TRUE);
  snprintf(buf, 8, "%+05d", encoder1_2.delta_count[1]);
  gwinSetText(ghLabelE2_count, buf, TRUE);
  snprintf(buf, 8, "%+05d", encoder3_4.delta_count[0]);
  gwinSetText(ghLabelE3_count, buf, TRUE);
  snprintf(buf, 8, "%+05d", encoder3_4.delta_count[1]);
  gwinSetText(ghLabelE4_count, buf, TRUE);
  snprintf(buf, 8, "%02d", (int) cpu_usage_get_recent());
  gwinSetText(ghLabelCPU_VAL, buf, TRUE);
}

void start_robot_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  guiCreate();

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_IMMEDIATE) == MSG_OK){

      switch(evt->type){
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){

          } else {

          }
          break;
        default:

          break;
      }
    }
    guiUpdate();
    chThdSleepMilliseconds(60);
  }

}


application start_robot = {
    .name = "Start robot",
    .main = start_robot_main
};
