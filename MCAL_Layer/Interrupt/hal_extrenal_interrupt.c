/* 
 * File:   hal_external_interrupt.c
 * Author: Kareem Taha
 *
 * Created on October 10, 2022, 1:47 PM
 */

/* Section : Includes */
#include "hal_extrenal_interrupt.h"
 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */


static void(*INT0_InterruptHandler)(void) = NULL;
static void(*INT1_InterruptHandler)(void) = NULL;
static void(*INT2_InterruptHandler)(void) = NULL;


static void(*RB4_InterruptHandler)(void) = NULL;
static void(*RB5_InterruptHandler)(void) = NULL;
static void(*RB6_InterruptHandler)(void) = NULL;
static void(*RB7_InterruptHandler)(void) = NULL;

static STD_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t *interrupt_obj);
static STD_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t *interrupt_obj);
static STD_ReturnType Interrupt_INTx_Priority_init(const Interrupt_INTx_t *interrupt_obj);
static STD_ReturnType Interrupt_INTx_Edge_init(const Interrupt_INTx_t *interrupt_obj);
static STD_ReturnType Interrupt_INTx_Pin(const Interrupt_INTx_t *interrupt_obj);
static STD_ReturnType Interrupt_INTx_Clear_Flag(const Interrupt_INTx_t *interrupt_obj);


static STD_ReturnType Set_INT0_InterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnType Set_INT1_InterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnType Set_INT2_InterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t *interrupt_obj);

static STD_ReturnType Interrupt_RBx_Enable(const Interrupt_RBx_t *interrupt_obj);
static STD_ReturnType Interrupt_RBx_Disable(const Interrupt_RBx_t *interrupt_obj);
static STD_ReturnType Interrupt_RBx_Priority_init(const Interrupt_RBx_t *interrupt_obj);
static STD_ReturnType Interrupt_RBx_Pin(const Interrupt_RBx_t *interrupt_obj);

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
STD_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        /*Disable*/
        ret = Interrupt_INTx_Disable(interrupt_obj);
        /*Clear Flag*/
        ret |= Interrupt_INTx_Clear_Flag(interrupt_obj);
        /*Edge set*/
        ret |= Interrupt_INTx_Edge_init(interrupt_obj);
        /*Priority Set*/
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        ret |= Interrupt_INTx_Priority_init(interrupt_obj);
        #endif
        /*I/O Pin*/
        ret |= Interrupt_INTx_Pin(interrupt_obj);
        /*Call Back*/
        ret |= Interrupt_INTx_SetInterruptHandler(interrupt_obj);
        /*Enable*/
        ret |= Interrupt_INTx_Enable(interrupt_obj);

    }
    return ret;
}

void INT0_ISR(void){
    /*Clear Flag*/
    INT0_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(INT0_InterruptHandler) INT0_InterruptHandler();
    
}


void INT1_ISR(void){
    /*Clear Flag*/
    INT1_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(INT1_InterruptHandler) INT1_InterruptHandler();
    
}


void INT2_ISR(void){
    /*Clear Flag*/
    INT2_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(INT2_InterruptHandler) INT2_InterruptHandler();
    
}

void RB4_ISR(void){
    /*Clear Flag*/
    RBx_OnChange_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(RB4_InterruptHandler) RB4_InterruptHandler();
    
}

void RB5_ISR(void){
    /*Clear Flag*/
    RBx_OnChange_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(RB5_InterruptHandler) RB5_InterruptHandler();
    
}


void RB6_ISR(void){
    /*Clear Flag*/
    RBx_OnChange_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(RB6_InterruptHandler) RB6_InterruptHandler();
    
}


void RB7_ISR(void){
    /*Clear Flag*/
    RBx_OnChange_Interrupt_Flag_Clear();
    /*Code*/
    
    /*Call Back Fun*/
    if(RB7_InterruptHandler) RB7_InterruptHandler();
    
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
STD_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        ret = Interrupt_INTx_Disable(interrupt_obj);
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
STD_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        RBx_OnChange_Interrupt_Disable();
        
        RBx_OnChange_Interrupt_Flag_Clear();
        
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(interrupt_obj->priority == INTERRUPT_High_Priority){
             Interrupt_GlobalInterruptHighEnable();
             RBx_OnChange_Interrupt_Priority_High();
             
        }else{
              Interrupt_GlobalInterruptLowEnable();
              RBx_OnChange_Interrupt_Priority_Low();
        }
        #else
        Interrupt_GlobalInterruptEnable();
        Interrupt_PeripheralInterruptEnable();
        #endif
        /*initialize pin to be input*/
        ret = gpio_pin_direction_init(&(interrupt_obj->mcu_pin));
        /**/
        switch(interrupt_obj->mcu_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler = interrupt_obj->Interrupt_Handler;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler = interrupt_obj->Interrupt_Handler;
                break; 
            case GPIO_PIN6:
                RB6_InterruptHandler = interrupt_obj->Interrupt_Handler;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler = interrupt_obj->Interrupt_Handler;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        RBx_OnChange_Interrupt_Enable();
        
    }
    return ret; 
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
STD_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        RBx_OnChange_Interrupt_Disable();
    }
    return ret;
}


/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
                Interrupt_PriorityLevelsEnable();
                Interrupt_GlobalInterruptHighEnable();
                #else
                Interrupt_GlobalInterruptEnable();
                Interrupt_PeripheralInterruptEnable();
                #endif
                INT0_Interrupt_Enable();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
                Interrupt_PriorityLevelsEnable();
                if(interrupt_obj->priority == INTERRUPT_High_Priority){
                    Interrupt_GlobalInterruptHighEnable();
                }else{
                    Interrupt_GlobalInterruptLowEnable();
                }
                #else
                Interrupt_GlobalInterruptEnable();
                Interrupt_PeripheralInterruptEnable();
                #endif
                INT1_Interrupt_Enable();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
                Interrupt_PriorityLevelsEnable();
                if(interrupt_obj->priority == INTERRUPT_High_Priority){
                    Interrupt_GlobalInterruptHighEnable();
                }else{
                    Interrupt_GlobalInterruptLowEnable();
                }
                #else
                Interrupt_GlobalInterruptEnable();
                Interrupt_PeripheralInterruptEnable();
                #endif
                INT2_Interrupt_Enable();
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : INT0_Interrupt_Disable(); break;
            case INTERRUPT_EXTERNAL_INT1 : INT1_Interrupt_Disable(); break;
            case INTERRUPT_EXTERNAL_INT2 : INT2_Interrupt_Disable(); break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */


#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
static STD_ReturnType Interrupt_INTx_Priority_init(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
         switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT1 :
                if(interrupt_obj->priority == INTERRUPT_High_Priority){
                    INT1_Interrupt_Priority_High();
                }else{
                    INT1_Interrupt_Priority_Low();
                }
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(interrupt_obj->priority == INTERRUPT_High_Priority){
                    INT2_Interrupt_Priority_High();
                }else{
                    INT2_Interrupt_Priority_Low();
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

#endif
/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_INTx_Edge_init(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
         switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                if(interrupt_obj->edge == INTERRUPT_RAISING_EDGE){
                    INT0_Interrupt_RaisingEdge_Set();
                }else{
                    INT0_Interrupt_FallingEdge_Set();
                }
                break;  
            case INTERRUPT_EXTERNAL_INT1 :
                if(interrupt_obj->edge == INTERRUPT_RAISING_EDGE){
                    INT1_Interrupt_RaisingEdge_Set();
                }else{
                    INT1_Interrupt_FallingEdge_Set();
                }
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(interrupt_obj->edge == INTERRUPT_RAISING_EDGE){
                    INT2_Interrupt_RaisingEdge_Set();
                }else{
                    INT2_Interrupt_FallingEdge_Set();
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_INTx_Pin(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       ret = gpio_pin_direction_init(&(interrupt_obj->mcu_pin));
    }
    return ret;
}



static STD_ReturnType Interrupt_INTx_Clear_Flag(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
        switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : INT0_Interrupt_Flag_Clear(); break;
            case INTERRUPT_EXTERNAL_INT1 : INT1_Interrupt_Flag_Clear(); break;
            case INTERRUPT_EXTERNAL_INT2 : INT2_Interrupt_Flag_Clear(); break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_RBx_Enable(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       
    }
    return ret;
}


/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_RBx_Disable(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       
    }
    return ret;
}


/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_RBx_Priority_init(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Interrupt_RBx_Pin(const Interrupt_RBx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Set_INT0_InterruptHandler(void(*InterruptHandler)(void)){
    STD_ReturnType ret = E_OK;
    if(InterruptHandler == NULL) ret = E_NOT_OK; 
    else{
       INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Set_INT1_InterruptHandler(void(*InterruptHandler)(void)){
    STD_ReturnType ret = E_OK;
    if(InterruptHandler == NULL) ret = E_NOT_OK; 
    else{
       INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}


/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */
static STD_ReturnType Set_INT2_InterruptHandler(void(*InterruptHandler)(void)){
    STD_ReturnType ret = E_OK;
    if(InterruptHandler == NULL) ret = E_NOT_OK; 
    else{
       INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return STD_ReturnType if Function finished successfully ret 1 else ret 0
 */


static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t *interrupt_obj){
    STD_ReturnType ret = E_OK;
    if(interrupt_obj == NULL) ret = E_NOT_OK; 
    else{
       switch(interrupt_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : ret = Set_INT0_InterruptHandler(interrupt_obj->Interrupt_Handler); break;
            case INTERRUPT_EXTERNAL_INT1 : ret = Set_INT1_InterruptHandler(interrupt_obj->Interrupt_Handler); break;
            case INTERRUPT_EXTERNAL_INT2 : ret = Set_INT2_InterruptHandler(interrupt_obj->Interrupt_Handler); break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}