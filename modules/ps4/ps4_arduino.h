/*
 * ps4.h
 *
 *  Created on: Jun 21, 2015
 *      Author: u564
 */

#ifndef MODULES_PS4_PS4_ARDUINO_H_
#define MODULES_PS4_PS4_ARDUINO_H_


typedef struct __attribute__((packed)){
  uint8_t left_hat_x;

  uint8_t left_hat_y;

  uint8_t right_hat_x;

  uint8_t right_hat_y;

  uint8_t l2;

  uint8_t r2;

  uint8_t ps:1;
  uint8_t share:1;
  uint8_t options:1;
  uint8_t touchpad:1;
  uint8_t triangle:1;
  uint8_t circle:1;
  uint8_t cross:1;
  uint8_t square:1;

  uint8_t left:1;
  uint8_t right:1;
  uint8_t up:1;
  uint8_t down:1;
  uint8_t l3:1;
  uint8_t r3:1;
  uint8_t l1:1;
  uint8_t r1:1;

  uint8_t finger0:1;
  uint8_t finger1:1;
  uint8_t reserved1:6;

  float pitch;
  float roll;

  uint8_t battery;

  uint16_t finger0_x;
  uint16_t finger0_y;
  uint16_t finger1_x;
  uint16_t finger1_y;
}PS4_status_t;

void cmd_ps4(BaseSequentialStream *chp, int argc, char *argv[]);

#endif /* MODULES_PS4_PS4_ARDUINO_H_ */
