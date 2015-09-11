#include "comm.h"
#include "comm_lld.h"

volatile LINE_SENSOR LineSensor[2] = { { { 0 } } };
volatile int16_t EncoderData[2] = { 0 };
volatile int16_t EncoderAlive = 0;

volatile int16_t Servo[8] = { 0, 0x5555, 1500, 1500, 1500, 1500, 1500, 1500 };
volatile int16_t ServoCurrent;

int Debug1[32];

void CalculateMotorSetPoint(volatile void *arg) {
	MotorObj *m = (MotorObj*) arg;
	m->NewSetPoint = m->Initializing ? m->Offset : m->SetPoint + m->Offset;
	palSetPad(GPIOC, GPIOC_LED_R);
}

void CalculateMotorFeedback(volatile void *arg) {
	MotorObj *m = (MotorObj*) arg;
	m->Feedback = m->NewFeedback - m->Offset;
	palClearPad(GPIOC, GPIOC_LED_R);
}

//#define SYNC_MOTOR(Index, ID) {																		\
//	if((M[(Index)].Board.State & 0x8000) == 0 || M[(Index)].Synced == 0 || M[(Index)].Alive == 0)	\
//	{																								\
//		InitMotor(Index);																			\
//		U1Enqueue((ID), 24, &M[(Index)].Setting, 0, 0, 0, 0, 0, NULL);								\
//		M[(Index)].Synced++;																		\
//	}																								\
//	M[(Index)].Alive = 3;																			\
//}

void SyncMotorSetting(volatile void *arg) {
	MotorObj *m = (MotorObj*) arg;
	//SYNC_MOTOR(0, 11)
	if ((m->Board.State & 0x8000) == 0 || m->Synced == 0 || m->Alive == 0) {
		InitMotor(m->id);
		U1Enqueue(11 + m->id * 4, 24, &m->Setting, 0, 0, 0, 0, 0, NULL);
		m->Synced++;
	}
	m->Alive = 3;
}
//void SyncM1Setting(void) { SYNC_MOTOR(1, 15) }
//void SyncM2Setting(void) { SYNC_MOTOR(2, 19) }
//void SyncM3Setting(void) { SYNC_MOTOR(3, 23) }
//void SyncM4Setting(void) { SYNC_MOTOR(4, 27) }
//void SyncM5Setting(void) { SYNC_MOTOR(5, 31) }
//void SyncM6Setting(void) { SYNC_MOTOR(6, 35) }
//void SyncM7Setting(void) { SYNC_MOTOR(7, 39) }

void DecMotorAlive(volatile void *arg) {
	MotorObj *m = (MotorObj*) arg;
	if (m->Alive > 0)
		m->Alive--;
}

//void SetLineSensor0Alive(void) { LineSensor[0].Alive = 3; }
//void SetLineSensor1Alive(void) { LineSensor[1].Alive = 3; }
//void DecLineSensor0Alive(void) { if(LineSensor[0].Alive > 0) LineSensor[0].Alive--; }
//void DecLineSensor1Alive(void) { if(LineSensor[1].Alive > 0) LineSensor[1].Alive--; }

void SetEncoderAlive(void) {
	EncoderAlive = 3;
}
void DecEncoderAlive(void) {
	if (EncoderAlive > 0)
		EncoderAlive--;
}

// Pre-set Communication ID Map, all boards should follow
//  Encoder Boards (ID 4-5)
//   4 : Board1 Encoders values
//   5 : Board2 Encoders values
//  Motor Boards (ID 8-71) max 16 boards
//   8+(n*4)+0 [8,12,16,...]  : Velocity SetPoint and Feedback
//   8+(n*4)+1 [9,13,17,...]  : Position SetPoint and Feedback
//   8+(n*4)+2 [10,14,18,...] : Voltage, Current, Temperature, ADC Feedback
//   8+(n*4)+3 [11,15,19,...] : Work mode, Prescaler, PID Parameters Setting
//  Line Sensor Terminals Boards  (72-95) max 4 Line Sensor
//   72+(n*6)+0 [72,78,84,90] : Sensor Position
//   72+(n*6)+1 [73,79,85,91] : Sensor Command
//   72+(n*6)+2 [74,80,86,92] : Sensor Individual Data for  0-11 LED/Photodiode pair
//   72+(n*6)+3 [75,81,87,93] : Sensor Individual Data for 12-23 LED/Photodiode pair
//   72+(n*6)+4 [76,82,88,94] : Sensfor Individual Data for 24-35 LED/Photodiode pair
//   72+(n*6)+5 [77,83,89,95] : Sensor Individual Data for 36-47 LED/Photodiode pair

int Data[4];
int Data2[8];
//static Semaphore *comm_start_sem_s;

//void DoCommunication(void (*SyncCallback)(void)) {
static THD_WORKING_AREA(waPFrame, 2048);
static THD_FUNCTION(SyncPeriodicFrame, arg) {

	COMMDriver *commp = arg;
	semaphore_t *comm_start_sem_s = &commp->sync_start_sem;

	static int MotorNumber = 0;
	static int SensorNumber = 0;

	chRegSetThreadName("SyncPeriodicFrame");
	(void) arg;
	while (!chThdShouldTerminateX()) {

		chSemWait(comm_start_sem_s);
		//palSetPad(GPIOD, GPIOD_LED3);

		// Setup Motors
		U1Enqueue(8, 2, &M[0].NewSetPoint, &CalculateMotorSetPoint, 2, &M[0].NewFeedback, &CalculateMotorFeedback,0, &M[0]);		// V motor
		//U1Enqueue(12, 2, &M[1].NewSetPoint, &CalculateMotorSetPoint, 2, &M[1].NewFeedback, 0, &CalculateMotorFeedback, &M[1]);		// V motor
		//U1Enqueue(17, 	2, &M[2].NewSetPoint, &CalculateM2SetPoint,		2, &M[2].NewFeedback, 0, &CalculateM2Feedback);		// P motor
		//U1Enqueue(21, 	2, &M[3].NewSetPoint, &CalculateM3SetPoint,		2, &M[3].NewFeedback, 0, &CalculateM3Feedback);		// P motor
		//U1Enqueue(25, 	2, &M[4].NewSetPoint, &CalculateM4SetPoint,		2, &M[4].NewFeedback, 0, &CalculateM4Feedback);		// P motor
		//U1Enqueue(28, 	2, &M[5].NewSetPoint, &CalculateM5SetPoint,		2, &M[5].NewFeedback, 0, &CalculateM5Feedback);		// P motor
		//U1Enqueue(33, 	2, &M[6].NewSetPoint, &CalculateM6SetPoint,		2, &M[6].NewFeedback, 0, &CalculateM6Feedback);		// P motor
		//U1Enqueue(37, 	2, &M[7].NewSetPoint, &CalculateM7SetPoint,		2, &M[7].NewFeedback, 0, &CalculateM7Feedback);		// P motor

		//U1Enqueue(100, 	16, Servo, 0,		0, 0, 0, 0);

		// These are group together to ensure the line sensor data and the encoder data are match
		//U1Enqueue(0,	0, 0, 0,						0, 0, 0,		0);

		// Miscellaneous Data
		//if (MotorNumber == 0 || M[0].Initializing)
		//	U1Enqueue(10, 0, 0, &DecMotorAlive, 10, &M[0].Board, &SyncMotorSetting, 0, &M[0]);
		/*if(MotorNumber == 1 || M[1].Initializing) U1Enqueue(14, 	0, 0, &DecM1Alive,	10, &M[1].Board, &SyncM1Setting,	0);
		 if(MotorNumber == 2 || M[2].Initializing) U1Enqueue(18, 	0, 0, &DecM2Alive,	10, &M[2].Board, &SyncM2Setting,	0);
		 if(MotorNumber == 3 || M[3].Initializing) U1Enqueue(22, 	0, 0, &DecM3Alive,	10, &M[3].Board, &SyncM3Setting,	0);
		 if(MotorNumber == 4 || M[4].Initializing) U1Enqueue(26, 	0, 0, &DecM4Alive,	10, &M[4].Board, &SyncM4Setting,	0);
		 if(MotorNumber == 5 || M[5].Initializing) U1Enqueue(30, 	0, 0, &DecM5Alive,	10, &M[5].Board, &SyncM5Setting,	0);
		 if(MotorNumber == 6 || M[6].Initializing) U1Enqueue(34, 	0, 0, &DecM6Alive,	10, &M[6].Board, &SyncM6Setting,	0);
		 if(MotorNumber == 7 || M[7].Initializing) U1Enqueue(38, 	0, 0, &DecM7Alive,	10, &M[7].Board, &SyncM7Setting,	0);
		 if(++MotorNumber >= 8) MotorNumber = 0;*/

		//if(SensorNumber == 0)		U1Enqueue(74, 0, 0, 0,	12, &LineSensor[0].Data[0], 0,		0);
		//else if(SensorNumber == 1) 	U1Enqueue(75, 0, 0, 0,	12, &LineSensor[0].Data[12], 0,		0);
		//else if(SensorNumber == 2) 	U1Enqueue(80, 0, 0, 0,	12, &LineSensor[1].Data[0], 0,		0);
		//else if(SensorNumber == 3) 	U1Enqueue(81, 0, 0, 0,	12, &LineSensor[1].Data[12], 0,		0);
		//if(++SensorNumber >= 4) SensorNumber = 0;
		//U1Enqueue(72, 	0, 0, &DecLineSensor0Alive,	8, LineSensor[0].Position, &SetLineSensor0Alive,	0);
		//U1Enqueue(78, 	0, 0, &DecLineSensor1Alive,	8, LineSensor[1].Position, &SetLineSensor1Alive,	0);
		//U1Enqueue(4,	0, 0, &DecEncoderAlive,		4, EncoderData, &SetEncoderAlive, 0);//SyncCallback);
		//U1Enqueue(150, 	16, &Data2[0], 0,		8, &Data[0], 0, 0);		// V motor
	}

	//return 0;
	chThdExit(1);

}

void ResyncMotorSetting(int index) {
	U1Enqueue(11 + index * 4, 24, &M[index].Setting, 0, 0, 0, 0, 0, NULL);
	M[index].Synced++;
}

void SendLineSensorCommand(int index, int command) {
	LineSensor[index].Command = command;
	U1Enqueue(73 + index * 6, 2, &LineSensor[index].Command, 0, 0, 0, 0, 0, NULL);
}

void GetDebug1Value(void) {
	U1Enqueue(128, 0, 0, 0, 16, &Debug1[0], 0, 0, NULL);
	U1Enqueue(129, 0, 0, 0, 16, &Debug1[8], 0, 0, NULL);
	U1Enqueue(130, 0, 0, 0, 16, &Debug1[16], 0, 0, NULL);
	U1Enqueue(131, 0, 0, 0, 16, &Debug1[24], 0, 0, NULL);
}

void commStart(COMMDriver *commp) {
	//InitUart1();
	//comm_start_sem_s = sync_start_sem;
	comm_lld_init();
	chSemObjectInit(&commp->sync_start_sem, 0);
	chEvtObjectInit(&commp->sync_complete_event);
	//chEvtGetAndClearEvents(ALL_EVENTS);



	//chSemInit(&EneSem, 0);
	chThdCreateStatic(waPFrame, sizeof(waPFrame), HIGHPRIO, SyncPeriodicFrame, (void *) commp);
	//Start uart1

}
