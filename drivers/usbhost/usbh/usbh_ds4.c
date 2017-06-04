#include "hal.h"
#include "usbh.h"

#if DRIVER_USBH_USE_DS4

#if !DRIVER_USE_USBH
#error "USBHDS4 needs USBH"
#endif

#include <string.h>
#include "usbh/dev/ds4.h"
#include "usbh/internal.h"

//#pragma GCC optimize("Og")


#if USBHDS4_DEBUG_ENABLE_TRACE
#define udbgf(f, ...)  usbDbgPrintf(f, ##__VA_ARGS__)
#define udbg(f, ...)  usbDbgPuts(f, ##__VA_ARGS__)
#else
#define udbgf(f, ...)  do {} while(0)
#define udbg(f, ...)   do {} while(0)
#endif

#if USBHDS4_DEBUG_ENABLE_INFO
#define uinfof(f, ...)  usbDbgPrintf(f, ##__VA_ARGS__)
#define uinfo(f, ...)  usbDbgPuts(f, ##__VA_ARGS__)
#else
#define uinfof(f, ...)  do {} while(0)
#define uinfo(f, ...)   do {} while(0)
#endif

#if USBHDS4_DEBUG_ENABLE_WARNINGS
#define uwarnf(f, ...)  usbDbgPrintf(f, ##__VA_ARGS__)
#define uwarn(f, ...)  usbDbgPuts(f, ##__VA_ARGS__)
#else
#define uwarnf(f, ...)  do {} while(0)
#define uwarn(f, ...)   do {} while(0)
#endif

#if USBHDS4_DEBUG_ENABLE_ERRORS
#define uerrf(f, ...)  usbDbgPrintf(f, ##__VA_ARGS__)
#define uerr(f, ...)  usbDbgPuts(f, ##__VA_ARGS__)
#else
#define uerrf(f, ...)  do {} while(0)
#define uerr(f, ...)   do {} while(0)
#endif





/*===========================================================================*/
/* USB Class driver loader for DS4								 		 	 */
/*===========================================================================*/

USBHDS4Driver USBHDS4[DRIVER_USBHDS4_MAX_INSTANCES];

static usbh_baseclassdriver_t *_ds4_load(usbh_device_t *dev, const uint8_t *descriptor, uint16_t rem);
static void _ds4_unload(usbh_baseclassdriver_t *drv);
static void _in_cb(usbh_urb_t *urb);
static void _out_cb(usbh_urb_t *urb);
static usbh_urbstatus_t _setidle(USBHDS4Driver *ds4p, uint8_t duration, uint8_t reportId);
static usbh_urbstatus_t _getreportdescriptor(USBHDS4Driver *ds4p, uint16_t length, uint8_t *buff);

static const usbh_classdriver_vmt_t class_driver_vmt = {
	_ds4_load,
	_ds4_unload
};

const usbh_classdriverinfo_t usbhds4ClassDriverInfo = {
	0x03, 0x00, 0x00, "Dual Shock 4", &class_driver_vmt
};

static usbh_baseclassdriver_t *_ds4_load(usbh_device_t *dev, const uint8_t *descriptor, uint16_t rem) {
	int i;
	USBHDS4Driver *ds4p;


	if (dev->devDesc.idVendor != 0x054C) {
    uerr("Wrong VID");
    return NULL;
  }

	if (dev->devDesc.idProduct != 0x05C4) {
    uerr("Wrong PID");
    return NULL;
  }

	if ((rem < descriptor[0]) || (descriptor[1] != USBH_DT_INTERFACE))
    return NULL;

	const usbh_interface_descriptor_t * const ifdesc = (const usbh_interface_descriptor_t *)descriptor;

	/* alloc driver */
	for (i = 0; i < DRIVER_USBHDS4_MAX_INSTANCES; i++) {
		if (USBHDS4[i].dev == NULL) {
			ds4p = &USBHDS4[i];
			goto alloc_ok;
		}
	}

	uwarn("Can't alloc DS4 driver");

	/* can't alloc */
	return NULL;

alloc_ok:
	/* initialize the driver's variables */
	ds4p->epin.status = USBH_EPSTATUS_UNINITIALIZED;
	ds4p->epout.status = USBH_EPSTATUS_UNINITIALIZED;
	ds4p->ifnum = ifdesc->bInterfaceNumber;
	usbhEPSetName(&dev->ctrl, "DS4[CTRL]");

	/* parse the configuration descriptor */
	if_iterator_t iif;
	generic_iterator_t iep;
	iif.iad = 0;
	iif.curr = descriptor;
	iif.rem = rem;
	for (ep_iter_init(&iep, &iif); iep.valid; ep_iter_next(&iep)) {
		const usbh_endpoint_descriptor_t *const epdesc = ep_get(&iep);
		if ((epdesc->bEndpointAddress & 0x80) && (epdesc->bmAttributes == USBH_EPTYPE_INT)) {
			uinfof("INT IN endpoint found: bEndpointAddress=%02x", epdesc->bEndpointAddress);
			usbhEPObjectInit(&ds4p->epin, dev, epdesc);
			usbhEPSetName(&ds4p->epin, "DS4[INTIN]");
		} else if (((epdesc->bEndpointAddress & 0x80) == 0)
				&& (epdesc->bmAttributes == USBH_EPTYPE_INT)) {
			uinfof("INT OUT endpoint found: bEndpointAddress=%02x", epdesc->bEndpointAddress);
			usbhEPObjectInit(&ds4p->epout, dev, epdesc);
			usbhEPSetName(&ds4p->epout, "DS4[INTOUT]");
		} else {
			uinfof("unsupported endpoint found: bEndpointAddress=%02x, bmAttributes=%02x",
					epdesc->bEndpointAddress, epdesc->bmAttributes);
		}
	}
	if ((ds4p->epin.status != USBH_EPSTATUS_CLOSED) || (ds4p->epout.status != USBH_EPSTATUS_CLOSED)) {
		goto deinit;
	}

	ds4p->state = USBHDS4_STATE_ACTIVE;

	return (usbh_baseclassdriver_t *)ds4p;

deinit:
	/* Here, the enpoints are closed, and the driver is unlinked */
	return NULL;
}

static void _ds4_unload(usbh_baseclassdriver_t *drv) {
	osalDbgCheck(drv != NULL);
	USBHDS4Driver *const ds4p = (USBHDS4Driver *)drv;
	usbhds4Stop(ds4p);
//	usbhEPCloseS(&ds4p->epin);
//	usbhEPCloseS(&ds4p->epout);
}


/*===========================================================================*/
/* MSD Class driver operations (Bulk-Only transport)			 		 	 */
/*===========================================================================*/
static usbh_urbstatus_t _setidle(USBHDS4Driver *ds4p, uint8_t duration, uint8_t reportId) {

  static const uint8_t bmRequestType = \
      USBH_REQTYPE_CLASS | USBH_REQTYPE_OUT | USBH_REQTYPE_INTERFACE;

  static const uint8_t bRequest = USB_HID_SET_IDLE;

  uint16_t wValue = (duration << 8 ) | reportId;

  static const uint16_t wIndex = 0;

  static const uint16_t wLength = 0;

  return usbhControlRequest(ds4p->dev, bmRequestType, bRequest, wValue, wIndex, wLength, NULL);
}

static usbh_urbstatus_t _getreportdescriptor(USBHDS4Driver *ds4p, uint16_t length, uint8_t *buff){

  static const uint8_t bmRequestType = \
      USBH_REQTYPE_STANDARD | USBH_REQTYPE_IN | USBH_REQTYPE_INTERFACE;

  static const uint8_t bRequest = USBH_REQ_GET_DESCRIPTOR;

  static const uint16_t wValue = USB_DESC_HID_REPORT;

  static const uint16_t wIndex = 0;

  uint16_t wLength = length;

  return usbhControlRequest(ds4p->dev, bmRequestType, bRequest, wValue, wIndex, wLength, buff);
}

static void _submitOutI(USBHDS4Driver *ds4p, uint32_t len) {
  udbgf("DS4: Submit OUT %d", len);
  ds4p->oq_urb.requestedLength = len;
  usbhURBObjectResetI(&ds4p->oq_urb);
  usbhURBSubmitI(&ds4p->oq_urb);
}

static void _out_cb(usbh_urb_t *urb) {
  USBHDS4Driver *const ds4p = (USBHDS4Driver *)urb->userData;
  switch (urb->status) {
  case USBH_URBSTATUS_OK:
    ds4p->oq_ptr = ds4p->oq_buff;
    ds4p->oq_counter = 32;
    chThdDequeueNextI(&ds4p->oq_waiting, Q_OK);
    return;
  case USBH_URBSTATUS_DISCONNECTED:
    uwarn("DS4: URB OUT disconnected");
    chThdDequeueNextI(&ds4p->oq_waiting, Q_RESET);
    return;
  default:
    uerrf("DS4: URB OUT status unexpected = %d", urb->status);
    break;
  }
  usbhURBObjectResetI(&ds4p->oq_urb);
  usbhURBSubmitI(&ds4p->oq_urb);
}

static void _submitInI(USBHDS4Driver *ds4p) {
  udbg("DS4: Submit IN");
  usbhURBObjectResetI(&ds4p->iq_urb);
  usbhURBSubmitI(&ds4p->iq_urb);
}

static void _in_cb(usbh_urb_t *urb) {
  USBHDS4Driver *const ds4p = (USBHDS4Driver *)urb->userData;
  switch (urb->status) {
  case USBH_URBSTATUS_OK:
    if (urb->actualLength < 64) {
      uwarnf("DS4: URB IN actualLength = %d, < 2", urb->actualLength);
    } else if (urb->actualLength == 64) {
      udbgf("DS4: URB IN data len=%d, Report ID=%02x",
          urb->actualLength,
          ((uint8_t *)urb->buff)[0]);
      ds4p->iq_counter = urb->actualLength;
      chThdDequeueNextI(&ds4p->iq_waiting, Q_OK);
      return;
    } else {
      udbgf("DS4: URB IN no data, Report ID=%02x",
          ((uint8_t *)urb->buff)[0]);
      return;
    }
    break;
  case USBH_URBSTATUS_DISCONNECTED:
    uwarn("DS4: URB IN disconnected");
    chThdDequeueNextI(&ds4p->iq_waiting, Q_RESET);
    return;
  default:
    uerrf("DS4: URB IN status unexpected = %d", urb->status);
    break;
  }
  _submitInI(ds4p);
}

static void _vt(void *p) {
  USBHDS4Driver *const ds4p = (USBHDS4Driver *)p;
  chSysLockFromISR();
//  uint32_t len = ds4p->oq_ptr - ds4p->oq_buff;
//  if (len && !usbhURBIsBusy(&ds4p->oq_urb)) {
//    _submitOutI(ds4p, len);
//  }
  if ((ds4p->iq_counter == 0) && !usbhURBIsBusy(&ds4p->iq_urb)) {
    _submitInI(ds4p);
  }
  chVTSetI(&ds4p->vt, MS2ST(2), _vt, ds4p);
  chSysUnlockFromISR();
}

void usbhds4Start(USBHDS4Driver *ds4p){

  osalDbgCheck((ds4p->state == USBHDS4_STATE_ACTIVE)
      || (ds4p->state == USBHDS4_STATE_READY));

  if (ds4p->state == USBHDS4_STATE_READY)
    return;

  /* HID Class request */
  usbh_urbstatus_t stat;
  // Set Idle
  usbhEPClose(&ds4p->dev->ctrl);
  usbhEPOpen(&ds4p->dev->ctrl);
  stat = _setidle(ds4p, 0, 0);
  if (stat == USBH_URBSTATUS_OK) {
  } else if (stat == USBH_URBSTATUS_STALL) {
    uwarn("Set Idle Stall");
  } else {
    uerr("Set Idle Error");
  }

  // Get report descriptor
  USBH_DEFINE_BUFFER(uint8_t, buff[483]);
  stat = _getreportdescriptor(ds4p, 483, buff);
  if (stat == USBH_URBSTATUS_OK) {
  } else if (stat == USBH_URBSTATUS_STALL) {
    uwarn("GetHIDReportDescriptor Stall");
  } else {
    uerr("GetHIDReportDescriptor Error");
  }

  /* open the INT IN/OUT endpoints */
  usbhURBObjectInit(&ds4p->oq_urb, &ds4p->epout, _out_cb, ds4p, ds4p->oq_buff, 0);
  chThdQueueObjectInit(&ds4p->oq_waiting);
  ds4p->oq_counter = 32;
  ds4p->oq_ptr = ds4p->oq_buff;
  usbhEPOpen(&ds4p->epout);

  usbhURBObjectInit(&ds4p->iq_urb, &ds4p->epin, _in_cb, ds4p, ds4p->iq_buff, 64);
  chThdQueueObjectInit(&ds4p->iq_waiting);
  ds4p->iq_counter = 0;
  ds4p->iq_ptr = ds4p->iq_buff;
  usbhEPOpen(&ds4p->epin);
  osalSysLock();
  usbhURBSubmitI(&ds4p->iq_urb);
  osalSysUnlock();

  chVTObjectInit(&ds4p->vt);
  chVTSet(&ds4p->vt, MS2ST(2), _vt, ds4p);

  ds4p->state = USBHDS4_STATE_READY;

}

void usbhds4Stop(USBHDS4Driver *ds4p){
  osalDbgCheck((ds4p->state == USBHDS4_STATE_ACTIVE)
      || (ds4p->state == USBHDS4_STATE_READY));

  if (ds4p->state == USBHDS4_STATE_ACTIVE) {
    return;
  }

  osalSysLock();
  chVTResetI(&ds4p->vt);
  usbhEPCloseS(&ds4p->epin);
  usbhEPCloseS(&ds4p->epout);
  chThdDequeueAllI(&ds4p->iq_waiting, Q_RESET);
  chThdDequeueAllI(&ds4p->oq_waiting, Q_RESET);
  osalOsRescheduleS();
  ds4p->state = USBHDS4_STATE_STOP;
  osalSysUnlock();
}

bool DS4_ReadTimeOut(USBHDS4Driver *ds4p, DS4_status_t *data, systime_t timeout) {

  chSysLock();

  if (ds4p->state != USBHDS4_STATE_READY) {
    chSysUnlock();
    return false;
  }
  while (ds4p->iq_counter == 0) {
    if (!usbhURBIsBusy(&ds4p->iq_urb))
      _submitInI(ds4p);
    if (chThdEnqueueTimeoutS(&ds4p->iq_waiting, timeout) != Q_OK) {
      chSysUnlock();
      return false;
    }
  }

  if ((ds4p->iq_counter == 64) && (ds4p->iq_ptr[0] == 0x01)) {
    memcpy(data, &(ds4p->iq_ptr[1]), sizeof(DS4_status_t));

    ds4p->iq_counter = 0;
    _submitInI(ds4p);
    chSchRescheduleS();
    chSysUnlock();
    return true;
  } else {
    chSysUnlock();
    return false;
  }

}

bool DS4_WriteTimeOut(USBHDS4Driver *ds4p, DS4_command_t *data, systime_t timeout){
  chSysLock();

  ds4p->oq_buff[0] = 0x05;
  ds4p->oq_buff[1] = 0xFF;
  memcpy(&(ds4p->oq_buff[4]), data, 7);

  if (ds4p->state != USBHDS4_STATE_READY) {
    chSysUnlock();
    return false;
  }
  while (usbhURBIsBusy(&ds4p->oq_urb)) {
    if (chThdEnqueueTimeoutS(&ds4p->oq_waiting, timeout) != Q_OK) {
      chSysUnlock();
      return false;
    }
  }

  ds4p->oq_counter = 0;

  _submitOutI(ds4p, 32);

  chSysUnlock();
  return true;
}

void usbhds4ObjectInit(USBHDS4Driver *ds4p) {
  osalDbgCheck(ds4p != NULL);
  memset(ds4p, 0, sizeof(*ds4p));
  ds4p->info = &usbhds4ClassDriverInfo;
}

#endif
