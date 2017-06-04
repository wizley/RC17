/*
 * common.h
 *
 *  Created on: 2015¦~4¤ë5¤é
 *      Author: Hung
 */

#ifndef COMMON_H_
#define COMMON_H_
#include "motor.h"
#include "driving.h"
#include "airboard.h"
#include "ps4_usbhost.h"

#ifndef PI
#define PI  3.1415926535897932384626433832795028841971693993751
#endif

#define ENCODER_RESOLUTION 4096
#define WHEEL_DIAMETER 40
#define EN_TO_DIS 1.14961122
#define PID_DEADZONE 1

#define CLOSE 60000
#define OPEN 1000

//for the shooter
enum shooter_states {
	PLATFORM_NO_MIDDLE_NO = 0,
	PLATFORM_YES_MIDDLE_YES = 1,
	PLATFORM_NO_MIDDLE_YES = 2,
	RAISE_HOIST = 3,
	RAM_AND_SHOOT = 4,
	LOWER_HOIST = 5,
	LOADING_ERROR = 6
};

typedef struct{
  int id,  x, y, pitch, roll, shootspd;
}PositionStates;



extern PositionStates stateSet[9];
/*

*/
extern int debug_display[10];
extern int targetPosition;

int getPitch(void);

int setPitch(int value);

int getRoll(void);

int setRoll(int value);

bool setPitchRoll(int pitch, int roll);

void runManual(void);
void runAuto(PositionStates *set, int pos);
void castLimit(void);

#define PITCH_MIN	395
#define PITCH_MAX	PITCH_MIN + 45
#define SERVO_STEP_ROLL (float)(500.0-425.0)/(428.0-2.0)
//0.2deg = 423 42.88deg=488
#define SERVO_STEP_PITCH (float)(488.0-425.0)/(428.0-2.0)
#define ROLL_DEFAULT 424
#define ROLL_MIN	ROLL_DEFAULT - 65 //more positive = roll to right
#define	ROLL_MAX	ROLL_DEFAULT + 65
#define RAMMER_MIN	290
#define RAMMER_MAX	RAMMER_MIN + 200

#define ADC_PITCH_MIN	33309
#define ADC_PITCH_MAX	39791
#define ADC_ROLL_MIN	25730

extern int leftDisc;
extern int rightDisc;
extern int shooterNextState;
extern enum shooter_states;

extern int leftMiddle_f;
extern int rightMiddle_f;
extern int lowerHoist_f;

extern const int platformNoMiddleYesAlive;

extern int shooterAlive;
extern int platformHaveDisc_f;


// Encoder Position
extern long encoder_1, encoder_2;
extern int32_t distance_1, distance_2;
extern int distanceSum;
extern float yDistance;
extern int carDirection;
void UpdatePosition(void);
extern DS4_status_t old_data2;
uint8_t PS4_ButtonPress(ButtonEnum b);
void savePS4Data(void);
void reload_and_shoot(void);
//for the shooter
void pusher(bool start);
extern int upperValveAlive;
extern int polezone;
extern int LSState;

extern const int reloadPos;


extern const int numberOfStage;

#if IS_MOTOR_0_2016 && IS_MOTOR_1_2016
	extern const float fastHatMultiplier_krpm;
	extern const float slowHatMultiplier_krpm;
	extern float hatMultiplier_krpm;
#else
	extern const int fastHatMultiplier;
	extern const int slowHatMultiplier;
	extern int hatMultiplier;
#endif
extern const int upLimit;// in terms of SetPoint
extern const int lowLimit;
extern const int acceleration_limit;
extern const int HatDeadzone;

//for ps4 button debounce
extern int old_r1_state,old_l1_state,old_dpad_state;
extern int old_circle_state, old_square_state,old_cross_state,old_triangle_state;
//for ps4 dpad
extern int circleAlive;
extern int dpadUPAlive;
extern int dpadDOWNAlive;

#define LSwitch (M[3].Board.ADCValue > CLOSE)
#define RSwitch (M[6].Board.ADCValue > CLOSE)
#define FSwitch (M[0].Board.ADCValue > CLOSE)
#define BSwitch (M[1].Board.ADCValue > CLOSE)
#define CSwitch (M[2].Board.ADCValue > CLOSE)


void update_shooter_flags(void);
int NormalizeAngle(int t);
float fNormalizeAngle(float t);
int AddDeadZone(int value, int tolerance);
int Euclidean(int x1, int y1, int x2, int y2);
float constrain(float value, float positiveLimit, float negativeLimit);
float accelerationLimit_krpm(float speed, float oldSpeed,float upperLimit, float lowerLimit);
int accelerationLimit(int speed, int oldSpeed,int upperLimit, int lowerLimit);

extern int asdasd;
#endif /* COMMON_H_ */
//rip
