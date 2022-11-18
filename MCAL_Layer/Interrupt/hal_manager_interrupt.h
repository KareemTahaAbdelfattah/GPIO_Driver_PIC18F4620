/* 
 * File:   hal_manager_interrupt.h
 * Author: Kareem Taha
 *
 * Created on October 10, 2022, 10:48 AM
 */

#ifndef HAL_MANAGER_INTERRUPT_H
#define	HAL_MANAGER_INTERRUPT_H

 /* Section : Includes */

#include "hal_interrupt_cfg.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
#endif	/* HAL_MANAGER_INTERRUPT_H */

