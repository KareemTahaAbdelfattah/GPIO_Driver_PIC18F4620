/* 
 * File:   hal_gpio.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "hal_gpio.h"


/* special registers of pins & ports */
volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* Configuration of interface of PIN */
#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG

/** My function initialize the direction of pin
    @param : _pin_config_t
    @brief : initialize the direction of pin
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config_t){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || (_pin_config_t->port > (MAX_PORT_NUM - 1)) || (_pin_config_t->pin > (MAX_PIN_NUM - 1))) ret = E_NOT_OK;
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


/* Configuration of interface of PIN */
#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG

/** My function get direction status
    @param : _pin_config_t & pointer to assigned direction status at it
    @brief : assigned direction status at direction_status pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_direction_status(const pin_config_t *_pin_config_t, direction_t *direction_status){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || direction_status == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
       *direction_status = READ_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}
#endif


/* Configuration of interface of PIN */
#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG
/** My function write logic at pin
    @param : _pin_config_t & logic of pin
    @brief : assigned logic to pin
    @return : return 1 if initialization made successfully or 0.
*/

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

/* Configuration of interface of PIN */
#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG

/** My function read logic from pin
    @param : _pin_config_t & pointer to assigned logic at it
    @brief : assigned logic of pin at logic pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config_t, logic_t *logic){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL  || logic == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        *logic = READ_BIT(*port_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}
#endif

/* Configuration of interface of PIN */
#if GPIO_CONFIGRATION_PIN==ENABLE_CONFIG

/** My function toggle logic at pin
    @param : _pin_config_t
    @brief : toggle logic at pin
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config_t){
    STD_ReturnType ret = E_OK;
    if(_pin_config_t == NULL || (_pin_config_t->port > MAX_PORT_NUM - 1) || (_pin_config_t->pin > MAX_PIN_NUM - 1)) ret = E_NOT_OK;
    else{
        TOGGLE_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;  
}
#endif


/* Configuration of interface of PORT */
#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG

/** My function initialize the direction of port
    @param : port & direction_init
    @brief : initialize the direction of port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_direction_init(const port_index_t port, uint8 direction_init){
    STD_ReturnType ret = E_OK;
    if(port > MAX_PORT_NUM - 1) ret = E_NOT_OK;
    else{
        *tris_register[port] = direction_init;
    }
    return ret; 
}
#endif

/* Configuration of interface of PORT */
#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG

/** My function get direction status of port
    @param : port & pointer to assigned direction status at it
    @brief : assigned direction status at direction_status pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8 *direction_status){
    STD_ReturnType ret = E_OK;
    if(direction_status == NULL || (port > MAX_PORT_NUM - 1)) ret = E_NOT_OK;
    else{
       *direction_status =  *tris_register[port];
    }
    return ret;
}
#endif

/* Configuration of interface of PORT */
#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG


/** My function write logic at port
    @param : port & logic of port
    @brief : assigned logic to port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic){
    STD_ReturnType ret = E_OK;
    if(port > MAX_PORT_NUM - 1) ret = E_NOT_OK;
    else{
        *lat_register[port] = logic;
    }
    return ret; 
}
#endif


/* Configuration of interface of PORT */
#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG

/** My function read logic from port
    @param : port & pointer to assigned logic at it
    @brief : assigned logic of port at logic pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_read_logic(const port_index_t port, uint8 *logic){
    STD_ReturnType ret = E_OK;
    if((port > MAX_PORT_NUM - 1) || logic == NULL) ret = E_NOT_OK;
    else{
        *logic = *lat_register[port];
    }
    return ret; 
}
#endif

/* Configuration of interface of PORT */
#if GPIO_CONFIGRATION_PORT==ENABLE_CONFIG

/** My function toggle logic at port
    @param : port
    @brief : toggle logic at port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_toggle_logic(const port_index_t port){
    STD_ReturnType ret = E_OK;
    if(port > MAX_PORT_NUM - 1) ret = E_NOT_OK;
    else{
        *lat_register[port] ^= 0xFF;
    }
    return ret; 
}
#endif