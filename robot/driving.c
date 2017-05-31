
#include "ch.h"
#include "drivers.h"
#include "driving.h"
#include "string.h"
#include "loop_stats.h"
#include "motor.h"
#include "encoder.h"
#include "servo.h"
#include "linesensor.h"
//#include "udc_objectlist.h"
//#include "udc.h"
//#include "ps4_usbhost.h"
#include "menu_struct.h"
#include "app_list.h"
#include "analog.h"
#include "auto_path.h"
#include "pid.h"
#include "ds4.h"
#include "umd.h"
#include "umd_objectlist.h"

#define LOOP_TIME 10                      /* Control Loop time in ms */
#define CTRL_LOOP_FREQ (1000 / LOOP_TIME) /* Control Loop frequency  */
#define CONTROL_EVENT 0

DRIVING_STATE DrivingState = DEACTIVATED;

static thread_t *ctrllp = NULL;
static event_source_t CtrlLp_evt;
static virtual_timer_t CtrlLpVT;
//<<<<<<< HEAD
//static UDC_config_t udc_config = {0};
//=======
//>>>>>>> b1ab300e10eec07a0da4c8f514d46b53bed302ea

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
  uint8_t motor_iter = 0;

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
    //UMD_PollObjectList(umd_objectlist);
    systime_t after_comm = chVTGetSystemTimeX();
    comm_stat_sample(ST2US(after_comm - start));
    //
    runButton();
    if (current_running_menu->data.app == &start_robot){
      //motor_get_status(&M[4]);
      //motor_get_status(&M[5]);
      //motor_get_status(&M[6]);
      RunPath();
      palClearPad(GPIOC, GPIOC_LED_G);
    }else if (current_running_menu->data.app == &ps4_test_app){
             //should not do anything at all --> TODO: to be removed
           palClearPad(GPIOC, GPIOC_LED_G);
    }


//    //get motor board status
//    if(motor_get_status(&M[motor_iter]) == UMD_OK){
//      M[motor_iter].timeout = 3;
//      if(!(M[motor_iter].Board.State & MOTOR_STATE_OK)){
//        motor_send_setting(&M[motor_iter]);
//      }
//    }else{
//      if(M[motor_iter].timeout)
//        M[motor_iter].timeout--;
//    }
//    motor_iter = (motor_iter + 1) % MOTOR_NUM;
//
//
//    M[0].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
//    M[1].SetPoint = DS4.hat_right_y - 128;

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

static THD_WORKING_AREA(wa_aux, 2048);
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
#if IS_MOTOR_0_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[0]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[0]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_1_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[1]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[1]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_2_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[2]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[2]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_3_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[3]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[3]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_4_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[4]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[4]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_5_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[5]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[5]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_6_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[6]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[6]);
    chThdSleepMilliseconds(50);
#endif
#if IS_MOTOR_7_DC
    if(DrivingState == ACTIVATED)
         motor_send_setting(&M[7]);
    else if(DrivingState == DEACTIVATED)
         motor_setIdle(&M[7]);
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
     }
     chThdSleepMicroseconds(1);
   }
}

void ActivateDriving(void){
  if (DrivingState == DEACTIVATED){
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
//<<<<<<< HEAD
//=======
//  chSysLock();
//  /* Stops the timer.*/
//  chVTDoResetI(&CtrlLpVT);
//  chSysUnlock();
//
//  //motor_setIdle(&M[0]);
//>>>>>>> b1ab300e10eec07a0da4c8f514d46b53bed302ea
}

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

  motor_init(&M[0], &M0VMode);
  motor_init(&M[1], &M1VMode);
  motor_init(&M[2], &M2VMode);
  motor_init(&M[3], &M3VMode);
  motor_init(&M[4], &M4VMode);
  motor_init(&M[5], &M5VMode);
  motor_init(&M[6], &M6VMode);
  motor_init(&M[7], &M7VMode);
  p_profile_init();

  //UMD_Master_Init();
  //UMD_Master_Start();

}


