#ifndef _DRIVING_H_
#define _DRIVING_H_


//base x-axis movement
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_0                 TRUE
#define IS_MOTOR_0_DC               FALSE
#define IS_MOTOR_0_2016				0
#endif
//base x-axis movement gear ratio 15:1
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_1                 TRUE
#define IS_MOTOR_1_DC               FALSE
#define IS_MOTOR_1_2016				0
#endif
//left stick
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_2                 TRUE
#define IS_MOTOR_2_DC               TRUE
#define IS_MOTOR_2_2016				FALSE
#endif
//right stick
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_3                 TRUE
#define IS_MOTOR_3_DC               TRUE
#define IS_MOTOR_3_2016				FALSE
#endif
//shooter
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_4                 TRUE
#define IS_MOTOR_4_DC               FALSE
#define IS_MOTOR_4_2016				FALSE
#endif
//shooter
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_5                 TRUE
#define IS_MOTOR_5_DC               FALSE
#define IS_MOTOR_5_2016				FALSE
#endif
//base y-axis movement, gear ratio 28:1
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_6                 TRUE
#define IS_MOTOR_6_DC               FALSE
#define IS_MOTOR_6_2016				FALSE
#endif
//reload action
#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_MOTOR_7                 FALSE
#define IS_MOTOR_7_DC               FALSE
#define IS_MOTOR_7_2016				TRUE
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_ENCODER                 TRUE
#define ENCODER_NUMBER              2
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_SERVO                   TRUE
#define SERVO_NUMBER                8
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_0            TRUE
#define IS_LINESENSOR_0_2016 		TRUE
#define LINESENSOR_0_SIZE             24//how many line sensor module i use per line, only need to define if using old line sensor
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_1            FALSE
#define IS_LINESENSOR_1_2016 		FALSE
#define LINESENSOR_1_SIZE             24
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_2            FALSE
#define IS_LINESENSOR_2_2016		FALSE
#define LINESENSOR_2_SIZE             24
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_LINESENSOR_3            FALSE
#define IS_LINESENSOR_3_2016		FALSE
#define LINESENSOR_3_SIZE             24
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_AIRBOARD_0            TRUE
#define AIRBOARD_0_SIZE             16
#endif

#if !defined(CH_TIME_QUANTUM) || defined(__DOXYGEN__)
#define USE_DISTANCESENSOR			TRUE
#endif

#ifndef NUMBER_OF_WHEEL
#define NUMBER_OF_WHEEL             (4)
#endif

#define EncoderDistance  (505.0f)
#define EncoderDiameter (68.24f)
#define EncoderResolution (4096.0f)

#define RearWheelDiameter (101.6f) //Omniwheel diamter
#define RearWheelGear (14.0f)
#define RearWheelEncoderResolution (2048.0f)
#define RearWheelSamplingTime (4.0f)

#define FrontWheelDistance (300.0f)
#define RearWheelDistance (610.0f)
#define FrontToRearDistance (350.0f)

#define ChassisScaleFactor (1.0f)/(RearWheelDiameter * (PI) / RearWheelEncoderResolution / RearWheelGear / RearWheelSamplingTime * (1000.0f))

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
