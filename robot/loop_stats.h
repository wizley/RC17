/*
 * loop_stats.h
 *
 *  Created on: 7 May 2016
 *      Author: u564
 */

#ifndef ROBOT_LOOP_STATS_H_
#define ROBOT_LOOP_STATS_H_

#define LOOP_STAT_HISTORY_DEPTH 8
#define LOOP_STAT_MONITOR_PERIOD_MS 400

typedef struct{
  uint32_t overruns;       // control loop overrun counter
  float    loop_frequency; // control loop frequency (Hz)
  uint32_t avg_loop_us;    // average total loop roundtrip (us)
  uint32_t max_loop_us;    // maximum total loop roundtrip (us)
  uint32_t avg_comm_us;    // average communication roundtrip (us)
  uint32_t max_comm_us;    // maximum communication roundtrip (us)

  uint32_t loop_history[LOOP_STAT_HISTORY_DEPTH];
  uint32_t comm_history[LOOP_STAT_HISTORY_DEPTH];

  uint8_t  loop_hist_cnt;
  uint8_t  comm_hist_cnt;

}loop_stats_t;

extern loop_stats_t loop_stats;

void loop_stat_sample(systime_t val);
void loop_stat_mean_update(void);
void comm_stat_sample(systime_t val);
void comm_stat_mean_update(void);

#endif /* ROBOT_LOOP_STATS_H_ */
