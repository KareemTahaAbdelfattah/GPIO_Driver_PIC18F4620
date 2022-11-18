/* 
 * File:   TIMER0.h
 * Author: Kareem Taha
 *
 * Created on October 20, 2022, 5:07 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

 /* Section : Includes */
#include "TIMER0_cfg.h"
#include "../hal_gpio.h"
#include "../std_types.h"
#include "pic18f4620.h"
#include "../Interrupt/hal_internal_interrupt.h"

 /* Section : Macros Definition */
#define TIMER0_PRESCLAER_ENABLE_CFG         1
#define TIMER0_PRESCLAER_DISABLE_CFG        0

#define TIMER0_RISING_EDGE_CFG              1
#define TIMER0_FALLING_EDGE_CFG             0


#define TIMER0_SOURCE_TIMER_MOD            1
#define TIMER0_SOURCE_COUNTER_MOD          0


#define TIMER0_8_BIT                         1
#define TIMER0_16_BIT                        0
 /* Section : Macros Functions Declaration */
#define TIMER0_PRESCALER_ENABLE()               (T0CONbits.PSA = 0);
#define TIMER0_PRESCALER_DISABLE()              (T0CONbits.PSA = 1);

#define TIMER0_RISING_EDGE()                    (T0CONbits.T0SE = 0);
#define TIMER0_FALLING_EDGE()                   (T0CONbits.T0SE = 1);

#define TIMER0_SOURCE_COUNTER_MODE()            (T0CONbits.T0CS = 1)          
#define TIMER0_SOURCE_TIMER_MODE()              (T0CONbits.T0CS = 0)  


#define TIMER0_8BIT()                           (T0CONbits.T08BIT = 1)          
#define TIMER0_16BIT()                          (T0CONbits.T08BIT = 0)  

#define TIMER0_ENABLE_MODULE()                  (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE_MODULE()                 (T0CONbits.TMR0ON = 0)
 /* Section : Data Types Declaration */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,  
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;

typedef struct{
    #if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void(*TIMER0_InterruptHandler)(void);
    Interrupt_Priority_cfg priority;
    #endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 timer0_reg_size : 1;
    uint8 prescaler_en : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode: 1;
    uint8 timer0_reserved: 4;
}timer0_t;

 /* Section : Function Declaration */

/**
 * @brief : initialize timer0
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_init(const timer0_t *_timer);


/**
 * @brief : De initialize timer0
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_Deinit(const timer0_t *_timer);


/**
 * @brief : write value at counter of timer0
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_write_value(const timer0_t *_timer, uint16 _value);



/**
 * @brief : read value from counter of timer0
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer0_read_value(const timer0_t *_timer, uint16 *_value);


#endif	/* TIMER0_H */

