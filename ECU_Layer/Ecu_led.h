/* 
 * File:   Ecu_led.h
 * Author: Kareem Taha
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 10:01 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

 /* Section : Includes */
#include "../MCAL_Layer/hal_gpio.h"
#include "LED/ecu_led_cfg.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
typedef enum{
    LED_LOW,
    LED_HIGH
}led_status_t;

typedef struct{
    uint8 port_name: 4;
    uint8 pin_number: 3;
    uint8 led_status: 1;
}led_t;

 /* Section : Function Declaration */

STD_ReturnType led_initialize(const led_t *led);


STD_ReturnType led_turn_on(const led_t *led);


STD_ReturnType led_turn_off(const led_t *led);


STD_ReturnType led_toggle_logic(const led_t *led);


#endif	/* ECU_LED_H */

