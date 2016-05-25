/*
 * common.c
 *
 *  Created on: 2015¦~4¤ë5¤é
 *      Author: Hung
 */
#include "common.h"
#include "driving.h"
#include "math.h"

int NormalizeAngle(int t)
{
    while(t > 1800) t -= 3600;
    while(t <= -1800) t += 3600;
    return t;           // range from -1799 to +1800
}

float fNormalizeAngle(float t)
{
    while(t > PI) t -= (PI * 2.0);
    while(t <= -PI) t += (PI * 2.0);
    return t;           // range from -PI to PI
}

int AddDeadZone(int value, int tolerance)
{
    if(value > tolerance) value -= tolerance;
    else if(value < -tolerance) value += tolerance;
    else value = 0;
    return value;
}

int Euclidean(int x1, int y1, int x2, int y2){
  float dx = x1 - x2;
  float dy = y1 - y2;
  return (int)sqrt(dx*dx+dy*dy);
}
