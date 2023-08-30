/* 
 * File:   ecu_led.h
 * Author: zyadi
 *
 * Created on August 15, 2023, 12:10 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*Section : Include */
#include "../../MCAL_Layer/GPIO/hall_gpio.h"
#include "ecu_led_config.h"
/*Section : Macro Declaration */

/*Section : Macro Function Declaration*/



/*Section :  Data Type Declaration*/
typedef enum
{
    LED_OFF,
    LED_ON
}led_status;

typedef struct
{
    uint8 port         : 4;
    uint8 pin          : 3;
    uint8 led_status   : 1;
}led_t;

/*Section Function Declaration*/
/**
 * @brief initialize the assigned pin to be OUTPUT and turn the led off
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
Std_ReturnType led_initialize(const led_t *led);
/**
 * @brief  turn the led on
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
Std_ReturnType led_turn_on(const led_t *led);
/**
 * @brief  turn the led off
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
Std_ReturnType led_turn_off(const led_t *led);
/**
 * @brief toggle  the status of the led
 * @param led : pointer to the led module configuration
 * @return Status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
Std_ReturnType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */

