//<<<<<<< HEAD
///*
// * ARTracker.h
// *
// *  Created on: May 30, 2016
// *      Author: Melvin
// */
//
//#ifndef MODULES_ARTRACKER_ARTRACKER_H_
//#define MODULES_ARTRACKER_ARTRACKER_H_
//
//typedef struct __attribute__((packed)){
//    uint8_t a;
//    int32_t angle;
//    uint8_t d;
//    int32_t distance;
//}ARTracker_status_t;
//
//extern ARTracker_status_t ARTracker_status;
//void artracker_init(void);
//bool check_tracker_data(ARTracker_status_t * a);
//
//#endif /* MODULES_ARTRACKER_ARTRACKER_H_ */
//=======
/*
 * ARTracker.h
 *
 *  Created on: May 30, 2016
 *      Author: Melvin
 */

#ifndef MODULES_ARTRACKER_ARTRACKER_H_
#define MODULES_ARTRACKER_ARTRACKER_H_

typedef struct __attribute__((packed)){
    uint8_t a;
    int32_t angle;
    uint8_t d;
    int32_t distance;
}ARTracker_status_t;

extern ARTracker_status_t ARTracker_status;
void artracker_init(void);
bool check_tracker_data(ARTracker_status_t * a);

#endif /* MODULES_ARTRACKER_ARTRACKER_H_ */
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
