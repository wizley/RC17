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
typedef struct {
  /* inherited from abstract class driver */
  _usbh_base_classdriver_data


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
  uint32_t tag;

} USBHDS4Driver;

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
//  void usbhftdipStart(USBHFTDIPortDriver *ftdipp, const USBHFTDIPortConfig *config);
//  void usbhftdipStop(USBHFTDIPortDriver *ftdipp);
#ifdef __cplusplus
}
#endif


#endif

#endif /* USBH_DS4_H_ */
