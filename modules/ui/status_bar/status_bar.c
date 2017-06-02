
/*
 * status_bar.c
 *
 *  Created on: Apr 22, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "umd.h"
#include "app.h"
#include "status_bar.h"
#include "widgets.h"
#include "analog.h"
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
#include <string.h>

static font_t font1;
static GHandle statusbar;
static RTCDateTime timespec;
static RTCDateTime starttime = { 0 };
static uint32_t system_time;
static char left[60] = "";
static char right[60] = "";
static char center[10] = "";
static char temp[40];
static int left_counter = 0;
static int right_counter = 0;

#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
int16_t UpdateVoltage(void){
  int i, Count = 0;
  float Sum = 0;
  for(i = 0; i < 8; i++)
  {
      if(M[i].timeout)
      {
          Sum += M[i].Board.Voltage;
          Count++;
      }
  }
  if (Count == 0)
    return 0.0;
  else
   return (float) (((float)(Sum / Count))/1000.0);
  //return M[5].Board.Voltage;
}
#endif

char * text_scrolling(const char * text, int size, int * position_counter, int line_width, int advancement){
     int i;
     memset(temp, 0, sizeof(temp));
//     if (size < line_width){
//       return text;
//     }else{
     for (i=*position_counter; i<(*position_counter+line_width); i++){
         temp[i-*position_counter] = text[i%size];
         //strcat(temp, text[i%size]);
     }
     //strcat(temp, '\0');
     *position_counter = (*position_counter + advancement)%size;
     return temp;
//     }
}

void get_time(int * hour, int * min, int * sec){
    rtcGetTime(&RTCD1, &timespec);
    *hour = ((int)timespec.millisecond / 1000) / 3600;
    *min = (((int)timespec.millisecond / 1000)%3600) / 60;
    *sec = (((int)timespec.millisecond / 1000)%3600) % 60;
    system_time = ((*hour << 12) & 0x0003F000) || ((*min<<6) & 0x00000FC0) || (*sec & 0x0000003F);
}

void online_status_update(void){
  memset(left, 0,sizeof(left));
#if  USE_MOTOR_0
  if (M[0].timeout)
     strcat(left, "M0 ");
#endif
#if  USE_MOTOR_1
  if (M[1].timeout)
     strcat(left, "M1 ");
#endif
#if  USE_MOTOR_2
  if (M[2].timeout)
     strcat(left, "M2 ");
#endif
#if  USE_MOTOR_3
  if (M[3].timeout)
     strcat(left, "M3 ");
#endif
#if  USE_MOTOR_4
  if (M[4].timeout)
     strcat(left, "M4 ");
#endif
#if  USE_MOTOR_5
  if (M[5].timeout)
     strcat(left, "M5 ");
#endif
#if  USE_MOTOR_6
  if (M[6].timeout)
     strcat(left, "M6 ");
#endif
#if  USE_MOTOR_7
  if (M[7].timeout)
     strcat(left, "M7 ");
#endif
#if USE_ENCODER && ENCODER_NUMBER > 0
  if (encoder1_2.Alive)
      strcat(left, "E0_1 ");
#endif
#if USE_ENCODER && ENCODER_NUMBER > 2
  if (encoder3_4.Alive)
      strcat(left, "E2_3 ");
#endif
#if USE_SERVO && SERVO_NUMBER > 0
  if (Servo1.Alive)
      strcat(left, "S0 ");
#endif
#if USE_SERVO && SERVO_NUMBER > 8
  if (Servo2.Alive)
      strcat(left, "S1 ");
#endif
#if USE_LINESENSOR_0
  if (LineSensor[0].Alive)
      strcat(left, "L0 ");
#endif
#if USE_LINESENSOR_1
  if (LineSensor[1].Alive)
      strcat(left, "L1 ");
#endif
#if USE_LINESENSOR_2
  if (LineSensor[2].Alive)
      strcat(left, "L2 ");
#endif
#if USE_LINESENSOR_3
  if (LineSensor[3].Alive)
      strcat(left, "L3 ");
#endif
}

void status_bar_redraw(void){
  //get cpu usage
  //get the online status of all board
   //check voltage
   //get the rtc
  int hour, min, sec;
  get_time(&hour, &min, &sec);
  gwinClear(statusbar);
  //chsnprintf(left, (sizeof(left)/sizeof(char)), "M0 M1 M2");
  online_status_update();
  //draw the left part
  gdispDrawStringBox(0, 0, (GDISP_SCREEN_WIDTH/2 - gdispGetFontMetric(font1, fontMaxWidth) * (6/2))-1, STATUS_BAR_HEIGHT,
                      text_scrolling(left, strlen(left), &left_counter, 29, 3), font1, Black, justifyLeft);
  //draw the middle part
  chsnprintf(center, (sizeof(center)/sizeof(char)), "%02d:%02d:%02d", hour, min, sec);
  gdispDrawStringBox((GDISP_SCREEN_WIDTH/2 - gdispGetFontMetric(font1, fontMaxWidth) * (6/2)),0,
                         gdispGetFontMetric(font1, fontMaxWidth) * 6, STATUS_BAR_HEIGHT, center, font1 , Black, justifyCenter);
  chsnprintf(right, (sizeof(right)/sizeof(char)),"CPU:%d              ",
//             UDC_GetStatistics(UDC_CHECKSUM_ERROR),UDC_GetStatistics(UDC_FRAMING_ERROR),UDC_GetStatistics(UDC_TIMEOUT),
             (int) cpu_usage_get_recent());
  //draw the right part
  gdispDrawStringBox((GDISP_SCREEN_WIDTH/2 + gdispGetFontMetric(font1, fontMaxWidth) * (6/2))+1,0,
                     (GDISP_SCREEN_WIDTH/2 - gdispGetFontMetric(font1, fontMaxWidth) * (6/2))-1,
                      STATUS_BAR_HEIGHT, text_scrolling(right, strlen(right), &right_counter, 29, 3), font1, Black, justifyRight);

}

THD_WORKING_AREA (wa_ui_rtc_event, 128);
THD_FUNCTION(ui_rtc_evt, arg){
  (void) arg;
  ui_event evt;
  evt.type = UI_STATUSBAR_TICK;
  uint32_t time = chVTGetSystemTimeX();
  while (true) {
      evt.data.status_bar_info.system_time = system_time;
      time += S2ST(1);
      chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
      //status_bar_redraw();
      chThdSleepUntil(time);
     }
}

void status_bar_init(void){
  //intitialize the rtc driver
  font1 = gdispOpenFont("DroidSans23");
  chThdCreateStatic(wa_ui_rtc_event, sizeof(wa_ui_rtc_event), LOWPRIO, ui_rtc_evt, NULL);
  statusbar = createContainer(0, 0, GDISP_SCREEN_WIDTH, STATUS_BAR_HEIGHT, FALSE);
  gwinShow(statusbar);
  rtcSetTime(&RTCD1, &starttime);
  status_bar_redraw();
}

