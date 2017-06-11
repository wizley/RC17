/*
 * red.c
 *
 *  Created on: 2017-01-02
 *      Author: Lau
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
#include "airboard.h"
#include "distancesensor.h"
#include "red.h"
/*
 * for searching purpose
 * START_STATE
 * AUTO_STATE
 * MANUAL_STATE
 */

/*
 * common for both manual and auto
 */
void updateOldPS4Data (void) {
    savePS4Data();
	old_cross_state = ps4_data.cross;
	old_circle_state = ps4_data.circle;
	old_square_state = ps4_data.square;
	old_triangle_state = ps4_data.triangle;

	old_l1_state = ps4_data.l1;
	old_r1_state = ps4_data.r1;
	old_dpad_state = ps4_data.dpad_code;
}



void displayDebug (void) {
	debug_display[0] = LineSensor2016[0].status;//M[0].Board.ADCValue;
	debug_display[1] = LineSensor2016[0].position;//M[1].Board.ADCValue;
	debug_display[2] = LineSensor2016[0].position - 1911;
	debug_display[3] = M[3].Board.ADCValue;
	debug_display[4] = M[6].Board.ADCValue;//M[4].Feedback;	//left to mid
	debug_display[5] = ps4_data.tpad_click;//M[5].Feedback;	//right to mid
    debug_display[6] = ps4_data.tpad_info[0].finger[0].x;
	debug_display[7] = ps4_data.tpad_info[0].finger[0].y;
    debug_display[8] = ps4_data.tpad_info[0].finger[0].is_touching;
    debug_display[9] = targetPosition;
}

PositionStates blueStateSet[9]={
                                // {id      ,x      ,y      ,pitch  ,roll   ,shootspd   },
                                //   {        ,       ,       ,       ,       ,           },

                                   {0       , 500    ,0      ,0      ,0      ,0          }, //Start Zone
                                   {1       , -883   ,336    ,138    ,-80    ,905        },
                                   {2       , -1864  ,250    ,228    ,128    ,1050       },
                                   {3       , -4600  ,250    ,240    ,0      ,710        }, //Middle Near
                                   {4       , -4454  ,398    ,191    ,220    ,1105       }, //Middle Middle
                                   {5       , -2830  ,3453   ,184    ,183    ,1390       }, //Middle Far
                                   {6       , -5730  ,350    ,212    ,132    ,1040       },
                                   {7       , -7767  ,320    ,189    ,75     ,990        },
                                   {8       , -12500 ,0      ,108    ,5      ,0          }  //Loading Zone
                                };
bool init = false;
void RunPath (void) {
	UpdatePosition();

	if (!init){
	  /*
	  for(int i=0; i<9; i++){
	    blueStateSet[i]=redStateSet[i];
	  }
	  blueStateSet[0].x =500;
	  blueStateSet[1].x = (redStateSet[7].x - 12000);
	  blueStateSet[2].x = (redStateSet[6].x - 12000);
	    blueStateSet[3].x = (redStateSet[3].x - 12000);
	      blueStateSet[4].x = (redStateSet[4].x - 12000);
	      blueStateSet[5].x = (redStateSet[5].x - 12000);
	      blueStateSet[6].x = (redStateSet[2].x - 12000);
	      blueStateSet[7].x = (redStateSet[1].x - 12000);
      xDistanceOffset = blueStateSet[0].x;
      */
      airSetState(&airBoard, 2, 1);
      airSetState(&airBoard, 4, 1);
      airSetState(&airBoard, 0, 1);
      airSetState(&airBoard, 1, 1);
      if (!BSwitch && !PS4_ButtonPress(TRIANGLE)){
        M[6].SetPoint = -100;
      }
      else{
        M[6].SetPoint = 0;
        if (!ps4_data.circle){
          init = true;
        }
      }
	}
	else{
        if(ps4_data.l2_trigger>200) {
          targetPosition = 0; //reload position
          firstPush=false;
          leftDisc=false;
          rightDisc=false;
          runAuto(blueStateSet, targetPosition);

        }
        else if(ps4_data.r2_trigger>200) {
          targetPosition = 8;
          runAuto(blueStateSet, targetPosition);
        }
        else if(ps4_data.l1) {
	      runAuto(blueStateSet, targetPosition);
	    }
	    else{
	         //Manual Mode
	        //updateData ();
	        runManual();
	        //checkForAuto ();
	    }

	    if(PS4_ButtonPress(SQUARE)) {
	      blueStateSet[targetPosition].pitch = getPitch();
	      blueStateSet[targetPosition].roll = getRoll();
	      blueStateSet[targetPosition].x = distanceSum;
	      blueStateSet[targetPosition].y = yDistance;
	      blueStateSet[targetPosition].shootspd = (M[4].SetPoint+M[5].SetPoint)/2;
	    }
	//Update position according to pole aiming
	    if(PS4_ButtonPress(RIGHT) && !ps4_data.r1) {
	      //Shift the pole aiming at
	        //For Wizley
	       targetPosition = constrain(++targetPosition, 8, 0);
	    }

	    if(PS4_ButtonPress(LEFT) && !ps4_data.r1) {
	        //Shift the pole aiming at
	        //For Wizley
	        targetPosition = constrain(--targetPosition, 8, 0);
	    }

	    if(ps4_data.tpad_click){
	      switch(ps4_data.tpad_info[0].finger[0].x / 400){
	      case 0:
	        targetPosition=1;
	        break;
	      case 1:
	        targetPosition=2;
	        break;
	      case 2:
	        switch(ps4_data.tpad_info[0].finger[0].y / 300){
	        case 0:
	          targetPosition=5;
	          break;
	        case 1:
	          targetPosition=4;
	          break;
	        case 2:
	          targetPosition=3;
	          break;
	        }
	        break;
	      case 3:
	        targetPosition=6;
	        break;
	      case 4:
	        targetPosition=7;
	        break;
	      }
	    }

        if(PS4_ButtonPress(PS)&& ps4_data.cross) {
          pusher(true);
        }

	    if(ps4_data.cross) {
	      //Reset all pneumatic to initial mode
	       // airSetState(&airBoard, 0, 0);
	       // airSetState(&airBoard, 1, 0);
	        airSetState(&airBoard, 2, 0);
	        airSetState(&airBoard, 3, 0);
	        airSetState(&airBoard, 4, 0);
	        airSetState(&airBoard, 5, 0);
	        airSetState(&airBoard, 6, 0);
	        airSetState(&airBoard, 7, 0);
	        airSetState(&airBoard, 8, 0);
	        Servo1.command[0] = (ROLL_MIN+ROLL_MAX)/2;
	        Servo1.command[1] = PITCH_MIN;
	        Servo1.command[2] = RAMMER_MIN;
	        shooterAlive=0;
	    }


	    if(ps4_data.circle) {
	        airSetState(&airBoard, 0,1);//base
	        airSetState(&airBoard, 1,1);//base
	        if (targetPosition != 8 && targetPosition != 0){
	           reload_and_shoot();
	        }
	    }
	    else if ((airBoard.state)&(1<<8)){
	      int servoRoll = constrain(ROLL_DEFAULT + getRoll()*SERVO_STEP_ROLL, ROLL_MAX, ROLL_MIN);
	      if (servoRoll > Servo1.command[0]) Servo1.command[0]+= (servoRoll > Servo1.command[0] + 20)?3:1;
	      else if (servoRoll < Servo1.command[0]) Servo1.command[0]-= (servoRoll < Servo1.command[0] - 20)?2:1;

	      int servoPitch = constrain(PITCH_MIN + getPitch()*SERVO_STEP_PITCH, PITCH_MAX, PITCH_MIN);
	      if (servoPitch > Servo1.command[1] )Servo1.command[1]+=(servoPitch > Servo1.command[1] + 20)?2:1;
	      else if (servoPitch < Servo1.command[1] )Servo1.command[1]-=(servoPitch < Servo1.command[1] - 20)?2:1;

	    }
	}
    castLimit();
    displayDebug ();
	updateOldPS4Data ();


}
