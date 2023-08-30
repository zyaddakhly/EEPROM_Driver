/* 
 * File:   application.c
 * Author: zyadi
 *
 * Created on August 18, 2023, 8:01 AM
 */

#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"

Std_ReturnType ret = 0;
uint8 Counter = 0;
uint8 Data = 0;


led_t led1 = 
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = LED_ON
};
led_t led2 = 
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = LED_ON
};

void Int0_ISR(void)
{
    Counter++;
}



interrupt_INTx_t Intx0 =
{
    .EXT_InterruptHandler = Int0_ISR,
    .edge = INTERRUPT_RASING_EDGE ,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin  = GPIO_PIN0,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_INT0   
    
};

void Program1(void)
{
    led_turn_on(&led1);
    __delay_ms(250);
    led_turn_off(&led1);
     __delay_ms(250);

}
void Program2(void)
{
    led_turn_on(&led2);
    __delay_ms(250);
    led_turn_off(&led2);
     __delay_ms(250);

}

void Program3(void)
{

    led_turn_off(&led2);
    led_turn_off(&led1);

}


int main() {
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = interrupt_INTx_init(&Intx0);
  
    while(1)
    {
        ret = Data_EEPROM_WriteBye(0x03ff,Counter);
        ret = Data_EEPROM_ReadBye(0x03ff,&Data);
        if(Data == 6)
        {
            Program1();
        }
        else if(Data == 7)
        {
            Program2();
        }
        else if(Counter > 8)
        {
            Counter = 0;
            
            Program3();
        }
    }


    return 0;
}

