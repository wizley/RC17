
#ifndef MODULES_DS4_DS4_H_
#define MODULES_DS4_DS4_H_

#include "usbh/dev/ds4.h"

#define DS4_MB_SIZE 10

extern mailbox_t ds4_mb;

extern DS4_status_t DS4;

void DS4_Start(void);
void DS4_SetLED(uint8_t r, uint8_t g, uint8_t b);
void DS4_SetFlash(uint8_t ontime, uint8_t offtime);
void DS4_SetRumble(uint8_t small, uint8_t big);
bool DS4_IsConnected(void);


#endif /* MODULES_DS4_DS4_H_ */
