/*
 * pid.c
 *
 *  Created on: 2015¦~4¤ë5¤é
 *      Author: Hung
 */
#include "ch.h"
#include "hal.h"
#include "pid.h"
#include "driving.h"
#include "app.h"
#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7
#include "motor.h"
#endif
//static int output, pre_output, error, pre_error;
P_PROFILE pmotor[4] = {{0}};
#if  USE_MOTOR_0  ||  USE_MOTOR_1  ||  USE_MOTOR_2  ||  USE_MOTOR_3  ||  USE_MOTOR_4  ||  USE_MOTOR_5  ||  USE_MOTOR_6  ||  USE_MOTOR_7

int df = 0;
int RUN_funt(P_PROFILE *motor, long int target) {
    long int p_term, d_term;

    motor->error = target - motor->abs_pos;

    p_term = motor->error;
    motor->I_term = motor->I_term + motor->error / 100.0;
    d_term = (motor->error - motor->pre_error)*10;
    motor->pre_error = motor->error;

    motor->output = motor->kp * p_term + motor->ki * (motor->I_term) + motor->kd * d_term + motor->kff * (motor->ff_term);

    if (motor->output - motor->pre_output > motor->max_acc)
      motor->output = motor->pre_output + motor->max_acc;
    if (motor->output - motor->pre_output < -motor->max_acc)
      motor->output = motor->pre_output - motor->max_acc;

    motor->output = motor->output > motor->max_speed ? motor->max_speed : motor->output;
    motor->output = motor->output < -motor->max_speed ? -motor->max_speed : motor->output;

    M[motor->motor_idx].SetPoint = motor->output;
    motor->pre_output = motor->output;

    if (motor->bound_en == 1) {
        if (motor->abs_pos >= motor->posUpLim && motor->output > 0){
            STOP_funt(motor);
        }
        if (motor->abs_pos <= motor->posLowLim && motor->output < 0){
            STOP_funt(motor);
        }
    }

    if(motor->error > -motor->deadzone && motor->error < motor->deadzone){
      return 1;
    }else{
      return 0;
    }
}

void STOP_funt(P_PROFILE *motor) {
    M[motor->motor_idx].SetPoint = 0;
    motor->I_term = 0;
    motor->ff_term = 0;
    motor->output = 0;
    motor->pre_output = 0;
    motor->error = 0;
    motor->pre_error = 0;
    motor->ff_counter = 0;
}

void update_pmotor(void) {
//    motor->current_pos += EncoderData1[0];
//    if(motor->current_pos < 0)
//        motor->current_pos += 4096;
//    motor->current_pos = motor->current_pos % 4096;
//    motor->abs_pos = M[motor->motor_idx].Board.ADCValue;
      pmotor[0].current_pos = M[pmotor[0].motor_idx].Board.EncoderCount - pmotor[0].offset;
      pmotor[0].abs_pos = pmotor[0].current_pos / pmotor[0].scale;
      pmotor[1].current_pos = M[pmotor[1].motor_idx].Board.EncoderCount - pmotor[1].offset;
      pmotor[1].abs_pos = pmotor[1].current_pos / pmotor[1].scale;
      pmotor[2].current_pos = M[pmotor[2].motor_idx].Board.EncoderCount - pmotor[2].offset;
      pmotor[2].abs_pos = pmotor[2].current_pos / pmotor[2].scale;
//      pmotor[2].current_pos = M[pmotor[2].motor_idx].Board.EncoderCount - pmotor[2].offset;
//      pmotor[2].abs_pos = pmotor[2].current_pos / pmotor[2].scale;
//      pmotor[3].current_pos = M[pmotor[3].motor_idx].Board.EncoderCount - pmotor[3].offset;
//      pmotor[3].abs_pos = pmotor[3].current_pos / pmotor[3].scale;

}
#endif
#define PID_INTEGRATION_TERM_LIMIT 1000
int PIDcontroller(TARGET *t, int src, GAIN *pid, int circular_flag){
    int p_term = t->destination - src;
    if(p_term > -t->deadzone && p_term <t->deadzone){
      t->reach_flag = 1;
    }else{
      t->reach_flag =0;
    }

    if(circular_flag){
      if(p_term > 1800){
        p_term -= 3600;
      }
      if(p_term < -1800){
        p_term += 3600;
      }
    }
    (pid->i_term) += p_term/100.0;
    int d_term = 100*(p_term - pid->pre_input);  //to be modified(add low pass filter)
    if(pid->i_term > PID_INTEGRATION_TERM_LIMIT)
      pid->i_term = PID_INTEGRATION_TERM_LIMIT;
    if(pid->i_term < -PID_INTEGRATION_TERM_LIMIT)
      pid->i_term = -PID_INTEGRATION_TERM_LIMIT;

    int output = (int)(pid->kp*p_term + pid->ki*(pid->i_term) + pid->kd*d_term);
    output = acc_limit(pid->pre_output, output, t->acc_lim);
    output = sp_limit(output, t->speed_lim);
    pid->pre_output = output;
    pid->pre_input = p_term;
    return output;
}

int acc_limit(int current, int next, int limit){
    if(next - current > limit)
        return current + limit;
    if(next - current < -limit)
        return current - limit;

    return next;

}

int sp_limit(int input, int limit){
    if(input > limit)
        return limit;
    if(input < -limit)
        return -limit;

    return input;
}

int run_p_mode(MOTOR_COMMAND cmd, P_PROFILE *pmotor, long int set_point) {
  int pmode_flag = 0;
  switch (cmd) {
//      case RUN:
//          pmode_flag = RUN_funt(pmotor, set_point);
//          break;
//      case PAUSE:
//          STOP_funt(pmotor);
//          break;
      default:
          break;
  }
  return pmode_flag;
}

void p_profile_init(void) {
  // 0 to -848904
    pmotor[0].motor_idx = 4;
    pmotor[0].adc_idx = 4;
    pmotor[0].scale = 425;
    pmotor[0].max_acc = 50;
    pmotor[0].max_speed = 1300;
    pmotor[0].bound_en = 1;
    pmotor[0].posLowLim = -10;    //relative to abs_pos
    pmotor[0].posUpLim = 550;     //relative to abs_pos
    pmotor[0].current_pos = 0;
    pmotor[0].deadzone = 10;
    pmotor[0].I_max = 400;
    pmotor[0].kp = 4;
    pmotor[0].ki = 0.06;
    pmotor[0].kd = 0;
    pmotor[0].kff = 0;

    pmotor[1].motor_idx = 5;
    pmotor[1].adc_idx = 5;
    pmotor[1].scale = 75.4879;
    pmotor[1].max_acc = 50;
    pmotor[1].max_speed = 1800;
    pmotor[1].bound_en = 1;
    pmotor[1].posLowLim = -2383;    //relative to abs_pos   //-2383
    pmotor[1].posUpLim = 6617;     //relative to abs_pos    //6617
    pmotor[1].current_pos = 0;
    pmotor[1].deadzone = 60;
    pmotor[1].I_max = 400;
    pmotor[1].kp = 1;
    pmotor[1].ki = 0.002;
    pmotor[1].kd = 0;
    pmotor[1].kff = 0;

    pmotor[2].motor_idx = 6;
    pmotor[2].adc_idx = 6;
    pmotor[2].scale = 75.4879;   //284.86
    pmotor[2].max_acc = 50;
    pmotor[2].max_speed = 1800;
    pmotor[2].bound_en = 1;
    pmotor[2].posLowLim = -1200;    //relative to abs_pos
    pmotor[2].posUpLim = 7800;     //relative to abs_pos
    pmotor[2].current_pos = 0;
    pmotor[2].deadzone = 60;
    pmotor[2].I_max = 400;
    pmotor[2].kp = 1;
    pmotor[2].ki = 0.002;
    pmotor[2].kd = 0;
    pmotor[2].kff = 0;
}
