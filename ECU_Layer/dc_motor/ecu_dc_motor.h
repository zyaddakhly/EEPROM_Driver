#ifndef _ECU_DC_MOTOR_H_
#define _ECU_DC_MOTOR_H_
/*Section : Incluse*/
#include "ecu_dc_motor_config.h"
#include "../../MCAL_Layer/GPIO/hall_gpio.h"

/*Section : User Data Type*/


typedef enum {
    DC_MOTOR_OFF,
    DC_MOTOR_ON
}dc_motor_status_t;

typedef struct 
{
    uint8 dc_motor_port   : 4;
    uint8 dc_motor_pin    : 3;
    uint8 dc_motor_status : 1;
    
    
}dc_motor_pin_t;

typedef struct 
{
    dc_motor_pin_t dc_motor[2];
}dc_motor_t;

/*Section : Function Declearation*/
Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);





#endif