/*-----------------------------------------------------------------------------
* Filename:OEM_MEMORY.C     For Chipset: ITE.IT85XX
*
* Function: Memory Definition for extern all code base reference
*
* [Memory Map Description]
*
* Chip Internal Ram : 0x00-0xFF For Kernel and Chip Level use
*
***************************************************
* Chip 8500       : External ram 0x000-0x7FF
* Chip Other 85XX : External ram 0x000-0xFFF
***************************************************
*
* [OEM Memory Rang]
* [External Ram]
* 0x100-0x1FF   OEM RAM
* 0x200-0x2FF   OEM RAM SPI buffer array
* 0x300-0x3FF   OEM RAM EC Space
* 0x400-0x4FF   OEM RAM
* 0x500-0x5FF   OEM RAM

* 0x800-0x8FF   OEM RAM Ramdebug function.
* 0x800-0x9FF   OEM RAM
* 0xA00-0xAFF   OEM RAM
* 0xB00-0xBFF   OEM RAM
* 0xC00-0xCFF   OEM RAM
* 0xD00-0xDFF   OEM RAM
* 0xE00-0xEFF   OEM RAM
* 0xF00-0xFFF   OEM RAM For HSPI ram code function
*
* Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
*---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* Kernel none use resources (need adjustment after update kernel) */
//-----------------------------------------------------------------------------
#define MEM_SCI_RAM                 0x00A0
XBYTE   SCIEVT_BUF[8]               _at_ MEM_SCI_RAM + 0x00;
XBYTE   SCIEVT_WIDX                 _at_ MEM_SCI_RAM + 0x08;
XBYTE   SCIEVT_RIDX                 _at_ MEM_SCI_RAM + 0x09;
XBYTE   SCIEVT_OUT                  _at_ MEM_SCI_RAM + 0x0A;
XBYTE   SCIEVT_LOSE                 _at_ MEM_SCI_RAM + 0x0B;
XBYTE   SCIEVT_OVT                  _at_ MEM_SCI_RAM + 0x0C;
XBYTE   SCIEVT_DELAY                _at_ MEM_SCI_RAM + 0x0D;
XBYTE   SCIEVT_LAST                 _at_ MEM_SCI_RAM + 0x0E;
XBYTE   SCIEVT_CNT                  _at_ MEM_SCI_RAM + 0x0F;
//-----------------------------------------------------------------------------
#define MEM_PWRCTRL                 0x00B0
XBYTE   SysPowState                 _at_ MEM_PWRCTRL + 0x00;
XBYTE   CtrlPowStep                 _at_ MEM_PWRCTRL + 0x01;
XWORD   PowSeqDelay                 _at_ MEM_PWRCTRL + 0x02;
XWORD   PowSeqWait                  _at_ MEM_PWRCTRL + 0x04;

XBYTE   PowerOnFailed               _at_ MEM_PWRCTRL + 0x07;
XBYTE   PowSwFlag                   _at_ MEM_PWRCTRL + 0x08;
// XBYTE   SetAutoBootTimer            _at_ MEM_PWRCTRL + 0x09;
XBYTE   AutoBootTimer               _at_ MEM_PWRCTRL + 0x0A;
XBYTE   PanelOnStep                 _at_ MEM_PWRCTRL + 0x0B;
XBYTE   PanelOnDelay                _at_ MEM_PWRCTRL + 0x0C;
XBYTE   MutePinDelay                _at_ MEM_PWRCTRL + 0x0D;
XBYTE   LID_Debounce                _at_ MEM_PWRCTRL + 0x0E;
XBYTE   LID_OpenDebounce            _at_ MEM_PWRCTRL + 0x0F;
XWORD   PowSwLockTimer              _at_ MEM_PWRCTRL + 0x10;
XWORD   PowSwDownTimer              _at_ MEM_PWRCTRL + 0x12;
XWORD   PowSwDebounce               _at_ MEM_PWRCTRL + 0x14;
XWORD   wPwrSwTypingDelay           _at_ MEM_PWRCTRL + 0x16;
XWORD   wLockPWRBTN                 _at_ MEM_PWRCTRL + 0x18;
XWORD   LID_Resend                  _at_ MEM_PWRCTRL + 0x1C;
XWORD   LID_OpenResend              _at_ MEM_PWRCTRL + 0x1E;
XBYTE   SystemFlag1                 _at_ MEM_PWRCTRL + 0x20;
XBYTE   ADP_Debounce                _at_ MEM_PWRCTRL + 0x22;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0100 ~ 0x01FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0200 ~ 0x02FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define DPTF_MemBase                 0x0260
XBYTE   xEC_T1_LoLimit              _at_ DPTF_MemBase + 0x00;
XBYTE   xEC_T1_HiLimit              _at_ DPTF_MemBase + 0x01;
XBYTE   xEC_T2_LoLimit              _at_ DPTF_MemBase + 0x02;
XBYTE   xEC_T2_HiLimit              _at_ DPTF_MemBase + 0x03;
XBYTE   xEC_T3_LoLimit              _at_ DPTF_MemBase + 0x04;
XBYTE   xEC_T3_HiLimit              _at_ DPTF_MemBase + 0x05;
XBYTE   xEC_T4_LoLimit              _at_ DPTF_MemBase + 0x06; //BATT_T
XBYTE   xEC_T4_HiLimit              _at_ DPTF_MemBase + 0x07; //BATT_T
XBYTE   xEC_T5_LoLimit              _at_ DPTF_MemBase + 0x08;
XBYTE   xEC_T5_HiLimit              _at_ DPTF_MemBase + 0x09;

XBYTE   xEC_T1_SendEvent            _at_ DPTF_MemBase + 0x0A;
XBYTE   xEC_T1_THR                  _at_ DPTF_MemBase + 0x0B;
XWORD   wEC_T1_THR_ACC              _at_ DPTF_MemBase + 0x0C;

XBYTE   xEC_CPUT_EventTimer         _at_ DPTF_MemBase + 0x0E;
XBYTE   xEC_CPUT_SendEvent          _at_ DPTF_MemBase + 0x0F;
XBYTE   xEC_CPUT_HiLimit            _at_ DPTF_MemBase + 0x10;
XBYTE   xEC_CPUT_LoLimit            _at_ DPTF_MemBase + 0x11;

XBYTE   xEC_T1_AVG                  _at_ DPTF_MemBase + 0x12;
XBYTE   xEC_T1_EventTimer           _at_ DPTF_MemBase + 0x13;
XBYTE   xEC_T2_AVG                  _at_ DPTF_MemBase + 0x14;
XBYTE   xEC_T2_EventTimer           _at_ DPTF_MemBase + 0x15;
XBYTE   xEC_T3_AVG                  _at_ DPTF_MemBase + 0x16;
XBYTE   xEC_T3_EventTimer           _at_ DPTF_MemBase + 0x17;
XBYTE   xEC_T4_AVG                  _at_ DPTF_MemBase + 0x18;
XBYTE   xEC_T4_SendEvent            _at_ DPTF_MemBase + 0x19;
XBYTE   xEC_T5_EventTimer           _at_ DPTF_MemBase + 0x1A;
XBYTE   xEC_T5_AVG                  _at_ DPTF_MemBase + 0x1B;

XBYTE   xEC_T2_SendEvent            _at_ DPTF_MemBase + 0x1C;
XBYTE   xEC_T2_THR                  _at_ DPTF_MemBase + 0x1D;
XWORD   wEC_T2_THR_ACC              _at_ DPTF_MemBase + 0x1E;

XBYTE   xEC_T3_SendEvent            _at_ DPTF_MemBase + 0x20;
XBYTE   xEC_T3_THR                  _at_ DPTF_MemBase + 0x21;
XWORD   wEC_T3_THR_ACC              _at_ DPTF_MemBase + 0x22;  

XBYTE   xEC_T5_SendEvent            _at_ DPTF_MemBase + 0x24;
XBYTE   xEC_T5_THR                  _at_ DPTF_MemBase + 0x25;
XWORD   wEC_T5_THR_ACC              _at_ DPTF_MemBase + 0x26; 

#define Fan_MemBase                 0x0290
XBYTE   Fan1_DnTempr                _at_ Fan_MemBase + 0x00;
XBYTE   Fan1_RefTempr               _at_ Fan_MemBase + 0x01;
XBYTE   Fan1_UpTempr                _at_ Fan_MemBase + 0x02;
XBYTE   Fan1_LevelDir               _at_ Fan_MemBase + 0x03;
XBYTE   Fan1_CurrentLevelDir        _at_ Fan_MemBase + 0x04;
XBYTE   Fan1_NowDCR                 _at_ Fan_MemBase + 0x05;
XWORD   wFan1_TargetRPM             _at_ Fan_MemBase + 0x06;
XWORD   wFan1_CurrentRPM            _at_ Fan_MemBase + 0x08;
XBYTE   Fan1_Up_Delay               _at_ Fan_MemBase + 0x0A;
XBYTE   Fan1_Step                   _at_ Fan_MemBase + 0x0B;
XBYTE   Fan1_NeedInit               _at_ Fan_MemBase + 0x0C;
XBYTE   Fan1_UpdRPMCnt              _at_ Fan_MemBase + 0x0D;
XBYTE   Fan1_DebugCmd               _at_ Fan_MemBase + 0x0E;
XBYTE   Fan1_DebugKey               _at_ Fan_MemBase + 0x0F;
XBYTE   Fan1_T_Dn[16]               _at_ Fan_MemBase + 0x10; //0x02A0
XBYTE   Fan1_T_Up[16]               _at_ Fan_MemBase + 0x20; //0x02B0
XBYTE   Fan1_PWM[16]                _at_ Fan_MemBase + 0x30; //0x02C0
XBYTE   Fan1_RPM_H[16]              _at_ Fan_MemBase + 0x40; //0x02D0
XBYTE   Fan1_RPM_L[16]              _at_ Fan_MemBase + 0x50; //0x02E0
XBYTE   Fan1_ErrCheck               _at_ Fan_MemBase + 0x60; //0x02F0
XBYTE   FAN_DBG_CTRL_PWM            _at_ Fan_MemBase + 0x61; //0x02F1
XBYTE   FAN_DBG_CTRL_ON             _at_ Fan_MemBase + 0x62; //0x02F2
XWORD   wEC_FAN_CurrentRPM          _at_ Fan_MemBase + 0x64; //0x02F4
XBYTE   Fan1_TargetDCR              _at_ Fan_MemBase + 0x66; //0x02F6

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0300 ~ 0x03FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define SMBX_MemBase                0x0300
//-----------------------------------------------------------------------------
XBYTE   SMBA_CHN_STS                _at_ SMBX_MemBase + 0x00;
XBYTE   SMBA_CHN_TIMER              _at_ SMBX_MemBase + 0x01;
XBYTE   SMBA_DEV_DIR                _at_ SMBX_MemBase + 0x02;
XBYTE   SMBA_CHN_CTL                _at_ SMBX_MemBase + 0x03;
XBYTE   SMBA_CHN_CMD                _at_ SMBX_MemBase + 0x04;
XBYTE   SMBA_BYTE_CNT               _at_ SMBX_MemBase + 0x05;
XWORD   SMBA_DEV_MEM                _at_ SMBX_MemBase + 0x06;
XBYTE   SMBA_ERR_STS[4]             _at_ SMBX_MemBase + 0x08;
XBYTE   SMBA_DAT_CNT[4]             _at_ SMBX_MemBase + 0x0C;
XBYTE   SMBB_CHN_STS                _at_ SMBX_MemBase + 0x10;
XBYTE   SMBB_CHN_TIMER              _at_ SMBX_MemBase + 0x11;
XBYTE   SMBB_DEV_DIR                _at_ SMBX_MemBase + 0x12;
XBYTE   SMBB_CHN_CTL                _at_ SMBX_MemBase + 0x13;
XBYTE   SMBB_CHN_CMD                _at_ SMBX_MemBase + 0x14;
XBYTE   SMBB_BYTE_CNT               _at_ SMBX_MemBase + 0x15;
XWORD   SMBB_DEV_MEM                _at_ SMBX_MemBase + 0x16;
XBYTE   SMBB_ERR_STS[4]             _at_ SMBX_MemBase + 0x18;
XBYTE   SMBB_DAT_CNT[4]             _at_ SMBX_MemBase + 0x1C;
XBYTE   SMBC_CHN_STS                _at_ SMBX_MemBase + 0x20;
XBYTE   SMBC_CHN_TIMER              _at_ SMBX_MemBase + 0x21;
XBYTE   SMBC_DEV_DIR                _at_ SMBX_MemBase + 0x22;
XBYTE   SMBC_CHN_CTL                _at_ SMBX_MemBase + 0x23;
XBYTE   SMBC_CHN_CMD                _at_ SMBX_MemBase + 0x24;
XBYTE   SMBC_BYTE_CNT               _at_ SMBX_MemBase + 0x25;
XWORD   SMBC_DEV_MEM                _at_ SMBX_MemBase + 0x26;
XBYTE   SMBC_ERR_STS[4]             _at_ SMBX_MemBase + 0x28;
XBYTE   SMBC_DAT_CNT[4]             _at_ SMBX_MemBase + 0x2C;
XBYTE   SMBD_CHN_STS                _at_ SMBX_MemBase + 0x30;
XBYTE   SMBD_CHN_TIMER              _at_ SMBX_MemBase + 0x31;
XBYTE   SMBD_DEV_DIR                _at_ SMBX_MemBase + 0x32;
XBYTE   SMBD_CHN_CTL                _at_ SMBX_MemBase + 0x33;
XBYTE   SMBD_CHN_CMD                _at_ SMBX_MemBase + 0x34;
XBYTE   SMBD_BYTE_CNT               _at_ SMBX_MemBase + 0x35;
XWORD   SMBD_DEV_MEM                _at_ SMBX_MemBase + 0x36;
XBYTE   SMBD_ERR_STS[4]             _at_ SMBX_MemBase + 0x38;
XBYTE   SMBD_DAT_CNT[4]             _at_ SMBX_MemBase + 0x3C;
//-----------------------------------------------------------------------------
#define SMBV_MemBase                0x0340
XBYTE   SMBA_DEV0_STS               _at_ SMBV_MemBase + 0x00;
XBYTE   SMBA_DEV0_DIR               _at_ SMBV_MemBase + 0x01;
XWORD   SMBA_DEV0_DLY               _at_ SMBV_MemBase + 0x02;
XBYTE   SMBA_DEV1_STS               _at_ SMBV_MemBase + 0x04;
XBYTE   SMBA_DEV1_DIR               _at_ SMBV_MemBase + 0x05;
XWORD   SMBA_DEV1_DLY               _at_ SMBV_MemBase + 0x06;
XBYTE   SMBB_DEV0_STS               _at_ SMBV_MemBase + 0x08;
XBYTE   SMBB_DEV0_DIR               _at_ SMBV_MemBase + 0x09;
XWORD   SMBB_DEV0_DLY               _at_ SMBV_MemBase + 0x0A;
XBYTE   SMBB_DEV1_STS               _at_ SMBV_MemBase + 0x0C;
XBYTE   SMBB_DEV1_DIR               _at_ SMBV_MemBase + 0x0D;
XWORD   SMBB_DEV1_DLY               _at_ SMBV_MemBase + 0x0E;
XBYTE   SMBC_DEV0_STS               _at_ SMBV_MemBase + 0x10;
XBYTE   SMBC_DEV0_DIR               _at_ SMBV_MemBase + 0x11;
XWORD   SMBC_DEV0_DLY               _at_ SMBV_MemBase + 0x12;
XBYTE   SMBC_DEV1_STS               _at_ SMBV_MemBase + 0x14;
XBYTE   SMBC_DEV1_DIR               _at_ SMBV_MemBase + 0x15;
XWORD   SMBC_DEV1_DLY               _at_ SMBV_MemBase + 0x16;
XWORD   SMBA_DEV2_DLY               _at_ SMBV_MemBase + 0x18;
XWORD   SMBB_DEV2_DLY               _at_ SMBV_MemBase + 0x1A;
//-----------------------------------------------------------------------------
#define ADCC_MemBase                0x0380
XWORD   wADC[8]                     _at_ ADCC_MemBase + 0x00;
XBYTE   xADC[8]                     _at_ ADCC_MemBase + 0x10;
XBYTE   xADC_ScanTimer              _at_ ADCC_MemBase + 0x18;
XBYTE   xADC_Count                  _at_ ADCC_MemBase + 0x19;
XBYTE   xEC_T1_CNT                  _at_ ADCC_MemBase + 0x1A;
XBYTE   xEC_T2_CNT                  _at_ ADCC_MemBase + 0x1B;
XBYTE   xEC_T3_CNT                  _at_ ADCC_MemBase + 0x1C;
XBYTE   xEC_T5_CNT                  _at_ ADCC_MemBase + 0x1D;

//-----------------------------------------------------------------------------
#define GPID_MemBase                0x03A0
XBYTE   DebounceGPJ0                _at_ GPID_MemBase + 0x00;
XBYTE   DebounceGPJ3                _at_ GPID_MemBase + 0x01;

//-----------------------------------------------------------------------------
XBYTE   AnyKeyDownFlag              _at_ 0x03E0;
XBYTE   KB_BacklightTimer           _at_ 0x03E1;
XBYTE   KB_BacklightPWM             _at_ 0x03E2;
XBYTE   PowerLatchTimer             _at_ 0x03E3;
XBYTE   PwrLedBlinkTimer            _at_ 0x03E4;
XBYTE   ChargerBlinkTimer           _at_ 0x03E5;
XBYTE   ThermalBlinkEn              _at_ 0x03E6;

XBYTE   xGPI_Debounce0              _at_ 0x03E8;
XBYTE   xGPI_Debounce1              _at_ 0x03E9;
XBYTE   xGPI_Debounce2              _at_ 0x03EA;
XBYTE   xGPI_Debounce3              _at_ 0x03EB;

XBYTE   EC_SW_MIRROR                _at_ 0x03EC;
XBYTE   EC_SW_MIRROR_DELAY          _at_ 0x03ED;


XBYTE   xAMP_EN_TestTimer            _at_ 0x03F0;

#define DUBM_MemBase                0x03F8
XBYTE   xUBM_Step                   _at_ DUBM_MemBase + 0x00;   // 3F8
XWORD   xPowerOnBlinkLEDEn          _at_ DUBM_MemBase + 0x01;   // 3F9 3FA
XBYTE   xLowBattShutdownCnt         _at_ DUBM_MemBase + 0x03;   // 3FB

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0400 ~ 0x04FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define MEM_EC_SPACE                0x0400
XBYTE   xEC_MainVersion             _at_ MEM_EC_SPACE + 0x00;
XBYTE   xEC_SubVersion              _at_ MEM_EC_SPACE + 0x01;
XBYTE   xEC_KBCVersion              _at_ MEM_EC_SPACE + 0x02;
XBYTE   xEC_TestVersion             _at_ MEM_EC_SPACE + 0x03;
XBYTE   xEC_TestVersion2            _at_ MEM_EC_SPACE + 0x04;
XBYTE   xEC_ShipMode                _at_ MEM_EC_SPACE + 0x07;
XBYTE   xEC_BuildHour               _at_ MEM_EC_SPACE + 0x08;
XBYTE   xEC_BuildMin                _at_ MEM_EC_SPACE + 0x09;
XBYTE   xEC_BuildSec                _at_ MEM_EC_SPACE + 0x0A;
XBYTE   xEC_BuildYear               _at_ MEM_EC_SPACE + 0x0C;
XBYTE   xEC_BuildMonth              _at_ MEM_EC_SPACE + 0x0D;
XBYTE   xEC_BuildDay                _at_ MEM_EC_SPACE + 0x0E;
XBYTE   xEC_BuildIndex              _at_ MEM_EC_SPACE + 0x0F;
XBYTE   OEM_ControlPOWER            _at_ MEM_EC_SPACE + 0x10;
XBYTE   OEM_ControlDevice           _at_ MEM_EC_SPACE + 0x11;
XBYTE   OEM_ShutdownReason          _at_ MEM_EC_SPACE + 0x12;
XBYTE   xEC_PDPort1MainVersion      _at_ MEM_EC_SPACE + 0x15;
XBYTE   xEC_PDPort1SubVersion       _at_ MEM_EC_SPACE + 0x16;
XBYTE   xEC_UCSIMajorVersion        _at_ MEM_EC_SPACE + 0x17;
XBYTE   xEC_UCSIMinorVersion        _at_ MEM_EC_SPACE + 0x18;
XBYTE   xEC_UCSIRevVersion          _at_ MEM_EC_SPACE + 0x19;
XBYTE   xEC_ThermalChargCMD         _at_ MEM_EC_SPACE + 0x20;
XBYTE   xEC_ThermalChargFlag        _at_ MEM_EC_SPACE + 0x21;
XBYTE   xEC_BoardID_Value           _at_ MEM_EC_SPACE + 0x22;

XBYTE   xEC_SensorT_Error_F         _at_ MEM_EC_SPACE + 0x30;

XBYTE   xEC_RTC_WakeupFlag          _at_ MEM_EC_SPACE + 0x42;
XBYTE   xEC_RTC_SupportFlag         _at_ MEM_EC_SPACE + 0x43;
XWORD   xEC_RTC_Wakeuptimer         _at_ MEM_EC_SPACE + 0x44;
XWORD   xEC_Forece_Shutdown_counter _at_ MEM_EC_SPACE + 0x47;
XWORD   xEC_RTC_test_counter        _at_ MEM_EC_SPACE + 0x49;
XBYTE   xEC_FAN_PWM_DCR             _at_ MEM_EC_SPACE + 0x4B;
XBYTE   xEC_MultiFunctionCtrl       _at_ MEM_EC_SPACE + 0x4F;
#if 0
XWORD   xEC_Charge_Rate             _at_ MEM_EC_SPACE + 0x50;
XWORD   xEC_Charge_InCurrent        _at_ MEM_EC_SPACE + 0x52;
XWORD   xEC_Charge_Vlot             _at_ MEM_EC_SPACE + 0x54;
XWORD   xEC_Charge_option           _at_ MEM_EC_SPACE + 0x56;
#else
XBYTE   xEC_FSL_PPSL                _at_ MEM_EC_SPACE + 0x50;
XBYTE   xEC_FSL_PPSH                _at_ MEM_EC_SPACE + 0x51;
XBYTE   xEC_FSL_PINV                _at_ MEM_EC_SPACE + 0x52;
XBYTE   xEC_FSL_PENV                _at_ MEM_EC_SPACE + 0x53;
XBYTE   xEC_FSL_PSTP                _at_ MEM_EC_SPACE + 0x54;
#endif

XBYTE   xEC_SOCCriTripPoint         _at_ MEM_EC_SPACE + 0x60; // Set from BIOS
XBYTE   xEC_SkinCriTripPoint        _at_ MEM_EC_SPACE + 0x61; // Set from BIOS
XBYTE   xEC_Sensor_2_T              _at_ MEM_EC_SPACE + 0x62; //T2 SEN2
XBYTE   xEC_Sensor_F                _at_ MEM_EC_SPACE + 0x63;
XBYTE   xEC_Sensor_TSHT             _at_ MEM_EC_SPACE + 0x64;
XBYTE   xEC_Sensor_TSLT             _at_ MEM_EC_SPACE + 0x65;
XBYTE   xEC_ThermalSource           _at_ MEM_EC_SPACE + 0x66;
XBYTE   xEC_POGO_Status             _at_ MEM_EC_SPACE + 0x67;
XWORD   xEC_BAT1_Temperature        _at_ MEM_EC_SPACE + 0x68;
XBYTE   xEC_BAT1_TemperatureCes     _at_ MEM_EC_SPACE + 0x6A;
XBYTE   xEC_PECI_CPU_T              _at_ MEM_EC_SPACE + 0x70;
XBYTE   xEC_PLMX_T                  _at_ MEM_EC_SPACE + 0x71;
XBYTE   xEC_Sensor_1_T              _at_ MEM_EC_SPACE + 0x72; //T1 SEN1
XBYTE   xEC_Sensor_3_T              _at_ MEM_EC_SPACE + 0x73; //T3 SEN3
XWORD   xEC_BAT1_T4                 _at_ MEM_EC_SPACE + 0x74;
XWORD   xEC_Debug_Fan1Rpm           _at_ MEM_EC_SPACE + 0x76;
XWORD   xEC_Debug_Fan2Rpm           _at_ MEM_EC_SPACE + 0x78;
XBYTE   xEC_SAR_Event               _at_ MEM_EC_SPACE + 0x7A;
XBYTE   xEC_FeatureStatus           _at_ MEM_EC_SPACE + 0x7B;
XBYTE   xEC_SafeVoltageValueL       _at_ MEM_EC_SPACE + 0x7C;
XBYTE   xEC_SafeVoltageValueH       _at_ MEM_EC_SPACE + 0x7D;
XBYTE   SetAutoBootTimer            _at_ MEM_EC_SPACE + 0x7E;
XBYTE   xEC_LID_STATUS              _at_ MEM_EC_SPACE + 0x7F;
XBYTE   xEC_PowerState              _at_ MEM_EC_SPACE + 0x80;
XBYTE   xEC_Bt1ModelCode            _at_ MEM_EC_SPACE + 0x81;
XBYTE   xEC_Bt1SerialNumberL        _at_ MEM_EC_SPACE + 0x82;
XBYTE   xEC_Bt1SerialNumberH        _at_ MEM_EC_SPACE + 0x83;
XBYTE   xEC_Bt1DesignCapacityL      _at_ MEM_EC_SPACE + 0x84;
XBYTE   xEC_Bt1DesignCapacityH      _at_ MEM_EC_SPACE + 0x85;
XBYTE   xEC_Bt1DesignVoltageL       _at_ MEM_EC_SPACE + 0x86;
XBYTE   xEC_Bt1DesignVoltageH       _at_ MEM_EC_SPACE + 0x87;
XBYTE   xEC_Bt1FullChrgCapacityL    _at_ MEM_EC_SPACE + 0x88;
XBYTE   xEC_Bt1FullChrgCapacityH    _at_ MEM_EC_SPACE + 0x89;
XBYTE   xEC_Bt1TripPointL           _at_ MEM_EC_SPACE + 0x8A;
XBYTE   xEC_Bt1TripPointH           _at_ MEM_EC_SPACE + 0x8B;
XBYTE   xEC_Bt1State                _at_ MEM_EC_SPACE + 0x8C;
XBYTE   xEC_Bt1PresentRateL         _at_ MEM_EC_SPACE + 0x8D;
XBYTE   xEC_Bt1PresentRateH         _at_ MEM_EC_SPACE + 0x8E;
XBYTE   xEC_Bt1RemainCapacityL      _at_ MEM_EC_SPACE + 0x8F;
XBYTE   xEC_Bt1RemainCapacityH      _at_ MEM_EC_SPACE + 0x90;
XBYTE   xEC_Bt1PresentVoltageL      _at_ MEM_EC_SPACE + 0x91;
XBYTE   xEC_Bt1PresentVoltageH      _at_ MEM_EC_SPACE + 0x92;
XBYTE   xEC_Bt1RSOC                 _at_ MEM_EC_SPACE + 0x93;
XBYTE   xEC_Bt1CurrentL             _at_ MEM_EC_SPACE + 0x94;
XBYTE   xEC_Bt1CurrentH             _at_ MEM_EC_SPACE + 0x95;

XBYTE   xEC_TSR1                    _at_ MEM_EC_SPACE + 0xA1;
XBYTE   xEC_TSR1H                   _at_ MEM_EC_SPACE + 0xA2;
XBYTE   xEC_StopChargingReason      _at_ MEM_EC_SPACE + 0xA3;

XBYTE   xEC_PD1FWVersion[8]    		_at_ MEM_EC_SPACE + 0xB0;
XBYTE   xEC_PD2FWVersion[8]    		_at_ MEM_EC_SPACE + 0xB8;
//-----------------------------------------------------------------------------
/* USB TYPE C  (x04C0 ~ 0x4EF) */
//-----------------------------------------------------------------------------
#if 1   //UCSI_SUPPORT  /* 0x4C0 ~ 0x4EF for UCSI function */
XBYTE   xUCSI_DS_VERSION[2]         _at_ MEM_EC_SPACE + 0xC0;
XBYTE   xUCSI_DS_RESERVED[2]        _at_ MEM_EC_SPACE + 0xC2;
XBYTE   xUCSI_DS_CCI0               _at_ MEM_EC_SPACE + 0xC4;
XBYTE   xUCSI_DS_CCI1               _at_ MEM_EC_SPACE + 0xC5;
XBYTE   xUCSI_DS_CCI2               _at_ MEM_EC_SPACE + 0xC6;
XBYTE   xUCSI_DS_CCI3               _at_ MEM_EC_SPACE + 0xC7;
XBYTE   xUCSI_DS_CTL0               _at_ MEM_EC_SPACE + 0xC8;
#define xUCSI_COMMAND       xUCSI_DS_CTL0
XBYTE   xUCSI_DS_CTL1               _at_ MEM_EC_SPACE + 0xC9;
XBYTE   xUCSI_DS_CTL2               _at_ MEM_EC_SPACE + 0xCA;
XBYTE   xUCSI_DS_CTL3               _at_ MEM_EC_SPACE + 0xCB;
XBYTE   xUCSI_DS_CTL4               _at_ MEM_EC_SPACE + 0xCC;
XBYTE   xUCSI_DS_CTL5               _at_ MEM_EC_SPACE + 0xCD;
XBYTE   xUCSI_DS_CTL6               _at_ MEM_EC_SPACE + 0xCE;
XBYTE   xUCSI_DS_CTL7               _at_ MEM_EC_SPACE + 0xCF;
XBYTE   xUCSI_DS_MGI[16]            _at_ MEM_EC_SPACE + 0xD0;
XBYTE   xUCSI_DS_MGO[16]            _at_ MEM_EC_SPACE + 0xE0;
#endif //UCSI_SUPPORT
//-----------------------------------------------------------------------------
XBYTE   HOST_BIOS_REG1              _at_ MEM_EC_SPACE + 0xF9; /* BIOS Setting */
XBYTE   PwrBtn_OVR_Mode             _at_ MEM_EC_SPACE + 0xFA; /* BIOS Setting */
XBYTE   System_CS_Mode              _at_ MEM_EC_SPACE + 0xFB; /* BIOS Setting */
XBYTE   LED_CTRL_MODE               _at_ MEM_EC_SPACE + 0xFC; /* BIOS Setting */
XBYTE   xEC_ShutdownCode            _at_ MEM_EC_SPACE + 0xFD;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0500 ~ 0x05FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define BAT1_MemBase                0x0500
XWORD   BAT1_ManufacturerAccess     _at_ BAT1_MemBase + 0x00;
XWORD   BAT1_BatteryMode            _at_ BAT1_MemBase + 0x02;
XWORD   BAT1_Temperature            _at_ BAT1_MemBase + 0x04;
XWORD   BAT1_Voltage                _at_ BAT1_MemBase + 0x06;
XWORD   BAT1_Current                _at_ BAT1_MemBase + 0x08;
XWORD   BAT1_AverageCurrent         _at_ BAT1_MemBase + 0x0A;
XWORD   BAT1_MaxError               _at_ BAT1_MemBase + 0x0C;
XBYTE   BAT1_RelativeStateOfChg     _at_ BAT1_MemBase + 0x0E;
XBYTE   BAT1_RelativeStateOfChgL    _at_ BAT1_MemBase + 0x0F;
XWORD   BAT1_AbsoluteOfCharge       _at_ BAT1_MemBase + 0x10;
XWORD   BAT1_RemainingCapacity      _at_ BAT1_MemBase + 0x12;
XWORD   BAT1_FullChargeCapacity     _at_ BAT1_MemBase + 0x14;
XWORD   BAT1_ChargingCurrent        _at_ BAT1_MemBase + 0x16;
XWORD   BAT1_ChargingVoltage        _at_ BAT1_MemBase + 0x18;
XWORD   BAT1_BatteryStatus1         _at_ BAT1_MemBase + 0x1A;
XWORD   BAT1_CycleCount             _at_ BAT1_MemBase + 0x1C;
XWORD   BAT1_DesignCapacity         _at_ BAT1_MemBase + 0x1E;
XWORD   BAT1_DesignVoltage          _at_ BAT1_MemBase + 0x20;
XWORD   BAT1_SpecificationInfo      _at_ BAT1_MemBase + 0x22;
XWORD   BAT1_ManufactureDate        _at_ BAT1_MemBase + 0x24;
XWORD   BAT1_SerialNumber           _at_ BAT1_MemBase + 0x26;
XBYTE   BAT1_ManufacturerName[14]   _at_ BAT1_MemBase + 0x28;
XBYTE   BAT1_DeviceName[14]         _at_ BAT1_MemBase + 0x37;
XBYTE   BAT1_DeviceChemistry[6]     _at_ BAT1_MemBase + 0x45;
XBYTE   BAT1_ManufacturerData[14]   _at_ BAT1_MemBase + 0x4B;
XBYTE   BAT1_PACKAGE                _at_ BAT1_MemBase + 0x59;
XWORD   BAT1_BatteryStatus2         _at_ BAT1_MemBase + 0x5A;
XWORD   BAT1_BatteryStatus          _at_ BAT1_MemBase + 0x5C;
XBYTE   BAT1_LockPowerOnRSOC        _at_ BAT1_MemBase + 0x5E;
XBYTE   BAT1_DebugMode              _at_ BAT1_MemBase + 0x5F;
XBYTE   BAT1_LastRSOC               _at_ BAT1_MemBase + 0x60;
XWORD   BAT1_LastFCC                _at_ BAT1_MemBase + 0x61;
XBYTE   BAT1_CheckRecharge          _at_ BAT1_MemBase + 0x63;
XBYTE   CHGR_StepChangeCnt          _at_ BAT1_MemBase + 0x64;
XBYTE   CHGR_FastChargeStep         _at_ BAT1_MemBase + 0x65;
XBYTE   BAT1_CelsiusDegree          _at_ BAT1_MemBase + 0x66;
XWORD   BAT1_Dead_Counter           _at_ BAT1_MemBase + 0x67;
XWORD   BAT1_SafeVoltageValue       _at_ BAT1_MemBase + 0x69;   // 0x69 0x6A
XBYTE   BAT1_THROT_DIR              _at_ BAT1_MemBase + 0x6B;
XWORD   BAT1_THROT_DNT              _at_ BAT1_MemBase + 0x6C;
XWORD   BAT1_THROT_UPT              _at_ BAT1_MemBase + 0x6E;

//-----------------------------------------------------------------------------
#define ACBT_MemBase                0x0570
XBYTE   xEC_PowerSource             _at_ ACBT_MemBase + 0x00;
XBYTE   PowerSource                 _at_ ACBT_MemBase + 0x01;
XBYTE   Debounce_ACin               _at_ ACBT_MemBase + 0x02;
XBYTE   Debounce_Bt1In              _at_ ACBT_MemBase + 0x03;
XBYTE   Debounce_Bt2In              _at_ ACBT_MemBase + 0x04;
XBYTE   SendBatEventTimer           _at_ ACBT_MemBase + 0x05;
XBYTE   SendACiEventTimer           _at_ ACBT_MemBase + 0x06;
XBYTE   BatSetPowerLimit            _at_ ACBT_MemBase + 0x07;
XBYTE   DeadBatteryActiveTimer      _at_ ACBT_MemBase + 0x08;
XBYTE   BatteryDetectStep           _at_ ACBT_MemBase + 0x0A;
XBYTE   BatteryDetectRetry          _at_ ACBT_MemBase + 0x0B;
XWORD   wBatteryDetectTmr           _at_ ACBT_MemBase + 0x0C;
XBYTE   EventTestTimer              _at_ ACBT_MemBase + 0x0E;
XBYTE   EventTestNumber             _at_ ACBT_MemBase + 0x0F;

//-----------------------------------------------------------------------------
#define XSAR_MemBase                0x0580
XBYTE   xSAR_PRODUCT_NUM            _at_ XSAR_MemBase+0x00;
XBYTE   xSAR_VERSION_NUM            _at_ XSAR_MemBase+0x01;
XBYTE   xSAR_DEBUG_EVENTS           _at_ XSAR_MemBase+0x02;
XBYTE   xSAR_COMMANDS               _at_ XSAR_MemBase+0x04;
XBYTE   xSAR_OTP_BANK1              _at_ XSAR_MemBase+0x05;
XBYTE   xSAR_OTP_BANK2              _at_ XSAR_MemBase+0x06;
XBYTE   xSAR_OTP_BANK3              _at_ XSAR_MemBase+0x07;
XBYTE   xSAR_QUICK_RELEASE          _at_ XSAR_MemBase+0x08;
XBYTE   xSAR_MOVEMENT               _at_ XSAR_MemBase+0x09;
XBYTE   xSAR_TOUCH_THR              _at_ XSAR_MemBase+0x0A;
XBYTE   xSAR_PROXIMITY_THR          _at_ XSAR_MemBase+0x0B;
XBYTE   xSAR_TEMP_INF_THR           _at_ XSAR_MemBase+0x0C;
XBYTE   xSAR_CH0_MULT               _at_ XSAR_MemBase+0x0D;
XBYTE   xSAR_CH0_COMP               _at_ XSAR_MemBase+0x0E;
XBYTE   xSAR_CH1_MULT               _at_ XSAR_MemBase+0x0F;
XBYTE   xSAR_CH1_COMP               _at_ XSAR_MemBase+0x10;
XBYTE   xSAR_SYS_FLAG               _at_ XSAR_MemBase+0x11;
XBYTE   xSAR_UI_FLAG                _at_ XSAR_MemBase+0x12;
XBYTE   xSAR_ATI_FLAG               _at_ XSAR_MemBase+0x13;
XBYTE   xSAR_EVENT_FLAG             _at_ XSAR_MemBase+0x14;
XBYTE   xSAR_CH0_ACF_H              _at_ XSAR_MemBase+0x15;
XBYTE   xSAR_CH0_ACF_L              _at_ XSAR_MemBase+0x16;
XBYTE   xSAR_CH0_LTA_H              _at_ XSAR_MemBase+0x17;
XBYTE   xSAR_CH0_LTA_L              _at_ XSAR_MemBase+0x18;
XBYTE   xSAR_CH0_QRD_H              _at_ XSAR_MemBase+0x19;
XBYTE   xSAR_CH0_QRD_L              _at_ XSAR_MemBase+0x1A;
XBYTE   xSAR_CH1_ACF_H              _at_ XSAR_MemBase+0x1B;
XBYTE   xSAR_CH1_ACF_L              _at_ XSAR_MemBase+0x1C;
XBYTE   xSAR_CH1_UMOV_H             _at_ XSAR_MemBase+0x1D;
XBYTE   xSAR_CH1_UMOV_L             _at_ XSAR_MemBase+0x1E;
XBYTE   xSAR_CH1_LMOV_H             _at_ XSAR_MemBase+0x1F;
XBYTE   xSAR_CH1_LMOV_L             _at_ XSAR_MemBase+0x20;
XBYTE   xSAR_CH1_RAW_H              _at_ XSAR_MemBase+0x21;
XBYTE   xSAR_CH1_RAW_L              _at_ XSAR_MemBase+0x22;
XBYTE   xSAR_TEMP_H                 _at_ XSAR_MemBase+0x23;
XBYTE   xSAR_TEMP_L                 _at_ XSAR_MemBase+0x24;
XBYTE   xSAR_LTA_HALT_TIMER_H       _at_ XSAR_MemBase+0x25;
XBYTE   xSAR_LTA_HALT_TIMER_L       _at_ XSAR_MemBase+0x26;
XBYTE   xSAR_FILTER_HALT_TIMER      _at_ XSAR_MemBase+0x27;
XBYTE   xSAR_TIMER_READ_INPUT       _at_ XSAR_MemBase+0x28;
XBYTE   xSAR_TIMER_READ_ATI         _at_ XSAR_MemBase+0x29;
XBYTE   xSAR_Event_Trigger_Timer    _at_ XSAR_MemBase+0x2A;
XBYTE   xSAR_Event_Release_Timer    _at_ XSAR_MemBase+0x2B;

#define xTP_MemBase                 0x05B0
XBYTE   xSOCTripPointCnt            _at_ xTP_MemBase+0x00;
XBYTE   xSkinTripPointCnt           _at_ xTP_MemBase+0x01;

#define xFP_MemBase                 0x05C0
XBYTE   xEC_StateTimer              _at_ xFP_MemBase+0x00;

#define DOCK_MemBase                0x05C8
XBYTE   xDOCK_Event_In_Timer        _at_ DOCK_MemBase+0x00;
XBYTE   xDOCK_Event_Out_Timer       _at_ DOCK_MemBase+0x01;

XBYTE   xEC_Battery4PWakeup         _at_ 0x05CA;
//-----------------------------------------------------------------------------
#define CHGR_MemBase                0x05D0
XWORD   CHGR_ChargerOption          _at_ CHGR_MemBase + 0x00;
XWORD   CHGR_InputCurrent           _at_ CHGR_MemBase + 0x02;
XWORD   CHGR_ChargingCurrent        _at_ CHGR_MemBase + 0x04;
XWORD   CHGR_ChargingVoltage        _at_ CHGR_MemBase + 0x06;
XWORD   CHGR_ManufacturerID         _at_ CHGR_MemBase + 0x08;
XWORD   CHGR_DeviceID               _at_ CHGR_MemBase + 0x0A;
XWORD   CHGR_ChargerREG3E           _at_ CHGR_MemBase + 0x0C;
XBYTE   WakeUpChargeTimer           _at_ CHGR_MemBase + 0x0E;
XWORD   CHGR_ChargerOptionR         _at_ CHGR_MemBase + 0x10;
XWORD   CHGR_InputCurrentR          _at_ CHGR_MemBase + 0x12;
XWORD   CHGR_ChargingCurrentR       _at_ CHGR_MemBase + 0x14;
XWORD   CHGR_ChargingVoltageR       _at_ CHGR_MemBase + 0x16;

XWORD   BAT1_0025FCC                _at_ CHGR_MemBase + 0x20;
XWORD   BAT1_005FCC                 _at_ CHGR_MemBase + 0x22;
XWORD   BAT1_02FCC                  _at_ CHGR_MemBase + 0x24;
XWORD   BAT1_05FCC                  _at_ CHGR_MemBase + 0x26;
XWORD   BAT1_08FCC                  _at_ CHGR_MemBase + 0x28;


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0600 ~ 0x06FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define MSBY_MemBase                0x0600
XBYTE   xMSBY_Mode                  _at_(MSBY_MemBase + 0x00);
XBYTE   xMSBY_SleepCounter          _at_(MSBY_MemBase + 0x01);
XBYTE   xMSBY_DozeCounter           _at_(MSBY_MemBase + 0x02);
XBYTE   xMSBY_ServiceKey            _at_(MSBY_MemBase + 0x03);
XBYTE   xMSBY_ExitKey               _at_(MSBY_MemBase + 0x04);
XBYTE   xMSBY_EnLidOpenWake         _at_(MSBY_MemBase + 0x05);
XBYTE   xMSBY_SleepDelay            _at_(MSBY_MemBase + 0x06);
XBYTE   xMSBY_GetBatteryStep        _at_(MSBY_MemBase + 0x07);
XBYTE   xMSBY_GetThermalStep        _at_(MSBY_MemBase + 0x08);
XBYTE   xMSBY_S3SleepCounter        _at_(MSBY_MemBase + 0x09);
XWORD   wMSBY_SLP_S0_LoT            _at_(MSBY_MemBase + 0x10);
XWORD   wMSBY_SLP_S0_HiT            _at_(MSBY_MemBase + 0x12);
XWORD   wMSBY_EnterDelay            _at_(MSBY_MemBase + 0x14);
XWORD wMSBY_SLP_S3_LoT              _at_(MSBY_MemBase + 0x16);
XWORD wMSBY_SLP_S3_HiT              _at_(MSBY_MemBase + 0x18);
XBYTE xMSBY_WakeUpFlag              _at_(MSBY_MemBase + 0x1A);
XBYTE xATNA_IdleTimer               _at_(MSBY_MemBase + 0x1B);
XBYTE xECPW_DeepSleepDelay          _at_(MSBY_MemBase + 0x1C);
XWORD wMSBY_BatteryPollingDelay     _at_(MSBY_MemBase + 0x1E);
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0700 ~ 0x08FF) (Don't use) **********************/
/*****************************************************************************/
//-----------------------------------------------------------------------------

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
XBYTE   RamBufferA[256]             _at_ 0x0A00;
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
/* 256 bytes SPI read/write buffer */
XBYTE   SPIBuffer[256]              _at_(OEMRAMC + 0x00);
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xD00-0xDFF   OEM RAM D
//-------------------------------------------------------------------------------
//*******************************************************************************
/* 256 bytes SPI read/write buffer */
XBYTE   SPIBuffer2[256]             _at_(OEMRAMD + 0x00);
//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xE00-0xEFF   OEM RAM E
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//  0xF00-0xFFF   OEM RAM F
//-------------------------------------------------------------------------------
//*******************************************************************************

#if 1   /* IT5570/IT5571 EXTEDED 2 KB RAM */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9000 ~ 0x90FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9000                      0x9000
XBYTE   WarmBootCounter                 _at_ ECRAM_9000 + 0x00;
XBYTE   Fan_First_Speed_Flag            _at_ ECRAM_9000 + 0x01;
XBYTE   Fan_Delay_Flag                  _at_ ECRAM_9000 + 0x02;
XBYTE   CPU_T_Flag                      _at_ ECRAM_9000 + 0x03;
XBYTE   CPU_T_Dn_Flag                   _at_ ECRAM_9000 + 0x04;
XBYTE   CPU_T_Up_Flag                   _at_ ECRAM_9000 + 0x05;


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9100 ~ 0x90FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9100                      0x9100

XBYTE   xNXP_PORT1_Device_ID                _at_ ECRAM_9100 + 0x00;
XBYTE   xNXP_PORT1_Devcie_Status            _at_ ECRAM_9100 + 0x01;
XBYTE   xNXP_PORT1_Switch_Control           _at_ ECRAM_9100 + 0x02;
XBYTE   xNXP_PORT1_Switch_Status            _at_ ECRAM_9100 + 0x03;
XBYTE   xNXP_PORT1_Interrupt1               _at_ ECRAM_9100 + 0x04;
XBYTE   xNXP_PORT1_Interrupt2               _at_ ECRAM_9100 + 0x05;
XBYTE   xNXP_PORT1_Interrupt1_Mask          _at_ ECRAM_9100 + 0x06;
XBYTE   xNXP_PORT1_Interrupt2_Mask          _at_ ECRAM_9100 + 0x07;
XBYTE   xNXP_PORT1_OVLO_Threshold           _at_ ECRAM_9100 + 0x08;
XBYTE   xNXP_PORT1_HV_SRC_OCP_Threshold     _at_ ECRAM_9100 + 0x09;
XBYTE   xNXP_PORT1_5V_SRC_OCP_Threshold     _at_ ECRAM_9100 + 0x0A;
XBYTE   xNXP_PORT1_Device_Control           _at_ ECRAM_9100 + 0x0B;

XBYTE   xNXP_PORT2_Device_ID                _at_ ECRAM_9100 + 0x10;
XBYTE   xNXP_PORT2_Devcie_Status            _at_ ECRAM_9100 + 0x11;
XBYTE   xNXP_PORT2_Switch_Control           _at_ ECRAM_9100 + 0x12;
XBYTE   xNXP_PORT2_Switch_Status            _at_ ECRAM_9100 + 0x13;
XBYTE   xNXP_PORT2_Interrupt1               _at_ ECRAM_9100 + 0x14;
XBYTE   xNXP_PORT2_Interrupt2               _at_ ECRAM_9100 + 0x15;
XBYTE   xNXP_PORT2_Interrupt1_Mask          _at_ ECRAM_9100 + 0x16;
XBYTE   xNXP_PORT2_Interrupt2_Mask          _at_ ECRAM_9100 + 0x17;
XBYTE   xNXP_PORT2_OVLO_Threshold           _at_ ECRAM_9100 + 0x18;
XBYTE   xNXP_PORT2_HV_SRC_OCP_Threshold     _at_ ECRAM_9100 + 0x19;
XBYTE   xNXP_PORT2_5V_SRC_OCP_Threshold     _at_ ECRAM_9100 + 0x1A;
XBYTE   xNXP_PORT2_Device_Control           _at_ ECRAM_9100 + 0x1B;
XBYTE   xNXP_PORT1_FailCount1               _at_ ECRAM_9100 + 0x20;
XBYTE   xNXP_PORT1_FailCount2               _at_ ECRAM_9100 + 0x21;
XBYTE   xNXP_PORT1_InitComplete             _at_ ECRAM_9100 + 0x22;

XBYTE   xNXP_PORT2_FailCount1               _at_ ECRAM_9100 + 0x28;
XBYTE   xNXP_PORT2_FailCount2               _at_ ECRAM_9100 + 0x29;
XBYTE   xNXP_PORT2_InitComplete             _at_ ECRAM_9100 + 0x2A;

#define MEM_EC_xNXP                        0x9130
XBYTE   xNXP_opm_cmd_ready                  _at_ MEM_EC_xNXP + 0x00;
XBYTE   xNXP_ppm_step                       _at_ MEM_EC_xNXP + 0x01;
XBYTE   xNXP_i2c_ack                        _at_ MEM_EC_xNXP + 0x02;
XBYTE   xNXP_i2c_fail                       _at_ MEM_EC_xNXP + 0x03;
XWORD   wNXP_pd_timeout                     _at_ MEM_EC_xNXP + 0x04;
XWORD   wNXP_hlk_timer                      _at_ MEM_EC_xNXP + 0x06;
XBYTE   xNXP_init                           _at_ MEM_EC_xNXP + 0x08;
XBYTE   xNXP_i2c_rbuf[16]                   _at_ MEM_EC_xNXP + 0x10;
XBYTE   xNXP_i2c_wbuf[18]                   _at_ MEM_EC_xNXP + 0x20;
XBYTE   xNXP_i2c_data[4]                    _at_ MEM_EC_xNXP + 0x32;

#if 1   //UCSI_SUPPORT
XBYTE   xUCSI1_DS_CCI0                      _at_ ECRAM_9100 + 0x74;
XBYTE   xUCSI1_DS_CCI1                      _at_ ECRAM_9100 + 0x75;
XBYTE   xUCSI1_DS_CCI2                      _at_ ECRAM_9100 + 0x76;
XBYTE   xUCSI1_DS_CCI3                      _at_ ECRAM_9100 + 0x77;
XBYTE   xUCSI1_DS_MGI[16]                   _at_ ECRAM_9100 + 0x80;

XBYTE   xUCSI2_DS_CCI0                      _at_ ECRAM_9100 + 0x94;
XBYTE   xUCSI2_DS_CCI1                      _at_ ECRAM_9100 + 0x95;
XBYTE   xUCSI2_DS_CCI2                      _at_ ECRAM_9100 + 0x96;
XBYTE   xUCSI2_DS_CCI3                      _at_ ECRAM_9100 + 0x97;
XBYTE   xUCSI2_DS_MGI[16]                   _at_ ECRAM_9100 + 0xA0;
#endif //UCSI_SUPPORT
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9200 ~ 0x92FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9200                          0x9200
#if 1	//UCSI_SUPPORT
//**********************************
// UCSI PPM Service Resources - Main Service Code Resources
//**********************************
#define UCSI_PPMBase                0x9200
XBYTE   xUCSI_ppm_step              _at_ UCSI_PPMBase + 0x00;
XBYTE   xUCSI_init                  _at_ UCSI_PPMBase + 0x01;
XBYTE   xUCSI_opm_cmd_ready         _at_ UCSI_PPMBase + 0x02;
XBYTE   xUCSI_i2c_fail              _at_ UCSI_PPMBase + 0x03;
XWORD   wUCSI_task_running          _at_ UCSI_PPMBase + 0x04; 
XBYTE   xITEPD_Check2port           _at_ UCSI_PPMBase + 0x06;

#define PDCMD_MemBase                0x9250
XBYTE   xITEPD_SetCtrl              _at_ PDCMD_MemBase + 0x00;
XBYTE   xITEPD_UPD_TBT_Entry        _at_ PDCMD_MemBase + 0x01;

//**********************************
// ITE PD Flash Utility
//**********************************
#define PDFU_MemBase                0x9260
XBYTE   xITEPD_FlashUtilityEnable   _at_ PDFU_MemBase + 0x00;
XBYTE   xITEPD_FlashUtilityCmd      _at_ PDFU_MemBase + 0x01;
XBYTE   xITEPD_FlashUtilityCmd2     _at_ PDFU_MemBase + 0x02;
XBYTE   xITEPD_FlashUtilityCmd3     _at_ PDFU_MemBase + 0x03;
XBYTE   xITEPD_FlashUtilityAck      _at_ PDFU_MemBase + 0x04;
XBYTE   xITEPD_FlashUtilitySkipVerifyEn     _at_ PDFU_MemBase + 0x05;
XBYTE   xITEPD_FlashUtilitySMBusSW  _at_ PDFU_MemBase + 0x06;

//**********************************
// PD Port#1 Reg.Service Resources
//**********************************
#define ECPD1_MemBase               0x9270
XBYTE   xPD1_i2c_addr               _at_ ECPD1_MemBase + 0x00;
XBYTE   xPD1_i2c_error              _at_ ECPD1_MemBase + 0x01;
XWORD   xPD1_pd_mVoltage            _at_ ECPD1_MemBase + 0x02;
XWORD   xPD1_pd_mCurrent            _at_ ECPD1_MemBase + 0x04;
XWORD   xPD1_pd_mWatt               _at_ ECPD1_MemBase + 0x06;
XBYTE   xPD1_pd_Voltage             _at_ ECPD1_MemBase + 0x08;
XBYTE   xPD1_pd_Current             _at_ ECPD1_MemBase + 0x09;
XBYTE   xPD1_pd_PowWatt             _at_ ECPD1_MemBase + 0x0A;
XBYTE   xPD1_pd_PowWatt_tmp         _at_ ECPD1_MemBase + 0x0B;
XBYTE   xPD1_int_service            _at_ ECPD1_MemBase + 0x0C;
XBYTE   xPD1_BIN_VERSION[4]         _at_ ECPD1_MemBase + 0x10;
XBYTE   xPD1_FW_VERSION[2]          _at_ ECPD1_MemBase + 0x14;
XBYTE   xPD1_fw_update              _at_ ECPD1_MemBase + 0x16;
XBYTE   xPD1_fw_init                _at_ ECPD1_MemBase + 0x17;

//**********************************
// UCSI Port#2 Reg.Service Resources
//**********************************
#define ECPD2_MemBase             	0x92B0
XBYTE   xPD2_i2c_addr               _at_ ECPD2_MemBase + 0x00;
XBYTE   xPD2_i2c_error              _at_ ECPD2_MemBase + 0x01;
XWORD   xPD2_pd_mVoltage            _at_ ECPD2_MemBase + 0x02;
XWORD   xPD2_pd_mCurrent            _at_ ECPD2_MemBase + 0x04;
XWORD   xPD2_pd_mWatt               _at_ ECPD2_MemBase + 0x06;
XBYTE   xPD2_pd_Voltage             _at_ ECPD2_MemBase + 0x08;
XBYTE   xPD2_pd_Current             _at_ ECPD2_MemBase + 0x09;
XBYTE   xPD2_pd_PowWatt             _at_ ECPD2_MemBase + 0x0A;
XBYTE   xPD2_pd_PowWatt_tmp         _at_ ECPD2_MemBase + 0x0B;
XBYTE   xPD2_int_service            _at_ ECPD2_MemBase + 0x0C;
XBYTE   xPD2_BIN_VERSION[4]         _at_ ECPD2_MemBase + 0x10;
XBYTE   xPD2_FW_VERSION[2]          _at_ ECPD2_MemBase + 0x14;
XBYTE   xPD2_fw_update              _at_ ECPD2_MemBase + 0x16;
XBYTE   xPD2_fw_init                _at_ ECPD2_MemBase + 0x17;
#endif  //UCSI_SUPPORT
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9300 ~ 0x93FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9300                  0x9300
XBYTE   SPI_BUF0[256]               _at_ ECRAM_9300 + 0x00;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9400 ~ 0x94FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9400                  0x9400
XBYTE   I2C_BUF0[128]               _at_ ECRAM_9400 + 0x00;
XBYTE   I2C_BUF1[128]               _at_ ECRAM_9400 + 0x80;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9500 ~ 0x95FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9500                  0x9500
BYTE code *OOB_Table_Pntr           _at_ ECRAM_9500 + 0x00;
XBYTE   xOOB_PacketMaxLength        _at_ ECRAM_9500 + 0x02;
XBYTE   xOOB_PacketLength           _at_ ECRAM_9500 + 0x04;
XBYTE   xOOB_Timeout                _at_ ECRAM_9500 + 0x06;
XBYTE   xOOB_Failed                 _at_ ECRAM_9500 + 0x07;
XBYTE   xOOB_FailedCounter          _at_ ECRAM_9500 + 0x08;
XBYTE   xOOB_DataCounter            _at_ ECRAM_9500 + 0x09;
XBYTE   xOOB_Scan                   _at_ ECRAM_9500 + 0x0A;
XBYTE   xOOB_GetPCH_Temper          _at_ ECRAM_9500 + 0x0B;
XBYTE   xOOB_GetPCH_RTC_Timer       _at_ ECRAM_9500 + 0x0C;
XBYTE   xOOB_GetPCH_Temper_Timer    _at_ ECRAM_9500 + 0x0D;
XBYTE   xOOB_PeciGetCpuT_Timer      _at_ ECRAM_9500 + 0x0E;
XBYTE   xOOB_PCH_Temperature        _at_ ECRAM_9500 + 0x0F;
XBYTE   eSPI_PCH_TMPR[16]           _at_ ECRAM_9500 + 0x10;
XBYTE   eSPI_RTC_DATA[12]           _at_ ECRAM_9500 + 0x20;
XBYTE   xTIME_SYNC                  _at_ ECRAM_9500 + 0x2C;
XBYTE   xTIME_HH                    _at_ ECRAM_9500 + 0x2D;
XBYTE   xTIME_MM                    _at_ ECRAM_9500 + 0x2E;
XBYTE   xTIME_SS                    _at_ ECRAM_9500 + 0x2F;

XBYTE   xOOB_PECI_CPU_T             _at_ ECRAM_9500 + 0x50;
XBYTE   xOOB_PECI_Tj_max            _at_ ECRAM_9500 + 0x51;
XBYTE   xOOB_PECI_Temper[2]         _at_ ECRAM_9500 + 0x52;
XBYTE   xOOB_KEY_CRASHLOG           _at_ ECRAM_9500 + 0x54;
XBYTE   xOOB_PauseTimer             _at_ ECRAM_9500 + 0x55;

XBYTE   xOOB_GET_FLASH_ADR3         _at_ ECRAM_9500 + 0x60;
XBYTE   xOOB_GET_FLASH_ADR2         _at_ ECRAM_9500 + 0x61;
XBYTE   xOOB_GET_FLASH_ADR1         _at_ ECRAM_9500 + 0x62;
XBYTE   xOOB_GET_FLASH_ADR0         _at_ ECRAM_9500 + 0x63;
XBYTE   xOOB_GET_CRASHLOG           _at_ ECRAM_9500 + 0x64;
XBYTE   xOOB_GET_PCH_TMPR           _at_ ECRAM_9500 + 0x65;
XBYTE   xOOB_GET_RTC_DATA           _at_ ECRAM_9500 + 0x66;
XBYTE   xOOB_CrashLogAddrH          _at_ ECRAM_9500 + 0x67;
XBYTE   xOOB_CrashLogAddrM          _at_ ECRAM_9500 + 0x68;
XBYTE   xOOB_Delay                  _at_ ECRAM_9500 + 0x69;
XBYTE   xOOB_CrashCpuIndex          _at_ ECRAM_9500 + 0x6A;
XBYTE   xOOB_CrashCpuIndexH         _at_ ECRAM_9500 + 0x6B;
XBYTE   xOOB_GetCrashLogLock        _at_ ECRAM_9500 + 0x6C;
XBYTE   xOOB_RemindGetCrashLogLED   _at_ ECRAM_9500 + 0x6D;

XWORD   wOOB_CrashCpuDataLines      _at_ ECRAM_9500 + 0x70;
XWORD   wOOB_CrashCpuDataBytes      _at_ ECRAM_9500 + 0x72;
XWORD   wOOB_CrashPchDataSizes      _at_ ECRAM_9500 + 0x74;
XWORD   wOOB_CrashLogDataIndex      _at_ ECRAM_9500 + 0x76;

XBYTE   eSPI_FLASH_DATA[80]         _at_ ECRAM_9500 + 0x80;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9600 ~ 0x96FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9600                  0x9600
//-----------------------------------------------------------------------------
#define PECI_MemBase                0x9600
XBYTE   PECI_FLAG                   _at_ PECI_MemBase + 0x00;
XBYTE   PECI_CMD                    _at_ PECI_MemBase + 0x01;
XBYTE   PECI_CompletionCode         _at_ PECI_MemBase + 0x02;
XBYTE   PECI_TIMER                  _at_ PECI_MemBase + 0x03;
XBYTE   PECI_ERRCNT                 _at_ PECI_MemBase + 0x04;
XBYTE   PECI_ERRSTS                 _at_ PECI_MemBase + 0x05;
XBYTE   PECI_OVTCT                  _at_ PECI_MemBase + 0x06;
XBYTE   PECI_CRC8                   _at_ PECI_MemBase + 0x07;
XBYTE   PECI_CPU_T                  _at_ PECI_MemBase + 0x08;
XBYTE   PECI_CNT                    _at_ PECI_MemBase + 0x09;

XBYTE   PECI_DIR                    _at_ PECI_MemBase + 0x0B;
XWORD   PECI_DELAY                  _at_ PECI_MemBase + 0x0C;
XWORD   PECI_MEMADR                 _at_ PECI_MemBase + 0x0E;
XBYTE   PECI_GetDIB[8]              _at_ PECI_MemBase + 0x10;
XBYTE   PECI_GetTemp[2]             _at_ PECI_MemBase + 0x18;
XBYTE   PECI_RdPkgCfg_Idx16_CC      _at_ PECI_MemBase + 0x1A;
XBYTE   PECI_RdPkgCfg_Idx16[5]      _at_ PECI_MemBase + 0x1B;
XBYTE   PECI_ReadBuffer[16]         _at_ PECI_MemBase + 0x20;
XBYTE   PECI_WriteBuffer[16]        _at_ PECI_MemBase + 0x30;

XBYTE   PECI_PowerLimit1            _at_ PECI_MemBase + 0x40;
XBYTE   PECI_PowerLimit1T           _at_ PECI_MemBase + 0x41;
XBYTE   PECI_PowerLimit2            _at_ PECI_MemBase + 0x42;
XBYTE   PECI_PowerLimit3            _at_ PECI_MemBase + 0x43;
XBYTE   PECI_PowerLimit4            _at_ PECI_MemBase + 0x44;

XBYTE   PECI_PowerUnit              _at_ PECI_MemBase + 0x46;
XBYTE   PECI_EnergyUnit             _at_ PECI_MemBase + 0x47;
XBYTE   PECI_TimeUnit               _at_ PECI_MemBase + 0x48;
XWORD   PECI_UnitPower              _at_ PECI_MemBase + 0x4A;
XWORD   PECI_UnitTime               _at_ PECI_MemBase + 0x4C;
XWORD   PECI_UnitEnergy             _at_ PECI_MemBase + 0x4E;

XBYTE   xOOB_PECI_TEST              _at_ PECI_MemBase + 0x50;
XBYTE   xOOB_PECI_PLx_Index         _at_ PECI_MemBase + 0x51;
XBYTE   xOOB_PECI_PLx_Data0         _at_ PECI_MemBase + 0x52;
XBYTE   xOOB_PECI_PLx_Data1         _at_ PECI_MemBase + 0x53;

#if 0   // SUPPORT_SERVICE_CIR
XBYTE   CIR_KEY_CODE                _at_ ECRAM_9600 + 0x90;
XBYTE   CIR_KEY_CODE2               _at_ ECRAM_9600 + 0x91;
XBYTE   LAST_CIR_KEY_CODE           _at_ ECRAM_9600 + 0x92;
XBYTE   CIR_RX_DIR                  _at_ ECRAM_9600 + 0x93;
XBYTE   CIR_RX_Timer                _at_ ECRAM_9600 + 0x94;
XBYTE   CIR_ResetTimer              _at_ ECRAM_9600 + 0x95;
XBYTE   CIR_KeyBreakTimer           _at_ ECRAM_9600 + 0x96;
XBYTE   CIR_KEY_COUNT               _at_ ECRAM_9600 + 0x97;
XBYTE   CIR_CodeTimer               _at_ ECRAM_9600 + 0x98;
XBYTE   CIR_RX_BUF[32]              _at_ ECRAM_9600 + 0xB0;
XBYTE   CIR_TX_BUF[32]              _at_ ECRAM_9600 + 0xD0;
XBYTE   CIR_RX_KEY[16]              _at_ ECRAM_9600 + 0xF0;
#endif

#if 1   //SUPPORT_WINAPP_ITE_RFDU
#define FREAD_MemBase               0x96F0
XBYTE   xFREAD_Enabled              _at_ FREAD_MemBase + 0x00;
XBYTE   xFREAD_StartNext            _at_ FREAD_MemBase + 0x01;
XBYTE   xFREAD_eFlashAddrH          _at_ FREAD_MemBase + 0x02;
XBYTE   xFREAD_eFlashAddrM          _at_ FREAD_MemBase + 0x03;
XBYTE   xFREAD_eFlashAddrL          _at_ FREAD_MemBase + 0x04;
XBYTE   xFREAD_BufferAddrH          _at_ FREAD_MemBase + 0x05;
XBYTE   xFREAD_BufferAddrL          _at_ FREAD_MemBase + 0x06;
#endif

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x9700 ~ 0x97FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define ECRAM_9700                  0x9700

#define OOBDAT_MemBase              ECRAM_9700//0x9780
XBYTE   eSPI_OOB_DATA[256]              _at_ OOBDAT_MemBase + 0x00;

//-----------------------------------------------------------------------------
#endif  ///* IT5570/IT5571 EXTEDED 2 KB RAM */
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* FUNCTION CALL AREA ********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Clear_Memory_Range
 * @function - Clear Memory Range
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Clear_Memory_Range(WORD nAddr, WORD nSize)
{
    Tmp_XPntr = (unsigned int *)nAddr;
    for (ITempW01 = 0; ITempW01 <= nSize; ITempW01++)
    {
        *Tmp_XPntr = 0;
        Tmp_XPntr++;
    }
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// END
//-----------------------------------------------------------------------------
//OEM_MEMORY_C