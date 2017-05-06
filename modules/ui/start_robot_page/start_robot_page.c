/*
 * start_robot_main_page.c
 *
 *  Created on: 21 Dec 2015
 *      Author: u564
 */
// This is the page for BLUE field, but not to rename.


#include <blue.h>
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#include "pid.h"
#include "analog.h"
#include "gui.h"

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
char * UIDrivingState[2] = {"activated","deactivated"}; //for ui

// GHandles
GHandle ContainerPage0;
GHandle Console;
GHandle Console1;
GHandle Console2;
GHandle Console3;
GHandle ConsoleDebug;

// Fonts
font_t dejavu_sans_16_anti_aliased;
font_t dejavu_sans_10;
font_t dejavu_sans_12_anti_aliased;
font_t dejavu_sans_24_anti_aliased;
font_t dejavu_sans_32_anti_aliased;

static void createPagePage0(void)
{
  // create container widget: ghContainerPage0
  ContainerPage0 = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);

  // Create console widget: ghConsole
  Console = createConsole(&ContainerPage0, 0, 0, 500, 130);
  gwinSetColor(Console, Silver);
  gwinSetBgColor(Console, Black);
  //gwinSetFont(ghConsole, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console);

  Console2 = createConsole(&ContainerPage0, 0, 131, 300, 350);
  gwinRedraw(Console2);

  Console3 = createConsole(&ContainerPage0, 300, 131, 300, 350);
  gwinRedraw(Console3);

  ConsoleDebug = createConsole(&ContainerPage0, 600, 0, 300, 700);
  gwinRedraw(ConsoleDebug);

  Console1 = createConsole(&ContainerPage0, 270,0,270,130);
  gwinSetColor(Console1, Silver);
  gwinSetBgColor(Console1, Black);
  //gwinSetFont(Console1, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console1);
}

void guiShowPage(unsigned pageIndex)
{
  // Hide all pages
  gwinHide(ContainerPage0);

  // Show page selected page
  switch (pageIndex) {
  case 0:
    gwinShow(ContainerPage0);
    break;

  default:
    break;
  }
}

void guiCreate(void)
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
  createPagePage0();

  // Select the default display page
  guiShowPage(0);

  // Console sample text
  //gwinPrintf(ghConsole, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet");
}

void guiUpdate(){
     gwinClear(Console1);
     gwinPrintf(Console1, UIDrivingState[DrivingState]);
     gwinClear(Console);
     gwinPrintf(Console, "Setpoint: %d ", M[0].SetPoint);
     gwinPrintf(Console, "%d ", M[1].SetPoint);
     gwinPrintf(Console, "%d ", M[2].SetPoint);
     gwinPrintf(Console, "%d\r\n", M[3].SetPoint);
//     gwinPrintf(Console, "stage_flag: %d\r\n", stage1_line_flag_x);
     gwinClear(Console2);
     gwinPrintf(Console2, "x: %d\r\n", x);
     gwinPrintf(Console2, "y: %d\r\n", y);
     gwinPrintf(Console2, "a: %d\r\n", tRotation);
     gwinPrintf(Console2, "E: %d ",E0);
     gwinPrintf(Console2, "%d ",E1);
     gwinPrintf(Console2, "%d\n",E2);
     gwinPrintf(Console2, "L0W : %d    ", LineSensor[0].Position[1]);
     gwinPrintf(Console2, "L0P: %d\n", LineSensor[0].Position[0]);
     gwinPrintf(Console2, "L1W : %d    ", LineSensor[1].Position[1]);
     gwinPrintf(Console2, "L1P: %d\n", LineSensor[1].Position[0]);
     gwinPrintf(Console2, "L2W : %d    ", LineSensor[2].Position[1]);
     gwinPrintf(Console2, "L2P: %d\n", LineSensor[2].Position[0]);
     gwinPrintf(Console2, "L3W : %d    ", LineSensor[3].Position[1]);
     gwinPrintf(Console2, "L3P: %d\n", LineSensor[3].Position[0]);
     gwinPrintf(Console2, "Step: %d\n", step);
//     gwinPrintf(Console2, "LD : %d\n", line_x_d);
     gwinClear(Console3);
//     gwinPrintf(Console3, "OA: %d\r\n", output_line_a);
//     gwinPrintf(Console3, "OX: %d\r\n", output_line_x);
//     gwinPrintf(Console3, "pc1: %d\r\n", pass_line_count[1]);
//     gwinPrintf(Console3, "pc2: %d\r\n", pass_line_count[2]);
//     gwinPrintf(Console3, "pc2: %d\r\n", stage2_line_flag);
     gwinPrintf(Console3, "S7: %d\r\n", Servo1.command[7]);
     gwinPrintf(Console3, "us : %d\n", ADCValue[0]);
     gwinPrintf(Console3, "pl : %d\n", push_length);
     gwinClear(ConsoleDebug);
     gwinPrintf(ConsoleDebug, "D0: %d\r\n", debug_display[0]);
     gwinPrintf(ConsoleDebug, "D1: %d\r\n", debug_display[1]);
     gwinPrintf(ConsoleDebug, "D2: %d\r\n", debug_display[2]);
     gwinPrintf(ConsoleDebug, "D3: %d\r\n", debug_display[3]);
     gwinPrintf(ConsoleDebug, "D4: %d\r\n", debug_display[4]);
     gwinPrintf(ConsoleDebug, "D5: %d\r\n", debug_display[5]);
     gwinPrintf(ConsoleDebug, "D6: %d\r\n", debug_display[6]);
     gwinPrintf(ConsoleDebug, "D7: %d\r\n", debug_display[7]);
     gwinPrintf(ConsoleDebug, "D8: %d\r\n", debug_display[8]);
     gwinPrintf(ConsoleDebug, "D9: %d\n", debug_display[9]);
//     gwinPrintf(Console2, "sum : %d\n", sum);

}

//static char buf[8];
//
//#define VAL_UPDATE(handle, ...) \
//  snprintf(buf, 8, __VA_ARGS__); \
//  gwinSetText(handle, buf, TRUE);
//
//static void guiUpdate(void){
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

void start_robot_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  guiCreate();
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
    guiUpdate();
    chThdSleepMilliseconds(60);
  }

}


application start_robot = {
    .name = "Blue",
    .main = start_robot_main
};
