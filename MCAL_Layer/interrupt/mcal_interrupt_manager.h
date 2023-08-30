#ifndef _MCAL_INTERRUPT_MANAGER_H_
#define _MCAL_INTERRUPT_MANAGER_H_


/*Section : Include */
#include "mcal_interrupt_config.h"

/*Section : Function Decleration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB0_ISR(void);
void RB1_ISR(void);
void RB2_ISR(void);
void RB3_ISR(void);
#endif