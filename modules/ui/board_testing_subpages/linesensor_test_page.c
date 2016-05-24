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
#if USE_LINESENSOR_0 || USE_LINESENSOR_1 || USE_LINESENSOR_2 || USE_LINESENSOR_3
#include "linesensor.h"
#endif

#define barheight 50

GHandle console1;
GHandle linesensorpageContainer;

void linesensor_test_main(void *params){
  (void) params;
  linesensorpageContainer = createContainer(0, STATUS_BAR_HEIGHT, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT - STATUS_BAR_HEIGHT, FALSE);
  //gwinClear(pageContainer);
  console1 = createConsole(&linesensorpageContainer,0,STATUS_BAR_HEIGHT,GDISP_SCREEN_WIDTH,250);
  gwinRedraw(console1);
  gwinShow(linesensorpageContainer);
  ui_event *evt = NULL;
  DeactivateDriving();
  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_IMMEDIATE) == MSG_OK){

      switch(evt->type){
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){

          } else if(evt->data.button_state == UI_BUTTON_UP){
            linesensor_send_command(&LineSensor[0], ESTIM_BLACK);
          }else if(evt->data.button_state == UI_BUTTON_DOWN){
            linesensor_send_command(&LineSensor[0], ESTIM_WHITE);
          }else if(evt->data.button_state == UI_BUTTON_RESERVED1){
            linesensor_send_command(&LineSensor[1], ESTIM_BLACK);
          }else if(evt->data.button_state == UI_BUTTON_RESERVED2){
            linesensor_send_command(&LineSensor[1], ESTIM_WHITE);
          }
          break;
        case UI_STATUSBAR_TICK:
           status_bar_redraw();
          break;
        default:

          break;
      }
    }
    gwinClear(linesensorpageContainer);
    gwinClear(console1);
    gwinPrintf(console1, "Press Button 2 for L0black, Button 3 for L0white\r\n");
    gwinPrintf(console1, "Press Button 4 for L1black, Button 5 for L1white\r\n");
#if USE_LINESENSOR_0
    gwinPrintf(console1, "Alive: %d Position: %d Width: %d\r\n", LineSensor[0].Alive, LineSensor[0].Position[0], LineSensor[0].Position[1]);
#endif
#if USE_LINESENSOR_1
    gwinPrintf(console1, "Alive: %d Position: %d Width: %d\r\n", LineSensor[1].Alive, LineSensor[1].Position[0], LineSensor[1].Position[1]);
#endif
#if USE_LINESENSOR_2
    gwinPrintf(console1, "Alive: %d Position: %d Width: %d\r\n", LineSensor[2].Alive, LineSensor[2].Position[0], LineSensor[2].Position[1]);
#endif
#if USE_LINESENSOR_3
    gwinPrintf(console1, "Alive: %d Position: %d Width: %d\r\n", LineSensor[3].Alive, LineSensor[3].Position[0], LineSensor[3].Position[1]);
#endif
    //          //draw some bars like the old blueboard
    int i;
#if USE_LINESENSOR_0
    for(i=0; i<LineSensor[0].size; i++){
    gdispFillArea(0+i*(GDISP_SCREEN_WIDTH/LineSensor[0].size),200+(barheight-(((LineSensor[0].Data[i])/15.0)*barheight)),
                   GDISP_SCREEN_WIDTH/LineSensor[0].size,((LineSensor[0].Data[i])/15.0)*barheight,Green);
    }
#endif
#if USE_LINESENSOR_1
    for (i=0; i<LineSensor[1].size; i++){
    gdispFillArea(0+i*(GDISP_SCREEN_WIDTH/LineSensor[1].size),300+(barheight-(((LineSensor[1].Data[i])/15.0)*barheight)),
                  GDISP_SCREEN_WIDTH/LineSensor[1].size,((LineSensor[1].Data[i])/15.0)*barheight,Green);
    }
#endif
#if USE_LINESENSOR_2
    for (i=0; i<LineSensor[2].size; i++){
        gdispFillArea(0+i*(GDISP_SCREEN_WIDTH/LineSensor[2].size),300+(barheight-(((LineSensor[2].Data[i])/15.0)*barheight)),
                      GDISP_SCREEN_WIDTH/LineSensor[2].size,((LineSensor[2].Data[i])/15.0)*barheight,Green);
        }
#endif
#if USE_LINESENSOR_3
    for (i=0; i<LineSensor[3].size; i++){
        gdispFillArea(0+i*(GDISP_SCREEN_WIDTH/LineSensor[3].size),300+(barheight-(((LineSensor[3].Data[i])/15.0)*barheight)),
                      GDISP_SCREEN_WIDTH/LineSensor[3].size,((LineSensor[3].Data[i])/15.0)*barheight,Green);
        }
#endif
    chThdSleepMilliseconds(60);
  }

}


application line_sensor_test_app = {
     .name="Line sensor test",
     .main=linesensor_test_main
};
