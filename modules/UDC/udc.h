/*
 * udc.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UDC_UDC_H_
#define MODULES_UDC_UDC_H_

typedef enum{
  UDC_INIT = 0,
  UDC_READY
}UDC_state_t;

typedef enum{
  UDC_NOERR = 0,
  UDC_CHECKSUM_ERR,
  UDC_FRAMING_ERR,
  UDC_NORESPONSE,
  UDC_RETRY_FAILED,
  UDC_RX_LENGTH_MISMATCH
}UDC_error_e;

typedef uint8_t* tx_data_ptr;
typedef uint8_t* rx_data_ptr;
typedef void (*rx_callback)();
typedef void (*udc_message_cb)();
typedef UDC_Obj_t* UDC_ObjectList;

typedef struct{
  uint8_t id;
  tx_data_ptr tx_data;
  uint8_t tx_len;
  rx_data_ptr rx_data;
  rx_callback rx_callback;
  uint8_t rx_len;

}UDC_Obj_t;



typedef struct{
  uint16_t baudrate;
  UDC_ObjectList udc_object_list;
  uint8_t autoretry;
  udc_message_cb cb;
}UDC_config_t;

void UDC_Init();
void UDC_Start();
void UDC_Stop();
void UDC_RegisterObjectList();
void UDC_RegisterCallback();
void UDC_PollObjectList();
void UDC_Poll_Single();
void UDC_GetStatistics();



#endif /* MODULES_UDC_UDC_H_ */
