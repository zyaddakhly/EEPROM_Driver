#include "ecu_seven_seg.h"


/**
 * 
 * @param segment
 * @return 
 */
static pin_config_t pin_seg[4];
Std_ReturnType seven_seg_initialize(const seg_t *segment)
{
    Std_ReturnType ret = E_OK;
    if((segment != NULL))
    {
        ret = gpio_pin_initalize(&(segment->segment[SEG_PIN0]));
        ret = gpio_pin_initalize(&(segment->segment[SEG_PIN1]));
        ret = gpio_pin_initalize(&(segment->segment[SEG_PIN2]));
        ret = gpio_pin_initalize(&(segment->segment[SEG_PIN3]));
        
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    
}
/**
 * 
 * @param segment
 * @param num
 * @return 
 */
Std_ReturnType seven_seg_write_number(const seg_t *segment,uint8 num)
{
    Std_ReturnType ret = E_OK;
    if((segment != NULL) && (num < 10))
    {
        ret = gpio_pin_write_logic(&(segment->segment[SEG_PIN0]),READ_BIT(num,SEG_PIN0));
        ret = gpio_pin_write_logic(&(segment->segment[SEG_PIN1]),READ_BIT(num,SEG_PIN1));
        ret = gpio_pin_write_logic(&(segment->segment[SEG_PIN2]),READ_BIT(num,SEG_PIN2));
        ret = gpio_pin_write_logic(&(segment->segment[SEG_PIN3]),READ_BIT(num,SEG_PIN3));
        
        
    }
    else
    {
        ret = E_NOT_OK;
        
    }
    
}
