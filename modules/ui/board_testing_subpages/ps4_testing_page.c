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
#include "status_bar.h"
#include "ps4_usbhost.h"
#include "widgets.h"

GHandle ps4Console;

void ps4_test_main(void *params){
  (void) params;
  GWidgetInit wi;
  gwinWidgetClearInit(&wi);
  font_t font1;
  font1 = gdispOpenFont("DejaVuSans32_aa");

  gdispClear(HTML2COLOR(0xEEEEEE));
  ps4Console = createConsole(NULL,0,STATUS_BAR_HEIGHT,800,480);
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
             gwinPrintf(ps4Console, "\r\n 1 \r\n");
             gwinRedraw(ps4Console);
          break;
        case UI_UDC_UPDATE:
             //gwinClear(ps4Console);
             gwinPrintf(ps4Console, "\r\n %d \r\n", (ps4_data.btns.val) & (1UL << PS4_BUTTONS_BITMASK[CROSS]));
             gwinRedraw(ps4Console);
          break;
        default:

          break;
      }
    }
  }

}


application ps4_test_app = {
    .name = "PS4 Test",
    .main = ps4_test_main,
    .syn_flg = sync //TODO: change to no_sync later
};
