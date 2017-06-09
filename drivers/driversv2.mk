DRIVERPATH = ./drivers

DRIVERSRC = $(DRIVERPATH)/drivers.c
DRIVERSRC += $(DRIVERPATH)/fmc/stm32f746xx_fmc.c
DRIVERSRC += $(DRIVERPATH)/qei/qei_lld.c
DRIVERSRC += $(DRIVERPATH)/qei/qei.c
DRIVERSRC += $(DRIVERPATH)/sdram/sdram_driver.c
#DRIVERSRC += $(DRIVERPATH)/usb/usbcfg.c
DRIVERSRC += $(DRIVERPATH)/crc/crc_lld.c
DRIVERSRC += $(DRIVERPATH)/crc/crcsw.c
DRIVERSRC += $(DRIVERPATH)/crc/crc.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh_lld.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_debug.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_desciter.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_hub.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_msd.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_ftdi.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_uvc.c
DRIVERSRC += $(DRIVERPATH)/usbhost/usbh/usbh_ds4.c
DRIVERSRC += $(DRIVERPATH)/eeprom/src/eeprom_driver.c
DRIVERSRC += $(DRIVERPATH)/eeprom/src/24xx_driver.c

DRIVERINC = $(DRIVERPATH)
DRIVERINC += $(DRIVERPATH)/eeprom
DRIVERINC += $(DRIVERPATH)/fmc
DRIVERINC += $(DRIVERPATH)/qei
DRIVERINC += $(DRIVERPATH)/sdram
#DRIVERINC += $(DRIVERPATH)/usb
DRIVERINC += $(DRIVERPATH)/crc
DRIVERINC += $(DRIVERPATH)/usbhost
DRIVERINC += $(DRIVERPATH)/eeprom/inc

# UGFX LLD path
GFXINC += ./drivers/gdisp_lld
GFXINC += ./drivers/gmouse_lld
GFXSRC += ./drivers/gdisp_lld/gdisp_lld_STM32LTDC.c

include $(GFXLIB)/drivers/ginput/touch/FT5x06/driver.mk
