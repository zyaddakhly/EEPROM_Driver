#ifndef _MCAL_EXTERNAL_INTERRUPT_H_
#define _MCAL_EXTERNAL_INTERRUPT_H_

/*Section : Include*/
#include "mcal_interrupt_config.h"



/*Section : Macro Defination*/


#if EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE == FEATURE_ENALE

/*Disable the external pin INT0 */
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0E = 0)
/*Enable the external pin INT0 */
#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0E = 1)
/*Clear flag bit for INT0 */
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0F = 0)
/*Make INT0 Rising Edge*/
#define EXT_INT0_RisingEdgeSet()        (INTCON2bits.INTEDG0 = 1)
/*Make INT0 Failing Edge*/
#define EXT_INT0_FallingEdgeSet()       (INTCON2bits.INTEDG0 = 0)


/*Disable the external pin INT1 */
#define EXT_INT1_InterruptDisable()     (INTCON3bits.INT1E = 0)
/*Enable the external pin INT1 */
#define EXT_INT1_InterruptEnable()      (INTCON3bits.INT1E = 1)
/*Clear flag bit for INT1 */
#define EXT_INT1_InterruptFlagClear()   (INTCON3bits.INT1IF = 0)
/*Make INT1 Rising Edge*/
#define EXT_INT1_RisingEdgeSet()        (INTCON2bits.INTEDG1 = 1)
/*Make INT1 Failing Edge*/
#define EXT_INT1_FallingEdgeSet()       (INTCON2bits.INTEDG1 = 0)



/*Disable the external pin INT2 */
#define EXT_INT2_InterruptDisable()     (INTCON3bits.INT2E = 0)
/*Enable the external pin INT2 */
#define EXT_INT2_InterruptEnable()      (INTCON3bits.INT2E = 1)
/*Clear flag bit for INT2 */
#define EXT_INT2_InterruptFlagClear()   (INTCON3bits.INT2IF = 0)
/*Make INT2 Rising Edge*/
#define EXT_INT2_RisingEdgeSet()        (INTCON2bits.INTEDG2 = 1)
/*Make INT2 Failing Edge*/
#define EXT_INT2_FallingEdgeSet()       (INTCON2bits.INTEDG2 = 0)


#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
/*Make INT1 HIGH Priority*/
#define EXT_INT1_HighPrioritySet()          (INTCON3bits.INT1IP = 1)
/*Make INT1 Low Priority*/
#define EXT_INT1_LowPrioritySet()          (INTCON3bits.INT1IP = 0)

/*Make INT1 HIGH Priority*/
#define EXT_INT2_HighPrioritySet()          (INTCON3bits.INT2IP = 1)
/*Make INT1 Low Priority*/
#define EXT_INT2_LowPrioritySet()          (INTCON3bits.INT2IP = 0)


#endif 



#endif


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == FEATURE_ENALE


/*Disable the external pin PortB On Change */
#define EXT_RBX_InterruptDisable()     (INTCONbits.RBIE = 0)
/*Enable the external pin PortB On Change */
#define EXT_RBX_InterruptEnable()      (INTCONbits.RBIE = 1)
/*Clear flag bit for PortB */
#define EXT_RBX_InterruptFlagClear()   (INTCONbits.RBIF = 0)




#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
/*Make PORTB HIGH Priority*/
#define EXT_RBX_HighPrioritySet()          (INTCON2bits.RBIP = 1)
/*Make PORTB Low Priority*/
#define EXT_RBX_LowPrioritySet()           (INTCON2bits.RBIP = 0)

#endif 

#endif

/*Section : User Data Type*/
typedef enum
{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RASING_EDGE 
    
}interrupt_INTx_edge;


typedef enum
{
    INTERRUPT_INT0 = 0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
    
}interrupt_INTx_src;




typedef struct 
{
    void (*EXT_InterruptHandler) (void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_prioity_t priority;
    
}interrupt_INTx_t;


typedef struct 
{
    void (*EXT_InterruptHandler) (void);
    pin_config_t mcu_pin;
    interrupt_prioity_t priority;
    
}interrupt_RBx_t;


/*Section : Function Declaration*/


Std_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj);
Std_ReturnType interrupt_INTx_Deinit(const interrupt_INTx_t * int_obj);


Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t * int_obj);
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t * int_obj);

#endif