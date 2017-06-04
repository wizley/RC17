
#include "ch.h"
#include "hal.h"
#include "SEGGER_RTT.h"
#include "RTTchannel.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

RTTChannel RTT_S0;

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static size_t writes(void *ip, const uint8_t *bp, size_t n) {

  (void)ip;

  return SEGGER_RTT_Write(0, bp, n);
}

static size_t reads(void *ip, uint8_t *bp, size_t n) {

  (void)ip;

  uint16_t r = 0;
  while(true){
    r += SEGGER_RTT_Read(0, bp + r, n - r);
    if(r == n)
      return n;
    else
      chThdSleepMilliseconds(50);
  }

  //return SEGGER_RTT_Read(0, bp, n);
}

static msg_t put(void *ip, uint8_t b) {

  (void)ip;

  if(SEGGER_RTT_Write(0, &b, 1))
    return STM_OK;
  else
    return STM_RESET;
}

static msg_t get(void *ip) {

  (void)ip;

  msg_t b;

  while(true){
    b = SEGGER_RTT_GetKey();
    if(b < 0)
      chThdSleepMilliseconds(50);
    else
      return b;
  }
}

static msg_t putt(void *ip, uint8_t b, systime_t timeout) {

  (void)timeout;

  return put(ip, b);
}

static msg_t gett(void *ip, systime_t timeout) {

  (void)ip;
  msg_t b;

  b = SEGGER_RTT_GetKey();
  if (b >= 0)
    return b;
  if (timeout == TIME_IMMEDIATE)
    return MSG_TIMEOUT;
  else if (timeout == TIME_INFINITE) {
    while ((b = SEGGER_RTT_GetKey()) < 0)
      chThdSleepMilliseconds(50);
    return b;
  } else {
    chThdSleep(timeout);
    b = SEGGER_RTT_GetKey();
    if (b >= 0)
      return b;
    return MSG_TIMEOUT;
  }
}

static size_t writet(void *ip, const uint8_t *bp, size_t n, systime_t timeout) {

  (void)timeout;

  return writes(ip, bp, n);
}

static size_t readt(void *ip, uint8_t *bp, size_t n, systime_t timeout) {

  (void)ip;

  uint16_t r = 0;

  if(timeout == TIME_INFINITE){
    while(true){
      r += SEGGER_RTT_Read(0, bp + r, n - r);
      if(r == n)
        return n;
      else
        chThdSleepMilliseconds(50);
    }
  } else {
    r = SEGGER_RTT_Read(0, bp, n);
    if (timeout == TIME_IMMEDIATE)
        return r;
    chThdSleep(timeout);
    r += SEGGER_RTT_Read(0, bp + r, n - r);
    return r;
  }
}

static const struct RTTChannelVMT vmt = {
    writes, reads, put, get,
    putt, gett, writet, readt
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   RTT stream object initialization.
 *
 * @param[out] nsp      pointer to the @p RTTStream object to be initialized
 */
void RTTchannelObjectInit(RTTChannel *rcp) {

  SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

  rcp->vmt = &vmt;
}
