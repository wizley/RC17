
#ifndef _RTTSTREAMS_H_
#define _RTTSTREAMS_H_

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
 * @brief   @p RTTStream specific data.
 */
#define _rtt_stream_data                                                   \
  _base_sequential_stream_data

/**
 * @brief   @p RTTStream virtual methods table.
 */
struct RTTStreamVMT {
  _base_sequential_stream_methods
};

/**
 * @extends BaseSequentialStream
 *
 * @brief   RTT stream object.
 */
typedef struct {
  /** @brief Virtual Methods Table.*/
  const struct RTTStreamVMT *vmt;
  _rtt_stream_data
} RTTStream;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern RTTStream RTT_S0;

#ifdef __cplusplus
extern "C" {
#endif
  void RTTstreamObjectInit(RTTStream *rsp);
#ifdef __cplusplus
}
#endif

#endif /* _RTTSTREAMS_H_ */

/** @} */
