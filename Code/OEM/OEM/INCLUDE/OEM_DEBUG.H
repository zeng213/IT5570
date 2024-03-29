/*-----------------------------------------------------------------------------
 * @file     | OEM_DEBUG.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_DEBUG.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_DEBUG_H
#define OEM_DEBUG_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void RamDebug(unsigned char dbgcode);
extern void RamDebug1(unsigned char dbgcode);
extern void PRINT_BYTE_ASCII(BYTE pcode);
extern void PRINT_DEC_ASCII(BYTE pcode);
extern void PRINT_DEC16_ASCII(WORD pcode);
extern void Service_UartBatteryMonitor(void);


//-----------------------------------------------------------------------------
#endif  //OEM_DEBUG_H
/*-----------------------------------------------------------------------------
 * End of OEM_DEBUG.H */