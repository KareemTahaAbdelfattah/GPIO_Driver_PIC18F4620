/* 
 * File:   Application.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "Application.h"
#include "MCAL_Layer/ADC/hal_adc.h"

STD_ReturnType ret = E_OK;


/*
ch_lcd_4bit_t lcd_1 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[0].port = PORTC_INDEX,
  .lcd_data_4_bit[0].pin = GPIO_PIN2,
  .lcd_data_4_bit[0].logic = GPIO_LOW,
  .lcd_data_4_bit[0].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[1].port = PORTC_INDEX,
  .lcd_data_4_bit[1].pin = GPIO_PIN3,
  .lcd_data_4_bit[1].logic = GPIO_LOW,
  .lcd_data_4_bit[1].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[2].port = PORTC_INDEX,
  .lcd_data_4_bit[2].pin = GPIO_PIN4,
  .lcd_data_4_bit[2].logic = GPIO_LOW,
  .lcd_data_4_bit[2].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[3].port = PORTC_INDEX,
  .lcd_data_4_bit[3].pin = GPIO_PIN5,
  .lcd_data_4_bit[3].logic = GPIO_LOW,
  .lcd_data_4_bit[3].direction = GPIO_OUTPUT_DIRECTION
};


ch_lcd_8bit_t lcd_2 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN6,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN7,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[0].port = PORTD_INDEX,
  .lcd_data_8_bit[0].pin = GPIO_PIN0,
  .lcd_data_8_bit[0].logic = GPIO_LOW,
  .lcd_data_8_bit[0].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[1].port = PORTD_INDEX,
  .lcd_data_8_bit[1].pin = GPIO_PIN1,
  .lcd_data_8_bit[1].logic = GPIO_LOW,
  .lcd_data_8_bit[1].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[2].port = PORTD_INDEX,
  .lcd_data_8_bit[2].pin = GPIO_PIN2,
  .lcd_data_8_bit[2].logic = GPIO_LOW,
  .lcd_data_8_bit[2].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[3].port = PORTD_INDEX,
  .lcd_data_8_bit[3].pin = GPIO_PIN3,
  .lcd_data_8_bit[3].logic = GPIO_LOW,
  .lcd_data_8_bit[3].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[4].port = PORTD_INDEX,
  .lcd_data_8_bit[4].pin = GPIO_PIN4,
  .lcd_data_8_bit[4].logic = GPIO_LOW,
  .lcd_data_8_bit[4].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[5].port = PORTD_INDEX,
  .lcd_data_8_bit[5].pin = GPIO_PIN5,
  .lcd_data_8_bit[5].logic = GPIO_LOW,
  .lcd_data_8_bit[5].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[6].port = PORTD_INDEX,
  .lcd_data_8_bit[6].pin = GPIO_PIN6,
  .lcd_data_8_bit[6].logic = GPIO_LOW,
  .lcd_data_8_bit[6].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[7].port = PORTD_INDEX,
  .lcd_data_8_bit[7].pin = GPIO_PIN7,
  .lcd_data_8_bit[7].logic = GPIO_LOW,
  .lcd_data_8_bit[7].direction = GPIO_OUTPUT_DIRECTION
};


keypad_t kaypad_1 = {
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[0].port = PORTD_INDEX,
    .keypad_row_pins[1].port = PORTD_INDEX,
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].logic = GPIO_LOW,
    .keypad_row_pins[0].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[1].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[2].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[3].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_colomns_pins[0].pin = GPIO_PIN4,
    .keypad_colomns_pins[1].pin = GPIO_PIN5,
    .keypad_colomns_pins[2].pin = GPIO_PIN6,
    .keypad_colomns_pins[3].pin = GPIO_PIN7,
    .keypad_colomns_pins[0].port = PORTD_INDEX,
    .keypad_colomns_pins[1].port = PORTD_INDEX,
    .keypad_colomns_pins[2].port = PORTD_INDEX,
    .keypad_colomns_pins[3].port = PORTD_INDEX,
    .keypad_colomns_pins[0].logic = GPIO_LOW,
    .keypad_colomns_pins[1].logic = GPIO_LOW,
    .keypad_colomns_pins[2].logic = GPIO_LOW,
    .keypad_colomns_pins[3].logic = GPIO_LOW,
    .keypad_colomns_pins[0].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[1].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[2].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[3].direction = GPIO_INPUT_DIRECTION,
};

void welcome_massege(void){
    for(int i = 1; i <= 6; i++){
        lcd_4_bit_send_string_pos(&lcd_1, 1, i, "Hello All");
        lcd_4_bit_send_string_pos(&lcd_1, 2, 5, "!Calculator!");
        _delay(250000);
        lcd_4_bit_send_string_pos(&lcd_1, 1, i, " ");
    }
    lcd_4_bit_send_string_pos(&lcd_1, 1, 1, "                  ");
    lcd_4_bit_send_string_pos(&lcd_1, 1, 6, "Hello All");
}

void loading(void){
    lcd_4_bit_send_string_pos(&lcd_1, 1, 1, "Loading");
    for(int i = 8; i <= 15; i++){
        lcd_4_bit_send_char_data_pos(&lcd_1, 1, i, '.');
        _delay(250000);
    }
}*/

/*
led_t led1 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN0,
  .port_name = PORTC_INDEX,
};



led_t led2 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN1,
  .port_name = PORTC_INDEX,
};


led_t led3 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN2,
  .port_name = PORTC_INDEX,
};

led_t led4 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN3,
  .port_name = PORTC_INDEX,
};

void RB_int0_app_isr(void){
   ret = led_toggle_logic(&led1);
}


void RB_int1_app_isr(void){
   ret = led_toggle_logic(&led2);
}

void RB_int2_app_isr(void){
   ret = led_toggle_logic(&led3);
}

void RB_int3_app_isr(void){
   ret = led_toggle_logic(&led4);
}


Interrupt_RBx_t int1_obj = {
   .Interrupt_Handler = RB_int0_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN4,
};
Interrupt_RBx_t int2_obj = {
   .Interrupt_Handler = RB_int1_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN5,
};
Interrupt_RBx_t int3_obj = {
   .Interrupt_Handler = RB_int2_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN6,
};
Interrupt_RBx_t int4_obj = {
   .Interrupt_Handler = RB_int3_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN7,
};*/


/*
void int0_app_isr(void){
   ret = led_toggle_logic(&led1);
}


void int1_app_isr(void){
   ret = led_toggle_logic(&led2);
}

void int2_app_isr(void){
   ret = led_toggle_logic(&led3);
}
Interrupt_INTx_t int0_obj = {
   .Interrupt_Handler = int0_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_High_Priority,
   .source = INTERRUPT_EXTERNAL_INT0,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN0,
};

Interrupt_INTx_t int1_obj = {
   .Interrupt_Handler = int1_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_Low_Priority,
   .source = INTERRUPT_EXTERNAL_INT1,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN1,
};


Interrupt_INTx_t int2_obj = {
   .Interrupt_Handler = int2_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_High_Priority,
   .source = INTERRUPT_EXTERNAL_INT2,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN2,
};*/

//uint8 epprom_cnt = 0, value = 0;


led_t led1 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN0,
  .port_name = PORTC_INDEX,
};

led_t led2 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN1,
  .port_name = PORTC_INDEX,
};

led_t led3 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN2,
  .port_name = PORTC_INDEX,
};

volatile uint32 counter_value = 0;

void timer0_defaultHandler(void){
    counter_value++;
    //led_toggle_logic(&led1);
    //led_toggle_logic(&led2);
    //led_toggle_logic(&led3);
};



void timer2_defaultHandler(void){
    led_toggle_logic(&led1);
    led_toggle_logic(&led2);
    led_toggle_logic(&led3);
};


timer2_t timer2_obj = {
  .TIMER2_InterruptHandler = timer2_defaultHandler,
  .timer2_postscaler = TIMER2_POSTSCALER_DIV_BY_16,
  .timer2_prescaler = TIMER2_PRESCALER_DIV_BY_1,
  .timer2_preload_value = 249,
};



timer0_t timer0_obj = {
    .TIMER0_InterruptHandler = timer0_defaultHandler,
    .timer0_mode = TIMER0_SOURCE_TIMER_MOD,
    .timer0_reg_size = TIMER0_16_BIT,
    .prescaler_en = TIMER0_PRESCLAER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_16,
    .timer0_preload_value = 3036
};

void timer1_defaultHandler(void){
    led_toggle_logic(&led2);
    led_toggle_logic(&led3);
};

timer1_t timer1_obj = {
    .TIMER1_InterruptHandler = timer1_defaultHandler,
    .timer1_mode = TIMER1_SOURCE_TIMER_MOD,
    .priority = INTERRUPT_Low_Priority,
    .timer1_preload_value = 3036,
    .timer1_prescaler = TIMER1_PRESCALER_DIV_BY_8,
    .timer1_reg_rw_mode = TIMER1_RW_REG_MODE_16BIT,
};





void timer3_defaultHandler(void){
    led_toggle_logic(&led1);
    led_toggle_logic(&led2);
    led_toggle_logic(&led3);
};

timer3_t timer3_obj = {
    .TIMER3_InterruptHandler = timer3_defaultHandler,
    .timer3_mode = TIMER3_SOURCE_TIMER_MOD,
    .priority = INTERRUPT_Low_Priority,
    .timer3_preload_value = 3036,
    .timer3_prescaler = TIMER3_PRESCALER_DIV_BY_8,
    .timer3_reg_rw_mode = TIMER3_RW_REG_MODE_16BIT,
};


timer1_t counter1_obj = {
    .TIMER1_InterruptHandler = NULL,
    .timer1_mode = TIMER1_SOURCE_COUNTER_MOD,
    .timer1_preload_value = 0,
    .timer1_prescaler = TIMER1_PRESCALER_DIV_BY_1,
    .timer1_reg_rw_mode = TIMER1_RW_REG_MODE_16BIT,
    .timer1_counter_mode = TIMER1_ASYNC_COUNTER_MOD,
};

int main() { 
    Application_initialize();
    ret = timer3_init(&timer3_obj);
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

/* initialize any pin with direction & logic */
void Application_initialize(void){
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
}
