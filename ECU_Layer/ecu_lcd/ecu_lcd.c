/* 
 * File:   ecu_lcd.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 23, 2022, 11:10 AM
 */

 /* Section : Includes */
#include "ecu_lcd.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */


 /* Section : Function Declaration */

static STD_ReturnType lcd_4bit_send_t(const ch_lcd_4bit_t *lcd, uint8 _data_command);
static STD_ReturnType lcd_8bit_send_t(const ch_lcd_8bit_t *lcd, uint8 _data_command);
static STD_ReturnType lcd_8bit_set_cursor(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column);
static STD_ReturnType lcd_4bit_set_cursor(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column);


STD_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
    STD_ReturnType ret = E_OK;
    if(value == NULL) ret = E_NOT_OK;
    else{
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}
STD_ReturnType convert_short_to_string(uint16 value, uint8 *str){
    STD_ReturnType ret = E_OK;
    if(value == NULL) ret = E_NOT_OK;
    else{
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
    }
    return ret;
}
STD_ReturnType convert_int_to_string(uint32 value, uint8 *str){
    STD_ReturnType ret = E_OK;
    if(value == NULL) ret = E_NOT_OK;
    else{
         memset(str, '\0', 11);
         sprintf(str, "%i", value);
    }
    return ret;
}

STD_ReturnType lcd_4_bit_initialize(const ch_lcd_4bit_t *lcd){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_direction_init(&(lcd->lcd_rs));
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        gpio_pin_direction_init(&(lcd->lcd_en));
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW); 
        for(int i = 0; i < 4; i++){
            gpio_pin_direction_init(&(lcd->lcd_data_4_bit[i]));
            gpio_pin_write_logic(&(lcd->lcd_data_4_bit[i]), GPIO_LOW);
        }
        _delay(200);
        lcd_4_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        _delay(50);
        lcd_4_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        _delay(15);
        lcd_4_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        lcd_4_bit_send_command(lcd, LCD_CLEAR);
        lcd_4_bit_send_command(lcd, LCD_RETURN_HOME);
        lcd_4_bit_send_command(lcd, LCD_ENTRY_MODE);
        lcd_4_bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        lcd_4_bit_send_command(lcd, LCD_4_BIT_MODE_2_LINE);
        lcd_4_bit_send_command(lcd, 0x80);
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_command(const ch_lcd_4bit_t *lcd, uint8 command){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        lcd_4bit_send_t(lcd, (command >> 4));
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(50);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
        lcd_4bit_send_t(lcd, command);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(50);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_char_data(const ch_lcd_4bit_t *lcd, uint8 data){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        lcd_4bit_send_t(lcd, (data >> 4));
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(50);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
        lcd_4bit_send_t(lcd, data);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(50);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_char_data_pos(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,uint8 data){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_4bit_set_cursor(lcd, row, column);
        lcd_4_bit_send_char_data(lcd, data);
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_string(const ch_lcd_4bit_t *lcd, uint8 *str){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        while(*str){
            lcd_4_bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_string_pos(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,uint8 *str){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            lcd_4_bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_4_bit_send_custom_char(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,const uint8 _chr[], uint8 pos){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_4_bit_send_command(lcd, ((LCD_CGRAM_START) + pos * 8));
        for(int i = 0; i < 8; i++){
            lcd_4_bit_send_char_data(lcd, _chr[i]);
        }
        lcd_4_bit_send_char_data_pos(lcd, row, column, pos);
    }
    return ret;
}



STD_ReturnType lcd_8_bit_initialize(const ch_lcd_8bit_t *lcd){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_direction_init(&(lcd->lcd_rs));
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        gpio_pin_direction_init(&(lcd->lcd_en));
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW); 
        for(int i = 0; i < 8; i++){
            gpio_pin_direction_init(&(lcd->lcd_data_8_bit[i]));
            gpio_pin_write_logic(&(lcd->lcd_data_8_bit[i]), GPIO_LOW);
        }
        _delay(200);
        lcd_8_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        _delay(50);
        lcd_8_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        _delay(15);
        lcd_8_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
        lcd_8_bit_send_command(lcd, LCD_CLEAR);
        lcd_8_bit_send_command(lcd, LCD_RETURN_HOME);
        lcd_8_bit_send_command(lcd, LCD_ENTRY_MODE);
        lcd_8_bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        lcd_8_bit_send_command(lcd, LCD_8_BIT_MODE_2_LINE);
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_command(const ch_lcd_8bit_t *lcd, uint8 command){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        lcd_8bit_send_t(lcd, command);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(5);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_char_data(const ch_lcd_8bit_t *lcd, uint8 data){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        lcd_8bit_send_t(lcd, data);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        _delay(5);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_char_data_pos(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,uint8 data){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_8bit_set_cursor(lcd, row, column);
        lcd_8_bit_send_char_data(lcd, data);
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_string(const ch_lcd_8bit_t *lcd, uint8 *str){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        while(*str){
            lcd_8_bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_string_pos(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,uint8 *str){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_8bit_set_cursor(lcd, row, column);
        while(*str){
            lcd_8_bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_8_bit_send_custom_char(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,const uint8 _chr[], uint8 pos){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        lcd_8_bit_send_command(lcd, ((LCD_CGRAM_START) + pos * 8));
        for(int i = 0; i < 8; i++){
            lcd_8_bit_send_char_data(lcd, _chr[i]);
        }
        lcd_8_bit_send_char_data_pos(lcd, row, column, pos);
    }
    return ret;
}

static STD_ReturnType lcd_4bit_send_t(const ch_lcd_4bit_t *lcd, uint8 _data_command){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_data_4_bit[0]), ((_data_command >> 0) & (uint8) 0x01));
        gpio_pin_write_logic(&(lcd->lcd_data_4_bit[1]), ((_data_command >> 1) & (uint8) 0x01));
        gpio_pin_write_logic(&(lcd->lcd_data_4_bit[2]), ((_data_command >> 2) & (uint8) 0x01));
        gpio_pin_write_logic(&(lcd->lcd_data_4_bit[3]), ((_data_command >> 3) & (uint8) 0x01));
    }
    return ret;
}


static STD_ReturnType lcd_8bit_send_t(const ch_lcd_8bit_t *lcd, uint8 _data_command){
    STD_ReturnType ret = E_OK;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[0]), (_data_command >> 0) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[1]), (_data_command >> 1) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[2]), (_data_command >> 2) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[3]), (_data_command >> 3) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[4]), (_data_command >> 4) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[5]), (_data_command >> 5) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[6]), (_data_command >> 6) & (uint8) 0x01);
        gpio_pin_write_logic(&(lcd->lcd_data_8_bit[7]), (_data_command >> 7) & (uint8) 0x01);
    }
    return ret;
}


static STD_ReturnType lcd_8bit_set_cursor(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column){
    STD_ReturnType ret = E_OK;
    column--;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        switch(row){
            case 1 :
                lcd_8_bit_send_command(lcd, (0x80 + column));
                break;
            case 2 :
                lcd_8_bit_send_command(lcd, (0xc0 + column));
                break;
            case 3 :
                lcd_8_bit_send_command(lcd, (0x94 + column));
                break;
            case 4 :
                lcd_8_bit_send_command(lcd, (0xd4 + column));
                break;
            default : 
                break;                    
        }
    }
    return ret; 
}

static STD_ReturnType lcd_4bit_set_cursor(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column){
    STD_ReturnType ret = E_OK;
    column--;
    if(lcd == NULL) ret = E_NOT_OK;
    else{
        switch(row){
            case 1 :
                lcd_4_bit_send_command(lcd, (0x80 + column));
                break;
            case 2 :
                lcd_4_bit_send_command(lcd, (0xc0 + column));
                break;
            case 3 :
                lcd_4_bit_send_command(lcd, (0x94 + column));
                break;
            case 4 :
                lcd_4_bit_send_command(lcd, (0xd4 + column));
                break;
            default : 
                break;                    
        }
    }
    return ret; 
}