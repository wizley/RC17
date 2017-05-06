/*
 * red_page.c
 *
 *  Created on: 2016¦~6¤ë7¤é
 *      Author: Hung
 */


//#include "app_list.h"
#include "red.h"
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#include "pid.h"
#include "analog.h"
//#include "gui.h"

#include "stdio.h"
#include "usage.h"
#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
    #include "motor.h"
#endif
#if USE_ENCODER
#include "encoder.h"
#endif
#if USE_SERVO
#include "servo.h"
#endif
#if USE_LINESENSOR_0 || USE_LINESENSOR_1 || USE_LINESENSOR_2 || USE_LINESENSOR_3
#include "linesensor.h"
#endif
#include "loop_stats.h"
#include "custom_draw.h"
#include "widgets.h"
#include "status_bar.h"
char * UIDrivingState_r[2] = {"activated","deactivated"}; //for ui

// GHandles
GHandle ContainerPage0_r;
GHandle Console_r;
GHandle Console1_r;
GHandle Console2_r;
GHandle Console3_r;
GHandle ConsoleDebug_r;
// Fonts
//font_t dejavu_sans_16_anti_aliased;
//font_t dejavu_sans_10;
//font_t dejavu_sans_12_anti_aliased;
//font_t dejavu_sans_24_anti_aliased;
//font_t dejavu_sans_32_anti_aliased;

static void createPagePage0_r(void)
{
  // create container widget: ghContainerPage0
  ContainerPage0_r = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);

  // Create console widget: ghConsole
  Console_r = createConsole(&ContainerPage0_r, 0, 0, 500, 130);
  gwinSetColor(Console_r, Silver);
  gwinSetBgColor(Console_r, Black);
  //gwinSetFont(ghConsole, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console_r);

  Console2_r = createConsole(&ContainerPage0_r, 0, 131, 300, 350);
  gwinRedraw(Console2_r);

  Console3_r = createConsole(&ContainerPage0_r, 300, 131, 300, 350);
  gwinRedraw(Console3_r);

  ConsoleDebug_r = createConsole(&ContainerPage0_r, 600, 0, 300, 700);
  gwinRedraw(ConsoleDebug_r);

  Console1_r = createConsole(&ContainerPage0_r, 270,0,270,130);
  gwinSetColor(Console1_r, Silver);
  gwinSetBgColor(Console1_r, Black);
//  gwinSetFont(Console1_r, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console1_r);
}

void guiShowPage_r(unsigned pageIndex)
{
  // Hide all pages
  gwinHide(ContainerPage0_r);

  // Show page selected page
  switch (pageIndex) {
  case 0:
    gwinShow(ContainerPage0_r);
    break;

  default:
    break;
  }
}

void guiCreate_r(void)
{
  //GWidgetInit wi;

  // Prepare fonts
//  dejavu_sans_16_anti_aliased = gdispOpenFont("DejaVuSans16_aa");
//  dejavu_sans_10 = gdispOpenFont("DejaVuSans10");
//  dejavu_sans_12_anti_aliased = gdispOpenFont("DejaVuSans12_aa");
//  dejavu_sans_24_anti_aliased = gdispOpenFont("DejaVuSans24_aa");
//  dejavu_sans_32_anti_aliased = gdispOpenFont("DejaVuSans32_aa");

  // Prepare images

  // GWIN settings
//  gwinSetDefaultFont(dejavu_sans_32_anti_aliased);
//  gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
//  gwinSetDefaultColor(Black);
//  gwinSetDefaultBgColor(White);

  // Create all the display pages
  createPagePage0_r();

  // Select the default display page
  guiShowPage_r(0);

  // Console_r sample text
  //gwinPrintf(ghConsole, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet");
}

void guiUpdate_r(){
     gwinClear(Console1_r);
     gwinPrintf(Console1_r, UIDrivingState_r[DrivingState]);
     gwinClear(Console_r);
     gwinPrintf(Console_r, "Setpoint: %d ", M[0].SetPoint);
     gwinPrintf(Console_r, "%d ", M[1].SetPoint);
     gwinPrintf(Console_r, "%d ", M[2].SetPoint);
     gwinPrintf(Console_r, "%d\r\n", M[3].SetPoint);
     //gwinPrintf(Console_r, "stage_flag: %d\r\n", stage1_line_flag_x_r);
     gwinClear(Console2_r);
     gwinPrintf(Console2_r, "x: %d\r\n", x_r);
     gwinPrintf(Console2_r, "y: %d\r\n", y_r);
     gwinPrintf(Console2_r, "a: %d\r\n", tRotation_r);
     gwinPrintf(Console2_r, "E: %d ",E0_r);
     gwinPrintf(Console2_r, "%d ",E1_r);
     gwinPrintf(Console2_r, "%d\n",E2_r);
     gwinPrintf(Console2_r, "L0W : %d    ", LineSensor[0].Position[1]);
     gwinPrintf(Console2_r, "L0P: %d\n", LineSensor[0].Position[0]);
     gwinPrintf(Console2_r, "L1W : %d    ", LineSensor[1].Position[1]);
     gwinPrintf(Console2_r, "L1P: %d\n", LineSensor[1].Position[0]);
     gwinPrintf(Console2_r, "L2W : %d    ", LineSensor[2].Position[1]);
     gwinPrintf(Console2_r, "L2P: %d\n", LineSensor[2].Position[0]);
     gwinPrintf(Console2_r, "L3W : %d    ", LineSensor[3].Position[1]);
     gwinPrintf(Console2_r, "L3P: %d\n", LineSensor[3].Position[0]);
     gwinPrintf(Console2_r, "Step: %d\n", step_r);
     //gwinPrintf(Console2_r, "LD : %d\n", line_x_d_r);
     gwinClear(Console3_r);
     //gwinPrintf(Console3_r, "OA: %d\r\n", output_line_a_r);
     //gwinPrintf(Console3_r, "OX: %d\r\n", output_line_x_r);
     //gwinPrintf(Console3_r, "pc1: %d\r\n", pass_line_count_r[1]);
     //gwinPrintf(Console3_r, "pc2: %d\r\n", pass_line_count_r[2]);
     //gwinPrintf(Console3_r, "pc2: %d\r\n", stage2_line_flag_r);
     gwinPrintf(Console3_r, "S7: %d\r\n", Servo1.command[7]);
     gwinPrintf(Console3_r, "us : %d\n", ADCValue[0]);
     gwinPrintf(Console3_r, "pl : %d\n", push_length_r);
     //gwinPrintf(Console2_r, "sum : %d\n", sum);
     gwinClear(ConsoleDebug_r);
     gwinPrintf(ConsoleDebug_r, "D0: %d\r\n", debug_display_r[0]);
     gwinPrintf(ConsoleDebug_r, "D1: %d\r\n", debug_display_r[1]);
     gwinPrintf(ConsoleDebug_r, "D2: %d\r\n", debug_display_r[2]);
     gwinPrintf(ConsoleDebug_r, "D3: %d\r\n", debug_display_r[3]);
     gwinPrintf(ConsoleDebug_r, "D4: %d\r\n", debug_display_r[4]);
     gwinPrintf(ConsoleDebug_r, "D5: %d\r\n", debug_display_r[5]);
     gwinPrintf(ConsoleDebug_r, "D6: %d\r\n", debug_display_r[6]);
     gwinPrintf(ConsoleDebug_r, "D7: %d\r\n", debug_display_r[7]);
     gwinPrintf(ConsoleDebug_r, "D8: %d\r\n", debug_display_r[8]);
     gwinPrintf(ConsoleDebug_r, "D9: %d\n", debug_display_r[9]);
}

//static char buf[8];
//
//#define VAL_UPDATE(handle, ...) \
//  snprintf(buf, 8, __VA_ARGS__); \
//  gwinSetText(handle, buf, TRUE);
//
//static void guiUpdate_r(void){
//  //refresh encoder values
//  VAL_UPDATE(ghLabelE1_count, "%+05d", encoder1_2.delta_count[0]);
//  VAL_UPDATE(ghLabelE2_count, "%+05d", encoder1_2.delta_count[1]);
//  VAL_UPDATE(ghLabelE3_count, "%+05d", encoder3_4.delta_count[0]);
//  VAL_UPDATE(ghLabelE4_count, "%+05d", encoder3_4.delta_count[1]);
//
//  //refresh motor values
//  VAL_UPDATE(ghLabelM0_Setpoint, "%+05d", M[0].SetPoint);
//  VAL_UPDATE(ghLabelM0_Feedback, "%+05d", M[0].Feedback);
//  VAL_UPDATE(ghLabelM0_Current, "%05d", M[0].Board.Current);
//
//  VAL_UPDATE(ghLabelM1_Setpoint, "%+05d", M[1].SetPoint);
//  VAL_UPDATE(ghLabelM1_Feedback, "%+05d", M[1].Feedback);
//  VAL_UPDATE(ghLabelM1_Current, "%05d", M[1].Board.Current);
//
//  VAL_UPDATE(ghLabelM2_Setpoint, "%+05d", M[2].SetPoint);
//  VAL_UPDATE(ghLabelM2_Feedback, "%+05d", M[2].Feedback);
//  VAL_UPDATE(ghLabelM2_Current, "%05d", M[2].Board.Current);
//
//  VAL_UPDATE(ghLabelM3_Setpoint, "%+05d", M[3].SetPoint);
//  VAL_UPDATE(ghLabelM3_Feedback, "%+05d", M[3].Feedback);
//  VAL_UPDATE(ghLabelM3_Current, "%05d", M[3].Board.Current);
//
//  VAL_UPDATE(ghLabelM4_Setpoint, "%+05d", M[4].SetPoint);
//  VAL_UPDATE(ghLabelM4_Feedback, "%+05d", M[4].Feedback);
//  VAL_UPDATE(ghLabelM4_Current, "%05d", M[4].Board.Current);
//
//  VAL_UPDATE(ghLabelM5_Setpoint, "%+05d", M[5].SetPoint);
//  VAL_UPDATE(ghLabelM5_Feedback, "%+05d", M[5].Feedback);
//  VAL_UPDATE(ghLabelM5_Current, "%05d", M[5].Board.Current);
//
//  VAL_UPDATE(ghLabelM6_Setpoint, "%+05d", M[6].SetPoint);
//  VAL_UPDATE(ghLabelM6_Feedback, "%+05d", M[6].Feedback);
//  VAL_UPDATE(ghLabelM6_Current, "%05d", M[6].Board.Current);
//
//  VAL_UPDATE(ghLabelM7_Setpoint, "%+05d", M[7].SetPoint);
//  VAL_UPDATE(ghLabelM7_Feedback, "%+05d", M[7].Feedback);
//  VAL_UPDATE(ghLabelM7_Current, "%05d", M[7].Board.Current);
//
//
//  VAL_UPDATE(ghLabellp_avg_val, "%05d", (int)loop_stats.avg_loop_us);
//  VAL_UPDATE(ghLabellp_max_val, "%05d", (int)loop_stats.max_loop_us);
//  VAL_UPDATE(ghLabelcomm_avg_val, "%05d", (int)loop_stats.avg_comm_us);
//  VAL_UPDATE(ghLabelcomm_max_val, "%05d", (int)loop_stats.max_comm_us);
//
//
//  VAL_UPDATE(ghLabelCPU_VAL, "%02d", (int) cpu_usage_get_recent());
//}

void red_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  guiCreate_r();
  //ActivateDriving();//lock motor
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
        case UI_STATUSBAR_TICK:
             status_bar_redraw();
          break;
        default:
          break;
      }
    }
    guiUpdate_r();
    chThdSleepMilliseconds(60);
  }

}


application red = {
    .name = "Red",
    .main = red_main
};
