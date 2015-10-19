#include "ch.h"
#include "hal.h"
#include "drivers.h"
#include "app.h"
#include "motor.h"
#include "servo.h"
#include "encoder.h"
#include "udc_objectlist.h"
#include "udc.h"

#define CONTROL_EVENT 0

static event_source_t CtrlLp_evt;
static virtual_timer_t CtrlLpVT;
static UDC_config_t udc_config;

void control_loop_timer(void *p) {
	/* Restarts the timer.*/
	chSysLockFromISR();
	chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, p);
	osalEventBroadcastFlagsI(&CtrlLp_evt, 0);
	chSysUnlockFromISR();
}

static THD_WORKING_AREA(waCtrlLp, 2048);
static THD_FUNCTION(RunManualControl, arg) {
	(void) arg;
	chRegSetThreadName("RunManualControl");

	event_listener_t el;

	chEvtRegister(&CtrlLp_evt, &el, CONTROL_EVENT);

	while (!chThdShouldTerminateX()) {
		chEvtWaitAny(EVENT_MASK(CONTROL_EVENT));
		chEvtGetAndClearEvents(EVENT_MASK(CONTROL_EVENT));

		UDC_PollObjectList(udc_objectlist);
		//motor_send_setpoint(&M[0]);


		M[0].SetPoint = qeiGetCount(&QEID4) * 10;

	}
	chEvtUnregister(&CtrlLp_evt, &el);
}

int app_init(void) {
  osalEventObjectInit(&CtrlLp_evt);

  UDC_Init(&udc_config);

  UDC_Start();


	motor_init(&M[0], &DefaultVMode);
	motor_send_setting(&M[0]);


	/* Control Loop Thread */
  chThdCreateStatic(waCtrlLp, sizeof(waCtrlLp), HIGHPRIO, RunManualControl, NULL);


	chSysLock();
	/* Starts the timer.*/
	chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, NULL);
	chSysUnlock();

	return 0;
}

