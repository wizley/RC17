/*
 * red.h
 *
 *  Created on: 2017-03-22
 *      Author: Lau
 */

#ifndef ROBOT_RED_H_
#define ROBOT_RED_H_
#include "driving.h"
#include "pid.h"
#include "stdint.h"

//auto or manual state for car
#define START_STATE 0
#define MANUAL_STATE 1
#define AUTO_STATE 2

#define PITCH_ZERO_DEGREE	0	//to be found
#define ROLL_ZERO_DEGREE	0	//to be found
#define ADC_TO_DEGREE 0		//to be found


extern int shootSpeed_r[8];

extern int p_error, i_error;
extern const float K_P, K_I;

extern int carState_r;
extern int currentPos_r;
extern long encoder_1, encoder_2;
extern int circleAlive;
extern int distanceSum_r;

extern int xCarSetPoint_r;
extern int yCarSetPoint_r;

#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
	extern float xMotorSpeed_krpm_r;
	extern float xMotorSpeed_rpm_r;
	extern float PID_krpm_r;
#elif !IS_MOTOR_0_2016 && !IS_MOTOR_1_2016
	extern int xMotorSpeed;
	extern int PID_setpoint;
#endif

extern float yMotorSpeed_krpm;
extern float yMotorSpeed_rpm;
extern float reloadMotorSpeed_krpm;

extern int shootSpeed;
extern int leftStickSpeed;
extern int rightStickSpeed;

extern int pushBarAlive;


void RunPath_r(void);

#endif /* ROBOT_RED_H_ */
