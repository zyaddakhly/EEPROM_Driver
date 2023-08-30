
#include "hall_gpio.h"

/*reference to data direction control register*/
volatile uint8 *tris_register[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*reference to data latch register (read and write*/
volatile uint8 *lat_register[] = {&LATA,&LATB,&LATC,&LATD,&LATE};
/*reference to data direction control register*/

volatile uint8 *port_register[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};


/**
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 *  
 */

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * pin_config)
{
    Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL)
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
            switch(pin_config->direction)
            {
                case GPIO_INPUT :
                    SET_BIT(*tris_register[pin_config->port],pin_config->pin);
                    break;
                case GPIO_OUTPUT :
                    CLEAR_BIT(*tris_register[pin_config->port],pin_config->pin);
                    break;
                default :
                    ret = E_NOT_OK;
                    break;
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
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * pin_config,direction_t *direction)
{
    Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL && direction != NULL)
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
        {
            *direction = READ_BIT(*tris_register[pin_config->port],pin_config->pin);
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
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @param logic
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config,logic_t logic)
{
    Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL)
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
            switch(logic)
            {
                case GPIO_HIGH:
                    SET_BIT(*lat_register[pin_config->port],pin_config->pin);
                    break;
                case GPIO_LOW :
                    CLEAR_BIT(*lat_register[pin_config->port],pin_config->pin);
                    break;
                default :
                    ret = E_NOT_OK;
                    break;
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
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @param logic
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config,logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL && logic != NULL)
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
        {
            *logic= READ_BIT(*port_register[pin_config->port],pin_config->pin);
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
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_pin_initalize(const pin_config_t * pin_config)
{
        Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL )
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
        {
            gpio_pin_direction_intialize(pin_config);
            gpio_pin_write_logic(pin_config,pin_config->logic);
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
 * 
 * @param pin_config pointer to the configuration  @ref port_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config)
{
    Std_ReturnType ret = E_OK;
    
    if(pin_config != NULL)
    {
        if((pin_config->pin < PORT_PIN_MAX_NUMBER) && (pin_config->port <= PORT_MAX_NUMBER))
         {
            TOGGLE_BIT(*lat_register[pin_config->port],pin_config->pin);
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
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE


Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if(port <= PORT_MAX_NUMBER)
    {
        *tris_register[port] = direction;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 * direction)
{
    Std_ReturnType ret = E_OK;
    if(direction != NULL)
    {
        
        if(port <= PORT_MAX_NUMBER)
        {
            *direction = *tris_register[port];
        }
        else
        {
            ret = E_NOT_OK;
        }
        return ret;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_port_write_logic(port_index_t port,uint8  logic)
{
    Std_ReturnType ret = E_OK;
    if(port <= PORT_MAX_NUMBER)
    {
        *lat_register[port] = logic;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_port_read_logic(port_index_t port,uint8  *logic)
{
    Std_ReturnType ret = E_OK;
    if(logic != NULL)
    {
        
        if(port <= PORT_MAX_NUMBER)
        {
            *logic = *port_register[port];
        }
        else
        {
            ret = E_NOT_OK;
        }
        return ret;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
#endif
/**
 * 
 * @param port 
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if(port <= PORT_MAX_NUMBER)
    {
        *lat_register[port] = (*lat_register[port]) ^ GPIO_PORT_TOGGLE_MASK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
#endif


