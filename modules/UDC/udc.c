/*
 * udc.c
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "udc.h"

static uint8_t retry_count = 0;

void UDC_Init(UDC_config_t *config){
  udc_lld_init();
  retry_count = config->autoretry;
}


void UDC_Start(void){
  udc_lld_start();
}


void UDC_Stop(void){
  udc_lld_stop();
}


void UDC_RegisterObjectList(void);


void UDC_RegisterCallback(void);

void UDC_PollObjectList(UDC_ObjectList object_list){
  uint8_t failcount = 0;
  udc_rx_state_e state;
  UDC_Obj_t* udc_object = object_list;
  osalDbgAssert(UDCD.udc_state == UDC_READY, "invalid state");
  osalMutexLock(&UDCD.mutex);
  if(udc_object == NULL) return;
  while(udc_object->id != -1){
    do{
      if (udc_object->tx_callback != NULL)
         udc_object->tx_callback(udc_object->tx_arg);
      state = udc_lld_send(udc_object);
    }while((state != udc_rx_idle) && (failcount++ < retry_count));
    if((state == udc_rx_idle) && (udc_object->rx_callback != NULL))
      udc_object->rx_callback(udc_object->rx_arg);
    udc_object++;
  }
  osalMutexUnlock(&UDCD.mutex);
  return;
}


udc_rx_state_e UDC_Poll_Single(UDC_Obj_t* udc_object){
  uint8_t failcount = 0;
  udc_rx_state_e state;
  osalDbgAssert(UDCD.udc_state == UDC_READY, "invalid state");
  osalMutexLock(&UDCD.mutex);
  do{
    if (udc_object->tx_callback != NULL)
       udc_object->tx_callback(udc_object->tx_arg);
    state = udc_lld_send(udc_object);
  }while((state != udc_rx_idle) && (failcount++ < retry_count));
  if((state == udc_rx_idle) && (udc_object->rx_callback != NULL))
    udc_object->rx_callback(udc_object->rx_arg);
  osalMutexUnlock(&UDCD.mutex);
  return state;
}


uint16_t UDC_GetStatistics(udc_error_metrics m){
    if (m == UDC_CHECKSUM_ERROR)
      return UDCD.checksum_error;
    else if(m == UDC_FRAMING_ERROR)
      return UDCD.framing_error;
    else if(m == UDC_TIMEOUT)
      return UDCD.timeout_error;
    else
      return 0;
}
