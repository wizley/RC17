/*
 * red_page.c
 *
 *  Created on: 2016¦~6¤ë7¤é
 *      Author: Hung
 */


//#include "app_list.h"
#include "blue.h"
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
char * UIDrivingState[2] = {"activated","deactivated"}; //for ui

// GHandles
GHandle ContainerPage0;
GHandle Console;
GHandle Console1;
GHandle Console2;
GHandle Console3;
GHandle Console4;
GHandle Console5;
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
static void createPagePage0(void)
{

  // create container widget: ghContainerPage0
  ContainerPage0 = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);

  // Create console widget: ghConsole
  Console = createConsole(&ContainerPage0, 0, 0, 800, 124);
  gwinSetColor(Console, Silver);
  gwinSetBgColor(Console, Black);
  //gwinSetFont(ghConsole, dejavu_sans_32_anti_aliased);
  gwinRedraw(Console);

  Console2 = createConsole(&ContainerPage0, 1, 125, 200, 350);
  gwinRedraw(Console2);

  Console3 = createConsole(&ContainerPage0, 200, 125, 200, 350);
  gwinRedraw(Console3);

  Console4 = createConsole(&ContainerPage0, 400, 125, 200, 350);
  gwinRedraw(Console4);

  Console5 = createConsole(&ContainerPage0, 600, 125, 200, 350);
  gwinRedraw(Console5);

//  Console1 = createConsole(&ContainerPage0, 1,1,520,130);
//  gwinSetColor(Console1, Silver);
//  gwinSetBgColor(Console1, Black);
//  gwinSetFont(Console1, dejavu_sans_32_anti_aliased);
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

void guiUpdate(void){
	 RunPath();
//     gwinClear(Console1);
//     gwinPrintf(Console1, UIDrivingState[DrivingState]);
     gwinClear(Console);
     //gwinPrintf(Console, "Setpoint: %d ", (int)((float)m[0].speedef_krpm));
//     gwinPrintf(Console, "%d\r\n ", (int)((float)m[1].speedef_krpm ));
     gwinPrintf(Console, "SHT  %4d\033t  ", M[4].SetPoint);
     gwinPrintf(Console, "PIT  %4d\033t  ", getPitch());//M[5].Board.ADCValue
     gwinPrintf(Console, "ROL  %4d\033t  ", getRoll());//M[4].Board.ADCValue
     gwinPrintf(Console, "X  %5d\033t  ", distanceSum);
     gwinPrintf(Console, "Y  %5d\033t\r\n", (int)yDistance);
     gwinPrintf(Console, "SPUS2 %3d\033t  ", Servo1.command[2]);
     gwinPrintf(Console, "SPIT1 %3d\033t  ", Servo1.command[1]);
     gwinPrintf(Console, "SROL0 %3d\033t  ", Servo1.command[0]);
     gwinPrintf(Console, "ALIVE %3d\033t  \r\n", shooterAlive);
#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
	gwinPrintf(Console, "M01X %4d", (int)(m[0].speed_krpm*1000));
	gwinPrintf(Console, ",%4d", (int)(m[1].speed_krpm*1000));
    gwinPrintf(Console, "  M23U %4d", (int)(m[2].speed_krpm*1000));
    gwinPrintf(Console, ",%4d", (int)(m[3].speed_krpm*1000));
    gwinPrintf(Console, "  M45S %4d", (int)(m[4].speed_krpm*1000));
    gwinPrintf(Console, ",%4d\r\n", (int)(m[5].speed_krpm*1000));
//	gwinPrintf(Console, "EN %d\r\n", (int16_t)encoder1_2.delta_count[0]);
//	gwinPrintf(Console, "EN %d\r\n", ((int16_t)encoder1_2.delta_count[0] * 0.013521634 / 1.14961122));
//	oldENvalue = (int16_t)encoder1_2.delta_count[0];
#elif !IS_MOTOR_0_2016 && !IS_MOTOR_1_2016
    gwinPrintf(Console, "M01X %4d", (int)(M[0].Feedback));
    gwinPrintf(Console, ",%4d", (int)(M[1].Feedback));
    gwinPrintf(Console, " M23U %4d", (int)(M[2].Feedback));
    gwinPrintf(Console, ",%4d", (int)(M[3].Feedback));
    gwinPrintf(Console, " M45S %4d", (int)(M[4].Feedback));
    gwinPrintf(Console, ",%4d", (int)(M[5].Feedback));
    gwinPrintf(Console, " M6Y %4d\r\n", (int)(M[6].Feedback));
//	gwinPrintf(Console, "EN %d\r\n", (int16_t)encoder1_2.delta_count[0] * WHEEL_DIAMETER * PI / ENCODERESOLUTION );
//	gwinPrintf(Console, "EN %d\r\n", ((int16_t)encoder1_2.delta_count[0] - oldENvalue) * WHEEL_DIAMETER * PI / ENCODERESOLUTION );
//	oldENvalue = (int16_t)encoder1_2.delta_count[0];
#endif
//     gwinPrintf(Console, "ls0", LineSensor2016[0].position);
//     if(carState == MANUAL_STATE) {
//    	 gwinPrintf(Console, "MANUAL STATE\r\n");
//     }
//     else if(carState == AUTO_STATE) {
//    	 gwinPrintf(Console, "AUTO STATE\r\n");
//     }
//     else if(carState == START_STATE) {
//    	 gwinPrintf(Console, "START STATE\r\n");
//     }
//     gwinPrintf(Console, "pushbar: %d\r\n", pushBarAlive);
     gwinClear(Console2);
     gwinPrintf(Console2, "D0: %d\r\n", debug_display[0]);
     gwinPrintf(Console2, "D1: %d\r\n", debug_display[1]);
     gwinPrintf(Console2, "D2: %d\r\n", debug_display[2]);
     gwinPrintf(Console2, "D3: %d\r\n", debug_display[3]);
     gwinPrintf(Console2, "D4: %d\r\n", debug_display[4]);
     gwinPrintf(Console2, "D5: %d\r\n", debug_display[5]);
     gwinPrintf(Console2, "D6: %d\r\n", debug_display[6]);
     gwinPrintf(Console2, "D7: %d\r\n", debug_display[7]);
     gwinPrintf(Console2, "D8: %d\r\n", debug_display[8]);
     gwinPrintf(Console2, "D9: %d\r", debug_display[9]);
//     gwinPrintf(Console2, "x: %d\r\n", x);
//     gwinPrintf(Console2, "y: %d\r\n", y);
//     gwinPrintf(Console2, "a: %d\r\n", tRotation);
//     gwinPrintf(Console2, "E: %d ",E0);
//     gwinPrintf(Console2, "%d ",E1);
//     gwinPrintf(Console2, "%d\n",E2);
//     gwinPrintf(Console2, "L0W : %d    ", LineSensor[0].Position[1]);
//     gwinPrintf(Console2, "L0P: %d\n", LineSensor[0].Position[0]);
//     gwinPrintf(Console2, "L1W : %d    ", LineSensor[1].Position[1]);
//     gwinPrintf(Console2, "L1P: %d\n", LineSensor[1].Position[0]);
//     gwinPrintf(Console2, "L2W : %d    ", LineSensor[2].Position[1]);
//     gwinPrintf(Console2, "L2P: %d\n", LineSensor[2].Position[0]);
//     gwinPrintf(Console2, "L3W : %d    ", LineSensor[3].Position[1]);
//     gwinPrintf(Console2, "L3P: %d\n", LineSensor[3].Position[0]);
//     gwinPrintf(Console2, "LA : %d\n", line_a_d);
//     gwinPrintf(Console2, "LD : %d\n", line_x_d);
//     gwinPrintf(Console2, "LA : %d\n", line_angle);
//     gwinPrintf(Console2, "LD : %d\n", line_y);

     gwinClear(Console3);

//     gwinPrintf(Console3, "ENC: %d\r\n,", currentPos);
//     gwinPrintf(Console3, "DIS: %d\r\n,", (uint16_t)dSensor.distance_mm);
     gwinPrintf(Console3, "LINE0: %d\r\n", LineSensor2016[0].status);
     gwinPrintf(Console3, "LINE0: %d\r\n", LineSensor2016[0].position);
     gwinPrintf(Console3, "SHOT: %d\r\n", M[4].SetPoint);
     gwinPrintf(Console3, "M4: %d\r\n", M[4].Feedback);
     gwinPrintf(Console3, "M5: %d\r\n", M[5].Feedback);
     gwinPrintf(Console3, "M6: %d\r\n", M[6].Feedback);
//     gwinPrintf(Console3, "STH: %4f\r\n", something);
//     gwinPrintf(Console3, "Y: %d\r\n", yDistance);
//     gwinPrintf(Console3, "LHX: %d\r\n", -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), HatDeadzone ) * hatMultiplier);
//     gwinPrintf(Console3, "LOOP %d\r\n", (int)loop_stats.loop_frequency );

//     gwinPrintf(Console3, "SPD: %d\r\n,", ((int16_t)encoder1_2.delta_count[0] + (int16_t)encoder1_2.delta_count[1])/2);
//     gwinPrintf(Console3, "N/m: %d\r\n,", m[0].status.torque_nm);


//     gwinPrintf(Console3, "");
//     gwinPrintf(Console3, "pc1: %d\r\n", pass_line_count[0]);
//     gwinPrintf(Console3, "zr: %d\r\n", z_dst.reach_flag);
//     gwinPrintf(Console3, "S7: %d\r\n", Servo1.command[7]);
//     gwinPrintf(Console3, "S0: %d\r\n", Servo1.command[0]);
//     gwinPrintf(Console3, "us : %d\n", ADCValue[0]);
////     gwinPrintf(Console3, "sum : %d\n", sum);
//     gwinPrintf(Console3, "fin : %d\n", finish_flag);
//     gwinPrintf(Console3, "run_flag : %d\n", run_auto_flag);
//     gwinPrintf(Console3, "AS: %d\r\n", auto_state);
//     gwinPrintf(Console3, "stage: %d\r\n", stage);

     gwinClear(Console4);
     gwinPrintf(Console4, "Pos: %d\r\n", blueStateSet[targetPosition].id);
     gwinPrintf(Console4, "Pit: %d\r\n", blueStateSet[targetPosition].pitch);
     gwinPrintf(Console4, "Rol: %d\r\n", blueStateSet[targetPosition].roll);
     gwinPrintf(Console4, "Sht: %d\r\n", blueStateSet[targetPosition].shootspd);
     gwinPrintf(Console4, "Xxx: %d\r\n", blueStateSet[targetPosition].x);
     gwinPrintf(Console4, "Yyy: %d\r\n", blueStateSet[targetPosition].y);

//     gwinPrintf(Console4, "EN: %d\r\n", (int)((encoder_1 + encoder_2)/2));
//     gwinPrintf(Console4, "EN1: %d\r\n", encoder_1);
//     gwinPrintf(Console4, "EN2: %d\r\n", encoder_2);

//     if(shooterNextState == PLATFORM_NO_MIDDLE_NO) {
//    	 gwinPrintf(Console4, "PLATFORM_NO_MIDDLE_NO\r\n");
//     }
//     else if(shooterNextState == PLATFORM_YES_MIDDLE_YES) {
//    	 gwinPrintf(Console4, "PLAT_Y_MID_Y \r\n");
//     }
//     else if(shooterNextState == PLATFORM_NO_MIDDLE_YES) {
//		 gwinPrintf(Console4, "PLAT_N_MID_Y \r\n");
//	 }
//     else if(shooterNextState == RAISE_HOIST) {
//		 gwinPrintf(Console4, "RAISE \r\n");
//	 }
//     else if(shooterNextState == RAM_AND_SHOOT) {
//		 gwinPrintf(Console4, "RAM_N_SHT \r\n");
//	 }
//     else if(shooterNextState == LOWER_HOIST) {
//		 gwinPrintf(Console4, "LOWER \r\n");
//	 }
//     else if(shooterNextState == LOADING_ERROR) {
//		 gwinPrintf(Console4, "LOAD_ERR \r\n");
//	 }

#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
     gwinPrintf(Console4, "PID: %d\r\n", (int)(PID_krpm*1000));
#endif
}

//static char buf[8];

#define VAL_UPDATE(handle, ...) \
  snprintf(buf, 8, __VA_ARGS__); \
  gwinSetText(handle, buf, TRUE);
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
//  VAL_UPDATE(ghLabelCPU_VAL, "%02d", (int) cpu_usage_getecent());
//}

void blue_main(void *params){
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


application blue = {
    .name = "Blue",
    .main = blue_main
};
