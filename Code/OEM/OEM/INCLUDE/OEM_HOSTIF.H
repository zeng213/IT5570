/*-----------------------------------------------------------------------------
 * @file     | OEM_HOSTIF.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_HOSTIF.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#ifndef OEM_HOSTIF_H
#define OEM_HOSTIF_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
enum intel_crashlog_step
{
    _CRASHLOG_END           = 0,
    _CRASHLOG_ERASE_DATA    = 1,
    _CRASHLOG_GET_CPU_SIZES = 2,
    _CRASHLOG_READ_CPU_LOG  = 3,
    _CRASHLOG_SAVE_CPU_LOG  = 4,
    _CRASHLOG_EXIT_CPU_LOG  = 5,
    _CRASHLOG_READ_PCH_LOG  = 6,
    _CRASHLOG_SAVE_PCH_LOG  = 7,
    _CRASHLOG_EXIT_PCH_LOG  = 8,
    _CRASHLOG_SAVE_INFO     = 9,
};

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Init_SIO(void);
extern void Init_SysMemory2ECRam(void);

extern void Service_OOB_Message(void);
extern BYTE Process_eSPI_OOB_Message(void);
extern void Process_eSPI_OOB_CrashLog(void);
extern void Get_OOB_RTC_Time(void);
extern void Get_OOB_PCH_Temperature(void);
extern void Get_OOB_PMC_CrashLog(void);

extern BYTE eSPI_Flash_Read(BYTE add3, BYTE add2, BYTE add1, BYTE add0,
                            BYTE length, XBYTE *bufferindex);
extern BYTE eSPI_Flash_Erase(BYTE addr3, BYTE addr2, BYTE addr1, BYTE addr0,
                             BYTE mode);
extern BYTE eSPI_Flash_Write(BYTE addr3, BYTE addr2, BYTE addr1, BYTE addr0,
                             BYTE length, XBYTE *bufferindex);

extern BYTE OOB_PECI_RdPkgConfig(BYTE addr, BYTE *ReadData, BYTE Domain,
                                 BYTE Retry, BYTE Index, BYTE LSB,
                                 BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern BYTE OOB_PECI_WrPkgConfig(BYTE addr, BYTE *WriteData, BYTE Domain,
                                 BYTE Retry, BYTE Index, BYTE LSB,
                                 BYTE MSB, BYTE ReadLen, BYTE WriteLen);

extern void OOB_PECI_ReadPowerUnit(void);
extern void OOB_PECI_ReadPowerLimit1(void);
extern void OOB_PECI_WritePowerLimit1(BYTE SettingWatts, BYTE SettingTimer);
extern void OOB_PECI_ReadPowerLimit2(void);
extern void OOB_PECI_WritePowerLimit2(BYTE SettingWatts);
extern void OOB_PECI_ReadPowerLimit3(void);
extern void OOB_PECI_WritePowerLimit3(BYTE SettingWatts);
extern void OOB_PECI_ReadPowerLimit4(void);
extern void OOB_PECI_WritePowerLimit4(BYTE SettingWatts);


//-----------------------------------------------------------------------------
#endif  //OEM_HOSTIF_H
/*-----------------------------------------------------------------------------
 * End of OEM_HOSTIF.H */