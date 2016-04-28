/*
 * encoder.h
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#ifndef ROBOT_ENCODER_ENCODER_H_
#define ROBOT_ENCODER_ENCODER_H_

#define ID_ENCODER1_2 4
#define ID_ENCODER3_4 5

typedef struct{
  uint16_t count_per_revolution[2];
  uint16_t count[2];
  uint16_t delta_count[2];
  uint8_t Alive;
}ENCObj_t;

extern ENCObj_t encoder1_2;
extern ENCObj_t encoder3_4;
void encoder_checkAlive(volatile void * arg);

#endif /* ROBOT_ENCODER_ENCODER_H_ */
