/*
 * ps4.c
 *
 *  Created on: Apr 18, 2016
 *      Author: Melvin
 */
#include "app.h"
#include "ps4_usbhost.h"
#if USBHDS4_DEBUG_ENABLE_INFO
#include "chprintf.h"
#endif

DS4_status_t ps4_data;
DS4_status_t old_data;
DS4_command_t cmd = {0};

uint8_t DS4_ButtonPress(ButtonEnum b){
     if (b <= LEFT){
         switch (b) {
             case UP:
                 return (ps4_data.dpad_code == DPAD_LEFT_UP && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_UP && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_UP_RIGHT && old_data.dpad_code == DPAD_OFF);
             case RIGHT:
                 return (ps4_data.dpad_code == DPAD_UP_RIGHT && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_RIGHT && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_RIGHT_DOWN && old_data.dpad_code == DPAD_OFF);
             case DOWN:
                 return (ps4_data.dpad_code == DPAD_RIGHT_DOWN && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_DOWN && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_DOWN_LEFT && old_data.dpad_code == DPAD_OFF);
             case LEFT:
                 return (ps4_data.dpad_code == DPAD_DOWN_LEFT && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_LEFT && old_data.dpad_code == DPAD_OFF)
                     || (ps4_data.dpad_code == DPAD_LEFT_UP && old_data.dpad_code == DPAD_OFF);
             default:
                 return 0;
         }
     }else{
       switch (b){
             case SHARE:
               return ps4_data.share & !(old_data.share);
             case OPTIONS:
               return ps4_data.options & !(old_data.options);
             case L3:
               return ps4_data.l3 & !(old_data.l3);
             case R3:
               return ps4_data.r3 & !(old_data.r3);
             case L2:
               return ps4_data.l2 & !(old_data.l2);
             case R2:
               return ps4_data.r2 & !(old_data.r2);
             case L1:
               return ps4_data.l1 & !(old_data.l1);
             case R1:
               return ps4_data.r1 & !(old_data.r1);
             case TRIANGLE:
               return ps4_data.triangle & !(old_data.triangle);
             case CROSS:
               return ps4_data.cross & !(old_data.cross);
             case SQUARE:
               return ps4_data.square & !(old_data.square);
             case PS:
               return ps4_data.ps & !(old_data.ps);
             case TOUCHPAD:
                return ps4_data.tpad_click & !(old_data.tpad_click);
             case CIRCLE:
                return ps4_data.circle & !(old_data.circle);
             default:
                return 0;
       }
     }
}

static THD_WORKING_AREA(waUSBHOST, 1024);
static THD_FUNCTION(USBHOST, arg) {

  (void)arg;
  chRegSetThreadName("USB Host Thread");
  while (TRUE) {
    usbhMainLoop(&USBHD2);
    chThdSleepMilliseconds(100);
  }
}

static THD_WORKING_AREA(waDS4, 1024);
static THD_FUNCTION(DS4, arg) {

  (void)arg;
  chRegSetThreadName("DS4 Thread");


  cmd.led_r = 255;
  cmd.led_g = 20;
  cmd.led_b = 147;

  USBHDS4Driver *const ds4p = &USBHDS4[0];

  ui_event evt;
  bool need_post = false;

#if USBHDS4_DEBUG_ENABLE_INFO
  chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "Waiting for connection...\r\n");
#endif

  while (TRUE) {
    switch (ds4p->state) {
    case USBHDS4_STATE_UNINIT:
    case USBHDS4_STATE_STOP:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD,
          "DS4 Disconnected or Stopped.\r\n");
#endif
      memset(&ps4_data, 0, sizeof(ps4_data));
      memset(&old_data, 0, sizeof(old_data));
      chThdSleepMilliseconds(500);
      break;
    case USBHDS4_STATE_ACTIVE:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 started.\r\n");
#endif
      usbhds4Start(ds4p);
      chThdSleepMilliseconds(20);
      DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      chThdSleepMilliseconds(500);
      break;
    case USBHDS4_STATE_READY:
      if (DS4_ReadTimeOut(ds4p, &ps4_data, MS2ST(50))){
#if USBHDS4_DEBUG_ENABLE_INFO
        chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "%5d %5d %5d\r",
            ps4_data.hat_left_x,
            ps4_data.r2_trigger,
            ps4_data.cross
            );
#endif
          if (DS4_ButtonPress(DOWN)){
                  evt.type = UI_INPUT_BUTTON;
                  evt.data.button_state = UI_BUTTON_DOWN;
                  need_post = true;
          }else if (DS4_ButtonPress(UP)){
                 evt.type = UI_INPUT_BUTTON;
                 evt.data.button_state = UI_BUTTON_UP;
                 need_post = true;
          }else if(DS4_ButtonPress(CIRCLE)){
                 evt.type = UI_INPUT_BUTTON;
                 evt.data.button_state = UI_BUTTON_ENTER;
                 need_post = true;
          }else if(DS4_ButtonPress(LEFT)){
                 evt.type = UI_INPUT_BUTTON;
                 evt.data.button_state = UI_BUTTON_BACK;
                 need_post = true;
          }
          DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      }else{
#if USBHDS4_DEBUG_ENABLE_INFO
        chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 Read Timeout\r\n");
#endif
          memset(&ps4_data, 0, sizeof(ps4_data));
          memset(&old_data, 0, sizeof(old_data));
      }
      if(need_post){
            chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
            need_post = false;
      }
      memcpy(&old_data, &ps4_data, sizeof(old_data));
      //old_data = ps4_data;
      chThdSleepMilliseconds(10);

    }
  }
}

void ps4_usbhost_init(void){
  usbhStart(&USBHD2);

  chThdCreateStatic(waUSBHOST, sizeof(waUSBHOST), NORMALPRIO,
                      USBHOST, NULL);
  usbhds4ObjectInit(&USBHDS4[0]);
  chThdCreateStatic(waDS4, sizeof(waDS4), NORMALPRIO,
                        DS4, NULL);

}

