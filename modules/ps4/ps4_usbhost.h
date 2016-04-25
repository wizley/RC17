/*
 * ps4.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Melvin
 */

#ifndef MODULES_PS4_PS4_USBHOST_H_
#define MODULES_PS4_PS4_USBHOST_H_

#include "usbh/dev/ds4.h"

extern DS4_status_t ps4_data;
extern DS4_command_t cmd;

uint8_t DS4_ButtonPress(ButtonEnum b);

extern uint8_t PS4_BUTTONS_BITMASK[];
void ps4_usbhost_init(void);
#endif /* MODULES_PS4_PS4_USBHOST_H_ */
