#ifndef __EEPROM_H__
#define __EEPROM_H__

#if (DRIVER_USE_EEPROM && HAL_USE_I2C) || defined(__DOXYGEN__)

#include "ch.h"

#define EEPROM_DRV_TABLE_SIZE 1

#define _eeprom_file_config_data                                            \
  /* Lower barrier of file in EEPROM memory array. */                       \
  uint32_t        barrier_low;                                              \
  /* Higher barrier of file in EEPROM memory array. */                      \
  uint32_t        barrier_hi;                                               \
  /* Size of memory array in bytes. */                                      \
  uint32_t        size;                                                     \
  /* Size of single page in bytes. */                                       \
  uint16_t        pagesize;                                                 \
  /* Time needed by IC for single byte/page writing. */                     \
  systime_t       write_time;
  
//typedef uint32_t fileoffset_t;
//#define FILE_OK   0
//#define FILE_ERROR   0xFFFFFFFFUL

typedef struct {
  _eeprom_file_config_data
} EepromFileConfig;

/**
 * @brief   @p EepromFileStream specific data.
 */
#define _eeprom_file_stream_data                                            \
  _base_sequential_stream_data                                                    \
  uint32_t                    errors;                                       \
  uint32_t                    position;                                     \

/**
 * @extends BaseFileStreamVMT
 *
 * @brief   @p EepromFileStream virtual methods table.
 */
struct EepromFileStreamVMT {
  _base_sequential_stream_methods
};

/**
 * @extends BaseFileStream
 *
 * @brief   EEPROM file stream driver class.
 * @details This class extends @p BaseFileStream by adding some fields.
 */
typedef struct {
  /** @brief Virtual Methods Table.*/
  const struct EepromFileStreamVMT *vmt;
  _eeprom_file_stream_data
  /** pointer to config object, must be overwritten by all derived classes.*/
  const EepromFileConfig *cfg;
} EepromFileStream;

/**
 * @brief   Low level device descriptor.
 */
typedef struct {
  const char                          *name;
  const struct EepromFileStreamVMT   *efsvmt;
} EepromDevice;

#if HAL_USE_I2C || defined(__DOXYGEN__)

/**
 * @extends EepromFileConfig
 */
typedef struct {
  _eeprom_file_config_data
  /**
   * Driver connected to IC.
   */
  I2CDriver     *i2cp;
  /**
   * Address of IC on I2C bus.
   */
  i2caddr_t     addr;
  /**
   * Pointer to write buffer. The safest size is (pagesize + 2)
   */
  uint8_t       *write_buf;
} I2CEepromFileConfig;

/**
 * @brief   @p I2CEepromFileStream specific data.
 */
#define _eeprom_file_stream_data_i2c                                       \
  _eeprom_file_stream_data

/**
 * @extends EepromFileStream
 *
 * @brief   EEPROM file stream driver class for I2C device.
 */
typedef struct {
  const struct EepromFileStreamVMT *vmt;
  _eeprom_file_stream_data_i2c
  /* Overwritten parent data member. */
  const I2CEepromFileConfig *cfg;
} I2CEepromFileStream;


/**
 * Open I2C EEPROM IC as file and return pointer to the file stream object
 * @note      Fucntion allways successfully open file. All checking makes
 *            in read/write functions.
 */
#define I2CEepromFileOpen(efs, eepcfg, eepdev) \
  EepromFileOpen((EepromFileStream *)efs, (EepromFileConfig *)eepcfg, eepdev);

#endif /* HAL_USE_I2C */


const EepromDevice *EepromFindDevice(const char *name);

EepromFileStream *EepromFileOpen(EepromFileStream *efs,
                                 const EepromFileConfig *eepcfg,
                                 const EepromDevice *eepdev);

uint8_t  EepromReadByte(EepromFileStream *efs);
uint16_t EepromReadHalfword(EepromFileStream *efs);
uint32_t EepromReadWord(EepromFileStream *efs);
size_t EepromWriteByte(EepromFileStream *efs, uint8_t data);
size_t EepromWriteHalfword(EepromFileStream *efs, uint16_t data);
size_t EepromWriteWord(EepromFileStream *efs, uint32_t data);

fileoffset_t eepfs_getsize(void *ip);
fileoffset_t eepfs_getposition(void *ip);
fileoffset_t eepfs_lseek(void *ip, fileoffset_t offset);
uint32_t eepfs_close(void *ip);
int eepfs_geterror(void *ip);
msg_t eepfs_put(void *ip, uint8_t b);
msg_t eepfs_get(void *ip);

void eepromInit(void);

#endif

#endif /* __EEPROM_H__ */
