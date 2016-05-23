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
#include "widgets.h"
#include "status_bar.h"



void linesensor_test_main(void *params){
  GHandle pageContainer;
  (void) params;
   font_t font1 = gdispOpenFont("DejaVuSans32_aa");
  pageContainer = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);
  gwinShow(pageContainer);
  gwinClear(pageContainer);
  //gdispDrawString(0, STATUS_BAR_HEIGHT, "404 Not Found", font1, HTML2COLOR(0x09180A));

  ui_event *evt = NULL;

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_IMMEDIATE) == MSG_OK){

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
    //          //draw some bars like the old blueboard
    //          for(i=0; i<LineSensor[0].size; i++){
    //              gdispFillArea(0+i*(132/LineSensor[0].size),gdisplineheight*3+1+(gdisplineheight-(((LineSensor[0].Data[i])/15.0)*gdisplineheight)),132/LineSensor[0].size,((LineSensor[0].Data[i])/15.0)*gdisplineheight,White);
    //              gdispFillArea(0+i*(132/LineSensor[1].size),gdisplineheight*4+1+(gdisplineheight-(((LineSensor[1].Data[i])/15.0)*gdisplineheight)),132/LineSensor[1].size,((LineSensor[1].Data[i])/15.0)*gdisplineheight,White);
    //          }
    chThdSleepMilliseconds(100);
  }

}


application line_sensor_test_app = {
     .name="Line sensor test",
     .main=linesensor_test_main
};
