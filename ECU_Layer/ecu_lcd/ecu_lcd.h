/* 
 * File:   ecu_lcd.h
 * Author: Kareem Taha
 *
 * Created on September 22, 2022, 10:33 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

 /* Section : Includes */
#include "ecu_lcd_cfg.h"
#include "../../MCAL_Layer/hal_gpio.h"
 /* Section : Macros Definition */

#define LCD_CLEAR                       0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE                  0x06
#define LCD_CURSOR_OFF_DISPLAY_ON       0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF      0x08
#define LCD_CURSOR_ON_BLINK_ON          0x0F
#define LCD_CURSOR_ON_BLINK_OFF         0x0E
#define LCD_DISPLAY_SHIFT_RIGHT         0x1C
#define LCD_DISPLAY_SHIFT_LEFT          0x18
#define LCD_8_BIT_MODE_2_LINE           0x38
#define LCD_4_BIT_MODE_2_LINE           0x28
#define LCD_CGRAM_START                 0x40
#define LCD_DDRAM_START                 0x80

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data_4_bit[4];
}ch_lcd_4bit_t;


typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data_8_bit[8];
}ch_lcd_8bit_t;

 /* Section : Function Declaration */

STD_ReturnType lcd_4_bit_initialize(const ch_lcd_4bit_t *lcd);
STD_ReturnType lcd_4_bit_send_command(const ch_lcd_4bit_t *lcd, uint8 command);
STD_ReturnType lcd_4_bit_send_char_data(const ch_lcd_4bit_t *lcd, uint8 data);
STD_ReturnType lcd_4_bit_send_char_data_pos(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,uint8 data);
STD_ReturnType lcd_4_bit_send_string(const ch_lcd_4bit_t *lcd, uint8 *str);
STD_ReturnType lcd_4_bit_send_string_pos(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,uint8 *str);
STD_ReturnType lcd_4_bit_send_custom_char(const ch_lcd_4bit_t *lcd, uint8 row, uint8 column ,const uint8 _chr[], uint8 pos);



STD_ReturnType lcd_8_bit_initialize(const ch_lcd_8bit_t *lcd);
STD_ReturnType lcd_8_bit_send_command(const ch_lcd_8bit_t *lcd, uint8 command);
STD_ReturnType lcd_8_bit_send_char_data(const ch_lcd_8bit_t *lcd, uint8 data);
STD_ReturnType lcd_8_bit_send_char_data_pos(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,uint8 data);
STD_ReturnType lcd_8_bit_send_string(const ch_lcd_8bit_t *lcd, uint8 *str);
STD_ReturnType lcd_8_bit_send_string_pos(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,uint8 *str);
STD_ReturnType lcd_8_bit_send_custom_char(const ch_lcd_8bit_t *lcd, uint8 row, uint8 column ,const uint8 _chr[], uint8 pos);


STD_ReturnType convert_byte_to_string(uint8 value, uint8 *str);
STD_ReturnType convert_short_to_string(uint16 value, uint8 *str);
STD_ReturnType convert_int_to_string(uint32 value, uint8 *str);

#endif	/* ECU_LCD_H */

