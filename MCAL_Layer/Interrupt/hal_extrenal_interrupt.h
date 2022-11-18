/* 
 * File:   hal_extrenal_interrupt.h
 * Author: Kareem Taha
 *
 * Created on October 10, 2022, 10:46 AM
 */

#ifndef HAL_EXTRENAL_INTERRUPT_H
#define	HAL_EXTRENAL_INTERRUPT_H

 /* Section : Includes */

#include "hal_interrupt_cfg.h"

 /* Section : Macros Definition */


 /* Section : Macros Functions Declaration */
#if External_Interrupt_INTx_Feature_Enable == Interrupt_Feature_Enable

/* INT0 pin */
#define INT0_Interrupt_Enable()                 (INTCONbits.INT0IE = 1)
#define INT0_Interrupt_Disable()                (INTCONbits.INT0IE = 0)
#define INT0_Interrupt_Flag_Clear()             (INTCONbits.INT0IF = 0)
#define INT0_Interrupt_RaisingEdge_Set()        (INTCON2bits.INTEDG0 = 1)
#define INT0_Interrupt_FallingEdge_Set()        (INTCON2bits.INTEDG0 = 0)

/* INT1 pin */
#define INT1_Interrupt_Enable()                 (INTCON3bits.INT1IE = 1)
#define INT1_Interrupt_Disable()                (INTCON3bits.INT1IE = 0)
#define INT1_Interrupt_Flag_Clear()             (INTCON3bits.INT1F = 0)
#define INT1_Interrupt_RaisingEdge_Set()        (INTCON2bits.INTEDG1 = 1)
#define INT1_Interrupt_FallingEdge_Set()        (INTCON2bits.INTEDG1 = 0)

/* INT2 pin */
#define INT2_Interrupt_Enable()                 (INTCON3bits.INT2IE = 1)
#define INT2_Interrupt_Disable()                (INTCON3bits.INT2IE = 0)
#define INT2_Interrupt_Flag_Clear()             (INTCON3bits.INT2F = 0)
#define INT2_Interrupt_RaisingEdge_Set()        (INTCON2bits.INTEDG2 = 1)
#define INT2_Interrupt_FallingEdge_Set()        (INTCON2bits.INTEDG2 = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable

/* INT0 pin is High priority */

/* INT1 pin priority */
#define INT1_Interrupt_Priority_High()                 (INTCON3bits.INT1IP = 1)
#define INT1_Interrupt_Priority_Low()                  (INTCON3bits.INT1IP = 0)

/* INT2 pin priority */
#define INT2_Interrupt_Priority_High()                 (INTCON3bits.INT2IP = 1)
#define INT2_Interrupt_Priority_Low()                  (INTCON3bits.INT2IP = 0)

#endif

#endif



#if External_Interrupt_OnChange_Feature_Enable == Interrupt_Feature_Enable

/* Port B */
#define RBx_OnChange_Interrupt_Enable()                 (INTCONbits.RBIE = 1)
#define RBx_OnChange_Interrupt_Disable()                (INTCONbits.RBIE = 0)
#define RBx_OnChange_Interrupt_Flag_Clear()             (INTCONbits.RBIF = 0)


#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable


/* Port B */
#define RBx_OnChange_Interrupt_Priority_High()                 (INTCON2bits.RBIP = 1)
#define RBx_OnChange_Interrupt_Priority_Low()                  (INTCON2bits.RBIP = 0)


#endif
        
#endif

 /* Section : Data Types Declaration */

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE,    
}Interrupt_INTx_edge;



typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,
}Interrupt_INTx_src;


typedef struct{
    void (* Interrupt_Handler)(void);
    pin_config_t mcu_pin;
    Interrupt_INTx_edge edge;
    Interrupt_INTx_src source;
    Interrupt_Priority_cfg priority;
}Interrupt_INTx_t;



typedef struct{
    void (* Interrupt_Handler)(void);
    pin_config_t mcu_pin;
    Interrupt_Priority_cfg priority;
}Interrupt_RBx_t;


 /* Section : Function Declaration */

STD_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t *interrupt_obj);
STD_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t *interrupt_obj);

STD_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_t *interrupt_obj);
STD_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t *interrupt_obj);
#endif	/* HAL_EXTRENAL_INTERRUPT_H */

