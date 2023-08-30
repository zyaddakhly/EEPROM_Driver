/* 
 * File:   mcal_std_type.h
 * Author: zyadi
 *
 * Created on August 14, 2023, 11:53 PM
 */

#ifndef MCAL_STD_TYPE_H
#define	MCAL_STD_TYPE_H



/*Section : Include */
#include "std_libraries.h"
#include "compiler.h"


/*Section : Macro Declaration */

/*Compiler data type */
#define CPU_TYPE_8  8  
#define CPU_TYPE_16 16
#define CPU_TYPE_32 32
#define CPU_TYPE_64 64
#define CPU_TYPE (CPU_TYPE_64)

/*Section : Macro Function Declaration*/



/*Section :  Data Type Declaration*/

#if (CPU_TYPE == CPU_TYPE_64)
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long long unit64;

typedef signed char sint8 ;
typedef signed short sint16;
typedef signed int   sint32;
typedef signed long long snit64;

typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_32)


typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long   uint32;
typedef unsigned long long unit64;

typedef signed char sint8 ;
typedef signed short sint16;
typedef signed long  sint32;
typedef signed long long snit64;

typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_16)

typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long   uint32;
typedef unsigned long long unit64;

typedef signed char sint8 ;
typedef signed short sint16;
typedef signed long  sint32;
typedef signed long long snit64;

typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_8)

typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long   uint32;

typedef signed char sint8 ;
typedef signed short sint16;
typedef signed long  sint32;

typedef float float32;

 #endif
typedef uint8 Std_ReturnType;

/*Section : Macro Declaration */

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK            (Std_ReturnType)0x00



#define STD_HIGH                0x01
#define STD_LOW                 0x00

#define STD_ON                  0x01
#define STD_OFF                 0x00

#define STD_ACTIVE              0x01
#define STD_IDEAL               0x00


#endif	/* MCAL_STD_TYPE_H */

