/*
 * linesensor.c
 *
 *  Created on: May 6, 2016
 *      Author: Melvin
 */

#include "ch.h"
#include "umd.h"
#include "linesensor.h"

LINE_SENSOR LineSensor[4] = {{.id = 0, .size = LINESENSOR_0_SIZE},{.id = 1, .size = LINESENSOR_1_SIZE},
                             {.id = 2, .size = LINESENSOR_2_SIZE},{.id = 3, .size = LINESENSOR_3_SIZE}};

umd_return_e linesensor_send_command(LINE_SENSOR *line, int command){
  line->Command = command;
  UMD_Obj_t umd_object;
  umd_object.id = CAL_ID_COMMAND(line->id);
  umd_object.tx_data = (uint8_t)&(line->Command);
  umd_object.tx_len = 2;
  umd_object.rx_len = 0;
  umd_object.rx_callback = NULL;
  return UMD_Poll_Single(&umd_object);
}

void linesensor_get_data(LINE_SENSOR *line){
  if (line->size > 36){
    UMD_Obj_t line_object_list[6] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA36_47(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[36]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UMD_PollObjectList(line_object_list);
    return;
  }else if(line->size > 24){
    UMD_Obj_t line_object_list[5] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA24_35(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[24]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UMD_PollObjectList(line_object_list);
    return;
  }else if(line->size > 12){
    UMD_Obj_t line_object_list[4] = {
     {ID_SYNC, NULL, 0, NULL, 0, NULL, NULL},
     {.id=CAL_ID_DATA0_11(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[0]),.rx_len=12,.rx_callback=NULL},
     {.id=CAL_ID_DATA12_23(line->id),.tx_data=(uint8_t*)&(line->size),.tx_len=2,.rx_data=(uint8_t*)&(line->Data[12]),.rx_len=12,.rx_callback=NULL},
     {ID_END, NULL, 0, NULL, 0, NULL, NULL}
    };
    UMD_PollObjectList(line_object_list);
    return;
  }else if(line->size > 0){
    UMD_Obj_t umd_object;
    umd_object.id = CAL_ID_DATA0_11(line->id);
    umd_object.tx_data = (uint8_t*)&(line->size);
    umd_object.tx_len = 2;
    umd_object.rx_data = (uint8_t*)&(line->Data[0]);
    umd_object.rx_len = 12;
    umd_object.rx_callback = NULL;
    UMD_Poll_Single(&umd_object);
    return;
  }
}

void linesensor_setAlive(void * arg){
  LINE_SENSOR * l = (LINE_SENSOR *) arg;
  l->Alive = 3;
}

void linesensor_decAlive(void * arg){
  LINE_SENSOR * l = (LINE_SENSOR * )arg;
  if ((l->Alive) > 0)
    (l->Alive)--;
}
