/* 
 * File:   hal_eeprom.c
 * Author: Kareem Taha
 *
 * Created on October 12, 2022, 11:34 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

 /* Section : Includes */

#include "../std_types.h"
#include "pic18f4620.h"
#include "../device_config.h"
#include "../Interrupt/hal_internal_interrupt.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
STD_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
STD_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

