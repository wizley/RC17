#include "ch.h"
#include "motor.h"
#include "drivers.h"

#include "driving.h"

#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
    #include "motor.h"
#endif
#if USE_ENCODER
#include "encoder.h"
#endif
#if USE_SERVO
#include "servo.h"
#endif
#include "udc_objectlist.h"
#include "udc.h"

#define LOOP_TIME 10   /* Control Loop time in ms */
#define CONTROL_EVENT 0


DRIVING_STATE DrivingState = DEACTIVATED;

static thread_t *ctrllp = NULL;
static event_source_t CtrlLp_evt;
static virtual_timer_t CtrlLpVT;
static UDC_config_t udc_config = {0};

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

  uint16_t oldcount = qeiGetCount(&QEID4);

  while (!chThdShouldTerminateX()) {
    chEvtWaitAny(EVENT_MASK(CONTROL_EVENT));
    //chEvtGetAndClearEvents(EVENT_MASK(CONTROL_EVENT));
    UDC_PollObjectList(udc_objectlist);

    motor_get_status(&M[0]);
    //motor_send_setting(&M[0]);
    //motor_send_setpoint(&M[0]);
    //Servo1.command[0] = (qeiGetCount(&QEID4) - oldcount) * 10;

    M[0].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;

      }
      chEvtUnregister(&CtrlLp_evt, &el);
}

void ActivateDriving(void){
  if (DrivingState == DEACTIVATED){
     if(ctrllp == NULL){//should not call it repeatedly
        /* Control Loop Thread */
        ctrllp = chThdCreateStatic(waCtrlLp, sizeof(waCtrlLp), HIGHPRIO, RunManualControl, NULL);
        DrivingState = ACTIVATED;
        chSysLock();
        /* Starts the timer.*/
        chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, NULL);
        chSysUnlock();
     }else{
         DrivingState = ACTIVATED;
         //TODO:change the object list content
     }
  }
}

void DeactivateDriving(void){
//  if(ctrllp != NULL){
//      chThdTerminate(ctrllp);
//    }
//    chSysLock();
//    /* Stops the timer.*/
//    chVTDoResetI(&CtrlLpVT);
//    chSysUnlock();
  if(DrivingState == ACTIVATED){//avoid doing them repeatedly
#if USE_MOTOR_0
    motor_setIdle(&M[0]);
#endif
#if USE_MOTOR_1
    motor_setIdle(&M[1]);
#endif
#if USE_MOTOR_2
    motor_setIdle(&M[2]);
#endif
#if USE_MOTOR_3
    motor_setIdle(&M[3]);
#endif
#if USE_MOTOR_4
    motor_setIdle(&M[4]);
#endif
#if USE_MOTOR_5
    motor_setIdle(&M[5]);
#endif
#if USE_MOTOR_6
    motor_setIdle(&M[6]);
#endif
#if USE_MOTOR_7
    motor_setIdle(&Mx[7]);
#endif

    //TODO: add changing the objectlist
//    UDC_Obj_t udc_object;
//    udc_object.id = CAL_ID_M_SETTING(motor->id);
//    udc_object.tx_data = (udc_tx_data_t)&DefaultIdle;
//    udc_object.tx_len = 24;
//    udc_object.rx_len = 0;
//    udc_object.rx_callback = NULL;
  }
}

extern volatile int DebugRun[4];

void InitDriving(void) {
  osalEventObjectInit(&CtrlLp_evt);

  UDC_Init(&udc_config);
  UDC_Start();
}


