#ifndef _ECU_KEYPAD_H_
#define _ECU_KEYPAD_H_


/*Section : Incluse*/

#include "ecu_keypad_config.h"
#include "../../MCAL_Layer/GPIO/hall_gpio.h"


/*Section : Macro Defination*/
#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COLUMS   4
#define ZERO_INT 0
/*Section : User Data Type*/

typedef struct
{
    pin_config_t  keypad_row_pin[ECU_KEYPAD_ROWS];
    
    pin_config_t  keypad_colums_pin[ECU_KEYPAD_COLUMS];
    
}keypad_t;




/*Section : Function Declearation*/
Std_ReturnType keypad_initialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value);




#endif 