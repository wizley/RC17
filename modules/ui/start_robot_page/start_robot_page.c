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

#include "start_robot_page_gui.h"

#include "stdio.h"
#include "usage.h"
#include "encoder.h"
#include "motor.h"
#include "loop_stats.h"
#include "custom_draw.h"
#include "log.h"
#include "ds4.h"

static char buf[8];

#define VAL_UPDATE(handle, ...) do {           \
  snprintf(buf, 8, __VA_ARGS__);               \
  gwinSetText(handle, buf, TRUE);              \
} while(0)

static void guiUpdate(void){
  //refresh encoder values
  VAL_UPDATE(ghLabelE1_count, "%+05d", encoder1_2.delta_count[0]);
  VAL_UPDATE(ghLabelE2_count, "%+05d", encoder1_2.delta_count[1]);
  VAL_UPDATE(ghLabelE3_count, "%+05d", encoder3_4.delta_count[0]);
  VAL_UPDATE(ghLabelE4_count, "%+05d", encoder3_4.delta_count[1]);

  //refresh motor values
  VAL_UPDATE(ghLabelM0_Setpoint, "%+05d", M[0].SetPoint);
  if(M[0].timeout)
    VAL_UPDATE(ghLabelM0_Feedback, "%+05d", M[0].Feedback);
  else
    VAL_UPDATE(ghLabelM0_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM0_Current, "%05d", M[0].Board.Current);

  VAL_UPDATE(ghLabelM1_Setpoint, "%+05d", M[1].SetPoint);
  if(M[1].timeout)
    VAL_UPDATE(ghLabelM1_Feedback, "%+05d", M[1].Feedback);
  else
    VAL_UPDATE(ghLabelM1_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM1_Current, "%05d", M[1].Board.Current);

  VAL_UPDATE(ghLabelM2_Setpoint, "%+05d", M[2].SetPoint);
  if(M[2].timeout)
    VAL_UPDATE(ghLabelM2_Feedback, "%+05d", M[2].Feedback);
  else
    VAL_UPDATE(ghLabelM2_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM2_Current, "%05d", M[2].Board.Current);

  VAL_UPDATE(ghLabelM3_Setpoint, "%+05d", M[3].SetPoint);
  if(M[3].timeout)
    VAL_UPDATE(ghLabelM3_Feedback, "%+05d", M[3].Feedback);
  else
    VAL_UPDATE(ghLabelM3_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM3_Current, "%05d", M[3].Board.Current);

  VAL_UPDATE(ghLabelM4_Setpoint, "%+05d", M[4].SetPoint);
  if(M[4].timeout)
    VAL_UPDATE(ghLabelM4_Feedback, "%+05d", M[4].Feedback);
  else
    VAL_UPDATE(ghLabelM4_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM4_Current, "%05d", M[4].Board.Current);

  VAL_UPDATE(ghLabelM5_Setpoint, "%+05d", M[5].SetPoint);
  if(M[5].timeout)
    VAL_UPDATE(ghLabelM5_Feedback, "%+05d", M[5].Feedback);
  else
    VAL_UPDATE(ghLabelM5_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM5_Current, "%05d", M[5].Board.Current);

  VAL_UPDATE(ghLabelM6_Setpoint, "%+05d", M[6].SetPoint);
  if(M[6].timeout)
    VAL_UPDATE(ghLabelM6_Feedback, "%+05d", M[6].Feedback);
  else
    VAL_UPDATE(ghLabelM6_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM6_Current, "%05d", M[6].Board.Current);

  VAL_UPDATE(ghLabelM7_Setpoint, "%+05d", M[7].SetPoint);
  if(M[7].timeout)
    VAL_UPDATE(ghLabelM7_Feedback, "%+05d", M[7].Feedback);
  else
    VAL_UPDATE(ghLabelM7_Feedback, "TIMEOUT");
  VAL_UPDATE(ghLabelM7_Current, "%05d", M[7].Board.Current);


  VAL_UPDATE(ghLabellp_avg_val, "%05d", (int)loop_stats.avg_loop_us);
  VAL_UPDATE(ghLabellp_max_val, "%05d", (int)loop_stats.max_loop_us);
  VAL_UPDATE(ghLabelcomm_avg_val, "%05d", (int)loop_stats.avg_comm_us);
  VAL_UPDATE(ghLabelcomm_max_val, "%05d", (int)loop_stats.max_comm_us);


  VAL_UPDATE(ghLabelCPU_VAL, "%02d", (int) cpu_usage_get_recent());

  gwinCheckboxCheck(ghCheckboxDS4, DS4_IsConnected());
}

void start_robot_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  guiCreate();

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_IMMEDIATE) == MSG_OK){

      switch(evt->type){
        case UI_DS4_BUTTON:
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            gwinDestroy(ghConsole);
            ghConsole = NULL;
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){
            log_i("LoLLoLLoLLoLLoLLoLLoLLoL\n");
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
