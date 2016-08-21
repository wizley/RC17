/*
 * servo.c
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#include "ch.h"
#include "umd.h"
#include "servo.h"

servo_t Servo1 = {.command={1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500}};
servo_t Servo2 = {.command={1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500}};

void servo_setAlive(void * arg){
     servo_t * s = (servo_t * ) arg;
     s->Alive = 3;
}

void servo_decAlive(void * arg){
     servo_t * s = (servo_t *) arg;
     if ((s->Alive)> 0)
         (s->Alive)--;
}
