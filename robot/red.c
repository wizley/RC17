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
#include "redblue.h"
#include "ARTracker.h"
#include "boardio.h"

#define TURN_LIMIT_R 500

int debug_display_r[10] = {};
////////////////////////////////////////////////////////////////////
//Encoder raw input
////////////////////////////////////////////////////////////////////
int E0_r = 0, E1_r = 0, E2_r = 0, E3_r = 0;
int x_r = 0, y_r = 0, tRotation_r = 0;
//tRotation_r is accumulative, HeadingAngle_r is Normalized
float xf_r = 0, yf_r = 0, tRotationf_r = 0, HeadingAngle_r = 0;
//all floating angles are in radian
long sum_r = 0; //for encoder tuning
void UpdatePosition_r(void) {
  debug_display_r[1] = M[0].Board.ADCValue;
  debug_display_r[2] = M[0].Board.EncoderCounter;
  debug_display_r[3] = M[0].SetPoint;//ADCValue[0];
  debug_display_r[4] = pmotor[0].abs_pos;
  debug_display_r[5] = pmotor[0].current_pos;
  debug_display_r[6] = ButtonDown[0];
  //debug_display_r[7] = ;
  //debug_display_r[8] = ARTracker_status.distance;
  debug_display_r[9] = ARTracker_status.pitch;
  //This part is manual added to display the debug values
  /*
   debug_display_r[0] = M[5].Board.EncoderCounter;
   debug_display_r[1] = M[6].Board.EncoderCounter;
   debug_display_r[2] = M[7].Board.EncoderCounter;
   debug_display_r[3] = pmotor[1].abs_pos;
   debug_display_r[4] = pmotor[2].abs_pos;
   debug_display_r[5]= pmotor[3].abs_pos;
   debug_display_r[6]= M[5].SetPoint;
   debug_display_r[7]= M[6].SetPoint;
   debug_display_r[8]= M[7].SetPoint;
   debug_display_r[9]=0;
   */
  update_pmotor();
  if (encoder1_2.Alive == 0) {
    encoder1_2.delta_count[0] = 0;
    encoder1_2.delta_count[1] = 0;
  }

  if (encoder3_4.Alive == 0) {
    encoder3_4.delta_count[0] = 0;
    encoder3_4.delta_count[1] = 0;
  }

  E0_r = (int16_t)encoder1_2.delta_count[0];
  E1_r = (int16_t)encoder1_2.delta_count[1];
  E2_r = (int16_t)encoder3_4.delta_count[0];
  //E3_r = (int16_t)encoder3_4.delta_count[1];

  float encoderT = ((float)(-E0_r - E1_r)) / 2.0 / 6996.9287; //6696.9287
  tRotationf_r += encoderT; //in scale of RADIAN
  HeadingAngle_r = fNormalizeAngle(tRotationf_r); //fNormalizeAngle set -PI<=angle<=PI

  tRotation_r = NormalizeAngle((int)(tRotationf_r / PI * 1800));
  float encoderX = -0.5 * (-E0_r + E1_r) * cosf(HeadingAngle_r)
      + E2_r * sinf(HeadingAngle_r);
  float encoderY = -0.5 * (-E0_r + E1_r) * sinf(HeadingAngle_r)
      - E2_r * cosf(HeadingAngle_r);

  xf_r += encoderX * 0.038705682; //1000/encoder Reading //0.038705682
  yf_r += encoderY * 0.038705682; //0.038705682

  x_r = (int)xf_r + 268 * (1 - cosf(HeadingAngle_r));
  y_r = (int)yf_r - 268 * sinf(HeadingAngle_r);
  sum_r += E0_r + E1_r;
}

void ClearPosition_r(void) {
  tRotationf_r = 0;
  xf_r = 0;
  yf_r = 0;
  sum_r = 0;
}

///////////////////////////////////////////////////////////////
bool base_lock_r = false;     //Flag of locking base
void UnlockBase_r(void) {
  motor_setIdle(&M[0]);
  motor_setIdle(&M[1]);
  motor_setIdle(&M[2]);
  motor_setIdle(&M[3]);
  base_lock_r = false;
}

//////////////////////////////////////////////////////////////
void LockBase_r(void) {
  ;
  motor_send_setting(&M[0]);
  motor_send_setting(&M[1]);
  motor_send_setting(&M[2]);
  motor_send_setting(&M[3]);
  base_lock_r = true;
}

/////////////////////////////////////////////////////////////
bool initialized_r = false;
int track_init_r = 3;
int clamp5_init_r = 2;
int clamp6_init_r = 2;
void Initialization_r(void) {
  initialized_r=true;
  /*
  //Vertical Track Initialization===========================================
  switch (track_init_r) {
  case 3:
    if (M[4].Board.ADCValue > 30000) {
      M[4].SetPoint = 600;
    }
    else {
      track_init_r--;
    }
    break;

  case 2:
    if (M[4].Board.ADCValue <= 30000) {
      M[4].SetPoint = -600;
    }
    else {
      pmotor[0].offset = M[4].Board.EncoderCounter - 175 * pmotor[0].scale;
      track_init_r--;
    }
    break;

  case 1:
    track_init_r--;
    break;
  default:
    run_p_mode(RUN, &pmotor[0], 100);
    break;
  }

  //Clamp[5] initialization=============================================
  switch (clamp5_init_r) {
  case 2:
    if (M[5].Board.ADCValue <= 512) {
      M[5].SetPoint = -1000;
    }
    else {
      clamp5_init_r--;
    }
    break;
  case 1:
    if (M[5].Board.ADCValue > 512) { //-16
      M[5].SetPoint = 300;
    }
    else {
      clamp5_init_r--;
      M[5].SetPoint = 0;
      pmotor[1].offset = M[5].Board.EncoderCounter - 14 * pmotor[1].scale;
    }
    break;
  default:
    //run_p_mode(RUN, &pmotor[1], -5);
    break;
  }

  //Clamp[6] initialization=============================================
  switch (clamp6_init_r) { //-14
  case 2:
    if (M[6].Board.ADCValue <= 512) {
      M[6].SetPoint = -1000;
    }
    else {
      clamp6_init_r--;
    }
    break;
  case 1:
    if (M[6].Board.ADCValue > 512) {
      M[6].SetPoint = 300;
    }
    else {
      clamp6_init_r--;
      M[6].SetPoint = 0;
      pmotor[2].offset = M[6].Board.EncoderCounter - 14 * pmotor[2].scale;
    }
    break;
  default:
    //run_p_mode(RUN, &pmotor[2], -5);
    break;
  }
  initialized_r = !(track_init_r || clamp5_init_r || clamp6_init_r);
  */
}
//////////////////////////////////////////////////////////////////////////
int xSpeed_r = 0, ySpeed_r = 0, turn_r = 0, push_length_r = 0;
void ManualControl_r() {
  //Get Input==================================
  ySpeed_r = -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y) - 128), 15);
  xSpeed_r = AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), 15);
  turn_r = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x) - 128), 15);
  push_length_r = AddDeadZone(
      (int)(((int16_t)ps4_data.l2_trigger - ps4_data.r2_trigger)), 15);
  //ySpeed_right_r = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_y)-128), 15);
  //Set Scale========================================
  push_length_r *= 4;     //4.5

  if (xSpeed_r < 85 && xSpeed_r > -85) {
    xSpeed_r *= 10;
  }
  else {
    if (xSpeed_r > 0) {
      xSpeed_r = 22 * xSpeed_r - 1020;
    }
    else {
      xSpeed_r = 22 * xSpeed_r + 1020;
    }
  }
  if (ySpeed_r < 85 && ySpeed_r > -85) {
    ySpeed_r *= 10;
  }
  else {
    if (ySpeed_r > 0) {
      ySpeed_r = 22 * ySpeed_r - 1020;
    }
    else {
      ySpeed_r = 22 * ySpeed_r + 1020;
    }
  }

  if (turn_r < 85 && turn_r > -85) {
    turn_r *= 6;
  }
  else {
    if (turn_r > 0) {
      turn_r = 11 * turn_r - 424;
    }
    else {
      turn_r = 11 * turn_r + 424;
    }
  }

  if (turn_r > TURN_LIMIT_R)
    turn_r = TURN_LIMIT_R;
  else if (turn_r < -TURN_LIMIT_R)
    turn_r = -TURN_LIMIT_R;

}
/////////////////////////////////////////////////////////////////
int v_track_h_r = 500;
#define track_y_offset 600
#define FanServoOffset 230
void Fan_r(bool turnon) {
  if (y_r < 1000 - track_y_offset) {     //1st Platform
    v_track_h_r = 230;
    if (turnon)
      Servo1.command[0] = 420;
  }
  else if (y_r < 2062.52 - track_y_offset) {     //1st Slope
    v_track_h_r = (y_r + track_y_offset - 1000) / 1062.52 * 200 + 230;
    if (turnon)
      Servo1.command[0] = 400;
  }
  else if (y_r < 3014.52 - track_y_offset) {     //2nd Platform
    if (turnon)
      Servo1.command[0] = 370;
  }
  else if (y_r < 3792.34 - track_y_offset) {     //2nd Slope
    v_track_h_r = (y_r + track_y_offset - 3014.52) / 777.82 * 200 + 430;
    if (turnon)
      Servo1.command[0] = 400;
  }
  else if (y_r < 5013.94 - track_y_offset) {     //3rd Platform
    if (turnon)
      Servo1.command[0] = 390;
  }
  else if (y_r < 6076.46 - track_y_offset) {     //3rd Slope
    v_track_h_r = (y_r + track_y_offset - 5013.94) / 1062.52 * 15 + 630;
    if (turnon)
      Servo1.command[0] = 370;
  }
  else if (y_r < 6831.75 - track_y_offset) {     //River
    v_track_h_r = 670;
    if (turnon)
      Servo1.command[0] = 200;
  }
  else if (y_r <= 10000) {
    v_track_h_r = 700;
  }
  else if (y_r > 10000) {
    v_track_h_r = 200;
  }
}

int fancount_r = 0;
int lastX_r = 0;
void TargetFan_r() {

  if (ARTracker_status.d == 'D') {
    lastX_r = ARTracker_status.anglex;
  }

  /*
   if (ARTracker_status.d == 'D') {
   v_track_h_r += ARTracker_status.angley / 500;
   }
   */

  if (fancount_r == 13) {
    fancount_r = 0;
    Servo1.command[7] += (int)(lastX_r / 90.0);
    lastX_r = 0;
  }
  else {
    fancount_r++;
  }

  return;
}

void Car_go_dir_r(int field_ang, int velo) {
  int car_go_ang = NormalizeAngle(tRotation_r - field_ang);
  float car_go_angf = (float)car_go_ang / 1800.0 * PI;
  ySpeed_r = velo * cosf(car_go_angf);
  xSpeed_r = velo * sinf(car_go_angf);
}

/////////////////////////////////////////////////////////////////
# define LINE_NARROW_R 20
# define LINE_THICK_R 55
bool LS0_r, LS1_r, LS2_r, LS3_r;
bool LockX_r(bool onturn) {
  int Lerror = 0;
  if (onturn) {
    //Rotation correction

    if (LineSensor[3].Position[1] > LINE_NARROW_R
        && LineSensor[3].Position[1] < LINE_THICK_R
        && LineSensor[2].Position[1] > LINE_NARROW_R
        && LineSensor[2].Position[1] < LINE_THICK_R) {
      Lerror += LineSensor[3].Position[0] - (220 - LineSensor[2].Position[0]);
      Lerror /= 2;
    }

    if (Lerror < -100 || Lerror > 100)
      turn_r -= Lerror * 40;
    else
      turn_r -= Lerror * 10;
  }

  //Translation correction
  int Xerror = 0;
  if (LineSensor[3].Position[3] > LINE_NARROW_R
      && LineSensor[3].Position[3] < LINE_THICK_R) {

  }
  if (LineSensor[3].Position[1] > LINE_NARROW_R
      && LineSensor[3].Position[1] < LINE_THICK_R
      && LineSensor[3].Position[3] < 0) {
    Xerror += (220 - LineSensor[3].Position[0]) - 110;
  }
  if (LineSensor[2].Position[1] > LINE_NARROW_R
      && LineSensor[2].Position[1] < LINE_THICK_R
      && LineSensor[2].Position[3] < 0) {
    if (Xerror == 0) {
      Xerror += LineSensor[2].Position[0] - 110;
    }
    else {
      Xerror += LineSensor[2].Position[0] - 110;
      Xerror /= 2;
    }
  }
  if (!LS2_r || !LS3_r)
    return false;
  if (Xerror < -2 || Xerror > 2) {
    xSpeed_r -= Xerror * 6;
    return false;
  }
  else {
    xSpeed_r -= Xerror * 2;
    if (Lerror > 2 || Lerror < -2)
      return false;
  }

  return true;

}

bool LockY_r(bool onturn) {
  int Aerror = 0;
  if (onturn) {
    //Rotation Correction

    if (LineSensor[0].Position[1] > LINE_NARROW_R
        && LineSensor[0].Position[1] < LINE_THICK_R
        && LineSensor[1].Position[1] > LINE_NARROW_R
        && LineSensor[1].Position[1] < LINE_THICK_R) {
      Aerror += LineSensor[1].Position[0] - LineSensor[0].Position[0];

    }

    if (Aerror < -60 || Aerror > 60)
      turn_r -= Aerror * 100;
    else
      turn_r -= Aerror * 10;
  }
  //Translation Correction
  int Yerror = 0;
  if (LineSensor[0].Position[1] > LINE_NARROW_R
      && LineSensor[0].Position[1] < LINE_THICK_R
      && LineSensor[0].Position[3] < 0) {
    Yerror += (220 - LineSensor[0].Position[0]) - 110;
  }
  if (LineSensor[1].Position[1] > LINE_NARROW_R
      && LineSensor[1].Position[1] < LINE_THICK_R
      && LineSensor[1].Position[3] < 0) {
    if (Yerror == 0) {
      Yerror += (220 - LineSensor[1].Position[0]) - 110;
    }
    else {
      Yerror += (220 - LineSensor[1].Position[0]) - 110;
      Yerror /= 2;
    }
  }

  if (!LS0_r || !LS1_r)
    return false;

  if (Yerror < -15 || Yerror > 15) {
    ySpeed_r -= Yerror * 10;
    return false;
  }
  else {
    ySpeed_r -= Yerror * 6;
    if (Aerror > 3 || Aerror < -3) {
      return false;
    }
  }
  return true;
}

void LockA_r(int angle) {
  int deltaA = NormalizeAngle(tRotation_r - angle);
  if (deltaA > -50 && deltaA < 50)
    return;
  else if (deltaA > -150 && deltaA < 150)
    turn_r += (deltaA < 0) ? 150 : -150;
  else {
    if (deltaA > 1200)
      turn_r += -1200;
    else if (deltaA < -1200)
      turn_r += 1200;
    else
      turn_r += -deltaA;
  }

}

/*
 void InnerCircle(){
 ManualControl_r();
 xSpeed_r = turn_r = 0;
 int front = 0, back = 0;
 if (LineSensor[3].Position[0] > 0) {
 front = LineSensor[3].Position[0];
 }
 if (LineSensor[2].Position[0] > 0) {
 back = 220 - LineSensor[2].Position[0];
 }
 turn_r = (front > back) ? back - front : back - front;
 if (front == 0 && back == 0) {
 xSpeed_r = -500;
 }
 else {
 xSpeed_r = front + back;
 }
 turn_r *= 10;
 ySpeed_r *= 2;
 }
 */

//////////////////////////////////////////////////////////////////////
//Acceleration limit
int prevA_r = 0, prevX_r = 0, prevY_r = 0, prevZ_r = 0, prevF_r = 0;
void Acc_lim_r() {
  if (xSpeed_r > prevX_r + 40) {
    xSpeed_r = prevX_r + 40;
  }
  else if (xSpeed_r < prevX_r - 40) {
    xSpeed_r = prevX_r - 40;
  }

  if (ySpeed_r > prevY_r + 40) {
    ySpeed_r = prevY_r + 40;
  }
  else if (ySpeed_r < prevY_r - 40) {
    ySpeed_r = prevY_r - 40;
  }

  if (turn_r > prevA_r + 40) {
    turn_r = prevA_r + 40;
  }
  else if (turn_r < prevA_r - 40) {
    turn_r = prevA_r - 40;
  }

  if (M[7].SetPoint != 0) {
    if (M[7].SetPoint > prevZ_r + 18) {
      M[7].SetPoint = prevZ_r + 18;
    }
    else if (M[7].SetPoint < prevZ_r - 18) {
      M[7].SetPoint = prevZ_r - 18;
    }
  }

  if (Servo1.command[0] != 200) {
    if (Servo1.command[0] > prevF_r + 3) {
      Servo1.command[0] = prevF_r + 3;
    }
    else if (Servo1.command[0] < prevF_r - 3) {
      Servo1.command[0] = prevF_r - 3;
    }
  }
  prevF_r = Servo1.command[0];
  prevX_r = xSpeed_r;
  prevY_r = ySpeed_r;
  prevA_r = turn_r;
  prevZ_r = M[7].SetPoint;
}

//Maximum/Minimum Limit
void MaxMin_lim_r() {
  if (Servo1.command[0] > 450) {
    Servo1.command[0] = 450;
  }
  else if (Servo1.command[0] < 200) {
    Servo1.command[0] = 200;
  }
  if (Servo1.command[7] > 598) {
    Servo1.command[7] = 598;
  }
  else if (Servo1.command[7] < 212) {
    Servo1.command[7] = 212;
  }
  for (int i = 1; i < 8; i++) {
    if (Servo1.command[i] > 600) {
      Servo1.command[i] = 600;
    }
    else if (Servo1.command[i] < 200) {
      Servo1.command[i] = 200;
    }
  }
}
//////////////////////////////////////////////////////////////////////
int step_r = -1, substep_r = 0;
;
bool upPressed_r = false, downPressed_r = false, l1Pressed_r = false,
    trianglePressed_r = false;
bool clamp_lock_r = false;
bool crossingline_r = false;
bool step_initialize_r = false;
bool self_drive_r = false;
bool finalY_r = false;
int testdummy_r = 0, timer_r = 0, maxdist_r = 0, count_r = 0;
GAIN z_control_r = {};
TARGET z_dst_r = {};
int reset_timer_r = 0;
int lasttimecross_r = 0;
void RunPath_r(void) {

UpdatePosition_r();

m[0].speed_ref_krpm=3.000;
m[1].speed_ref_krpm=3.000;
debug_display_r[0]=m[0].speed_krpm*1000;
debug_display_r[1]=m[0].status.voltage_V*1000;
debug_display_r[2]=m[0].status.current_A*1000;
debug_display_r[3]=m[1].speed_krpm*1000;
debug_display_r[4]=m[1].status.voltage_V*1000;
debug_display_r[5]=m[1].status.current_A*1000;
//Pneumatic Board
/*
if (pmotor[0].abs_pos <000){
  AirBoard.states = 0x0000;
  if (debug_display_r[7] == 0) debug_display_r[7] = M[0].Feedback;
  Servo1.command[1] = 1350;
}
else{
  AirBoard.states = 0x0001;
  debug_display_r[7] = 0;
  Servo1.command[1] = 2070;
}
*/


}

