/*
 * common.h
 *
 *  Created on: 2015¦~4¤ë5¤é
 *      Author: Hung
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifndef PI
#define PI  3.1415926535897932384626433832795028841971693993751
#endif

int NormalizeAngle(int t);
float fNormalizeAngle(float t);
int AddDeadZone(int value, int tolerance);
int Euclidean(int x1, int y1, int x2, int y2);
#endif /* COMMON_H_ */
