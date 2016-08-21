
#include "ch.h"
#include "hal.h"
#include "umd.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/
#define UMD_UART UARTD1
#define UMD_TIMER GPTD14

#define BAUDERATE 625000UL
#define EXTRA_TIMEOUT_US 100

#define TIMER_FREQ (2000000.0)
#define EXTRA_TIMEOUT_TICK (TIMER_FREQ / 1000000.0 * EXTRA_TIMEOUT_US)
#define BYTE_TIMEOUT(n) (TIMER_FREQ / BAUDERATE * 11.0 * n + EXTRA_TIMEOUT_TICK)

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

static uint16_t tx_buffer[32];
static uint16_t rx_buffer[32];
static thread_t* umd_thread_ptr = NULL;
static thread_reference_t umd_thread_ref = NULL;
static mutex_t umd_mutex;

typedef struct{
  uint8_t rx_len;
  uint8_t *out_data_ptr;
  uint8_t checksum;
}umd_rx_frame_t;
static volatile umd_rx_frame_t rx_frame;


static void umd_rxend(UARTDriver *uartp);
static void umd_rxerr(UARTDriver *uartp, uartflags_t e);
static void umd_txend(UARTDriver *uartp);

UARTConfig umd_uart_cfg = {
  NULL, /* End of Transmission buffer callback               */
  umd_txend, /* Physical end of transmission callback             */
  umd_rxend, /* Receive buffer filled callback                    */
  NULL, /* Char received while out of the UART_RECEIVE state */
  umd_rxerr, /* Receive error callback                            */
  BAUDERATE, /* Baudrate                                          */
  USART_CR1_M | USART_CR1_RE | USART_CR1_TE, /* cr1 register values     */
  USART_CR2_LBDL, /* cr2 register values                               */
  0 /* cr3 register values                               */
};

static void umd_timeout_cb(GPTDriver *gptp);

GPTConfig umd_gpt_cfg = {
  TIMER_FREQ, /* Timer clock in Hz. */
  umd_timeout_cb, /* Timer callback     */
  0,
  0
};

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

UMD_Driver UMDD;


/*===========================================================================*/
/* Interrupt handlers.                                                       */
/*===========================================================================*/

static void umd_rxerr(UARTDriver *uartp, uartflags_t e) {
  (void) uartp;
  (void) e;
  UMDD.framing_error++;
}

static void umd_rxend(UARTDriver *uartp) {
  (void) uartp;
  chSysLockFromISR();
  gptStopTimerI(&UMD_TIMER);
  chThdResumeI(&umd_thread_ref, MSG_OK);
  chSysUnlockFromISR();
}

static void umd_txend(UARTDriver *uartp) {
  (void) uartp;
  /* retrigger only when tx finish later than rx */
  if(UMD_UART.rxstate != UART_RX_ACTIVE){
    chSysLockFromISR();
    chThdResumeI(&umd_thread_ref, MSG_OK);
    chSysUnlockFromISR();
  }
}

static void umd_timeout_cb(GPTDriver *gptp) {
  (void) gptp;
  chSysLockFromISR();
  uartStopReceiveI(&UMD_UART);
  chThdResumeI(&umd_thread_ref, MSG_TIMEOUT);
  chSysUnlockFromISR();
}

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

static THD_WORKING_AREA(waumd, 256);
static THD_FUNCTION(umd_process, arg) {
  (void)arg;
  thread_t* p;

  chRegSetThreadName("UART Multi-Drop Handler");

  while (!chThdShouldTerminateX()) {

    p = chMsgWait();

    UMD_Obj_t *active_object = (UMD_Obj_t*) chMsgGet(p);

    tx_buffer[0] = active_object->id | 0x100;

    /* wait for ongoing uart transmission */
    if(UMD_UART.txstate == UART_TX_ACTIVE){
      chSysLock();
      chThdSuspendTimeoutS(&umd_thread_ref, TIME_INFINITE);
      chSysUnlock();
    }

    /* prepare transmit */
    if(active_object->tx_len > 0){

      if (active_object->tx_callback != NULL)
        active_object->tx_callback(active_object->cb_arg);

      uint8_t tx_checksum = active_object->id ^ 0xAA;
      for (int i = 0; i < active_object->tx_len; i++) {
        tx_buffer[i + 1] = active_object->tx_data[i];
        tx_checksum ^= active_object->tx_data[i];
      }
      tx_buffer[active_object->tx_len + 1] = tx_checksum;

      uartStartSend(&UMD_UART, active_object->tx_len + 2, tx_buffer);
    }else
      uartStartSend(&UMD_UART, 1, tx_buffer);

    /* prepare receive */
    if(active_object->rx_len > 1){

      rx_frame.checksum = active_object->id;
      rx_frame.rx_len = active_object->rx_len + 1;
      rx_frame.out_data_ptr = active_object->rx_data;

      uartStartReceive(&UMD_UART, rx_frame.rx_len, rx_buffer);
      gptStartOneShot(&UMD_TIMER, BYTE_TIMEOUT(rx_frame.rx_len));

      chSysLock();
      msg_t msg = chThdSuspendTimeoutS(&umd_thread_ref, TIME_INFINITE);
      chSysUnlock();

      /* process receive */
      if(msg == MSG_TIMEOUT)
        chMsgRelease(p, UMD_TIMEOUT);
      else{
        /* calculate checksum */
        for(int i = 0; i <= rx_frame.rx_len; i++)
          rx_frame.checksum ^= rx_buffer[i] & 0xFF;
        if (rx_frame.checksum == 0xAA) {
          /* copy buffer to rx data variable */
          for(int i = 0; i < active_object->rx_len; i++)
            rx_frame.out_data_ptr[i] = rx_buffer[i];
          /* rx callback */
          if (active_object->rx_callback != NULL)
            active_object->rx_callback(active_object->cb_arg);
          chMsgRelease(p, UMD_OK);
        } else {
          UMDD.checksum_error++;
          chMsgRelease(p, UMD_CHECKSUM_ERROR);
        }
      }
    }else{
      chMsgRelease(p, UMD_OK);
    }
  }
}

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

void UMD_Master_Init(void){
  gptStart(&UMD_TIMER, &umd_gpt_cfg);
  osalMutexObjectInit(&umd_mutex);
  UMDD.state = UMD_STOP;
}

void UMD_Master_Start(void){
  uartStart(&UMD_UART, &umd_uart_cfg);
  umd_thread_ptr = chThdCreateStatic(waumd, sizeof(waumd),HIGHPRIO,
        umd_process, NULL);
  UMDD.state = UMD_READY;
}

void UMD_Master_Stop(void){
  uartStop(&UMD_UART);
  chThdTerminate(umd_thread_ptr);
  umd_thread_ptr = NULL;
  UMDD.state = UMD_STOP;
}

umd_return_e UMD_Poll_Single(UMD_Obj_t* umd_object){
  osalDbgAssert(UMDD.state == UMD_READY, "invalid state");
  osalMutexLock(&umd_mutex);
  umd_return_e state = chMsgSend(umd_thread_ptr, (msg_t)umd_object);
  osalMutexUnlock(&umd_mutex);
  return state;
}

void UMD_PollObjectList(UMD_Obj_t* object_list){
  UMD_Obj_t* umd_object = object_list;
  osalDbgAssert(UMDD.state == UMD_READY, "invalid state");
  osalMutexLock(&umd_mutex);
  if(umd_object == NULL) return;
  while(umd_object->id != ID_END){
    chMsgSend(umd_thread_ptr, (msg_t)umd_object);
    umd_object++;
  }
  osalMutexUnlock(&umd_mutex);
}


