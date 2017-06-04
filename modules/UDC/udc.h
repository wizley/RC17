/*
 * udc.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UDC_UDC_H_
#define MODULES_UDC_UDC_H_

#ifndef ID_SYNC
#define ID_SYNC 0
#endif
#ifndef ID_END
#define ID_END -1
#endif

typedef enum{
  UDC_UNINIT = 0,
  UDC_READY,
  UDC_BUSY,
  UDC_STOP
}udc_state_e;

typedef enum{
  UDC_CHECKSUM_ERROR,
  UDC_FRAMING_ERROR,
  UDC_TIMEOUT
}udc_error_metrics;

#include "udc_lld.h"

typedef void (*udc_message_cb)(void);
typedef UDC_Obj_t* UDC_ObjectList;

typedef struct{
  //uint32_t baudrate;//intializer element need to be constant, not a variable
  uint8_t autoretry;
  udc_message_cb cb;//to be implemented
}UDC_config_t;

void UDC_Init(UDC_config_t *config);
void UDC_Start(void);
void UDC_Stop(void);
void UDC_RegisterObjectList(void);
void UDC_RegisterCallback(void);
void UDC_PollObjectList(UDC_ObjectList object_list);
udc_rx_state_e UDC_Poll_Single(UDC_Obj_t* udc_object);
uint16_t UDC_GetStatistics(udc_error_metrics m);



#endif /* MODULES_UDC_UDC_H_ */
