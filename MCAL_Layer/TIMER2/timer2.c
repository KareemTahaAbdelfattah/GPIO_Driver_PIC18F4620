
/* 
 * File:   timer2.c
 * Author: Kareem Taha
 *
 * Created on November 9, 2022, 9:14 PM
 */



 /* Section : Includes */
#include "timer2.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*TIMER2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer2_preload_value = 0;


/**
 * @brief : initialize timer2
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_init(const timer2_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /*disable timer2*/
        TIMER2_DISABLE_MODULE();
        /*Prescaler config*/
        T2CONbits.T2CKPS = (_timer->timer2_prescaler);
        /*Postscaler config*/
        T2CONbits.TOUTPS = (_timer->timer2_postscaler);
        /* preload value */
        TMR2 = (_timer->timer2_preload_value);
        timer2_preload_value = (_timer->timer2_preload_value);
        /*________ Interrupt ______*/
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER2_Interrupt_Enable();
        TIMER2_Interrupt_Flag_Clear();
        TIMER2_InterruptHandler = (_timer->TIMER2_InterruptHandler);
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_High_Priority){
            Interrupt_GlobalInterruptHighEnable();
            TIMER2_Interrupt_Priority_High();
        }
        else{
            Interrupt_GlobalInterruptLowEnable();
            TIMER2_Interrupt_Priority_Low();
        }
        #else
        /*Enable Global Interrupt */
        Interrupt_GlobalInterruptEnable();
        /*Enable Peripherals Interrupt */
        Interrupt_PeripheralInterruptEnable();
        #endif
        #endif
        /*enable timer1*/
        TIMER2_ENABLE_MODULE();
    }
    return ret;
}


/**
 * @brief : De initialize timer2
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_Deinit(const timer2_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /* disable timer2*/
        TIMER2_DISABLE_MODULE();
        /*disable interrupt*/
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER2_Interrupt_Disable();
        #endif
    }
    return ret;
}


/**
 * @brief : write value at counter of timer2
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_write_value(const timer2_t *_timer, uint8 _value){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        TMR2 = _value; 
    }
    return ret;
}



/**
 * @brief : read value from counter of timer2
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_read_value(const timer2_t *_timer, uint8 *_value){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        (*_value) = TMR2;
    }
    return ret;
}


/*_____Function of interrupt____*/
void TIMER2_ISR(void){
    TIMER2_Interrupt_Flag_Clear();
    TMR2 = (uint8)(timer2_preload_value);
    if(TIMER2_InterruptHandler){
        TIMER2_InterruptHandler();
    }
}