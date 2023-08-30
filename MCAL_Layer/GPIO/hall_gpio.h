/* 
 * File:   hall_gpio.h
 * Author: zyadi
 *
 * Created on August 14, 2023, 11:35 PM
 */

#ifndef HALL_GPIO_H
#define	HALL_GPIO_H

/*Section : Include */
#include "../../pic/include/proc/pic18f4620.h"
#include "../mcal_std_type.h"
#include "../device_configuration.h"
#include "gpio_config.h"







/*Section : Macro Declaration */
#define _XTAL_FREQ 4000000UL
#define BIT_MASK    (uint8) 1
#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER     5
#define GPIO_PORT_TOGGLE_MASK 0xff

/*Section : Macro Function Declaration*/
#define HWREG8(_X)      (*(volatile uint8 *)_X)

#define SET_BIT(REG,BIT)    ((REG) |= (BIT_MASK<<(BIT)))
#define CLEAR_BIT(REG,BIT)  ((REG) &= ~(BIT_MASK<<(BIT)))
#define TOGGLE_BIT(REG,BIT) ((REG) ^= (BIT_MASK<<(BIT)))
#define READ_BIT(REG,BIT)   ((REG >> BIT) & BIT_MASK)


/*Section :  Data Type Declaration*/
typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum
{
    GPIO_OUTPUT = 0,
    GPIO_INPUT
}direction_t;

typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}Pin_index_t;



typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX, 
    PORTE_INDEX
    
}port_index_t;

typedef struct
{
    uint8 port       : 3;
    uint8 pin        : 3;
    uint8 direction  : 1;
    uint8 logic      : 1;
    
}pin_config_t;






/* Section Macro Function Declaration*/
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * pin_config,direction_t *direction);
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config,logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config);
Std_ReturnType gpio_pin_initalize(const pin_config_t * pin_config);



Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 * direction);
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8  logic);
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8  *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);










#endif	/* HALL_GPIO_H */








