/* 
 * File:   hal_eeprom.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on October 12, 2022, 11:35 PM
 */

/* Section : Includes */

#include "hal_eeprom.h"


 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
STD_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    STD_ReturnType ret = E_OK;
    /*Save interrupt Status*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /*Update Address Register*/
    EEADRH = (uint8)((bAdd >> 8) && 0x03);
    EEADR = ((bAdd) && 0xFF);
    /*Update Data register*/
    EEDATA = bData;
    /*Access write data*/
    EECON1bits.EEPGD = 0; //Access EEPROM Memory at 0 || Flash at 1
    EECON1bits.CFGS = 0; //Access EEPROM Memory at 0 || Flash at 0 && Configuration bits at 1
    /*Allow write cycle*/
    EECON1bits.WREN = 1;
    /*Disable interrupt*/
    Interrupt_GlobalInterruptDisable();
    /*write require sequence*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*initiate data cycle of eeprom*/
    EECON1bits.WR = 1;
    /*wait for write complete*/
    while(EECON1bits.WR){}
    /*stop write access*/
    EECON1bits.WREN = 0;
    /*restore interrupt again*/
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}
STD_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    STD_ReturnType ret = E_OK;
    if(bData == NULL) ret = E_NOT_OK;
    else{
        /*Select Access data*/
        EEADRH = (uint8)((bAdd >> 8) && 0x03);
        EEADR = ((bAdd) && 0xFF);
        /*initiate data read*/
        EECON1bits.RD = 1;
        /*no operation to not make anything to give a delay time to make a read data*/
        NOP();
        NOP();
        /*refer my data*/
        *bData = EEDATA;
    }
    return ret;
}