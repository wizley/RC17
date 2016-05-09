#include "ch.h"
#include "motor.h"
#include "drivers.h"
#include "driving.h"
#include "string.h"
#include "loop_stats.h"
#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
    #include "motor.h"
#endif
#if USE_ENCODER
#include "encoder.h"
#endif
#if USE_SERVO
#include "servo.h"
#endif
#if USE_LINESENSOR_0 || USE_LINESENSOR_1 || USE_LINESENSOR_2 || USE_LINESENSOR_3
#include "linesensor.h"
#endif
#include "udc_objectlist.h"
#include "udc.h"
#include "ps4_usbhost.h"
#include "menu_struct.h"
#include "app_list.h"
#include "analog.h"

#define LOOP_TIME 10                      /* Control Loop time in ms */
#define CTRL_LOOP_FREQ (1000 / LOOP_TIME) /* Control Loop frequency  */
#define CONTROL_EVENT 0

DRIVING_STATE DrivingState = DEACTIVATED;

static thread_t *ctrllp = NULL;
static event_source_t CtrlLp_evt;
static virtual_timer_t CtrlLpVT;
static UDC_config_t udc_config = {0};

loop_stats_t loop_stats;

void control_loop_timer(void *p) {
  /* Restarts the timer.*/
  chSysLockFromISR();
  chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, p);
  osalEventBroadcastFlagsI(&CtrlLp_evt, 0);
  chSysUnlockFromISR();
}

static THD_WORKING_AREA(waCtrlLp, 2048);
static THD_FUNCTION(ControlLoop, arg) {
  (void) arg;
  chRegSetThreadName("Robot Control Loop");

  event_listener_t el;
  volatile systime_t last_loop_start = chVTGetSystemTimeX();
  volatile systime_t last_monitor_time = chVTGetSystemTimeX();
  volatile uint32_t cycle_count = 0;

  chEvtRegister(&CtrlLp_evt, &el, CONTROL_EVENT);

  uint16_t oldcount = qeiGetCount(&QEID4);

  while (!chThdShouldTerminateX()) {
    chEvtWaitAny(EVENT_MASK(CONTROL_EVENT));
    chEvtGetAndClearEvents(EVENT_MASK(CONTROL_EVENT));
    decAllAlive();
    // control loop roundtrip stat
    systime_t loop_start = chVTGetSystemTimeX();
    loop_stat_sample(ST2US(loop_start - last_loop_start));
    last_loop_start = chVTGetSystemTimeX();
    // communication roundtrip stat
    systime_t start = chVTGetSystemTimeX();
    UDC_PollObjectList(udc_objectlist);
    systime_t after_comm = chVTGetSystemTimeX();
    comm_stat_sample(ST2US(after_comm - start));
    //
    if (current_running_menu->data.app == &start_robot){
             //motor_get_status(&M[0]);// Miscellaneous Data
             //motor_send_setting(&M[5]);
             if (ps4_data.triangle)//brake
                 motor_setBrake(&M[0]);
             else if (ps4_data.square)//reactivate after brake
                 motor_send_setting(&M[0]);//should have set the motor global setting before calling this
             //motor_send_setpoint(&M[0]);
             //Servo1.command[0] = (qeiGetCount(&QEID4) - oldcount) * 10;
             else if (ps4_data.ps)
                 DeactivateDriving();
             M[0].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
             M[5].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
             M[6].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
             palSetPad(GPIOC, GPIOC_LED_G);
    }else if (current_running_menu->data.app == &ps4_test_app){
             //should not do anything at all --> TODO: to be removed
           palClearPad(GPIOC, GPIOC_LED_G);
    }
    cycle_count++;
    if(start - last_monitor_time > MS2ST(LOOP_STAT_MONITOR_PERIOD_MS)){
         loop_stats.loop_frequency = (float) cycle_count / LOOP_STAT_MONITOR_PERIOD_MS * 1000.0;
         loop_stat_mean_update();
         comm_stat_mean_update();
         if(loop_stats.loop_frequency < 0.75 * CTRL_LOOP_FREQ)
             loop_stats.overruns++;
         cycle_count = 0;
         last_monitor_time = start;
         }
    }
    chEvtUnregister(&CtrlLp_evt, &el);
}

static THD_WORKING_AREA(wa_aux, 1024);
static THD_FUNCTION(auxiliary_comm, arg){
  (void) arg;
  chRegSetThreadName("auxiliary communication thread");
  while (!chThdShouldTerminateX()) {
#if USE_MOTOR_0
    motor_get_status(&M[0]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_1
    motor_get_status(&M[1]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_2
    motor_get_status(&M[2]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_3
    motor_get_status(&M[3]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_4
    motor_get_status(&M[4]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_5
    motor_get_status(&M[5]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_6
    motor_get_status(&M[6]);
    chThdSleepMilliseconds(50);
#endif
#if USE_MOTOR_7
    motor_get_status(&M[7]);
    chThdSleepMilliseconds(50);
#endif
     if (current_running_menu->data.app == &line_sensor_test_app){
#if USE_LINESENSOR_0
        linesensor_get_data(&LineSensor[0]);
        chThdSleepMilliseconds(50);
#endif
#if USE_LINESENSOR_1
        linesensor_get_data(&LineSensor[1]);
        chThdSleepMilliseconds(50);
#endif
#if USE_LINESENSOR_2
        linesensor_get_data(&LineSensor[2]);
        chThdSleepMilliseconds(50);
#endif
#if USE_LINESENSOR_3
        linesensor_get_data(&LineSensor[3]);
        chThdSleepMilliseconds(50);
#endif
     }else{
          continue;
     }
   }
}

void ActivateDriving(void){
  if (DrivingState == DEACTIVATED){
    M[0].Setting = DefaultVMode;//please initialize the motor with something else, this pid sucks
    M[1].Setting = DefaultVMode;
    M[2].Setting = DefaultVMode;
    M[3].Setting = DefaultVMode;
    M[4].Setting = DefaultVMode;
    M[5].Setting = DefaultPMode;
    M[6].Setting = DefaultPMode;
    M[7].Setting = DefaultVMode;
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
#if USE_LINESENSOR_0
        linesensor_get_data(&LineSensor[0]);
#endif
#if USE_LINESENSOR_1
        linesensor_get_data(&LineSensor[1]);
#endif
#if USE_LINESENSOR_2
        linesensor_get_data(&LineSensor[2]);
#endif
#if USE_LINESENSOR_3
        linesensor_get_data(&LineSensor[3]);
#endif
        /* Control Loop Thread */
        ctrllp = chThdCreateStatic(waCtrlLp, sizeof(waCtrlLp), HIGHPRIO, ControlLoop, NULL);
        chThdCreateStatic(wa_aux, sizeof(wa_aux), NORMALPRIO, auxiliary_comm, NULL);
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
    motor_setIdle(&M[7]);
#endif
  }
}

extern volatile int DebugRun[4];

void decAllAlive(void){
#if USE_MOTOR_0
    motor_decAlive(&M[0]);
#endif
#if USE_MOTOR_1
    motor_decAlive(&M[1]);
#endif
#if USE_MOTOR_2
    motor_decAlive(&M[2]);
#endif
#if USE_MOTOR_3
    motor_decAlive(&M[3]);
#endif
#if USE_MOTOR_4
    motor_decAlive(&M[4]);
#endif
#if USE_MOTOR_5
    motor_decAlive(&M[5]);
#endif
#if USE_MOTOR_6
    motor_decAlive(&M[6]);
#endif
#if USE_MOTOR_7
    motor_decAlive(&M[7]);
#endif
#if USE_SERVO && SERVO_NUMBER > 0
    servo_decAlive(&Servo1);
#endif
#if USE_SERVO && SERVO_NUMBER > 8
    servo_decAlive(&Servo2);
#endif
#if USE_ENCODER && ENCODER_NUMBER > 0
    encoder_decAlive(&encoder1_2);
#endif
#if USE_ENCODER && ENCODER_NUMBER > 2
    encoder_decAlive(&encoder3_4);
#endif
#if USE_LINESENSOR_0
    linesensor_decAlive(&LineSensor[0]);
#endif
#if USE_LINESENSOR_1
    linesensor_decAlive(&LineSensor[1]);
#endif
#if USE_LINESENSOR_2
    linesensor_decAlive(&LineSensor[2]);
#endif
#if USE_LINESENSOR_3
    linesensor_decAlive(&LineSensor[3]);
#endif
}

void InitDriving(void) {
  osalEventObjectInit(&CtrlLp_evt);
  memset(&loop_stats, 0, sizeof(loop_stats));
  UDC_Init(&udc_config);
  UDC_Start();
}


