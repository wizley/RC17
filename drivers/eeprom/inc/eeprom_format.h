/*
 * eeprom_address.h
 *
 *  Created on: Jun 3, 2017
 *      Author: Melvin
 */

#ifndef DRIVERS_EEPROM_INC_EEPROM_FORMAT_H_
#define DRIVERS_EEPROM_INC_EEPROM_FORMAT_H_

#define _24LC02_SIZE_      256
//#define _24LC02_PAGESIZE_  8
#define _24LC024H_PAGESIZE_  16


/*EEPROM Address Format definition must follow EEPROM format.xlsx*/

#define _PROM_CRC_VALUE (0x00)
#define _PROM_LCD_BRIGHTNESS (0x01)


#endif /* DRIVERS_EEPROM_INC_EEPROM_FORMAT_H_ */
