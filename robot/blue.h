/*
 * auto_path.h
 *
 *  Created on: 2016¦~5¤ë25¤é
 *      Author: Hung
 */

#ifndef ROBOT_BLUE_H_
#define ROBOT_BLUE_H_
#include "pid.h"

extern int track_init0;
extern int x,y,tRotation;
extern int E0,E1,E2,E3;
extern int line_angle;
extern int line_y;
extern int sum;
extern int online_flag;
extern int pole_flag;
extern int pole_detect_flag,pole_reach_flag;
extern int line_a_d,line_x_d;
extern int stage1_line_flag_x;
extern int output_line_x;
extern int output_line_a;
extern int pass_line_count[2];
extern int stage4_line_flag_x;
extern int push_length;
extern int finish_flag;
extern int servo_time;
extern int servo_state;
extern int run_auto_flag;
extern int auto_state;
extern int stage;
extern TARGET z_dst,x_dst,y_dst;
extern int tune_wind_1,tune_wind_2;

extern int spinSpeed;
extern int deltaEN;

void RunPath(void);

#endif /* ROBOT_BLUE_H_ */
