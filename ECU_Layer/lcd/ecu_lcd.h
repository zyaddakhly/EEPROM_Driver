/* 
 * File:   ecu_lcd.h
 * Author: mahdy
 *
 * Created on August 10, 2023, 4:41 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section : Includes */
#include "ecu_lcd.h"
#include "../../MCAL_Layer/GPIO/hall_gpio.h"
/* Section : Macro Declarations */
#define _LCD_CLEAR                  0x01
#define _LCD_RETURN_HOME            0x02
#define _LCD_ENTRY_MODE             0x06
#define _LCD_CURSOR_OFF_DISPLY_ON   0x0C
#define _LCD_CURSOR_OFF_DISPLY_OFF  0x08
#define _LCD_CURSOR_ON_BLINK_ON     0x0F
#define _LCD_CURSOR_ON_BLINK_OFF    0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT    0x1C
#define _LCD_DISPLAY_SHIFT_LEFT     0x18
#define _LCD_8BIT_MODE_2_LINE       0x38
#define _LCD_4BIT_MODE_2_LINE       0x28
#define _LCD_CGRAM_START            0x40
#define _LCD_DDRAM_START            0x80
#define ROW1_POSITION               0x80
#define ROW2_POSITION               0xC0
#define ROW3_POSITION               0x94
#define ROW4_POSITION               0xd4





#define LCD_8BIT                   (uint8)8
#define LCD_4BIT                   (uint8)4

#define ROW1                       (uint8)1
#define ROW2                       (uint8)2
#define ROW3                       (uint8)3
#define ROW4                       (uint8)4

#define MAX_ROW                    (uint8)4
#define MAX_COLUM                  (uint8)20


/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;
/* Section : Function Prototype */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t * lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t * lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t * lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t * lcd, uint8 row, uint8 colum, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t * lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t * lcd, uint8 row, uint8 colum, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t * lcd, uint8 row
                                         , uint8 colum, uint8 ch[], uint8 pos);

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t * lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t * lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t * lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t * lcd, uint8 row, uint8 colum, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t * lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t * lcd, uint8 row, uint8 colum, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t * lcd, uint8 row
                                         , uint8 colum, uint8 ch[], uint8 pos);

Std_ReturnType convert_byte_to_str(uint8 value, uint8 *str);
Std_ReturnType convert_short_to_str(uint16 value, uint8 *str);
Std_ReturnType convert_int_to_str(uint32 value, uint8 *str);
#endif	/* ECU_LCD_H */

