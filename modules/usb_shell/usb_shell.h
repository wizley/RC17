/*
 * usb_shell.h
 *
 *  Created on: Jun 21, 2015
 *      Author: u564
 */

#ifndef MODULES_USB_SHELL_USB_SHELL_H_
#define MODULES_USB_SHELL_USB_SHELL_H_

#define IS42S16400J_SIZE	0x1000000

void usb_shell_init(void);
void usb_shell_start(void);
void usb_shell_stop(void);
bool usb_shell_is_running(void);

#endif /* MODULES_USB_SHELL_USB_SHELL_H_ */
