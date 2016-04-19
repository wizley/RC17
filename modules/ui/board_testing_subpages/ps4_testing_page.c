/*
 * template_page.c
 *
 *  Created on: 28 Oct 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#include "ps4_usbhost.h"

GHandle ps4Console;

void ps4_test_main(void *params){
  (void) params;
  GWidgetInit wi;
  gwinWidgetClearInit(&wi);
  font_t font1;
  font1 = gdispOpenFont("DejaVuSans32_aa");

  gdispClear(HTML2COLOR(0xEEEEEE));

  wi.g.show = TRUE;
  wi.g.x = 0;
  wi.g.y = 30;
  wi.g.width = 270;
  wi.g.height = 130;
  //wi.g.parent = ghContainerPage0;
  ps4Console = gwinConsoleCreate(0, &wi.g);
  gwinSetColor(ps4Console, Silver);
  gwinSetBgColor(ps4Console, Black);
  gwinSetFont(ps4Console, font1);

  ui_event *evt = NULL;

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

      switch(evt->type){
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){

          } else {

          }
          break;
        case UI_STATUSBAR_TICK:
             gwinClear(ps4Console);
             gwinPrintf(ps4Console, "%d %d %d %d\r\n", data.hat_left_x, data.hat_left_y, data.hat_right_x, data.hat_right_y);
             gwinRedraw(ps4Console);
        default:

          break;
      }
    }
  }

}


application ps4_test_app = {
    .name = "PS4 Test",
    .main = ps4_test_main
};
