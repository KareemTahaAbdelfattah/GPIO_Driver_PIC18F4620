/* 
 * File:   hal_interrupt_cfg.h
 * Author: Kareem Taha
 *
 * Created on October 6, 2022, 1:47 PM
 */

#ifndef HAL_INTERRUPT_CFG_H
#define	HAL_INTERRUPT_CFG_H



 /* Section : Includes */

#include "../std_types.h"
#include "pic18f4620.h"
#include "../device_config.h"
#include "../hal_gpio.h"
#include "hal_interrupt_gen_cfg.h"

 /* Section : Macros Definition */


#define Interrupt_Enable                          1
#define Interrupt_Disable                         0
#define Interrupt_Occur                           1
#define Interrupt_Not_Occur                       0
#define Interrupt_Priority_Enable                 1
#define Interrupt_Priority_Disable                0

 /* Section : Macros Functions Declaration */



#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/*Enable or disable All Priority levels Interrupt */
#define Interrupt_PriorityLevelsEnable()                 (RCONbits.IPEN = 1)
#define Interrupt_PriorityLevelsDisable()                (RCONbits.IPEN = 0)

/*Enable or disable Global High Interrupt */
#define Interrupt_GlobalInterruptHighEnable()             (INTCONbits.GIEH = 1)
#define Interrupt_GlobalInterruptHighDisable()            (INTCONbits.GIEH = 0)
  
/*Enable or disable Global Low Interrupt */
#define Interrupt_GlobalInterruptLowEnable()              (INTCONbits.GIEL = 1)
#define Interrupt_GlobalInterruptLowDisable()             (INTCONbits.GIEL = 0)
#else

 /*Enable or disable Global Interrupt */
#define Interrupt_GlobalInterruptEnable()             (INTCONbits.GIE = 1)
#define Interrupt_GlobalInterruptDisable()            (INTCONbits.GIE = 0)

/*Enable or disable Peripherals Interrupt */
#define Interrupt_PeripheralInterruptEnable()             (INTCONbits.PEIE = 1)
#define Interrupt_PeripheralInterruptDisable()            (INTCONbits.PEIE = 0)
#endif

 /* Section : Data Types Declaration */

typedef enum{
    INTERRUPT_Low_Priority = 0,
    INTERRUPT_High_Priority,
}Interrupt_Priority_cfg;

 /* Section : Function Declaration */


#endif	/* HAL_INTERRUPT_CFG_H */

