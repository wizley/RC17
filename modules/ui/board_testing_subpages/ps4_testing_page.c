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
//#include "ps4_usbhost.h"
#include "ds4.h"
#include "widgets.h"

GHandle ps4Console;
GHandle pageContainer;

void ps4_test_main(void *params){
  (void) params;
  GWidgetInit wi;
  gwinWidgetClearInit(&wi);
  font_t font1;
  font1 = gdispOpenFont("DejaVuSans32_aa");


  pageContainer = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);
  ps4Console = createConsole(&pageContainer,0,STATUS_BAR_HEIGHT,800,480 - STATUS_BAR_HEIGHT);
  gwinSetColor(ps4Console, Black);
  gwinSetBgColor(ps4Console, White);
  gwinSetFont(ps4Console, font1);
  gwinShow(pageContainer);
  gwinClear(pageContainer);
  gwinPrintf(ps4Console, "PS4 Testing Console\r\n");
  gwinRedraw(ps4Console);
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
             status_bar_redraw();
          break;
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
