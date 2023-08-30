#include "mcal_external_interrupt.h"


static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;


static void (*RB0_InterruptHandler)(void) = NULL;
static void (*RB1_InterruptHandler)(void) = NULL;
static void (*RB2_InterruptHandler)(void) = NULL;
static void (*RB3_InterruptHandler)(void) = NULL;


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t * int_obj);


static Std_ReturnType INT0_SetInterruptHandler( void (*INT_InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler( void (*INT_InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler( void (*INT_InterruptHandler)(void));

static Std_ReturnType Interrupt_INTX_SetInterruptHandler( const interrupt_INTx_t * int_obj);




static Std_ReturnType RB0_SetInterruptHandler( void (*RB_InterruptHandler)(void));
static Std_ReturnType RB1_SetInterruptHandler( void (*RB_InterruptHandler)(void));
static Std_ReturnType RB2_SetInterruptHandler( void (*RB_InterruptHandler)(void));
static Std_ReturnType RB3_SetInterruptHandler( void (*RB_InterruptHandler)(void));

static Std_ReturnType Interrupt_RBX_SetInterruptHandler( const interrupt_RBx_t * int_obj);







static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t * int_obj);


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        /*disable the external interrupt*/
        ret = Interrupt_INTx_Disable(int_obj);
        /*Clear the flag bit*/
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /*detemine edge falling or rising*/
        ret = Interrupt_INTx_Edge_Init(int_obj);
        /*determine high priority high or low*/
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /*set Function handler*/
        ret = Interrupt_INTX_SetInterruptHandler(int_obj);
        /*initialize input output pin*/
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /*enalbe the interrupt */
        ret = Interrupt_INTx_Enable(int_obj);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

 
void INT0_ISR(void)
{
    EXT_INT0_InterruptFlagClear();
    if(INT0_InterruptHandler != NULL)
    {
        INT0_InterruptHandler();
    }
}


void INT1_ISR(void)
{
    EXT_INT1_InterruptFlagClear();
    if(INT1_InterruptHandler != NULL)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void)
{
    EXT_INT2_InterruptFlagClear();
    if(INT2_InterruptHandler != NULL)
    {
        INT2_InterruptHandler();
    }
}


void RB0_ISR(void)
{
    EXT_RBX_InterruptFlagClear();
    if(RB0_InterruptHandler != NULL)
    {
        RB0_InterruptHandler();
    }
}

void RB1_ISR(void)
{
    EXT_RBX_InterruptFlagClear();
    if(RB1_InterruptHandler != NULL)
    {
        RB1_InterruptHandler();
    }
}
void RB2_ISR(void)
{
    EXT_RBX_InterruptFlagClear();
    if(RB2_InterruptHandler != NULL)
    {
        RB2_InterruptHandler();
    }
}

void RB3_ISR(void)
{
    EXT_RBX_InterruptFlagClear();
    if(RB3_InterruptHandler != NULL)
    {
        RB3_InterruptHandler();
    }
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_INTx_Deinit(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        ret = Interrupt_INTx_Disable(int_obj);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t * int_obj)/********************************************/
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        /*Disable the interrupt*/
        ret = Interrupt_RBx_Disable(int_obj);
        /*Clear the flage */
        EXT_RBX_InterruptFlagClear();
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
        ret = Interrupt_RBx_Priority_Init(int_obj);
        #endif

        /*initialize input output pin*/
        ret = Interrupt_RBx_Pin_Init(int_obj);
        /*Path fucntion to layer*/
        ret = Interrupt_RBX_SetInterruptHandler(int_obj);
        /*Initialize the pin on change*/
        ret = Interrupt_RBx_Enable(int_obj);
        
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        EXT_RBX_InterruptDisable();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}




/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
                
                INTERRUPT_PriorityLevelEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();

                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_INT1:
                #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
                
                INTERRUPT_PriorityLevelEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();

                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_INT2:
                #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
                
                INTERRUPT_PriorityLevelEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();

                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_InterruptEnable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t * int_obj)
{
    
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptDisable();
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}
#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t * int_obj)
{
    
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY)
                {
                    
                }
                else if (int_obj->priority == INTERRUPT_HIGH_PRIORITY)
                {
                    
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_INT1:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT1_LowPrioritySet() ;
                }
                else if (int_obj->priority == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT1_HighPrioritySet() ;
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_INT2:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT2_LowPrioritySet(); 
                }
                else if (int_obj->priority == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT2_HighPrioritySet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t * int_obj)
{
    
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else if (int_obj->edge == INTERRUPT_RASING_EDGE)
                {
                    EXT_INT0_RisingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_INT1:
               if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else if (int_obj->edge == INTERRUPT_RASING_EDGE)
                {
                    EXT_INT1_RisingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_INT2:
               if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else if (int_obj->edge == INTERRUPT_RASING_EDGE)
                {
                    EXT_INT2_RisingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
            ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));

    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t * int_obj)

{
    
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptFlagClear();
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}


/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
       
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
                
        INTERRUPT_PriorityLevelEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();

        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        EXT_RBX_InterruptEnable(); 
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t * int_obj)
{
        Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        EXT_RBX_InterruptDisable();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        if(int_obj->priority == INTERRUPT_HIGH_PRIORITY )
        {
            EXT_RBX_HighPrioritySet() ;
        }
        else if(int_obj->priority == INTERRUPT_LOW_PRIORITY)
        {
            EXT_RBX_LowPrioritySet(); 
        }
        else
        {
            ret = E_NOT_OK;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */

static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t * int_obj)
{
     Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}



/**
 * 
 * @param INT_InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_SetInterruptHandler( void (*INT_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(INT_InterruptHandler != NULL)
    {
        INT0_InterruptHandler = INT_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param INT_InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_SetInterruptHandler( void (*INT_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(INT_InterruptHandler != NULL)
    {
        INT1_InterruptHandler = INT_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param INT_InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_SetInterruptHandler( void (*INT_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(INT_InterruptHandler != NULL)
    {
        INT2_InterruptHandler = INT_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_SetInterruptHandler( const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->source)
        {
            case INTERRUPT_INT0:
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT1:
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT2:
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}




/**
 * 
 * @param RB_InterruptHandler
 * @return 
 */

static Std_ReturnType RB0_SetInterruptHandler( void (*RB_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(RB_InterruptHandler != NULL)
    {
        RB0_InterruptHandler = RB_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param RB_InterruptHandler
 * @return 
 */
static Std_ReturnType RB1_SetInterruptHandler( void (*RB_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(RB_InterruptHandler != NULL)
    {
        RB1_InterruptHandler = RB_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param RB_InterruptHandler
 * @return 
 */
static Std_ReturnType RB2_SetInterruptHandler( void (*RB_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(RB_InterruptHandler != NULL)
    {
        RB2_InterruptHandler = RB_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param RB_InterruptHandler
 * @return 
 */
static Std_ReturnType RB3_SetInterruptHandler( void (*RB_InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(RB_InterruptHandler != NULL)
    {
        RB3_InterruptHandler = RB_InterruptHandler;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */

static Std_ReturnType Interrupt_RBX_SetInterruptHandler( const interrupt_RBx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj != NULL)
    {
        switch(int_obj->mcu_pin.pin)
        {
            case GPIO_PIN4:
                ret = RB0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case GPIO_PIN5:
                ret = RB1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case GPIO_PIN6:
                 ret = RB2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case GPIO_PIN7:
                ret = RB3_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                 break;
                 
            default:
                ret = E_NOT_OK;
                break;
              
                
        }
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}