//#include "Communication.h"
#include "motor.h"
//#include "Driving.h"
//#include "__ADC.h"
#define MOTORDECL(var, id) struct MotorObj var = {.id = id};


MotorObj M[NUMBER_OF_MOTOR] = {{.id=0},{.id=1},{.id=2},{.id=3},{.id=4},{.id=5},{.id=6},{.id=7}};


void InitMotors(void) {
    MOTOR_SETTING DefaultVMode = { IDLE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	MOTOR_SETTING DefaultPMode = { IDLE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	DefaultVMode.Mode = VMODE;
	DefaultVMode.ScaleFactor = 1;
	DefaultVMode.AccelerationLimit = 3;
	DefaultVMode.SpeedLimit = 600;
	DefaultVMode.CommandCycle = 4000;
	DefaultVMode.MotorVoltage = 12000;
	DefaultVMode.CurrentLimit = 10000;
	DefaultVMode.kP = 100;
	DefaultVMode.kI = 100;
	DefaultVMode.kD = 200;
	DefaultVMode.kFF = 1350;
	
	M[0].Offset = 0;
	M[0].Initializing = 1;

	M[0].Setting = DefaultVMode;
	M[1].Setting = DefaultVMode;

	DefaultPMode.Mode = PMODE;
	DefaultPMode.ScaleFactor = 10;
	DefaultPMode.AccelerationLimit = 200;
	DefaultPMode.SpeedLimit = 4000;
	DefaultPMode.CommandCycle = 4000;
	DefaultPMode.MotorVoltage = 24000;
	DefaultPMode.CurrentLimit = 1000;
	DefaultPMode.kP = 200;
	DefaultPMode.kI = 1;
	DefaultPMode.kD = 40;
	DefaultPMode.kFF = 0;

	M[2].Setting = DefaultPMode;
	M[3].Setting = DefaultPMode;
	M[4].Setting = DefaultPMode;
	M[5].Setting = DefaultPMode;
	M[6].Setting = DefaultPMode;
	M[7].Setting = DefaultPMode;
	
//	InitMotor(2);
//	InitMotor(3);
}

void InitMotor(int index) {
	switch(index)
	{
		case 2:
			M[2].Setting.Mode = BRAKE;
			M[2].Offset = 0;
			M[2].AbsolutePosition.SteadyCount = 0;
			M[2].AbsolutePosition.ADCValue =   0 ;
			M[2].AbsolutePosition.ADCToEncoderScale = 3600.0 / 65535.0;
			M[2].Initializing = 1;
			break;
		case 3:
			M[3].Setting.Mode = PMODE;
			M[3].Setting.AccelerationLimit = 10;
			M[3].Setting.CurrentLimit = 8000;
			M[3].Setting.ScaleFactor = 100;
		//	M[3].Initializing = 1;
			break;
	}
}

//#include "App.h"
//#include "__ADC.h"
//#include "Serial.h"
/*
void CheckMotorStatus(void) {
    
	if(M[2].Initializing) {
        M[2].Initializing++;
        
		if(M[2].Initializing == 10) {
			M[2].Offset = M[2].Feedback;
			M[2].Setting.Mode = PMODE;
			ResyncMotorSetting(2);
		}
        
		if(M[2].Initializing >= 10) {
			uint64_t ADCOffset = (uint64_t)M[2].Board.ADCValue - (uint64_t)M[2].AbsolutePosition.ADCValue;
			int32_t MotorOffset = (int32_t)(M[2].AbsolutePosition.ADCToEncoderScale * ADCOffset);
			int32_t OffsetIncrement = MotorOffset / 10;
            
			if(OffsetIncrement > 20) {
                OffsetIncrement = 20;
            } else if(OffsetIncrement < -20) {
                OffsetIncrement = -20;
			}
            
			if(MotorOffset > -10 && MotorOffset < 10) {
				if(++M[2].AbsolutePosition.SteadyCount >= 50){
					M[2].Initializing = 0;
                }
			} else {
				M[2].AbsolutePosition.SteadyCount = 0;
            }
			
			M[2].Offset += OffsetIncrement;
		}
        
		if(M[2].Initializing > 500) {		// Force to Stop Initialization
			M[2].Initializing = 0;
        }
	}
	if(M[3].Ilitialixile)
	{
		MY3].Initializine+);
		if(M[1].Initializing == 10)
		{
			M[3].Offset = M[3].Feedback;
			M[3].Setting.Mode = PMODE;
			ResyncMotorSetting(3);
		}
		if(M[3].Initializing >= 10)
		{
			longdADCOffset = (long)M[3].Board"ADCValue - (long)M[3].AbsolutePosition.ADCValue;
			int MotorOffset = (int)(M[3].AbsolutePosition.ADCToEncoderScale * ADCOffset);
			int OffsetIncrement = MotorOffset / 10;
			if(OffsetIncrement > 20)		OffsetIncrement = 20;
			else if(OffsetIncrement < -20)	OffsetIncrement = -20;
			
			if(MotorOffset > -10 && MotorOffset < 10)
			{
				if(++M[3].AbsolutePosition.SteadyCount >= 50)
					M[3].Initializing = 0;
			}
			else
				M[3].AbsolutePosition.SteadyCount = 0;
			
			M[3].Offset += OffsetIncrement;
		}
		if(M[3].Initializing > 500)		// Force to Stop Initialization
			M[3].Initializing = 0;
	}
}*/
