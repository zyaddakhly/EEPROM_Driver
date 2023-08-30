/* 
 * File:   ecu_push_button.h
 * Author: zyadi
 *
 * Created on August 18, 2023, 2:09 PM
 */

#ifndef ECU_PUSH_BUTTON_H
#define	ECU_PUSH_BUTTON_H
/* Section : Include */
#include "../../MCAL_Layer/GPIO/hall_gpio.h"
#include "ecu_push_button_config.h"

/* Section : User Data Type*/


typedef enum {
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;


typedef enum {
    BUTTON_ACTIVE_HIGH = 0,
    BUTTON_ACTIVE_LOW
}button_active_t;


typedef struct
{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_active;
}button_t;

/*Section : Function Declaration*/
/**
 * @brief Initialize the assigned pin to be input
 * @param btn pointer to the button configuration
 * @return State of the function
 *          (E_OK)     : if function done successfuly
 *          (E_NOT_OK) : if function has issue
 */
Std_ReturnType button_initialize(button_t *btn);
/**
 * @brief Initialize the assigned pin to be input
 * @param btn pointer to the button configuration
 * @return State of the function
 *          (E_OK)     : if function done successfuly
 *          (E_NOT_OK) : if function has issue
 */
Std_ReturnType button_read_state(button_t *btn,button_state_t *btn_state);

#endif	/* ECU_PUSH_BUTTON_H */

