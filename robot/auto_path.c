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

#define BLUE  //right
//#define RED     //left

#define TURN_LIMIT 500

int E0,E1,E2,E3;
int base_lock = 1;
float AvgVoltage;
float tRotationf,xf,yf;
int x,y,tRotation;
float HeadingAngle = 0;
int xSpeed, ySpeed, zSpeed, turn;
int pre_xSpeed, pre_ySpeed, pre_turn;
int xSpeed_r, ySpeed_r;
int auto_x, auto_y;
int orientation;
int centerFlag = 0;
int lfCenter, rtCenter;
int x_com,y_com;
float temp,dydx,rad;
int stage = 0;
int servo_time = 0;

TARGET x_dst = {0},y_dst = {0},a_dst = {0},r_dst = {0},z_dst = {0};
GAIN a_control = {0};
GAIN x_control = {0};
GAIN y_control = {0};
GAIN r_control = {0};
GAIN z_control = {0};

int blue_path[12][2] =
{
   {0,0},
   {0,1154},
   {265,2213},
   {676,2971},
   {1468,3720},
   {2278,5176},
   {2583,6250},
   {2583,6827},
   {2583,7387},
   {2583,10017},
   {-346,12946},
   {-2808,12946}
};

int red_path[12][2] =
{
   {0,0},
   {0,1154},
   {-265,2213},
   {-676,2971},
   {-1468,3720},
   {-2278,5176},
   {-2583,6250},
   {-2583,6827},
   {-2583,7387},
   {-2583,10017},
   {346,12946},
   {2808,12946}
};

int track_init0 = 0;
int track_init1 = 0;
int track_init2 = 0;
uint16_t pre_adc = 0;

int push_length = 0;

int clamp_p = 0;
int clamp_c = 0;

int db_flag[6] = {0};
int bt_delay[6] = {0};
int tt_flag[6] = {0};
int waltz_mode = 0;

float v_track_h = 0;

int hysteresis_flag= 1;
int climb_flag = 0;

long sum = 0;
float line_anglef = 0;
int line_angle = 0;

void UpdatePosition(void) {
  if(encoder1_2.Alive == 0){
    encoder1_2.delta_count[0] = 0;
    encoder1_2.delta_count[1] = 0;
  }

  if(encoder3_4.Alive == 0){
    encoder3_4.delta_count[0] = 0;
    encoder3_4.delta_count[1] = 0;
  }

  E0 = (int16_t)encoder1_2.delta_count[0];
  E1 = (int16_t)encoder1_2.delta_count[1];
  E2 = (int16_t)encoder3_4.delta_count[0];
  E3 = (int16_t)encoder3_4.delta_count[1];

  float encoderT = ((float) (-E0 - E1)) / 2.0 / 7179.7978;
  tRotationf += encoderT; //in scale of RADIAN
  HeadingAngle = fNormalizeAngle(tRotationf); //fNormalizeAngle set -PI<=angle<=PI


//  if(LineSensor[0].Position[1] > 0 && LineSensor[0].Position[1] < 40 && LineSensor[1].Position[1] > 0 && LineSensor[1].Position[1] < 40){
//    int line_diff = (int)LineSensor[0].Position[0] - (int)LineSensor[1].Position[0];
//    line_anglef = atanf((float)line_diff/224.0);
//    line_angle = line_anglef / PI * 1800;
//
//    if(line_angle < 180 && line_angle > -180){
//      tRotationf = line_anglef;
////        if(tRotationf < PI/2 && tRotationf > -PI/2){
////          tRotationf = line_anglef;
////        }else if(tRotationf >= PI/2){
////          tRotationf = line_anglef + PI;
////        }else{
////          tRotationf = line_anglef - PI;
////        }
//    }
//  }

  tRotation = NormalizeAngle((int) (tRotationf / PI * 1800));

#ifdef BLUE
    float encoderX = 0.5*(-E0 +  E1)*cosf(HeadingAngle) - E2*sinf(HeadingAngle);
    float encoderY = 0.5*(-E0 +  E1)*sinf(HeadingAngle) + E2*cosf(HeadingAngle);
#endif

#ifdef RED
    float encoderX = -0.5*(-E0 +  E1)*cosf(HeadingAngle) + E2*sinf(HeadingAngle);
    float encoderY = -0.5*(-E0 +  E1)*sinf(HeadingAngle) - E2*cosf(HeadingAngle);
#endif

    xf += encoderX*0.038705682;
    x = (int) xf;
    yf += encoderY*0.038705682;
    y = (int) yf;
    sum += E0 + E1;
    if(ps4_data.cross){
      if(LineSensor[0].Position[1] > 0 && LineSensor[0].Position[1] < 40){
        int yl = -(LineSensor[0].Position[0] -55) + 350*tanf(tRotationf);
        if(yl - yf > 20 || yl - yf < -20){
          yf = yl;
        }
      }
    }

}
void ClearPosition(void){
  tRotationf = 0;
  xf = 0;
  yf = 0;
  sum = 0;
}

void RunPath(void) {
    /** angle PID constants */
//    a_constant.kp = 2;
//    a_constant.ki = 0.3;
//    a_constant.kd = 0;

  //    if(ButtonDown[8] == 1){
  //      palClearPad(GPIOC, GPIOC_LED_B);
  //    }
  //    else{
  //      palSetPad(GPIOC, GPIOC_LED_B);
  //    }

  if(ButtonDown[1] || ps4_data.r1){
    ClearPosition();
    a_control.pre_input = 0;
    a_control.pre_output = 0;
    x_control.pre_input = 0;
    x_control.pre_output = 0;
    y_control.pre_input = 0;
    y_control.pre_output = 0;
    r_control.pre_input = 0;
    r_control.pre_output = 0;
  }

  if(ButtonDown[2]){
#ifdef RED
    tRotationf = 0.2617993878;
#endif
#ifdef BLUE
    tRotationf = -0.2617993878;
#endif
    xf = 0;
    yf = 1218;
  }

  if(ButtonDown[3]){
    xf = 0;
    if(LineSensor[0].Position[1] > 0 && LineSensor[0].Position[1] < 40){
      yf = (LineSensor[0].Position[0] - 55)+tanf(tRotationf)*350;
    }
  }

#ifdef BLUE
    ySpeed = -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y)-128), 15);
    xSpeed = AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x)-128), 15);
#endif
#ifdef RED
    ySpeed =  AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y)-128), 15);
    xSpeed = -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x)-128), 15);
#endif

  //  zSpeed = -AddDeadZone((int)((uint16_t)(ps4_data.left_hat_x)-128), 15);
    turn =  -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x)-128), 15);
    push_length =  AddDeadZone((int)(((int16_t)ps4_data.l2-ps4_data.r2)), 15);

    ySpeed_r = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_y)-128), 15);
 //   xSpeed_r = AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x)-128), 15);

    push_length *= 8;     //4.5
    ySpeed_r *= 8;
    xSpeed_r *= 8;

    if(xSpeed < 85 && xSpeed > -85){
      xSpeed *=10;
    }else{
      if(xSpeed > 0){
        xSpeed = 22*xSpeed - 1020;
      }else{
        xSpeed = 22*xSpeed + 1020;
      }
    }
    if(ySpeed < 85 && ySpeed > -85){
      ySpeed *=10;
    }else{
      if(ySpeed > 0){
        ySpeed = 22*ySpeed - 1020;
      }else{
        ySpeed = 22*ySpeed + 1020;
      }
    }

    if(turn < 85 && turn > -85){
      turn *=6;
    }else{
      if(turn > 0){
        turn = 11*turn - 424;
      }else{
        turn = 11*turn + 424;
      }
    }

    if(turn > TURN_LIMIT)
      turn = TURN_LIMIT;
    else if(turn < -TURN_LIMIT)
      turn = -TURN_LIMIT;

    if(ps4_data.r3 == 0){
      turn = 0;
    }else{
      ySpeed_r = 0;
      xSpeed_r = 0;
    }

    UpdatePosition();
    //update_pmotor();

/////////////////////////////fan
    if(ps4_data.circle){
      if(bt_delay[4] < 200){
        bt_delay[4] ++;
      }
    }else{
      bt_delay[4] = 0;
    }
    if(bt_delay[4] >= 200){
      Servo1.command[3] += 3;

      if(Servo1.command[1] > 1500){
        Servo1.command[3] = 1500;
      }
    }
    if((ps4_data.circle && !db_flag[4]) || ButtonDown[0] == 1){
      Servo1.command[1] = 1000;
      Servo1.command[3] = 1000;
      bt_delay[4] = 0;
    }
    db_flag[4] = ps4_data.circle;

/////////////////////////////arm servo
    if(ps4_data.tpad_click && !db_flag[2]){
      tt_flag[2] ^= 1;
    }


    if(z_dst.reach_flag){
      Servo1.command[0] = 1600;
      if(servo_time < 60){
        Servo1.command[1] = 1200;
      }
      servo_time ++;
    }else{
      Servo1.command[0] = 1200;
      Servo1.command[1] = 1800;
      servo_time = 0;
    }

    db_flag[2] = ps4_data.tpad_click;

/////////////////////////////vertical track
    int track_y_offset = 500;
    if(stage == 1){
      if(yf < 1000 - track_y_offset){
        v_track_h = 100;
      }else if(yf < 2062.52 - track_y_offset){
        v_track_h = (yf-1000)/1062.52*200 + 100;
      }else if(yf < 3014.52 - track_y_offset){
      }else if(yf < 3792.34 - track_y_offset){
        v_track_h = (yf-3014.52)/777.82*200 + 300;
      }else if(yf < 5013.94 - track_y_offset){
      }else if(yf < 6076.46 - track_y_offset){
        v_track_h = (yf-5013.94)/1062.52*200 + 500;
      }else if(yf < 6831.75 - track_y_offset){
      }
    }else if(ps4_data.r1){
      v_track_h = 100;
    }else if(ps4_data.triangle){
      v_track_h = 550;
    }

    if(v_track_h > 550){
      v_track_h = 550;
    }
    if(v_track_h < 100){
      v_track_h = 100;
    }

    if(track_init0 == 0){
      if(M[4].Board.ADCValue <= 30000){
        M[4].SetPoint = -300;
      }else{
        pmotor[0].offset = M[4].Board.EncoderCounter;
        track_init0 = 1;
      }
    }else if(track_init0 == 1){
      if(!run_p_mode(RUN,&pmotor[0],100)){
        track_init0 = 2;
      }
    }else{
        run_p_mode(RUN,&pmotor[0],v_track_h);
    }

/////////////////////////////push motor   100 = 1 mm    p1 = p2 - 1183
    if(ps4_data.l1 || ButtonDown[6]){
      bt_delay[5]++;
    }else{
      bt_delay[5] = 0;
    }
    if(bt_delay[5] == 50){
      tt_flag[5] ^= 1;
    }

    if(track_init1 == 0){
      if(M[5].Board.ADCValue <= 512){
        M[5].SetPoint = -1000;
      }else{
        track_init1 = 1;
      }
    }else if(track_init1 == 1){
      if(M[5].Board.ADCValue > 512){
        M[5].SetPoint = 300;
      }else{
        track_init1 = 2;
        M[5].SetPoint = 0;
        pmotor[1].offset = M[5].Board.EncoderCounter;
      }
    }

    if(track_init2 == 0){
      if(M[6].Board.ADCValue <= 512){
        M[6].SetPoint = -800;
      }else{
        track_init2 = 1;
      }
    }else if(track_init2 == 1){
      if(M[6].Board.ADCValue > 512){
        M[6].SetPoint = 300;
      }else{
        track_init2 = 2;
        M[6].SetPoint = 0;
        pmotor[2].offset = M[6].Board.EncoderCounter;
      }
    }

    if(track_init1 == 2 && track_init2 == 2){
      if(tt_flag[5]){
        if(base_lock){
          motor_setIdle(&M[0]);
          motor_setIdle(&M[1]);
          motor_setIdle(&M[2]);
          motor_setIdle(&M[3]);
          base_lock = 0;
        }
        int flag1 = run_p_mode(RUN,&pmotor[1],5117);
        int flag2 = run_p_mode(RUN,&pmotor[2],6300);
        if (flag1 && flag2){
          climb_flag += 1;
          if(climb_flag > 100)
            climb_flag = 100;
        }
      }else{
        if(!base_lock){
          motor_send_setting(&M[0]);
          motor_send_setting(&M[1]);
          motor_send_setting(&M[2]);
          motor_send_setting(&M[3]);
          base_lock = 1;
        }
        run_p_mode(RUN,&pmotor[1],-1244);
        run_p_mode(RUN,&pmotor[2],-61);
        climb_flag = 0;
        z_dst.reach_flag = 0;
      }
    }

/////////////////////////////////////////////  climb motor
    if(climb_flag == 100 && !z_dst.reach_flag){
      z_control.kp = 1.5;
      z_control.ki = 0.7;
      z_dst.acc_lim = 15;
      z_dst.deadzone = 10;
      z_dst.speed_lim = 1200;
      z_dst.destination = 700;  //720
      int z_output = -PIDcontroller(&z_dst, (int)(ADCValue[0]), &z_control,0);
      M[7].SetPoint = z_output;
    }else{
      M[7].SetPoint = 0;
      z_control.pre_input = 0;
      z_control.pre_output = 0;
    }
    M[7].SetPoint += push_length;

/////////////////////////////path destinations calculation
    if(ps4_data.dpad_code == DPAD_UP){
      stage = 0;
    }else if(ps4_data.dpad_code == DPAD_LEFT){
      stage = 1;
    }else if(ps4_data.dpad_code == DPAD_RIGHT){
      stage = 2;
    }else if(ps4_data.dpad_code == DPAD_DOWN){
      stage = 3;
    }

    if(ButtonDown[5] || ps4_data.square){
      if(stage == 0){
        x_dst.acc_lim = 40;
        y_dst.acc_lim = 40;
        a_dst.acc_lim = 40;
        x_dst.speed_lim = 1500;
        y_dst.speed_lim = 1500;
        a_dst.speed_lim = 1500;
        x_dst.destination = -2857;
        y_dst.destination = 0;
        a_dst.destination = 0;
      }else if(stage == 1){
        x_dst.acc_lim = 40;
        y_dst.acc_lim = 40;
        a_dst.acc_lim = 40;
        x_dst.speed_lim = 800;
        y_dst.speed_lim = 300;
        a_dst.speed_lim = 800;
        y_dst.destination = blue_path[6][1];
        auto_y = 100;
        int angle_offset = 0;
        if(y < blue_path[1][1]){               //0-1
          a_dst.destination = 0 + angle_offset;
          x_dst.destination =  0;
          auto_x = 0;
        }else if(y < blue_path[2][1]){         //1-2
          a_dst.destination = - 150 + angle_offset;
          x_dst.destination = (y - blue_path[1][1])/tanf(5*PI/12);
          auto_x = auto_y/tanf(5*PI/12);
        }else if(y < blue_path[3][1]){         //2-3
          a_dst.destination = - 300 + angle_offset;
          x_dst.destination = (y - blue_path[2][1])/tanf(PI/3)+ blue_path[2][0];
          auto_x = auto_y/tanf(PI/3);
        }else if(y < blue_path[4][1]){         //3-4
          a_dst.destination = - 450 + angle_offset;
          x_dst.destination = (y - blue_path[3][1])/tanf(PI/4) + blue_path[3][0];
          auto_x = auto_y/tanf(PI/4);
        }else if(y < blue_path[5][1]){         //4-5
          a_dst.destination = - 300 + angle_offset;
          x_dst.destination = (y - blue_path[4][1])/tanf(PI/3) + blue_path[4][0];
          auto_x = auto_y/tanf(PI/3);
        }else if(y < blue_path[6][1]){         //5-6
          a_dst.destination = - 150 + angle_offset;
          x_dst.destination = (y - blue_path[5][1])/tanf(5*PI/12)+ blue_path[5][0];
          auto_x = auto_y/tanf(5*PI/12);
        }else if(y < blue_path[7][1]){         //6-7
          a_dst.destination = 0;
          x_dst.destination =  blue_path[6][0];
          auto_x = 0;
        }
      }else if(stage == 2){
        if(y < blue_path[8][1]){         //7-8
          a_dst.destination = 0;
          x_dst.destination =  blue_path[8][0];
          auto_x = 0;
        }else if(y < blue_path[9][1]){         //8-9
          a_dst.destination = 1800;
          x_dst.destination =  blue_path[9][0];
          auto_x = 0;
          hysteresis_flag = 1;
        }else if(y < blue_path[10][1] && hysteresis_flag){     //9-10
          a_dst.destination = 900 - 900*(y-blue_path[9][1])/((float)(blue_path[10][1]-blue_path[9][1]));
          x_dst.destination =  (y - blue_path[9][1])+ blue_path[9][0];;
          auto_x = - auto_y;
        }else{                                //10-11
          hysteresis_flag = 0;
          a_dst.destination = 1800;
          y_dst.destination = blue_path[11][1];
          x_dst.destination =  x;
          auto_x = -auto_y;
          auto_y = 0;
        }
      }else if(stage == 3){
        x_dst.acc_lim = 30;
        y_dst.acc_lim = 30;
        a_dst.acc_lim = 30;
        r_dst.acc_lim = 30;
        x_dst.speed_lim = 1000;
        y_dst.speed_lim = 1000;
        a_dst.speed_lim = 1000;
        r_dst.speed_lim = 1000;
        x_dst.destination = 0;
        y_dst.destination = 4400;
        a_dst.destination = 0;
        r_dst.destination = 4400;
      }else if(stage == 4){
        x_dst.acc_lim = 30;
        y_dst.acc_lim = 30;
        a_dst.acc_lim = 30;
        x_dst.speed_lim = 1200;
        y_dst.speed_lim = 1200;
        a_dst.speed_lim = 1200;
        x_dst.destination = -5450;
        y_dst.destination = 0;
        a_dst.destination = 0;
        x_dst.path_mode = 0;
        x_control.kp = 1.5;
        y_control.kp = 1.5;
      }
    }else{
      x_dst.destination = x;        //loop back for zero input(for safe)
      y_dst.destination = y;
      a_dst.destination = tRotation;
      a_control.kp = 3;
      x_control.kp = 2;
      y_control.kp = 2;
      r_control.kp = 3;
      a_control.pre_input = 0;
      a_control.pre_output = 0;
      x_control.pre_input = 0;
      x_control.pre_output = 0;
      y_control.pre_input = 0;
      y_control.pre_output = 0;
      r_control.pre_input = 0;
      r_control.pre_output = 0;
      auto_y = 0;
      auto_x = 0;
    }

/////////////////////////////movement input selection
    int output_x = PIDcontroller(&x_dst, x, &x_control,0);
    int output_y = PIDcontroller(&y_dst, y, &y_control,0);
    int output_a = PIDcontroller(&a_dst, tRotation, &a_control,1);
    x_com = -(auto_y+output_y)*sinf(HeadingAngle) + (auto_x+output_x)*cosf(HeadingAngle);
    y_com =  (auto_y+output_y)*cosf(HeadingAngle) + (auto_x+output_x)*sinf(HeadingAngle);

    M[0].SetPoint =  x_com + y_com + output_a + xSpeed + ySpeed + turn;
    M[1].SetPoint = -x_com + y_com + output_a - xSpeed + ySpeed + turn;
    M[2].SetPoint = -x_com - y_com + output_a - xSpeed - ySpeed + turn;
    M[3].SetPoint =  x_com - y_com + output_a + xSpeed - ySpeed + turn;

}





