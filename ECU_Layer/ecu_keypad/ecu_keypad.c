 /* Section : Includes */
#include "ecu_keypad.h"


 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
static const uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_Columns] = {
                                                                    {'7', '8', '9', '/'},
                                                                    {'4', '5', '6', '*'},
                                                                    {'1', '2', '3', '-'},
                                                                    {'#', '0', '=', '+'}
                                                        };

 /* Section : Function Declaration */
STD_ReturnType keypad_initialize(const keypad_t *_keypad){
    STD_ReturnType ret = E_OK;
    uint8 cnt_row = ECU_KEYPAD_ROW;
    uint8 cnt_column = ECU_KEYPAD_Columns;
    if(NULL == _keypad){
        ret = E_NOT_OK;
    }
    else{
        for(uint8 i = 0; i < cnt_row; i++){
            gpio_pin_direction_init(&(_keypad->keypad_row_pins[i]));
            gpio_pin_write_logic(&(_keypad->keypad_row_pins[i]), (_keypad->keypad_row_pins[i].logic));
        }
        for(uint8 j = 0; j < cnt_column; j++){
        gpio_pin_direction_init(&(_keypad->keypad_colomns_pins[j]));
        gpio_pin_write_logic(&(_keypad->keypad_colomns_pins[j]), (_keypad->keypad_colomns_pins[j].logic));
        }
    }
    return ret;
}
STD_ReturnType keypad_get_value(const keypad_t *_keypad, uint8 *value){
    STD_ReturnType ret = E_OK;
    uint8 cnt_row1 = ECU_KEYPAD_ROW;
    uint8 cnt_row2 = ECU_KEYPAD_ROW;
    uint8 cnt_column = ECU_KEYPAD_Columns;
    logic_t logic_btn = GPIO_LOW;
    if(NULL == _keypad){
        ret = E_NOT_OK;
    }
    else{
        for(uint8 i = 0; i < cnt_row1; i++){
            for(uint8 j = 0; j < cnt_row2; j++){
                ret = gpio_pin_write_logic(&(_keypad->keypad_row_pins[j]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad->keypad_row_pins[i]), GPIO_HIGH);
            for(uint8 k = 0; k < cnt_column; k++){
               ret = gpio_pin_read_logic(&(_keypad->keypad_colomns_pins[k]), &(logic_btn));
               if(logic_btn == GPIO_HIGH){
                   *value = btn_values[i][k];
               }
            }
        }
    }
    return ret;
}