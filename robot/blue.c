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

#define TURN_LIMIT 500

int red_path1[12][2] = { {2819, 0}, {2819, 1089}, {2534, 2151}, {2118, 2872}, {
    1340, 3650},
                        {496, 5113}, {211, 6175}, {200, 6800}, {200, 7387}, {
                            200, 10017},
                        {2800, 13000},           //{-3165,13000},
                        {5450, 13000}};
int debug_display[10] = {};
////////////////////////////////////////////////////////////////////
//Encoder raw input
int E0 = 0, E1 = 0, E2 = 0, E3 = 0;
int x = 0, y = 0, tRotation = 0;
//tRotation is accumulative, HeadingAngle is Normalized
float xf = 0, yf = 0, tRotationf = 0, HeadingAngle = 0;
//all floating angles are in radian
long sum = 0; //for encoder tuning
void UpdatePosition(void) {
  debug_display[1] = M[4].Board.EncoderCounter;
  debug_display[2] = pmotor[0].current_pos;
  debug_display[3] = ADCValue[0];
  debug_display[4] = M[1].Board.ADCValue;
  debug_display[5] = (int)ARTracker_status.d;
  debug_display[6] = ARTracker_status.anglex;
  debug_display[7] = ARTracker_status.angley;
  debug_display[8] = ARTracker_status.distance;
  debug_display[9] = ARTracker_status.pitch;
  //This part is manual added to display the debug values
  /*
   debug_display[0] = M[5].Board.EncoderCounter;
   debug_display[1] = M[6].Board.EncoderCounter;
   debug_display[2] = M[7].Board.EncoderCounter;
   debug_display[3] = pmotor[1].abs_pos;
   debug_display[4] = pmotor[2].abs_pos;
   debug_display[5]= pmotor[3].abs_pos;
   debug_display[6]= M[5].SetPoint;
   debug_display[7]= M[6].SetPoint;
   debug_display[8]= M[7].SetPoint;
   debug_display[9]=0;
   */

  if (encoder1_2.Alive == 0) {
    encoder1_2.delta_count[0] = 0;
    encoder1_2.delta_count[1] = 0;
  }

  if (encoder3_4.Alive == 0) {
    encoder3_4.delta_count[0] = 0;
    encoder3_4.delta_count[1] = 0;
  }

  E0 = (int16_t)encoder1_2.delta_count[0];
  E1 = (int16_t)encoder1_2.delta_count[1];
  E2 = (int16_t)encoder3_4.delta_count[0];
  //E3 = (int16_t)encoder3_4.delta_count[1];

  float encoderT = ((float)(-E0 - E1)) / 2.0 / 6996.9287; //6696.9287
  tRotationf += encoderT; //in scale of RADIAN
  HeadingAngle = fNormalizeAngle(tRotationf); //fNormalizeAngle set -PI<=angle<=PI

  tRotation = NormalizeAngle((int)(tRotationf / PI * 1800));
  float encoderX = -0.5 * (-E0 + E1) * cosf(HeadingAngle)
      + E2 * sinf(HeadingAngle);
  float encoderY = -0.5 * (-E0 + E1) * sinf(HeadingAngle)
      - E2 * cosf(HeadingAngle);

  xf -= encoderX * 0.038705682; //1000/encoder Reading //0.038705682
  yf -= encoderY * 0.038705682; //0.038705682

  x = (int)xf + 268 * (1 - cosf(HeadingAngle));
  y = (int)yf - 268 * sinf(HeadingAngle);
  sum += E0 + E1;
}

void ClearPosition(void) {
  tRotationf = 0;
  xf = 0;
  yf = 0;
  sum = 0;
}

///////////////////////////////////////////////////////////////
bool base_lock = false;     //Flag of locking base
void UnlockBase(void) {
  motor_setIdle(&M[0]);
  motor_setIdle(&M[1]);
  motor_setIdle(&M[2]);
  motor_setIdle(&M[3]);
  base_lock = false;
}

//////////////////////////////////////////////////////////////
void LockBase(void) {
  motor_send_setting(&M[0]);
  motor_send_setting(&M[1]);
  motor_send_setting(&M[2]);
  motor_send_setting(&M[3]);
  base_lock = true;
}

/////////////////////////////////////////////////////////////
bool initialized = false;
int track_init = 3;
int clamp5_init = 2;
int clamp6_init = 2;
void Initialization(void) {
  initialized=true;
  /*
  //Vertical Track Initialization===========================================
  switch (track_init) {
  case 3:
    if (M[4].Board.ADCValue > 30000) {
      M[4].SetPoint = 600;
    }
    else {
      track_init--;
    }
    break;

  case 2:
    if (M[4].Board.ADCValue <= 30000) {
      M[4].SetPoint = -600;
    }
    else {
      pmotor[0].offset = M[4].Board.EncoderCounter - 175 * pmotor[0].scale;
      track_init--;
    }
    break;

  case 1:
    track_init--;
    break;
  default:
    run_p_mode(RUN, &pmotor[0], 100);
    break;
  }

  //Clamp[5] initialization=============================================
  switch (clamp5_init) {
  case 2:
    if (M[5].Board.ADCValue <= 512) {
      M[5].SetPoint = -1000;
    }
    else {
      clamp5_init--;
    }
    break;
  case 1:
    if (M[5].Board.ADCValue > 512) { //-16
      M[5].SetPoint = 300;
    }
    else {
      clamp5_init--;
      M[5].SetPoint = 0;
      pmotor[1].offset = M[5].Board.EncoderCounter - 14 * pmotor[1].scale;
    }
    break;
  default:
    //run_p_mode(RUN, &pmotor[1], -5);
    break;
  }

  //Clamp[6] initialization=============================================
  switch (clamp6_init) { //-14
  case 2:
    if (M[6].Board.ADCValue <= 512) {
      M[6].SetPoint = -1000;
    }
    else {
      clamp6_init--;
    }
    break;
  case 1:
    if (M[6].Board.ADCValue > 512) {
      M[6].SetPoint = 300;
    }
    else {
      clamp6_init--;
      M[6].SetPoint = 0;
      pmotor[2].offset = M[6].Board.EncoderCounter - 14 * pmotor[2].scale;
    }
    break;
  default:
    //run_p_mode(RUN, &pmotor[2], -5);
    break;
  }
  initialized = !(track_init || clamp5_init || clamp6_init);
  */
}
//////////////////////////////////////////////////////////////////////////
int xSpeed = 0, ySpeed = 0, turn = 0, push_length = 0;
void ManualControl() {
  //Get Input==================================
  ySpeed = -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y) - 128), 15);
  xSpeed = AddDeadZone((int)((uint16_t)(ps4_data.hat_left_x) - 128), 15);
  turn = -AddDeadZone((int)((uint16_t)(ps4_data.hat_right_x) - 128), 15);
  push_length = AddDeadZone(
      (int)(((int16_t)ps4_data.l2_trigger - ps4_data.r2_trigger)), 15);
  //ySpeedight = -AddDeadZone((int)((uint16_t)(ps4_data.hatight_y)-128), 15);
  //Set Scale========================================
  push_length *= 4;     //4.5

  if (xSpeed < 85 && xSpeed > -85) {
    xSpeed *= 10;
  }
  else {
    if (xSpeed > 0) {
      xSpeed = 22 * xSpeed - 1020;
    }
    else {
      xSpeed = 22 * xSpeed + 1020;
    }
  }
  if (ySpeed < 85 && ySpeed > -85) {
    ySpeed *= 10;
  }
  else {
    if (ySpeed > 0) {
      ySpeed = 22 * ySpeed - 1020;
    }
    else {
      ySpeed = 22 * ySpeed + 1020;
    }
  }

  if (turn < 85 && turn > -85) {
    turn *= 6;
  }
  else {
    if (turn > 0) {
      turn = 11 * turn - 424;
    }
    else {
      turn = 11 * turn + 424;
    }
  }

  if (turn > TURN_LIMIT)
    turn = TURN_LIMIT;
  else if (turn < -TURN_LIMIT)
    turn = -TURN_LIMIT;

}
/////////////////////////////////////////////////////////////////
int v_track_h = 500;
#define track_y_offset 600
#define FanServoOffset 230
void Fan(bool turnon) {
  if (y < 1000 - track_y_offset) {     //1st Platform
    v_track_h = 230;
    if (turnon)
      Servo1.command[0] = 420;
  }
  else if (y < 2062.52 - track_y_offset) {     //1st Slope
    v_track_h = (y + track_y_offset - 1000) / 1062.52 * 200 + 230;
    if (turnon)
      Servo1.command[0] = 400;
  }
  else if (y < 3014.52 - track_y_offset) {     //2nd Platform
    if (turnon)
      Servo1.command[0] = 370;
  }
  else if (y < 3792.34 - track_y_offset) {     //2nd Slope
    v_track_h = (y + track_y_offset - 3014.52) / 777.82 * 200 + 430;
    if (turnon)
      Servo1.command[0] = 400;
  }
  else if (y < 5013.94 - track_y_offset) {     //3rd Platform
    if (turnon)
      Servo1.command[0] = 390;
  }
  else if (y < 6076.46 - track_y_offset) {     //3rd Slope
    v_track_h = (y + track_y_offset - 5013.94) / 1062.52 * 15 + 630;
    if (turnon)
      Servo1.command[0] = 370;
  }
  else if (y < 6831.75 - track_y_offset) {     //River
    v_track_h = 670;
    if (turnon)
      Servo1.command[0] = 200;
  }
  else if (y <= 10000) {
    v_track_h = 700;
  }
  else if (y > 10000) {
    v_track_h = 200;
  }
}

int fancount = 0;
int lastX = 0;
void TargetFan() {

  if (ARTracker_status.d == 'D') {
    lastX = ARTracker_status.anglex;
  }

  /*
   if (ARTracker_status.d == 'D') {
   v_track_h += ARTracker_status.angley / 500;
   }
   */

  if (fancount == 13) {
    fancount = 0;
    Servo1.command[7] += (int)(lastX / 90.0);
    lastX = 0;
  }
  else {
    fancount++;
  }

  return;
}

void Car_go_dir(int field_ang, int velo) {
  int car_go_ang = NormalizeAngle(tRotation - field_ang);
  float car_go_angf = (float)car_go_ang / 1800.0 * PI;
  ySpeed = velo * cosf(car_go_angf);
  xSpeed = velo * sinf(car_go_angf);
}

/////////////////////////////////////////////////////////////////
# define LINE_NARROW 20
# define LINE_THICK 55
bool LS0, LS1, LS2, LS3;
bool LockX(bool onturn) {
  int Lerror = 0;
  if (onturn) {
    //Rotation correction

    if (LineSensor[3].Position[1] > LINE_NARROW
        && LineSensor[3].Position[1] < LINE_THICK
        && LineSensor[2].Position[1] > LINE_NARROW
        && LineSensor[2].Position[1] < LINE_THICK) {
      Lerror += LineSensor[3].Position[0] - (220 - LineSensor[2].Position[0]);
      Lerror /= 2;
    }

    if (Lerror < -100 || Lerror > 100)
      turn -= Lerror * 40;
    else
      turn -= Lerror * 10;
  }

  //Translation correction
  int Xerror = 0;
  if (LineSensor[3].Position[3] > LINE_NARROW
      && LineSensor[3].Position[3] < LINE_THICK) {

  }
  if (LineSensor[3].Position[1] > LINE_NARROW
      && LineSensor[3].Position[1] < LINE_THICK
      && LineSensor[3].Position[3] < 0) {
    Xerror += (220 - LineSensor[3].Position[0]) - 110;
  }
  if (LineSensor[2].Position[1] > LINE_NARROW
      && LineSensor[2].Position[1] < LINE_THICK
      && LineSensor[2].Position[3] < 0) {
    if (Xerror == 0) {
      Xerror += LineSensor[2].Position[0] - 110;
    }
    else {
      Xerror += LineSensor[2].Position[0] - 110;
      Xerror /= 2;
    }
  }
  if (!LS2 || !LS3)
    return false;
  if (Xerror < -2 || Xerror > 2) {
    xSpeed += Xerror * 6;
    return false;
  }
  else {
    xSpeed += Xerror * 2;
    if (Lerror > 2 || Lerror < -2)
      return false;
  }

  return true;

}

bool LockY(bool onturn) {
  int Aerror = 0;
  if (onturn) {
    //Rotation Correction

    if (LineSensor[0].Position[1] > LINE_NARROW
        && LineSensor[0].Position[1] < LINE_THICK
        && LineSensor[1].Position[1] > LINE_NARROW
        && LineSensor[1].Position[1] < LINE_THICK) {
      Aerror += LineSensor[1].Position[0] - LineSensor[0].Position[0];

    }

    if (Aerror < -60 || Aerror > 60)
      turn -= Aerror * 100;
    else
      turn -= Aerror * 10;
  }
  //Translation Correction
  int Yerror = 0;
  if (LineSensor[0].Position[1] > LINE_NARROW
      && LineSensor[0].Position[1] < LINE_THICK
      && LineSensor[0].Position[3] < 0) {
    Yerror += (220 - LineSensor[0].Position[0]) - 110;
  }
  if (LineSensor[1].Position[1] > LINE_NARROW
      && LineSensor[1].Position[1] < LINE_THICK
      && LineSensor[1].Position[3] < 0) {
    if (Yerror == 0) {
      Yerror += (220 - LineSensor[1].Position[0]) - 110;
    }
    else {
      Yerror += (220 - LineSensor[1].Position[0]) - 110;
      Yerror /= 2;
    }
  }

  if (!LS0 || !LS1)
    return false;

  if (Yerror < -15 || Yerror > 15) {
    ySpeed += Yerror * 10;
    return false;
  }
  else {
    ySpeed += Yerror * 6;
    if (Aerror > 3 || Aerror < -3) {
      return false;
    }
  }
  return true;
}

void LockA(int angle) {
  int deltaA = NormalizeAngle(tRotation - angle);
  if (deltaA > -50 && deltaA < 50)
    return;
  else if (deltaA > -150 && deltaA < 150)
    turn += (deltaA < 0) ? 150 : -150;
  else {
    if (deltaA > 1200)
      turn += -1200;
    else if (deltaA < -1200)
      turn += 1200;
    else
      turn += -deltaA;
  }

}

/*
 void InnerCircle(){
 ManualControl();
 xSpeed = turn = 0;
 int front = 0, back = 0;
 if (LineSensor[3].Position[0] > 0) {
 front = LineSensor[3].Position[0];
 }
 if (LineSensor[2].Position[0] > 0) {
 back = 220 - LineSensor[2].Position[0];
 }
 turn = (front > back) ? back - front : back - front;
 if (front == 0 && back == 0) {
 xSpeed = -500;
 }
 else {
 xSpeed = front + back;
 }
 turn *= 10;
 ySpeed *= 2;
 }
 */

//////////////////////////////////////////////////////////////////////
//Acceleration limit
int prevA = 0, prevX = 0, prevY = 0, prevZ = 0, prevF = 0;
void Acc_lim() {
  if (xSpeed > prevX + 40) {
    xSpeed = prevX + 40;
  }
  else if (xSpeed < prevX - 40) {
    xSpeed = prevX - 40;
  }

  if (ySpeed > prevY + 40) {
    ySpeed = prevY + 40;
  }
  else if (ySpeed < prevY - 40) {
    ySpeed = prevY - 40;
  }

  if (turn > prevA + 40) {
    turn = prevA + 40;
  }
  else if (turn < prevA - 40) {
    turn = prevA - 40;
  }

  if (M[7].SetPoint != 0) {
    if (M[7].SetPoint > prevZ + 18) {
      M[7].SetPoint = prevZ + 18;
    }
    else if (M[7].SetPoint < prevZ - 18) {
      M[7].SetPoint = prevZ - 18;
    }
  }

  if (Servo1.command[0] != 200) {
    if (Servo1.command[0] > prevF + 3) {
      Servo1.command[0] = prevF + 3;
    }
    else if (Servo1.command[0] < prevF - 3) {
      Servo1.command[0] = prevF - 3;
    }
  }
  prevF = Servo1.command[0];
  prevX = xSpeed;
  prevY = ySpeed;
  prevA = turn;
  prevZ = M[7].SetPoint;
}

//Maximum/Minimum Limit
void MaxMin_lim() {
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
int step = -1, substep = 0;
;
bool upPressed = false, downPressed = false, l1Pressed = false,
    trianglePressed = false;
bool clamp_lock = false;
bool crossingline = false;
bool step_initialize = false;
bool self_drive = false;
bool finalY = false;
int testdummy = 0, timer = 0, maxdist = 0, count = 0;
GAIN z_control = {};
TARGET z_dst = {};
int reset_timer = 0;
int lasttimecross = 0;
void RunPath(void) {
  timer++;
  xSpeed = ySpeed = turn = 0;
  LS0 = (LineSensor[0].Position[1] > LINE_NARROW
      && LineSensor[0].Position[1] < LINE_THICK);
  LS1 = (LineSensor[1].Position[1] > LINE_NARROW
      && LineSensor[1].Position[1] < LINE_THICK);
  LS2 = (LineSensor[2].Position[1] > LINE_NARROW
      && LineSensor[2].Position[1] < LINE_THICK);
  LS3 = (LineSensor[3].Position[1] > LINE_NARROW
      && LineSensor[3].Position[1] < LINE_THICK);
  UpdatePosition();
  M[7].SetPoint = 0;
  update_pmotor();

  //Initialize before run
  if (!initialized) {
    Initialization();
    return;
  }

  if (!ps4_data.square && !ps4_data.triangle && !self_drive) {
    ManualControl();
    M[5].SetPoint = 0;
    M[6].SetPoint = 0;
  }
  else {
    //Run Path
    switch (step) {
    /////////////////////////////////////////////////////////////////////////
    case -3: //Test Function Mode
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 700;
        v_track_h = 200; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405;
        step_initialize = true;
      }
//      TargetFan();
//      ManualControl();
//      v_track_h += -AddDeadZone((int)((uint16_t)(ps4_data.hat_left_y) - 128),
//                                  15);
//
//      ySpeed = 0;
//      xSpeed = 0;
      LockX(true);
      break;
      /////////////////////////////////////////////////////////////////////////
    case -2: //Tuning Mode
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        v_track_h = 700; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        step_initialize = true;
      }

      testdummy = Servo1.command[6];
      if (ps4_data.dpad_code == DPAD_RIGHT) {
        //up
        testdummy++;
      }
      else if (ps4_data.dpad_code == DPAD_LEFT) {
        //down
        testdummy--;
      }
      //TargetFan();
      /*
       bool clamp5 = run_p_mode(RUN, &pmotor[1], testdummy);
       bool clamp6 = run_p_mode(RUN, &pmotor[2], testdummy);
       if(clamp5 && clamp6){
       M[5].SetPoint=0;
       M[6].SetPoint=0;
       }
       */
      Servo1.command[6] = testdummy;
      debug_display[0] = testdummy;
      break;
      /////////////////////////////////////////////////////////////////////////
    case -1: // Set Zero Before Start
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        Servo1.command[0] = 200;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        v_track_h = 500; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 570; //412-296=180 deg
        step_initialize = true;
        break;
      }
      if ((timer > 100) || (LockX(true) & LockY(true))) {
        xf = yf = 0.0;
        tRotationf = 0.0;
        step_initialize = false;
        self_drive = false;
        UnlockBase();
        step++;
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 0: // Go Get Eco
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        Servo1.command[0] = 200;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        //v_track_h = 100; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 550; //412-296=180 deg
        step_initialize = true;
        break;
      }

      if ((LS2 || LS3) && x < -2000) {
        Servo1.command[0] = 390;
        if (LS2 && LS3) {
          if (LockX(true) & LockY(false)) {
            tRotationf = 0.0;
            xf = -2819.0;
            yf = 0.0;
            crossingline = true;
            step++;
            step_initialize = false;
          }
        }
        else if (LS3) {
          LockY(false);
          turn = 50;
          xSpeed = -50;
        }
        else if (LS2) {
          LockY(false);
          turn = -50;
          xSpeed = -50;
        }
      }
      else {
        if (self_drive) {
          if (x - (-2900) < 500) {
            xSpeed = -200;
          }
          else {
            xSpeed = -(x + 2900);
          }
        }
        else {
          ManualControl();
          ySpeed = 0;
        }
        LockY(true);
      }

      break;
      /////////////////////////////////////////////////////////////////////////
    case 1: //First Platform
      /////////////////////////////////////////////////////////////////////////
    case 2: // First Slope
      /////////////////////////////////////////////////////////////////////////
    case 3: // Second Platform
      /////////////////////////////////////////////////////////////////////////
    case 4: //Second Slope
      /////////////////////////////////////////////////////////////////////////
    case 5: //Third Platform
      /////////////////////////////////////////////////////////////////////////
    case 6: //Third Slope
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        //v_track_h = 100; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 570; //412-296=180 deg
        step_initialize = true;
        break;
      }

      if (self_drive) {
        ySpeed = 800;
      }
      else {
        ManualControl();
        xSpeed = 0;
      }
      LockX(true);
      TargetFan_r();
      if (ARTracker_status.d == 'D') {
        if (ARTracker_status.angley > 30)
          v_track_h++;
        else if (ARTracker_status.angley < -30)
          v_track_h--;
      }

      if (step == 1 && timer < 150) {
        ySpeed = 0;
        Servo1.command[7] = 550;
      }
      else {
        Servo1.command[7] = 570;
      }
      if (step == 2) {
        Servo1.command[7] = 590;
      }
      if (step == 4) {
        Servo1.command[7] = 550;
      }
      /*
       if (step==1 || step>4){
       Servo1.command[7] = 550;
       }
       else{
       Servo1.command[7] = 570;
       }*/
      if (crossingline && !LS0)
        crossingline = false;
      else if (!crossingline && LS0 && timer > 50) {
        //Servo1.command[0]=200;
        crossingline = true;
        step++;
        step_initialize = false;
      }
      ySpeed /= 1.3;
      xSpeed /= 1.3;
      turn /= 1.3;
      /*
       if (ARTracker_status.distance )Servo1.command[0] = 400 + (100 - ARTracker_status.distance);
       if (Servo1.command[0]>1500)Servo1.command[0]=1500;
       if (Servo1.command[0]<1000)Servo1.command[0]=1000;
       */
      break;
      /////////////////////////////////////////////////////////////////////////
    case 7: //Approach River
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 700; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }

      if (self_drive) {
        ySpeed = 500;
      }
      else {
        ManualControl();
        xSpeed = 0;
      }
      LockX(true);

      Servo1.command[0] = 200;

      if (crossingline && !LS0)
        crossingline = false;

      if (!crossingline && LS0) {
        xSpeed = ySpeed = turn = 0;
        LineSensor[3].Position[0] = LineSensor[2].Position[0];
        if (LockY(true) && LockX(false)) {
          tRotationf = 0.0;
          xf = -200.0;
          yf = 6750.0;
          crossingline = true;
          step++;
          step_initialize = false;
        }
        if (LineSensor[0].Position[0] < 100)
          ySpeed = 300;
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 8: // Blow River
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        //Servo1.command[0] = 340;
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        maxdist = 0;
        break;
      }

      if (self_drive) {
        xSpeed = ySpeed = turn = 0;
      }
      else {
        ManualControl();
        xSpeed = 0;
      }
      if (reset_timer > 0)
        reset_timer--;
      else {
        TargetFan();
        if (ARTracker_status.d == 'D' && ARTracker_status.distance > maxdist) {
          maxdist = ARTracker_status.distance;
        }

        if (Servo1.command[0] <= 340) {
          Servo1.command[0]++;
        }
        else if (ARTracker_status.d == 'D' && ARTracker_status.distance > 100) {
          int windspd = 340 + (ARTracker_status.distance - 100) * 90.0 / 400.0;
          if (windspd > Servo1.command[0]) {
            Servo1.command[0] = windspd;
          }
          if (ARTracker_status.angley > 0) {
            Servo1.command[0] = 200;
            step_initialize = false;
            reset_timer = 700;
          }
        }

        if (maxdist > 430) {
          if (ARTracker_status.d != 'D') {
            count++;
          }
          else {
            count = 0;
            if (ARTracker_status.pitch > 53 || ARTracker_status.pitch < -53) {
              count = 100;
            }
            if (ARTracker_status.distance > 430) {
              count++;
            }
          }
          if (count > 10) {
            step++;
            step_initialize = false;
          }
        }
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 9: //Approach Pole(Grab Line)
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 200; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        finalY = false;
        break;
      }
      if (self_drive) {

      }
      else {

      }
      //find last vert path

      if (LineSensor[0].Position[2] >= 0) {
        LineSensor[0].Position[0] = LineSensor[0].Position[2];
        LineSensor[0].Position[1] = LineSensor[0].Position[3];
      }
      if (LineSensor[1].Position[2] >= 0) {
        LineSensor[1].Position[0] = LineSensor[1].Position[2];
        LineSensor[1].Position[1] = LineSensor[1].Position[3];
      }
      {
        //Find angle
        int tx = -4600; //6025;
        int ty = 12800; //13000;     //6484
        int d2x = (x - tx);
        int d2y = (ty - y);
        float angle = atan(-(d2x / 2.0) / (d2y * 2.0)) * 1800 / PI;
        angle = NormalizeAngle(angle);
        //find dist
        int dist = Euclidean(x, y, tx, ty);
        //dist = d2y + 1000;

        if (d2y > 4500) {
          Car_go_dir(0, 2000);
          turn = 300;
        }
        else if (d2y > 2000) {
          Car_go_dir(0, 2000);
          LockA(-1800);
        }
        else if (!LS0 && !LS1) {
          Car_go_dir(450, d2y + 600);
          LockA(-1800);
        }
        else if (LineSensor[0].Position[0] > 130
            || LineSensor[1].Position[0] > 130) {
          Car_go_dir(450 + (450.0 * (220 - LineSensor[1].Position[0]) / 110.0),
                     300);
          LockA(-1800);
        }
        else {
          xSpeed = ySpeed = turn = 0;
          step++;
          step_initialize = false;
        }
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 10: //Approach Pole(Straight Line)
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 200; //(160-730mm)
        Servo1.command[1] = 397; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        finalY = false;
        break;
      }
      if (self_drive) {

      }
      else {

      }
      if (LineSensor[0].Position[2] >= 0) {
        LineSensor[0].Position[0] = LineSensor[0].Position[2];
        LineSensor[0].Position[1] = LineSensor[0].Position[3];
      }
      if (LineSensor[1].Position[2] >= 0) {
        LineSensor[1].Position[0] = LineSensor[1].Position[2];
        LineSensor[1].Position[1] = LineSensor[1].Position[3];
      }
      {
        //Find angle
        int tx = -4600; //6025;
        int ty = 12800; //13000;     //6484
        int d2x = (x - tx);
        int d2y = (ty - y);
        float angle = atan(-(d2x / 2.0) / (d2y * 2.0)) * 1800 / PI;
        angle = NormalizeAngle(angle);
        //find dist
        int dist = Euclidean(x, y, tx, ty);
        //dist = d2y + 1000;

        if (d2x > 1600) {
          xSpeed = 1500;
          LockY(true);

        }
        else if (d2x > 500) {
          xSpeed = d2x;
          LockY(true);
        }
        else {
          LockY(true);
          xSpeed = 300;
          if (LS2 && LS3) {
            int right = (220 - LineSensor[3].Position[0]) - 140;
            int left = (LineSensor[2].Position[0]) - 140;
            if (right > left - 5)
              turn = -5;
            else if (left > right - 5)
              turn = 5;
            else
              turn = 0;
            if (left < 10 && right < 10 && M[2].Board.ADCValue < 30000) {
              xSpeed = ySpeed = turn = 0;
              step++;
              step_initialize = false;
            }
          }
        }
      }

      break;
      /////////////////////////////////////////////////////////////////////////
    case 11:
      //Grab Propeller
      if (!step_initialize) {
        if (M[1].Board.ADCValue > 30000) {
          UnlockBase();
          clamp_lock = true;
          step++;
          step_initialize = false;
          break;
        }
        else {
          timer = 0;
          count = 0;
          substep = 0;
          LockBase();
          xSpeed = 0;
          ySpeed = 0;
          turn = 0;
          M[5].SetPoint = 0;
          M[6].SetPoint = 0;
          Servo1.command[0] = 200;
          //v_track_h = 150; //(160-730mm)
          Servo1.command[1] = 303; //Red Arm Angle(close=280;right=307;open=450)
          Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
          Servo1.command[7] = 405; //412-296=180 deg
          step_initialize = true;
          break;
        }
      }
      if (self_drive) {

      }
      else {

      }
      if (M[1].Board.ADCValue > 30000) {
        count++;
        if (Servo1.command[1] < 397)
          Servo1.command[1]++;
        UnlockBase();
        clamp_lock = true;
        if (count > 200) {
          M[5].SetPoint = 0;
          M[6].SetPoint = 0;
          step++;
          step_initialize = false;
        }
      }
      else {
        run_p_mode(RUN, &pmotor[1], 70);
        run_p_mode(RUN, &pmotor[2], 70);
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 12:
      //Climb Pole
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 397; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 466; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }
      if (self_drive) {
        xSpeed = ySpeed = turn = 0;
        z_control.kp = 1.5;
        z_control.ki = 0.5;
        z_dst.acc_lim = 18;
        z_dst.deadzone = 5;
        z_dst.speed_lim = 1400;
        z_dst.destination = 720; //690;  //700
        int z_output = -PIDcontroller(&z_dst, (int)(ADCValue[0]), &z_control,
                                      0); //ADCValue[0] = ultrasound feedback (720 around snap)
        M[7].SetPoint = z_output;

      }
      else {
        xSpeed = ySpeed = turn = 0;
      }
      if (ps4_data.options || M[7].Board.ADCValue < 30000) {
        Servo1.command[1] = 472;
        M[7].SetPoint = 0;
        step++;
        step_initialize = false;
      }
      xSpeed = ySpeed = turn = 0;
      break;
      /////////////////////////////////////////////////////////////////////////
    case 13:
      //Finishing
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        UnlockBase();
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 472; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 466; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }
      xSpeed = ySpeed = turn = 0;
      if (Servo1.command[2] > 386)
        Servo1.command[2]--;
      if (timer > 50 && Servo1.command[1] > 373)
        Servo1.command[1]--;

      if (self_drive) {
        xSpeed = ySpeed = turn = 0;
        z_control.kp = 2;
        z_control.ki = 0.7;
        z_dst.acc_lim = 15;
        z_dst.deadzone = 5;
        z_dst.speed_lim = 600;
        z_dst.destination = 200; //690;  //700
        int z_output = -PIDcontroller(&z_dst, (int)(ADCValue[0]), &z_control,
                                      0);
        M[7].SetPoint = z_output;
      }
      else {
        xSpeed = ySpeed = turn = 0;
      }

      if (ADCValue[0] <= 200) {
        M[7].SetPoint = 0;
        step++;
        step_initialize = false;
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 14:
      //Finished
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;

        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        M[7].SetPoint = 0; ///////////////////////////////////////////////////////
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 466; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }
      if (self_drive) {
        xSpeed = ySpeed = turn = 0;
      }
      else {
        xSpeed = ySpeed = turn = 0;
      }
      xSpeed = ySpeed = turn = 0;
      self_drive = false;
      break;
      /////////////////////////////////////////////////////////////////////////
    case 20: // Set Zero Before Start
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        Servo1.command[0] = 200;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        v_track_h = 500; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }
      if ((LockX(true) & LockY(true))||timer>100) {
        xf = yf = 0.0;
        tRotationf = 0.0;
        step_initialize = false;
        self_drive = false;
        UnlockBase();
        step++;
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 21:
      //Retry: River
      xSpeed = ySpeed = turn = 0;
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        M[7].SetPoint = 0; ///////////////////////////////////////////////////////
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 445; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        break;
      }
      else {
        bool xarr = false, yarr = false;
        if (self_drive) {
          if (LineSensor[0].Position[0] < 0 || LineSensor[1].Position[0] < 0
              || y < 2000) {

            ySpeed = (6750 - y) * 1.0;
            if (ySpeed > 2000)
              ySpeed = 2000;
            else if (ySpeed < -2000)
              ySpeed = -2000;

            xSpeed = -(x + 200) * 3;
            LockA(0);
          }
          else if (LineSensor[2].Position[0] < 0
              || LineSensor[3].Position[0] < 0) {
            ySpeed = 0;
            LockY(true);
            xSpeed = -500;
          }
          else if (LockX(true)) {
            step = 7;
            tRotationf = 0.0;
            xf = -200.0;
            yf = 6750.0;
            crossingline = false;
            step_initialize = false;
          }
        }
        else {
          ManualControl();
          if (Euclidean(x, y, 195, 6750) < 100) {
            if (LockX(true) && LockY(true)) {
              step = 7;
              tRotationf = 0.0;
              xf = -200.0;
              yf = 6750.0;
              crossingline = false;
              step_initialize = false;
            }
          }
        }

      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 22: //Retry: Manual Get Propeller - Set Zero Before Start
      if (!step_initialize) {
        clamp_lock = false;
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        M[7].SetPoint = 0; ///////////////////////////////////////////////////////
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 373; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        //debug_display[8]++;
        step_initialize = true;
        break;
      }
      if ((LockX(true) & LockY(true))||timer>100) {
        xf = yf = 0.0;
        tRotationf = PI;
        step_initialize = false;
        self_drive = false;
        UnlockBase();
        step++;
      }
      break;
    case 23:
      //Retry: Manual Get Propeller
      xSpeed = ySpeed = turn = 0;
      if (!step_initialize) {
        clamp_lock = false;
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        M[7].SetPoint = 0; ///////////////////////////////////////////////////////
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 397; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 386; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        //debug_display[8]++;
        step_initialize = true;
        break;
      }
      if (x > -1000) {
        xSpeed = 1000;
        LockY(true);
      }
      else {
        step = 10;
        step_initialize = false;
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    case 24:
      //Retry: Manual Climb Pole
      xSpeed = ySpeed = turn = 0;
      if (!step_initialize) {
        timer = 0;
        count = 0;
        substep = 0;
        xSpeed = 0;
        ySpeed = 0;
        turn = 0;
        M[5].SetPoint = 0;
        M[6].SetPoint = 0;
        Servo1.command[0] = 200;
        //v_track_h = 150; //(160-730mm)
        Servo1.command[1] = 397; //Red Arm Angle(close=280;right=307;open=450)
        Servo1.command[2] = 466; //Red Arm Length(Far=333;Near=418)
        Servo1.command[7] = 405; //412-296=180 deg
        step_initialize = true;
        clamp_lock = false;
        self_drive = false;
        break;
      }
      if (self_drive) {
        clamp_lock = true;
        count++;
        if (count > 100) {
          step = 12;
          step_initialize = false;
        }
      }
      break;
      /////////////////////////////////////////////////////////////////////////
    default:
      //Stop Everything, Waiting for retry
      timer = 0;
      count = 0;
      substep = 0;
      step_initialize = false;
      UnlockBase();
      v_track_h = 700;
      M[0].SetPoint = M[1].SetPoint = M[2].SetPoint = M[3].SetPoint =
          M[4].SetPoint = M[5].SetPoint = M[6].SetPoint = M[7].SetPoint = 0;
      Servo1.command[0] = 200;
      Servo1.command[1] = 445;
      Servo1.command[2] = 386;
      Servo1.command[3] = 400;
      Servo1.command[4] = 308;
      Servo1.command[5] = 415;
      Servo1.command[6] = 400;
      Servo1.command[7] = 405;
      break;
    }
  }

//Periodic Check or update to values=====================================
//Stage Select
  if (ps4_data.dpad_code == DPAD_UP && downPressed == false) {
    step++;
    step_initialize = false;
    downPressed = true;
  }
  downPressed = (ps4_data.dpad_code == DPAD_UP);

  if (ps4_data.dpad_code == DPAD_DOWN && upPressed == false) {
    step--;
    step_initialize = false;
    upPressed = true;
  }
  upPressed = (ps4_data.dpad_code == DPAD_DOWN);

  if (ps4_data.l1 && l1Pressed == false) {
    clamp_lock = !clamp_lock;
    l1Pressed = true;
  }
  l1Pressed = (ps4_data.l1);

  if (ps4_data.triangle && trianglePressed == false) {
    self_drive = !self_drive;
    trianglePressed = true;
  }
  trianglePressed = (ps4_data.triangle);

//Lock or release Base
  if (Button_edge[6]) {
    self_drive = false;
    if (base_lock)
      UnlockBase();
  }
  if (Button_edge[0]) {
    self_drive = true;
    if (!base_lock)
      LockBase();
  }

  if (Button_edge[1]) {
    step = -1;
    step_initialize = false;
    self_drive = true;
    if (!base_lock)
      LockBase();
  }
  if (Button_edge[2]) {
    step = 20;
    step_initialize = false;
    self_drive = true;
    if (!base_lock)
      LockBase();
  }
  if (Button_edge[3]) {
    step = 22;
    step_initialize = false;
    self_drive = true;
    if (!base_lock)
      LockBase();
  }
  if (Button_edge[4]) {
    step = 24;
    step_initialize = false;
    self_drive = true;
    if (!base_lock)
      LockBase();
  }
  if (Button_edge[5]) {
    self_drive = false;
    if (!base_lock)
      LockBase();
  }

  int push_length = AddDeadZone(
      (int)(((int16_t)ps4_data.l2_trigger - ps4_data.r2_trigger)), 15);
  push_length *= 4;
  if (M[7].SetPoint == 0)
    M[7].SetPoint = push_length;
  if (M[7].Board.ADCValue < 30000 && push_length < 0) {
    M[7].SetPoint = 0;
  }

  if (clamp_lock) {
    bool clamp5 = run_p_mode(RUN, &pmotor[1], 87);
    bool clamp6 = run_p_mode(RUN, &pmotor[2], 85);
    if ((clamp5 && clamp6)) {
      M[5].SetPoint = 0;
      M[6].SetPoint = 0;
    }
  }
  else if (step != 11) {
    bool clamp5 = run_p_mode(RUN, &pmotor[1], 10);
    bool clamp6 = run_p_mode(RUN, &pmotor[2], 10);
    if ((clamp5 && clamp6)) {
      M[5].SetPoint = 0;
      M[6].SetPoint = 0;
    }
  }

  if (timer % 100 == 0) {
    if (base_lock)
      LockBase();
    else
      UnlockBase();
  }
  //self_drive = ps4_data.triangle;

  /*
   Servo1.command[7] -= ARTracker_status.angle/16;
   if (Servo1.command[7]< 1430-213) Servo1.command[7]=1430-213;
   else if (Servo1.command[7]> 1430+213) Servo1.command[7]=1430+213;
   */

//CheckLimits
  /*
   if (Servo1.command[7] < 1430 - 213)
   Servo1.command[7] = 1430 - 213;
   else if (Servo1.command[7] > 1430 + 213)
   Servo1.command[7] = 1430 + 213;
   */
  switch (step) {
  case 1:
    if (v_track_h < 200)
      v_track_h = 200;
    Servo1.command[0] = 420;
    break;
  case 2:
    if (v_track_h < 300)
      v_track_h = 300;
    Servo1.command[0] = 410;
    Servo1.command[7] = 552;
    break;
  case 3:
    if (v_track_h < 400)
      v_track_h = 400;
    Servo1.command[0] = 400;
    Servo1.command[7] = 570;
    break;
  case 4:
    if (v_track_h < 500)
      v_track_h = 500;
    Servo1.command[0] = 390;
    Servo1.command[7] = 570;
    break;
  case 5:
    if (v_track_h < 600)
      v_track_h = 600;
    Servo1.command[0] = 420;
    Servo1.command[7] = 534;
    break;
  case 6:
    if (v_track_h < 700)
      v_track_h = 700;
    Servo1.command[0] = 400;
    Servo1.command[7] = 534;
    break;
  default:
    Fan(false);
    break;
  }
  run_p_mode(RUN, &pmotor[0], v_track_h);
//Move Motor=============================================================
  Acc_lim();
  MaxMin_lim();
  M[0].SetPoint = xSpeed + ySpeed + turn;
  M[1].SetPoint = -xSpeed + ySpeed + turn;
  M[2].SetPoint = -xSpeed - ySpeed + turn;
  M[3].SetPoint = xSpeed - ySpeed + turn;
//  M[0].SetPoint /=4;
//  M[1].SetPoint /=4;
//  M[2].SetPoint /=4;
//  M[3].SetPoint /=4;
//  debug_display[3] = LockY(false);
//  debug_display[4] = LockX(false);
//  debug_display[5] = base_lock;
//  debug_display[6] = self_drive;
//  debug_display[9] = step_initialize;
}

