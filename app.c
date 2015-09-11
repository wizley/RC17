#include "ch.h"
#include "hal.h"
#include "app.h"
#include "motor.h"

static virtual_timer_t CtrlLpVT;
//static Semaphore syncSem;
//static Semaphore CtrlLpSem;
//static WORKING_AREA(waThread1, 128);

//static msg_t Thread1(void *arg);
#define CONTROL_ID 0

void control_loop_timer(void *p) {
	/* Restarts the timer.*/
	chSysLockFromISR();
	chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, p);

	chSemSignalI(&comm.sync_start_sem);
	chSysUnlockFromISR();

	/* Periodic code here.*/

}

static THD_WORKING_AREA(waCtrlLp, 2048);
static THD_FUNCTION(RunManualControl, arg) {
	event_listener_t el;
	uint16_t cnt = 0;

	(void) arg;
	chRegSetThreadName("RunManualControl");
	chEvtRegister(&comm.sync_complete_event, &el, CONTROL_ID);

	while (!chThdShouldTerminateX()) {
		chEvtWaitAny(ALL_EVENTS); //EVENT_MASK(CONTROL_ID));
		//chEvtGetAndClearEvents(ALL_EVENTS);
		//chSemWait(&CtrlLpSem);
		//palTogglePad(GPIOC, GPIOC_LED_G);
		M[0].SetPoint = 50;
//		M[0].SetPoint += cnt;
//		if (M[0].SetPoint >= 100)
//			cnt = -1;
//		if (M[0].SetPoint <= 0)
//			cnt = 1;
		//chThdSleepMilliseconds(5);
		//palClearPad(GPIOC, GPIOC_LED_B);
		//chThdSleepMilliseconds(100);

		/*//if (RightStick>2048)
		 //	RightStick = RightStick*433/470;
		 ResyncMotorSetting(3);
		 int Speed = AddDeadZone(2048 - LeftStick, 20) * 2;
		 int Angle = AddDeadZone(2048 - RightStick, 20)* 4 /3;
		 //	if(ButtonPressed[1]) M[3].SetPoint = 5000;
		 //if(ButtonPressed[2]) M[3].SetPoint = 500;
		 //	if(ButtonPressed[3]) M[3].SetPoint = 0;
		 M[3].SetPoint = ADCValue[0];
		 //2458 3784 2200 3784	2614
		 int s;
		 s = (float)ADCValue[1];
		 Servo[1] = (int)s/4096.0f*784.0f+3000.0f;///4096*1000;
		 //Servo[1] = ADCValue[1]*5/2;
		 //if (ButtonPressed[1]) {Servo[1] = 750*5/2;}//Servo[1] = 1100*5/2;}
		 //if (ButtonPressed[2]) {Servo[1] = 900*5/2;}//Servo[1] = 640*5/2;}
		 Run(Speed, 999999L, Angle, 1000, 0);


		 //	Servo[0] = ADCValue[0]*5/2;
		 //	Servo[1] = ADCValue[0]*5/2;*/
	}
}

int app_init(void) {

	/* Frame Processing Thread */
	//InitUART();
	//chSemInit(&syncSem, 0);
	/* Periodic Frame Sync Thread */
	commStart(&comm);

	/* Control Loop Thread */
	//chSemInit(&CtrlLpSem, 0);
	chThdCreateStatic(waCtrlLp, sizeof(waCtrlLp), HIGHPRIO, RunManualControl, NULL);

	InitMotors();
	M[0].Setting.ScaleFactor = 2.0f;
	ResyncMotorSetting(0);
	M[0].Initializing = 0;

	chSysLock()
	;
	/* Starts the timer.*/
	chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, NULL);
	chSysUnlock();

	//for(;;) {
	//    chThdSleepMilliseconds(MS2ST(1000));
	//}
	return 0;
}

/*static msg_t Thread1(void *arg){
 while(TRUE){
 //chSemWait(&EneSem);
 //palSetPad(GPIOD, GPIOD_LED4);
 //chThdSleepMilliseconds(200);
 //palClearPad(GPIOD, GPIOD_LED4);
 chThdSleepMilliseconds(200);
 }
 }*/
