/* 
 * File:   ecu_lcd.c
 * Author: mahdy
 *
 * Created on August 10, 2023, 4:41 PM
 */

#include "ecu_lcd.h"


static Std_ReturnType send_enable_signal_lcd_8bit(lcd_8bit_t *lcd);
static Std_ReturnType send_enable_signal_lcd_4bit(lcd_4bit_t *lcd);
static Std_ReturnType load_data_lcd_8bit(lcd_8bit_t *lcd,uint8 data);
static Std_ReturnType load_data_lcd_4bit(lcd_4bit_t *lcd,uint8 data);
static Std_ReturnType set_cursor_lcd_8bit(lcd_8bit_t *lcd,uint8 row,uint8 colum);


Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t * lcd, uint8 command);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t * lcd, uint8 command);
static Std_ReturnType set_cursor_lcd_4bit(lcd_4bit_t *lcd,uint8 row,uint8 colum);


/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret &= gpio_pin_initalize(&(lcd->lcd_rs));
        ret &= gpio_pin_initalize(&(lcd->lcd_en));
        
        uint8 count = 0;
        for(count = 0; count < LCD_4BIT; count++)
        {
            ret &= gpio_pin_initalize(&(lcd->lcd_data[count]));
        }
        __delay_ms(20);
        ret &= lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret &= lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
            
        ret &= lcd_4bit_send_command(lcd , _LCD_CLEAR);
        ret &= lcd_4bit_send_command(lcd , _LCD_RETURN_HOME);
        ret &= lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret &= lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLY_ON);
        ret &= lcd_4bit_send_command(lcd , _LCD_DDRAM_START);
        ret &= lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);

    }
    else
    {
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t * lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        
        ret = load_data_lcd_4bit(lcd,(command >> 4));
        ret = send_enable_signal_lcd_4bit(lcd);
        ret = ret = load_data_lcd_4bit(lcd,(command));
        ret = send_enable_signal_lcd_4bit(lcd);

        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t * lcd, uint8 data)
{
        Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        
        ret = load_data_lcd_4bit(lcd,(data>> 4));
        ret = send_enable_signal_lcd_4bit(lcd);
        ret = ret = load_data_lcd_4bit(lcd,(data));
        ret = send_enable_signal_lcd_4bit(lcd);

        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t * lcd, uint8 row, uint8 colum, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        if((row <= MAX_ROW) && (colum <= MAX_COLUM))
        {
            ret = set_cursor_lcd_4bit(lcd,row,colum);
            ret = lcd_4bit_send_char_data(lcd,data);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t * lcd, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        uint8 count = 0;
        while(*(str + count) !='\0')
        {
            ret &= lcd_4bit_send_char_data(lcd,*(str + count));
            count++;
            
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t * lcd, uint8 row, uint8 colum, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        if((row <= MAX_ROW) && (colum <= MAX_COLUM))
        {
            ret = set_cursor_lcd_4bit(lcd,row,colum);
            ret = lcd_4bit_send_string( lcd, str);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param ch
 * @param pos
 * @return 
 */

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t * lcd, uint8 row
                                         , uint8 colum, uint8 ch[], uint8 pos)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START +(pos * 8)));
        uint8 count = 0;
        for(count = 0; count < 8; count++)
        {
            ret = lcd_4bit_send_char_data(lcd,ch[count]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd,row,colum,pos);
        
   
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret &= gpio_pin_initalize(&(lcd->lcd_rs));
        ret &= gpio_pin_initalize(&(lcd->lcd_en));
        
        uint8 count = 0;
        for(count = 0; count < LCD_8BIT; count++)
        {
            ret &= gpio_pin_initalize(&(lcd->lcd_data[count]));
        }
        __delay_ms(20);
        ret &= lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret &= lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
            
        ret &= lcd_8bit_send_command(lcd , _LCD_CLEAR);
        ret &= lcd_8bit_send_command(lcd , _LCD_RETURN_HOME);
        ret &= lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret &= lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLY_ON);
        ret &= lcd_8bit_send_command(lcd , _LCD_DDRAM_START);

    }
    else
    {
        ret = E_NOT_OK;
                
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t * lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        ret = load_data_lcd_8bit(lcd,(command));
        ret = send_enable_signal_lcd_8bit(lcd);
        
    

        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t * lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        ret = load_data_lcd_8bit(lcd,(data));
        ret = send_enable_signal_lcd_8bit(lcd);
        
    
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * @param lcd
 * @param row
 * @param colum
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t * lcd, uint8 row, uint8 colum, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        if((row <= MAX_ROW) && (colum <= MAX_COLUM))
        {
            ret = set_cursor_lcd_8bit(lcd,row,colum);
            ret = lcd_8bit_send_char_data(lcd,data);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
        
    
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t * lcd, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        uint8 count = 0;
        while(*(str + count) !='\0')
        {
            ret &= lcd_8bit_send_char_data(lcd,*(str + count));
            count++;
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
    
}
/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t * lcd, uint8 row, uint8 colum, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        if((row <= MAX_ROW) && (colum <= MAX_COLUM))
        {
            ret = set_cursor_lcd_8bit(lcd,row,colum);
            ret = lcd_8bit_send_string( lcd, str);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param ch
 * @param pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t * lcd, uint8 row
                                         , uint8 colum, uint8 ch[], uint8 pos)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd != NULL)
    {
        ret = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START +(pos * 8)));
        uint8 count = 0;
        for(count = 0; count < 8; count++)
        {
            ret = lcd_8bit_send_char_data(lcd,ch[count]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd,row,colum,pos);
        
   
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
    
    
    
    
    
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_byte_to_str(uint8 value, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(str != NULL)
    {
        memset(str,'\0',4);
        sprintf(str,"%i",value);
  
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_short_to_str(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(str != NULL)
    {
        memset(str,'\0',6);
        sprintf(str,"%i",value);
  
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_int_to_str(uint32 value, uint8 *str)
{
        Std_ReturnType ret = E_NOT_OK;
    if(str != NULL)
    {
        memset(str,'\0',10);
        sprintf(str,"%i",value);
  
    }
    else
    {
        ret = E_NOT_OK;
               
    }
    return ret;
}

static Std_ReturnType load_data_lcd_4bit(lcd_4bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 count = 0;
    for(count = 0; count < LCD_4BIT; count++)
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_data[count]),READ_BIT(data,count));
    }
    return ret;
}

static Std_ReturnType load_data_lcd_8bit(lcd_8bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 count = 0;
    for(count = 0; count < LCD_8BIT; count++)
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_data[count]),READ_BIT(data,count));
    }
    return ret;
}

static Std_ReturnType send_enable_signal_lcd_4bit(lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_us(5);
    ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    return ret;

}

static Std_ReturnType send_enable_signal_lcd_8bit(lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_us(5);
    ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    return ret ;

}

static Std_ReturnType set_cursor_lcd_8bit(lcd_8bit_t *lcd,uint8 row,uint8 colum)
{
    colum--;
    
    Std_ReturnType ret = E_NOT_OK;
    switch(row)
    {
        case ROW1:
            ret = lcd_8bit_send_command(lcd,(ROW1_POSITION + colum));
            break;
        case ROW2:
            ret = lcd_8bit_send_command(lcd,(ROW2_POSITION + colum));
            break;
        case ROW3:
            ret = lcd_8bit_send_command(lcd,(ROW3_POSITION + colum));
            break;
        case ROW4:
            ret = lcd_8bit_send_command(lcd,(ROW4_POSITION + colum));
            break;
        default :
            break;
    }
    
    return ret;
}


static Std_ReturnType set_cursor_lcd_4bit(lcd_4bit_t *lcd,uint8 row,uint8 colum)
{
    colum--;
    
    Std_ReturnType ret = E_NOT_OK;
    switch(row)
    {
        case ROW1:
            ret = lcd_4bit_send_command(lcd,(ROW1_POSITION + colum));
            break;
        case ROW2:
            ret = lcd_4bit_send_command(lcd,(ROW2_POSITION + colum));
            break;
        case ROW3:
            ret = lcd_4bit_send_command(lcd,(ROW3_POSITION + colum));
            break;
        case ROW4:
            ret = lcd_4bit_send_command(lcd,(ROW4_POSITION + colum));
            break;
        default :
            break;
    }
    
    return ret;
}