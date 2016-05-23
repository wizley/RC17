/*
 * udc_lld.c
 *
 *  Created on: 8 Oct 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "udc.h"

static uint16_t tx_buffer[32];
static thread_t* udc_lld_thread_ptr = NULL;
//static uint16_t rx_buffer[32];
//static uint8_t rx_checksum;
typedef struct{
  uint16_t rx_buffer[32];
  uint8_t rx_len;
  uint8_t rx_count;
  uint8_t *out_data_ptr;
  uint8_t checksum;
}udc_lld_rx_frame_t;
static volatile udc_lld_rx_frame_t rx_frame;



//static volatile udc_lld_rx_state_e udc_rx_state;
//static volatile udc_lld_tx_state_e udc_tx_state;

UDC_Driver UDCD;

#define UDC_UART UARTD1
#define UDC_TIMER GPTD14

#define TIMER_FREQ (2000000.0)
#define RCV_TIMEOUT15 (TIMER_FREQ / 625000.0 * 11.0 * 1.5)
#define RCV_TIMEOUT25 (TIMER_FREQ / 625000.0 * 11.0 * 2.5)

#define TX_EVENT EVENT_MASK(0)
#define RX_EVENT EVENT_MASK(1)

void udc_lld_txend(UARTDriver *uartp);
void udc_lld_rxend(UARTDriver *uartp);
void udc_lld_rxchar(UARTDriver *uartp, uint16_t c);
void udc_lld_rxerr(UARTDriver *uartp, uartflags_t e);

UARTConfig udc_uart_cfg = {
  NULL, /* End of Transmission buffer callback               */
  udc_lld_txend, /* Physical end of transmission callback             */
  udc_lld_rxend, /* Receive buffer filled callback                    */
  udc_lld_rxchar, /* Char received while out of the UART_RECEIVE state */
  udc_lld_rxerr, /* Receive error callback                            */
  625000UL, /* Baudrate                                          */
  USART_CR1_M | USART_CR1_RE | USART_CR1_TE, /* cr1 register values     */
  USART_CR2_LBDL, /* cr2 register values                               */
  0 /* cr3 register values                               */
};

void udc_lld_timer_cb(GPTDriver *gptp);

GPTConfig udc_gpt_cfg = {
  TIMER_FREQ, /* Timer clock in Hz. */
  udc_lld_timer_cb, /* Timer callback     */
  0,
  0
};

static THD_WORKING_AREA(udc_lld_process_wa, 256);
static THD_FUNCTION(udc_lld_process, arg) {
  (void)arg;
  thread_t* p;
  event_listener_t el_tx, el_rx;
  chRegSetThreadName("UDC Data Handler");

  udc_lld_event_register(&el_tx, &el_rx);

  while (!chThdShouldTerminateX()) {

    p = chMsgWait();

    UDC_Obj_t *udc_object = (UDC_Obj_t*) chMsgGet(p);

    uint16_t *tx_buf_ptr = tx_buffer;
    *tx_buf_ptr++ = udc_object->id | 0x100;
    uint8_t tx_checksum = udc_object->id ^ 0xAA;
    rx_frame.checksum = udc_object->id;
    rx_frame.rx_len = udc_object->rx_len + 1;
    rx_frame.rx_count = 0;
    rx_frame.out_data_ptr = udc_object->rx_data;

    uint8_t i;
    for(i = 0; i < udc_object->tx_len; i++){
      *tx_buf_ptr++ = udc_object->tx_data[i];
      tx_checksum ^= udc_object->tx_data[i];
    }
    *tx_buf_ptr = tx_checksum;

    uartStartSend(&UDC_UART, i + 2, tx_buffer);
    UDCD.udc_tx_state = udc_tx_active;

    if(udc_object->rx_len > 1){
      uartStopReceive(&UDC_UART);
      uartStartReceive(&UDC_UART, rx_frame.rx_len, rx_frame.rx_buffer);
      UDCD.udc_rx_state = udc_rx_active;
      gptStopTimer(&UDC_TIMER);
      gptStartOneShot(&UDC_TIMER, RCV_TIMEOUT25 * rx_frame.rx_len);
//      gptStartOneShot(&UDC_TIMER, RCV_TIMEOUT25);
      UDCD.udc_rx_state = udc_lld_get_rx_event(&el_rx);
    }else{
      UDCD.udc_rx_state = udc_rx_idle;
    }

    UDCD.udc_tx_state = udc_lld_get_tx_event(&el_tx);
    chMsgRelease(p, (msg_t)UDCD.udc_rx_state);

  }

  udc_lld_event_unregister(&el_tx, &el_rx);

}

void udc_lld_init(void){
  //(void) baudrate;
  udc_lld_timer_init();
  udc_lld_event_init();
  udc_lld_mutex_init();
  UDCD.udc_state = UDC_STOP;

}

void udc_lld_timer_init(void){
  gptStart(&UDC_TIMER, &udc_gpt_cfg);
}

void udc_lld_event_init(void){
  osalEventObjectInit(&UDCD.tx_evt);
  osalEventObjectInit(&UDCD.rx_evt);
}

void udc_lld_mutex_init(void){
  osalMutexObjectInit(&UDCD.mutex);
}

void udc_lld_event_register(event_listener_t *el_tx, event_listener_t *el_rx){
  chEvtRegisterMask(&UDCD.tx_evt, el_tx, TX_EVENT);
  chEvtRegisterMask(&UDCD.rx_evt, el_rx, RX_EVENT);
}

void udc_lld_event_unregister(event_listener_t *el_tx, event_listener_t *el_rx){
  chEvtUnregister(&UDCD.tx_evt, el_tx);
  chEvtUnregister(&UDCD.rx_evt, el_rx);
}

udc_tx_state_e udc_lld_get_tx_event(event_listener_t *el_tx){
  chEvtWaitOne(TX_EVENT);
  return chEvtGetAndClearFlags(el_tx);
}

udc_rx_state_e udc_lld_get_rx_event(event_listener_t *el_rx){
  chEvtWaitOne(RX_EVENT);
  return chEvtGetAndClearFlags(el_rx);
}

void udc_lld_start(void){
  uartStart(&UDC_UART, &udc_uart_cfg);
  udc_lld_thread_ptr = chThdCreateStatic(udc_lld_process_wa, sizeof(udc_lld_process_wa),HIGHPRIO,
        udc_lld_process, NULL);
  UDCD.udc_state = UDC_READY;
}

void udc_lld_stop(void){
  uartStop(&UDC_UART);
  chThdTerminate(udc_lld_thread_ptr);
  udc_lld_thread_ptr = NULL;
  UDCD.udc_state = UDC_STOP;
}


udc_rx_state_e udc_lld_send(UDC_Obj_t* udc_object){
  return (udc_rx_state_e)chMsgSend(udc_lld_thread_ptr, (msg_t)udc_object);
}



void udc_lld_txend(UARTDriver *uartp) {
  (void) uartp;
  UDCD.udc_tx_state = udc_tx_idle;
  chSysLockFromISR();
  osalEventBroadcastFlagsI(&UDCD.tx_evt, (eventflags_t)UDCD.udc_tx_state);
  chSysUnlockFromISR();

}

void udc_lld_rxerr(UARTDriver *uartp, uartflags_t e) {
  (void) uartp;
  (void) e;
  UDCD.framing_error++;
  UDCD.udc_rx_state = udc_rx_framing_error;
}

void udc_lld_rxchar(UARTDriver *uartp, uint16_t c) {
  //this callback is only invoked when receiving character but not at RX_ACTIVE STATE
  (void) uartp;
//  chSysLockFromISR();
//  gptStopTimerI(&UDC_TIMER);
//  chSysUnlockFromISR();
//  switch(UDCD.udc_rx_state){
//    case udc_rx_init:
//      UDCD.udc_rx_state = udc_rx_state_error;
//      break;
//    case udc_rx_idle:
//      UDCD.udc_rx_state = udc_rx_state_error;
//      break;
//    case udc_rx_active:
//      rx_frame.rx_buffer[rx_frame.rx_count++] = c;
//      if(rx_frame.rx_count <= rx_frame.rx_len) rx_frame.checksum ^= c;
//      if(rx_frame.rx_count == rx_frame.rx_len){
//        if(rx_frame.checksum == 0xAA){
//          for(rx_frame.rx_count = 0; rx_frame.rx_count < rx_frame.rx_len-1; rx_frame.rx_count++){
//            *rx_frame.out_data_ptr++ = rx_frame.rx_buffer[rx_frame.rx_count];
//          }
//          UDCD.udc_rx_state = udc_rx_idle;
//        }else{
//          UDCD.checksum_error++;
//          UDCD.udc_rx_state = udc_rx_checksum_error;
//        }
//        chSysLockFromISR();
//        osalEventBroadcastFlagsI(&UDCD.rx_evt, (eventflags_t)UDCD.udc_rx_state);
//        chSysUnlockFromISR();
//        return;
//      }
//      chSysLockFromISR();
//      gptStartOneShotI(&UDC_TIMER, RCV_TIMEOUT15);
//      chSysUnlockFromISR();
//      break;
//    default:
//      UDCD.udc_rx_state = udc_rx_state_error;
//      break;
//
//  }
}

void udc_lld_rxend(UARTDriver *uartp) {
  (void) uartp;
  //UDCD.udc_rx_state = udc_rx_idle;
  uint8_t i;
  chSysLockFromISR();
    gptStopTimerI(&UDC_TIMER);
    chSysUnlockFromISR();
    switch(UDCD.udc_rx_state){
      case udc_rx_init:
        UDCD.udc_rx_state = udc_rx_state_error;
        break;
      case udc_rx_idle:
        UDCD.udc_rx_state = udc_rx_state_error;
        break;
      case udc_rx_active:
        for (i = 0; i < rx_frame.rx_len; i++) {
            rx_frame.checksum ^= rx_frame.rx_buffer[i];
          }

          if (rx_frame.checksum == 0xAA) {
            for (i = 0; i < rx_frame.rx_len-1; i++) {
              rx_frame.out_data_ptr[i] = rx_frame.rx_buffer[i];
            }
            UDCD.udc_rx_state = udc_rx_idle;
          }else{
            UDCD.checksum_error++;
            UDCD.udc_rx_state = udc_rx_checksum_error;
          }
        break;
      case udc_rx_framing_error:
        //palClearPad(GPIOC, GPIOC_LED_R);
        break;
      case udc_rx_state_error:
        break;
      case udc_rx_timeout:
        UDCD.timeout_error++;
        break;
      default:
        UDCD.udc_rx_state = udc_rx_state_error;
        break;
    }
    chSysLockFromISR();
    osalEventBroadcastFlagsI(&UDCD.rx_evt, (eventflags_t)UDCD.udc_rx_state);
    chSysUnlockFromISR();
    return;
}

void udc_lld_timer_cb(GPTDriver *gptp) {
  (void) gptp;
  UDCD.timeout_error++;
  UDCD.udc_rx_state = udc_rx_timeout;
  chSysLockFromISR();
  osalEventBroadcastFlagsI(&UDCD.rx_evt, (eventflags_t)udc_rx_timeout);
  chSysUnlockFromISR();
}
