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

// GHandles
GHandle ghContainerPage0;
GHandle ghContainer1;
GHandle ghProgressbar3;
GHandle ghContainer1_copy;
GHandle ghProgressbar2;
GHandle ghSlider1;
GHandle ghContainer1_copy_copy;
GHandle ghProgressbar1;
GHandle ghConsole;
GHandle ghButton_EME;
GHandle ghLabel_M1;
GHandle ghButton3;
GHandle ghButton2;
GHandle ghButton1;
GHandle ghLabel2;
GHandle ghLabel_Enc1_2;
GHandle ghButton_Back;
GHandle ghLabel_StatusBar;
GHandle ghCheckbox1;
GHandle ghLabel_Timer;
GHandle ghLabel6;
GHandle ghLabel_M2;
GHandle ghLabel_M3;
GHandle ghLabel_M4;
GHandle ghLabel_Enc3_4;
GHandle ghCheckbox2;

// Fonts
font_t dejavu_sans_20_anti_aliased;
font_t dejavu_sans_16_anti_aliased;
font_t dejavu_sans_12_anti_aliased;
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

  // create container widget: ghContainer1_copy
  wi.g.show = TRUE;
  wi.g.x = 440;
  wi.g.y = 250;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer1_copy = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // create container widget: ghContainer1_copy_copy
  wi.g.show = TRUE;
  wi.g.x = 260;
  wi.g.y = 250;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer1_copy_copy = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // create container widget: ghContainer1
  wi.g.show = TRUE;
  wi.g.x = 620;
  wi.g.y = 250;
  wi.g.width = 170;
  wi.g.height = 220;
  wi.g.parent = ghContainerPage0;
  wi.text = "Container1";
  wi.customDraw = gwinContainerDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghContainer1 = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);

  // Create progressbar widget: ghProgressbar3
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 20;
  wi.g.width = 140;
  wi.g.height = 20;
  wi.g.parent = ghContainer1;
  wi.text = "Progressbar3";
  wi.customDraw = gwinProgressbarDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghProgressbar3 = gwinProgressbarCreate(0, &wi);
  gwinProgressbarSetRange(ghProgressbar3, 0, 100);
  gwinProgressbarSetPosition(ghProgressbar3, 25);

  // Create progressbar widget: ghProgressbar2
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 20;
  wi.g.width = 140;
  wi.g.height = 20;
  wi.g.parent = ghContainer1_copy;
  wi.text = "Progressbar2";
  wi.customDraw = gwinProgressbarDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghProgressbar2 = gwinProgressbarCreate(0, &wi);
  gwinProgressbarSetRange(ghProgressbar2, 0, 100);
  gwinProgressbarSetPosition(ghProgressbar2, 25);

  // create button widget: ghSlider1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 60;
  wi.g.width = 140;
  wi.g.height = 20;
  wi.g.parent = ghContainer1_copy;
  wi.text = "Slider1";
  wi.customDraw = gwinSliderDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghSlider1 = gwinSliderCreate(0, &wi);
  gwinSliderSetRange(ghSlider1, 0, 100);
  gwinSliderSetPosition(ghSlider1, 35);
  gwinSetColor(ghSlider1, Black);
  gwinSetBgColor(ghSlider1, White);

  // Create progressbar widget: ghProgressbar1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 20;
  wi.g.width = 20;
  wi.g.height = 180;
  wi.g.parent = ghContainer1_copy_copy;
  wi.text = "Progressbar1";
  wi.customDraw = gwinProgressbarDraw_Std;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghProgressbar1 = gwinProgressbarCreate(0, &wi);
  gwinProgressbarSetRange(ghProgressbar1, 0, 100);
  gwinProgressbarSetPosition(ghProgressbar1, 25);

  // Create console widget: ghConsole
  wi.g.show = TRUE;
  wi.g.x = 0;
  wi.g.y = 30;
  wi.g.width = 270;
  wi.g.height = 130;
  wi.g.parent = ghContainerPage0;
  ghConsole = gwinConsoleCreate(0, &wi.g);
  gwinSetColor(ghConsole, Silver);
  gwinSetBgColor(ghConsole, Black);
  gwinSetFont(ghConsole, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghConsole);

  // create button widget: ghButton_EME
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 420;
  wi.g.width = 140;
  wi.g.height = 60;
  wi.g.parent = ghContainerPage0;
  wi.text = "STOP";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton_EME = gwinButtonCreate(0, &wi);
  gwinSetFont(ghButton_EME, dejavu_sans_32_anti_aliased);
  gwinRedraw(ghButton_EME);

  // Create label widget: ghLabel_M1
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 60;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "M1         0000        0000           1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_M1 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_M1, TRUE);

  // create button widget: ghButton3
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 370;
  wi.g.width = 70;
  wi.g.height = 40;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button3";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton3 = gwinButtonCreate(0, &wi);

  // create button widget: ghButton2
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 320;
  wi.g.width = 70;
  wi.g.height = 40;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button2";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton2 = gwinButtonCreate(0, &wi);

  // create button widget: ghButton1
  wi.g.show = TRUE;
  wi.g.x = 10;
  wi.g.y = 270;
  wi.g.width = 70;
  wi.g.height = 40;
  wi.g.parent = ghContainerPage0;
  wi.text = "Button1";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghButton1 = gwinButtonCreate(0, &wi);

  // Create label widget: ghLabel2
  wi.g.show = TRUE;
  wi.g.x = 620;
  wi.g.y = 30;
  wi.g.width = 170;
  wi.g.height = 160;
  wi.g.parent = ghContainerPage0;
  wi.text = "Label2";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = &BlackWidgetStyle;
  ghLabel2 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel2, FALSE);

  // Create label widget: ghLabel_Enc1_2
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 140;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Encoder1 : 00000 : Encoder2 : 00000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_Enc1_2 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_Enc1_2, TRUE);
  gwinSetFont(ghLabel_Enc1_2, dejavu_sans_16_anti_aliased);
  gwinRedraw(ghLabel_Enc1_2);

  // create button widget: ghButton_Back
  wi.g.show = TRUE;
  wi.g.x = 0;
  wi.g.y = 0;
  wi.g.width = 80;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "Back";
  wi.customDraw = gwinButtonDraw_Normal;
  wi.customParam = 0;
  wi.customStyle = &BlackWidgetStyle;
  ghButton_Back = gwinButtonCreate(0, &wi);

  // Create label widget: ghLabel_StatusBar
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 0;
  wi.g.width = 570;
  wi.g.height = 30;
  wi.g.parent = ghContainerPage0;
  wi.text = "CPU 50%  Motor Voltage 24.0V  MainBoard Voltage 7.4V";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_StatusBar = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_StatusBar, FALSE);
  gwinSetFont(ghLabel_StatusBar, dejavu_sans_20_anti_aliased);
  gwinRedraw(ghLabel_StatusBar);

  // create checkbox widget: ghCheckbox1
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 350;
  wi.g.width = 140;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Motors Online";
  wi.customDraw = gwinCheckboxDraw_CheckOnRight;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghCheckbox1 = gwinCheckboxCreate(0, &wi);
  gwinCheckboxCheck(ghCheckbox1, FALSE);
  gwinSetFont(ghCheckbox1, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghCheckbox1);

  // Create label widget: ghLabel_Timer
  wi.g.show = TRUE;
  wi.g.x = 40;
  wi.g.y = 170;
  wi.g.width = 130;
  wi.g.height = 70;
  wi.g.parent = ghContainerPage0;
  wi.text = "00:00";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = &WhiteWidgetStyle;
  ghLabel_Timer = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_Timer, FALSE);
  gwinSetFont(ghLabel_Timer, dejavu_sans_32_anti_aliased);
  gwinRedraw(ghLabel_Timer);

  // Create label widget: ghLabel6
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 40;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Motor  SetPoint  FeedBack  Current(mA)";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel6 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel6, FALSE);

  // Create label widget: ghLabel_M2
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 80;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "M2         0000        0000           1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_M2 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_M2, TRUE);

  // Create label widget: ghLabel_M3
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 100;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "M3         0000        0000           1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_M3 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_M3, TRUE);

  // Create label widget: ghLabel_M4
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 120;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "M4         0000        0000           1000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_M4 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_M4, TRUE);

  // Create label widget: ghLabel_Enc3_4
  wi.g.show = TRUE;
  wi.g.x = 280;
  wi.g.y = 160;
  wi.g.width = 330;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Encoder3 : 00000 : Encoder4 : 00000";
  wi.customDraw = gwinLabelDrawJustifiedLeft;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghLabel_Enc3_4 = gwinLabelCreate(0, &wi);
  gwinLabelSetBorder(ghLabel_Enc3_4, TRUE);

  // create checkbox widget: ghCheckbox2
  wi.g.show = TRUE;
  wi.g.x = 100;
  wi.g.y = 380;
  wi.g.width = 140;
  wi.g.height = 20;
  wi.g.parent = ghContainerPage0;
  wi.text = "Encoders Online";
  wi.customDraw = gwinCheckboxDraw_CheckOnRight;
  wi.customParam = 0;
  wi.customStyle = 0;
  ghCheckbox2 = gwinCheckboxCreate(0, &wi);
  gwinCheckboxCheck(ghCheckbox2, FALSE);
  gwinSetFont(ghCheckbox2, dejavu_sans_12_anti_aliased);
  gwinRedraw(ghCheckbox2);
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
  gwinWidgetClearInit(&wi);
  gwinSetDefaultFont(dejavu_sans_16_anti_aliased);
  gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
  gwinSetDefaultColor(Black);
  gwinSetDefaultBgColor(White);

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
        case UI_UDC_UPDATE:
             gwinPrintf(ghConsole, "abc def %d", evt->data.comm_info.M0.SetPoint);
             gwinRedraw(ghConsole);
             gwinSetText(ghLabel_M4, "M4         1000        1000           0000", TRUE);
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
