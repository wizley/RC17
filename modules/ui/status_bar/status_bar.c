/*
 * status_bar.c
 *
 *  Created on: Apr 22, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "udc.h"
#include "status_bar.h"
#include "widgets.h"

static font_t f1;
void status_bar_redraw(){
 //get the online status of all board
  //check voltage
  //get the rtc
  char * buffer;
  sprintf(buffer, "M");
  gdispDrawString(0,0,buffer, f1, Black);
}

void status_bar_init(){
  //intitialize the rtc driver
  font_t f1 = gdispOpenFont("DroidSans23");
  //gdispOpenFont(dejavu_sans_20_anti_aliased);
}
