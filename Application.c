/* 
 * File:   Application.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "Application.h"

STD_ReturnType ret = E_OK;

button_t btn_1 = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_INPUT_DIRECTION,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};


led_t led_1 = {
    .port_name = PORTC_INDEX,
    .pin_number = GPIO_PIN0,
    .led_status = LED_LOW      
};
led_t led_2 = {
    .port_name = PORTC_INDEX,
    .pin_number = GPIO_PIN1,
    .led_status = LED_LOW      
};

button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_high_valid_status = BUTTON_RELEASED;
button_state_t btn_high_last_valid_status = BUTTON_RELEASED;


uint32 btn_high_valid = 0;
uint8 Program_Selected = 0;

void program_1(void){
    led_turn_on(&led_1);
    _delay(1000);
    led_turn_off(&led_1);
    _delay(1000);
}

void program_2(void){
    uint8 counter = 0;
    for(counter = 0; counter < 2; counter ++){
        led_turn_on(&led_1);
        _delay(1000);
        led_turn_off(&led_1);
        _delay(1000);
    }
}

void program_3(void){
    uint8 counter = 0;
    for(counter = 0; counter < 3; counter ++){
        led_turn_on(&led_1);
        _delay(1000);
        led_turn_off(&led_1);
        _delay(1000);
    }
}
int main() { 
    Application_initialize();

    while(1){
        
        ret = button_read_state(&btn_1, &btn_high_status);
        
        if(BUTTON_PRESSED == btn_high_status){
            btn_high_valid++;
            if(btn_high_valid > 500){
                btn_high_valid_status = BUTTON_PRESSED;
            }
        }
        else{
            btn_high_valid = 0;
            btn_high_valid_status = BUTTON_RELEASED;
        }
        
        if(btn_high_valid_status != btn_high_last_valid_status){
            btn_high_last_valid_status = btn_high_valid_status;
            if(BUTTON_PRESSED == btn_high_valid_status){
                if(3 == Program_Selected){
                    Program_Selected = 0;
                }
                
                Program_Selected++;
                switch(Program_Selected){
                    case 1 : program_1(); break;
                    case 2 : program_2(); break;
                    case 3 : program_3(); break;
                    default : break; /* Nothing */
                }
            }
        }

        
        
    }
    return (EXIT_SUCCESS);
}

/* initialize any pin with direction & logic */
void Application_initialize(void){
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = button_initialize(&btn_1);
}