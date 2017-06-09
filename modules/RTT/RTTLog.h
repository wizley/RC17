#ifndef _RTTLOG_H_
#define _RTTLOG_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   @p RTTLog specific data.
 */
#define _rtt_log_data                                                   \
  _base_sequential_stream_data

/**
 * @brief   @p RTTLog virtual methods table.
 */
struct RTTLogVMT {
  _base_sequential_stream_methods
};

/**
 * @extends BaseSequentialStream
 *
 * @brief   RTT Log object.
 */
typedef struct {
  /** @brief Virtual Methods Table.*/
  const struct RTTLogVMT *vmt;
  _rtt_log_data
} RTTLog;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern RTTLog RTT_Log;

#ifdef __cplusplus
extern "C" {
#endif
  void RTTLogObjectInit(RTTLog *rlp);
#ifdef __cplusplus
}
#endif

#endif /* _RTTLOG_H_ */

/** @} */
