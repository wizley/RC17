/*
 * abc.c
 *
 *  Created on: 2016¦~5¤ë25¤é
 *      Author: Hung
 */
#include "tgmath.h"
#include "app.h"
#include "driving.h"
#include "pid.h"
#include "common.h"
#include "encoder.h"
#include "linesensor.h"
#include "motor.h"
#include "servo.h"
#include "ps4_usbhost.h"
#include "analog.h"

#define TURN_LIMIT 500
#define SAFE_MARGIN 300
#define LINE_NARROW 20
#define LINE_THICK 50

#define SHRINK 1010
#define STRETCH 1313
#define FLAT 1270   // 1240
#define LIFT 1850
#define HOLD 1630
#define PUSH 1900

int output_line_x = 0;
int output_line_a = 0;

int E0,E1,E2,E3;
int base_lock = 1;
float tRotationf,xf,yf;
float correct_x,correct_y;
int x,y,tRotation;
float HeadingAngle = 0;
int xSpeed, ySpeed, zSpeed, turn;
int pre_xSpeed, pre_ySpeed, pre_turn;
int xSpeed_right, ySpeed_right;
int auto_x, auto_y;
int x_com,y_com;
int stage = 0;
int servo_time = 0;

int online_flag;
int stage0_line_flag_y = 0;
int stage1_line_flag_y = 0;
int stage2_line_flag_y = 0;
int stage4_line_flag_y = 0;

int stage0_line_flag_x = 0;
int stage1_line_flag_x = 0;
int stage2_line_flag_x = 0;
int stage4_line_flag_x = 0;

int pole_flag = 0;
int pre_pole_flag = 0;
int pole_detect_flag = 0;
int pole_reach_flag = 0;

int servo_state = 0;
int pick_delay = 0;
int prop_detect = 0;

int pass_line_count[2] = {0};
int pre_line_position[4] = {0};

int check_point[3] = {0};

int fan_delay = 0;
int fan_delay1 = 0;
int fan_on = 0;

int finish_flag = 0;

int run_auto_flag = 0;
int auto_state = -1;
int pre_auto_state = 0;
int auto_timer = 0;
int auto_stage_delay = 0;
int change_state_flag = 0;
int climb_flag = 0;

int x_position_ready = 0;

int tune_wind_1 = 0;
int tune_wind_2 = 0;

int manual_delay = 0;

TARGET x_dst = {0},y_dst = {0},a_dst = {0},r_dst = {0},z_dst = {0},line_dst_x = {0},line_dst_a = {0};
GAIN a_control = {0};
GAIN x_control = {0};
GAIN y_control = {0};
GAIN r_control = {0};
GAIN z_control = {0};
GAIN linex_control = {0};
GAIN linea_control = {0};

int blue_path0[2] = {-2819,0};

int blue_path1[12][2] =
{
   {-2819,0},
   {-2819,1089},
   {-2534,2151},
   {-2118,2872},
   {-1340,3650},
   {-496,5113},
   {-211,6175},
   {-200,6800},
   {-200,7387},
   {-200,10000},
   {-2200,13000},           //{-3165,13000},
   {-5450,13000}
};

int track_init0 = 0;
int track_init1 = 0;
int track_init2 = 0;

int push_length = 0;

int db_flag[6] = {0};
int bt_delay[6] = {0};
int tt_flag[6] = {0};

float v_track_h = 0;

int hysteresis_flag= 1;

long sum = 0;
float line_anglef = 0;
int line_angle = 0;
int line_y = 0;
int line_x_d = 0;
int line_a_d = 0;
float line_af_d = 0;

int spinSpeed = 0, oldSpinSpeed = 0;
const int accLimit = 60;
int oldM7EN = 0;
int deltaEN;
int old_r1_state_b, old_l1_state_b,old_triangle_state_b,old_circle_state_b, old_dpad_state_b;

int constrain_b(int value, int positiveLimit, int negativeLimit) {
	if(value > positiveLimit)
		value = positiveLimit;
	if(value < negativeLimit)
		value = negativeLimit;
	return value;
}


int accelerationLimit_b(int speed, int oldSpeed,int upperLimit, int lowerLimit ) {
	if(oldSpeed > 0){
		if(speed > oldSpeed + upperLimit) {//forward limit
			speed = oldSpeed + upperLimit;
		}
		if(speed < oldSpeed + -70) {
		speed = oldSpeed + -70;
		}
	}
	if(oldSpeed <= 0) {
		if(speed > oldSpeed + 70) {//backward limit stopstop
			speed = oldSpeed + 70;
		}
		if(speed < oldSpeed + lowerLimit) {
		speed = oldSpeed + lowerLimit;
		}
	}
	return speed;
}


//void UpdatePosition(void) {
//	if(ps4_data.circle) {
//		spinSpeed = 0;
//	}
//	if(ps4_data.square) {
//		spinSpeed = 500;
//	}
//	if(ps4_data.triangle) {
//		spinSpeed = 1000;
//	}
//	if(ps4_data.l1 && old_l1_state_b == 0) {
//		spinSpeed-=1;
//	}
//	old_l1_state_b = ps4_data.l1;
//	if(ps4_data.r1 && old_r1_state_b == 0) {
//		spinSpeed+=1;
//	}
//	old_r1_state_b = ps4_data.r1;
//spinSpeed = constrain_b(spinSpeed, 1400, -1400);
////spinSpeed = AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y)-127), 10);
////deltaEN = M[7].Board.EncoderCounter - oldM7EN;
////oldM7EN = M[7].Board.EncoderCounter;
//spinSpeed = accelerationLimit_b(spinSpeed, oldSpinSpeed, accLimit, -accLimit);
//M[5].SetPoint = spinSpeed;
//oldSpinSpeed = spinSpeed;
//
//}

void ClearPosition(void){
//  tRotationf = 0;
//  xf = 0;
//  yf = 0;
//  x = 0;
//  y = 0;
//  sum = 0;
}

void UnlockBase(void){
//  motor_setIdle(&M[0]);
//  motor_setIdle(&M[1]);
//  motor_setIdle(&M[2]);
//  motor_setIdle(&M[3]);
}

void LockBase(void){
//  motor_send_setting(&M[0]);
//  motor_send_setting(&M[1]);
//  motor_send_setting(&M[2]);
//  motor_send_setting(&M[3]);
}
//int xOldMotorSpeed = 0;
//int xMotorSpeed = 0;
//int turn = 0;
//int oldturn = 0;
void RunPath(void) {

//	xMotorSpeed = AddDeadZone((int)((uint16_t)(ps4_data.r2_trigger)), HatDeadzone )* hatMultiplier- AddDeadZone((int)((uint16_t)(ps4_data.l2_trigger)), HatDeadzone ) * hatMultiplier;
//	turn = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x) - 127), HatDeadzone ) * hatMultiplier * 2;
//	xMotorSpeed = accelerationLimit(xMotorSpeed, xOldMotorSpeed, acceleration_limit, -acceleration_limit);
//	turn = accelerationLimit(turn, oldturn, acceleration_limit, -acceleration_limit);
//	xMotorSpeed = constrain(xMotorSpeed, upLimit, lowLimit);
//	M[0].SetPoint = xMotorSpeed + turn;
//	M[1].SetPoint = -xMotorSpeed + turn;
//	xOldMotorSpeed = xMotorSpeed;
//	oldturn = turn;
  //  if(M[7].Board.ADCValue > 30000){
  //    palClearPad(GPIOC, GPIOC_LED_G);
  //  }else{
  //    palSetPad(GPIOC, GPIOC_LED_G);
  //  }

  //    if(ButtonDown[8] == 1){
  //      palClearPad(GPIOC, GPIOC_LED_B);
  //    }
  //    else{
  //      palSetPad(GPIOC, GPIOC_LED_B);
  //    }

//  if(ps4_data.cross){
//    Servo1.command[7] -=3;
//  }else if(ps4_data.triangle){
//    Servo1.command[7] +=3;
//  }
//  if(Servo1.command[7] > 2000){
//    Servo1.command[7] = 2000;
//  }else if(Servo1.command[7] < 1000){
//    Servo1.command[7] = 1000;
//  }

//  if(ps4_data.r1){
//    ClearPosition();
//    a_control.pre_input = 0;
//    a_control.pre_output = 0;
//    x_control.pre_input = 0;
//    x_control.pre_output = 0;
//    y_control.pre_input = 0;
//    y_control.pre_output = 0;
//    r_control.pre_input = 0;
//    r_control.pre_output = 0;
//  }
//
//    ySpeed = -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y)-128), 15);
//    xSpeed = AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x)-128), 15);
//
//  //  zSpeed = -AddDeadZone((int)((uint16_t)(ps4_data.left_hat_x)-128), 15);
//    turn =  -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x)-128), 15);
//    push_length =  AddDeadZone((int)(((int16_t)ps4_data.l2_trigger-ps4_data.r2_trigger)), 15);
//
//    ySpeed_right = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_y)-128), 15);
//    xSpeed_right = AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x)-128), 15);
//
//    if(ps4_data.r1){
//      tune_wind_1 = ySpeed_right/4;
//      tune_wind_2 = xSpeed_right/4;
//    }
//
//    push_length *= 4;     //4.5
//    ySpeed_right *= 8;
//    xSpeed_right *= 8;
//
//    if(xSpeed < 85 && xSpeed > -85){
//      xSpeed *=10;
//    }else{
//      if(xSpeed > 0){
//        xSpeed = 22*xSpeed - 1020;
//      }else{
//        xSpeed = 22*xSpeed + 1020;
//      }
//    }
//    if(ySpeed < 85 && ySpeed > -85){
//      ySpeed *=10;
//    }else{
//      if(ySpeed > 0){
//        ySpeed = 22*ySpeed - 1020;
//      }else{
//        ySpeed = 22*ySpeed + 1020;
//      }
//    }
//
//    if(turn < 85 && turn > -85){
//      turn *=6;
//    }else{
//      if(turn > 0){
//        turn = 11*turn - 424;
//      }else{
//        turn = 11*turn + 424;
//      }
//    }
//
//    if(turn > TURN_LIMIT)
//      turn = TURN_LIMIT;
//    else if(turn < -TURN_LIMIT)
//      turn = -TURN_LIMIT;
//
//    if(ps4_data.r3 == 0){
//      turn = 0;
//    }else{
//      ySpeed_right = 0;
//      xSpeed_right = 0;
//    }
//
    UpdatePosition();
    update_pmotor();
///////////////////////////////////auto state machine
//    switch(auto_state){
//      case -1:  //idle
//        run_auto_flag = 0;
//        if(base_lock){
//          if(Button_edge[0]){
//            auto_state = 5;
//            run_auto_flag = 1;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//          }else if(Button_edge[3]){
//            auto_state = 0;
//            run_auto_flag = 1;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//          }else if(Button_edge[4]){
//            auto_state = 3;
//            run_auto_flag = 1;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//          }else if(Button_edge[5]){
//            auto_state = 4;
//            run_auto_flag = 1;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//          }
//        }
//        auto_timer = 0;
//        auto_stage_delay = 0;
//        break;
//      case 0:   //stage 0 path
//        if(x_dst.reach_flag && y_dst.reach_flag){
//          run_auto_flag = 0;
//          auto_timer ++;
//          if(auto_timer > 10){
//            auto_timer = 0;
//            auto_state = 1;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//          }
//        }else{
//          run_auto_flag = 1;
//        }
//
//        if(ps4_data.circle || ButtonDown[0] || ButtonDown[1] || ButtonDown[2] || ButtonDown[4] || ButtonDown[5] || ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//      case 1:   //stage 1 path
//        if(pass_line_count[0] == 7 && y_dst.reach_flag){
//          run_auto_flag = 0;
//          //auto_timer ++;
//          if(fan_delay > 600){
//            auto_timer = 0;
//            auto_state = 2;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//            run_auto_flag = 1;
//          }
//        }else{
//          auto_timer ++;
//          if(auto_timer < 120){
//            fan_on = 1;
//          }else{
//            run_auto_flag = 1;
//          }
//        }
//
//        if(ps4_data.circle || ButtonDown[0] || ButtonDown[1] || ButtonDown[2] || ButtonDown[3] || ButtonDown[4] || ButtonDown[5] || ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//      case 2:   //stage 2 path
//        if(x_dst.reach_flag && y_dst.reach_flag){
//          run_auto_flag = 0;
////          auto_timer ++;
////          if(auto_timer > 100){
////            auto_timer = 0;
////          }
//        }else{
//          run_auto_flag = 1;
//        }
//
//        if(ps4_data.circle || ButtonDown[0] || ButtonDown[1] || ButtonDown[2] || ButtonDown[3] || ButtonDown[4] || ButtonDown[5] || ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//      case 3:   //retry path (river yet)
//        if(pass_line_count[0] == 7 && y_dst.reach_flag && x_dst.reach_flag){
//          run_auto_flag = 0;
//          fan_on = 1;
//          if(fan_delay > 600){
//            auto_timer = 0;
//            auto_state = 2;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//            run_auto_flag = 1;
//          }
//        }
//        if(ps4_data.circle || ButtonDown[0] || ButtonDown[1] || ButtonDown[2] || ButtonDown[3] || ButtonDown[5] || ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//      case 4:   //retry path (river passed)
//        if(pass_line_count[0] == 7 && y_dst.reach_flag && x_dst.reach_flag){
//          run_auto_flag = 0;
//          fan_on = 1;
//          if(fan_delay > 400){
//            auto_timer = 0;
//            auto_state = 2;
//            x_dst.reach_flag = 0;
//            y_dst.reach_flag = 0;
//            run_auto_flag = 1;
//          }
//        }
//        if(ps4_data.circle || ButtonDown[0] || ButtonDown[1] || ButtonDown[2] || ButtonDown[3] || ButtonDown[4] || ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//      case 5:
//        if(x_dst.reach_flag && y_dst.reach_flag){
//          run_auto_flag = 0;
//        }else{
//          run_auto_flag = 1;
//        }
//
//        if(ps4_data.circle || ButtonDown[1] || ButtonDown[2] || ButtonDown[3] || ButtonDown[4] || ButtonDown[5]|| ButtonDown[6]){
//          auto_state = -1;
//        }
//        break;
//    }
//    if(pre_auto_state != auto_state){
//      change_state_flag = 1;
//    }else{
//      change_state_flag = 0;
//    }
//    pre_auto_state = auto_state;
///////////////////////////////fan
//    if(ps4_data.cross){
//       fan_on = 1;
//    }
//
////    if(ps4_data.square && stage == 1){
////      manual_delay ++;
////    }else{
////      manual_delay = 0;
////    }
////
////    if(manual_delay > 120){
////      fan_on = 1;
////    }
//
//     int river_fan = 0;
//     if(fan_on){
//      if(stage == 1 || stage == 2 || stage == 4){
//        if(y < blue_path1[1][1] - 800){
//          Servo1.command[0] = 1500;
//        }else if(y < blue_path1[4][1]){
//          Servo1.command[0] = 1580;
//        }else if(y < blue_path1[6][1] - 300){
//          Servo1.command[0] = 1540;
//        }else if(pass_line_count[0] < 7){
//          Servo1.command[0] = 1000;
//        }else if(pass_line_count[0] == 7){
//          river_fan = 1;
//        }
//      }else{
//        river_fan = 0;
//        Servo1.command[0] = 1000;
//      }
//     }
//
//     if(ps4_data.triangle || river_fan){
//       fan_delay ++;
//       if(auto_state == 4){
//         if(fan_delay < 10){
//           Servo1.command[0] = 1000;
//         }else if(fan_delay < 400){
//           Servo1.command[0] = 1600;
//         }else{
//           Servo1.command[0] = 1000;
//         }
//       }else{
//         if(fan_delay < 10){
//           Servo1.command[0] = 1000;
//         }else if(fan_delay < 350){
//           Servo1.command[0] = 1410;
//         }else if(fan_delay < 500){
//           Servo1.command[0] = 1560;
//         }else if(fan_delay < 600){
//           Servo1.command[0] = 1600;
//         }else{
//           Servo1.command[0] = 1000;
//         }
//       }
//     }else{
//       fan_delay = 0;
//     }
//
//     if(climb_flag == 100 && !z_dst.reach_flag && !finish_flag){
//       fan_delay1 ++;
//       if(fan_delay1 > 500){
//         fan_delay1 = 500;
//       }
//
//       if(fan_delay1 < 100){
//         Servo1.command[0] = 1000;
//       }else if(fan_delay1 < 250){
//         Servo1.command[0] = 1600;
//       }else{
//         Servo1.command[0] = 1000;
//       }
//     }else{
//       fan_delay1 = 0;
//     }
//
//     if(ps4_data.circle){
//       Servo1.command[0] = 1000;
//       fan_on = 0;
//     }
//
//     if(Servo1.command[0] > 1600){
//       Servo1.command[0] = 1600;
//     }
//     if(Servo1.command[0] < 1000){
//       Servo1.command[0] = 1000;
//     }
//
//     db_flag[3] = ps4_data.triangle;
//     db_flag[4] = ps4_data.cross;
/////////////////////////////////////////////fan servo
//    if(y < blue_path1[1][1] - 500){
//      Servo1.command[7] = 1214;
//    }else if(y < blue_path1[3][1]){
//      Servo1.command[7] = 1179;
//    }else if(y < blue_path1[5][1]){
//      Servo1.command[7] = 1214 + 21;
//    }else if(y < blue_path1[7][1] - 500){ //1420
//      Servo1.command[7] = 1214; //1633
//    }else if(pole_reach_flag){
//      Servo1.command[7] = 1668;
//    }else{
//      if(auto_state == 4){
//        Servo1.command[7] = 1380;
//      }else{
//        if(fan_delay < 550){
//          Servo1.command[7] = 1400;
//        }else if(fan_delay < 650){
//          Servo1.command[7] = 1380;
//        }
//      }
//    }
///////////////////////////////vertical track
//    int track_y_offset = 400;
//    int track_h_offset = 20;
//    if(ps4_data.r1){
//      v_track_h = 100;
//    }else{
//      if(y < 1000 - track_y_offset){
//        v_track_h = track_h_offset;
//      }else if(y < 2062.52 - track_y_offset){
//        v_track_h = (y-1000+track_y_offset)/1062.52*200 + track_h_offset;
//      }else if(y < 3014.52 - track_y_offset){
//      }else if(y < 3792.34 - track_y_offset){
//        v_track_h = (y-3014.52+track_y_offset)/777.82*200 + 200 + track_h_offset;
//      }else if(y < 5013.94 - track_y_offset){
//      }else if(y < 6076.46 - track_y_offset){
//        v_track_h = (y-5013.94+track_y_offset)/1062.52*200 + 400 + track_h_offset;
//      }else if(y < 6831.75 - track_y_offset){
//        v_track_h = 580;
//      }else if(y <= 10000){
//        v_track_h = 580;
//      }else if(y > 10000){
//        v_track_h = 100;
//      }
//    }
//
//    if(v_track_h > 570){
//      v_track_h = 570;
//    }
//    if(v_track_h < 50){
//      v_track_h = 50;
//    }
//
//    if(track_init0 == 0){
//      if(M[4].Board.ADCValue <= 30000){
//        M[4].SetPoint = -300;
//      }else{
//        pmotor[0].offset = M[4].Board.EncoderCounter;
//        track_init0 = 1;
//      }
//    }else if(track_init0 == 1){
//      if(!run_p_mode(RUN,&pmotor[0],100)){
//        track_init0 = 2;
//      }
//    }else{
//        run_p_mode(RUN,&pmotor[0],v_track_h);
//    }
//
//////////////////////////////////////////////////arm servo
//    Servo1.command[4] = 1280;
//    Servo1.command[5] = 1528;
////    if(ps4_data.tpad_click && !db_flag[2]){
////      tt_flag[2] ^= 1;
////    }
//
//    switch (servo_state){
//      case 0:   // 0 for normal pose
//        Servo1.command[1] = LIFT;
//        Servo1.command[2] = SHRINK;
//        prop_detect = 0;
//        if(pole_detect_flag){
//          servo_state = 1;
//        }
//        break;
//      case 1:   // 1 for down arm
//        Servo1.command[1] = FLAT;
//        Servo1.command[2] = SHRINK;
//        prop_detect = 0;
//        pick_delay = 0;
//        if(M[1].Board.ADCValue > 30000){
//          servo_state = 2;
//        }
//        break;
//      case 2:   // 2 for take prop
//        prop_detect = 0;
//        Servo1.command[1] += 3;
//        if(Servo1.command[1] > HOLD){   //1620
//          Servo1.command[1] = HOLD;
//        }
//        pick_delay++;
//        if(pick_delay > 150){
//          Servo1.command[2] = STRETCH;
//          servo_state = 3;
//        }
//        break;
//      case 3:   // 3 for hold prop
//        Servo1.command[1] = HOLD;
//        Servo1.command[2] = STRETCH;
//        prop_detect = 1;
//        servo_time = 0;
//        if(z_dst.reach_flag && !finish_flag){
//          servo_state = 4;
//        }
//        break;
//      case 4:   // 4 for plug prop
//        Servo1.command[1] = PUSH;
//        prop_detect = 1;
//        servo_time ++;
//        if(servo_time == 70){
//          finish_flag = 1;
//          z_dst.reach_flag = 0;
//          servo_state = 5;
//          servo_time = 0;
//        }
//        break;
//      case 5:   // finish pose
//        servo_time ++;
//        Servo1.command[2] = SHRINK;
//        if(servo_time == 50){
//          Servo1.command[1] = HOLD;
//          servo_time = 50;
//        }
//        break;
//    }
//
////    db_flag[2] = ps4_data.tpad_click;
//
///////////////////////////////push motor   100 = 1 mm    p1 = p2 - 1183
//    if(ps4_data.l1){
//      bt_delay[5]++;
//    }else{
//      bt_delay[5] = 0;
//    }
//    if(bt_delay[5] == 50){
//      tt_flag[5] ^= 1;
//    }
//    if(pole_reach_flag && x > blue_path1[11][0] - 100 && x < blue_path1[11][0] + 100 && y > blue_path1[11][1] - 100 && y < blue_path1[11][1] + 100 && (auto_state == 2 || auto_state == 5)){
//      tt_flag[5] = 1;
//    }
//
//    if(track_init1 == 0){
//      if(M[5].Board.ADCValue <= 512){
//        M[5].SetPoint = -1000;
//      }else{
//        track_init1 = 1;
//      }
//    }else if(track_init1 == 1){
//      if(M[5].Board.ADCValue > 512){
//        M[5].SetPoint = 300;
//      }else{
//        track_init1 = 2;
//        M[5].SetPoint = 0;
//        pmotor[1].offset = M[5].Board.EncoderCounter;
//      }
//    }
//
//    if(track_init2 == 0){
//      if(M[6].Board.ADCValue <= 512){
//        M[6].SetPoint = -800;
//      }else{
//        track_init2 = 1;
//      }
//    }else if(track_init2 == 1){
//      if(M[6].Board.ADCValue > 512){
//        M[6].SetPoint = 300;
//      }else{
//        track_init2 = 2;
//        M[6].SetPoint = 0;
//        pmotor[2].offset = M[6].Board.EncoderCounter;
//      }
//    }
//
//    if(track_init1 == 2 && track_init2 == 2){
//      if(tt_flag[5]){
//        if(base_lock){
//          UnlockBase();
//          base_lock = 0;
//        }
//        int flag1 = 0;
//        int flag2 = 0;
//        if(prop_detect){
//          flag1 = run_p_mode(RUN,&pmotor[1],5117);    // 5117
//          flag2 = run_p_mode(RUN,&pmotor[2],6300);    //6300
//        }else{
//          run_p_mode(RUN,&pmotor[1],4917);    // 5117
//          run_p_mode(RUN,&pmotor[2],6100);    //6300
//        }
//        if (flag1 && flag2){
//          climb_flag += 1;
//          if(climb_flag > 100)
//            climb_flag = 100;
//        }
//      }else{
//        if(Button_edge[6]){
//          if(base_lock){
//            UnlockBase();
//            base_lock = 0;
//          }else{
//            LockBase();
//            base_lock = 1;
//          }
//        }
//        run_p_mode(RUN,&pmotor[1],-1244);
//        run_p_mode(RUN,&pmotor[2],-61);
//        climb_flag = 0;
//        z_dst.reach_flag = 0;
//      }
//    }
//
///////////////////////////////////////////////  climb motor
//    if(ps4_data.options){
//      z_dst.reach_flag = 1;
//    }
//    if(!finish_flag){
//      if(climb_flag == 100 && !z_dst.reach_flag && prop_detect){
//        z_control.kp = 1.5;
//        z_control.ki = 0.5;
//        z_dst.acc_lim = 18;
//        z_dst.deadzone = 5;
//        z_dst.speed_lim = 1800;
//        z_dst.destination = 720; //690;  //700
//        int z_output = -PIDcontroller(&z_dst, (int)(ADCValue[0]), &z_control,0);
//        M[7].SetPoint = z_output;
//        if(ADCValue[0] > 690 && M[7].Board.ADCValue < 30000){   //600
//          z_dst.reach_flag = 1;
//        }
//      }else{
//        M[7].SetPoint = 0;
//        z_control.pre_input = 0;
//        z_control.pre_output = 0;
//      }
//    }else{
//      if(climb_flag == 100 && !z_dst.reach_flag){
//        z_control.kp = 2;
//        z_control.ki = 0.7;
//        z_dst.acc_lim = 15;
//        z_dst.deadzone = 5;
//        z_dst.speed_lim = 600;
//        z_dst.destination = 200; //690;  //700
//        int z_output = -PIDcontroller(&z_dst, (int)(ADCValue[0]), &z_control,0);
//        M[7].SetPoint = z_output;
//      }else{
//        M[7].SetPoint = 0;
//        z_control.pre_input = 0;
//        z_control.pre_output = 0;
//      }
//    }
//
//    M[7].SetPoint += push_length;
//
///////////////////////////////path destinations calculation
//    if(ps4_data.dpad_code == DPAD_LEFT || ButtonDown[1]){
//      stage = 0;
//      servo_state = 0;
//      yf = 0;
//      xf = 0;
//      y = 0;
//      x = 0;
//      tRotationf = 0;
//      stage0_line_flag_y = 0;
//      stage1_line_flag_y = 0;
//      stage2_line_flag_y = 0;
//      stage4_line_flag_x = 0;
//      pole_flag = 0;
//      pre_pole_flag = 0;
//      pole_detect_flag = 0;
//      pole_reach_flag = 0;
//      pass_line_count[0] = 0;
//      check_point[1] = 0;
//      Servo1.command[0] = 1000;
//      finish_flag = 0;
//      change_state_flag = 0;
//    }else if(ps4_data.dpad_code == DPAD_UP || (auto_state == 1 && change_state_flag)){
//      stage = 1;
//      servo_state = 0;
//      yf = blue_path0[1];
//      xf = blue_path0[0];
//      y = blue_path0[1];
//      x = blue_path0[0];
//      tRotationf = 0;
//      stage0_line_flag_y = 1;
//      stage1_line_flag_y = 0;
//      stage2_line_flag_y = 0;
//      stage4_line_flag_y = 0;
//      stage4_line_flag_x = 0;
//      pole_flag = 0;
//      pre_pole_flag = 0;
//      pole_detect_flag = 0;
//      pole_reach_flag = 0;
//      pass_line_count[0] = 0;
//      check_point[1] = 0;
//      Servo1.command[0] = 1000;
//      finish_flag = 0;
//      change_state_flag = 0;
//    }else if(ps4_data.dpad_code == DPAD_RIGHT || (auto_state == 2 && change_state_flag)){
//      stage = 2;
//      servo_state = 0;
//      yf = blue_path1[7][1];
//      xf = blue_path1[7][0];
//      y = blue_path1[7][1];
//      x = blue_path1[7][0];
//      tRotationf = 0;
//      stage0_line_flag_y = 1;
//      stage1_line_flag_y = 1;
//      stage2_line_flag_y = 0;
//      stage4_line_flag_y = 0;
//      stage4_line_flag_x = 0;
//      pole_flag = 0;
//      pre_pole_flag = 0;
//      pole_detect_flag = 0;
//      pole_reach_flag = 0;
//      pass_line_count[0] = 8;
//      check_point[1] = 1;
//      Servo1.command[0] = 1000;
//      finish_flag = 0;
//      change_state_flag = 0;
//    }else if(ps4_data.dpad_code == DPAD_DOWN){
//      stage = 3;
//      servo_state = 3;
//      yf = blue_path1[11][1];
//      xf = 0 + 268*(1-cosf(HeadingAngle));
//      y = blue_path1[11][1];
//      x = 0;
//      tRotationf = PI;
//      pole_flag = 0;
//      pre_pole_flag = 0;
//      pole_detect_flag = 0;
//      pole_reach_flag = 0;
//      stage0_line_flag_y = 1;
//      stage1_line_flag_y = 1;
//      stage2_line_flag_y = 1;
//      stage4_line_flag_y = 0;
//      stage4_line_flag_x = 0;
//      check_point[1] = 1;
//      Servo1.command[0] = 1000;
//      finish_flag = 0;
//      change_state_flag = 0;
//    }else if(ButtonDown[2]){
//      stage = 4;
//      servo_state = 0;
//      yf = 0;
//      xf = 0;
//      y = 0;
//      x = 0;
//      tRotationf = 0;
//      stage0_line_flag_y = 0;
//      stage1_line_flag_y = 0;
//      stage2_line_flag_y = 0;
//      stage4_line_flag_y = 0;
//      stage4_line_flag_x = 0;
//      pole_flag = 0;
//      pre_pole_flag = 0;
//      pole_detect_flag = 0;
//      pole_reach_flag = 0;
//      pass_line_count[0] = 6;
//      check_point[1] = 0;
//      Servo1.command[0] = 1000;
//      finish_flag = 0;
//      change_state_flag = 0;
//    }
//
//    if(ps4_data.square || run_auto_flag){
//      if(stage == 0){
//        x_dst.acc_lim = 40;
//        y_dst.acc_lim = 40;
//        a_dst.acc_lim = 40;
//        x_dst.deadzone = 25;
//        y_dst.deadzone = 25;
//        a_dst.deadzone = 10;
//        x_dst.speed_lim = 1500;
//        y_dst.speed_lim = 1500;
//        a_dst.speed_lim = 1500;
//        x_dst.destination = blue_path1[0][0];
//        y_dst.destination = 0;
//        a_dst.destination = 0;
//        auto_x = 0;
//        auto_y = 0;
//      }else if(stage == 1){
//        x_dst.acc_lim = 40;
//        y_dst.acc_lim = 40;
//        a_dst.acc_lim = 40;
//        x_dst.deadzone = 20;
//        y_dst.deadzone = 20;
//        a_dst.deadzone = 20;
//        line_dst_x.acc_lim = 40;
//        line_dst_a.acc_lim = 40;
//        line_dst_x.deadzone = 20;
//        line_dst_a.deadzone = 20;
//        x_dst.speed_lim = 800;
//        a_dst.speed_lim = 400;
//        line_dst_x.speed_lim = 1000;
//        line_dst_a.speed_lim = 500;
//        linex_control.kp = 7;
//        linex_control.ki = 5;
//        linex_control.kd = 1;
//        linea_control.kp = 6;
//
//        if(y < blue_path1[1][1] - 600){
//          y_dst.speed_lim = 700;
//        }else if(y < blue_path1[4][1]){
//          y_dst.speed_lim = 800;
//        }else if(pass_line_count[0] < 6){
//          y_dst.speed_lim = 1200;
//        }else{
//          y_dst.speed_lim = 500;
//        }
//
//        if(pass_line_count[0] < 7){
//          y_dst.destination = blue_path1[7][1] + 1000;
//        }else{
//          y_dst.destination = blue_path1[7][1];
//        }
//
//        int angle_offset = 0;
//        if(1){
//          x_dst.destination = x;        //loop back for zero input(for safe)
//          a_dst.destination = tRotation;
//          line_dst_x.destination = 0;
//          line_dst_a.destination = 0;
//        }else{
//          line_dst_x.destination = line_x_d;
//          line_dst_a.destination = line_a_d;
//          if(y < blue_path1[1][1]){               //0-1
//            a_dst.destination = 0 + angle_offset;
//            x_dst.destination = blue_path1[1][0];
//            auto_x = 0;
//          }else if(y < blue_path1[2][1]){         //1-2
//            a_dst.destination = 150 + angle_offset;
//            x_dst.destination = (y - blue_path1[1][1])/tanf(5*PI/12) + blue_path1[1][0];
//            auto_x = auto_y/tanf(7*PI/12);
//          }else if(y < blue_path1[3][1]){         //2-3
//            a_dst.destination = 300 + angle_offset;
//            x_dst.destination = (y - blue_path1[2][1])/tanf(PI/3) + blue_path1[2][0];
//            auto_x = auto_y/tanf(2*PI/3);
//          }else if(y < blue_path1[4][1]){         //3-4
//            a_dst.destination = 450 + angle_offset;
//            x_dst.destination = (y - blue_path1[3][1])/tanf(PI/4) + blue_path1[3][0];
//            auto_x = auto_y/tanf(3*PI/4);
//          }else if(y < blue_path1[5][1]){         //4-5
//            a_dst.destination = 300 + angle_offset;
//            x_dst.destination = (y - blue_path1[4][1])/tanf(PI/3) + blue_path1[4][0];
//            auto_x = auto_y/tanf(2*PI/3);
//          }else if(y < blue_path1[6][1]){         //5-6
//            a_dst.destination = 150 + angle_offset;
//            x_dst.destination = (y - blue_path1[5][1])/tanf(5*PI/12)+ blue_path1[5][0];
//            auto_x = auto_y/tanf(5*PI/12);
//          }else if(y < blue_path1[7][1]){         //6-7
//            a_dst.destination = 0;
//            x_dst.destination =  blue_path1[7][0];
//            auto_x = 0;
//          }else if(y < blue_path1[8][1]){         //7-8
//            a_dst.destination = 0;
//            x_dst.destination =  blue_path1[8][0];
//            auto_x = 0;
//          }
//        }
//      }else if(stage == 2){
//        x_dst.acc_lim = 40;
//        y_dst.acc_lim = 40;
//        a_dst.acc_lim = 40;
//        y_control.kp = 2.5;
//        y_control.kd = 1;
//        x_control.kp = 2.5;
//        x_control.kd = 1;
//
//        if(!stage2_line_flag_y){
//          y_dst.destination = blue_path1[11][1] + 500;
//          if(y < blue_path1[11][1] - 150){
//            y_dst.speed_lim = 1800;
//          }else{
//            y_dst.speed_lim = 500;
//          }
//        }else{
//          y_dst.destination = blue_path1[11][1];
//          y_dst.speed_lim = 800;
//        }
//
//        if(y < blue_path1[9][1]){         //8-9
//          x_dst.speed_lim = 1200;
//          a_dst.speed_lim = 500;
//          x_dst.deadzone = 1;
//          y_dst.deadzone = 1;
//          a_dst.deadzone = 1;
//          a_dst.destination = 1350;
//          x_dst.destination = blue_path1[9][0];
//          hysteresis_flag = 1;
//        }else if(y < blue_path1[10][1] - 200 && hysteresis_flag){     //9-10
//          x_dst.speed_lim = 1400;
//          a_dst.speed_lim = 400;
//          x_dst.deadzone = 1;
//          y_dst.deadzone = 1;
//          a_dst.deadzone = 1;
//          a_dst.destination = 1800;
//          x_dst.destination = blue_path1[10][0];
//        }else{  //10-11
//          hysteresis_flag = 0;
//          y_dst.speed_lim = 800;
//          a_dst.speed_lim = 500;
//          a_dst.destination = 1800;
//          y_dst.destination = blue_path1[11][1];
//
//          if(!pole_reach_flag){
//            x_dst.deadzone = 1;
//            y_dst.deadzone = 1;
//            a_dst.deadzone = 1;
//          }else{
//            x_dst.deadzone = 10;
//            y_dst.deadzone = 10;
//            a_dst.deadzone = 10;
//          }
//
//          if(x_position_ready != 2 || !pole_detect_flag){
//            x_dst.destination = blue_path1[11][0] - 1000;
//            if(x < blue_path1[11][0] + 700){
//              x_dst.speed_lim = 400;
//            }else{
//              x_dst.speed_lim = 1500;
//            }
//          }else{
//            x_dst.destination = blue_path1[11][0] + 30;
//            x_dst.speed_lim = 200;
//          }
//        }
//      }else if(stage == 3){
//        x_dst.acc_lim = 40;
//        y_dst.acc_lim = 40;
//        a_dst.acc_lim = 40;
//        x_dst.speed_lim = 1500;
//        y_dst.speed_lim = 1000;
//        a_dst.speed_lim = 1000;
//        y_dst.destination = blue_path1[11][1];
//        x_dst.destination = blue_path1[11][0] + 30;
//        a_dst.destination = 1800;
//
//        if(!pole_reach_flag){
//          x_dst.deadzone = 1;
//          y_dst.deadzone = 1;
//          a_dst.deadzone = 1;
//        }else{
//          x_dst.deadzone = 10;
//          y_dst.deadzone = 10;
//          a_dst.deadzone = 10;
//        }
//
//        if(x_position_ready != 2 || !pole_detect_flag){
//          x_dst.destination = blue_path1[11][0] - 1000;
//          if(x < blue_path1[11][0] + 700){
//            x_dst.speed_lim = 400;
//          }else{
//            x_dst.speed_lim = 1500;
//          }
//        }else{
//          x_dst.destination = blue_path1[11][0] + 30;
//          x_dst.speed_lim = 200;
//        }
//      }else if(stage == 4){
//        x_dst.acc_lim = 30;
//        y_dst.acc_lim = 30;
//        a_dst.acc_lim = 30;
//        x_dst.deadzone = 15;
//        y_dst.deadzone = 15;
//        a_dst.deadzone = 15;
//        x_dst.speed_lim = 500;
//        a_dst.speed_lim = 800;
//        a_dst.destination = 0;
//
//        if(stage4_line_flag_y){
//          y_dst.destination = blue_path1[7][1];
//          if(stage4_line_flag_x){
//            x_dst.destination = blue_path1[7][0] - 700;
//          }else{
//            x_dst.destination = x - 300;
//          }
//        }else{
//          x_dst.destination = 0;
//          y_dst.destination = blue_path1[7][1] + 500;
//          if(y < blue_path1[7][1] - 800){
//            y_dst.speed_lim = 1800;
//          }else{
//            y_dst.speed_lim = 500;
//          }
//        }
//      }
//    }else if(auto_state == -1){
//      x_dst.destination = x;        //loop back for zero input(for safe)
//      y_dst.destination = y;
//      a_dst.destination = tRotation;
//      x_dst.deadzone = 10;
//      y_dst.deadzone = 10;
//      a_dst.deadzone = 10;
//      line_dst_x.destination = line_x_d;
//      line_dst_a.destination = line_a_d;
//      a_control.kp = 3;
//      x_control.kp = 2;
//      x_control.kd = 0;
//      y_control.kp = 2;
//      y_control.kd = 0;
//      r_control.kp = 3;
//      a_control.pre_input = 0;
//      a_control.pre_output = 0;
//      x_control.pre_input = 0;
//      x_control.pre_output = 0;
//      y_control.pre_input = 0;
//      y_control.pre_output = 0;
//      r_control.pre_input = 0;
//      r_control.pre_output = 0;
//      linex_control.pre_input = 0;
//      linex_control.pre_output = 0;
//      linea_control.i_term = 0;
//      linea_control.pre_input = 0;
//      linea_control.pre_output = 0;
//      auto_y = 0;
//      auto_x = 0;
//    }
//
///////////////////////////////movement input selection
//    int output_x = PIDcontroller(&x_dst, x, &x_control,0);
//    int output_y = PIDcontroller(&y_dst, y, &y_control,0);
//    int output_a = PIDcontroller(&a_dst, tRotation, &a_control,1);
//
//    if(stage == 1 && (ps4_data.square || run_auto_flag)){
//      output_line_x = PIDcontroller(&line_dst_x, line_x_d, &linex_control, 0);
//      output_line_a = PIDcontroller(&line_dst_a, line_a_d, &linea_control, 1);
//    }else{
//      output_line_x = 0;
//      output_line_a = 0;
//    }
//
//    x_com =  (auto_y+output_y)*sinf(HeadingAngle) + (auto_x+output_x)*cosf(HeadingAngle);
//    y_com =  (auto_y+output_y)*cosf(HeadingAngle) - (auto_x+output_x)*sinf(HeadingAngle);
//
//    M[0].SetPoint =  x_com + y_com + output_a + xSpeed + ySpeed + turn + output_line_x + output_line_a;
//    M[1].SetPoint = -x_com + y_com + output_a - xSpeed + ySpeed + turn - output_line_x + output_line_a;
//    M[2].SetPoint = -x_com - y_com + output_a - xSpeed - ySpeed + turn - output_line_x + output_line_a;
//    M[3].SetPoint =  x_com - y_com + output_a + xSpeed - ySpeed + turn + output_line_x + output_line_a;

}





