#include "motor.h"
#include "comm.h"

//#include "Position.h"
#include "driving.h"

#define NUMBER_OF_WHEEL				(4)

float EncoderDistance				= 487.0;
float EncoderDiameter				= 81.8;
float EncoderResolution				= 4096.0;

float RearWheelDiameter				= 120.0;
float RearWheelGear					= 14.0;
float RearWheelEncoderResolution	= 2048.0;
float RearWheelSamplingTime			= 4.0;

float FrontWheelDistance			= 300.0;
float RearWheelDistance				= 610.0;
float FrontToRearDistance			= 350.0;


WHEEL_POSITION WheelPosition[NUMBER_OF_WHEEL] = {{0}};
WHEEL_OUTPUT WheelOutput[NUMBER_OF_WHEEL] = {{0}};

DRIVING_STATE DrivingState = ACTIVATED;

void ActivateDriving(void)
{
	M[0].Setting.Mode = VMODE;
	M[1].Setting.Mode = VMODE;
	ResyncMotorSetting(0);
	ResyncMotorSetting(1);
	DrivingState = ACTIVATED;
}

void DeactivateDriving(void)
{
	M[0].Setting.Mode = IDLE;
	M[1].Setting.Mode = IDLE;
	ResyncMotorSetting(0);
	ResyncMotorSetting(1);
	DrivingState = DEACTIVATED;
}

extern volatile int DebugRun[4];

void Run(int TargetSpeed, long lRadius, int AngleOffset, int AngleOffsetAtX, int AngleOffsetAtY)
{

	
	M[0].SetPoint = -WheelOutput[0].Speed;
	M[1].SetPoint = WheelOutput[1].Speed;
	M[2].SetPoint = WheelOutput[2].Angle;
//	M[3].SetPoint = ADCValue[1];

}

void InitDriving(void) {
    //float SacleFactor =	1.0 / (RearWheelDiameter * PI / RearWheelEncoderResolution / RearWheelGear / RearWheelSamplingTime * 1000.0);
    float SacleFactor =	1.0 / (RearWheelDiameter * 3.14 / RearWheelEncoderResolution / RearWheelGear / RearWheelSamplingTime * 1000.0);
	M[0].Setting.Mode = VMODE;
	M[0].Setting.ScaleFactor = SacleFactor;
	M[0].Setting.CommandCycle = (int)(RearWheelSamplingTime * 1000);
    M[1].Setting = M[0].Setting;
	M[2].Setting.ScaleFactor = 4096.0 * 15.0 * 3.71 / 3600.0;
	
	WheelPosition[0].x = FrontToRearDistance;
	WheelPosition[0].y = RearWheelDistance / 2;
	WheelPosition[0].IsDrivingWheel = 1;
	
	WheelPosition[1].x = FrontToRearDistance;
	WheelPosition[1].y = -RearWheelDistance / 2;
	WheelPosition[1].IsDrivingWheel = 1;

	WheelPosition[2].x = FrontToRearDistance;
	WheelPosition[2].y = FrontWheelDistance / 2;
	WheelPosition[2].IsSteeringWheel = 1;

	WheelPosition[3].x = FrontToRearDistance;
	WheelPosition[3].y = -FrontWheelDistance / 2;
	WheelPosition[3].IsSteeringWheel = 1;
}
