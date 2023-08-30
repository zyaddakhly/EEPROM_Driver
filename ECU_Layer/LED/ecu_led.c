#include "ecu_led.h"



/**
 * @brief initialize the assigned pin to be OUTPUT and turn the led off
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
#if ECU_LED == CONFIG_ENABLE
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin;
    if(NULL != led)
    {
        if((led->port <= PORT_MAX_NUMBER)&& (led->pin <= PORT_PIN_MAX_NUMBER))
        {
            pin.direction = GPIO_OUTPUT;
            pin.port = led->port;
            pin.pin = led->pin;
            pin.logic = GPIO_LOW;
            gpio_pin_initalize(&pin);
            
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
#endif
/**
 * @brief  turn the led on
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
#if ECU_LED == CONFIG_ENABLE
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin;
    if(NULL != led)
    {
        if((led->port <= PORT_MAX_NUMBER)&& (led->pin <= PORT_PIN_MAX_NUMBER))
        {
            pin.direction = GPIO_OUTPUT;
            pin.port = led->port;
            pin.pin = led->pin;
            pin.logic = led->led_status;
            gpio_pin_write_logic(&pin,GPIO_HIGH);
            
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
#endif
/**
 * @brief  turn the led off
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
#if ECU_LED == CONFIG_ENABLE
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin;
    if(NULL != led)
    {
        if((led->port <= PORT_MAX_NUMBER)&& (led->pin <= PORT_PIN_MAX_NUMBER))
        {
            pin.direction = GPIO_OUTPUT;
            pin.port = led->port;
            pin.pin = led->pin;
            pin.logic = led->led_status;
            gpio_pin_write_logic(&pin,GPIO_LOW);
            
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
#endif
/**
 * @brief toggle  the status of the led
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
#if ECU_LED == CONFIG_ENABLE
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin;
    if(NULL != led)
    {
        if((led->port <= PORT_MAX_NUMBER)&& (led->pin <= PORT_PIN_MAX_NUMBER))
        {
            pin.direction = GPIO_OUTPUT;
            pin.port = led->port;
            pin.pin = led->pin;
            pin.logic = led->led_status;
            gpio_pin_toggle_logic(&pin);        
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
#endif