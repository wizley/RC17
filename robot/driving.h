#ifndef _DRIVING_H_
#define _DRIVING_H_

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_0                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_1                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_2                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_3                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_4                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_5                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_6                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_7                 TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_ENCODER                 TRUE
#define ENCODER_NUMBER              3
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_SERVO                   TRUE
#define SERVO_NUMBER                8
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_0            TRUE
#define LINESENSOR_0_SIZE             12
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_1            TRUE
#define LINESENSOR_1_SIZE             12
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_2            FALSE
#define LINESENSOR_2_SIZE             12
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_3            FALSE
#define LINESENSOR_3_SIZE             12
#endif

typedef enum tagDrivingState {
	ACTIVATED = 0,
	DEACTIVATED
} DRIVING_STATE;



typedef struct _tagWheelPosition {
	float x;
	float y;
	int IsSteeringWheel;
	int IsDrivingWheel;
} WHEEL_POSITION;

typedef struct _tagWheelOutput {
	int Speed;
	int Angle;
} WHEEL_OUTPUT;

typedef struct
{
	float x;
	float y;
	float t;
}fPOSITION;

typedef struct
{
	int x;
	int y;
	int t;
}iPOSITION;

extern DRIVING_STATE DrivingState;

void decAllAlive(void);

void ActivateDriving(void);
void DeactivateDriving(void);
void InitDriving(void);

#endif
