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

uint8_t PS4_BUTTONS_BITMASK[] = {
        UP, // UP
        RIGHT, // RIGHT
        DOWN, // DOWN
        LEFT, // LEFT

        0x0C, // SHARE
        0x0D, // OPTIONS
        0x0E, // L3
        0x0F, // R3

        0x0A, // L2
        0x0B, // R2
        0x08, // L1
        0x09, // R1

        0x07, // TRIANGLE
        0x06, // CIRCLE
        0x05, // CROSS
        0x04, // SQUARE

        0x10, // PS
        0x11 // TOUCHPAD
};


uint8_t DS4_ButtonPress(ButtonEnum b){
     if (b <= LEFT){
         switch (b) {
             case UP:
                 return (ps4_data.btns.dpad_code == DPAD_LEFT_UP && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_UP && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_UP_RIGHT && old_data.btns.dpad_code == DPAD_OFF);
             case RIGHT:
                 return (ps4_data.btns.dpad_code == DPAD_UP_RIGHT && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_RIGHT && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_RIGHT_DOWN && old_data.btns.dpad_code == DPAD_OFF);
             case DOWN:
                 return (ps4_data.btns.dpad_code == DPAD_RIGHT_DOWN && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_DOWN && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_DOWN_LEFT && old_data.btns.dpad_code == DPAD_OFF);
             case LEFT:
                 return (ps4_data.btns.dpad_code == DPAD_DOWN_LEFT && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_LEFT && old_data.btns.dpad_code == DPAD_OFF)
                     || (ps4_data.btns.dpad_code == DPAD_LEFT_UP && old_data.btns.dpad_code == DPAD_OFF);
             default:
                 return false;
         }
     }else{
         return ((ps4_data.btns.val & (1UL << PS4_BUTTONS_BITMASK[b]))
             && (!(old_data.btns.val & (1UL << PS4_BUTTONS_BITMASK[b]))));
     }
}

uint8_t DS4_status_change(DS4_status_t a, DS4_status_t b){//function to determine generating ui_event to update screen
     if (abs(a.hat_left_x - b.hat_left_x) < 2
         && abs(a.hat_left_y - b.hat_left_y)<2 && abs(a.hat_right_x - b.hat_right_x) < 2 &&
         abs(a.hat_right_y - b.hat_right_y) < 2 && a.l2_trigger == b.l2_trigger &&
         a.r2_trigger == b.r2_trigger && ((a.btns.val & !(0xFC0)) == (b.btns.val & !(0xFC0)))){
         return 0;
     }
     return 1;
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

  ui_event evt; ui_event evt1 = {UI_STATUSBAR_TICK};
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
            ps4_data.btns.cross
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
      }
//      cmd.led_r = ps4_data.l2_trigger;
//      cmd.led_g = ps4_data.r2_trigger;
//      if(ps4_data.cross)
//        DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      if(need_post){
            chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
            need_post = false;
      }
      if (DS4_status_change(ps4_data, old_data)){
            //chMBPost(&app_mb, (msg_t)&evt1, TIME_IMMEDIATE);//FIXME: post as status bar tick should be removed
      }
      old_data = ps4_data;
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

