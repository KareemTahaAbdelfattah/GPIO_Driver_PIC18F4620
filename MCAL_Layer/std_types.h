/* 
 * File:   std_types.h
 * Author: Kareem Taha
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:58 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H


 /* Section : Includes */
#include "std_libraries.h"
#include "compiler.h"

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef uint8 STD_ReturnType;



 /* Section : Macros Definition */

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_HIGH        0x01
#define STD_LOW         0x00

#define E_OK            (STD_ReturnType)0x01
#define E_NOT_OK        (STD_ReturnType)0x00


 /* Section : Function Declaration */


#endif	/* STD_TYPES_H */

