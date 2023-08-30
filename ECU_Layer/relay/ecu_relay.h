#ifndef _ECU_RELAY_H_
#define _ECU_RELAY_H_
/*Section : Include*/
#include "ecu_relay_config.h"
#include "../../MCAL_Layer//GPIO/hall_gpio.h"

/*Section : User data type*/

typedef enum 
{
    RELAY_OFF_STATUS = 0,
    RELAY_ON_STATUS
    
}relay_status_t;

typedef struct 
{
    uint8 relay_port   : 4;
    uint8 relay_pin    : 3;
    uint8 relay_status : 1;
    
}relay_t;
/*Section : Function Declearation*/


/**
 * @brief to initialize the pin and make it output
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *relay);
/**
 * @brief Turn the Relay on 
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay);
/**
 * @brief Turn the Relay off 
 * @param relay pinter to the relay module configurations
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_OK) : the function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay);




#endif