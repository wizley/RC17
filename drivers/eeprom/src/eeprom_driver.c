#include "ch.h"
#include "hal.h"
#include "eeprom_driver.h"
#include <string.h>

#if (DRIVER_USE_EEPROM && HAL_USE_I2C) || defined(__DOXYGEN__)

extern EepromDevice eepdev_24xx;

EepromDevice *__eeprom_drv_table[] = {
  &eepdev_24xx
};


/**
 * @breif  Find low level EEPROM device by id.
 */
const EepromDevice *EepromFindDevice(const char *name) {

  int i;
  const EepromDevice *drv;

  osalDbgCheck(name != NULL);

  for (i = 0; i < EEPROM_DRV_TABLE_SIZE; i++) {
    drv = __eeprom_drv_table[i];
    if (drv->name != NULL && strcmp(drv->name, name) == 0) {
      return drv;
    }
  }

  return NULL;
}

/**
 * Open EEPROM IC as file and return pointer to the file stream object
 * @note      Fucntion allways successfully open file. All checking makes
 *            in read/write functions.
 */
EepromFileStream *EepromFileOpen(EepromFileStream *efs,
                                 const EepromFileConfig *eepcfg,
                                 const EepromDevice *eepdev) {

  osalDbgAssert((efs != NULL) && (eepcfg != NULL) && (eepdev != NULL) &&
             (eepdev->efsvmt != NULL), "EepromFileOpen");
  osalDbgAssert(efs->vmt != eepdev->efsvmt, "file allready opened");
  osalDbgAssert(eepcfg->barrier_hi > eepcfg->barrier_low, "wrong barriers");
  osalDbgAssert(eepcfg->pagesize < eepcfg->size, "pagesize can not be lager than EEPROM size");
  osalDbgAssert(eepcfg->barrier_hi <= eepcfg->size, "barrier out of bounds");

  efs->vmt      = eepdev->efsvmt;
  efs->cfg      = eepcfg;
  efs->errors   = FILE_OK;
  efs->position = 0;
  return (EepromFileStream *)efs;
}

uint8_t EepromReadByte(EepromFileStream *efs) {

  uint8_t buf;
  streamRead(efs, &buf, sizeof(buf));
  return buf;
}

uint16_t EepromReadHalfword(EepromFileStream *efs) {

  uint16_t buf;
  streamRead(efs, (uint8_t *)&buf, sizeof(buf));
  return buf;
}

uint32_t EepromReadWord(EepromFileStream *efs) {

  uint32_t buf;
  streamRead(efs, (uint8_t *)&buf, sizeof(buf));
  return buf;
}

size_t EepromWriteByte(EepromFileStream *efs, uint8_t data) {

  return streamWrite(efs, &data, sizeof(data));
}

size_t EepromWriteHalfword(EepromFileStream *efs, uint16_t data) {

  return streamWrite(efs, (uint8_t *)&data, sizeof(data));
}

size_t EepromWriteWord(EepromFileStream *efs, uint32_t data) {

  return streamWrite(efs, (uint8_t *)&data, sizeof(data));
}

fileoffset_t eepfs_getsize(void *ip) {

  uint32_t h, l;

  osalDbgCheck((ip != NULL) && (((EepromFileStream *)ip)->vmt != NULL) &&
             (((EepromFileStream *)ip)->cfg != NULL));

  h = ((EepromFileStream *)ip)->cfg->barrier_hi;
  l = ((EepromFileStream *)ip)->cfg->barrier_low;
  return  h - l;
}

fileoffset_t eepfs_getposition(void *ip) {

  osalDbgCheck((ip != NULL) && (((EepromFileStream *)ip)->vmt != NULL));

  return ((EepromFileStream *)ip)->position;
}

fileoffset_t eepfs_lseek(void *ip, fileoffset_t offset) {

  uint32_t size;

  osalDbgCheck((ip != NULL) && (((EepromFileStream *)ip)->vmt != NULL));

  size = eepfs_getsize(ip);
  if (offset > size)
    offset = size;
  ((EepromFileStream *)ip)->position = offset;
  return offset;
}

uint32_t eepfs_close(void *ip) {

  osalDbgCheck((ip != NULL) && (((EepromFileStream *)ip)->vmt != NULL));

  ((EepromFileStream *)ip)->errors   = FILE_OK;
  ((EepromFileStream *)ip)->position = 0;
  ((EepromFileStream *)ip)->vmt      = NULL;
  ((EepromFileStream *)ip)->cfg      = NULL;
  return FILE_OK;
}

int eepfs_geterror(void *ip) {

  osalDbgCheck((ip != NULL) && (((EepromFileStream *)ip)->vmt != NULL));
  return ((EepromFileStream *)ip)->errors;
}

msg_t eepfs_put(void *ip, uint8_t b) {

  (void)ip;
  (void)b;
  return 0;
}

msg_t eepfs_get(void *ip) {

  (void)ip;
  return 0;
}

#endif

