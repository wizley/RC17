/*
n * boardio.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Wizley
 */

#ifndef ROBOT_AIRBOARD_H_
#define ROBOT_AIRBOARD_H_

#include <stdint.h>

// Change here for different air boards
#define ID_AIRBOARD_0 110

typedef struct {
  int size;
  uint16_t state;
  int Command;
  int Alive;
  uint8_t id;
} AirBoardObj;

extern AirBoardObj airBoard;

void airSetState(AirBoardObj* ab, uint8_t channel, uint8_t state);

void airToggleState(AirBoardObj* ab, uint8_t channel);
#endif /* ROBOT_BOARDIO_H_ */
