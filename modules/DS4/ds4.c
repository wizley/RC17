#include "ch.h"
#include "hal.h"
#include "usbh/dev/ds4.h"
#include "ds4.h"
#include "log.h"

DS4_status_t DS4;
static DS4_command_t cmd = {.led_r = 255, .led_g = 20, .led_b = 147};
static bool need_write = false;
static bool ds4_connected = false;

static THD_WORKING_AREA(waDS4, 1024);
static THD_FUNCTION(DS4Thd, arg) {

  (void)arg;
  chRegSetThreadName("DS4 Thread");

  USBHDS4Driver *const ds4p = &USBHDS4[0];

#if USBHDS4_DEBUG_ENABLE_INFO
  chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "Waiting for connection...\r\n");
#endif

  while (TRUE) {
    switch (ds4p->state) {
    case USBHDS4_STATE_UNINIT:
    case USBHDS4_STATE_STOP:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD,
          "DS4 Disconnected or Stopped.\r\n");
#endif
      if(ds4_connected)
        log_i("\nDS4 Disconnected or Stopped\n");
      ds4_connected = false;
      chThdSleepMilliseconds(500);
      break;
    case USBHDS4_STATE_ACTIVE:
#if USBHDS4_DEBUG_ENABLE_INFO
      chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 started.\r\n");
#endif
      log_i("\nDS4 connected\n");
      ds4_connected = true;
      usbhds4Start(ds4p);
      chThdSleepMilliseconds(20);
      DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
      chThdSleepMilliseconds(100);
      break;
    case USBHDS4_STATE_READY:
      if (!DS4_ReadTimeOut(ds4p, &DS4, MS2ST(50))){
#if USBHDS4_DEBUG_ENABLE_INFO
        chprintf((BaseSequentialStream *) &USBH_DEBUG_SD, "DS4 Read Timeout\r\n");
#endif
      }
      if(need_write){
        DS4_WriteTimeOut(ds4p, &cmd, MS2ST(10));
        need_write = false;
      }
      chThdSleepMilliseconds(10);
    }
  }
}

void DS4_Start(void){
  usbhds4ObjectInit(&USBHDS4[0]);
  chThdCreateStatic(waDS4, sizeof(waDS4), NORMALPRIO,
                        DS4Thd, NULL);
}

void DS4_SetLED(uint8_t r, uint8_t g, uint8_t b){
  cmd.led_r = r;
  cmd.led_g = g;
  cmd.led_b = b;
  need_write = true;
}

void DS4_SetFlash(uint8_t ontime, uint8_t offtime){
  cmd.flash_on = ontime;
  cmd.flash_off = offtime;
  need_write = true;
}

void DS4_SetRumble(uint8_t small, uint8_t big){
  cmd.rumble_small = small;
  cmd.rumble_big = big;
  need_write = true;
}

bool DS4_IsConnected(void){
  return ds4_connected;
}
