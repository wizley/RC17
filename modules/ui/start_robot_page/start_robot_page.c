/*
 * start_robot_main_page.c
 *
 *  Created on: 21 Dec 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"
#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
    #include "motor.h"
#endif
#if USE_ENCODER
#include "encoder.h"
#endif
#if USE_SERVO
#include "servo.h"
#endif
#include "widgets.h"
char * UIDrivingState[2] = {"activated","deactivated"}; //for ui

// GHandles
GHandle ghContainerPage0;
GHandle ghConsole;
GHandle ghConsole1;

// Fonts
font_t dejavu_sans_20_anti_aliased;
font_t dejavu_sans_16_anti_aliased;
font_t dejavu_sans_12_anti_aliased;
font_t dejavu_sans_32_anti_aliased;

static void createPagePage0(void)
{
  // create container widget: ghContainerPage0
  ghContainerPage0 = createContainer(0, 0, 800, 480, FALSE);

  // Create console widget: ghConsole
  ghConsole = createConsole(&ghContainerPage0, 0, 30, 270, 130);
  gwinSetColor(ghConsole, Silver);
  gwinSetBgColor(ghConsole, Black);
  gwinSetFont(ghConsole, dejavu_sans_32_anti_aliased);
  gwinRedraw(ghConsole);

  ghConsole1 = createConsole(&ghContainerPage0, 270,30,270,130);
  gwinSetColor(ghConsole1, Silver);
  gwinSetBgColor(ghConsole1, Black);
  gwinSetFont(ghConsole1, dejavu_sans_32_anti_aliased);
  gwinRedraw(ghConsole1);
}

void guiShowPage(unsigned pageIndex)
{
  // Hide all pages
  gwinHide(ghContainerPage0);

  // Show page selected page
  switch (pageIndex) {
  case 0:
    gwinShow(ghContainerPage0);
    break;

  default:
    break;
  }
}

void guiCreate(void)
{
  GWidgetInit wi;

  // Prepare fonts
  dejavu_sans_20_anti_aliased = gdispOpenFont("DejaVuSans20_aa");
  dejavu_sans_16_anti_aliased = gdispOpenFont("DejaVuSans16_aa");
  dejavu_sans_12_anti_aliased = gdispOpenFont("DejaVuSans12_aa");
  dejavu_sans_32_anti_aliased = gdispOpenFont("DejaVuSans32_aa");

  // Prepare images

  // GWIN settings
  gwinSetDefaultFont(dejavu_sans_32_anti_aliased);
  gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
  gwinSetDefaultColor(Black);
  gwinSetDefaultBgColor(White);

  // Create all the display pages
  createPagePage0();

  // Select the default display page
  guiShowPage(0);

  // Console sample text
  //gwinPrintf(ghConsole, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet");
}

void start_robot_main(void *params){
  (void) params;

  ui_event *evt = NULL;

  guiCreate();

  while(TRUE){

    if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

      switch(evt->type){
        case UI_INPUT_BUTTON:
          if(evt->data.button_state == UI_BUTTON_BACK){
            return;
          } else if(evt->data.button_state == UI_BUTTON_ENTER){
            ActivateDriving();
            gwinClear(ghConsole1);
            gwinPrintf(ghConsole1, UIDrivingState[DrivingState]);
          } else {

          }
          break;
        case UI_UDC_UPDATE:
             gwinClear(ghConsole);
             gwinPrintf(ghConsole, "Setpoint: %d\r\n", M[0].SetPoint);
             gwinPrintf(ghConsole, "feedback: %d\r\n", M[0].Feedback);
          break;
        default:
          break;
      }
    }
  }

}


application start_robot = {
    .name = "Start robot",
    .main = start_robot_main,
    .syn_flg = sync
};
