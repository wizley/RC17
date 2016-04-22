/*
 * udc_objectlist.h
 *
 *  Created on: 9 Oct, 2015
 *      Author: u564
 */

#ifndef ROBOT_UDC_OBJECTLIST_H_
#define ROBOT_UDC_OBJECTLIST_H_

#define ID_SYNC 0
#define ID_END -1

extern void SetMotorAlive();

UDC_Obj_t udc_objectlist[32] =
{
    {ID_SYNC, NULL, 0, NULL, 0, NULL},
#if USE_MOTOR_0
    {ID_M0_VMODE, (udc_tx_data_t)&M[0].SetPoint, 2, (udc_rx_data_t)&M[0].Feedback, 2, &SetMotorAlive},
#endif
#if USE_MOTOR_1
    {ID_M1_VMODE, (udc_tx_data_t)&M[1].SetPoint, 2, (udc_rx_data_t)&M[1].Feedback, 2, NULL},
#endif
#if USE_MOTOR_2
    {ID_M2_VMODE, (udc_tx_data_t)&M[2].SetPoint, 2, (udc_rx_data_t)&M[2].Feedback, 2, NULL},
#endif
#if USE_MOTOR_3
    {ID_M3_VMODE, (udc_tx_data_t)&M[3].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
#endif
#if USE_MOTOR_4
    {ID_M4_VMODE, (udc_tx_data_t)&M[4].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
#endif
#if USE_MOTOR_5
    {ID_M5_VMODE, (udc_tx_data_t)&M[5].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
#endif
#if USE_MOTOR_6
    {ID_M6_VMODE, (udc_tx_data_t)&M[6].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
#endif
#if USE_MOTOR_7
    {ID_M7_VMODE, (udc_tx_data_t)&M[7].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
#endif
#if USE_SERVO && SERVO_NUMBER > 0
    {106, (udc_tx_data_t)&Servo1.command, 16, (udc_rx_data_t)&Servo1.current, 2, NULL},
#endif
#if USE_SERVO && SERVO_NUMBER > 8
    {ID_SERVO2, (udc_tx_data_t)&Servo2.command, 16, (udc_rx_data_t)&Servo2.current, 2, NULL},
#endif
#if USE_ENCODER && ENCODER_NUMBER > 0
    {ID_ENCODER1_2, NULL, 0, (udc_rx_data_t)&encoder1_2.count, 4, NULL},
#endif
#if defined(USE_ENCODER) && ENCODER_NUMBER > 2
    {ID_ENCODER3_4, NULL, 0, (udc_rx_data_t)&encoder3_4.count, 4, NULL},
#endif
    {ID_END, NULL, 0, NULL, 0, NULL}
};

#endif /* ROBOT_UDC_OBJECTLIST_H_ */
