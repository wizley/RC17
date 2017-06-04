//<<<<<<< HEAD
///*
// * encoder.h
// *
// *  Created on: 12 Oct, 2015
// *      Author: u564
// */
//
//#ifndef ROBOT_ENCODER_ENCODER_H_
//#define ROBOT_ENCODER_ENCODER_H_
//
//#define ID_ENCODER1_2 4
//#define ID_ENCODER3_4 5
//
//typedef struct{
//  uint16_t count_per_revolution[2];
//  uint16_t count[2];
//  int16_t delta_count[2];
//  uint8_t Alive;
//}ENCObj_t;
//
//extern ENCObj_t encoder1_2;
//extern ENCObj_t encoder3_4;
//void encoder_setAlive(void * arg);
//void encoder_decAlive(void * arg);
//#endif /* ROBOT_ENCODER_ENCODER_H_ */
//=======
/*
 * encoder.h
 *
 *  Created on: 12 Oct, 2015
 *      Author: u564
 */

#ifndef ROBOT_ENCODER_ENCODER_H_
#define ROBOT_ENCODER_ENCODER_H_

#define ID_ENCODER1_2 4
#define ID_ENCODER3_4 5

typedef struct{
  uint16_t count_per_revolution[2];
  uint16_t count[2];
  uint16_t delta_count[2];
  uint8_t Alive;
}ENCObj_t;

extern ENCObj_t encoder1_2;
extern ENCObj_t encoder3_4;
void encoder_setAlive(volatile void * arg);
void encoder_decAlive(volatile void * arg);
#endif /* ROBOT_ENCODER_ENCODER_H_ */
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
