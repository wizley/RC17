
#include "ch.h"
#include "hal.h"
#include "SEGGER_RTT.h"
#include "RTTstream.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

RTTStream RTT_S0;

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

  return SEGGER_RTT_Read(0, bp, n);
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

static const struct RTTStreamVMT vmt = {writes, reads, put, get};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   RTT stream object initialization.
 *
 * @param[out] nsp      pointer to the @p RTTStream object to be initialized
 */
void RTTstreamObjectInit(RTTStream *rsp) {

  SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

  rsp->vmt = &vmt;
}
