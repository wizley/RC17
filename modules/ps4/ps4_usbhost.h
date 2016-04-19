/*
 * ps4.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Melvin
 */

#ifndef MODULES_PS4_PS4_USBHOST_H_
#define MODULES_PS4_PS4_USBHOST_H_

#include "usbh/dev/ds4.h"

extern DS4_status_t data;
extern DS4_command_t cmd;

extern void ps4_usbhost_init(void);
#endif /* MODULES_PS4_PS4_USBHOST_H_ */
