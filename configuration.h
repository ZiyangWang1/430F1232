/*******************************************************************************
Type Definitions
*******************************************************************************/



/*******************************************************************************
Includes
*******************************************************************************/

#include "typedefs.h"
#include "pindefinitions.h"


/*******************************************************************************
Registers Setup
*******************************************************************************/

#define P1SEL_INIT (u8)0x02    // Enable I/O Function of P1.0;2;3;4;5;6;7
#define P2SEL_INIT (u8)0x05    // Enable I/O Function of P2.1;3;4;5
#define P3SEL_INIT (u8)0xB0    // Enable I/O Function of P1.0;1;2;3;6

#define P1DIR_INIT (u8)0x3D    // Set P1.0;2;3;4;5 to output direction
#define P2DIR_INIT (u8)0x3A    // Set P2.1;3;4;5 to output direction
#define P3DIR_INIT (u8)0x4F    // Set P3.0;1;2;3;6 to output direction
