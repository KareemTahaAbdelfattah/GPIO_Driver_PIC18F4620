/* 
 * File:   Application.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "Application.h"

STD_ReturnType ret = E_OK;

relay_t relay1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .status = RELAY_OFF
};
relay_t relay2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .status = RELAY_OFF
};


int main() { 
    Application_initialize();
    while(1){
        ret = relay_turn_on(&relay1);
        _delay(5000000);
        ret = relay_turn_off(&relay1);
        ret = relay_turn_on(&relay2);
        _delay(5000000);
        ret = relay_turn_off(&relay2);
    }
    return (EXIT_SUCCESS);
}

/* initialize any pin with direction & logic */
void Application_initialize(void){
    ret = relay_initialize(&relay1);
    ret = relay_initialize(&relay2);
}