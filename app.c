#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "app.h"
#include "app_list.h"
#include "driving.h"
#include "ds4.h"

THD_WORKING_AREA(waApp, 2048);

mailbox_t app_mb;
static msg_t msg_buf[UI_MB_SIZE];

THD_WORKING_AREA(wa_ui_button_thread, 256);
THD_FUNCTION(ui_button_thread, arg) {
  (void) arg;
  chRegSetThreadName("UI button thread");

  ui_event evt;
  bool need_post = false;

  uint16_t qei_old_count = qeiGetCount(&QEID4);
  uint8_t but1_old_state = PAL_HIGH;
  uint8_t but2_old_state = PAL_HIGH;
  uint8_t but3_old_state = PAL_HIGH;
  uint8_t but7_old_state = PAL_HIGH;
  uint8_t but8_old_state = PAL_HIGH;
  uint8_t but9_old_state = PAL_HIGH;
  uint8_t ds4_cross_old_state = 0;
  uint8_t ds4_square_old_state = 0;
  uint8_t ds4_circle_old_state = 0;
  uint8_t ds4_triangle_old_state = 0;
  uint8_t ds4_up_old_state = 0;
  uint8_t ds4_down_old_state = 0;

  while(TRUE){
    /* scan for buttons */
    if((palReadPad(GPIOH, GPIOH_BUT1) == PAL_LOW) && (but1_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_BACK;
      need_post = true;
    }
    else if((palReadPad(GPIOB, GPIOB_BUT2) == PAL_LOW) && (but2_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_UP;
      need_post = true;
    }
    else if((palReadPad(GPIOG, GPIOG_BUT3) == PAL_LOW) && (but3_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_DOWN;
      need_post = true;
    }
    else if((palReadPad(GPIOD, GPIOD_BUT7) == PAL_LOW) && (but7_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_7;
      need_post = true;
    }
    else if((palReadPad(GPIOC, GPIOC_BUT8) == PAL_LOW) && (but8_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_8;
      need_post = true;
    }
    else if((palReadPad(GPIOB, GPIOB_PB12) == PAL_LOW) && (but9_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_ENTER;
      need_post = true;
    }
    else if((int16_t)(qeiGetCount(&QEID4) - qei_old_count) >= 4){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_DOWN;
      qei_old_count = qeiGetCount(&QEID4);
      need_post = true;
    }
    else if((int16_t)(qeiGetCount(&QEID4) - qei_old_count) <= -4){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_UP;
      qei_old_count = qeiGetCount(&QEID4);
      need_post = true;
    }
    else if(DS4.cross && !ds4_cross_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_BACK;
      need_post = true;
    }
    else if(DS4.square && !ds4_square_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_8;
      need_post = true;
    }
    else if(DS4.circle && !ds4_circle_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_ENTER;
      need_post = true;
    }
    else if(DS4.triangle && !ds4_triangle_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_7;
      need_post = true;
    }
    else if((DS4.dpad_code == 0b0000) && !ds4_up_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_UP;
      need_post = true;
    }
    else if((DS4.dpad_code == 0b0100) && !ds4_down_old_state){
      evt.type = UI_DS4_BUTTON;
      evt.data.button_state = UI_BUTTON_DOWN;
      need_post = true;
    }

    if(need_post){
      chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
      need_post = false;
    }

    but1_old_state = palReadPad(GPIOH, GPIOH_BUT1);
    but2_old_state = palReadPad(GPIOB, GPIOB_BUT2);
    but3_old_state = palReadPad(GPIOG, GPIOG_BUT3);
    but7_old_state = palReadPad(GPIOD, GPIOD_BUT7);
    but8_old_state = palReadPad(GPIOC, GPIOC_BUT8);
    but9_old_state = palReadPad(GPIOB, GPIOB_PB12);
    ds4_cross_old_state = DS4.cross;
    ds4_square_old_state = DS4.square;
    ds4_circle_old_state = DS4.circle;
    ds4_triangle_old_state = DS4.triangle;
    ds4_up_old_state = DS4.dpad_code == 0b0000;
    ds4_down_old_state = DS4.dpad_code == 0b0100;

    chThdSleepMilliseconds(50);
  }
}


int app_init(void) {
  chMBObjectInit(&app_mb, msg_buf, UI_MB_SIZE);
  chThdCreateStatic(waApp, sizeof(waApp), LOWPRIO, menu.main, NULL);
  InitDriving();
  chThdCreateStatic(wa_ui_button_thread, sizeof(wa_ui_button_thread), LOWPRIO, ui_button_thread, NULL);
  return 0;
}

