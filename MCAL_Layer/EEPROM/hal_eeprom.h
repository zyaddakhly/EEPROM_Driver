/* 
 * File:   hal_eeprom.h
 * Author: zyadi
 *
 * Created on August 30, 2023, 6:10 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*Section : Include */

#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_type.h"


/*Section Macro Declaration*/

#define INTERRUPT_GET_STATUS INTCONbits.GIE
#define ENABLE           1
#define DISABLE          0  
#define WRITE_STATUS     EECON1bits.WR


/*Section : macro function declaration*/

#define ADDRESE_HIGH(Add)                (EEADRH = (uint8)((Add >> 8) & 0x03))
#define ADDRESE_LOW(Add)                 (EEADR  = (uint8) (Add & 0xff))
#define INTERRUPT_STATUS(VAL)            (INTCONbits.GIE = VAL)
#define ADD_DATA(DATA)                   (EEDATA = DATA)
#define READ_DATA(VAL)                    (VAL = EEDATA)
#define ACCESS_EEPROM_FLASH_PATH()       (EECON1bits.CFGS = 0)
#define ACCESS_EEPROM()                  (EECON1bits.EEPGD = 0)
#define WRITE_FLASH_EEPROM(VAL)          (EECON1bits.WREN = VAL)
#define WRITE_SEQUENCE(VAL)              (EECON2 = VAL)
#define READ_EEPROM()                    (EECON1bits.RD = 1)
#define WRITE_EEPROM_START()             (EECON1bits.WR = 1)
/*Section : Function Declaration*/  

/**
 * 
 * @param bAdd the addresse of data on eeprom to wriet
 * @param bData the data which want to store in eeprom
 * @return the status of function 
 *          @ret (E_OK) if function successfuly
 *          @ret (E_NOT_OK) if function not successfuly
 */
Std_ReturnType Data_EEPROM_WriteBye(uint16 bAdd,uint8 bData);
/**
 * 
 * @param bAdd the addresse of data on eeprom to read
 * @param pointer point to  the data which want to read from eeprom
 * @return the status of function 
 *          @ret (E_OK) if function successfuly
 *          @ret (E_NOT_OK) if function not successfuly
 */

Std_ReturnType Data_EEPROM_ReadBye(uint16 bAdd,uint8 *bData);


#endif	/* HAL_EEPROM_H */

