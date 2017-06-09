/*
 * red.c
 *
 *  Created on: 2017-01-02
 *      Author: Lau
 */

#include "tgmath.h"
#include "app.h"
#include "driving.h"
#include "pid.h"
#include "common.h"
#include "encoder.h"
#include "linesensor.h"
#include "motor.h"
#include "servo.h"
#include "ps4_usbhost.h"
#include "analog.h"
#include "airboard.h"
#include "distancesensor.h"
#include "red.h"
/*
 * for searching purpose
 * START_STATE_r
 * AUTO_STATE_r
 * MANUAL_STATE_r
 */
int xTrack_r[8] =
{//position for pillar and reload
	0,
	1500,
	3000,
	4500,
	6000,
	7500,
	9000,
	10000
};
int yTrack_r[8] =
{//position for pillar and reload
	0,
	10,
	20,
	30,
	40,
	50,
	60,
	70
};

const int numberOfWhiteline = 5;
const int linePos_r[5] =
{
		2000,
		4000,
		6000,
		8000,
		10000
};

//const int linePos_r[5] =
//{
//		75000,
//		75000 * 2,
//		75000 * 3,
//		75000 * 4,
//		75000 * 5
//};

int shootSpeed_r[8] =
{//to be written after having good shooter
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

//for hat control

//for car state
int carState_r = START_STATE;
int nextCarState_r = START_STATE;
const int numberOfCarState_r = 2;
int currentPos_r = 0;//for displaying current position of the car in auto state
int xCarSetPoint_r = 0;//unit is mm
int yCarSetPoint_r = 0;

//flags
//int left_platform_r = FALSE;
//int left_buffer_r = FALSE;
//int right_platform_r = FALSE;
//int right_buffer_r = FALSE;
//int hoist_r = FALSE;
//int barrel_r = FALSE;

//to be written
int shootAngle_r[8] = {0};

//PID for track


//#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
//	float K_P = 0.006, K_I = 0.01;
	float p_error_krpm = 0.0000;
	float i_error_krpm = 0.0000;
	float i_error_limit_krpm = 0.004;
	float PID_krpm_r = 0.0000;
	float oldPID_krpm = 0.0000;

	const float upLimit_2016 = 13.0000;//in terms of krpm
	const float lowLimit_2016 = -13.0000;
	float acceleration_limit_krpm = 0.06;
	float xOldMotorSpeed_krpm = 0;
	float xMotorSpeed_krpm_r = 0.000000;
	float xMotorSpeed_rpm = 0.000000;

//#elif !IS_MOTOR_0_2016 && !IS_MOTOR_1_2016
	const float K_P = 1.0, K_I = 0.2;//0.2
	int i_error_limit = 400;
	int p_error = 0;
	int i_error = 0;
	int PIDSetPoint_r = 0;
	int oldPIDSetpoint = 0;

	int xOldMotorSpeed_r = 0;
	int xMotorSpeed_r = 0;
//#endif

//y axis movement
//float yMotorSpeed_krpm_r = 0.000000;
//float yOldMotorSpeed_krpm = 0.000000;
//const float yMotorSpeedLimit_krpm = 3.0000;
//float yMotorSpeed_rpm_r = 0.000000;
//int yDistance_r = 0;
//float y_i_error = 0;
//float y_PID_krpm = 0;

int yMotorSpeed_r = 0;

float reloadMotorSpeed_krpm = 0.000000;
int oneAxisMovement = FALSE;

const int STICK_K_P = 0.1;
int pitchAngle = 0;
int rollAngle = 0;




//debug display, easy to show needed data
;
//for start state
int pushBarAlive = 55;

#if IS_MOTOR_0_2016
//PID for 2016 board
float PID_for_path_krpm_r( int currentPosition, int targetPosition, int PID_deadzone) {
	p_error_krpm = K_P * (currentPosition - targetPosition);
	i_error_krpm += K_I * p_error;
	i_error_krpm = constrain(i_error_krpm, i_error_limit, -i_error_limit);
	PID_krpm_r = p_error_krpm + i_error_krpm;
	PID_krpm_r = accelerationLimit_krpm(PID_krpm_r, xOldMotorSpeed_krpm, acceleration_limit_krpm, -acceleration_limit_krpm);
	PID_krpm_r = constrain(PID_krpm_r, upLimit_2016, lowLimit_2016);
	xOldMotorSpeed_krpm = PID_krpm_r;
	if(abs(targetPosition - currentPosition) < PID_deadzone) {
		PID_krpm_r = 0;
		i_error_krpm = 0;
	}
	return -PID_krpm_r;
}
#elif !IS_MOTOR_0_2016
//PID for 2012 board
int PID_for_path_r(int currentPosition, int targetPosition, int PID_deadzone) {
	p_error = K_P * (currentPosition - targetPosition);
	i_error += K_I * p_error;
	i_error = constrain(i_error, i_error_limit, -i_error_limit);
	PIDSetPoint_r = p_error + i_error;
	PIDSetPoint_r = accelerationLimit(PIDSetPoint_r, xOldMotorSpeed_r, acceleration_limit, -acceleration_limit);
	xOldMotorSpeed_r = PIDSetPoint_r;
	if(abs(targetPosition - currentPosition) < PID_deadzone){
		PIDSetPoint_r = 0;
		i_error = 0;
	}
	return -PIDSetPoint_r;
}
#endif

//void clearPID(void) {
//	p_error = 0;
//	i_error = 0;
//}
//Map ADC value to actual degree
void ADC_TO_MOTOR(int PAngle, int RAngle) {
	int pitch = PAngle - M[2].Board.ADCValue;
	int roll = RAngle - M[3].Board.ADCValue;
	M[2].SetPoint = STICK_K_P * (pitch + roll);
	M[3].SetPoint = STICK_K_P * (pitch - roll);
}
//clear PID variable
void clearPID(void) {
	p_error = 0;
	i_error = 0;
}
//function which will load the cannon and shoot it, need to add weight and correction later
//void reloadAndShoot(void) {
	/*
	 * 2 : upper valve L
	 * 3 : lower valve L
	 * 4 : upper valve R
	 * 5 : lower valve R
	 * 6 : from left to middle platform
	 * 7 : form right to middle platform
	 * 8 : hoist
	 *
	 * Servo1.command[0] : roll
	 * Servo1.command[1] : pitch
	 * Servo1.command[2] : rammer
	 *
	 * start cases
	 * case 1: no disk on left, right, hoist and barrel
	 * case 2: disk in barrel
	 *
	 * end cases
	 * case 1: disk at left platform,
	 * case 2: disk at right platform
	 * case 3: no disk
	 */
//void pushBar_r(void) {
//	if(pushBarAlive > 0) {
//		if(pushBarAlive == 50) {
//			airSetState(&airBoard, 2,1);
//			airSetState(&airBoard, 3,0);
//			airSetState(&airBoard, 4,1);
//			airSetState(&airBoard, 5,0);
//			airSetState(&airBoard, 6,0);
//			airSetState(&airBoard, 7,0);
//			airSetState(&airBoard, 8,0);
//			airSetState(&airBoard, 0,1);//base
//			airSetState(&airBoard, 1,1);//base
//			Servo1.command[0] = ROLL_MIN;
//			Servo1.command[1] = PITCH_MIN;
//			Servo1.command[2] = RAMMER_MIN;
//		}
//		else if(pushBarAlive == 1) {
//			xCarSetPoint_r = xTrack_r[0];
//			carState_r = AUTO_STATE;
//		}
//	}
//	else {
////		airSetState(&airBoard, 0,1);
////		airSetState(&airBoard, 1,1);
//		pushBarAlive = 0;
//	}
//}

int totalDistance = 0;

void clearEncoder(void) {
	encoder_1 = 0;
	encoder_2 = 0;
	distance_1 = 0;
	distance_2 = 0;
	distanceSum_r = 0;
}

void ClearPosition_r(void){
	xCarSetPoint_r = 0;
	yCarSetPoint_r = 0;
	encoder_1 = 0;
	encoder_2 = 0;
	distanceSum_r = 0;
	distance_1 = 0;
	distance_2 = 0;
}

void UnlockBase_r(void){
	motor_setIdle(&M[0]);
	motor_setIdle(&M[1]);
//  motor_setIdle(&M[0]);
//  motor_setIdle(&M[1]);
//  motor_setIdle(&M[2]);
//  motor_setIdle(&M[3]);
}

void LockBase_r(void){
	motor_send_setting(&M[0]);
	motor_send_setting(&M[1]);
//  motor_send_setting(&M[0]);
//  motor_send_setting(&M[1]);
//  motor_send_setting(&M[2]);
//  motor_send_setting(&M[3]);
}

/*
 * common for both manual and auto
 */
void updateOldPS4Data_r(void) {
    savePS4Data();
	old_cross_state = ps4_data.cross;
	old_circle_state = ps4_data.circle;
	old_square_state = ps4_data.square;
	old_triangle_state = ps4_data.triangle;

	old_l1_state = ps4_data.l1;
	old_r1_state = ps4_data.r1;
	old_dpad_state = ps4_data.dpad_code;
}

void updateData_r(void) {


//	if(ps4_data.dpad_code == DPAD_UP) {	//pressing UP
//	  //Increase Shooting Speed
//		if(dpadUPAlive == 0) {
//			shootSpeed_r[currentPos_r] += 5;
//		}
//		if(dpadUPAlive > 20 && dpadUPAlive % 8 == 0 && ps4_data.r1) {
//			shootSpeed_r[currentPos_r] += 20;
//		}
//		dpadUPAlive++;
//		nextCarState_r = MANUAL_STATE;
//		shootSpeed_r[currentPos_r] = constrain(shootSpeed_r[currentPos_r], 3000, 0);
//	}
//	else {
//		dpadUPAlive = 0;
//	}
//
//	if(ps4_data.dpad_code == DPAD_DOWN) {	//pressing down
//	  //Decrease Shooting Speed
//		if(dpadDOWNAlive == 0) {
//			shootSpeed_r[currentPos_r] -= 5;
//		}
//		if(dpadDOWNAlive > 20 && dpadDOWNAlive % 8 == 0 && ps4_data.r1) {
//			shootSpeed_r[currentPos_r] -= 20;
//		}
//		shootSpeed_r[currentPos_r] = constrain(shootSpeed_r[currentPos_r], 3000, 0);
//		dpadDOWNAlive++;
//		nextCarState_r = MANUAL_STATE;
//	}
//	else {
//		dpadDOWNAlive = 0;
//	}

//	if(ps4_data.l1) {
//          #if IS_MOTOR_0_2016
//                  hatMultiplier_krpm = slowHatMultiplier_krpm;
//          #elif !IS_MOTOR_0_2016
//                  hatMultiplier = slowHatMultiplier;
//          #endif
//	}
//	else {
//          #if IS_MOTOR_0_2016
//                  hatMultiplier_krpm = fastHatMultiplier_krpm;
//          #elif !IS_MOTOR_0_2016
//                  hatMultiplier = fastHatMultiplier;
//          #endif
//	}

//	if(ps4_data.r1) {
//		oneAxisMovement = TRUE;
//	}
//	else {
//		oneAxisMovement = FALSE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_right_y) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
}
//MANUAL_STATE_r


void checkForAuto_r(void) {
	if(nextCarState_r == AUTO_STATE) {
		carState_r = AUTO_STATE;
	}
}

//void updateAutoData_r(void) {
//	if(ps4_data.dpad_code == 0) {	//pressing UP
//		if(dpadUPAlive == 0) {
//			shootSpeed_r[currentPos_r] += 5;
//			shootSpeed_r[currentPos_r] = constrain(shootSpeed_r[currentPos_r], 2000, 0);
//		}
//		if(dpadUPAlive > 20 && dpadUPAlive % 6 == 0) {
//			shootSpeed_r[currentPos_r] += 20;
//			shootSpeed_r[currentPos_r] = constrain(shootSpeed_r[currentPos_r], 2000, 0);
//		}
//		dpadUPAlive++;
//		nextCarState_r = MANUAL_STATE;
//	}
//	else {
//		dpadUPAlive = 0;
//	}
//	if(ps4_data.dpad_code == 4) {	//pressing down
//		if(dpadDOWNAlive == 0) {
//			shootSpeed_r[currentPos_r] -= 5;
//		}
//		if(dpadDOWNAlive > 20 && dpadDOWNAlive % 6 == 0) {
//			shootSpeed_r[currentPos_r] -= 20;
//		}
//		dpadDOWNAlive++;
//		nextCarState_r = MANUAL_STATE;
//		shootSpeed_r[currentPos_r] = constrain(shootSpeed_r[currentPos_r], 2000, 0);
//	}
//	else {
//		dpadDOWNAlive = 0;
//	}
//	if(ps4_data.l1) {
//#if IS_MOTOR_0_2016
//		hatMultiplier_krpm = slowHatMultiplier_krpm;
//#elif !IS_MOTOR_0_2016
//		hatMultiplier = slowHatMultiplier;
//#endif
//		nextCarState_r = MANUAL_STATE;
//	}
//	else {
//#if IS_MOTOR_0_2016
//		hatMultiplier_krpm = fastHatMultiplier_krpm;
//#elif !IS_MOTOR_0_2016
//		hatMultiplier = fastHatMultiplier;
//#endif
//	}
//	if(ps4_data.r1) {
//		oneAxisMovement = TRUE;
//	}
//	else {
//		oneAxisMovement = FALSE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(AddDeadZone((int)((uint16_t)(ps4_data.hat_right_y) - 128), HatDeadzone) != 0) {
//		nextCarState_r = MANUAL_STATE;
//	}
//	if(ps4_data.dpad_code == 2 && old_dpad_state != 2) {
//		nextCarState_r = AUTO_STATE;
//		currentPos_r--;
//		currentPos_r = constrain(currentPos_r, 7, 0);
//		xCarSetPoint_r = xTrack_r[currentPos_r];
//		yCarSetPoint_r = yTrack_r[currentPos_r];
//	}
//	if(ps4_data.dpad_code == 6 && old_dpad_state != 6) {
//		nextCarState_r = AUTO_STATE;
//		currentPos_r++;
//		currentPos_r = constrain(currentPos_r, 7, 0);
//		xCarSetPoint_r = xTrack_r[currentPos_r];
//		yCarSetPoint_r = yTrack_r[currentPos_r];
//	}
//	if(ps4_data.cross) {
//		nextCarState_r = AUTO_STATE;
//		xCarSetPoint_r = xTrack_r[reloadPos];
//		yCarSetPoint_r = yTrack_r[reloadPos];
//	}
//}


void runAuto_r(void) {
//#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
//	xMotorSpeed_krpm_r = PID_for_path_krpm_r(distanceSum_r,xCarSetPoint_r,PID_DEADZONE);
//	m[0].speed_ref_krpm = xMotorSpeed_krpm_r;
//	m[1].speed_ref_krpm = xMotorSpeed_krpm_r;
//#elif !IS_MOTOR_0_2016 && !IS_MOTOR_1_2016
	xMotorSpeed_r = PID_for_path_r(distanceSum,xCarSetPoint_r,PID_DEADZONE);
//	xMotorSpeed_r = constrain(xMotorSpeed_r, upLimit, lowLimit);
	M[0].SetPoint = xMotorSpeed_r;
	M[1].SetPoint = xMotorSpeed_r;
//#endif
	//		at reload position
	if(distanceSum >= xTrack_r[reloadPos]) {
		airSetState(&airBoard, 2, 0);
	}
	if(distanceSum == xCarSetPoint_r) {
		nextCarState_r = MANUAL_STATE;
	}
}

void checkForManual_r(void) {
	if(nextCarState_r == MANUAL_STATE) {
		carState_r = MANUAL_STATE;
	}
}

void displayDebug_r(void) {
	debug_display[0] = LineSensor2016[0].status;//M[0].Board.ADCValue;
	debug_display[1] = LineSensor2016[0].position;//M[1].Board.ADCValue;
	debug_display[2] = LineSensor2016[0].position - 1911;
	debug_display[3] = M[3].Board.ADCValue;
	debug_display[4] = M[6].Board.ADCValue;//M[4].Feedback;	//left to mid
	debug_display[5] = ps4_data.tpad_click;//M[5].Feedback;	//right to mid
    debug_display[6] = ps4_data.tpad_info[0].finger[0].x;
	debug_display[7] = ps4_data.tpad_info[0].finger[0].y;
    debug_display[8] = ps4_data.tpad_info[0].finger[0].is_touching;
    debug_display[9] = targetPosition;
}

PositionStates redStateSet[9] =
{
// {id      ,x      ,y      ,pitch  ,roll   ,shootspd   },
//   {        ,       ,       ,       ,       ,           },

   {0		, -500  ,0		,0		,0		,0          }, //Start Zone
   {1		, 4621	,250	,190	,140	,1010       },
   {2       , 6246	,250	,210	,50 	,1045       },
   {3       , 7400	,250	,240	,0	    ,710        }, //Middle Near
   {4       , 7236	,250	,235	,60 	,1070       }, //Middle Middle
   {5       , 7435	,250	,130	,120    ,1345       }, //Middle Far
   {6       , 9709	,250	,210    ,50     ,1045       },
   {7       , 10767	,250	,74	    ,-20	,930        },
   {8       , 12500	,0		,108	,5		,0          }  //Loading Zone
};
bool init_r = false;
void RunPath_r(void) {
	UpdatePosition();

	if (!init_r){
      airSetState(&airBoard, 2, 1);
      airSetState(&airBoard, 4, 1);
      airSetState(&airBoard, 0, 1);
      airSetState(&airBoard, 1, 1);
      xDistanceOffset = redStateSet[0].x;
      if (!BSwitch && !PS4_ButtonPress(TRIANGLE)){
        M[6].SetPoint = -100;
      }
      else{
        M[6].SetPoint = 0;
        if (!ps4_data.circle){
          init_r = true;
        }
      }
	}
	else{
        if(ps4_data.l2_trigger>200) {
          targetPosition = 8; //reload position
          firstPush=false;
          leftDisc=false;
          rightDisc=false;
          runAuto(redStateSet, targetPosition);

        }
        else if(ps4_data.r2_trigger>200) {
          targetPosition = 0;
          runAuto(redStateSet, targetPosition);
        }
        else if(ps4_data.l1) {
	      runAuto(redStateSet, targetPosition);
	    }
	    else{
	         //Manual Mode
	        //updateData_r();
	        runManual();
	        //checkForAuto_r();
	    }

	    if(PS4_ButtonPress(SQUARE)) {
	      redStateSet[targetPosition].pitch = getPitch();
	      redStateSet[targetPosition].roll = getRoll();
	      redStateSet[targetPosition].x = distanceSum;
	      redStateSet[targetPosition].y = yDistance;
	      redStateSet[targetPosition].shootspd = (M[4].SetPoint+M[5].SetPoint)/2;
	    }
	//Update position according to pole aiming
	    if(PS4_ButtonPress(RIGHT) && !ps4_data.r1) {
	      //Shift the pole aiming at
	        //For Wizley
	        targetPosition = constrain(--targetPosition, 8, 0);
	    }

	    if(PS4_ButtonPress(LEFT) && !ps4_data.r1) {
	        //Shift the pole aiming at
	        //For Wizley
	        targetPosition = constrain(++targetPosition, 8, 0);
	    }

	    if(ps4_data.tpad_click){
	      switch(ps4_data.tpad_info[0].finger[0].x / 400){
	      case 0:
	        targetPosition=7;
	        break;
	      case 1:
	        targetPosition=6;
	        break;
	      case 2:
	        switch(ps4_data.tpad_info[0].finger[0].y / 300){
	        case 0:
	          targetPosition=5;
	          break;
	        case 1:
	          targetPosition=4;
	          break;
	        case 2:
	          targetPosition=3;
	          break;
	        }
	        break;
	      case 3:
	        targetPosition=2;
	        break;
	      case 4:
	        targetPosition=1;
	        break;
	      }
	    }

        if(PS4_ButtonPress(PS)&& ps4_data.cross) {
          pusher(true);
        }

	    if(ps4_data.cross) {
	      //Reset all pneumatic to initial mode
	       // airSetState(&airBoard, 0, 0);
	       // airSetState(&airBoard, 1, 0);
	        airSetState(&airBoard, 2, 0);
	        airSetState(&airBoard, 3, 0);
	        airSetState(&airBoard, 4, 0);
	        airSetState(&airBoard, 5, 0);
	        airSetState(&airBoard, 6, 0);
	        airSetState(&airBoard, 7, 0);
	        airSetState(&airBoard, 8, 0);
	        Servo1.command[0] = (ROLL_MIN+ROLL_MAX)/2;
	        Servo1.command[1] = PITCH_MIN;
	        Servo1.command[2] = RAMMER_MIN;
	        shooterAlive=0;
	    }


	    if(ps4_data.circle) {
	        airSetState(&airBoard, 0,1);//base
	        airSetState(&airBoard, 1,1);//base
	        if (targetPosition != 8 && targetPosition != 0){
	           reload_and_shoot();
	        }
	    }
	    else if ((airBoard.state)&(1<<8)){
	      int servoRoll = constrain(ROLL_DEFAULT + getRoll()*SERVO_STEP_ROLL, ROLL_MAX, ROLL_MIN);
	      if (servoRoll > Servo1.command[0]) Servo1.command[0]+= (servoRoll > Servo1.command[0] + 20)?3:1;
	      else if (servoRoll < Servo1.command[0]) Servo1.command[0]-= (servoRoll < Servo1.command[0] - 20)?2:1;

	      int servoPitch = constrain(PITCH_MIN + getPitch()*SERVO_STEP_PITCH, PITCH_MAX, PITCH_MIN);
	      if (servoPitch > Servo1.command[1] )Servo1.command[1]+=(servoPitch > Servo1.command[1] + 20)?2:1;
	      else if (servoPitch < Servo1.command[1] )Servo1.command[1]-=(servoPitch < Servo1.command[1] - 20)?2:1;

	    }
	}
    castLimit();
    displayDebug_r();
	updateOldPS4Data_r();


}
