/*
n * boardio.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Wizley
 */

#ifndef ROBOT_BOARDIO_H_
#define ROBOT_BOARDIO_H_

#include "udc.h"

typedef struct tagAirBoard {
  int size;
  uint16_t states;
  int Command;
  int Alive;
  const uint8_t id;
} AIR_BOARD;

extern AIR_BOARD AirBoard;
void airSwitch(unsigned short which, bool state);
void airSwitchOff();

/*
#include "driving.h"
#include "udc.h"

#define ESTIM_BLACK     80
#define ESTIM_WHITE     81
#define GET_TURN_ON     82
#define GET_TURN_OFF    83
#define GET_RAW         84

#define CAL_ID_POS(n) (72+(n*6)+0)
#define CAL_ID_COMMAND(n) (72+(n*6)+1)
#define CAL_ID_DATA0_11(n) (72+(n*6)+2)
#define CAL_ID_DATA12_23(n) (72+(n*6)+3)
#define CAL_ID_DATA24_35(n) (72+(n*6)+4)
#define CAL_ID_DATA36_47(n) (72+(n*6)+5)

#define ID_L0_POS CAL_ID_POS(0)
#define ID_L1_POS CAL_ID_POS(1)
#define ID_L2_POS CAL_ID_POS(2)
#define ID_L3_POS CAL_ID_POS(3)

typedef struct tagLineSensor {
  int size;
  int short Position[4];
  unsigned char Data[48];
  int Command;
  int Alive;
  const uint8_t id;
} LINE_SENSOR;

extern LINE_SENSOR LineSensor[4];

void linesensor_decAlive(volatile void * arg);
void linesensor_setAlive(volatile void * arg);
udc_rx_state_e linesensor_send_command(LINE_SENSOR *line, int command);
void linesensor_get_data(LINE_SENSOR *line);
void linesensor_get_data0_11(LINE_SENSOR *line);
void linesensor_get_data12_23(LINE_SENSOR *line);
void linesensor_get_data24_35(LINE_SENSOR *line);
*/
#endif /* ROBOT_BOARDIO_H_ */
