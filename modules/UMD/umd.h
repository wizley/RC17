/*
 * udc_lld.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UMD_UMD_H_
#define MODULES_UMD_UMD_H_

#define ID_SYNC 0
#define ID_END -1

#define UMD_OBJECTLIST_END {ID_END, NULL, 0, NULL, NULL, 0, NULL, NULL}

typedef enum{
  UMD_UNINIT = 0,
  UMD_READY,
  UMD_STOP
}umd_state_e;

typedef enum{
  UMD_OK = 0,
  UMD_TIMEOUT,
  UMD_CHECKSUM_ERROR
}umd_return_e;


typedef struct{
  /**
   * @brief Object id
   */
  int16_t                id;
  /**
   * @brief Transmit data pointer
   */
  uint8_t*               tx_data;
  /**
   * @brief Transmit data length
   */
  uint8_t                tx_len;
  /**
   * @brief Callback before transmission
   */
  void                   (*tx_callback)(void *);
  /**
   * @brief Receive data pointer
   */
  uint8_t*               rx_data;
  /**
   * @brief Receive data length
   */
  uint8_t                rx_len;
  /**
   * @brief Callback after successful data receive
   */
  void                   (*rx_callback)(void *);
  /**
   * @brief Pointer passed to callbacks
   */
  void*                  cb_arg;
}UMD_Obj_t;


typedef struct{
  umd_state_e state;
  uint16_t framing_error;
  uint16_t checksum_error;
}UMD_Driver;
extern UMD_Driver UMDD;

void UMD_Master_Init(void);
void UMD_Master_Start(void);
void UMD_Master_Stop(void);
umd_return_e UMD_Poll_Single(UMD_Obj_t* udc_object);
void UMD_PollObjectList(UMD_Obj_t* object_list);


#endif /* MODULES_UMD_UMD_H_ */
