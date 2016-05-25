/*
 * pid.h
 *
 *  Created on: 2015¦~4¤ë5¤é
 *      Author: Hung
 */

#ifndef PID_H_
#define PID_H_

typedef struct Position
{
    int destination;
    int path_mode; //0 for straight, 1 for cirucular
    int travel_d;
    int deadzone;
    int speed_lim;
    int acc_lim;
    int reach_flag;
}TARGET;

typedef struct PID_gain
{
    float kp;
    float ki;
    float kd;
    int i_term;
    int pre_output;
    int pre_input;
}GAIN;

typedef struct Path
{
    GAIN pid_const, a_pid_const;
        int no_point;
        int *p;
}curve;

typedef volatile struct
{
  int bound_en;    //0 = disable; 1 = enable
  int input_invert;   //0 = not invert, 1 = invert
  int adc_idx;
  long offset;
  float scale;
  int dist;
  int ff_counter;
  int deadzone,deadcount;
  int running_flag,reach_flag;
  int motor_idx;
  float kp,ki,kd,kff;
  int I_term,I_max,ff_term;
  int max_speed,max_acc;
  long int current_pos,posUpLim, posLowLim;
  int  abs_pos;
  int output, pre_output, error, pre_error;
}P_PROFILE;

typedef enum tagPMode
{
//    SET,
    RUN,
    STOP,
    NONE
}MOTOR_COMMAND;

void SET_funt(P_PROFILE *motor,long int set_pos);
int RUN_funt(P_PROFILE *motor, long int target);
void STOP_funt(P_PROFILE *motor);
int run_p_mode(MOTOR_COMMAND cmd, P_PROFILE *pmotor, long int set_point);
void p_profile_init(void);
void update_pmotor(void);
int PIDcontroller(TARGET *t, int src, GAIN *pid, int circular_flag);
int acc_limit(int current, int next, int limit);
int sp_limit(int input, int limit);
extern P_PROFILE pmotor[4];

#endif /* PID_H_ */
