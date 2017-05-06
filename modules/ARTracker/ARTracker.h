/*
 * ARTracker.h
 *
 *  Created on: May 30, 2016
 *      Author: Melvin
 */

#ifndef MODULES_ARTRACKER_ARTRACKER_H_
#define MODULES_ARTRACKER_ARTRACKER_H_

typedef struct __attribute__((packed)){
    //uint8_t a;
    uint8_t d;
    int16_t anglex;//Tangent of X translation
    int16_t angley;//Tangent of Y translation
    int16_t distance;// Distance from cam to code
    int16_t pitch; //upward = -ve; downward = +ve;
}ARTracker_status_t;

extern volatile ARTracker_status_t ARTracker_status;
void artracker_init(void);
bool check_tracker_data(ARTracker_status_t * a);

#endif /* MODULES_ARTRACKER_ARTRACKER_H_ */
