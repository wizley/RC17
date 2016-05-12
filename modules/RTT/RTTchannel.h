
#ifndef _RTTCHANNEL_H_
#define _RTTCHANNEL_H_

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
 * @brief   @p RTTChannel specific data.
 */
#define _rtt_channel_data                                                   \
  _base_channel_data

/**
 * @brief   @p RTTChannel virtual methods table.
 */
struct RTTChannelVMT {
  _base_channel_methods
};

/**
 * @extends BaseSequentialStream
 *
 * @brief   RTT channel object.
 */
typedef struct {
  /** @brief Virtual Methods Table.*/
  const struct RTTChannelVMT *vmt;
  _rtt_channel_data
} RTTChannel;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern RTTChannel RTT_S0;

#ifdef __cplusplus
extern "C" {
#endif
  void RTTchannelObjectInit(RTTChannel *rcp);
#ifdef __cplusplus
}
#endif

#endif /* _RTTCHANNEL_H_ */

/** @} */
