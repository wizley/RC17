DRIVERPATH = ./drivers

DRIVERSRC = $(DRIVERPATH)/drivers.c
#DRIVERSRC += $(DRIVERPATH)/dma2d/stm32_dma2d.c
DRIVERSRC += $(DRIVERPATH)/fmc/stm32f4xx_fmc.c
#DRIVERSRC += $(DRIVERPATH)/ltdc/stm32_ltdc.c
DRIVERSRC += $(DRIVERPATH)/qei/qei_lld.c
DRIVERSRC += $(DRIVERPATH)/qei/qei.c
DRIVERSRC += $(DRIVERPATH)/sdram/sdram_driver.c
DRIVERSRC += $(DRIVERPATH)/usb/usbcfg.c

DRIVERINC = $(DRIVERPATH)
#DRIVERINC += $(DRIVERPATH)/dma2d
DRIVERINC += $(DRIVERPATH)/eeprom
DRIVERINC += $(DRIVERPATH)/fmc
#DRIVERINC += $(DRIVERPATH)/ltdc
DRIVERINC += $(DRIVERPATH)/qei
DRIVERINC += $(DRIVERPATH)/sdram
DRIVERINC += $(DRIVERPATH)/usb

# UGFX LLD path
GFXINC += ./drivers/gdisp_lld
GFXINC += ./drivers/gmouse_lld
#GFXINC +=	$(GFXLIB)/drivers/gdisp/STM32LTDC
GFXSRC += ./drivers/gdisp_lld/gdisp_lld_STM32LTDC.c

include $(GFXLIB)/drivers/ginput/touch/FT5x06/driver.mk