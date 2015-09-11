#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "ch.h"
#include "hal.h"
#include "comm_lld.h"
#include "motor.h"

#define ESTIM_BLACK		80
#define ESTIM_WHITE		81
#define GET_TURN_ON		82
#define GET_TURN_OFF	83
#define GET_RAW			84

typedef struct tagLineSensor {
    int Position[4];
	unsigned char Data[48];
	int Command;
	int Alive;
} LINE_SENSOR;

extern volatile LINE_SENSOR LineSensor[2];
extern volatile int16_t EncoderData[2];
extern volatile int16_t EncoderAlive;

void commStart(COMMDriver *commp);

extern volatile int16_t Servo[8];
extern volatile int16_t ServoCurrent;

void ResyncMotorSetting(int index);
void SendLineSensorCommand(int index, int command);
void GetDebug1Value(void);

#endif
