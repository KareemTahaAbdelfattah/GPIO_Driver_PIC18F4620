/* 
 * File:   Ecu_led.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

 /* Section : Includes */
#include "Ecu_led.h"


 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

STD_ReturnType led_initialize(const led_t *led){
    STD_ReturnType ret = E_OK;
    if(led == NULL) ret = E_NOT_OK;
    else{
       pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin_number,
            .direction = GPIO_OUTPUT_DIRECTION,
            .logic = led->led_status
        };
        gpio_pin_direction_init(&pin_obj);
        gpio_pin_write_logic(&pin_obj, led->led_status);
    }
    return ret;
}


STD_ReturnType led_turn_on(const led_t *led){
    STD_ReturnType ret = E_OK;
    
    if(led == NULL) ret = E_NOT_OK;
    else{
       pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin_number,
            .direction = GPIO_OUTPUT_DIRECTION,
            .logic = led->led_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;  
}


STD_ReturnType led_turn_off(const led_t *led){
    STD_ReturnType ret = E_OK;
    if(led == NULL) ret = E_NOT_OK;
    else{
       pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin_number,
            .direction = GPIO_OUTPUT_DIRECTION,
            .logic = led->led_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}


STD_ReturnType led_toggle_logic(const led_t *led){
    STD_ReturnType ret = E_OK;
    if(led == NULL) ret = E_NOT_OK;
    else{
       pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin_number,
            .direction = GPIO_OUTPUT_DIRECTION,
            .logic = led->led_status
        };
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}

