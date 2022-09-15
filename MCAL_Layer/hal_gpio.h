/* 
 * File:   hal_gpio.h
 * Author: Kareem Taha
 *
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


#define GPIO_CONFIGRATION_PORT        ENABLE_CONFIG
#define GPIO_CONFIGRATION_PIN         ENABLE_CONFIG

#define BIT_MASK             (uint8)1
#define MAX_PORT_NUM         5
#define MAX_PIN_NUM          8


 /* Section : Macros Functions Declaration */

#define HWREG8(_x)                                 (*((volatile unsigned char *)(_x)))
#define SET_BIT(Register, Pos)                     (Register |= (BIT_MASK << Pos))
#define CLEAR_BIT(Register, Pos)                   (Register &= ~(BIT_MASK << Pos))
#define TOGGLE_BIT(Register, Pos)                  (Register ^= (BIT_MASK << Pos))
#define READ_BIT(Register, Pos)                    ((BIT_MASK << Pos) & Register)


 /* Section : Data Types Declaration */

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_OUTPUT_DIRECTION = 0,
    GPIO_INPUT_DIRECTION
}direction_t;

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

STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config_t);
STD_ReturnType gpio_pin_direction_status(const pin_config_t *_pin_config_t, direction_t *direction_status);
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic);
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config_t, logic_t *logic);
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config_t);


STD_ReturnType gpio_port_direction_init(const port_index_t *port, uint8 direction_init);
STD_ReturnType gpio_port_get_direction_status(const port_index_t *port, uint8 *direction_status);
STD_ReturnType gpio_port_write_logic(const port_index_t *port, uint8 logic);
STD_ReturnType gpio_port_read_logic(const port_index_t *port, uint8 *logic);
STD_ReturnType gpio_port_toggle_logic(const port_index_t *port);

#endif	/* HAL_GPIO_H */

