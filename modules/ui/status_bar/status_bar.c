/*
 * status_bar.c
 *
 *  Created on: Apr 22, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "udc.h"
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

static GHandle statusbar;
static RTCDateTime timespec;
static RTCDateTime starttime = { 0 };
static uint32_t system_time;
static char buffer[200] = {0};

#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
int16_t UpdateVoltage(void){
  int i, Count = 0;
  float Sum = 0;
  for(i = 0; i < 8; i++)
  {
      if(M[i].Alive)
      {
          Sum += M[i].Board.Voltage;
          Count++;
      }
  }
//  if (Sum == 0 && Count == 0)
//    return 0.0;
//  else
   //return (float) (((float)(Sum / Count))/1000.0);
  return M[0].Board.Voltage;
}
#endif

void get_time(int * hour, int * min, int * sec){
    rtcGetTime(&RTCD1, &timespec);
    *hour = ((int)timespec.millisecond / 1000) / 3600;
    *min = (((int)timespec.millisecond / 1000)%3600) / 60;
    *sec = (((int)timespec.millisecond / 1000)%3600) % 60;
    system_time = ((*hour << 12) & 0x0003F000) || ((*min<<6) & 0x00000FC0) || (*sec & 0x0000003F);
}

void online_status_update(void){
   //if (M[0].Alive)

}

void status_bar_redraw(void){
  //get cpu usage
  //get the online status of all board
   //check voltage
   //get the rtc
  int hour, min, sec;
  get_time(&hour, &min, &sec);
  gwinClear(statusbar);
  chsnprintf(buffer, (sizeof(buffer)/sizeof(buffer[0])),"cks:%d frm:%d tmo:%d %02d:%02d:%02d mb:%dV cpu:%.2f",
             UDC_GetStatistics(UDC_CHECKSUM_ERROR),UDC_GetStatistics(UDC_FRAMING_ERROR),UDC_GetStatistics(UDC_TIMEOUT),
             hour, min, sec, UpdateVoltage(), cpu_usage_get_recent());
  gdispDrawStringBox(0,0,GDISP_SCREEN_WIDTH, STATUS_BAR_HEIGHT, buffer, gdispOpenFont("DroidSans23"), Black, justifyCenter);
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
  chThdCreateStatic(wa_ui_rtc_event, sizeof(wa_ui_rtc_event), LOWPRIO, ui_rtc_evt, NULL);
  statusbar = createContainer(0, 0, GDISP_SCREEN_WIDTH, STATUS_BAR_HEIGHT, FALSE);
  gwinShow(statusbar);
  rtcSetTime(&RTCD1, &starttime);
  status_bar_redraw();
}
