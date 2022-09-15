/* 
 * File:   hal_gpio.c
 * Author: Kareem Taha Abdelfatah Mohammed
 *
 * Created on September 13, 2022, 9:10 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config_t){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        switch(_pin_config_t->direction){
            case GPIO_OUTPUT_DIRECTION:
                CLEAR_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
                break;
            case GPIO_INPUT_DIRECTION:
                SET_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
STD_ReturnType gpio_pin_direction_status(const pin_config_t *_pin_config_t, direction_t *direction_status){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || direction_status == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
       *direction_status = READ_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}
#endif

#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret; 
}
#endif

#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config_t, logic_t *logic){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL  || logic == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        *logic = READ_BIT(*port_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}
#endif

#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config_t){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        
    }
    
    return ret;  
}
#endif


#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG
STD_ReturnType gpio_port_direction_init(const port_index_t *port, uint8 direction_init){
    STD_ReturnType ret = E_OK;
    if(port == NULL || direction_init == NULL) ret = E_NOT_OK;
    else{
        
    }
    
    return ret; 
}
#endif


#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG
STD_ReturnType gpio_port_get_direction_status(const port_index_t *port, uint8 *direction_status){
    STD_ReturnType ret = E_OK;
    if(port == NULL || direction_status == NULL) ret = E_NOT_OK;
    else{
        
    }
    
    return ret;
}
#endif


#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG
STD_ReturnType gpio_port_write_logic(const port_index_t *port, uint8 logic){
    STD_ReturnType ret = E_OK;
    if(port == NULL || logic == NULL) ret = E_NOT_OK;
    else{
        
    }
    
    return ret; 
}
#endif


#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG
STD_ReturnType gpio_port_read_logic(const port_index_t *port, uint8 *logic){
    STD_ReturnType ret = E_OK;
    if(port == NULL || logic == NULL) ret = E_NOT_OK;
    else{
        
    }
    
    return ret; 
}
#endif


#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG
STD_ReturnType gpio_port_toggle_logic(const port_index_t *port){
    STD_ReturnType ret = E_OK;
    if(port == NULL) ret = E_NOT_OK;
    else{
        
    }
    
    return ret; 
}
#endif