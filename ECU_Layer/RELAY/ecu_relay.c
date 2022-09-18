/* 
 * File:   ecu_relay.h
 * Author: Kareem Taha
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 18, 2022, 7:03 PM
 */


 /* Section : Includes */
#include "ecu_relay.h"



/* Section : Macros Definition */


 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */


 /* Section : Function Declaration */


/**
 * @brief : initialize the pin 
 * @param : relay pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType relay_initialize(const relay_t *relay){
    STD_ReturnType ret = E_OK;
    if(relay == NULL) ret = E_NOT_OK;
    else{
        pin_config_t relayy = {
            .pin = relay->pin,
            .port = relay->port,
            .logic = relay->status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_direction_init(&relayy);
        gpio_pin_write_logic(&relayy, relay->status);
    }
    return ret;
}

/**
 * @brief : initialize the pin as high logic 
 * @param : relay pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType relay_turn_on(const relay_t *relay){
    STD_ReturnType ret = E_OK;
    if(relay == NULL) ret = E_NOT_OK;
    else{
        pin_config_t relayy = {
            .pin = relay->pin,
            .port = relay->port,
            .logic = relay->status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_write_logic(&relayy, GPIO_HIGH);
    }
    return ret;
}


/**
 * @brief : initialize the pin as low logic
 * @param : relay pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType relay_turn_off(const relay_t *relay){
    STD_ReturnType ret = E_OK;
    if(relay == NULL) ret = E_NOT_OK;
    else{
        pin_config_t relayy = {
            .pin = relay->pin,
            .port = relay->port,
            .logic = relay->status,
            .direction = GPIO_OUTPUT_DIRECTION
        };
        gpio_pin_write_logic(&relayy, GPIO_LOW);
    }
    return ret;
}