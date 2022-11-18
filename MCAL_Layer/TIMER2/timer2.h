/* 
 * File:   timer2.h
 * Author: Kareem Taha
 *
 * Created on November 9, 2022, 9:14 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

 /* Section : Includes */
#include "../hal_gpio.h"
#include "../std_types.h"
#include "pic18f4620.h"
#include "../Interrupt/hal_internal_interrupt.h"

 /* Section : Macros Definition */


/*Post-Scalar of TIMER2*/
#define TIMER2_POSTSCALER_DIV_BY_1           0
#define TIMER2_POSTSCALER_DIV_BY_2           1
#define TIMER2_POSTSCALER_DIV_BY_3           2
#define TIMER2_POSTSCALER_DIV_BY_4           3
#define TIMER2_POSTSCALER_DIV_BY_5           4
#define TIMER2_POSTSCALER_DIV_BY_6           5
#define TIMER2_POSTSCALER_DIV_BY_7           6
#define TIMER2_POSTSCALER_DIV_BY_8           7
#define TIMER2_POSTSCALER_DIV_BY_9           8
#define TIMER2_POSTSCALER_DIV_BY_10          9
#define TIMER2_POSTSCALER_DIV_BY_11          10
#define TIMER2_POSTSCALER_DIV_BY_12          11
#define TIMER2_POSTSCALER_DIV_BY_13          12
#define TIMER2_POSTSCALER_DIV_BY_14          13
#define TIMER2_POSTSCALER_DIV_BY_15          14
#define TIMER2_POSTSCALER_DIV_BY_16          15


/*Pre-Scalar of TIMER2*/
#define TIMER2_PRESCALER_DIV_BY_1           0
#define TIMER2_PRESCALER_DIV_BY_4           1
#define TIMER2_PRESCALER_DIV_BY_16          2

 /* Section : Macros Functions Declaration */
#define TIMER2_ENABLE_MODULE()                  (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE_MODULE()                 (T2CONbits.TMR2ON = 0)

 /* Section : Data Types Declaration */
typedef struct{
    #if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void(*TIMER2_InterruptHandler)(void);
    Interrupt_Priority_cfg priority;
    #endif 
    uint8 timer2_postscaler: 4; 
    uint8 timer2_prescaler: 2; 
    uint8 timer2_preload_value;
}timer2_t;


 /* Section : Function Declaration */




/**
 * @brief : initialize timer2
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_init(const timer2_t *_timer);


/**
 * @brief : De initialize timer2
 * @param _timer
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_Deinit(const timer2_t *_timer);


/**
 * @brief : write value at counter of timer2
 * @param _timer & value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_write_value(const timer2_t *_timer, uint8 _value);



/**
 * @brief : read value from counter of timer2
 * @param _timer & pointer of value
 * @return return 1 if initialization made successfully or 0.
 */
STD_ReturnType timer2_read_value(const timer2_t *_timer, uint8 *_value);

#endif	/* TIMER2_H */

