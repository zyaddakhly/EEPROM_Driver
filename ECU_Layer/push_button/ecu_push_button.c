#include "ecu_push_button.h"


/**
 * @brief Initialize the assigned pin to be input
 * @param btn pointer to the button configuration
 * @return State of the function
 *          (E_OK)     : if function done successfuly
 *          (E_NOT_OK) : if function has issue
 */
Std_ReturnType button_initialize(button_t *btn)
{
    Std_ReturnType ret = E_OK;
    if(btn != NULL)
    {
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
            
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
            
            
    
}
/**
 * @brief Initialize the assigned pin to be input
 * @param btn pointer to the button configuration
 * @return State of the function
 *          (E_OK)     : if function done successfuly
 *          (E_NOT_OK) : if function has issue
 */
Std_ReturnType button_read_state(button_t *btn,button_state_t *btn_state)
{
    Std_ReturnType ret = E_OK;
    logic_t logic = GPIO_HIGH;
    if(btn != NULL && btn_state != NULL)
    {
        if(btn->button_active == BUTTON_ACTIVE_HIGH)
        {
            ret = gpio_pin_read_logic(&(btn->button_pin),&logic);
            if(logic == GPIO_HIGH)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_active == BUTTON_ACTIVE_LOW)
        {
            ret = gpio_pin_read_logic(&(btn->button_pin),&logic);
            if(logic == GPIO_LOW)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
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