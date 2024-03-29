/*-----------------------------------------------------------------------------
 * @file     | NXP.H
 *-----------+-----------------------------------------------------------------
 * @function | NXP.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6 
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef NXP_H
#define NXP_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _NXP_PORT1_ADDR             0xE6
#define _NXP_PORT2_ADDR             0xE4


// NXP NX20P3483UK Register map
#define _NXP_DEVICE_ID              0x00
#define _NXP_DEVICE_STATUS          0x01
#define _NXP_SWITCH_CONTROL         0x02
#define _NXP_SWITCH_STATUS          0x03
#define _NXP_INTERRUPT1             0x04
#define _NXP_INTERRUPT2             0x05
#define _NXP_INTERRUPT1_MASK        0x06
#define _NXP_INTERRUPT2_MASK        0x07
#define _NXP_OVLO_THRESHOLD         0x08
#define _NXP_HV_SRC_OCP_THRESHOLD   0x09
#define _NXP_5V_SRC_OCP_THRESHOLD   0x0A
#define _NXP_DEVICE_CONTROL         0x0B

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern BYTE NXP_ReadREG(BYTE Addr, unsigned int reg, XBYTE *buf, BYTE len);
extern BYTE NXP_WriteREG(BYTE Addr, unsigned int reg, XBYTE *buf, BYTE len);
extern BYTE NXP_Init(void);
//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of NXP.H */
 
 
 