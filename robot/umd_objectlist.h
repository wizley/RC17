
#ifndef ROBOT_UMD_OBJECTLIST_H_
#define ROBOT_UMD_OBJECTLIST_H_

UMD_Obj_t umd_objectlist[32] =
{
    {ID_M0_VMODE, (uint8_t*)&M[0].SetPoint, 2, NULL, (uint8_t*)&M[0].Feedback, 2, NULL, NULL},
    {ID_M1_VMODE, (uint8_t*)&M[1].SetPoint, 2, NULL, (uint8_t*)&M[1].Feedback, 2, NULL, NULL},
    {ID_M2_VMODE, (uint8_t*)&M[2].SetPoint, 2, NULL, (uint8_t*)&M[2].Feedback, 2, NULL, NULL},
    {ID_M3_VMODE, (uint8_t*)&M[3].SetPoint, 2, NULL, (uint8_t*)&M[3].Feedback, 2, NULL, NULL},
    {ID_SYNC, NULL, 0, NULL, NULL, 0, NULL, NULL},
    {ID_ENCODER1_2, NULL, 0, NULL, (uint8_t*)&encoder1_2.delta_count, 4, NULL, NULL},
    {ID_ENCODER3_4, NULL, 0, NULL, (uint8_t*)&encoder3_4.delta_count, 4, NULL, NULL},
    {ID_SERVO1, (uint8_t*)&Servo1.command, 16, NULL, (uint8_t*)&Servo1.current, 2, NULL, NULL},
    UMD_OBJECTLIST_END
};

#endif /* ROBOT_UMD_OBJECTLIST_H_ */
