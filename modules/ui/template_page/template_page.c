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

void template_main(void *params){
  (void) params;

  font_t font1;
  font1 = gdispOpenFont("DejaVuSans32_aa");

  gdispClear(HTML2COLOR(0xEEEEEE));
  gdispDrawString(0, 0, "404 Not Found", font1, HTML2COLOR(0x09180A));

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
        default:

          break;
      }
    }
  }

}


application template = {
    .name = "Template",
    .main = template_main,
    .syn_flg = no_sync
};
