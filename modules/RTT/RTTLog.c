#include "ch.h"
#include "hal.h"
#include "SEGGER_RTT.h"
#include "RTTLog.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

RTTLog RTT_Log;

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

static char upBuffer[BUFFER_SIZE_UP];
//static char downBuffer[BUFFER_SIZE_DOWN];

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static size_t writes(void *ip, const uint8_t *bp, size_t n) {

  (void)ip;

  return SEGGER_RTT_Write(1, bp, n);
}

static size_t reads(void *ip, uint8_t *bp, size_t n) {

  (void)ip;
  (void)bp;
  (void)n;

  return 0;
}

static msg_t put(void *ip, uint8_t b) {

  (void)ip;

  if(SEGGER_RTT_Write(1, &b, 1))
    return STM_OK;
  else
    return STM_RESET;
}

static msg_t get(void *ip) {

  (void)ip;

  return STM_RESET;
}

static const struct RTTLogVMT vmt = {writes, reads, put, get};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   RTT stream object initialization.
 *
 * @param[out] nsp      pointer to the @p RTTStream object to be initialized
 */
void RTTLogObjectInit(RTTLog *rlp) {

  SEGGER_RTT_ConfigUpBuffer(1, "Logger", upBuffer, BUFFER_SIZE_UP, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
//  SEGGER_RTT_ConfigDownBuffer(1, "Logger", downBuffer, BUFFER_SIZE_UP, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  rlp->vmt = &vmt;
}
