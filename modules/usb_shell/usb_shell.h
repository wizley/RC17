/*
 * usb_shell.h
 *
 *  Created on: Jun 21, 2015
 *      Author: u564
 */

#ifndef MODULES_USB_SHELL_USB_SHELL_H_
#define MODULES_USB_SHELL_USB_SHELL_H_

#define SDRAM_SIZE	0x1000000

void usb_shell_init(void);
void usb_shell_start(void);
void usb_shell_create(void);
void usb_shell_wait(void);
bool usb_is_active(void);

#endif /* MODULES_USB_SHELL_USB_SHELL_H_ */
