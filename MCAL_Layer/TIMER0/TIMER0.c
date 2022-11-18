/* 
 * File:   TIMER0.c
 * Author: Kareem Taha
 *
 * Created on October 20, 2022, 5:07 PM
 */


 /* Section : Includes */
#include "TIMER0.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
static uint16 timer0_preload = 0;

 /* Section : Function Declaration */
static inline void Timer0_prescaler_config(const timer0_t *_timer);
static inline void Timer0_mode_select(const timer0_t *_timer);
static inline void Timer0_register_size(const timer0_t *_timer);


#if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*TIMER0_InterruptHandler)(void) = NULL;
#endif

/**
 * @brief : initialize timer0
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_init(const timer0_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /*disable timer0*/
        TIMER0_DISABLE_MODULE();
        /*Prescaler config*/
        Timer0_prescaler_config(_timer);
        /*timer0 mode select*/
        Timer0_mode_select(_timer);
        /* register size */
        Timer0_register_size(_timer);
        /* preload value */
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
        /*________ Interrupt ______*/
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER0_Interrupt_Enable();
        TIMER0_Interrupt_Flag_Clear();
        TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_High_Priority){
            Interrupt_GlobalInterruptHighEnable();
            TIMER0_Interrupt_Priority_High();
        }
        else{
            Interrupt_GlobalInterruptLowEnable();
            TIMER0_Interrupt_Priority_Low();
        }
        #else
        /*Enable Global Interrupt */
        Interrupt_GlobalInterruptEnable();
        /*Enable Peripherals Interrupt */
        Interrupt_PeripheralInterruptEnable();
        #endif
        #endif
        /*enable timer0*/
        TIMER0_ENABLE_MODULE();
    }
    return ret;
}


/**
 * @brief : De initialize timer0
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_Deinit(const timer0_t *_timer){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        /* disable timer0*/
        TIMER0_DISABLE_MODULE();
        /*disable interrupt*/
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        TIMER0_Interrupt_Disable();
        #endif
    }
    return ret;
}


/**
 * @brief : write value at counter of timer0
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_write_value(const timer0_t *_timer, uint16 _value){
    STD_ReturnType ret = E_OK;
    if(_timer == NULL) ret = E_NOT_OK;
    else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
    }
    return ret;
}



/**
 * @brief : read value from counter of timer0
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_read_value(const timer0_t *_timer, uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 tmr0_low = 0, tmr0_high  = 0;
    if(_timer == NULL || _value == NULL) ret = E_NOT_OK;
    else{
        tmr0_low = TMR0L;
        tmr0_high = TMR0H;
        (*_value) = (uint16)(tmr0_high << 8) + (tmr0_low);
    }
    return ret;
}


/*_____Function of interrupt____*/
void TIMER0_ISR(void){
    TIMER0_Interrupt_Flag_Clear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler){
        TIMER0_InterruptHandler();
    }
}


/*____prescaler config function____*/
static inline void Timer0_prescaler_config(const timer0_t *_timer){
    if(TIMER0_PRESCLAER_ENABLE_CFG == _timer->prescaler_en){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }else{
        TIMER0_PRESCALER_DISABLE();
    }
}

/*____timer mode select & edge____*/
static inline void Timer0_mode_select(const timer0_t *_timer){
    if(TIMER0_SOURCE_TIMER_MOD == _timer->timer0_mode){
        TIMER0_SOURCE_TIMER_MODE();
    }else{
        TIMER0_SOURCE_COUNTER_MODE();
        if(_timer->timer0_counter_edge == TIMER0_RISING_EDGE_CFG){
            TIMER0_RISING_EDGE();
        }else{
            TIMER0_FALLING_EDGE();
        }
    }
}


static inline void Timer0_register_size(const timer0_t *_timer){
    if(_timer->timer0_reg_size == TIMER0_8_BIT){
        TIMER0_8BIT();
    }else{
        TIMER0_16BIT();
    }
}