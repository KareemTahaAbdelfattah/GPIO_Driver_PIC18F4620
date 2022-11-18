/* 
 * File:   hal_adc.h
 * Author: Kareem Taha
 *
 * Created on September 30, 2022, 2:44 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

 /* Section : Includes */
#include "../std_types.h"
#include "pic18f4620.h"
#include "../device_config.h"
#include "hal_adc_cfg.h"
#include "../Interrupt/hal_internal_interrupt.h"

 /* Section : Macros Definition */

#define ADC_AN0_ANALOG_FUNCTANILITY    0x0E
#define ADC_AN1_ANALOG_FUNCTANILITY    0x0D
#define ADC_AN2_ANALOG_FUNCTANILITY    0x0C
#define ADC_AN3_ANALOG_FUNCTANILITY    0x0B
#define ADC_AN4_ANALOG_FUNCTANILITY    0x0A
#define ADC_AN4_ANALOG_FUNCTANILITY    0x09
#define ADC_AN5_ANALOG_FUNCTANILITY    0x08
#define ADC_AN6_ANALOG_FUNCTANILITY    0x07
#define ADC_AN7_ANALOG_FUNCTANILITY    0x05
#define ADC_AN8_ANALOG_FUNCTANILITY    0x04
#define ADC_AN9_ANALOG_FUNCTANILITY    0x03
#define ADC_AN10_ANALOG_FUNCTANILITY   0x02
#define ADC_ALL_ANALOG_FUNCTANILITY    0x00
#define ADC_ALL_DIGITAL_FUNCTANILITY   0x0F

    
#define ADC_RESULT_LEFT                   0x00U
#define ADC_RESULT_RIGHT                  0x01U


#define ADC_VOLTAGE_REF_ENABLE            0x01U
#define ADC_VOLTAGE_REF_DISABLE           0x00U



#define HWREG8(_x)                                 (*((volatile unsigned char *)(_x)))
#define SET_BIT(Register, Pos)                     (Register |= (1 << Pos))
#define CLEAR_BIT(Register, Pos)                   (Register &= ~(1 << Pos))
#define TOGGLE_BIT(Register, Pos)                  (Register ^= (1 << Pos))
#define READ_BIT(Register, Pos)                    ((Register >> Pos) & 1)

 /* Section : Macros Functions Declaration */


/* RESULT Format RIGHT */
#define ADC_RESULT_RIGHT_FORMAT()                        (ADCON2bits.ADFM = 1);
/* RESULT Format LEFT */
#define ADC_RESULT_LEFT_FORMAT()                        (ADCON2bits.ADFM = 0);

/* A/D Conversion Status : (in Progress or in Idle) */
#define ADC_CONVERSION_STATUS()                          (ADCON0bits.GO_nDONE)
/* A/D Conversion Start */
#define ADC_CONVERSION_START()                           (ADCON0bits.GODONE = 1)

/* Enable ADC */
#define ADC_CONVERTER_ENABLE()                           (ADCON0bits.ADON = 1)
/* Disable ADC */
#define ADC_CONVERTER_DISABLE()                          (ADCON0bits.ADON = 0)


/* Enable Voltage ref of ADC */
#define ADC_ENABLE_VOLTAGE_REF()                          do{ADCON1bits.VCFG0 = 1;\
                                                              ADCON1bits.VCFG1 = 1;\
                                                             }while(0)
/* Disable Voltage ref of ADC */
#define ADC_DISABLE_VOLTAGE_REF()                          do{ADCON1bits.VCFG0 = 0;\
                                                              ADCON1bits.VCFG1 = 0;\
                                                             }while(0)

/* CONFIG MY FUCTIONALITY OF BITS */
#define ADC_BIT_CONFIGRATION_FUNCTANILITY(_CONFIG)          (ADCON1bits.PCFG = _CONFIG)

 /* Section : Data Types Declaration */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,  
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10, 
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}adc_select_channel_t;


typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,  
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_acquicition_time_t;


typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,  
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
}adc_conversion_clock_t;


typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void (* ADC_InterruptHandler)(void);   // for call back
    Interrupt_Priority_cfg priority;
#endif
    adc_acquicition_time_t acquicition_time; /* @ref adc_acquicition_time_t */
    adc_conversion_clock_t onversion_clock; /* @ref adc_conversion_clock_t */
    adc_select_channel_t select_channel; /* @ref adc_select_channel_t */
    uint8 voltage_ref: 1; /* voltage reference configuration */
    uint8 format_status: 1; /* Format status */
    uint8 ADC_Resreved: 6;  
}adc_conf_t;
 /* Section : Function Declaration */



STD_ReturnType ADC_Init(const adc_conf_t *_adc);

STD_ReturnType ADC_DeInit(const adc_conf_t *_adc);

STD_ReturnType ADC_Select_Channel(const adc_conf_t *_adc, adc_select_channel_t adc_channel);

STD_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc);

STD_ReturnType ADC_Is_Conversion_done(const adc_conf_t *_adc, uint8 *conversion_status);

STD_ReturnType ADC_GetConversion_Status_Result(const adc_conf_t *_adc, uint16 *converstion_result);

STD_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_select_channel_t adc_channel, uint16 *conversion_result);

STD_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_select_channel_t adc_channel);
#endif	/* HAL_ADC_H */

