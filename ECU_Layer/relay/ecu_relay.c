#include "ecu_relay.h"







/**
 * @brief to initialize the pin and make it output
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin_config;
    
    if(relay != NULL)
    {
        pin_config.port = relay->relay_port;
        pin_config.pin = relay->relay_pin ;
        pin_config.direction = GPIO_OUTPUT ;
        pin_config.logic = relay->relay_status;
        ret = gpio_pin_initalize(&pin_config);
    }
    else
    {
        ret = E_NOT_OK;
    }
}
/**
 * @brief Turn the Relay on 
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin_config;
    
    if(relay != NULL)
    {
        pin_config.port = relay->relay_port;
        pin_config.pin = relay->relay_pin ;
        pin_config.direction = GPIO_OUTPUT ;
        pin_config.logic = GPIO_LOW;
        ret = gpio_pin_write_logic(&pin_config,GPIO_HIGH);
    }
    else
    {
        ret = E_NOT_OK;
    }
}
/**
 * @brief Turn the Relay off 
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    pin_config_t pin_config;
    
    if(relay != NULL)
    {
        pin_config.port = relay->relay_port;
        pin_config.pin = relay->relay_pin ;
        pin_config.direction = GPIO_OUTPUT ;
        pin_config.logic = GPIO_LOW;
        ret = gpio_pin_write_logic(&pin_config,GPIO_LOW);
    }
    else
    {
        ret = E_NOT_OK;
    }
}
