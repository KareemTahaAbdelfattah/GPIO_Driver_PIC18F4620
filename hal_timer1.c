/* 
 * File:   timer1.c
 * Author: Kareem Taha
 *
 * Created on November 3, 2022, 9:03 AM
 */


 /* Section : Includes */
#include "timer1.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */


 /* Section : Function Declaration */
static inline void Timer1_mode_select(const timer1_t *_timer);


#if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*TIMER1_InterruptHandler)(void) = NULL;
#endif

static uint16 timer1_preload_value = 0;


/**
 * @brief : initialize timer1
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_init(const timer1_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /*disable timer1*/
        TIMER1_DISABLE_MODULE();
        /*Prescaler config*/
        T1CONbits.T1CKPS = (_timer->timer1_prescaler);
        /*timer0 mode select*/
        Timer1_mode_select(_timer);
        /* preload value */
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload_value = (_timer->timer1_preload_value);
        /*________ Interrupt ______*/
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER1_Interrupt_Enable();
        TIMER1_Interrupt_Flag_Clear();
        TIMER1_InterruptHandler = (_timer->TIMER1_InterruptHandler);
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_High_Priority){
            Interrupt_GlobalInterruptHighEnable();
            TIMER1_Interrupt_Priority_High();
        }
        else{
            Interrupt_GlobalInterruptLowEnable();
            TIMER1_Interrupt_Priority_Low();
        }
        #else
        /*Enable Global Interrupt */
        Interrupt_GlobalInterruptEnable();
        /*Enable Peripherals Interrupt */
        Interrupt_PeripheralInterruptEnable();
        #endif
        #endif
        /*enable timer1*/
        TIMER1_ENABLE_MODULE();
    }
    return ret;
}


/**
 * @brief : De initialize timer1
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_Deinit(const timer1_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /* disable timer1*/
        TIMER1_DISABLE_MODULE();
        /*disable interrupt*/
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER1_Interrupt_Disable();
        #endif
    }
    return ret;
}


/**
 * @brief : write value at counter of timer1
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_write_value(const timer1_t *_timer, uint16 _value){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
    }
    return ret;
}



/**
 * @brief : read value from counter of timer1
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_read_value(const timer1_t *_timer, uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 tmr1_low = 0, tmr1_high  = 0;
    if(_timer == NULL || _value == NULL) ret = E_NOT_OK;
    else{
        tmr1_low = TMR1L;
        tmr1_high = TMR1H;
        (*_value) = (uint16)(tmr1_high << 8) + (tmr1_low);
    }
    return ret;
}




/*_____Function of interrupt____*/
void TIMER1_ISR(void){
    TIMER1_Interrupt_Flag_Clear();
    TMR1H = (timer1_preload_value) >> 8;
    TMR1L = (uint8)(timer1_preload_value);
    if(TIMER1_InterruptHandler){
        TIMER1_InterruptHandler();
    }
}

/*____timer mode select & edge____*/
static inline void Timer1_mode_select(const timer1_t *_timer){
    if((_timer->timer1_mode) == TIMER1_SOURCE_TIMER_MOD){
        TIMER1_SOURCE_TIMER_MODE();
    }else{
        TIMER1_SOURCE_COUNTER_MODE();
        if((_timer->timer1_counter_mode) == TIMER1_SYNC_COUNTER_MOD){
            TIMER1_SYNC_COUNTER_MODE();
        }else{
            TIMER1_ASYNC_COUNTER_MODE();
        }
    }
}
