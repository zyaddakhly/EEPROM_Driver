#ifndef _ECU_SEVEN_SEG_H_
#define _ECU_SEVEN_SEG_H_
/*Section : Include*/
#include "ecu_seven_seg_config.h"
#include "../../MCAL_Layer/GPIO/hall_gpio.h"
/*Section : User Data Type*/
typedef enum
{
    SEG_PIN0,
    SEG_PIN1,
    SEG_PIN2,
    SEG_PIN3
    
}seg_pin_t;

typedef enum
{
    SEG_COMMON_ANODE,
    SEG_COMMON_CATHOD
    
}seg_type_t;


typedef struct
{
    pin_config_t segment[4];
    seg_type_t seg_type;
    
}seg_t;

/*Section : Function Decleration*/
Std_ReturnType seven_seg_initialize(const seg_t *segment);
Std_ReturnType seven_seg_write_number(const seg_t *segment,uint8 num);

#endif