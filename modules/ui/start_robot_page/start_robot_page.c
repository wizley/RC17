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

#include "colors.h"
#include "widgetstyles.h"

// GListeners
GListener gl;

// GHandles
GHandle ghContainerPage0;
GHandle ghContainer1;
GHandle ghProgressbar1;
GHandle ghContainer2;
GHandle ghProgressbar2;
GHandle ghContainer3;
GHandle ghContainer4;
GHandle ghLabelm0;
GHandle ghLabelm1;
GHandle ghLabelm2;
GHandle ghLabelm3;
GHandle ghLabelm4;
GHandle ghLabelm5;
GHandle ghLabelm6;
GHandle ghLabelm7;
GHandle ghLabele12;
GHandle ghLabele34;
GHandle ghLabel2;
GHandle ghConsole;
GHandle ghButtonStop;
GHandle ghButton1;
GHandle ghButton2;
GHandle ghButton3;
GHandle ghCheckboxMotor;
GHandle ghCheckboxEncoder;
GHandle ghLabelTimer;
GHandle ghButtonBack;
GHandle ghLabelStatus;
GHandle ghLabel35;
GHandle ghCheckboxDS4;

// Fonts
font_t dejavu_sans_16_anti_aliased;
font_t dejavu_sans_10;
font_t dejavu_sans_12_anti_aliased;
font_t dejavu_sans_24_anti_aliased;
font_t dejavu_sans_32_anti_aliased;

static void createPagePage0(void)
{
  GWidgetInit wi;
  gwinWidgetClearInit(&wi);


  // create container widget: ghContainerPage0
  wi.g.show = FALSE;
  wi.g.x = 0;
  wi.g.y = 0;
  wi.g.width = 800;
  wi.g.height = 480;
  wi.g.parent = 0;
  wi.text = "Container";
  wi.customDraw = 0;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainerPage0 = gwinContainerCreate(0, &wi, 0);

  // create container widget: ghContainer2
  wi.g.show = TRUE;
  wi.g.x = 440;
  wi.g.y = 260;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer2 = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // create container widget: ghContainer4
  wi.g.show = TRUE;
  wi.g.x = 240;
  wi.g.y = 20;
  wi.g.width = 270;
  wi.g.height = 230;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container4";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer4 = gwinContainerCreate(0, &wi, 0);

  // create container widget: ghContainer3
  wi.g.show = TRUE;
  wi.g.x = 630;
  wi.g.y = 260;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer3 = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // create container widget: ghContainer1
  wi.g.show = TRUE;
  wi.g.x = 250;
  wi.g.y = 260;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer1 = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // Create progressbar widget: ghProgressbar1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 20;
  wi.g.width = 20;
  wi.g.height = 170;
  wi.g.parent = ghContainer1;
  wi.text = "Progressbar1";
  wi.customDraw = gwinProgressbarDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghProgressbar1 = gwinProgressbarCreate(0, &wi);
  gwinProgressbarSetRange(ghProgressbar1, 0, 100);
  gwinProgressbarSetPosition(ghProgressbar1, 25);
  gwinSetFont(ghProgressbar1, dejavu_sans_10);
  gwinRedraw(ghProgressbar1);

  // Create progressbar widget: ghProgressbar2
  wi.g.show = TRUE;
  wi.g.x = 20;
  wi.g.y = 90;
  wi.g.width = 130;
  wi.g.height = 20;
  wi.g.parent = ghContainer2;
  wi.text = "Progressbar2";
  wi.customDraw = gwinProgressbarDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghProgressbar2 = gwinProgressbarCreate(0, &wi);
  gwinProgressbarSetRange(ghProgressbar2, 0, 100);
  gwinProgressbarSetPosition(ghProgressbar2, 25);

  // Create label widget: ghLabelm0
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 30;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M0       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm0 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm0, TRUE);
  gwinSetFont(ghLabelm0, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm0);

  // Create label widget: ghLabelm1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 50;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M1       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm1 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm1, TRUE);
  gwinSetFont(ghLabelm1, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm1);

  // Create label widget: ghLabelm2
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 70;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M2       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm2 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm2, TRUE);
  gwinSetFont(ghLabelm2, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm2);

  // Create label widget: ghLabelm3
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 90;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M3       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm3 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm3, TRUE);
  gwinSetFont(ghLabelm3, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm3);

  // Create label widget: ghLabelm4
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 110;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M4       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm4 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm4, TRUE);
  gwinSetFont(ghLabelm4, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm4);

  // Create label widget: ghLabelm5
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 130;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M5       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm5 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm5, TRUE);
  gwinSetFont(ghLabelm5, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm5);

  // Create label widget: ghLabelm6
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 150;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M6       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm6 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm6, TRUE);
  gwinSetFont(ghLabelm6, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm6);

  // Create label widget: ghLabelm7
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 170;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "M7       +0000      +0000       +1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelm7 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelm7, TRUE);
  gwinSetFont(ghLabelm7, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabelm7);

  // Create label widget: ghLabele12
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 190;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "E1 : +00000  E2 : +00000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabele12 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabele12, TRUE);
  gwinSetFont(ghLabele12, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabele12);

  // Create label widget: ghLabele34
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 210;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "E3 : +00000  E4 : +00000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabele34 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabele34, TRUE);
  gwinSetFont(ghLabele34, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabele34);

  // Create label widget: ghLabel2
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 10;
  wi.g.width = 250;
  wi.g.height = 20;
  wi.g.parent = ghContainer4;
  wi.text = "Motor  SetPoint  FeedBack  Current(mA)";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel2 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel2, FALSE);
  gwinSetFont(ghLabel2, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghLabel2);

  // Create console widget: ghConsole
  wi.g.show = TRUE;
  wi.g.x = 0;
  wi.g.y = 30;
  wi.g.width = 220;
  wi.g.height = 140;
  wi.g.parent = ghContainerPage0;
  ghConsole = gwinConsoleCreate(0, &wi.g);
  gwinSetColor(ghConsole, silver_studio);
  gwinSetBgColor(ghConsole, black_studio);
  gwinSetFont(ghConsole, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghConsole);

  // create button widget: ghButtonStop
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 410;
  wi.g.width = 110;
  wi.g.height = 60;
  wi.g.parent = ghContainerPage0;
  wi.text = "Stop";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButtonStop = gwinButtonCreate(0, &wi);
  gwinSetFont(ghButtonStop, dejavu_sans_24_anti_aliased);
  gwinRedraw(ghButtonStop);

  // create button widget: ghButton1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 260;
  wi.g.width = 80;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button1";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton1 = gwinButtonCreate(0, &wi);

  // create button widget: ghButton2
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 310;
  wi.g.width = 80;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button2";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton2 = gwinButtonCreate(0, &wi);

  // create button widget: ghButton3
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 360;
  wi.g.width = 80;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button3";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton3 = gwinButtonCreate(0, &wi);

  // create checkbox widget: ghCheckboxMotor
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 340;
  wi.g.width = 130;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Motors Online";
  wi.customDraw = gwinCheckboxDraw_CheckOnRight;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghCheckboxMotor = gwinCheckboxCreate(0, &wi);
  gwinCheckboxCheck(ghCheckboxMotor, FALSE);
  gwinSetFont(ghCheckboxMotor, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghCheckboxMotor);

  // create checkbox widget: ghCheckboxEncoder
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 370;
  wi.g.width = 130;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Encoders Online";
  wi.customDraw = gwinCheckboxDraw_CheckOnRight;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghCheckboxEncoder = gwinCheckboxCreate(0, &wi);
  gwinCheckboxCheck(ghCheckboxEncoder, FALSE);
  gwinSetFont(ghCheckboxEncoder, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghCheckboxEncoder);

  // Create label widget: ghLabelTimer
  wi.g.show = TRUE;
  wi.g.x = 50;
  wi.g.y = 190;
  wi.g.width = 120;
  wi.g.height = 40;
  wi.g.parent = ghContainerPage0;
  wi.text = "00:00";
  wi.customDraw = gwinLabelDrawJustifiedCenter;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelTimer = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelTimer, FALSE);
  gwinSetFont(ghLabelTimer, dejavu_sans_32_anti_aliased);
  gwinRedraw(ghLabelTimer);

  // create button widget: ghButtonBack
  wi.g.show = TRUE;
  wi.g.x = 0;
  wi.g.y = 0;
  wi.g.width = 80;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "Back";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = &black;
  ghButtonBack = gwinButtonCreate(0, &wi);

  // Create label widget: ghLabelStatus
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 0;
  wi.g.width = 500;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "CPU 50% Motor Voltage 24.0V MainBoard Voltage 7.4V";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabelStatus = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabelStatus, FALSE);
  gwinSetFont(ghLabelStatus, dejavu_sans_16_anti_aliased);
  gwinRedraw(ghLabelStatus);

  // Create label widget: ghLabel35
  wi.g.show = TRUE;
  wi.g.x = 560;
  wi.g.y = 0;
  wi.g.width = 240;
  wi.g.height = 240;
  wi.g.parent = ghContainerPage0;
  wi.text = "Label35";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = &black;
  ghLabel35 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel35, FALSE);

  // create checkbox widget: ghCheckboxDS4
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 310;
  wi.g.width = 130;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "DS4 Online";
  wi.customDraw = gwinCheckboxDraw_CheckOnRight;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghCheckboxDS4 = gwinCheckboxCreate(0, &wi);
  gwinCheckboxCheck(ghCheckboxDS4, FALSE);
  gwinSetFont(ghCheckboxDS4, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghCheckboxDS4);
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
  dejavu_sans_16_anti_aliased = gdispOpenFont("DejaVuSans16_aa");
  dejavu_sans_10 = gdispOpenFont("DejaVuSans10");
  dejavu_sans_12_anti_aliased = gdispOpenFont("DejaVuSans12_aa");
  dejavu_sans_24_anti_aliased = gdispOpenFont("DejaVuSans24_aa");
  dejavu_sans_32_anti_aliased = gdispOpenFont("DejaVuSans32_aa");

  // Prepare images

  // GWIN settings
  gwinWidgetClearInit(&wi);
  gwinSetDefaultFont(dejavu_sans_16_anti_aliased);
  gwinSetDefaultStyle(&white, FALSE);
  gwinSetDefaultColor(black_studio);
  gwinSetDefaultBgColor(white_studio);

  // Create all the display pages
  createPagePage0();

  // Select the default display page
  guiShowPage(0);

  // Console sample text
  gwinPrintf(ghConsole, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet");
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

          } else {

          }
          break;
        default:

          break;
      }
    }
  }

}


application start_robot = {
    .name = "Start robot",
    .main = start_robot_main
};
