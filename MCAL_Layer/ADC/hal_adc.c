/* 
 * File:   hal_adc.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 30, 2022, 2:43 PM
 */


 /* Section : Includes */
#include "hal_adc.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
#if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_pin_conf(const adc_select_channel_t channel_adc);
static inline void adc_select_result_format(const adc_conf_t *_adc);
static inline void adc_select_vol_ref(const adc_conf_t *_adc);

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_Init(const adc_conf_t *_adc){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL) ret = E_NOT_OK;
    else{
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT = _adc->acquicition_time;
        ADCON2bits.ADCS = _adc->onversion_clock;
        ADCON0bits.CHS = _adc->select_channel;
        adc_input_channel_pin_conf(_adc->select_channel);
        
        #if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        ADC_Interrupt_Enable();
        ADC_Interrupt_Flag_Clear();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
        #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
        Interrupt_PriorityLevelsEnable();
        if(_adc->priority == INTERRUPT_High_Priority){
            Interrupt_GlobalInterruptHighEnable();
            ADC_Interrupt_Priority_High();
        }
        else{
            Interrupt_GlobalInterruptLowEnable();
            ADC_Interrupt_Priority_Low();
        }   
        #else
        /*Enable Global Interrupt */
        Interrupt_GlobalInterruptEnable();
        /*Enable Peripherals Interrupt */
        Interrupt_PeripheralInterruptEnable();
        #endif    
        #endif
        
        adc_select_result_format(_adc);
        adc_select_vol_ref(_adc);
        
        ADC_CONVERTER_ENABLE();
                
        
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_DeInit(const adc_conf_t *_adc){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL) ret = E_NOT_OK;
    else{
        ADC_CONVERTER_DISABLE();
        #if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        ADC_Interrupt_Disable();
        #endif
        
    }
    return ret;  
}

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_Select_Channel(const adc_conf_t *_adc, adc_select_channel_t adc_channel){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL) ret = E_NOT_OK;
    else{
        ADCON0bits.CHS = adc_channel;
        adc_input_channel_pin_conf(adc_channel);
        
    }
    return ret;
}


/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL) ret = E_NOT_OK;
    else{
        ADC_CONVERSION_START();
    }
    return ret;
}


/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_Is_Conversion_done(const adc_conf_t *_adc, uint8 *conversion_status){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL || conversion_status == NULL) ret = E_NOT_OK;
    else{
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}


/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_GetConversion_Status_Result(const adc_conf_t *_adc, uint16 *converstion_result){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL || converstion_result == NULL) ret = E_NOT_OK;
    else{
        if(_adc->format_status == ADC_RESULT_LEFT){
            *converstion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
           *converstion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}


/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_select_channel_t adc_channel, uint16 *conversion_result){
    STD_ReturnType ret = E_OK;
    uint8 conversion_status = 0;
    if(_adc == NULL || conversion_result == NULL) ret = E_NOT_OK;
    else{
        ADC_Select_Channel(_adc, adc_channel);
        ADC_Start_Conversion(_adc);
        while(ADCON0bits.GO_nDONE);
        ADC_GetConversion_Status_Result(_adc, conversion_result);
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
static inline void adc_input_channel_pin_conf(const adc_select_channel_t channel_adc){
    switch(channel_adc){
        case ADC_CHANNEL_AN0 :
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1 :
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break; 
        case ADC_CHANNEL_AN2 :
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;    
        case ADC_CHANNEL_AN3 :
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;   
        case ADC_CHANNEL_AN4 :
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;   
        case ADC_CHANNEL_AN5 :
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;   
        case ADC_CHANNEL_AN6 :
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;    
        case ADC_CHANNEL_AN7 :
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;    
        case ADC_CHANNEL_AN8 :
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;  
        case ADC_CHANNEL_AN9 :
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;   
        case ADC_CHANNEL_AN10 :
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;   
        case ADC_CHANNEL_AN11 :
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;    
        case ADC_CHANNEL_AN12 :
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;    
    }
}

/**
 * 
 * @param _adc
 * @return 
 */
static inline void adc_select_result_format(const adc_conf_t *_adc){
    if(_adc->format_status == ADC_RESULT_LEFT){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{
       ADC_RESULT_RIGHT_FORMAT();
    }
}


/**
 * 
 * @param _adc
 * @return 
 */
static inline void adc_select_vol_ref(const adc_conf_t *_adc){
    if(_adc->voltage_ref == ADC_VOLTAGE_REF_DISABLE){
        ADC_DISABLE_VOLTAGE_REF();
    }else{
        ADC_ENABLE_VOLTAGE_REF();
    }
}



STD_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_select_channel_t adc_channel){
    STD_ReturnType ret = E_OK;
    if(_adc == NULL) ret = E_NOT_OK;
    else{
        /* start A/D channel*/
        ADC_Select_Channel(_adc, adc_channel);
        /* start conversion */
        ADC_Start_Conversion(_adc);
    }
    return ret;
}

void ADC_ISR(void){
    ADC_Interrupt_Flag_Clear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}