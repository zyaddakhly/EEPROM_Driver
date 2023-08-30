#include "hal_eeprom.h"



/**
 * 
 * @param bAdd the addresse of data on eeprom to wriet
 * @param bData the data which want to store in eeprom
 * @return the status of function 
 *          @ret (E_OK) if function successfuly
 *          @ret (E_NOT_OK) if function not successfuly
 */
Std_ReturnType Data_EEPROM_WriteBye(uint16 bAdd,uint8 bData)
{
    Std_ReturnType ret = E_OK;
    /*Read the interrupt "Status"*/
    uint8 Global_InterruptStatus = INTERRUPT_GET_STATUS;
    /* Update the Addresse Register*/
    ADDRESE_HIGH(bAdd);
    ADDRESE_LOW(bAdd);
    /*Update the data register*/
    ADD_DATA(bData) ;
    /*Select Access Data EEPROM Memory*/
    ACCESS_EEPROM();
    ACCESS_EEPROM_FLASH_PATH();  
    /*Allows write cycles to flash program/EEPROM*/
    WRITE_FLASH_EEPROM(ENABLE);
    /*Disable All Interrupt*/
    INTERRUPT_STATUS(DISABLE);
    /*Write the required Sequence :0x55->0xAA */
    WRITE_SEQUENCE(0x55);
    WRITE_SEQUENCE(0xAA);
    /*Initialize data EEPROM Write cycle*/
    WRITE_EEPROM_START();
    /*wait for write complete*/
    while(WRITE_STATUS);
    /*disable the write cycle*/
    WRITE_FLASH_EEPROM(DISABLE);
    /*Restore the interrupt*/
    INTERRUPT_STATUS(Global_InterruptStatus);
    
    return ret;
}
/**
 * 
 * @param bAdd the addresse of data on eeprom to read
 * @param pointer point to  the data which want to read from eeprom
 * @return the status of function 
 *          @ret (E_OK) if function successfuly
 *          @ret (E_NOT_OK) if function not successfuly
 */

Std_ReturnType Data_EEPROM_ReadBye(uint16 bAdd,uint8 *bData)
{
    Std_ReturnType ret = E_OK;
    if(bData != NULL)
    {
           /* Update the Addresse Register*/
            ADDRESE_HIGH(bAdd);
            ADDRESE_LOW(bAdd);
            /*Select Access Data EEPROM Memory*/
            ACCESS_EEPROM();
            ACCESS_EEPROM_FLASH_PATH();
            /*Initiates a data EEPROM read cycle*/
            READ_EEPROM(); 
            /*Make two nop to operation*/
            NOP();
            NOP();
            /*READ DATA*/
            READ_DATA(*bData);
            
            
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}