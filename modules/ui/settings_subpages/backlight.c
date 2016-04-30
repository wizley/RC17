/*
 * backlight.c
 *
 *  Created on: Apr 30, 2016
 *      Author: Melvin
 */
#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "app.h"

void backlight_main(void){
  gdispSetBacklight(50);
}

application set_backlight = { .name="Set backlight", .main=backlight_main, .syn_flg = no_sync };

