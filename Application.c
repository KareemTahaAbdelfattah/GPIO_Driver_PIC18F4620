/* 
 * File:   Application.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "Application.h"

/* object of pin0 at portC */
pin_config_t led_1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW    
};

/* object of pin1 at portC */
pin_config_t led_2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of pin2 at portC */
pin_config_t led_3 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of pin3 at portC */
pin_config_t led_4 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of pin4 at portC */
pin_config_t led_5 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN4,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of pin5 at portC */
pin_config_t led_6 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN5,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of pin6 at portC */
pin_config_t led_7 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN6,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

/* object of button at portD */
pin_config_t button_t = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_INPUT_DIRECTION,
    .logic = GPIO_HIGH    
};

/* object of pin7 */
pin_config_t led_8 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN7,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_LOW   
};

STD_ReturnType ret = E_OK;
direction_t led_l_st;
logic_t button1_status;

int main() {
    
    Application_initialize();
    
    ret = gpio_pin_direction_status(&led_1, &led_l_st);
    ret = gpio_pin_direction_status(&button_t, &led_l_st);
    
    while(1){
       ret = gpio_pin_read_logic(&button_t, &button1_status);
       ret = gpio_pin_direction_init(&led_8);
       if(button1_status == GPIO_HIGH) ret = gpio_pin_write_logic(&led_8, GPIO_HIGH);
       else ret = gpio_pin_write_logic(&led_8, GPIO_LOW);
        ret = gpio_pin_write_logic(&led_1, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_2, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_3, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_4, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_5, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_6, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_7, GPIO_HIGH);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_1, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_2, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_3, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_4, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_5, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_6, GPIO_LOW);
        _delay(1000);
        ret = gpio_pin_write_logic(&led_7, GPIO_LOW);
        //gpio_pin_toggle_logic(&led_1);
        _delay(1000);
    }
    return (EXIT_SUCCESS);
}

/* initialize any pin with direction & logic */
void Application_initialize(void){
    ret = gpio_pin_direction_init(&button_t);
    ret = gpio_pin_direction_init(&led_1);
    ret = gpio_pin_direction_init(&led_2);
    ret = gpio_pin_direction_init(&led_3);
    ret = gpio_pin_direction_init(&led_4);
    ret = gpio_pin_direction_init(&led_5);
    ret = gpio_pin_direction_init(&led_6);
    ret = gpio_pin_direction_init(&led_7);
}