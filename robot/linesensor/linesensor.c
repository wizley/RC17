//<<<<<<< HEAD
///*
// * linesensor.c
// *
// *  Created on: May 6, 2016
// *      Author: Melvin
// */
//
//#include "ch.h"
//#include "umd.h"
//#include "linesensor.h"
//
//LINE_SENSOR LineSensor[4] = {{.id = 0, .size = LINESENSOR_0_SIZE},{.id = 1, .size = LINESENSOR_1_SIZE},
//                             {.id = 2, .size = LINESENSOR_2_SIZE},{.id = 3, .size = LINESENSOR_3_SIZE}};
//
//umd_return_e linesensor_send_command(LINE_SENSOR *line, int command){
//  line->Command = command;
//  UMD_Obj_t umd_object;
//  umd_object.id = CAL_ID_COMMAND(line->id);
//  umd_object.tx_data = (uint8_t)&(line->Command);
//  umd_object.tx_len = 2;
//  umd_object.rx_len = 0;
//  umd_object.rx_callback = NULL;
//  return UMD_Poll_Single(&umd_object);
//}
//
//void linesensor_get_data(LINE_SENSOR *line){
//  if (line->size > 36){
//    UMD_Obj_t line_object_list[6] = {
//     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
//     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA36_47(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[36]),.rx_len=12,.rx_callback=NULL},
//     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
//    };
//    UMD_PollObjectList(line_object_list);
//    return;
//  }else if(line->size > 24){
//    UMD_Obj_t line_object_list[5] = {
//     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
//     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
//     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
//    };
//    UMD_PollObjectList(line_object_list);
//    return;
//  }else if(line->size > 12){
//    UMD_Obj_t line_object_list[4] = {
//     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
//     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
//     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
//     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
//    };
//    UMD_PollObjectList(line_object_list);
//    return;
//  }else if(line->size > 0){
//    UMD_Obj_t umd_object;
//    umd_object.id = CAL_ID_DATA0_11(line->id);
//    umd_object.tx_data = (uint8_t*)&(line->size);
//    umd_object.tx_len = 2;
//    umd_object.rx_data = (uint8_t*)&(line->Data[0]);
//    umd_object.rx_len = 12;
//    umd_object.rx_callback = NULL;
//    UMD_Poll_Single(&umd_object);
//    return;
//  }
//}
//
//void linesensor_setAlive(void * arg){
//  LINE_SENSOR * l = (LINE_SENSOR *) arg;
//  l->Alive = 3;
//}
//
//void linesensor_decAlive(void * arg){
//  LINE_SENSOR * l = (LINE_SENSOR * )arg;
//  if ((l->Alive) > 0)
//    (l->Alive)--;
//}
//=======
/*
 * linesensor.c
 *
 *  Created on: May 6, 2016
 *      Author: Melvin
 */

#include "ch.h"
#include "udc.h"
#include "linesensor.h"

LINE_SENSOR LineSensor[4] = {{.id = 0, .size = LINESENSOR_0_SIZE, .Alive = 0},{.id = 1, .size = LINESENSOR_1_SIZE, .Alive = 0},
                             {.id = 2, .size = LINESENSOR_2_SIZE, .Alive = 0},{.id = 3, .size = LINESENSOR_3_SIZE, .Alive = 0}};
ls_pos_info_t LineSensor2016[4];

udc_rx_state_e linesensor_send_command(LINE_SENSOR *line, int command){
  line->Command = command;
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_COMMAND(line->id);
  udc_object.tx_data = (udc_tx_data_t)&(line->Command);
  udc_object.tx_len = 2;
  udc_object.rx_len = 0;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

void linesensor_get_data(LINE_SENSOR *line){
  if (line->size > 36){
    UDC_Obj_t line_object_list[6] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA36_47(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[36]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UDC_PollObjectList(line_object_list);
    return;
  }else if(line->size > 24){
    UDC_Obj_t line_object_list[5] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UDC_PollObjectList(line_object_list);
    return;
  }else if(line->size > 12){
    UDC_Obj_t line_object_list[4] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(udc_tx_data_t)&(line->size),.tx_len=2,.rx_data=(udc_rx_data_t)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UDC_PollObjectList(line_object_list);
    return;
  }else if(line->size > 0){
    UDC_Obj_t udc_object;
    udc_object.id = CAL_ID_DATA0_11(line->id);
    udc_object.tx_data = (udc_tx_data_t)&(line->size);
    udc_object.tx_len = 2;
    udc_object.rx_data = (udc_rx_data_t)&(line->Data[0]);
    udc_object.rx_len = 12;
    udc_object.rx_callback = NULL;
    UDC_Poll_Single(&udc_object);
    return;
  }
}

void linesensor_get_data0_11(LINE_SENSOR *line){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_DATA0_11(line->id);
  udc_object.tx_data = (udc_tx_data_t)&(line->size);
  udc_object.tx_len = 2;
  udc_object.rx_data = (udc_rx_data_t)&(line->Data[0]);
  udc_object.rx_len = 12;
  udc_object.rx_callback = NULL;
  UDC_Poll_Single(&udc_object);
  return;
}

void linesensor_get_data12_23(LINE_SENSOR *line){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_DATA12_23(line->id);
  udc_object.tx_data = (udc_tx_data_t)&(line->size);
  udc_object.tx_len = 2;
  udc_object.rx_data = (udc_rx_data_t)&(line->Data[12]);
  udc_object.rx_len = 12;
  udc_object.rx_callback = NULL;
  UDC_Poll_Single(&udc_object);
  return;
}

void linesensor_get_data24_35(LINE_SENSOR *line){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_DATA24_35(line->id);
  udc_object.tx_data = (udc_tx_data_t)&(line->size);
  udc_object.tx_len = 2;
  udc_object.rx_data = (udc_rx_data_t)&(line->Data[24]);
  udc_object.rx_len = 12;
  udc_object.rx_callback = NULL;
  UDC_Poll_Single(&udc_object);
  return;
}

void linesensor_setAlive(volatile void * arg){
  LINE_SENSOR * l = (LINE_SENSOR *) arg;
  l->Alive = 3;
}

void linesensor_decAlive(volatile void * arg){
  LINE_SENSOR * l = (LINE_SENSOR * )arg;
  if ((l->Alive) > 0)
    (l->Alive)--;
}
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
