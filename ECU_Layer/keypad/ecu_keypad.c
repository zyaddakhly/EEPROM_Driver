#include "ecu_keypad.h"



/**
 * 
 * @param keypad
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */

static const uint8 btn_value[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMS] = { {'7','8','9','/'},
                                                                    {'4','5','6','*'},
                                                                    {'1','2','3','-'},
                                                                    {'#','0','=','+'}};
Std_ReturnType keypad_initialize(const keypad_t *keypad)
{
    Std_ReturnType ret = E_OK;
    if(keypad != NULL)
    {
        uint8 con = ZERO_INT;
        for(con = ZERO_INT; con < ECU_KEYPAD_ROWS ; con++)
        {
            ret = gpio_pin_direction_intialize(&(keypad->keypad_row_pin[con]));
        }
        for(con = ZERO_INT; con < ECU_KEYPAD_COLUMS ; con++)
        {
            ret = gpio_pin_direction_intialize(&(keypad->keypad_colums_pin[con]));
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
 * @param keypad pointer refer to the 
 * @param value
 * * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value)
{
    Std_ReturnType ret = E_OK;
    if(keypad != NULL && value != NULL)
    {
        uint8 row = ZERO_INT;
        uint8 colum = ZERO_INT;
        uint8 low = ZERO_INT;
        logic_t colum_logic = ZERO_INT;
        
        for(row = ZERO_INT; row < ECU_KEYPAD_ROWS; row++)
        {
            
            for(low = ZERO_INT; low < ECU_KEYPAD_ROWS; low++)
            {
                ret = gpio_pin_write_logic(&(keypad->keypad_row_pin[low]),GPIO_LOW);
            }
                ret = gpio_pin_write_logic(&(keypad->keypad_row_pin[row]),GPIO_HIGH);
            for(colum = ZERO_INT; colum < ECU_KEYPAD_COLUMS ; colum++)
            {
                ret = gpio_pin_read_logic(&(keypad->keypad_colums_pin[colum]), &colum_logic);
                if(colum_logic == GPIO_HIGH)
                {
                    *value = btn_value[row][colum];
                    colum_logic = GPIO_LOW;
                }
            }
            
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
