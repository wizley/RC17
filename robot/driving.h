#ifndef _DRIVING_H_
#define _DRIVING_H_

#define MOTOR_NUM 8

typedef enum tagDrivingState {
	ACTIVATED,
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

void ActivateDriving(void);
void DeactivateDriving(void);

void InitDriving(void);

#endif
