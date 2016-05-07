/*
 * servo.h
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#ifndef ROBOT_SERVO_SERVO_H_
#define ROBOT_SERVO_SERVO_H_

#define ID_SERVO1 100
#define ID_SERVO2 101

typedef struct{
  int16_t command[8];
  int16_t current;
  uint8_t Alive;
}servo_t;

extern servo_t Servo1;
extern servo_t Servo2;

void servo_init(servo_t *servo);
void servo_set_offset(servo_t *servo);
void servo_set_angle(servo_t *servo, float angle, uint8_t channel);
void servo_setAlive(volatile void * arg);
void servo_decAlive(volatile void * arg);

#endif /* ROBOT_SERVO_SERVO_H_ */
