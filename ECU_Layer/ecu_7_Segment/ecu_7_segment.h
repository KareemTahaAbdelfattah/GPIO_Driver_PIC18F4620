/* 
 * File:   ecu_7_segment.h
 * Author: Kareem Taha
 *
 * Created on September 20, 2022, 11:07 AM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

 /* Section : Includes */
#include "ecu_7_segment_cfg.h"
#include "../../ECU_Layer/../MCAL_Layer/hal_gpio.h"
 /* Section : Macros Definition */
#define SEGMENT_PIN0  0
#define SEGMENT_PIN1  1
#define SEGMENT_PIN2  2
#define SEGMENT_PIN3  3

 /* Section : Macros Functions Declaration */


 /* Section : Data Types Declaration */
typedef enum{
    SEGMENT_COM_ANODE,
    SEGMENT_COM_CATHODE,       
}segment_type_t;


typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;    
}segment_t;

 /* Section : Function Declaration */

STD_ReturnType segment_initialize(const segment_t *_segment);
STD_ReturnType segment_write_num(const segment_t *_segment, uint8 _number);

#endif	/* ECU_7_SEGMENT_H */

