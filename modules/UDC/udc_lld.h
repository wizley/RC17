/*
 * udc_lld.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UDC_UDC_LLD_H_
#define MODULES_UDC_UDC_LLD_H_

typedef enum{
  udc_rx_idle = 0,
  udc_rx_active = 1,
  udc_rx_checksum_error = 2,
  udc_rx_framing_error = 4,
  udc_rx_timeout = 8,
  udc_rx_retry_failed = 16,
  udc_rx_state_error = 32,
  udc_rx_init = 64
}udc_rx_state_e;

typedef enum{
  udc_tx_idle = 0,
  udc_tx_active = 1
}udc_tx_state_e;

typedef uint8_t* udc_tx_data_t;
typedef uint8_t* udc_rx_data_t;
typedef void (*udc_rx_callback)(volatile void *);

typedef struct{
  int16_t id;
  udc_tx_data_t tx_data;
  uint8_t tx_len;
  udc_rx_data_t rx_data;
  uint8_t rx_len;
  udc_rx_callback rx_callback;
  volatile void *arg;
}UDC_Obj_t;

typedef struct{
  udc_state_e udc_state;
  udc_rx_state_e udc_rx_state;
  udc_tx_state_e udc_tx_state;
  event_source_t tx_evt;
  event_source_t rx_evt;
  mutex_t mutex;
  uint16_t framing_error;
  uint16_t checksum_error;
  uint16_t timeout_error;
}UDC_Driver;
extern UDC_Driver UDCD;

void udc_lld_init();
void udc_lld_start(void);
void udc_lld_stop(void);
udc_rx_state_e udc_lld_send(UDC_Obj_t* udc_object);
void udc_lld_timer_init(void);
void udc_lld_event_init(void);
void udc_lld_mutex_init(void);
void udc_lld_event_register(event_listener_t *el_tx, event_listener_t *el_rx);
void udc_lld_event_unregister(event_listener_t *el_tx, event_listener_t *el_rx);
udc_tx_state_e udc_lld_get_tx_event(event_listener_t *el_tx);
udc_rx_state_e udc_lld_get_rx_event(event_listener_t *el_rx);
void udc_lld_timer_start(void);


#endif /* MODULES_UDC_UDC_LLD_H_ */
