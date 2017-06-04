/*
 * distancesensor.h
 *
 *  Created on: 3 Mar, 2017
 *      Author: Lau
 */

#ifndef MODULES_DISTANCE_DISTANCE_H_
#define MODULES_DISTANCE_DISTANCE_H_

typedef enum {
  distance_rx_init = 0,
  distance_rx_active = 1,
  distance_rx_error = 4
}distance_rx_state_e;

typedef struct __attribute__((packed)){
    uint16_t distance_mm_pre;
    uint16_t distance_mm;
    distance_rx_state_e rx_state;
    uint16_t rate_constraint; //prevent from rapid change
    uint8_t error_rapid;
    uint8_t data_count;
    uint8_t distance[10];
    uint32_t distance_smoothened;
} DistanceSensor;

extern DistanceSensor dSensor;
void distance_init(void);

#endif
