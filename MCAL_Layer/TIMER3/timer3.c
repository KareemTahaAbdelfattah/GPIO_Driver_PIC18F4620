/* 
 * File:   timer3.c
 * Author: Kareem Taha
 *
 * Created on November 18, 2022, 5:41 PM
 */



 /* Section : Includes */
#include "timer3_hal.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

static inline void Timer3_mode_select(const timer3_t *_timer);

#if TIMER3_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*TIMER3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload_value = 0;

/**
 * @brief : initialize timer3
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer3_init(const timer3_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /*disable timer3*/
        TIMER3_DISABLE_MODULE();
        /*Prescaler config*/
        T3CONbits.T3CKPS = (_timer->timer3_prescaler);
        /*timer3 mode select*/
        Timer3_mode_select(_timer);
        /* preload value */
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload_value = (_timer->timer3_preload_value);
        /*________ Interrupt ______*/
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER3_Interrupt_Enable();
        TIMER3_Interrupt_Flag_Clear();
        TIMER3_InterruptHandler = (_timer->TIMER3_InterruptHandler);
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_High_Priority){
            Interrupt_GlobalInterruptHighEnable();
            TIMER3_Interrupt_Priority_High();
        }
        else{
            Interrupt_GlobalInterruptLowEnable();
            TIMER3_Interrupt_Priority_Low();
        }
        #else
        /*Enable Global Interrupt */
        Interrupt_GlobalInterruptEnable();
        /*Enable Peripherals Interrupt */
        Interrupt_PeripheralInterruptEnable();
        #endif
        #endif
        /*enable timer3*/
        TIMER3_ENABLE_MODULE();
    }
    return ret;
}


/**
 * @brief : De initialize timer3
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer3_Deinit(const timer3_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /* disable timer1*/
        TIMER3_DISABLE_MODULE();
        /*disable interrupt*/
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER3_Interrupt_Disable();
        #endif
    }
    return ret;
}


/**
 * @brief : write value at counter of timer3
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer3_write_value(const timer3_t *_timer, uint16 _value){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
    }
    return ret;
}



/**
 * @brief : read value from counter of timer3
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer3_read_value(const timer3_t *_timer, uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 tmr3_low = 0, tmr3_high  = 0;
    if(_timer == NULL || _value == NULL) ret = E_NOT_OK;
    else{
        tmr3_low = TMR3L;
        tmr3_high = TMR3H;
        (*_value) = (uint16)(tmr3_high << 8) + (tmr3_low);
    }
    return ret;
}




/*_____Function of interrupt____*/
void TIMER3_ISR(void){
    TIMER3_Interrupt_Flag_Clear();
    TMR3H = (timer3_preload_value) >> 8;
    TMR3L = (uint8)(timer3_preload_value);
    if(TIMER3_InterruptHandler){
        TIMER3_InterruptHandler();
    }
}



/*____timer mode select & edge____*/
static inline void Timer3_mode_select(const timer3_t *_timer){
    if((_timer->timer3_mode) == TIMER3_SOURCE_TIMER_MOD){
        TIMER3_SOURCE_TIMER_MODE();
    }else{
        TIMER3_SOURCE_COUNTER_MODE();
        if((_timer->timer3_counter_mode) == TIMER3_SYNC_COUNTER_MOD){
            TIMER3_SYNC_COUNTER_MODE();
        }else{
            TIMER3_ASYNC_COUNTER_MODE();
        }
    }
}