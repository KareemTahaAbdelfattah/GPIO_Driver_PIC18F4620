/* 
 * File:   hal_manager_interrupt.c
 * Author: Kareem Taha
 *
 * Created on October 10, 2022, 1:47 PM
 */

/* Section : Includes */
#include "hal_manager_interrupt.h"
 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */
#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable

void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == Interrupt_Enable) && (INTCONbits.INT0IF == Interrupt_Occur)) INT0_ISR();
    if((INTCON3bits.INT2IE == Interrupt_Enable) && (INTCON3bits.INT2IF == Interrupt_Occur)) INT2_ISR();
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1IE == Interrupt_Enable) && (INTCON3bits.INT1IF == Interrupt_Occur)) INT1_ISR();
}

#else

void __interrupt() InterruptManager(void){
    if((INTCONbits.INT0IE == Interrupt_Enable) && (INTCONbits.INT0IF == Interrupt_Occur)) INT0_ISR();
    if((INTCON3bits.INT1IE == Interrupt_Enable) && (INTCON3bits.INT1IF == Interrupt_Occur)) INT1_ISR();
    if((INTCON3bits.INT2IE == Interrupt_Enable) && (INTCON3bits.INT2IF == Interrupt_Occur)) INT2_ISR();
    if((INTCONbits.RBIE == Interrupt_Enable) && (INTCONbits.RBIF == Interrupt_Occur) && (PORTBbits.RB4 == 1)) RB4_ISR();
    if((INTCONbits.RBIE == Interrupt_Enable) && (INTCONbits.RBIF == Interrupt_Occur) && (PORTBbits.RB5 == 1)) RB5_ISR();
    if((INTCONbits.RBIE == Interrupt_Enable) && (INTCONbits.RBIF == Interrupt_Occur) && (PORTBbits.RB6 == 1)) RB6_ISR();
    if((INTCONbits.RBIE == Interrupt_Enable) && (INTCONbits.RBIF == Interrupt_Occur) && (PORTBbits.RB7 == 1)) RB7_ISR();
    if((PIE1bits.ADIE == Interrupt_Enable) && (PIR1bits.ADIF == Interrupt_Occur)) ADC_ISR();
    if((INTCONbits.TMR0IE == Interrupt_Enable) && (INTCONbits.TMR0IF == Interrupt_Occur)) TIMER0_ISR();
    if((PIE1bits.TMR1IE == Interrupt_Enable) && (PIR1bits.TMR1IF == Interrupt_Occur)) TIMER1_ISR();
    if((PIE1bits.TMR2IE == Interrupt_Enable) && (PIR1bits.TMR2IF == Interrupt_Occur)) TIMER2_ISR();
    if((PIE2bits.TMR3IE == Interrupt_Enable) && (PIR2bits.TMR3IF == Interrupt_Occur)) TIMER3_ISR();
    //if((INTCON3bits.INT2IE == Interrupt_Enable) && (INTCON3bits.INT2IF == Interrupt_Occur)) INT2_ISR();
    //if((INTCON3bits.INT2IE == Interrupt_Enable) && (INTCON3bits.INT2IF == Interrupt_Occur)) INT2_ISR();
    //if((INTCON3bits.INT2IE == Interrupt_Enable) && (INTCON3bits.INT2IF == Interrupt_Occur)) INT2_ISR();
}

#endif


 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

