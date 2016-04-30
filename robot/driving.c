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
#include "ps4_usbhost.h"
#include "menu_struct.h"
#include "app_list.h"

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
    chEvtGetAndClearEvents(EVENT_MASK(CONTROL_EVENT));
    UDC_PollObjectList(udc_objectlist);
    if (current_running_menu->data.app == &start_robot){
             motor_get_status(&M[0]);// Miscellaneous Data
             if (ps4_data.btns.triangle)//brake
                 motor_setBrake(&M[0]);
             else if (DS4_ButtonPress(SQUARE))//reactivate after brake
                 motor_send_setting(&M[0]);//should have set the motor global setting before calling this
             //motor_send_setpoint(&M[0]);
             //Servo1.command[0] = (qeiGetCount(&QEID4) - oldcount) * 10;
             else if (DS4_ButtonPress(CROSS))
                 DeactivateDriving();
             M[0].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
             palSetPad(GPIOC, GPIOC_LED_G);
    }else if (current_running_menu->data.app == &ps4_test_app){
             //should not do anything
           palClearPad(GPIOC, GPIOC_LED_G);
      }
    }
    chEvtUnregister(&CtrlLp_evt, &el);
}

void ActivateDriving(void){
  if (DrivingState == DEACTIVATED){
    M[0].Setting = DefaultVMode;//please initialize the motor with something else, this pid sucks
#if USE_MOTOR_0
    motor_send_setting(&M[0]);
#endif
#if USE_MOTOR_1
    motor_send_setting(&M[1]);
#endif
#if USE_MOTOR_2
    motor_send_setting(&M[2]);
#endif
#if USE_MOTOR_3
    motor_send_setting(&M[3]);
#endif
#if USE_MOTOR_4
    motor_send_setting(&M[4]);
#endif
#if USE_MOTOR_5
    motor_send_setting(&M[5]);
#endif
#if USE_MOTOR_6
    motor_send_setting(&M[6]);
#endif
#if USE_MOTOR_7
    motor_send_setting(&M[7]);
#endif

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
     }
  }
}

void DeactivateDriving(void){
  if(DrivingState == ACTIVATED){//avoid doing them repeatedly
    DrivingState = DEACTIVATED;
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
  }
}

extern volatile int DebugRun[4];

void InitDriving(void) {
  osalEventObjectInit(&CtrlLp_evt);
  UDC_Init(&udc_config);
  UDC_Start();
}


