/*
 * usb_shell.h
 *
 *  Created on: Jun 21, 2015
 *      Author: u564
 */

#ifndef MODULES_USB_SHELL_USB_SHELL_H_
#define MODULES_USB_SHELL_USB_SHELL_H_

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

#define IS42S16400J_SIZE	0x1000000

void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_reset(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_write(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_erase(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_selfrefresh(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_normal(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_check(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_sdram(BaseSequentialStream *chp, int argc, char *argv[]);


#endif /* MODULES_USB_SHELL_USB_SHELL_H_ */
