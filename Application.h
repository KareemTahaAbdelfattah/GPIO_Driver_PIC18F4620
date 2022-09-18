/* 
 * File:   Application.h
 * Author: Kareem Taha
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 10:10 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

 /* Section : Includes */
#include "ECU_Layer/Ecu_led.h"
#include "ECU_Layer/ecu_button.h"
#include "ECU_Layer/RELAY/ecu_relay.h"

 /* Section : Macros Definition */

#define _XTAL_FREQ       8000000UL

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

/* initialize any pin with direction & logic */
void Application_initialize(void);

#endif	/* APPLICATION_H */

