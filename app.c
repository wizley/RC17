#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "app.h"
#include "app_list.h"
#include "driving.h"
#include "airboard.h"

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
  uint8_t but4_old_state = PAL_HIGH;
  uint8_t but5_old_state = PAL_HIGH;
  uint8_t but6_old_state = PAL_HIGH;
  uint8_t but7_old_state = PAL_HIGH;
  uint8_t but8_old_state = PAL_HIGH;
  uint8_t but9_old_state = PAL_HIGH;

  while(TRUE){
    /* scan for buttons */
    if((palReadPad(GPIOH, GPIOH_BUT1) == PAL_LOW) && (but1_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_1;
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
    else if((palReadPad(GPIOE, GPIOE_BUT4) == PAL_LOW) && (but4_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_RESERVED1;
      need_post = true;
    }
    else if((palReadPad(GPIOH, GPIOH_BUT5) == PAL_LOW) && (but5_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_RESERVED2;
      need_post = true;
    }
    else if((palReadPad(GPIOE, GPIOE_BUT6) == PAL_LOW) && (but6_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_RESERVED3;
      need_post = true;
    }
    else if((palReadPad(GPIOD, GPIOD_BUT7) == PAL_LOW) && (but7_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_7;
      need_post = true;
    }
    else if((palReadPad(GPIOC, GPIOC_BUT8) == PAL_LOW) && (but8_old_state == PAL_HIGH)){
      evt.type = UI_INPUT_BUTTON;
      evt.data.button_state = UI_BUTTON_BACK;
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

    if(need_post){
      chMBPost(&app_mb, (msg_t)&evt, TIME_IMMEDIATE);
      need_post = false;
    }

    but1_old_state = palReadPad(GPIOH, GPIOH_BUT1);
    but2_old_state = palReadPad(GPIOB, GPIOB_BUT2);
    but3_old_state = palReadPad(GPIOG, GPIOG_BUT3);
    but4_old_state = palReadPad(GPIOE, GPIOE_BUT4);
    but5_old_state = palReadPad(GPIOH, GPIOH_BUT5);
    but6_old_state = palReadPad(GPIOE, GPIOE_BUT6);
    but7_old_state = palReadPad(GPIOD, GPIOD_BUT7);
    but8_old_state = palReadPad(GPIOC, GPIOC_BUT8);
    but9_old_state = palReadPad(GPIOB, GPIOB_PB12);

    chThdSleepMilliseconds(50);
  }
}

int ButtonDown[9]={0};
int Button_db[9]={0};
int Button_state[9]={0};
int Button_edge[9]={0};

void runButton(void){
    uint8_t i = 0;
    ButtonDown[0] = !palReadPad(GPIOH, GPIOH_BUT1);
    ButtonDown[1] = !palReadPad(GPIOB, GPIOB_BUT2);
    ButtonDown[2] = !palReadPad(GPIOG, GPIOG_BUT3);
    ButtonDown[3] = !palReadPad(GPIOE, GPIOE_BUT4);
    ButtonDown[4] = !palReadPad(GPIOH, GPIOH_BUT5);
    ButtonDown[5] = !palReadPad(GPIOE, GPIOE_BUT6);
    ButtonDown[6] = !palReadPad(GPIOD, GPIOD_BUT7);
    ButtonDown[7] = !palReadPad(GPIOC, GPIOC_BUT8);
    ButtonDown[8] = !palReadPad(GPIOB, GPIOB_PB12);
    for (i=0;i<9;i++){
      if(ButtonDown[i] == 1 && Button_db[i] == 0){
        Button_state[i] = Button_state[i] ^ 1;
        Button_edge[i] = 1;
      }
      else{
        Button_edge[i] = 0;
      }
    }
    Button_db[0] = ButtonDown[0];
    Button_db[1] = ButtonDown[1];
    Button_db[2] = ButtonDown[2];
    Button_db[3] = ButtonDown[3];
    Button_db[4] = ButtonDown[4];
    Button_db[5] = ButtonDown[5];
    Button_db[6] = ButtonDown[6];
    Button_db[7] = ButtonDown[7];
    Button_db[8] = ButtonDown[8];
  return;
}


int app_init(void) {
  chMBObjectInit(&app_mb, msg_buf, UI_MB_SIZE);
  chThdCreateStatic(waApp, sizeof(waApp), LOWPRIO+1, menu.main, NULL);
  InitDriving();
  chThdCreateStatic(wa_ui_button_thread, sizeof(wa_ui_button_thread), LOWPRIO, ui_button_thread, NULL);
  return 0;
}

