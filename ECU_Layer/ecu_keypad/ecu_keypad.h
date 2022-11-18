/* 
 * File:   ecu_keypad.h
 * Author: Kareem Taha
 *
 * Created on September 21, 2022, 1:06 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

 /* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../ECU_Layer/../MCAL_Layer/hal_gpio.h"

 /* Section : Macros Definition */
#define ECU_KEYPAD_ROW           4
#define ECU_KEYPAD_Columns       4

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW];
    pin_config_t keypad_colomns_pins[ECU_KEYPAD_Columns];
}keypad_t;

 /* Section : Function Declaration */
STD_ReturnType keypad_initialize(const keypad_t *_keypad);
STD_ReturnType keypad_get_value(const keypad_t *_keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

