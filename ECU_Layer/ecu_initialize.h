/* 
 * File:   ecu_initialize.h
 * Author: zyadi
 *
 * Created on August 22, 2023, 9:07 AM
 */

#ifndef ECU_INITIALIZE_H
#define	ECU_INITIALIZE_H

/*Section : Include :*/
#include "LED/ecu_led.h"
#include "dc_motor/ecu_dc_motor.h"
#include "keypad/ecu_keypad.h"
#include "lcd/ecu_lcd.h"
#include "push_button/ecu_push_button.h"
#include "relay/ecu_relay.h"
#include "seven_seg/ecu_seven_seg.h"


/*Section : Function Declaration*/

void ecu_initialize(void);
#endif	/* ECU_INITIALIZE_H */

