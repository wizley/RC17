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
#include "motor.h"
#include "loop_stats.h"
#include "custom_draw.h"

static char buf[8];

#define VAL_UPDATE(handle, ...) \
  snprintf(buf, 8, __VA_ARGS__); \
  gwinSetText(handle, buf, TRUE);

static void guiUpdate(void){
  //refresh encoder values
  VAL_UPDATE(ghLabelE1_count, "%+05d", encoder1_2.delta_count[0]);
  VAL_UPDATE(ghLabelE2_count, "%+05d", encoder1_2.delta_count[1]);
  VAL_UPDATE(ghLabelE3_count, "%+05d", encoder3_4.delta_count[0]);
  VAL_UPDATE(ghLabelE4_count, "%+05d", encoder3_4.delta_count[1]);

  //refresh motor values
  VAL_UPDATE(ghLabelM0_Setpoint, "%+05d", M[0].SetPoint);
  VAL_UPDATE(ghLabelM0_Feedback, "%+05d", M[0].Feedback);
  VAL_UPDATE(ghLabelM0_Current, "%05d", M[0].Board.Current);

  VAL_UPDATE(ghLabelM1_Setpoint, "%+05d", M[1].SetPoint);
  VAL_UPDATE(ghLabelM1_Feedback, "%+05d", M[1].Feedback);
  VAL_UPDATE(ghLabelM1_Current, "%05d", M[1].Board.Current);

  VAL_UPDATE(ghLabelM2_Setpoint, "%+05d", M[2].SetPoint);
  VAL_UPDATE(ghLabelM2_Feedback, "%+05d", M[2].Feedback);
  VAL_UPDATE(ghLabelM2_Current, "%05d", M[2].Board.Current);

  VAL_UPDATE(ghLabelM3_Setpoint, "%+05d", M[3].SetPoint);
  VAL_UPDATE(ghLabelM3_Feedback, "%+05d", M[3].Feedback);
  VAL_UPDATE(ghLabelM3_Current, "%05d", M[3].Board.Current);

  VAL_UPDATE(ghLabelM4_Setpoint, "%+05d", M[4].SetPoint);
  VAL_UPDATE(ghLabelM4_Feedback, "%+05d", M[4].Feedback);
  VAL_UPDATE(ghLabelM4_Current, "%05d", M[4].Board.Current);

  VAL_UPDATE(ghLabelM5_Setpoint, "%+05d", M[5].SetPoint);
  VAL_UPDATE(ghLabelM5_Feedback, "%+05d", M[5].Feedback);
  VAL_UPDATE(ghLabelM5_Current, "%05d", M[5].Board.Current);

  VAL_UPDATE(ghLabelM6_Setpoint, "%+05d", M[6].SetPoint);
  VAL_UPDATE(ghLabelM6_Feedback, "%+05d", M[6].Feedback);
  VAL_UPDATE(ghLabelM6_Current, "%05d", M[6].Board.Current);

  VAL_UPDATE(ghLabelM7_Setpoint, "%+05d", M[7].SetPoint);
  VAL_UPDATE(ghLabelM7_Feedback, "%+05d", M[7].Feedback);
  VAL_UPDATE(ghLabelM7_Current, "%05d", M[7].Board.Current);


  VAL_UPDATE(ghLabellp_avg_val, "%05d", (int)loop_stats.avg_loop_us);
  VAL_UPDATE(ghLabellp_max_val, "%05d", (int)loop_stats.max_loop_us);
  VAL_UPDATE(ghLabelcomm_avg_val, "%05d", (int)loop_stats.avg_comm_us);
  VAL_UPDATE(ghLabelcomm_max_val, "%05d", (int)loop_stats.max_comm_us);


  VAL_UPDATE(ghLabelCPU_VAL, "%02d", (int) cpu_usage_get_recent());
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
