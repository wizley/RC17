
#include "ch.h"
#include "motor.h"
#include "drivers.h"
#include "string.h"

#include "driving.h"
#include "loop_stats.h"
#include "ds4.h"

#include "motor.h"
#include "servo.h"
#include "encoder.h"
#include "umd.h"
#include "umd_objectlist.h"

#define LOOP_TIME 10                      /* Control Loop time in ms */
#define CTRL_LOOP_FREQ (1000 / LOOP_TIME) /* Control Loop frequency  */

#define CONTROL_EVENT 0

static thread_t *ctrllp = NULL;
static event_source_t CtrlLp_evt;
static virtual_timer_t CtrlLpVT;

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

    // control loop roundtrip stat
    systime_t loop_start = chVTGetSystemTimeX();
    loop_stat_sample(ST2US(loop_start - last_loop_start));
    last_loop_start = chVTGetSystemTimeX();

    // communication roundtrip stat
    systime_t start = chVTGetSystemTimeX();
    UMD_PollObjectList(umd_objectlist);
    systime_t after_comm = chVTGetSystemTimeX();
    comm_stat_sample(ST2US(after_comm - start));


    //get motor board status
    if(motor_get_status(&M[motor_iter]) == UMD_OK){
      M[motor_iter].timeout = 3;
      if(!(M[motor_iter].Board.State & MOTOR_STATE_OK)){
        motor_send_setting(&M[motor_iter]);
      }
    }else{
      if(M[motor_iter].timeout)
        M[motor_iter].timeout--;
    }
    motor_iter = (motor_iter + 1) % MOTOR_NUM;


    M[0].SetPoint = (qeiGetCount(&QEID4) - oldcount) * 10;
    M[1].SetPoint = DS4.hat_right_y - 128;


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

void ActivateDriving(void){
  if(ctrllp == NULL){
    /* Control Loop Thread */
    ctrllp = chThdCreateStatic(waCtrlLp, sizeof(waCtrlLp), HIGHPRIO, ControlLoop, NULL);
  }

  chSysLock();
  /* Starts the timer.*/
  chVTDoSetI(&CtrlLpVT, MS2ST(LOOP_TIME), control_loop_timer, NULL);
  chSysUnlock();
}

void DeactivateDriving(void){
  if(ctrllp != NULL){
    chThdTerminate(ctrllp);
  }
  chSysLock();
  /* Stops the timer.*/
  chVTDoResetI(&CtrlLpVT);
  chSysUnlock();

  //motor_setIdle(&M[0]);
}

extern volatile int DebugRun[4];

void InitDriving(void) {
  osalEventObjectInit(&CtrlLp_evt);

  memset(&loop_stats, 0, sizeof(loop_stats));

  motor_init(&M[0], &DefaultVMode);

  UMD_Master_Init();
  UMD_Master_Start();
}
