/*
 * loop_stats.c
 *
 *  Created on: 23 May 2016
 *      Author: u564
 */

#include "ch.h"
#include "loop_stats.h"

loop_stats_t loop_stats;

void loop_stat_sample(systime_t val){
  loop_stats.loop_history[loop_stats.loop_hist_cnt] = val;
  loop_stats.loop_hist_cnt = (loop_stats.loop_hist_cnt + 1) % LOOP_STAT_HISTORY_DEPTH;
  loop_stats.max_loop_us = loop_stats.max_loop_us > val ? loop_stats.max_loop_us : val;
}

void loop_stat_mean_update(void){
  int i;
  uint32_t sum = 0;
  for(i = 0; i < LOOP_STAT_HISTORY_DEPTH; i++)
    sum += loop_stats.loop_history[i];
  loop_stats.avg_loop_us = sum / LOOP_STAT_HISTORY_DEPTH;
}

void comm_stat_sample(systime_t val){
  loop_stats.comm_history[loop_stats.comm_hist_cnt] = val;
  loop_stats.comm_hist_cnt = (loop_stats.comm_hist_cnt + 1) % LOOP_STAT_HISTORY_DEPTH;
  loop_stats.max_comm_us = loop_stats.max_comm_us > val ? loop_stats.max_comm_us : val;
}

void comm_stat_mean_update(void){
  int i;
  uint32_t sum = 0;
  for(i = 0; i < LOOP_STAT_HISTORY_DEPTH; i++)
    sum += loop_stats.comm_history[i];
  loop_stats.avg_comm_us = sum / LOOP_STAT_HISTORY_DEPTH;
}
