#ifndef _MCAL_INTERRUPT_CONFIG_H_
#define _MCAL_INTERRUPT_CONFIG_H_

/*Section : Include */
#include "mcal_interrupt_config.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../mcal_std_type.h"
#include "mcal_interrupt_gen_config.h"
#include "../GPIO/hall_gpio.h"

/*Section : Macro Declaration*/

#define INTERRUPT_ENABLE              1
#define INTERRUPT_DISABLE             0
#define INTERRUPT_OCCUR               1
#define INTERRUPT_NOT_OCCUR           0
#define INTERRUPT_PRIORITY_ENABLE     1
#define INTERRUPT_PRIORITY_DISABLE    0

/*Section : Macro Function Decleration*/

#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE

/*to make enalbe  priority interrupt*/
#define INTERRUPT_PriorityLevelEnable() (RCONbits.IPEN= 1)
/*to make disalbe  priority interrupt*/
#define INTERRUPT_PriorityLevelDisable() (RCONbits.IPEN = 0)
/*to make enalbe  high priority global interrupt*/
#define INTERRUPT_GlobalInterruptHighEnable() (INTCONbits.GIEH = 1)
/*to make disalbe all high priority interrupt*/
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)
/*to make enalbe  low priority global interrupt*/
#define INTERRUPT_GlobalInterruptLowEnable() (INTCONbits.GIEL = 1)
/*to make disalbe all low priority interrupt*/
#define INTERRUPT_GlobalInterruptLowDisable() (INTCONbits.GIEL = 0)
#else
/*to make enalbe  global interrupt*/
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
/*to make disalbe  interrupt*/
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
/*to make enalbe peripheral interrupt*/
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
/*to make disalbe peripheral interrupt*/
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif 

typedef enum
{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY 
    
}interrupt_prioity_t;

#endif