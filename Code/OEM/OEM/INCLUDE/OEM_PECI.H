/*-----------------------------------------------------------------------------
 * @file     | OEM_PECI.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_PECI.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_PECI_H
#define OEM_PECI_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _PECI_HostID                0x01

//-----------------------------------------------------------------------------
// Define CPU address
//-----------------------------------------------------------------------------
#define _PECI_CPU_ADDR              0x30

//-----------------------------------------------------------------------------
// Define PECI command
//-----------------------------------------------------------------------------
#define _PECI_CMD_GetDIB            0xF7
#define _PECI_CMD_Ping              0x00
#define _PECI_CMD_GetTemp           0x01
#define _PECI_CMD_RdPkgConfig       0xA1
#define _PECI_CMD_WrPkgConfig       0xA5
#define _PECI_CMD_RdIAMSR           0xB1
#define _PECI_CMD_WrIAMSR           0xB5
#define _PECI_CMD_RdPCIConfig       0x61
#define _PECI_CMD_WrPCIConfig       0x65
#define _PECI_CMD_RdPCIConfigLocal  0xE1
#define _PECI_CMD_WrPCIConfigLocal  0xE5
/* Define completion code */
#define _PECI_CC_Valid              0x40
#define _PECI_CC_TimeOut            0x80
#define _PECI_CC_Ignored            0x90

// ----------------------------------------------------------------------------
// PECI3.0 domain parameter definition
// ----------------------------------------------------------------------------
#define _PECI_Domain_0              0x00
#define _PECI_Domain_1              0x01

// ----------------------------------------------------------------------------
// The index definition of PECI3.0 read/write Pkg command
// ----------------------------------------------------------------------------
#define _PECI_Index_IDENTIFIER      0x00 // Package identifier read
#define _PECI_Index_PTR             0x02 // Package temperature read
#define _PECI_Index_TTR             0x10 // Read max. Allowed Processor temper.
#define _PECI_Index_DRCTR           0x16 // DRAM rank channel temperature read
#define _PECI_Index_PLANE           0x19 // Per Plane Power Limit
#define _PECI_Index_PPL1            0x1A // Power limit 1
#define _PECI_Index_PPL2            0x1B // Power limit 2
#define _PECI_Index_PPSU            0x1C // Power SKU unit
#define _PECI_Index_PPSL            0x1D // Package power and time limit info.
#define _PECI_Index_PPSH            0x1E // Package power and time limit info.
#define _PECI_Index_PPL3            0x39 // Power limit 3
#define _PECI_Index_PPL4            0x3C // Power limit 4

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Init_PECI(void);
extern void Service_PECI(void);
#if 0
extern void Service_PECI_Command(void);
extern void Service_PECI_Data(void);
#endif
extern void Calc_CPU_Temperature(void);
extern BYTE PECI_ReadDIB(void);
extern BYTE PECI_ReadTemp(void);
extern BYTE PECI_ReadPowerUnit(void);
extern BYTE PECI_ReadPowerLimit1(void);
extern BYTE PECI_ReadPowerLimit2(void);
extern BYTE PECI_WritePowerLimit1(BYTE SettingWatts, BYTE SettingTimer);
extern BYTE PECI_WritePowerLimit2(BYTE SettingWatts);
extern BYTE PECI_ReadPowerLimit3(void);
extern BYTE PECI_WritePowerLimit3(BYTE SettingWatts);
extern BYTE PECI_ReadPowerLimit4(void);
extern BYTE PECI_WritePowerLimit4(BYTE SettingWatts);

extern BYTE PECI_RdPkgConfig(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
                             BYTE Index, BYTE LSB, BYTE MSB,
                             BYTE ReadLen, BYTE WriteLen);
//-----------------------------------------------------------------------------
#endif  //OEM_PECI_H
/*-----------------------------------------------------------------------------
 * End of OEM_PECI.H */