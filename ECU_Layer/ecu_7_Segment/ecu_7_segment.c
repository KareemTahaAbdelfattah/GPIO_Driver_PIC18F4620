/* 
 * File:   ecu_7_segment.c
 * Author: Kareem Taha
 *
 * Created on September 20, 2022, 11:06 AM
 */

 /* Section : Includes */
#include "ecu_7_segment.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */


STD_ReturnType segment_initialize(const segment_t *_segment){
    STD_ReturnType ret = E_OK;
    if(_segment == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_direction_init(&(_segment->segment_pins[0]));
        gpio_pin_direction_init(&(_segment->segment_pins[1]));
        gpio_pin_direction_init(&(_segment->segment_pins[2]));
        gpio_pin_direction_init(&(_segment->segment_pins[3]));
        gpio_pin_write_logic(&(_segment->segment_pins[0]), (_segment->segment_pins[0].logic));
        gpio_pin_write_logic(&(_segment->segment_pins[1]), (_segment->segment_pins[1].logic));
        gpio_pin_write_logic(&(_segment->segment_pins[2]), (_segment->segment_pins[2].logic));
        gpio_pin_write_logic(&(_segment->segment_pins[3]), (_segment->segment_pins[3].logic));
    }
    return ret;
}
STD_ReturnType segment_write_num(const segment_t *_segment, uint8 _number){
    STD_ReturnType ret = E_OK;
    if(_segment == NULL || _number > 9) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(_segment->segment_pins[0]), (_number & 0x01));
        gpio_pin_write_logic(&(_segment->segment_pins[1]), ((_number >> 1) & 0x02));
        gpio_pin_write_logic(&(_segment->segment_pins[2]), ((_number >> 2) & 0x03));
        gpio_pin_write_logic(&(_segment->segment_pins[3]), ((_number >> 3) & 0x04));
    }
    return ret;
}