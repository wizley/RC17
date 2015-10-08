/*
 * udc_lld.h
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#ifndef MODULES_UDC_UDC_LLD_H_
#define MODULES_UDC_UDC_LLD_H_

typedef enum{
  udc_lld_rx_idle = 0,
  udc_lld_rx_ready,
  udc_lld_rx_init
}udc_rx_frame_state_e;

typedef enum{
  udc_lld_tx_idle = 0,
  udc_lld_tx_ready
}udc_tx_frame_state_e;

typedef struct{
  uint16_t id;
  uint16_t payload;
  uint16_t checksum;
}udc_frame_t;


void udc_lld_init();
void udc_lld_start();
void udc_lld_stop();
void udc_lld_send();
void udc_lld_timer_init();
void udc_lld_timer_start();

#endif /* MODULES_UDC_UDC_LLD_H_ */
