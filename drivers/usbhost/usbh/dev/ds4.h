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

typedef struct __attribute__((packed)){
  uint8_t left_hat_x;

  uint8_t left_hat_y;

  uint8_t right_hat_x;

  uint8_t right_hat_y;

  uint8_t l2;

  uint8_t r2;

  uint8_t ps:1;
  uint8_t share:1;
  uint8_t options:1;
  uint8_t touchpad:1;
  uint8_t triangle:1;
  uint8_t circle:1;
  uint8_t cross:1;
  uint8_t square:1;

  uint8_t left:1;
  uint8_t right:1;
  uint8_t up:1;
  uint8_t down:1;
  uint8_t l3:1;
  uint8_t r3:1;
  uint8_t l1:1;
  uint8_t r1:1;

  uint8_t finger0:1;
  uint8_t finger1:1;
  uint8_t reserved1:6;

  float pitch;
  float roll;

  uint8_t battery;

  uint16_t finger0_x;
  uint16_t finger0_y;
  uint16_t finger1_x;
  uint16_t finger1_y;
}DS4_status_t;

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
//  void usbhftdipObjectInit(USBHFTDIPortDriver *ftdipp);
  void usbhds4Start(USBHDS4Driver *ds4p);
  void usbhds4Stop(USBHDS4Driver *ds4p);
  bool DS4_ReadTimeOut(USBHDS4Driver *ds4p, DS4_status_t *data, systime_t timeout);
#ifdef __cplusplus
}
#endif


#endif

#endif /* USBH_DS4_H_ */
