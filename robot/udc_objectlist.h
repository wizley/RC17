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

UDC_Obj_t udc_objectlist[32] =
{
    {ID_SYNC, NULL, 0, NULL, 0, NULL},
    {ID_M0_VMODE, (udc_tx_data_t)&M[0].SetPoint, 2, (udc_rx_data_t)&M[0].Feedback, 2, NULL},
    {ID_M1_VMODE, (udc_tx_data_t)&M[1].SetPoint, 2, (udc_rx_data_t)&M[1].Feedback, 2, NULL},
    {ID_M2_VMODE, (udc_tx_data_t)&M[2].SetPoint, 2, (udc_rx_data_t)&M[2].Feedback, 2, NULL},
    {ID_M3_VMODE, (udc_tx_data_t)&M[3].SetPoint, 2, (udc_rx_data_t)&M[3].Feedback, 2, NULL},
    {ID_SERVO1, (udc_tx_data_t)&Servo1.command, 16, (udc_rx_data_t)&Servo1.current, 2, NULL},
    {ID_ENCODER1_2, NULL, 0, (udc_rx_data_t)&encoder1_2.count, 4, NULL},
    {ID_ENCODER3_4, NULL, 0, (udc_rx_data_t)&encoder3_4.count, 4, NULL},
    {ID_END, NULL, 0, NULL, 0, NULL}
};

#endif /* ROBOT_UDC_OBJECTLIST_H_ */
