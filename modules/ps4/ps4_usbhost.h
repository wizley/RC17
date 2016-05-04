/*
 * ps4.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Melvin
 */

#ifndef MODULES_PS4_PS4_USBHOST_H_
#define MODULES_PS4_PS4_USBHOST_H_

#include "usbh/dev/ds4.h"

typedef enum{
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
        SHARE = 4,
        OPTIONS = 5,
        L3 = 6,
        R3 = 7,
        L2 = 8,
        R2 = 9,
        L1 = 10,
        R1 = 11,
        TRIANGLE = 12,
        CIRCLE = 13,
        CROSS = 14,
        SQUARE = 15,
        PS = 16,
        TOUCHPAD = 17,
}ButtonEnum;

extern DS4_status_t ps4_data;
extern DS4_status_t old_data;
extern DS4_command_t cmd;

void ps4_usbhost_init(void);
#endif /* MODULES_PS4_PS4_USBHOST_H_ */
