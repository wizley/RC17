/*
 * red.h
 *
 *  Created on: 2016¦~6¤ë6¤é
 *      Author: Hung
 */

#ifndef ROBOT_RED_H_
#define ROBOT_RED_H_

extern int track_init0_r;
extern int x_r,y_r,tRotation_r;
extern int E0_r,E1_r,E2_r,E3_r;
extern int line_angle_r;
extern int line_y_r;
extern int sum_r;// Sum to tune encoder
extern int online_flag_r;
extern int pole_flag_r;
extern int pole_detect_flag_r,pole_reach_flag_r;
extern int line_a_d_r,line_x_d_r;
extern int stage1_line_flag_x_r;
extern int output_line_x_r;
extern int output_line_a_r;
extern int pass_line_count_r[4];
extern int stage2_line_flag_r;
extern int push_length_r;


extern int step_r;
extern int debug_display_r[10];

void RunPath_r(void);

#endif /* ROBOT_RED_H_ */
