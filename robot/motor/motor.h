#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "ch.h"

#define NUMBER_OF_MOTOR 8

#define IDLE 0x0
#define BRAKE 0x1
#define VMODE 0x2
#define PMODE 0x3

typedef struct tagBoardFeedback {
    int16_t Voltage;		// in mV
    int16_t Current;		// in mA
    int16_t Temperature;	// in Degree Celsius
    uint16_t ADCValue;
    uint16_t State;
} __attribute__((packed)) BOARD_FEEDBACK;


//enum { IDLE = 0, BRAKE = 1, VMODE = 2, PMODE = 3 } Mode ;

typedef struct tagMotorSetting {
    /** 
     *  IDLE  : Motor terminals is left open (not shorted or driven)
     *  BRAKE : Motor terminals are short
	 *  VMODE : Motor is running in V Mode
	 *  PMODE : Motor is running in P Mode
	 *  For VMODE and PMODE, if there is no correct set point command received,
     *  motor will be in brake state
     */
    //enum { IDLE = 0, BRAKE = 1, VMODE = 2, PMODE = 3 } Mode ;
    uint16_t Mode;
    float ScaleFactor;				// PID Controller SetPoint = Input SetPoint * ScaleFactor
    uint16_t AccelerationLimit;	// in Encoder count / CommandCycle
    uint16_t SpeedLimit;		// in Encoder count / CommandCycle
	uint16_t CommandCycle;		// in us
	uint16_t MotorVoltage;		// in mV
	uint16_t CurrentLimit;		// in mA
	int16_t kP;
	int16_t kI;
	int16_t kD;
	int16_t kFF;
} __attribute__((packed)) MOTOR_SETTING;

typedef struct tagAbsolutePosition {
	uint16_t ADCValue;
	float ADCToEncoderScale;
	int16_t SteadyCount;
} __attribute__((packed)) ABSOLUTE_POSITION;

typedef volatile struct tagMotor {
	int16_t SetPoint;
	int16_t Feedback;
	
	int16_t Offset;

	volatile int16_t NewSetPoint;	// For Communication
	volatile int16_t NewFeedback;	// For Communication

	uint16_t Synced;
	uint16_t Alive;

	int16_t Initializing;
	ABSOLUTE_POSITION AbsolutePosition;

	BOARD_FEEDBACK Board;
	MOTOR_SETTING Setting;
	const uint8_t id;
} MotorObj;// __attribute__((packed)) MotorObj;

extern MotorObj M[NUMBER_OF_MOTOR];

void InitMotors(void);
void InitMotor(int index);
void CheckMotorStatus(void);

#endif  /* _MOTOR_H_ */
