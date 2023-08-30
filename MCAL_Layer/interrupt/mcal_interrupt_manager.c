#include "mcal_interrupt_manager.h"



#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE

void __interrupt() InterruptManagerHigh(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0F  == INTERRUPT_OCCUR  ))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    

    /**
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB5 == 1))
    {
        RB1_ISR();
    }
    else
    {
        
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB6 == 1))
    {
        RB2_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB7 == 1))
    {
        RB3_ISR();
    }
    else
    {
        
    }
    **/
    
    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }
    if((INTCON3bits.INT2E == INTERRUPT_ENABLE) && (INTCON3bits.INT2F  == INTERRUPT_OCCUR  ))
    {
        INT2_ISR();
    }
    else
    {
        
    }
    
     if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }

    
}

void __interrupt(low_priority) InterruptManagerLow(void)
{


        
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB4 == GPIO_HIGH))
    {
        RB0_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB4 == GPIO_LOW))
    {
        RB0_ISR();
    }
    else
    {
        
    }
}
#else

void __interrupt() InterruptManagerHigh(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0F  == INTERRUPT_OCCUR  ))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB4 == GPIO_HIGH))
    {
        RB0_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB4 == GPIO_LOW))
    {
        RB0_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB5 == 1))
    {
        RB1_ISR();
    }
    else
    {
        
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB6 == 1))
    {
        RB2_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB7 == 1))
    {
        RB3_ISR();
    }
    else
    {
        
    }
    
    
    
    


    
}

#endif




