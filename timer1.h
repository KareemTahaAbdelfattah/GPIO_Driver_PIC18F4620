/* 
 * File:   timer1.h
 * Author: Kareem Taha
 *
 * Created on November 3, 2022, 9:03 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

 /* Section : Includes */
#include "timer1_cfg.h"
#include "../GPIO Driver/MCAL_Layer/hal_gpio.h"
#include "MCAL_Layer/std_types.h"
#include "pic18f4620.h"
#include "MCAL_Layer/Interrupt/hal_internal_interrupt.h"


 /* Section : Macros Definition */
#define TIMER1_SOURCE_COUNTER_MOD          1
#define TIMER1_SOURCE_TIMER_MOD            0


#define TIMER1_ASYNC_COUNTER_MOD           1
#define TIMER1_SYNC_COUNTER_MOD            0

/*Timer1 Oscillator*/
#define TIMER1_OSCILLATOR_ENABLE           1
#define TIMER1_OSCILLATOR_DISABLE          0

#define TIMER1_RW_REG_MODE_16BIT           1
#define TIMER1_RW_REG_MODE_8BIT            0

#define TIMER1_PRESCALER_DIV_BY_1          0
#define TIMER1_PRESCALER_DIV_BY_2          1
#define TIMER1_PRESCALER_DIV_BY_4          2
#define TIMER1_PRESCALER_DIV_BY_8          3

 /* Section : Macros Functions Declaration */
#define TIMER1_ENABLE_MODULE()                  (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE_MODULE()                 (T1CONbits.TMR1ON = 0)
    

#define TIMER1_SOURCE_COUNTER_MODE()            (T1CONbits.TMR1CS = 1)          
#define TIMER1_SOURCE_TIMER_MODE()              (T1CONbits.TMR1CS = 0)  

#define TIMER1_ASYNC_COUNTER_MODE()             (T1CONbits.T1SYNC = 1) 
#define TIMER1_SYNC_COUNTER_MODE()              (T1CONbits.T1SYNC = 0) 

#define TIMER1_OSCILLATOR_EXTERNAL_ENABLE()     (T1CONbits.T1OSCEN = 1) 
#define TIMER1_OSCILLATOR_EXTERNAL_DISABLE()    (T1CONbits.T1OSCEN = 0) 

#define TIMER1_SYSTEM_CLK_STATUS()              (T1CONbits.T1RUN)


#define TIMER1_8BIT_READ()                      (T1CONbits.RD16 = 1)          
#define TIMER1_16BIT_READ()                     (T1CONbits.RD16 = 0)  

 /* Section : Data Types Declaration */


typedef struct{
    #if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void(*TIMER1_InterruptHandler)(void);
    Interrupt_Priority_cfg priority;
    #endif 
    uint16 timer1_preload_value;
    uint8 timer1_mode: 1;
    uint8 timer1_counter_mode: 1;
    uint8 timer1_oscillator_cfg: 1;
    uint8 timer1_reg_rw_mode: 1;
    uint8 timer1_prescaler: 2; 
}timer1_t;

 /* Section : Function Declaration */

/**
 * @brief : initialize timer1
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_init(const timer1_t *_timer);


/**
 * @brief : De initialize timer1
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_Deinit(const timer1_t *_timer);


/**
 * @brief : write value at counter of timer1
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_write_value(const timer1_t *_timer, uint16 _value);



/**
 * @brief : read value from counter of timer1
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer1_read_value(const timer1_t *_timer, uint16 *_value);

#endif	/* TIMER1_H */

