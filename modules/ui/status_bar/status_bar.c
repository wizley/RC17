/*
 * status_bar.c
 *
 *  Created on: Apr 22, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "udc.h"
#include "app.h"
#include "status_bar.h"
#include "widgets.h"

GHandle statusbar_label;
static font_t f1;
static RTCDateTime timespec;
static uint32_t system_time;
static char buffer[50] = {0};
void status_bar_redraw(void){
  //get the online status of all board
   //check voltage
   //get the rtc
  rtcGetTime(&RTCD1, &timespec);
  system_time = rtcConvertDateTimeToFAT(&timespec);
  chsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]),"M %d:%d:%d", (system_time & RTC_FAT_TIME_HOURS_MASK >> 12), (system_time & RTC_FAT_TIME_MINUTES_MASK >> 6),  system_time & RTC_FAT_TIME_SECONDS_MASK);
  //gdispDrawStringBox(0,0,800, STATUS_BAR_HEIGHT, buffer, f1, Black, justifyCenter);
  gwinSetText(statusbar_label, buffer);
}

THD_WORKING_AREA (wa_ui_rtc_event, 64);
THD_FUNCTION(ui_rtc_evt, arg){
  (void) arg;
  ui_event evt;
  evt.type = UI_STATUSBAR_TICK;

  uint32_t time = chVTGetSystemTimeX();
  while (true) {


      evt.data.status_bar_info.system_time = system_time;
      time += S2ST(1);
      chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
      chThdSleep(time);
     }
}

void status_bar_init(void){
  //intitialize the rtc driver
  chThdCreateStatic(wa_ui_rtc_event, sizeof(wa_ui_rtc_event), LOWPRIO, ui_rtc_evt, NULL);
  f1 = gdispOpenFont("DroidSans23");
  statusbar_label = createLabel(NULL, 0,0,800,STATUS_BAR_HEIGHT);
  //gdispOpenFont(dejavu_sans_20_anti_aliased);
}
