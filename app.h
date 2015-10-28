#ifndef _APP_H_
#define _APP_H_

#include "ch.h"

#define UI_MB_SIZE 10

extern mailbox_t app_mb;

typedef enum{
  UI_INPUT_BUTTON = 0,
  UI_INPUT_TOUCH,
  UI_STATUSBAR_TICK
}ui_evt_type_e;

typedef enum{
  UI_BUTTON_UP = 0,
  UI_BUTTON_DOWN,
  UI_BUTTON_LEFT,
  UI_BUTTON_RIGHT,
  UI_BUTTON_ENTER,
  UI_BUTTON_BACK,
  UI_BUTTON_RESERVED1,
  UI_BUTTON_RESERVED2,
  UI_BUTTON_RESERVED3
}ui_button_evt_e;

//typedef struct{
//  uint16_t but1_pressed  : 1;
//  uint16_t but2_pressed  : 1;
//  uint16_t but3_pressed  : 1;
//  uint16_t but4_pressed  : 1;
//  uint16_t but5_pressed  : 1;
//  uint16_t but6_pressed  : 1;
//  uint16_t but7_pressed  : 1;
//  uint16_t but8_pressed  : 1;
//  uint16_t but9_pressed  : 1;
//  uint16_t but10_pressed : 1;
//  uint16_t but11_pressed : 1;
//  uint16_t but12_pressed : 1;
//  uint16_t but13_pressed : 1;
//  uint16_t but14_pressed : 1;
//  uint16_t but15_pressed : 1;
//  uint16_t but16_pressed : 1;
//}ui_button_state_t;

typedef struct{
  uint16_t mb_voltage;
  uint16_t motor_voltage;
  uint32_t system_time;
  uint8_t robot_state;
}ui_status_bar_type_t;

typedef struct{
  uint16_t x;
  uint16_t y;
  uint8_t is_touching;
}ui_touch_type_t;

typedef struct {
  ui_evt_type_e type;
  union{
    ui_button_evt_e button_state;
    ui_status_bar_type_t status_bar_info;
    ui_touch_type_t touchscreen_info[2];
  }data;
}ui_event;

/**
 * @brief An application entry, used by the menu application.
 */
typedef struct {
    ///> Application name
    const char* name;

    /**
     * @brief Main application routine.
     * @params Optional parameters, dependendent on application.
     */
    void (*main)(void* params);
} application;

int app_init(void);

#endif
