/*-----------------------------------------------------------------------------
 * @file     | OEM_POWER.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_POWER.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_POWER_H
#define OEM_POWER_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _EC_BOOT            0x00
#define _SYSTEM_S0          0x01
#define _SYSTEM_S1          0x02
#define _SYSTEM_S3          0x03
#define _SYSTEM_S4          0x04
#define _SYSTEM_S5          0x05
#define _SYSTEM_G3          0x06

#define _PST_G3_to_S5       0x80
#define _PST_S5_to_S0       0x81
#define _PST_S0_to_S3       0x82
#define _PST_S3_to_S0       0x83
#define _PST_S0_to_S5       0x84
#define _PST_S5_to_G3       0x85

#define _ST_UNAVAIL_SHUTDOWN_RS     0xFF
#define _ST_NORMAL_SHUTDOWN         0x00
#define _ST_FORCE_SHUTDOWN          0x05
#define _ST_ABNORMAL_SHUTDOWN       0x06
#define _ST_SOC_TP_SHUTDOWN         0x07
#define _ST_SKIN_TP_SHUTDOWN        0x08

#define POWER_BTN_REASON_PHY_BTN        0x1
#define POWER_BTN_REASON_PHY_LID        0x2
#define POWER_BTN_REASON_HOME_KEY       0x3
#define POWER_BTN_REASON_KB_WAKEUP      0x4
/*-----------------------------------------------------------------------------
 * System status define
 *---------------------------------------------------------------------------*/
#define SystemIsS0          SysPowState==_SYSTEM_S0
#define SystemIsS3          SysPowState==_SYSTEM_S3
#define SystemIsS4          SysPowState==_SYSTEM_S4
#define SystemIsS5          SysPowState==_SYSTEM_S5

#define SystemNotS0         SysPowState!=_SYSTEM_S0
#define SystemNotS3         SysPowState!=_SYSTEM_S3
#define SystemNotS4         SysPowState!=_SYSTEM_S4
#define SystemNotS5         SysPowState!=_SYSTEM_S5

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct PowerSEQ
{
    FUNCT_PTR_B_V func;
    WORD    delay;
    BYTE    checkstatus;
} sPowerSEQ;
//-----------------------------------------------------------------------------
typedef struct InitSleepWakeReg
{
    XBYTE   *reg;
    BYTE    entrysleep;
    BYTE    exitsleep;
} sInitSleepWakeReg;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void CheckResetSource(void);
extern void SystemWarmBoot(void);
extern void Oem_SysPowSequence(void);
extern void Set_SysPowState(BYTE SetValue);
extern void Oem_TriggerPowerOn(void);
extern void Oem_TriggerPowerOff(BYTE ShutdownCauseCode);
extern void Oem_AutoBoot(void);
extern BYTE Oem_AutoBoot_CheckMS(void);
extern void Oem_SysPowState_S0_S1(void);
extern void Oem_SysPowState_S3(void);
extern void Oem_SysPowState_S4_S5(void);
extern void Oem_SysPowState_G3(void);
extern void Hook_EC_ACK_eSPI_Reset(void);
extern void Service_PowerLatch(void);
extern BYTE IsThermalShutdowmHappen(void);
extern void PF_PWR_LED_OFF(void);
extern void PF_EC_VDDQ_EN_LO(void);
extern void POWER_LATCH_OFF(void);
extern void PF_TrggerSOCPwrBtn(BYTE Reason);
/*-----------------------------------------------------------------------------
 * ModernStandby Calling Prototype
 *---------------------------------------------------------------------------*/
#define _EC_GENERAL_IDLE        0x80
#define _EC_ATHENA_IDLE         0x81
#define _EC_S3_POWER_SAVING     0x82
#define _EC_MODERN_STANDBY      0x83
#define _EC_POWER_DOWN_IDLE     0x84
#define _EC_ENTRY_ATHENA_TIME   6       //Unit: Sec

extern void CheckCanGo_DeepSleep(void);
extern void CheckCanGo_S3ModernStandby(void);
extern void InitEntry_S3ModernStandby(void);
extern void InitExit_S3ModernStandby(void);

extern void InitEntry_DeepSleep(void);
extern void InitExit_DeepSleep(void);
extern BYTE CheckCanGo_AthenaIdle(void);
extern BYTE CheckCanGo_ModernStandby(void);
extern BYTE CheckExit_AthenaIdle(void);
extern void InitEntry_AthenaIdle(void);
extern void InitWake_AthenaIdle(void);
extern void InitExit_AthenaIdle(void);
extern void HookMS_CheckS3ExitCondition(void);
extern void InitEntry_ModernStandby(void);
extern void InitExit_ModernStandby(void);
extern void InitWake_ModernStandby(void);
extern void InitSleep_ModernStandby(void);
extern void Hook_ModernStandbyService(void);
extern void Hook_ModernStandbyService1ms(void);
extern void SET_ExitMS(BYTE ExitCode, BYTE ExitTsec);
extern void Service_eSPI_PLTRST(void);

//-----------------------------------------------------------------------------
#endif  //OEM_POWER_H
/*-----------------------------------------------------------------------------
 * End of OEM_POWER.H */