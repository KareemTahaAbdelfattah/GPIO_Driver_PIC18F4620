/* 
 * File:   hal_internal_interrupt.h
 * Author: Kareem Taha
 *
 * Created on October 6, 2022, 1:47 PM
 */

#ifndef HAL_INTERRUPT_H
#define	HAL_INTERRUPT_H

 /* Section : Includes */

#include "hal_interrupt_cfg.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

/*________________________ ADC ____________________*/

#if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for ADC module */
#define ADC_Interrupt_Disable()                (PIE1bits.ADIE = 0)
/* set interrupt enable for ADC module */
#define ADC_Interrupt_Enable()                 (PIE1bits.ADIE = 1)
/* clear interrupt flag for ADC module */
#define ADC_Interrupt_Flag_Clear()             (PIR1bits.ADIF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set ADC module interrupt -> high priority */
#define ADC_Interrupt_Priority_High()          (IPR1bits.ADIP = 1)
/* set ADC module interrupt -> low priority */
#define ADC_Interrupt_Priority_Low()           (IPR1bits.ADIP = 0)
#endif

#endif



/*________________________ TIMER0 ____________________*/

#if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER0 module */
#define TIMER0_Interrupt_Disable()                (INTCONbits.TMR0IE = 0)
/* set interrupt enable for TIMER0 module */
#define TIMER0_Interrupt_Enable()                 (INTCONbits.TMR0IE = 1)
/* clear interrupt flag for TIMER0 module */
#define TIMER0_Interrupt_Flag_Clear()             (INTCONbits.TMR0IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER0 module interrupt -> high priority */
#define TIMER0_Interrupt_Priority_High()          (INTCON2bits.TMR0IP = 1)
/* set TIMER0 module interrupt -> low priority */
#define TIMER0_Interrupt_Priority_Low()           (INTCON2bits.TMR0IP = 0)
#endif

#endif



/*________________________ TIMER1 ____________________*/

#if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER1 module */
#define TIMER1_Interrupt_Disable()                (PIE1bits.TMR1IE = 0)
/* set interrupt enable for TIMER1 module */
#define TIMER1_Interrupt_Enable()                 (PIE1bits.TMR1IE = 1)
/* clear interrupt flag for TIMER1 module */
#define TIMER1_Interrupt_Flag_Clear()             (PIR1bits.TMR1IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER1 module interrupt -> high priority */
#define TIMER1_Interrupt_Priority_High()          (IPR1bits.TMR1IP = 1)
/* set TIMER1 module interrupt -> low priority */
#define TIMER1_Interrupt_Priority_Low()           (IPR1bits.TMR1IP = 0)
#endif

#endif





/*________________________ TIMER2 ____________________*/

#if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER2 module */
#define TIMER2_Interrupt_Disable()                (PIE1bits.TMR2IE = 0)
/* set interrupt enable for TIMER2 module */
#define TIMER2_Interrupt_Enable()                 (PIE1bits.TMR2IE = 1)
/* clear interrupt flag for TIMER2 module */
#define TIMER2_Interrupt_Flag_Clear()             (PIR1bits.TMR2IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER2 module interrupt -> high priority */
#define TIMER2_Interrupt_Priority_High()          (IPR1bits.TMR2IP = 1)
/* set TIMER2 module interrupt -> low priority */
#define TIMER2_Interrupt_Priority_Low()           (IPR1bits.TMR2IP = 0)
#endif

#endif




/*________________________ TIMER3 ____________________*/

#if TIMER3_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER3 module */
#define TIMER3_Interrupt_Disable()                (PIE2bits.TMR3IE = 0)
/* set interrupt enable for TIMER3 module */
#define TIMER3_Interrupt_Enable()                 (PIE2bits.TMR3IE = 1)
/* clear interrupt flag for TIMER3 module */
#define TIMER3_Interrupt_Flag_Clear()             (PIR2bits.TMR3IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER3 module interrupt -> high priority */
#define TIMER3_Interrupt_Priority_High()          (IPR2bits.TMR3IP = 1)
/* set TIMER3 module interrupt -> low priority */
#define TIMER3_Interrupt_Priority_Low()           (IPR2bits.TMR3IP = 0)
#endif

#endif
 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

#endif	/* HAL_INTERRUPT_H */

