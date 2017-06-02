/*
 * servo.c
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#include "ch.h"
#include "udc.h"
#include "servo.h"

//HS-7966HB range: 950 - 2050
//HS-7965MG range: 750 - 2250

//new servo board 200 - 550

servo_t Servo1 = {.command={423, 396, 480/*290*/, 370, 370, 370, 370, 370}};
servo_t Servo2 = {.command={400, 400, 400, 400, 400, 400, 400, 400}};


void servo_setAlive(volatile void * arg){
     servo_t * s = (servo_t * ) arg;
     s->Alive = 3;
}

void servo_decAlive(volatile void * arg){
     servo_t * s = (servo_t *) arg;
     if ((s->Alive)> 0)
         (s->Alive)--;
}
