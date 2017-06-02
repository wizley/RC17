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
#include "common.h"
//#include "ps4_usbhost.h"
//#include "gui.h"

#include "stdio.h"
#include "usage.h"
#include "driving.h"
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
#if USE_AIRBOARD_0//defined in driving.h
#include "airboard.h"
#endif
#if USE_DISTANCESENSOR
#include "distancesensor.h"
#endif
#include "loop_stats.h"
#include "custom_draw.h"
#include "widgets.h"
#include "status_bar.h"
char * UIDrivingState_r[2] = {"activated","deactivated"}; //for ui
int oldENvalue = 0;
// GHandles
GHandle ContainerPage0_r;
GHandle Console_r;
GHandle Console1_r;
GHandle Console2_r;
GHandle Console3_r;
GHandle Console4_r;

// Fonts
//font_t dejavu_sans_16_anti_aliased;
//font_t dejavu_sans_10;
//font_t dejavu_sans_12_anti_aliased;
//font_t dejavu_sans_24_anti_aliased;
//font_t dejavu_sans_32_anti_aliased;
//Whole Width = 800
//Whole Height excluding the board connection bar is 480
//Text Height = 31
//Text width around 19px
static void createPagePage0_r(void)
{

  // create container widget: ghContainerPage0
  ContainerPage0_r = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);

  // Create console widget: ghConsole
  Console_r = createConsole(&ContainerPage0_r, 0, 0, 800, 124);
  gwinSetColor(Console_r, Silver);
  gwinSetBgColor(Console_r, Black);
  //gwinSetFont(ghConsole, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console_r);

  Console2_r = createConsole(&ContainerPage0_r, 1, 125, 200, 350);
  gwinRedraw(Console2_r);

  Console3_r = createConsole(&ContainerPage0_r, 200, 125, 200, 350);
  gwinRedraw(Console3_r);

  Console4_r = createConsole(&ContainerPage0_r, 400, 125, 200, 350);
  gwinRedraw(Console4_r);


//  Console1_r = createConsole(&ContainerPage0_r, 1,1,520,130);
//  gwinSetColor(Console1_r, Silver);
//  gwinSetBgColor(Console1_r, Black);
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

void guiUpdate_r(void){
	 RunPath_r();
//     gwinClear(Console1_r);
//     gwinPrintf(Console1_r, UIDrivingState_r[DrivingState]);
     gwinClear(Console_r);
     //gwinPrintf(Console_r, "Setpoint: %d ", (int)((float)m[0].speed_ref_krpm));
//     gwinPrintf(Console_r, "%d\r\n ", (int)((float)m[1].speed_ref_krpm ));
     gwinPrintf(Console_r, "SHT  %4d\033t  ", M[4].SetPoint);
     gwinPrintf(Console_r, "PIT  %4d\033t  ", getPitch());//M[5].Board.ADCValue
     gwinPrintf(Console_r, "ROL  %4d\033t  ", getRoll());//M[4].Board.ADCValue
     gwinPrintf(Console_r, "X  %5d\033t  ", distanceSum);
     gwinPrintf(Console_r, "Y  %5d\033t\r\n", (int)yDistance);
     gwinPrintf(Console_r, "SPUS2 %3d\033t  ", Servo1.command[2]);
     gwinPrintf(Console_r, "SPIT1 %3d\033t  ", Servo1.command[1]);
     gwinPrintf(Console_r, "SROL0 %3d\033t  ", Servo1.command[0]);
     gwinPrintf(Console_r, "ALIVE %3d\033t  \r\n", shooterAlive);
#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
	gwinPrintf(Console_r, "M01X %4d", (int)(m[0].speed_krpm*1000));
	gwinPrintf(Console_r, ",%4d", (int)(m[1].speed_krpm*1000));
    gwinPrintf(Console_r, "  M23U %4d", (int)(m[2].speed_krpm*1000));
    gwinPrintf(Console_r, ",%4d", (int)(m[3].speed_krpm*1000));
    gwinPrintf(Console_r, "  M45S %4d", (int)(m[4].speed_krpm*1000));
    gwinPrintf(Console_r, ",%4d\r\n", (int)(m[5].speed_krpm*1000));
//	gwinPrintf(Console_r, "EN %d\r\n", (int16_t)encoder1_2.delta_count[0]);
//	gwinPrintf(Console_r, "EN %d\r\n", ((int16_t)encoder1_2.delta_count[0] * 0.013521634 / 1.14961122));
//	oldENvalue = (int16_t)encoder1_2.delta_count[0];
#elif !IS_MOTOR_0_2016 && !IS_MOTOR_1_2016
    gwinPrintf(Console_r, "M01X %4d", (int)(M[0].Feedback));
    gwinPrintf(Console_r, ",%4d", (int)(M[1].Feedback));
    gwinPrintf(Console_r, " M23U %4d", (int)(M[2].Feedback));
    gwinPrintf(Console_r, ",%4d", (int)(M[3].Feedback));
    gwinPrintf(Console_r, " M45S %4d", (int)(M[4].Feedback));
    gwinPrintf(Console_r, ",%4d", (int)(M[5].Feedback));
    gwinPrintf(Console_r, " M6Y %4d\r\n", (int)(M[6].Feedback));
//	gwinPrintf(Console_r, "EN %d\r\n", (int16_t)encoder1_2.delta_count[0] * WHEEL_DIAMETER * PI / ENCODER_RESOLUTION );
//	gwinPrintf(Console_r, "EN %d\r\n", ((int16_t)encoder1_2.delta_count[0] - oldENvalue) * WHEEL_DIAMETER * PI / ENCODER_RESOLUTION );
//	oldENvalue = (int16_t)encoder1_2.delta_count[0];
#endif
//     gwinPrintf(Console_r, "ls0", LineSensor2016[0].position);
//     if(carState_r == MANUAL_STATE) {
//    	 gwinPrintf(Console_r, "MANUAL STATE\r\n");
//     }
//     else if(carState_r == AUTO_STATE) {
//    	 gwinPrintf(Console_r, "AUTO STATE\r\n");
//     }
//     else if(carState_r == START_STATE) {
//    	 gwinPrintf(Console_r, "START STATE\r\n");
//     }
//     gwinPrintf(Console_r, "pushbar: %d\r\n", pushBarAlive);
     gwinClear(Console2_r);
     gwinPrintf(Console2_r, "D0: %d\r\n", debug_display[0]);
     gwinPrintf(Console2_r, "D1: %d\r\n", debug_display[1]);
     gwinPrintf(Console2_r, "D2: %d\r\n", debug_display[2]);
     gwinPrintf(Console2_r, "D3: %d\r\n", debug_display[3]);
     gwinPrintf(Console2_r, "D4: %d\r\n", debug_display[4]);
     gwinPrintf(Console2_r, "D5: %d\r\n", debug_display[5]);
     gwinPrintf(Console2_r, "D6: %d\r\n", debug_display[6]);
     gwinPrintf(Console2_r, "D7: %d\r\n", debug_display[7]);
     gwinPrintf(Console2_r, "D8: %d\r\n", debug_display[8]);
     gwinPrintf(Console2_r, "D9: %d\r", debug_display[9]);
//     gwinPrintf(Console2_r, "x: %d\r\n", x_r);
//     gwinPrintf(Console2_r, "y: %d\r\n", y_r);
//     gwinPrintf(Console2_r, "a: %d\r\n", tRotation_r);
//     gwinPrintf(Console2_r, "E: %d ",E0_r);
//     gwinPrintf(Console2_r, "%d ",E1_r);
//     gwinPrintf(Console2_r, "%d\n",E2_r);
//     gwinPrintf(Console2_r, "L0W : %d    ", LineSensor[0].Position[1]);
//     gwinPrintf(Console2_r, "L0P: %d\n", LineSensor[0].Position[0]);
//     gwinPrintf(Console2_r, "L1W : %d    ", LineSensor[1].Position[1]);
//     gwinPrintf(Console2_r, "L1P: %d\n", LineSensor[1].Position[0]);
//     gwinPrintf(Console2_r, "L2W : %d    ", LineSensor[2].Position[1]);
//     gwinPrintf(Console2_r, "L2P: %d\n", LineSensor[2].Position[0]);
//     gwinPrintf(Console2_r, "L3W : %d    ", LineSensor[3].Position[1]);
//     gwinPrintf(Console2_r, "L3P: %d\n", LineSensor[3].Position[0]);
//     gwinPrintf(Console2_r, "LA : %d\n", line_a_d_r);
//     gwinPrintf(Console2_r, "LD : %d\n", line_x_d_r);
//     gwinPrintf(Console2_r, "LA : %d\n", line_angle_r);
//     gwinPrintf(Console2_r, "LD : %d\n", line_y_r);

     gwinClear(Console3_r);

//     gwinPrintf(Console3_r, "ENC: %d\r\n,", currentPos_r);
//     gwinPrintf(Console3_r, "DIS: %d\r\n,", (uint16_t)dSensor.distance_mm);
     gwinPrintf(Console3_r, "LINE0: %d\r\n", LineSensor2016[0].status);
     gwinPrintf(Console3_r, "LINE0: %d\r\n", LineSensor2016[0].position);
     gwinPrintf(Console3_r, "SHOT: %d\r\n", M[4].SetPoint);
     gwinPrintf(Console3_r, "M4: %d\r\n", M[4].Feedback);
     gwinPrintf(Console3_r, "M5: %d\r\n", M[5].Feedback);
     gwinPrintf(Console3_r, "M6: %d\r\n", M[6].Feedback);
//     gwinPrintf(Console3_r, "STH: %4f\r\n", something);
//     gwinPrintf(Console3_r, "Y: %d\r\n", yDistance);
//     gwinPrintf(Console3_r, "LHX: %d\r\n", -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), HatDeadzone ) * hatMultiplier);
//     gwinPrintf(Console3_r, "LOOP %d\r\n", (int)loop_stats.loop_frequency );

//     gwinPrintf(Console3_r, "SPD: %d\r\n,", ((int16_t)encoder1_2.delta_count[0] + (int16_t)encoder1_2.delta_count[1])/2);
//     gwinPrintf(Console3_r, "N/m: %d\r\n,", m[0].status.torque_nm);


//     gwinPrintf(Console3_r, "");
//     gwinPrintf(Console3_r, "pc1: %d\r\n", pass_line_count_r[0]);
//     gwinPrintf(Console3_r, "zr: %d\r\n", z_dst_r.reach_flag);
//     gwinPrintf(Console3_r, "S7: %d\r\n", Servo1.command[7]);
//     gwinPrintf(Console3_r, "S0: %d\r\n", Servo1.command[0]);
//     gwinPrintf(Console3_r, "us : %d\n", ADCValue[0]);
////     gwinPrintf(Console3_r, "sum : %d\n", sum_r);
//     gwinPrintf(Console3_r, "fin : %d\n", finish_flag_r);
//     gwinPrintf(Console3_r, "run_flag : %d\n", run_auto_flag_r);
//     gwinPrintf(Console3_r, "AS: %d\r\n", auto_state_r);
//     gwinPrintf(Console3_r, "stage: %d\r\n", stage_r);

     gwinClear(Console4_r);
     gwinPrintf(Console4_r, "Jintsuu kai \r\n");
//     gwinPrintf(Console4_r, "EN: %d\r\n", (int)((encoder_1 + encoder_2)/2));
//     gwinPrintf(Console4_r, "EN1: %d\r\n", encoder_1);
//     gwinPrintf(Console4_r, "EN2: %d\r\n", encoder_2);
     gwinPrintf(Console4_r, "DIS: %d\r\n", distanceSum);
     gwinPrintf(Console4_r, "XSP: %d\r\n", xCarSetPoint_r);
     gwinPrintf(Console4_r, "YSP: %d\r\n", asdasd);
     gwinPrintf(Console4_r, "POS: %d\r\n", currentPos_r);
//     if(shooterNextState == PLATFORM_NO_MIDDLE_NO) {
//    	 gwinPrintf(Console4_r, "PLATFORM_NO_MIDDLE_NO\r\n");
//     }
//     else if(shooterNextState == PLATFORM_YES_MIDDLE_YES) {
//    	 gwinPrintf(Console4_r, "PLAT_Y_MID_Y \r\n");
//     }
//     else if(shooterNextState == PLATFORM_NO_MIDDLE_YES) {
//		 gwinPrintf(Console4_r, "PLAT_N_MID_Y \r\n");
//	 }
//     else if(shooterNextState == RAISE_HOIST) {
//		 gwinPrintf(Console4_r, "RAISE \r\n");
//	 }
//     else if(shooterNextState == RAM_AND_SHOOT) {
//		 gwinPrintf(Console4_r, "RAM_N_SHT \r\n");
//	 }
//     else if(shooterNextState == LOWER_HOIST) {
//		 gwinPrintf(Console4_r, "LOWER \r\n");
//	 }
//     else if(shooterNextState == LOADING_ERROR) {
//		 gwinPrintf(Console4_r, "LOAD_ERR \r\n");
//	 }

#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
     gwinPrintf(Console4_r, "PID: %d\r\n", (int)(PID_krpm*1000));
#endif
}

//static char buf[8];

#define VAL_UPDATE(handle, ...) \
  snprintf(buf, 8, __VA_ARGS__); \
  gwinSetText(handle, buf, TRUE);
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
