/* 
 * File:   Ecu_motor.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 19, 2022, 4:39 PM
 */

 /* Section : Includes */
#include "ecu_motor.h"


 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */


/**
 * @brief : initialize the pins of motor 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_initialize(const Dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(_dc_motor == NULL) ret = E_NOT_OK;
    else{
        pin_config_t dc_motor_pin_1 = {
            .pin = _dc_motor->two_direction[0].pin,
            .port = _dc_motor->two_direction[0].port,
            .logic = _dc_motor->two_direction[0].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        pin_config_t dc_motor_pin_2 = {
            .pin = _dc_motor->two_direction[1].pin,
            .port = _dc_motor->two_direction[1].port,
            .logic = _dc_motor->two_direction[1].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_direction_init(&dc_motor_pin_1);
        gpio_pin_direction_init(&dc_motor_pin_2);
        gpio_pin_write_logic(&dc_motor_pin_1, dc_motor_pin_1.logic);
        gpio_pin_write_logic(&dc_motor_pin_2, dc_motor_pin_2.logic);
    }
    return ret; 
}


/**
 * @brief : initialize the pin1 of motor as high and pin2 as low 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_turn_left(const Dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    logic_t logic_pin_1 = GPIO_HIGH;
    logic_t logic_pin_2 = GPIO_HIGH;
    if(_dc_motor == NULL) ret = E_NOT_OK;
    else{
        pin_config_t dc_motor_pin_1 = {
            .pin = _dc_motor->two_direction[0].pin,
            .port = _dc_motor->two_direction[0].port,
            .logic = _dc_motor->two_direction[0].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        pin_config_t dc_motor_pin_2 = {
            .pin = _dc_motor->two_direction[1].pin,
            .port = _dc_motor->two_direction[1].port,
            .logic = _dc_motor->two_direction[1].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_write_logic(&dc_motor_pin_1, GPIO_HIGH);
        gpio_pin_write_logic(&dc_motor_pin_2, GPIO_LOW);
    }
    return ret;
}


/**
 * @brief : initialize the pin1 of motor as low and pin2 as high 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_turn_right(const Dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(_dc_motor == NULL) ret = E_NOT_OK;
    else{
        pin_config_t dc_motor_pin_1 = {
            .pin = _dc_motor->two_direction[0].pin,
            .port = _dc_motor->two_direction[0].port,
            .logic = _dc_motor->two_direction[0].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        pin_config_t dc_motor_pin_2 = {
            .pin = _dc_motor->two_direction[1].pin,
            .port = _dc_motor->two_direction[1].port,
            .logic = _dc_motor->two_direction[1].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_write_logic(&dc_motor_pin_1, GPIO_LOW);
        gpio_pin_write_logic(&dc_motor_pin_2, GPIO_HIGH);
    }
    return ret;
}


/**
 * @brief : initialize the pin1 of motor as low and pin2 as low 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_stop(const Dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(_dc_motor == NULL) ret = E_NOT_OK;
    else{
        pin_config_t dc_motor_pin_1 = {
            .pin = _dc_motor->two_direction[0].pin,
            .port = _dc_motor->two_direction[0].port,
            .logic = _dc_motor->two_direction[0].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        pin_config_t dc_motor_pin_2 = {
            .pin = _dc_motor->two_direction[1].pin,
            .port = _dc_motor->two_direction[1].port,
            .logic = _dc_motor->two_direction[1].status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_write_logic(&dc_motor_pin_1, GPIO_LOW);
        gpio_pin_write_logic(&dc_motor_pin_2, GPIO_LOW);
    }
    return ret;
}