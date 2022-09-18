/* 
 * File:   hal_gpio.h
 * Author: Kareem Taha
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:50 PM
 */
 
#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

 /* Section : Includes */
#include "std_types.h"
#include "pic18f4620.h"
#include "device_config.h"
#include "GPIO/hal_gpio_cfg_inter.h"

 /* Section : Macros Definition */

/* Configuration of ports and pins */
#define GPIO_CONFIGRATION_PORT        ENABLE_CONFIG
#define GPIO_CONFIGRATION_PIN         ENABLE_CONFIG

/* max port numbers & pin numbers */
#define MAX_PORT_NUM         5
#define MAX_PIN_NUM          8


 /* Section : Macros Functions Declaration */

/* Bitwise operators */
#define HWREG8(_x)                                 (*((volatile unsigned char *)(_x)))
#define SET_BIT(Register, Pos)                     (Register |= (1 << Pos))
#define CLEAR_BIT(Register, Pos)                   (Register &= ~(1 << Pos))
#define TOGGLE_BIT(Register, Pos)                  (Register ^= (1 << Pos))
#define READ_BIT(Register, Pos)                    ((Register >> Pos) & 1)


 /* Section : Data Types Declaration */

/* Logic of pins */
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

/* Directions of pins */
typedef enum{
    GPIO_OUTPUT_DIRECTION = 0,
    GPIO_INPUT_DIRECTION
}direction_t;

/* pins */
typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

/* ports */
typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;



typedef struct{
    uint8 port : 3;         /*@ref port_index_t */
    uint8 pin  : 3;         /*@ref pin_index_t */
    uint8 direction : 1;    /*@ref direction_t */
    uint8 logic : 1;        /*@ref logic_t */
}pin_config_t;


 /* Section : Function Declaration */

/** My function initialize the direction of pin
    @param : _pin_config_t
    @brief : initialize the direction of pin
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config_t);

/** My function get direction status
    @param : _pin_config_t & pointer to assigned direction status at it
    @brief : assigned direction status at direction_status pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_direction_status(const pin_config_t *_pin_config_t, direction_t *direction_status);

/** My function write logic at pin
    @param : _pin_config_t & logic of pin
    @brief : assigned logic to pin
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic);

/** My function read logic from pin
    @param : _pin_config_t & pointer to assigned logic at it
    @brief : assigned logic of pin at logic pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config_t, logic_t *logic);

/** My function toggle logic at pin
    @param : _pin_config_t
    @brief : toggle logic at pin
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config_t);

/** My function initialize the direction of port
    @param : port & direction_init
    @brief : initialize the direction of port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_direction_init(const port_index_t port, uint8 direction_init);

/** My function get direction status of port
    @param : port & pointer to assigned direction status at it
    @brief : assigned direction status at direction_status pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8 *direction_status);

/** My function write logic at port
    @param : port & logic of port
    @brief : assigned logic to port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic);

/** My function read logic from port
    @param : port & pointer to assigned logic at it
    @brief : assigned logic of port at logic pointer
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_read_logic(const port_index_t port, uint8 *logic);

/** My function toggle logic at port
    @param : port
    @brief : toggle logic at port
    @return : return 1 if initialization made successfully or 0.
*/
STD_ReturnType gpio_port_toggle_logic(const port_index_t port);

#endif	/* HAL_GPIO_H */

