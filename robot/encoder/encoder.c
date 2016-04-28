/*
 * encoder.c
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#include "ch.h"
#include "udc.h"
#include "encoder.h"

ENCObj_t encoder1_2;
ENCObj_t encoder3_4;

void encoder_checkAlive(volatile void * arg){
     ENCObj_t * e = (ENCObj_t *) arg;
     e->Alive = 3;
}
