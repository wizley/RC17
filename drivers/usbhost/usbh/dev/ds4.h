#ifndef USBH_DS4_H_
#define USBH_DS4_H_

#include "usbh.h"

#if DRIVER_USE_USBH && DRIVER_USBH_USE_DS4

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/
#define USB_HID_GET_REPORT           0x01
#define USB_HID_GET_IDLE             0x02
#define USB_HID_GET_PROTOCOL         0x03
#define USB_HID_SET_REPORT           0x09
#define USB_HID_SET_IDLE             0x0A
#define USB_HID_SET_PROTOCOL         0x0B

#define USB_DESC_TYPE_HID            0x21
#define USB_DESC_TYPE_HID_REPORT     0x22
#define USB_HID_DESC_SIZE            9

#define USB_DESC_HID_REPORT          ((USB_DESC_TYPE_HID_REPORT << 8) & 0xFF00)
#define USB_DESC_HID                 ((USB_DESC_TYPE_HID << 8) & 0xFF00)


/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
typedef enum {
  USBHDS4_STATE_UNINIT = 0,
  USBHDS4_STATE_STOP = 1,
  USBHDS4_STATE_ACTIVE = 2,
  USBHDS4_STATE_READY = 3
} usbhds4_state_t;

typedef struct {
  /* inherited from abstract class driver */
  _usbh_base_classdriver_data

  usbhds4_state_t state;

  usbh_ep_t epin;
  usbh_urb_t iq_urb;
  threads_queue_t iq_waiting;
  uint32_t iq_counter;
  USBH_DEFINE_BUFFER(uint8_t, iq_buff[64]);
  uint8_t *iq_ptr;
  usbh_ep_t epout;
  usbh_urb_t oq_urb;
  threads_queue_t oq_waiting;
  uint32_t oq_counter;
  USBH_DEFINE_BUFFER(uint8_t, oq_buff[64]);
  uint8_t *oq_ptr;
  uint8_t ifnum;
  virtual_timer_t vt;

} USBHDS4Driver;

typedef enum{
  DPAD_UP = 0x0,
  DPAD_UP_RIGHT = 0x1,
  DPAD_RIGHT = 0x2,
  DPAD_RIGHT_DOWN = 0x3,
  DPAD_DOWN = 0x4,
  DPAD_DOWN_LEFT = 0x5,
  DPAD_LEFT = 0x6,
  DPAD_LEFT_UP = 0x7,
  DPAD_OFF = 0x8
}ds4_dpad_state_e;

typedef struct __attribute__((packed)) {
  uint8_t padding;
  struct {
    uint8_t counter :7;
    uint8_t is_touching :1;
    uint16_t x :12;
    uint16_t y :12;
  }__attribute__((packed)) finger[2];
} ds4_tpad_info_t;

typedef union  __attribute__((packed)){
  struct __attribute__((packed)){
    uint8_t dpad_code :4;
    uint8_t square :1;
    uint8_t cross :1;
    uint8_t circle :1;
    uint8_t triangle :1;

    uint8_t l1 :1;
    uint8_t r1 :1;
    uint8_t l2 :1;
    uint8_t r2 :1;
    uint8_t share :1;
    uint8_t options :1;
    uint8_t l3 :1;
    uint8_t r3 :1;

    uint8_t ps :1;
    uint8_t tpad_click :1;
    uint8_t reportCounter :6;
  };
  uint32_t val : 24;
}ds4_buttons;//added for doing debounce

typedef enum{
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
        SHARE = 4,
        OPTIONS = 5,
        L3 = 6,
        R3 = 7,
        L2 = 8,
        R2 = 9,
        L1 = 10,
        R1 = 11,
        TRIANGLE = 12,
        CIRCLE = 13,
        CROSS = 14,
        SQUARE = 15,
        PS = 16,
        TOUCHPAD = 17,
}ButtonEnum;





typedef struct __attribute__((packed)) {
  uint8_t hat_left_x;

  uint8_t hat_left_y;

  uint8_t hat_right_x;

  uint8_t hat_right_y;

  ds4_buttons btns;

  uint8_t l2_trigger;

  uint8_t r2_trigger;

  uint8_t padding1[2];

  uint8_t battery;

  int16_t gyroY;

  int16_t gyroZ;

  int16_t gyroX;

  int16_t accX;

  int16_t accZ;

  int16_t accY;

  uint8_t padding2[5];

  uint8_t status;

  uint8_t padding3[3];

  ds4_tpad_info_t tpad_info[3];
} DS4_status_t;

typedef struct __attribute__((packed)){
  uint8_t rumble_small;
  uint8_t rumble_big;
  uint8_t led_r;
  uint8_t led_g;
  uint8_t led_b;
  uint8_t flash_on;
  uint8_t flash_off;
}DS4_command_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
extern USBHDS4Driver USBHDS4[DRIVER_USBHDS4_MAX_INSTANCES];

#ifdef __cplusplus
extern "C" {
#endif
  void usbhds4ObjectInit(USBHDS4Driver *ds4p);
  void usbhds4Start(USBHDS4Driver *ds4p);
  void usbhds4Stop(USBHDS4Driver *ds4p);
  bool DS4_ReadTimeOut(USBHDS4Driver *ds4p, DS4_status_t *data, systime_t timeout);
  bool DS4_WriteTimeOut(USBHDS4Driver *ds4p, DS4_command_t *data, systime_t timeout);
#ifdef __cplusplus
}
#endif


#endif

#endif /* USBH_DS4_H_ */
