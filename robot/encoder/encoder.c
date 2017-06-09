//<<<<<<< HEAD
///*
// * encoder.c
// *
// *  Created on: 12 Oct, 2015
// *      Author: u564
// */
//
//#include "ch.h"
//#include "umd.h"
//#include "encoder.h"
//
//ENCObj_t encoder1_2;
//ENCObj_t encoder3_4;
//
//void encoder_setAlive(void * arg){
//     ENCObj_t * e = (ENCObj_t *) arg;
//     e->Alive = 3;
//}
//
//void encoder_decAlive(void * arg){
//     ENCObj_t *e = (ENCObj_t * ) arg;
//     if ((e->Alive) > 0)
//         (e->Alive)--;
//}
//=======
/*
 * encoder.c
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#include "ch.h"
#include "udc.h"
#include "encoder.h"

ENCObj_t encoder1_2 = {.Alive = 0};
ENCObj_t encoder3_4 = {.Alive = 0};

void encoder_setAlive(volatile void * arg){
     ENCObj_t * e = (ENCObj_t *) arg;
     e->Alive = 3;
}

void encoder_decAlive(volatile void * arg){
     ENCObj_t *e = (ENCObj_t * ) arg;
     if ((e->Alive) > 0)
         (e->Alive)--;
}
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
