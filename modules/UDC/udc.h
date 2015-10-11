/*
 * udc.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UDC_UDC_H_
#define MODULES_UDC_UDC_H_

typedef enum{
  UDC_UNINIT = 0,
  UDC_READY,
  UDC_BUSY,
  UDC_STOP
}udc_state_e;

#include "udc_lld.h"

typedef void (*udc_message_cb)(void);
typedef UDC_Obj_t* UDC_ObjectList;

typedef struct{
  uint32_t baudrate;
  UDC_ObjectList udc_object_list;
  uint8_t autoretry;
  udc_message_cb cb;
}UDC_config_t;

void UDC_Init(UDC_config_t *config);
void UDC_Start(void);
void UDC_Stop(void);
void UDC_RegisterObjectList(void);
void UDC_RegisterCallback(void);
void UDC_PollObjectList(UDC_ObjectList object_list);
udc_rx_state_e UDC_Poll_Single(UDC_Obj_t* udc_object);
void UDC_GetStatistics(void);



#endif /* MODULES_UDC_UDC_H_ */
