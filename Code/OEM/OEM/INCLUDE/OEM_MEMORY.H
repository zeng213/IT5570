/*----------------------------------------------------------------------------
 * @file     | OEM_MEMORY.C            | @Chipset | ITE.IT85XX/IT557X
 * ----------+-----------------------------------------------------------------
 * @function | Memory Definition for extern all code base reference
 * ----------+-----------------------------------------------------------------
 * [Memory Map Description]
 *
 * Chip Internal Ram : 0x00-0xFF For Kernel and Chip Level use
 *
 *****************************************************************
 * Chip IT8500/IT8527 : External RAM 0x0000-0x07FF
 * Chip IT85XX/IT89XX : External RAM 0x0000-0x0FFF
 * Chip IT557X        : External RAM  0x0000-0x0FFF, 0x9000~0x97FF
 *****************************************************************
 *
 * [OEM Memory Rang]
 * [External Ram]
 * 0x100-0x1FF   OEM RAM
 * 0x200-0x2FF   OEM RAM
 * 0x300-0x3FF   OEM RAM
 * 0x400-0x4FF   OEM RAM
 * 0x500-0x5FF   OEM RAM
 * 0x600-0x6FF   OEM RAM ITE_Flash_Utility & SPI ROM Read/Write
 * 0x700-0x7FF   OEM RAM RamProgram
 * 0x800-0x8FF   OEM RAM
 * 0x900-0x9FF   OEM RAM
 * 0xA00-0xAFF   OEM RAM
 * 0xB00-0xBFF   OEM RAM
 * 0xC00-0xCFF   OEM RAM
 * 0xD00-0xDFF   OEM RAM
 * 0xE00-0xEFF   OEM RAM Ramdebug function
 * 0xF00-0xFFF   OEM RAM
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Kernel Copyright(c)2012, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_MEMORY_H
#define OEM_MEMORY_H

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* RAM BASE DEFINE ***********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define EC_RAMBase          0x0000

#define OEMRAM1             EC_RAMBase+0x0100   // EC_RAMBase+0x0100
#define OEMRAM2             EC_RAMBase+0x0200   // EC_RAMBase+0x0200
#define OEMRAM3             EC_RAMBase+0x0300   // EC_RAMBase+0x0300
#define OEMRAM4             EC_RAMBase+0x0400   // EC_RAMBase+0x0400
#define OEMRAM5             EC_RAMBase+0x0500   // EC_RAMBase+0x0500
#define OEMRAM6             EC_RAMBase+0x0600   // EC_RAMBase+0x0600
#define OEMRAM7             EC_RAMBase+0x0700   // EC_RAMBase+0x0700
#define OEMRAM8             EC_RAMBase+0x0800   // EC_RAMBase+0x0800
#define OEMRAM9             EC_RAMBase+0x0900   // EC_RAMBase+0x0900
#define OEMRAMA             EC_RAMBase+0x0A00   // EC_RAMBase+0x0A00
#define OEMRAMB             EC_RAMBase+0x0B00   // EC_RAMBase+0x0B00
#define OEMRAMC             EC_RAMBase+0x0C00   // EC_RAMBase+0x0C00
#define OEMRAMD             EC_RAMBase+0x0D00   // EC_RAMBase+0x0D00
#define OEMRAME             EC_RAMBase+0x0E00   // EC_RAMBase+0x0E00
#define OEMRAMF             EC_RAMBase+0x0F00   // EC_RAMBase+0x0F00

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* Kernel none use resources (need adjustment after update kernel) */
//-----------------------------------------------------------------------------
extern XBYTE    SCIEVT_BUF[];
extern XBYTE    SCIEVT_WIDX;
extern XBYTE    SCIEVT_RIDX;
extern XBYTE    SCIEVT_OUT;
extern XBYTE    SCIEVT_LOSE;
extern XBYTE    SCIEVT_OVT;
extern XBYTE    SCIEVT_DELAY;
extern XBYTE    SCIEVT_LAST;
extern XBYTE    SCIEVT_CNT;
//-----------------------------------------------------------------------------
extern XBYTE    SysPowState;
#define F_PST_BUSY          BIT(7)
extern XBYTE    CtrlPowStep;
extern XWORD    PowSeqDelay;
extern XWORD    PowSeqWait;
extern XBYTE    PowerOnFailed;
extern XBYTE    PowSwFlag;
#define F_PSW_WAIT_UP       BIT(0)
#define F_PSW_UP_DELAY      BIT(1)

#define F_PSW_EVT_BREAK     BIT(5)
#define F_PSW_SCANCODE      BIT(6)
#define F_PSW_SEND_SOC_PWRBTN        BIT(7)
extern XWORD    PowSwLockTimer;
extern XWORD    PowSwDownTimer;
extern XWORD    PowSwDebounce;
extern XWORD    wPwrSwTypingDelay;
extern XWORD    wLockPWRBTN;
// extern XBYTE    SetAutoBootTimer;
extern XBYTE    AutoBootTimer;
extern XBYTE    PanelOnStep;
extern XBYTE    PanelOnDelay;
extern XBYTE    MutePinDelay;
extern XBYTE    LID_Debounce;
extern XBYTE    LID_OpenDebounce;
extern XWORD    LID_Resend;
extern XWORD    LID_OpenResend;
extern XBYTE    SystemFlag1;
#define F_ME_LOCK_MODE      BIT(6)
#define F_ACPI_MODE         BIT(7)
extern XBYTE    ADP_Debounce;
//-----------------------------------------------------------------------------


//*******************************************************************************
//-------------------------------------------------------------------------------
//  0x800-0x8FF   OEM RAM 2
//-------------------------------------------------------------------------------
//*******************************************************************************
extern XBYTE    xEC_T1_LoLimit;
extern XBYTE    xEC_T1_HiLimit;
extern XBYTE    xEC_T2_LoLimit;
extern XBYTE    xEC_T2_HiLimit;
extern XBYTE    xEC_T3_LoLimit;
extern XBYTE    xEC_T3_HiLimit;
extern XBYTE    xEC_T4_LoLimit;
extern XBYTE    xEC_T4_HiLimit;
extern XBYTE    xEC_T5_LoLimit;
extern XBYTE    xEC_T5_HiLimit;

extern XBYTE    xEC_T1_SendEvent;
extern XBYTE    xEC_T1_THR;
extern XWORD    wEC_T1_THR_ACC;
extern XBYTE    xEC_CPUT_EventTimer;
extern XBYTE    xEC_CPUT_SendEvent;

extern XBYTE    xEC_CPUT_HiLimit;
extern XBYTE    xEC_CPUT_LoLimit;

extern XBYTE    xEC_T1_AVG;
extern XBYTE    xEC_T1_EventTimer;
extern XBYTE    xEC_T2_AVG;
extern XBYTE    xEC_T2_EventTimer;
extern XBYTE    xEC_T3_AVG;
extern XBYTE    xEC_T3_EventTimer;
extern XBYTE    xEC_T4_AVG;
extern XBYTE    xEC_T4_SendEvent;
extern XBYTE    xEC_T5_AVG;
extern XBYTE    xEC_T5_SendEvent;

extern XBYTE    xEC_T2_SendEvent;
extern XBYTE    xEC_T2_THR;
extern XWORD    wEC_T2_THR_ACC;
extern XBYTE    xEC_T3_SendEvent;
extern XBYTE    xEC_T3_THR;
extern XWORD    wEC_T3_THR_ACC;
extern XBYTE    xEC_T5_SendEvent;
extern XBYTE    xEC_T5_THR;
extern XWORD    wEC_T5_THR_ACC;

//-----------------------------------------------------------------------------

#define Fan_MemBase                 0x0290
extern XBYTE    Fan1_DnTempr;
extern XBYTE    Fan1_RefTempr;
extern XBYTE    Fan1_UpTempr;
extern XBYTE    Fan1_LevelDir;
extern XBYTE    Fan1_CurrentLevelDir;
extern XBYTE    Fan1_NowDCR;
extern XWORD    wFan1_TargetRPM;
extern XWORD    wFan1_CurrentRPM;
extern XBYTE    Fan1_Up_Delay;
extern XBYTE    Fan1_Step;
extern XBYTE    Fan1_NeedInit;
extern XBYTE    Fan1_UpdRPMCnt;
extern XBYTE    Fan1_DebugCmd;
extern XBYTE    Fan1_DebugKey;
extern XBYTE    Fan1_T_Dn[];
extern XBYTE    Fan1_T_Up[];
extern XBYTE    Fan1_PWM[];
extern XBYTE    Fan1_RPM_H[];
extern XBYTE    Fan1_RPM_L[];
extern XBYTE    Fan1_ErrCheck;
extern XBYTE    FAN_DBG_CTRL_PWM;
extern XBYTE    FAN_DBG_CTRL_ON;
extern XWORD    wEC_FAN_CurrentRPM;
extern XBYTE    Fan1_TargetDCR;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0300 ~ 0x03FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    SMBA_CHN_STS;
extern XBYTE    SMBA_CHN_TIMER;
extern XBYTE    SMBA_DEV_DIR;
extern XBYTE    SMBA_CHN_CTL;
extern XBYTE    SMBA_CHN_CMD;
extern XBYTE    SMBA_BYTE_CNT;
extern XWORD    SMBA_DEV_MEM;
extern XBYTE    SMBA_ERR_STS[];
extern XBYTE    SMBA_DAT_CNT[];
extern XBYTE    SMBB_CHN_STS;
extern XBYTE    SMBB_CHN_TIMER;
extern XBYTE    SMBB_DEV_DIR;
extern XBYTE    SMBB_CHN_CTL;
extern XBYTE    SMBB_CHN_CMD;
extern XBYTE    SMBB_BYTE_CNT;
extern XWORD    SMBB_DEV_MEM;
extern XBYTE    SMBB_ERR_STS[];
extern XBYTE    SMBB_DAT_CNT[];
extern XBYTE    SMBC_CHN_STS;
extern XBYTE    SMBC_CHN_TIMER;
extern XBYTE    SMBC_DEV_DIR;
extern XBYTE    SMBC_CHN_CTL;
extern XBYTE    SMBC_CHN_CMD;
extern XBYTE    SMBC_BYTE_CNT;
extern XWORD    SMBC_DEV_MEM;
extern XBYTE    SMBC_ERR_STS[];
extern XBYTE    SMBC_DAT_CNT[];
extern XBYTE    SMBD_CHN_STS;
extern XBYTE    SMBD_CHN_TIMER;
extern XBYTE    SMBD_DEV_DIR;
extern XBYTE    SMBD_CHN_CTL;
extern XBYTE    SMBD_CHN_CMD;
extern XBYTE    SMBD_BYTE_CNT;
extern XWORD    SMBD_DEV_MEM;
extern XBYTE    SMBD_ERR_STS[];
extern XBYTE    SMBD_DAT_CNT[];
extern XBYTE    SMBA_DEV0_STS;
extern XBYTE    SMBA_DEV0_DIR;
extern XWORD    SMBA_DEV0_DLY;
extern XBYTE    SMBA_DEV1_STS;
extern XBYTE    SMBA_DEV1_DIR;
extern XWORD    SMBA_DEV1_DLY;
extern XBYTE    SMBB_DEV0_STS;
extern XBYTE    SMBB_DEV0_DIR;
extern XWORD    SMBB_DEV0_DLY;
extern XBYTE    SMBB_DEV1_STS;
extern XBYTE    SMBB_DEV1_DIR;
extern XWORD    SMBB_DEV1_DLY;
extern XBYTE    SMBC_DEV0_STS;
extern XBYTE    SMBC_DEV0_DIR;
extern XWORD    SMBC_DEV0_DLY;
extern XBYTE    SMBC_DEV1_STS;
extern XBYTE    SMBC_DEV1_DIR;
extern XWORD    SMBC_DEV1_DLY;
extern XWORD    SMBA_DEV2_DLY;
extern XWORD    SMBB_DEV2_DLY;
//-----------------------------------------------------------------------------
// SMBX BIT DEFINE
/* SMBX_CHN_STS */
#define F_SMB_BUSY          BIT(7)
#define F_SMB_CHID1         BIT(3)
#define F_SMB_CHID0         BIT(2)
#define F_SMB_DEVD1         BIT(1)
#define F_SMB_DEVD0         BIT(0)
/* SMBA_CHN_STS */
#define F_DEV_STOP          BIT(7)
#define F_DEV_FAILED        BIT(6)
#define F_DEV_UPDATED       BIT(3)

#define F_DEV_EARLY_INIT    BIT(2)
#define F_DEV_INIT          BIT(1)
#define F_DEV_ON_LINE       BIT(0)
#define F_DEV_MASK_READY    (BIT(7) | BIT(6) | BIT(0))
#define F_DEV_READY         BIT(0)

//-----------------------------------------------------------------------------
extern XWORD    wADC[];
extern XBYTE    xADC[];
extern XBYTE    xADC_ScanTimer;
extern XBYTE    xADC_Count;
extern XBYTE    xEC_T1_CNT;
extern XBYTE    xEC_T2_CNT;
extern XBYTE    xEC_T3_CNT;
extern XBYTE    xEC_T5_CNT;

//-----------------------------------------------------------------------------
extern XBYTE    DebounceGPJ0;
extern XBYTE    DebounceGPJ3;

//-----------------------------------------------------------------------------
extern XBYTE    AnyKeyDownFlag;
extern XBYTE    KB_BacklightTimer;
extern XBYTE    KB_BacklightPWM;
extern XBYTE    PowerLatchTimer;
extern XBYTE    PwrLedBlinkTimer;
extern XBYTE    ChargerBlinkTimer;
extern XBYTE    ThermalBlinkEn;

extern XBYTE    xGPI_Debounce0;
extern XBYTE    xGPI_Debounce1;
extern XBYTE    xGPI_Debounce2;
extern XBYTE    xGPI_Debounce3;


extern XBYTE    EC_SW_MIRROR;
#define SW_MIRROR_EN            BIT(0)
extern XBYTE    EC_SW_MIRROR_DELAY;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0400 ~ 0x04FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define MEM_EC_SPACE                0x0400
//-----------------------------------------------------------------------------
extern XBYTE    xEC_MainVersion;
extern XBYTE    xEC_SubVersion;
extern XBYTE    xEC_KBCVersion;
extern XBYTE    xEC_TestVersion;
extern XBYTE   xEC_TestVersion2;

extern XBYTE   xEC_BuildHour;
extern XBYTE   xEC_BuildMin;
extern XBYTE   xEC_BuildSec;

extern XBYTE   xEC_BuildYear;
extern XBYTE   xEC_BuildMonth;
extern XBYTE   xEC_BuildDay;
extern XBYTE   xEC_BuildIndex;
extern XBYTE   xEC_ShipMode;
extern XBYTE   OEM_ControlPOWER;//            _at_ MEM_EC_SPACE + 0x10;
extern XBYTE   OEM_ControlDevice;//           _at_ MEM_EC_SPACE + 0x11;
extern XBYTE   OEM_ShutdownReason;//          _at_ MEM_EC_SPACE + 0x12;
extern XBYTE   xEC_PDPort1MainVersion;//      _at_ MEM_EC_SPACE + 0x15;
extern XBYTE   xEC_PDPort1SubVersion;//       _at_ MEM_EC_SPACE + 0x16;
extern XBYTE   xEC_UCSIMajorVersion;//        _at_ MEM_EC_SPACE + 0x17;
extern XBYTE   xEC_UCSIMinorVersion;//        _at_ MEM_EC_SPACE + 0x18;
extern XBYTE   xEC_UCSIRevVersion;//          _at_ MEM_EC_SPACE + 0x19;
extern XBYTE    xEC_ThermalChargCMD;
extern XBYTE    xEC_ThermalChargFlag;
extern XBYTE    xEC_BoardID_Value;
extern XBYTE    xEC_SensorT_Error_F;
#define F_Skin_Sensor_error      BIT(0)

extern XBYTE    xEC_RTC_WakeupFlag;
extern XBYTE    xEC_RTC_SupportFlag;
extern XWORD    xEC_RTC_Wakeuptimer;
extern XWORD    xEC_Forece_Shutdown_counter;

extern XWORD    xEC_RTC_test_counter;//+0x49;
extern XBYTE    xEC_FAN_PWM_DCR;//               _at_ MEM_EC_SPACE+0x4B;

extern XBYTE   xEC_MultiFunctionCtrl;

extern XBYTE    xEC_SOCCriTripPoint;
extern XBYTE    xEC_SkinCriTripPoint;
extern XBYTE    xEC_PECI_CPU_T;
extern XBYTE    xEC_PLMX_T;
extern XBYTE    xEC_Sensor_2_T;
extern XBYTE    xEC_Sensor_1_T;
extern XBYTE    xEC_Sensor_3_T;
extern XWORD    xEC_BAT1_T4;
extern XWORD    xEC_Debug_Fan1Rpm;
extern XWORD    xEC_Debug_Fan2Rpm;
extern XBYTE   xEC_SafeVoltageValueL;
extern XBYTE   xEC_SafeVoltageValueH;
extern XBYTE    SetAutoBootTimer;
extern XBYTE    xEC_LID_STATUS;
#define F_LID_STA           BIT(0)
#define F_GPI_LID_STA       BIT(7)      //OEPN:1, CLOSED:0
extern XBYTE    xEC_SAR_Event;
extern XBYTE   xEC_FeatureStatus;
#define F_FASTCHARGE_EN_STA BIT(0)


extern XBYTE    xEC_Sensor_F;
// Bit0..4: 0-CPU,1-SEN2,2-SEN3,3-SEN4...
// Bit4..7: Hysteresis

extern XBYTE    xEC_Sensor_TSHT;
extern XBYTE    xEC_Sensor_TSLT;

extern XBYTE    xEC_ThermalSource;
#define F_SEN1_TRIP         BIT(0)
#define F_SEN2_TRIP         BIT(1)
#define F_SEN3_TRIP         BIT(2)
#define F_SEN4_TRIP         BIT(3)

extern XBYTE   xEC_POGO_Status;

#if 0
extern XWORD    xEC_Charge_Rate;
extern XWORD    xEC_Charge_InCurrent;
extern XWORD    xEC_Charge_Vlot;
extern XWORD    xEC_Charge_option;
#else
extern XBYTE    xEC_FSL_PPSL;   //PWM Port Select low byte
extern XBYTE    xEC_FSL_PPSH;   //PWM Port Select high byte
extern XBYTE    xEC_FSL_PINV;   //PWM initial value
extern XBYTE    xEC_FSL_PENV;   //PWM ending value
extern XBYTE    xEC_FSL_PSTP;   //PWM ms delay between steps
#endif

extern XBYTE    xEC_PowerState;
extern XBYTE    xEC_Bt1ModelCode;
extern XBYTE    xEC_Bt1SerialNumberL;
extern XBYTE    xEC_Bt1SerialNumberH;
extern XBYTE    xEC_Bt1DesignCapacityL;
extern XBYTE    xEC_Bt1DesignCapacityH;
extern XBYTE    xEC_Bt1DesignVoltageL;
extern XBYTE    xEC_Bt1DesignVoltageH;
extern XBYTE    xEC_Bt1FullChrgCapacityL;
extern XBYTE    xEC_Bt1FullChrgCapacityH;
extern XBYTE    xEC_Bt1TripPointL;
extern XBYTE    xEC_Bt1TripPointH;
extern XBYTE    xEC_Bt1State;
#define F_ACPI_DISCHRGE     BIT(0)
#define F_ACPI_CHARGING     BIT(1)
#define F_ACPI_CRITICAL     BIT(2)

extern XBYTE    xEC_Bt1PresentRateL;
extern XBYTE    xEC_Bt1PresentRateH;
extern XBYTE    xEC_Bt1RemainCapacityL;
extern XBYTE    xEC_Bt1RemainCapacityH;
extern XBYTE    xEC_Bt1PresentVoltageL;
extern XBYTE    xEC_Bt1PresentVoltageH;
extern XBYTE    xEC_Bt1RSOC;
extern XBYTE    xEC_Bt1CurrentL;
extern XBYTE    xEC_Bt1CurrentH;

extern XBYTE    xEC_TSR1;
extern XBYTE    xEC_TSR1H;

extern XBYTE    xEC_StopChargingReason;
extern XBYTE   xEC_PD1FWVersion[];
extern XBYTE   xEC_PD2FWVersion[];

#if 1 //UCSI_SUPPORT
extern XBYTE    xUCSI_DS_VERSION[];
extern XBYTE    UCSI_DS_RESERVED[];
extern XBYTE    xUCSI_DS_CCI0;
#define xUCSI_CCI_ConnectorChangeIndicator  xUCSI_DS_CCI0   /* BIT[1:7] */

extern XBYTE    xUCSI_DS_CCI1;
#define xUCSI_CCI_DataLength                xUCSI_DS_CCI1

extern XBYTE    xUCSI_DS_CCI2;
extern XBYTE    xUCSI_DS_CCI3;
#define F_NotSupportedIndicator         BIT1
#define F_CancelCompletedIndicator      BIT2
#define F_ResetCompletedIndicator       BIT3
#define F_BusyIndicator                 BIT4
#define F_AcknowledgeCommandIndicator   BIT5
#define F_ErrorIndicator                BIT6
#define F_CommandCompletedIndicator     BIT7

extern XBYTE    xUCSI_DS_CTL0;
#define xUCSI_COMMAND                       xUCSI_DS_CTL0

extern XBYTE    xUCSI_DS_CTL1;  //data_length
extern XBYTE    xUCSI_DS_CTL2;  //command_specific[0]
#define xUCSI_CMD_SPEC_0                    xUCSI_DS_CTL2
extern XBYTE    xUCSI_DS_CTL3;  //command_specific[1]
#define xUCSI_CMD_SPEC_1                    xUCSI_DS_CTL3
extern XBYTE    xUCSI_DS_CTL4;  //command_specific[2]
#define xUCSI_CMD_SPEC_2                    xUCSI_DS_CTL4
extern XBYTE    xUCSI_DS_CTL5;  //command_specific[3]
#define xUCSI_CMD_SPEC_3                    xUCSI_DS_CTL5
extern XBYTE    xUCSI_DS_CTL6;  //command_specific[4]
#define xUCSI_CMD_SPEC_4                    xUCSI_DS_CTL6
extern XBYTE    xUCSI_DS_CTL7;  //command_specific[5]
#define xUCSI_CMD_SPEC_5                    xUCSI_DS_CTL7
extern XBYTE    xUCSI_DS_MGI[];
extern XBYTE    xUCSI_DS_MGO[];

#endif  //UCSI_SUPPORT
//-----------------------------------------------------------------------------
extern XBYTE    HOST_BIOS_REG1;
#define F_ME_UNLOCK         BIT(0)

extern XBYTE    PwrBtn_OVR_Mode;
extern XBYTE    System_CS_Mode;
extern XBYTE    LED_CTRL_MODE;
extern XBYTE    xEC_ShutdownCode;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0500 ~ 0x05FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define BAT1_MemBase                0x0500
extern XWORD    BAT1_ManufacturerAccess;
extern XWORD    BAT1_BatteryMode;
extern XWORD    BAT1_Temperature;
extern XWORD    BAT1_Voltage;
extern XWORD    BAT1_Current;
extern XWORD    BAT1_AverageCurrent;
extern XWORD    BAT1_MaxError;
extern XBYTE    BAT1_RelativeStateOfChg;
extern XBYTE    BAT1_RelativeStateOfChgL;
extern XWORD    BAT1_AbsoluteOfCharge;
extern XWORD    BAT1_RemainingCapacity;
extern XWORD    BAT1_FullChargeCapacity;
extern XWORD    BAT1_ChargingCurrent;
extern XWORD    BAT1_ChargingVoltage;
extern XWORD    BAT1_BatteryStatus1;
extern XWORD    BAT1_CycleCount;
extern XWORD    BAT1_DesignCapacity;
extern XWORD    BAT1_DesignVoltage;
extern XWORD    BAT1_SpecificationInfo;
extern XWORD    BAT1_ManufactureDate;
extern XWORD    BAT1_SerialNumber;
extern XBYTE    BAT1_ManufacturerName[];
extern XBYTE    BAT1_DeviceName[];
extern XBYTE    BAT1_DeviceChemistry[];
extern XBYTE    BAT1_ManufacturerData[];
extern XBYTE    BAT1_PACKAGE;
extern XWORD    BAT1_BatteryStatus2;
extern XWORD    BAT1_BatteryStatus;
extern XBYTE    BAT1_LockPowerOnRSOC;
extern XBYTE    BAT1_DebugMode;
extern XBYTE    BAT1_LastRSOC;
extern XWORD    BAT1_LastFCC;
extern XBYTE    CHGR_StepChangeCnt;
extern XBYTE    CHGR_FastChargeStep;
extern XBYTE    BAT1_CelsiusDegree;
extern XBYTE    BAT1_CheckRecharge;
extern XWORD    BAT1_Dead_Counter;
extern XWORD    BAT1_SafeVoltageValue;
extern XBYTE    BAT1_THROT_DIR;
extern XWORD    BAT1_THROT_DNT;
extern XWORD    BAT1_THROT_UPT;
//-----------------------------------------------------------------------------
extern XBYTE    xEC_PowerSource;
extern XBYTE    PowerSource;
#define _BATT_CLR_MASK      F_BAT1_DISCHRGE+F_BAT1_CHARGING+F_BAT1_CRITICAL+\
    F_BAT1_LOW+F_BAT1_DETECTED+F_BAT1_PRESENT
#define F_BAT1_DISCHRGE     BIT(7)
#define F_BAT1_CHARGING     BIT(6)
#define F_BAT1_CRITICAL     BIT(5)
#define F_BAT1_LOW          BIT(4)
#define F_BAT1_DETECTED     BIT(2)
#define F_BAT1_PRESENT      BIT(1)
#define F_AC_ON_LINE        BIT(0)

extern XBYTE    Debounce_ACin;
extern XBYTE    Debounce_Bt1In;
extern XBYTE    Debounce_Bt2In;
extern XBYTE    SendBatEventTimer;
extern XBYTE    SendACiEventTimer;
extern XBYTE    BatSetPowerLimit;
#define F_BAT1_BAD_SET      BIT(2)
#define F_BAT1_LOW_SET      BIT(1)
#define F_BAT1_OUT_SET      BIT(0)
extern XBYTE    DeadBatteryActiveTimer;
extern XBYTE    BatteryDetectStep;
extern XBYTE    BatteryDetectRetry;
extern XWORD    wBatteryDetectTmr;
extern XBYTE    EventTestTimer;
extern XBYTE    EventTestNumber;

//-----------------------------------------------------------------------------
extern XBYTE    xSAR_PRODUCT_NUM;
extern XBYTE    xSAR_VERSION_NUM;
extern XBYTE    xSAR_DEBUG_EVENTS;
extern XBYTE    xSAR_COMMANDS;
extern XBYTE    xSAR_OTP_BANK1;
extern XBYTE    xSAR_OTP_BANK2;
extern XBYTE    xSAR_OTP_BANK3;
extern XBYTE    xSAR_QUICK_RELEASE;
extern XBYTE    xSAR_MOVEMENT;
extern XBYTE    xSAR_TOUCH_THR;
extern XBYTE    xSAR_PROXIMITY_THR;
extern XBYTE    xSAR_TEMP_INF_THR;
extern XBYTE    xSAR_CH0_MULT;
extern XBYTE    xSAR_CH0_COMP;
extern XBYTE    xSAR_CH1_MULT;
extern XBYTE    xSAR_CH1_COMP;
extern XBYTE    xSAR_SYS_FLAG;
extern XBYTE    xSAR_UI_FLAG;
extern XBYTE    xSAR_ATI_FLAG;
extern XBYTE    xSAR_EVENT_FLAG;
extern XBYTE    xSAR_ATI_FLAG;
extern XBYTE    xSAR_ATI_FLAG;
extern XBYTE    xSAR_ATI_FLAG;
extern XBYTE    xSAR_CH0_ACF_H;
extern XBYTE    xSAR_CH0_ACF_L;
extern XBYTE    xSAR_CH0_LTA_H;
extern XBYTE    xSAR_CH0_LTA_L;
extern XBYTE    xSAR_CH0_QRD_H;
extern XBYTE    xSAR_CH0_QRD_L;
extern XBYTE    xSAR_CH1_ACF_H;
extern XBYTE    xSAR_CH1_ACF_L;
extern XBYTE    xSAR_CH1_UMOV_H;
extern XBYTE    xSAR_CH1_UMOV_L;
extern XBYTE    xSAR_CH1_LMOV_H;
extern XBYTE    xSAR_CH1_LMOV_L;
extern XBYTE    xSAR_CH1_LMOV_H;
extern XBYTE    xSAR_CH1_LMOV_L;
extern XBYTE    xSAR_CH1_RAW_H;
extern XBYTE    xSAR_CH1_RAW_L;
extern XBYTE    xSAR_TEMP_H;
extern XBYTE    xSAR_TEMP_L;
extern XBYTE    xSAR_LTA_HALT_TIMER_H;
extern XBYTE    xSAR_LTA_HALT_TIMER_L;
extern XBYTE    xSAR_FILTER_HALT_TIMER;
extern XBYTE    xSAR_TIMER_READ_INPUT;
extern XBYTE    xSAR_TIMER_READ_ATI;
extern XBYTE    xSAR_Event_Trigger_Timer;
extern XBYTE    xSAR_Event_Release_Timer;

//-----------------------------------------------------------------------------
extern XBYTE   xSOCTripPointCnt;
extern XBYTE   xSkinTripPointCnt;

extern XBYTE   xEC_StateTimer;

extern XBYTE   xDOCK_Event_In_Timer;
extern XBYTE   xDOCK_Event_Out_Timer;
extern XBYTE   xEC_Battery4PWakeup;

//-----------------------------------------------------------------------------
extern XWORD    CHGR_ChargerOption;
extern XWORD    CHGR_InputCurrent;
extern XWORD    CHGR_ChargingCurrent;
extern XWORD    CHGR_ChargingVoltage;
extern XWORD    CHGR_ManufacturerID;
extern XWORD    CHGR_DeviceID;
extern XWORD    CHGR_ChargerREG3E;
extern XBYTE    WakeUpChargeTimer;
extern XWORD    CHGR_ChargerOptionR;
extern XWORD    CHGR_InputCurrentR;
extern XWORD    CHGR_ChargingCurrentR;
extern XWORD    CHGR_ChargingVoltageR;

extern XWORD    BAT1_0025FCC;
extern XWORD    BAT1_005FCC;
extern XWORD    BAT1_02FCC;
extern XWORD    BAT1_05FCC;
extern XWORD    BAT1_08FCC;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0600 ~ 0x06FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    xMSBY_Mode;
extern XBYTE    xMSBY_SleepCounter;
extern XBYTE    xMSBY_DozeCounter;
extern XBYTE    xMSBY_ServiceKey;
extern XBYTE    xMSBY_ExitKey;
extern XBYTE    xMSBY_EnLidOpenWake;
extern XBYTE    xMSBY_SleepDelay;
extern XBYTE    xMSBY_GetBatteryStep;
extern XBYTE    xMSBY_GetThermalStep;
extern XBYTE    xMSBY_S3SleepCounter;
extern XWORD    wMSBY_SLP_S0_LoT;
extern XWORD    wMSBY_SLP_S0_HiT;
extern XWORD    wMSBY_EnterDelay;
extern XWORD    wMSBY_SLP_S3_LoT;
extern XWORD    wMSBY_SLP_S3_HiT;
extern XBYTE    xMSBY_WakeUpFlag;
#define PlugInAC            BIT0
#define AnyKey              BIT1
#define eSPI                BIT2
extern XBYTE    xATNA_IdleTimer;
extern XBYTE    xECPW_DeepSleepDelay;
extern XWORD    wMSBY_BatteryPollingDelay;

extern XBYTE   xAMP_EN_TestTimer;

extern XBYTE    xUBM_Step;
extern XWORD    xPowerOnBlinkLEDEn;
extern XBYTE    xLowBattShutdownCnt;

//-----------------------------------------------------------------------------
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0x0700 ~ 0x08FF   EXTERNAL RAM AREA (Don't use)
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//  0x900-0x9FF   OEM RAM 9
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xA00-0xAFF   OEM RAM A
//-------------------------------------------------------------------------------
//*******************************************************************************
extern XBYTE    RamBufferA[];
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xB00-0xBFF   OEM RAM B
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xC00-0xCFF   OEM RAM C
//-------------------------------------------------------------------------------
//*******************************************************************************
extern XBYTE    SPIBuffer[];
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xD00-0xDFF   OEM RAM D
//-------------------------------------------------------------------------------
//*******************************************************************************
extern XBYTE    SPIBuffer2[];
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xE00-0xEFF   OEM RAM E
//-------------------------------------------------------------------------------
//*******************************************************************************
//0x0E00 - 0x0EFF       for RamDebug
#define DebugRamAddr                0xE00
#define DebugRamRange               0xFF

//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xF00-0xFFF   OEM RAM F
//-------------------------------------------------------------------------------
//*******************************************************************************


//*****************************************************************************
/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
//*****************************************************************************
extern void Clear_Memory_Range(WORD nAddr, WORD nSize);


#if 1   /* IT5570/IT5571 EXTEDED 2 KB RAM */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9000 ~ 0x90FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9000                  0x9000
extern XBYTE    WarmBootCounter;
extern XBYTE    Fan_First_Speed_Flag;
extern XBYTE    Fan_Delay_Flag;
extern XBYTE    CPU_T_Flag;
extern XBYTE    CPU_T_Dn_Flag;
extern XBYTE    CPU_T_Up_Flag;


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9100 ~ 0x90FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9100                  0x9100
extern XBYTE   xNXP_PORT1_Device_ID;
extern XBYTE   xNXP_PORT1_Devcie_Status;
extern XBYTE   xNXP_PORT1_Switch_Control;
extern XBYTE   xNXP_PORT1_Switch_Status;
extern XBYTE   xNXP_PORT1_Interrupt1;
extern XBYTE   xNXP_PORT1_Interrupt2;
extern XBYTE   xNXP_PORT1_Interrupt1_Mask;
extern XBYTE   xNXP_PORT1_Interrupt2_Mask;
extern XBYTE   xNXP_PORT1_OVLO_Threshold;
extern XBYTE   xNXP_PORT1_HV_SRC_OCP_Threshold;
extern XBYTE   xNXP_PORT1_5V_SRC_OCP_Threshold;
extern XBYTE   xNXP_PORT1_Device_Control;

extern XBYTE   xNXP_PORT2_Device_ID;
extern XBYTE   xNXP_PORT2_Devcie_Status;
extern XBYTE   xNXP_PORT2_Switch_Control;
extern XBYTE   xNXP_PORT2_Switch_Status;
extern XBYTE   xNXP_PORT2_Interrupt1;
extern XBYTE   xNXP_PORT2_Interrupt2;
extern XBYTE   xNXP_PORT2_Interrupt1_Mask;
extern XBYTE   xNXP_PORT2_Interrupt2_Mask;
extern XBYTE   xNXP_PORT2_OVLO_Threshold;
extern XBYTE   xNXP_PORT2_HV_SRC_OCP_Threshold;
extern XBYTE   xNXP_PORT2_5V_SRC_OCP_Threshold;
extern XBYTE   xNXP_PORT2_Device_Control;

extern XBYTE   xNXP_PORT1_FailCount1;
extern XBYTE   xNXP_PORT1_FailCount2;
extern XBYTE   xNXP_PORT1_InitComplete;
extern XBYTE   xNXP_PORT2_FailCount1;
extern XBYTE   xNXP_PORT2_FailCount2;
extern XBYTE   xNXP_PORT2_InitComplete;
extern XBYTE   xNXP_opm_cmd_ready;
extern XBYTE   xNXP_ppm_step;
extern XBYTE   xNXP_i2c_ack;
extern XBYTE   xNXP_i2c_fail;
extern XWORD   wNXP_pd_timeout;
extern XWORD   wNXP_hlk_timer;
extern XBYTE   xNXP_init;
extern XBYTE   xNXP_i2c_rbuf[];
extern XBYTE   xNXP_i2c_wbuf[];
extern XBYTE   xNXP_i2c_data[];

#if 1 //UCSI_SUPPORT
extern XBYTE    xUCSI1_DS_CCI0;
extern XBYTE    xUCSI1_DS_CCI1;
extern XBYTE    xUCSI1_DS_CCI2;
extern XBYTE    xUCSI1_DS_CCI3;
extern XBYTE    xUCSI1_DS_MGI[];

extern XBYTE    xUCSI2_DS_CCI0;
extern XBYTE    xUCSI2_DS_CCI1;
extern XBYTE    xUCSI2_DS_CCI2;
extern XBYTE    xUCSI2_DS_CCI3;
extern XBYTE    xUCSI2_DS_MGI[];

#endif  //UCSI_SUPPORT
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9200 ~ 0x92FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9200                  0x9200
//*******************************************************************************
#if 1   //UCSI_SUPPORT
//**********************************
// UCSI PPM Service Resources - Main Service Code Resources
//**********************************
extern XBYTE    xUCSI_ppm_step;          
extern XBYTE    xUCSI_init;         
extern XBYTE    xUCSI_opm_cmd_ready;          
extern XBYTE    xUCSI_i2c_fail;   
extern XWORD    wUCSI_task_running; 
extern XBYTE    xITEPD_Check2port;
#define F_PD_PORT1         BIT(0)
#define F_PD_PORT2         BIT(1)

extern XBYTE    xITEPD_SetCtrl;
extern XBYTE    xITEPD_UPD_TBT_Entry;

//**********************************
// ITE PD Flash Utility
//**********************************
extern XBYTE    xITEPD_FlashUtilityEnable;
extern XBYTE    xITEPD_FlashUtilityCmd;
extern XBYTE    xITEPD_FlashUtilityCmd2;
extern XBYTE    xITEPD_FlashUtilityCmd3;
extern XBYTE    xITEPD_FlashUtilityAck;
extern XBYTE    xITEPD_FlashUtilitySkipVerifyEn;
extern XBYTE    xITEPD_FlashUtilitySMBusSW;

//**********************************
// PD Port#1 Reg.Service Resources
//**********************************
extern XBYTE    xPD1_i2c_addr;          
extern XBYTE    xPD1_i2c_error;         
extern XWORD    xPD1_pd_mVoltage;       
extern XWORD    xPD1_pd_mCurrent;       
extern XWORD    xPD1_pd_mWatt;          
extern XBYTE    xPD1_pd_Voltage;        
extern XBYTE    xPD1_pd_Current;        
extern XBYTE    xPD1_pd_PowWatt;
extern XBYTE    xPD1_pd_PowWatt_tmp;
extern XBYTE    xPD1_int_service;      
extern XBYTE    xPD1_BIN_VERSION[];    
extern XBYTE    xPD1_FW_VERSION[];    
extern XBYTE    xPD1_fw_update; 
extern XBYTE    xPD1_fw_init;
//**********************************
// UCSI Port#2 Reg.Service Resources
//**********************************
extern XBYTE    xPD2_i2c_addr;          
extern XBYTE    xPD2_i2c_error;         
extern XWORD    xPD2_pd_mVoltage;       
extern XWORD    xPD2_pd_mCurrent;       
extern XWORD    xPD2_pd_mWatt;          
extern XBYTE    xPD2_pd_Voltage;        
extern XBYTE    xPD2_pd_Current;        
extern XBYTE    xPD2_pd_PowWatt;
extern XBYTE    xPD2_pd_PowWatt_tmp;        
extern XBYTE    xPD2_int_service;      
extern XBYTE    xPD2_BIN_VERSION[];    
extern XBYTE    xPD2_FW_VERSION[];    
extern XBYTE    xPD2_fw_update; 
extern XBYTE    xPD2_fw_init;

#endif  //UCSI_SUPPORT
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9300 ~ 0x93FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9300                  0x9300
extern XBYTE    SPI_BUF0[];
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9400 ~ 0x94FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9400                  0x9400
extern XBYTE    I2C_BUF0[];
extern XBYTE    I2C_BUF1[];

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9500 ~ 0x95FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9500                  0x9500
extern BYTE code *OOB_Table_Pntr;
extern XBYTE    xOOB_PacketMaxLength;
extern XBYTE    xOOB_PacketLength;
extern XBYTE    xOOB_Timeout;
extern XBYTE    xOOB_Failed;
extern XBYTE    xOOB_FailedCounter;
extern XBYTE    xOOB_DataCounter;
extern XBYTE    xOOB_Scan;
extern XBYTE    xOOB_GetPCH_Temper;
extern XBYTE    xOOB_GetPCH_RTC_Timer;
extern XBYTE    xOOB_GetPCH_Temper_Timer;
extern XBYTE    xOOB_PeciGetCpuT_Timer;
extern XBYTE    xOOB_PCH_Temperature;
extern XBYTE    eSPI_RTC_DATA[];
extern XBYTE    xTIME_SYNC;
extern XBYTE    xTIME_HH;
extern XBYTE    xTIME_MM;
extern XBYTE    xTIME_SS;
extern XBYTE    eSPI_PCH_TMPR[];

extern XBYTE    xOOB_PECI_CPU_T;
extern XBYTE    xOOB_PECI_Tj_max;
extern XBYTE    xOOB_PECI_Temper[];
extern XBYTE    xOOB_KEY_CRASHLOG;
#define KEY_FCD_LOCK         BIT1
#define KEY_FLD_LOCK         BIT2
extern XBYTE    xOOB_PauseTimer;

extern XBYTE    xOOB_GET_FLASH_ADR3;
extern XBYTE    xOOB_GET_FLASH_ADR2;
extern XBYTE    xOOB_GET_FLASH_ADR1;
extern XBYTE    xOOB_GET_FLASH_ADR0;
extern XBYTE    xOOB_GET_CRASHLOG;
extern XBYTE    xOOB_GET_PCH_TMPR;
extern XBYTE    xOOB_GET_RTC_DATA;

extern XBYTE    xOOB_CrashLogAddrH;
extern XBYTE    xOOB_CrashLogAddrM;
extern XBYTE    xOOB_Delay;
extern XBYTE    xOOB_CrashCpuIndex;
extern XBYTE    xOOB_CrashCpuIndexH;
extern XBYTE    xOOB_GetCrashLogLock;
extern XBYTE    xOOB_RemindGetCrashLogLED;

extern XWORD    wOOB_CrashCpuDataLines;
extern XWORD    wOOB_CrashCpuDataBytes;
extern XWORD    wOOB_CrashPchDataSizes;
extern XWORD    wOOB_CrashLogDataIndex;

extern XBYTE    eSPI_FLASH_DATA[];

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9600 ~ 0x96FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9600                  0x9600
//-----------------------------------------------------------------------------
extern XBYTE    PECI_FLAG;
#define F_PECI_STOP         BIT(7)
#define F_PECI_BUSY         BIT(6)
#define F_PECI_UPDATED      BIT(5)
#define F_PECI_INIT5        BIT(4)
#define F_PECI_INIT4        BIT(3)
#define F_PECI_INIT3        BIT(2)
#define F_PECI_INIT2        BIT(1)
#define F_PECI_INIT         BIT(0)

extern XBYTE    PECI_CMD;
extern XBYTE    PECI_CompletionCode;
extern XBYTE    PECI_TIMER;
extern XBYTE    PECI_ERRCNT;
extern XBYTE    PECI_ERRSTS;
extern XBYTE    PECI_OVTCT;
extern XBYTE    PECI_CRC8;
extern XBYTE    PECI_CPU_T;
extern XBYTE    PECI_CNT;

extern XBYTE    PECI_DIR;
extern XWORD    PECI_DELAY;
extern XWORD    PECI_MEMADR;
extern XBYTE    PECI_GetDIB[];
extern XBYTE    PECI_GetTemp[];
extern XBYTE    PECI_RdPkgCfg_Idx16_CC;
extern XBYTE    PECI_RdPkgCfg_Idx16[];
#define Processor_Tj_max        PECI_RdPkgCfg_Idx16[2]
#define Processor_T_control     PECI_RdPkgCfg_Idx16[1]
extern XBYTE    PECI_ReadBuffer[];
extern XBYTE    PECI_WriteBuffer[];

extern XBYTE    PECI_PowerLimit1;
extern XBYTE    PECI_PowerLimit1T;
extern XBYTE    PECI_PowerLimit2;
extern XBYTE    PECI_PowerLimit3;
extern XBYTE    PECI_PowerLimit4;

extern XBYTE    PECI_PowerUnit;
extern XBYTE    PECI_EnergyUnit;
extern XBYTE    PECI_TimeUnit;
extern XWORD    PECI_UnitPower;
extern XWORD    PECI_UnitTime;
extern XWORD    PECI_UnitEnergy;
extern XBYTE    xOOB_PECI_TEST;
extern XBYTE    xOOB_PECI_PLx_Index;
extern XBYTE    xOOB_PECI_PLx_Data0;
extern XBYTE    xOOB_PECI_PLx_Data1;

#if 1
#define _PL_RW_PL1      0x01
#define _PL_RW_PL2      0x02
#define _PL_RW_PL3      0x03
#define _PL_RW_PL4      0x04

#define _OOB_PL_RW_PL1  0x81
#define _OOB_PL_RW_PL2  0x82
#define _OOB_PL_RW_PL3  0x83
#define _OOB_PL_RW_PL4  0x84

#define _PL_WR_GO       0x20    //1,2,3,4 , Check = 0 not busy
#define _PLx_WR_ADDR    0x21
#define _PLxT_WR_ADDR   0x22

#define _PL_RD_GO       0x23    // 0: Read ok, 1,2,3,4=PL, Others read all
#define _PL1_RD_ADDR    0x24
#define _PL1T_RD_ADDR   0x25
#define _PL2_RD_ADDR    0x26
#define _PL3_RD_ADDR    0x27
#define _PL4_RD_ADDR    0x28

#define _PL1_SETW       0x2A
#define _PL1_SETT       0x2B
#define _PL2_SETW       0x2C
#define _PL3_SETW       0x2D
#define _PL4_SETW       0x2E

#endif

#if 1   // SUPPORT_SERVICE_CIR
extern XBYTE    CIR_KEY_CODE;
extern XBYTE    CIR_KEY_CODE2;
extern XBYTE    LAST_CIR_KEY_CODE;
extern XBYTE    CIR_RX_DIR;
extern XBYTE    CIR_RX_Timer;
extern XBYTE    CIR_ResetTimer;
extern XBYTE    CIR_KeyBreakTimer;
extern XBYTE    CIR_KEY_COUNT;
extern XBYTE    CIR_CodeTimer;
extern XBYTE    CIR_RX_BUF[];
extern XBYTE    CIR_TX_BUF[];
extern XBYTE    CIR_RX_KEY[];
#endif

#if 1   //SUPPORT_WINAPP_ITE_RFDU
extern XBYTE    xFREAD_Enabled;
extern XBYTE    xFREAD_StartNext;
extern XBYTE    xFREAD_eFlashAddrH;
extern XBYTE    xFREAD_eFlashAddrM;
extern XBYTE    xFREAD_eFlashAddrL;
extern XBYTE    xFREAD_BufferAddrH;
extern XBYTE    xFREAD_BufferAddrL;
#endif
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9700 ~ 0x97FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9700                  0x9700

extern XBYTE   eSPI_OOB_DATA[];
//-----------------------------------------------------------------------------
#endif  ///* IT5570/IT5571 EXTEDED 2 KB RAM */
//-----------------------------------------------------------------------------
// END
//-----------------------------------------------------------------------------
#endif  //OEM_MEMORY_H
