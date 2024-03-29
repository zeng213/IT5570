/*-----------------------------------------------------------------------------
 * @file     | OEM_BATTERY.C
 *-----------+-----------------------------------------------------------------
 * @function | Battery and Charger control
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_BATTERY           FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_BATTERY
#define Battery_RamDebug(x)     RamDebug(x)
#else
#define Battery_RamDebug(x)     {}
#endif


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define _AC1_IN_DEBOUNCE        3      //500 X 1 //40 X
#define _ADP_IN_DEBOUNCE        8      //5msX400

#define _BAT_IN_DEBOUNCE        8
//-----------------------------------------------------------------------------
void SetChargingStopReason(BYTE Reason);
void ClearChargingStopReason(BYTE Reason);
BYTE IsAllowCharging(void);
void TryActiveDeadBattery(void);
void StartActiveDeadBattery(void);
void SetFakeBattInfo(BYTE Type);
//-----------------------------------------------------------------------------
//*****************************************************************************
/* Smart Battery Table */
//*****************************************************************************
const sRSmbusStruct code _SMB_BATT1_INIT_TBL[] =
{
    {_SMB_RD_WORD, _CMD_Voltage,                &BAT1_Voltage               },
    {_SMB_RD_WORD, _CMD_RelativeStateOfCharge,  &BAT1_RelativeStateOfChg    },    
    {_SMB_RD_WORD, _CMD_ManufacturerAccess,     &BAT1_ManufacturerAccess    },
    {_SMB_RD_WORD, _CMD_Temperature,            &BAT1_Temperature           },
    {_SMB_RD_WORD, _CMD_BatteryMode,            &BAT1_BatteryMode           },
    {_SMB_RD_WORD, _CMD_Current,                &BAT1_Current               },
    {_SMB_RD_WORD, _CMD_AverageCurrent,         &BAT1_AverageCurrent        },
    {_SMB_RD_WORD, _CMD_MaxError,               &BAT1_MaxError              },
    {_SMB_RD_WORD, _CMD_AbsoluteStateOfCharge,  &BAT1_AbsoluteOfCharge      },
    {_SMB_RD_WORD, _CMD_RemainingCapacity,      &BAT1_RemainingCapacity     },
    {_SMB_RD_WORD, _CMD_FullChargeCapacity,     &BAT1_FullChargeCapacity    },
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &BAT1_ChargingCurrent       },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &BAT1_ChargingVoltage       },
    {_SMB_RD_WORD, _CMD_BatteryStatus,          &BAT1_BatteryStatus         },
    {_SMB_RD_WORD, _CMD_CycleCount,             &BAT1_CycleCount            },
    {_SMB_RD_WORD, _CMD_DesignCapacity,         &BAT1_DesignCapacity        },
    {_SMB_RD_WORD, _CMD_DesignVoltage,          &BAT1_DesignVoltage         },
    {_SMB_RD_WORD, _CMD_SpecificationInfo,      &BAT1_SpecificationInfo     },
    {_SMB_RD_WORD, _CMD_ManufactureDate,        &BAT1_ManufactureDate       },
    {_SMB_RD_WORD, _CMD_SerialNumber,           &BAT1_SerialNumber          },
    {_SMB_RD_BLCK, _CMD_ManufacturerName,       &BAT1_ManufacturerName      },
    {_SMB_RD_BLCK, _CMD_DeviceName,             &BAT1_DeviceName            },
    {_SMB_RD_BLCK, _CMD_DeviceChemistry,        &BAT1_DeviceChemistry       },
    {_SMB_RD_BLCK, _CMD_ManufacturerData,       &BAT1_ManufacturerData      },
};
//-----------------------------------------------------------------------------
const sRSmbusStruct code _SMB_BATT1_POLL_TBL[] =
{
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &BAT1_ChargingCurrent       },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &BAT1_ChargingVoltage       },
    {_SMB_RD_WORD, _CMD_Temperature,            &BAT1_Temperature           },
    {_SMB_RD_WORD, _CMD_Voltage,                &BAT1_Voltage               },
    {_SMB_RD_WORD, _CMD_Current,                &BAT1_Current               },
    {_SMB_RD_WORD, _CMD_AverageCurrent,         &BAT1_AverageCurrent        },
    {_SMB_RD_WORD, _CMD_RelativeStateOfCharge,  &BAT1_RelativeStateOfChg    },
    {_SMB_RD_WORD, _CMD_RemainingCapacity,      &BAT1_RemainingCapacity     },
    {_SMB_RD_WORD, _CMD_FullChargeCapacity,     &BAT1_FullChargeCapacity    },
    {_SMB_RD_WORD, _CMD_BatteryStatus,          &BAT1_BatteryStatus         },
};
//-----------------------------------------------------------------------------
//*****************************************************************************
/* Smart Charger Table */
//*****************************************************************************
const sRSmbusStruct code _SMB_CHGRA_INIT_TBL[] =
{
    {_SMB_RD_WORD, _CMD_ChargerManufacturerID,  &CHGR_ManufacturerID        },
    {_SMB_RD_WORD, _CMD_ChargerDeviceID,        &CHGR_DeviceID              },
    {_SMB_WR_WORD, _CMD_ChargerOption,          &CHGR_ChargerOption         },
    {_SMB_WR_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltage       },
    {_SMB_WR_WORD, _CMD_MinSystemVoltage,       &CHGR_ChargerREG3E          },
    {_SMB_WR_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrent          },
    {_SMB_WR_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrent       },
    {_SMB_RD_WORD, _CMD_ChargerManufacturerID,  &CHGR_ManufacturerID        },
    {_SMB_RD_WORD, _CMD_ChargerDeviceID,        &CHGR_DeviceID              },
};
//-----------------------------------------------------------------------------
const sRSmbusStruct code _SMB_CHGRA_POLL_TBL[] =
{
    {_SMB_WR_WORD, _CMD_ChargerOption,          &CHGR_ChargerOption         },
    {_SMB_WR_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltage       },
    {_SMB_WR_WORD, _CMD_MinSystemVoltage,       &CHGR_ChargerREG3E          },
    {_SMB_WR_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrent          },
    {_SMB_WR_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrent       },
#if 1   /* SUPPORT READ BACK CHECK */
    {_SMB_RD_WORD, _CMD_ChargerOption,          &CHGR_ChargerOptionR        },
    {_SMB_RD_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrentR         },
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrentR      },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltageR      },
#endif
};
//*****************************************************************************
#define _SIZE_SMB_BATT1_INIT        (sizeof(_SMB_BATT1_INIT_TBL) / 4)
#define _SIZE_SMB_BATT1_POLL        (sizeof(_SMB_BATT1_POLL_TBL) / 4)
#define _SIZE_SMB_CHGRA_INIT        (sizeof(_SMB_CHGRA_INIT_TBL) / 4)
#define _SIZE_SMB_CHGRA_POLL        (sizeof(_SMB_CHGRA_POLL_TBL) / 4)
//*****************************************************************************

//*****************************************************************************
// CODE START
//*****************************************************************************
#if SUPPORT_SMART_BATTERY
/*-----------------------------------------------------------------------------
 * @subroutine - PollSmartBattery
 * @function - Process SMBus Smart Battery Data
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - None
 * @return   - None
 * @note     - GPC.4_SMCLK2, GPB.5_SMDAT2
 */
void PollSmartBattery(void)
{
#if 0   //SUPPORT_BATT_FAKE_INFO
    if ((BAT1_RemainingCapacity == 0) || (BAT1_FullChargeCapacity == 0))
    {
        BAT1_Temperature = 2730 + 333;
        BAT1_Voltage = 8123;
        BAT1_Current = 1000;
        BAT1_AverageCurrent = 1000;
        BAT1_RelativeStateOfChgL = 66;
        BAT1_RemainingCapacity = 2000;
        BAT1_FullChargeCapacity  = 3000;
        BAT1_ChargingCurrent = 1500;
        BAT1_ChargingVoltage = 8700;
        BAT1_CycleCount = 99;
        BAT1_DesignCapacity = 3200;
        BAT1_DesignVoltage = 8400;
    }
    SMBA_DEV0_DLY = 500;    //5ms x 500 = 2.5 sec (per loop)
#endif 
#ifdef _SUPPORT_BATT_FAKE_INFO_
    SetFakeBattInfo(0);
#else
    if (!(SMBB_DEV0_STS & F_DEV_INIT))
    {
        /* Initial read all battery information. */
        if (SMBB_DEV0_DIR >= _SIZE_SMB_BATT1_INIT)
        {
            if ((BAT1_DesignVoltage == 0) || (BAT1_DeviceChemistry == 0) ||
                    (BAT1_FullChargeCapacity == 0))
            {
                SMBB_DEV0_STS &= F_DEV_ON_LINE;
                SMBB_DEV0_DIR = 0;
            }
            else
            {
                SMBB_DEV0_DIR = 0;
                SMBB_DEV0_STS |= F_DEV_INIT;
                PowerSource |= F_BAT1_PRESENT;
                //Hook_SmartBatteryInitOK();
                /* Delay 1 sec to Charger setting */
                SMBB_DEV1_DLY = 500;   //2ms x 500 = 1 sec
            }
            return;
        }
        SMBB_CHN_CTL = _SMB_BATT1_INIT_TBL[SMBB_DEV0_DIR].address;
        SMBB_CHN_CMD = _SMB_BATT1_INIT_TBL[SMBB_DEV0_DIR].cmd;
        SMBB_DEV_MEM = _SMB_BATT1_INIT_TBL[SMBB_DEV0_DIR].smbdata;
    }
    else
    {
        /* Update SMBus device dynamic data. */
        if (SMBB_DEV0_DIR >= _SIZE_SMB_BATT1_POLL)
        {
            SMBB_DEV0_DIR = 0;
            SMBB_DEV0_STS |= F_DEV_UPDATED;
            SMBB_DEV0_DLY = 2500;    //2ms x 2500 = 5 sec (per loop)
            /* TODO: Here check data one loop */
            // :
        }
        SMBB_CHN_CTL = _SMB_BATT1_POLL_TBL[SMBB_DEV0_DIR].address;
        SMBB_CHN_CMD = _SMB_BATT1_POLL_TBL[SMBB_DEV0_DIR].cmd;
        SMBB_DEV_MEM = _SMB_BATT1_POLL_TBL[SMBB_DEV0_DIR].smbdata;
    }
    SMBB_DEV0_DIR++;
    SMBB_SetToRegs(_SMB_BATT1_ADDR, _SMB_DEV0);
#endif
}
#endif

#if SUPPORT_SMART_CHARGER
/*-----------------------------------------------------------------------------
 * @subroutine - Battery_Protection
 * @function - Battery_Protection
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *              * * * * * * Alarm Bits * * * * *
 *              0x8000 OVER_CHARGED_ALARM
 *              0x4000 TERMINATE_CHARGE_ALARM
 *              0x2000 Reserved
 *              0x1000 OVER_TEMP_ALARM
 *              0x0800 TERMINATE_DISCHARGE_ALARM
 *              0x0400 Reserved
 *              0x0200 REMAINING_CAPACITY_ALARM
 *              0x0100 REMAINING_TIME_ALARM
 *              * * * * * * Status Bits * * * * *
 *              0x0080 INITIALIZED
 *              0x0040 DISCHARGING
 *              0x0020 FULLY_CHARGED
 *              0x0010 FULLY_DISCHARGED
 *              * * * * * * Error Code * * * * *
 *              0x0000-0x000f Reserved for error codes
 */
void Battery_Protection(void)
{
#if 0
    /* Check battery drops to under 95%  */
    if (BAT1_CheckRecharge > 0)
    {
        if (BAT1_RelativeStateOfChgL < 95)
        {
            BAT1_CheckRecharge = 0;
            BAT1_BatteryStatus2 = 0;
        }
        else
        {
            CHGR_ChargingCurrent = 0;
            return;
        }
    }
#endif

#if  SUPPORT_BATTERY_FASTCHARGE
    if( IS_MASK_SET(xEC_FeatureStatus, F_FASTCHARGE_EN_STA))
    {
        ITempB05 = BAT1_CelsiusDegree;
        if ((ITempB05 == 0) || (ITempB05 > 45))
        {
            CHGR_ChargingCurrent = 0;       /* Stop Charging */
            return;
        }
        if (BAT1_Voltage <= PRECHARGE_BATTERY_VOLTAGE)
        {
            // Precharge
            CHGR_ChargingVoltage = 0x2328;  //9V
            CHGR_ChargingCurrent = 0x0080;  //0.15A
        }
        
        if ((ITempB05 < 10) || (BAT1_Current < BAT1_005FCC))
        {
            CHGR_ChargingVoltage = 0x3390;      // 13.2V
            CHGR_ChargingCurrent = BAT1_02FCC;  // FCC * 0.2
        }
    }
    else
    {
        /*
            Battery pack temperature is  0~15'C, charge current is 0.9A
            Battery pack temperature is 15~45'C, charge current is 2.3A
            Battery pack temperature is 45~XX'C, charge current is 0A
        */
        ITempB05 = BAT1_CelsiusDegree;
        if (ITempB05 < 15)
        {
            CHGR_ChargingCurrent = 900;    /* Charging Current=512+256+128+64mA */
        }
        else if (ITempB05 > 45)
        {
            CHGR_ChargingCurrent = 0x0000;    /* Stop Charging */
            return;
        }
    }
#else
    /*
        Battery pack temperature is  0~15'C, charge current is 0.9A
        Battery pack temperature is 15~45'C, charge current is 2.3A
        Battery pack temperature is 45~XX'C, charge current is 0A
    */
    ITempB05 = BAT1_CelsiusDegree;
    if (ITempB05 < 15)
    {
        CHGR_ChargingCurrent = 900;    /* Charging Current=512+256+128+64mA */
    }
    else if (ITempB05 > 45)
    {
        CHGR_ChargingCurrent = 0x0000;    /* Stop Charging */
        return;
    }
#endif
    /* Normal Battery Charge Protection (Suggestion) */
    BAT1_BatteryStatus2 = (BAT1_BatteryStatus & 0xD020);
    if (BAT1_BatteryStatus2 > 0)
    {
        if ((BAT1_BatteryStatus2 & 0xD000) > 0)
        {
            CHGR_ChargingCurrent = 0;
            return;
        }
        else if (BAT1_BatteryStatus & 0x0020)
        {
            /* 0x0020 FULLY_CHARGED */
            BAT1_CheckRecharge = 0xB1;
            CHGR_ChargingCurrent = 0;
            return;
        }
        else if (BAT1_RelativeStateOfChgL > 94)
        {
            CHGR_ChargingCurrent = 0;
            return;
        }
        else
        {
            BAT1_BatteryStatus2 = 0;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - SetCharger_FastCharging
 * @function - Process SMBus Smart Charger Setting
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Mome
 */
void SetCharger_FastCharging(void)
{
    if( ((xEC_Sensor_1_T + xEC_Sensor_2_T)/2) > 60)
    {
        CHGR_ChargingVoltage = 0x3390;  //13.2V
        CHGR_ChargingCurrent = BAT1_05FCC;  // FCC * 0.5
        CHGR_StepChangeCnt = 0;
        CHGR_FastChargeStep = 0xFF;
        return;
    }
    if( CHGR_FastChargeStep == 0xFF)
    {
        if (((xEC_Sensor_1_T + xEC_Sensor_2_T)/2) < 50)
        {
            CHGR_FastChargeStep = 0;    //go back to fast charging
            CHGR_StepChangeCnt = 0;

            return;
        }

        return;
    }

    /*  Charge Voltage & Current Setting */
    if (CHGR_FastChargeStep == 0)
    {
        CHGR_FastChargeStep = 1;
        return;
    }
    if (CHGR_FastChargeStep == 1)
    {
        CHGR_ChargingVoltage = 0x3260;  //12.9V
        CHGR_ChargingCurrent = BAT1_FullChargeCapacity;  // FCC * 0.8 // BAT1_FullChargeCapacity;  // FCC * 1
        if ((BAT1_Current < 0x8000) && (BAT1_Current > BAT1_08FCC))  // FCC * 0.8
        {
            CHGR_StepChangeCnt = 0;
            return;
        }
       if (CHGR_StepChangeCnt > 5)
        {
            CHGR_StepChangeCnt = 0;
            CHGR_FastChargeStep = 2;
        }
        return;
    }
    if (CHGR_FastChargeStep == 2)
    {
        CHGR_ChargingVoltage = 0x3390;  //13.2V
        CHGR_ChargingCurrent = BAT1_08FCC;  // FCC * 0.8
        if ((BAT1_Current < 0x8000) && (BAT1_Current > BAT1_02FCC))  // FCC * 0.2
        {
            CHGR_StepChangeCnt = 0;
            return;
        }
       if (CHGR_StepChangeCnt > 5)
        {
            CHGR_StepChangeCnt = 0;
            CHGR_FastChargeStep = 3;
        }
        return;
    }
    /* CHGR_FastChargeStep = 3 */
    CHGR_ChargingVoltage = 0x3390;  //13.2V
    CHGR_ChargingCurrent = BAT1_02FCC;  // FCC * 0.2
    CHGR_StepChangeCnt = 0;
    
    if ((BAT1_Current < 0x8000) && (BAT1_Current < BAT1_0025FCC))  // FCC * 0.025
    {
        CHGR_ChargingCurrent = 0;
    }
}


/*-----------------------------------------------------------------------------
 * @subroutine - Battery_GetChargingCurrent
 * @function - Process SMBus Smart Charger Enable
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Mome
 */
void SetCharger_NormalCharging(void)
{
    CHGR_ChargingVoltage = 0x3390;  //13.2V
    CHGR_ChargingCurrent = 0x0800;  //2.05A
}

/*-----------------------------------------------------------------------------
 * @subroutine - SetCharger_StopCharging
 * @function - Process SMBus Smart Charger Setting
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Mome
 */
void SetCharger_StopCharging(void)
{
    CHGR_ChargingVoltage = 0x3390;  //13.2V
    CHGR_ChargingCurrent = 0x0000;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Battery_GetChargingCurrent
 * @function - Process SMBus Smart Charger Enable
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Mome
 */
/*
BD99950MUV Charge Options Register (0x12H) default: 0xF302
BIT  BIT NAME   DESCRIPTION
[15] ACOK Deglitch Time Setting
        0: ACOK rising edge deglitch time 150ms
        1: ACOK rising edge deglitch time 1.3s <default at POR>
[14:13] Watchdog Timer Setting
        00: Disable Watchdog Timer
        01: Enabled, 44 sec
        10: Enabled, 88 sec
        11: Enable Watchdog Timer (175s) <default at POR>
[12] SLLM mode
        0: Fixed Frequency Switching
        1: Variable Frequency Switching(SLLM mode)<default at POR>
[11] BGATE Charge Pump Enable
        0: BGATE Charge Pump ON <default at POR>
        1: BGATE Charge Pump OFF(from HOST when battery is removed)
[10:9] Switching Frequency setting
        00: 600kHz
        01: 800kHz <default at POR>
        10: 1MHz
        11: 1.2MHz
[8] High Side FET OCP Comparator Threshold Setting
        0: function is disabled
        1: 450mV <default at POR>
[7] Low Side FET OCP Comparator Threshold Setting
        0: 135mV <default at POR>
        1: 230mV
[6] LEARN Enable
        0: Disable LEARN Cycle <default at POR>
        1: Enable LEARN Cycle
[5] IOUT Selection
        0: IOUT is the 20x Adapter Current Amplifier Output <default at POR>
        1: IOUT is the 20x Charge Current Amplifier Output
[4] ACOK Indication (Read Only) Adapter Detection Indicator
        0: AC adapter is not present (ACDET < 2.4V) <default at POR>
        1: AC adapter is present (ACDET > 2.4V)
[3] Charge Over Current Protection
        0: Charge Current DAC Reset and Charger Restart <default at POR>
        1: Charge Current DAC Reset
[2] Trickle Charge Indication (Read Only) Trickle Charge Indicator
        0: Charge in Switching Mode <default at POR>
        1: In Trickle Charge mode(Linear charge mode )
[1] ACOC Enable
        0: ACOC Disable
        1: 3.33x of Adapter Current Setting <default at POR>
[0] Shut down
        0: Enable NVDC Charger Control <default at POR>
        1: Shut Down
 */
void Battery_GetChargingCurrent(void)
{
// move to ADP_Control()
//     /* Input Current Setting */
// #if  SUPPORT_BATTERY_FASTCHARGE
//     CHGR_InputCurrent = 0x0DC0;	// 3.5A
// #else
//     CHGR_InputCurrent = 0x0C80;
// #endif
    /* Minimum System Voltage Setting */
    CHGR_ChargerREG3E = 0x1800;
    
    /* Charge Option  */
    if (IS_ADP_PRESENT_LO() || IS_BATTERY1_OUT())
    {
        CHGR_ChargerOption = 0xF102;    //Charger OFF: Bit0: 1
        CHGR_ChargingCurrent = 0x0000;
        CHGR_ChargingVoltage = 0x3390;  //13.2V
        CHGR_FastChargeStep = 0;
        CHGR_StepChangeCnt = 0;
        return;
    }
    else
    {
        CHGR_ChargerOption = 0xF102;        //Charger ON: Bit0: 0
    }
    CHGR_ChargingVoltage = 0x3390;  //13.2V
    CHGR_ChargingCurrent = 0x7C0;  //2A
#if INTEL_SMARTCHARGING_PHASE1
    if (Charging_CheckTimeRange())
    {
        if (BAT1_RelativeStateOfChgL < 80)
        {
            SetCharger_NormalCharging();
        }
        else
        {
            SetCharger_StopCharging();
        }
        return;
    }
    if (SysPowState == _SYSTEM_S0)
    {
        SetCharger_NormalCharging();
        return;
    }
#endif
#if  SUPPORT_BATTERY_FASTCHARGE
    if( IS_MASK_SET(xEC_FeatureStatus, F_FASTCHARGE_EN_STA))
    {
        if((xPD1_pd_PowWatt >= 65) || (xPD2_pd_PowWatt >= 65))
        {
            SetCharger_FastCharging();
        }
        else
        {
            SetCharger_NormalCharging();
        }
    }
#endif
#if 0   /* 1: Protect Check non-spec 2S Battery */
    if (BAT1_DesignVoltage > 8000)
    {
        return;
    }
    if (BAT1_DesignVoltage <= 7400)
    {
        CHGR_ChargingVoltage = 8400;
    }
    else if (BAT1_DesignVoltage <= 7600)
    {
        CHGR_ChargingVoltage = 8700;
    }
    else
    {
        CHGR_ChargingVoltage = 8800;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - PollSmartCharger
 * @function - Process SMBus Smart Charger Data
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - None
 * @return   - None
 * @note     - GPB.4_SMCLK2, GPB.5_SMDAT2
 *
 */
void PollSmartCharger(void)
{
    Battery_GetChargingCurrent();
    if (IS_BATTERY1_IN())
    {
        if (IS_MASK_SET(SMBB_DEV0_STS, F_DEV_EARLY_INIT))
        {
            if (BAT1_Voltage >= DEAD_BATTERY_VOLTAGE)
            {
                Battery_Protection();
            }
            else if (IsAllowCharging())
            {
                StartActiveDeadBattery();
            }
    
                ClearChargingStopReason(CHARGING_STOP_NO_BATTERY);
        }
        else
        {
            SetChargingStopReason(CHARGING_STOP_NO_BATTERY);            
        }
    }
    else
    {
        SetChargingStopReason(CHARGING_STOP_NO_BATTERY);   
    }
    
    //--------------------------------------------------
    if (!(SMBB_DEV1_STS & F_DEV_INIT))
    {
        CHGR_ChargingCurrent = 0x0000;  //[REG3F]
        /* Initial read all battery information. */
        if (SMBB_DEV1_DIR >= _SIZE_SMB_CHGRA_INIT)
        {
            SMBB_DEV1_DIR = 0;
            SMBB_DEV1_STS |= (F_DEV_INIT + F_DEV_READY);
            /* TODO: Here Check Data Failed Retry */
            // :
            if (CHGR_DeviceID == 0)
            {
                SMBB_DEV1_STS = 0;
                return;
            }
        }
        SMBB_CHN_CTL = _SMB_CHGRA_INIT_TBL[SMBB_DEV1_DIR].address;
        SMBB_CHN_CMD = _SMB_CHGRA_INIT_TBL[SMBB_DEV1_DIR].cmd;
        SMBB_DEV_MEM = _SMB_CHGRA_INIT_TBL[SMBB_DEV1_DIR].smbdata;
    }
    else
    {
        /* Update SMBus device dynamic data. */
        if (SMBB_DEV1_DIR >= _SIZE_SMB_CHGRA_POLL)
        {
            if (CHGR_StepChangeCnt < 255)
            {
                CHGR_StepChangeCnt++;
            }
            SMBB_DEV1_DIR = 0;
            SMBB_DEV1_STS |= F_DEV_UPDATED;
            /* Polling Speed */
            SMBB_DEV1_DLY = 7500;   //2ms x 7500 = 15 sec (per loop)
            /* TODO: Here check data one loop */
            // :
        }
        else
        {
            SMBB_DEV1_DLY = 2;
        }

        SMBB_CHN_CTL = _SMB_CHGRA_POLL_TBL[SMBB_DEV1_DIR].address;
        SMBB_CHN_CMD = _SMB_CHGRA_POLL_TBL[SMBB_DEV1_DIR].cmd;
        SMBB_DEV_MEM = _SMB_CHGRA_POLL_TBL[SMBB_DEV1_DIR].smbdata;
    }
    SMBB_DEV1_DIR++;
    SMBB_SetToRegs(_SMB_CHGRA_ADDR, _SMB_DEV1);
}
#endif  //SUPPORT_SMART_CHARGER

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SmartCharger
 * @function - Process SMBus Smart Charger init
 * @upstream - By Call
 * @input    - None
 * @return   - None
 * @note     - GPB.4_SMCLK2, GPB.5_SMDAT2
 *
 */
void Init_SmartCharger(void)
{
#if SUPPORT_SMART_CHARGER
    CHGR_InputCurrent = 0x0800; // 2A
    /* Minimum System Voltage Setting */
    CHGR_ChargerREG3E = 0x1800;
    /* Charge Option  */
    CHGR_ChargerOption = 0xF102;    //Charger OFF: Bit0: 1
    CHGR_ChargingVoltage = 0x3390;  //13.2V
    CHGR_ChargingCurrent = 0x0000;

    SPI_BUF0[1] = 0xF1;
    SPI_BUF0[0] = 0x02;
    bRWSMBus(_SMB_CH1, SMbusWW, _SMB_CHGRA_ADDR,
             _CMD_ChargerOption, &SPI_BUF0[0], 0);
    SPI_BUF0[1] = 0x18;
    SPI_BUF0[0] = 0x00;
    bRWSMBus(_SMB_CH1, SMbusWW, _SMB_CHGRA_ADDR,
             _CMD_ChargerREG3E, &SPI_BUF0[0], 0);
#endif

#if INTEL_SMARTCHARGING_PHASE1
    ChargerLimitHourStart = 22;
    ChargerLimitHourEnd = 5;
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Charger_Hook1SecTimer
 * @function - Charger_Hook1SecTimer
 * @Upstream - Hook_Timer1SecEventC
 * @input    -
 * @return   - None
 * @note     - None
 */
void Charger_Hook1SecTimer(void)
{
    TryActiveDeadBattery();
    
    if (WakeUpChargeTimer > 0)
    {
        WakeUpChargeTimer--;
    }
    
    //-------------------------------------------------------------------------
    if ((IS_ADAPTER_IN()) && (IS_BATTERY1_IN()))
    {
        if ((BAT1_Current == 0) &&
            (BAT1_RelativeStateOfChgL < 100) &&
            (BAT1_Voltage < LOW_BATTERY_VOLTAGE))
        {
            WakeUpChargeTimer = 30;
            BAT1_Dead_Counter++;
            if (BAT1_Dead_Counter > 1800)   //30min set dead battery.
            {
                SET_MASK(PowerSource, F_BAT1_CRITICAL);
            }
        }
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Adapter_Detection
 * @function - AC-Adapter plug-in Detection
 * @Upstream - Hook_Timer50msEventA
 * @input    - GPI
 * @return   - None
 * @note     - None
 */
void Adapter_Detection(void)
{
    if (IS_ADAPTER_IN())
    {
        if (Debounce_ACin < _AC1_IN_DEBOUNCE)
        {
            Debounce_ACin++;
        }
        else
        {
            if (IS_MASK_CLEAR(PowerSource, F_AC_ON_LINE))
            {
                AC_PRESENT_HI();
                SET_MASK(PowerSource, F_AC_ON_LINE);
                /* Adapter Plug-In Initialize */
                WakeUpChargeTimer = 6;
                /* Clear Battery Status Lock */
                BAT1_BatteryStatus = 0;
                BAT1_BatteryStatus2 = 0;
                //xEC_PowerState = PowerSource;
                //BAT1_CheckRecharge = 0;
                //SendACiEventTimer = 20;
                SMBB_DEV1_DLY = 0;
                /* TODO: */
                //SET_MASK(xEC_USB_TypeCFlag, Flag_inputcurrent);
#if 1   /* Intel request Battery < 95 enabled charging */
                if (BAT1_RelativeStateOfChgL > 94)
                {
                    BAT1_CheckRecharge = 0xA1;
                }
#endif
                Update_ACPI_BST1();
            }
        }
    }
    else
    {
        if (IS_MASK_SET(PowerSource, F_AC_ON_LINE))
        {
            AC_PRESENT_LO();
            CLEAR_MASK(PowerSource, F_AC_ON_LINE);
            /* Adapter Removed Initialize */
            //xEC_PowerState = PowerSource;
            //SendACiEventTimer = 20;
            WriteSCI_Buffer(_SCIEVT_ADAPTER);
            /* TODO: */
            /* Delay 4 sec to Charger setting */
            SMBB_DEV1_DLY = 0;            
        }
        BAT1_Dead_Counter = 0;
        Debounce_ACin = 0;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Battery_Detection
 * @function - Battery#1 plug-in Detection
 * @Upstream - Hook_Timer50msEventB
 * @input    - GPI
 * @return   - None
 * @note     - None
 */
void Battery_Detection(void)
{
#if SUPPORT_BATTERY_IN
    if (IS_BATTERY1_IN())
    {
        if (Debounce_Bt1In < _BAT_IN_DEBOUNCE)
        {
            Debounce_Bt1In++;
        }
        else
        {
#if SUPPORT_BATTERY_SMBA
            if (IS_MASK_CLEAR(SMBA_DEV0_STS, F_DEV_ON_LINE))
            {
                // Smart Battery connected to SMBus-A
                SET_MASK(SMBA_DEV0_STS, F_DEV_ON_LINE);
                //wPowerSavingDelay = 1000;
            }
#else
            if (IS_MASK_CLEAR(SMBB_DEV0_STS, F_DEV_ON_LINE))
            {
                // Smart Battery connected to SMBus-B
                SET_MASK(SMBB_DEV0_STS, F_DEV_ON_LINE);
                //wPowerSavingDelay = 1000;
            }
#endif
            if (IS_MASK_CLEAR(PowerSource, F_BAT1_PRESENT))
            {
#if SUPPORT_BATTERY_SMBA
                // Smart Battery connected to SMBus-A
                if ((IS_MASK_SET(SMBA_DEV0_STS, F_DEV_INIT)) &&
                        (IS_MASK_SET(SMBA_DEV0_STS, F_DEV_UPDATED)))
                {
                    SET_MASK(PowerSource, F_BAT1_PRESENT);
                }
#else
                // Smart Battery connected to SMBus-B
                if ((IS_MASK_SET(SMBB_DEV0_STS, F_DEV_INIT)) &&
                        (IS_MASK_SET(SMBB_DEV0_STS, F_DEV_UPDATED)))
                {
                    SET_MASK(PowerSource, F_BAT1_PRESENT);
                }
#endif
            }
        }
    }
    else
    {
#if SUPPORT_BATTERY_SMBA
        // Smart Battery connected to SMBus-A
        if (SMBA_DEV0_STS != 0)
        {
            Clear_Memory_Range(BAT1_MemBase, 0x6F);
            SMBA_DEV0_STS = 0;
        }
#else
        // Smart Battery connected to SMBus-B
        if (SMBB_DEV0_STS != 0)
        {
            Clear_Memory_Range(BAT1_MemBase, 0x6F);
            SMBB_DEV0_STS = 0;
        }
#endif
        CLEAR_MASK(PowerSource, F_BAT1_PRESENT);
        BAT1_Dead_Counter = 0;
        Debounce_Bt1In = 0;
    }
#else
    //-------------------------------------------------------------------------
    // No Battery ID Detected pin,
    // we used try SMBus error or successful for battery present
    if (wBatteryDetectTmr > 0)
    {
        wBatteryDetectTmr--;
        return;
    }
    //-----------------------------------------------------
    if (BatteryDetectStep == 0)
    {
        /* Force Battery On-Line */
        GPCRC1 = ALT;
        GPCRC2 = ALT;
        SMBB_DEV0_STS = F_DEV_ON_LINE;
        SMBB_ERR_STS[0] = 0;
        SMBB_DEV1_DLY = 1;
        SMBB_DEV0_DIR = 0;
        WakeUpChargeTimer = 6;
        Clear_Memory_Range(BAT1_MemBase, 0x6F);
        BatteryDetectStep = 1;
        wBatteryDetectTmr = 60;        //60x50ms = 3sec
        return;
    }
    //-----------------------------------------------------
    if (BatteryDetectStep == 1)
    {
        if (SMBB_ERR_STS[0] == 0)
        {
            BatteryDetectStep = 3;
            BatteryDetectRetry = 0;
        }
        else
        {
            BatteryDetectStep = 2;
            wBatteryDetectTmr = 100;    //100x50ms = 5sec
            SMBB_DEV0_STS = 0;
        }
        return;
    }
    //-----------------------------------------------------
    if (BatteryDetectStep == 2)
    {
        BatteryDetectStep = 0;
        BatteryDetectRetry++;
        return;
    }
    //-----------------------------------------------------
    if (BatteryDetectStep == 3)
    {
        if (SMBB_ERR_STS[0] > 32)
        {
            BatteryDetectStep = 0;
            wBatteryDetectTmr = 80 * (BatteryDetectRetry + 1); // 8sec
            SMBB_ERR_STS[0] = 0;
            Clear_Memory_Range(BAT1_MemBase, 0x6F);
            SMBB_DEV0_STS = 0;
            CLEAR_MASK(PowerSource, F_BAT1_PRESENT);
            GPCRC1 = INPUT;
            GPCRC2 = INPUT;
            BATT_DET_OUT_HI();
        }
        else
        {
            SET_MASK(PowerSource, F_BAT1_PRESENT);
            BATT_DET_OUT_LO();
            GPCRC1 = ALT;
            GPCRC2 = ALT;
        }
        return;
    }
#endif
}

void SetChargingStopReason(BYTE Reason)
{
    SET_MASK(xEC_StopChargingReason, Reason);
}

void ClearChargingStopReason(BYTE Reason)
{
    CLEAR_MASK(xEC_StopChargingReason, Reason);
}

BYTE IsAllowCharging(void)
{
    return CHARGING_STOP_NO_ERROR == xEC_StopChargingReason;
}

void TryActiveDeadBattery(void)
{
    if (DeadBatteryActiveTimer > 1)
    {

        --DeadBatteryActiveTimer;
        if (1 == DeadBatteryActiveTimer)
        {
            if (BAT1_Voltage <= DEAD_BATTERY_VOLTAGE)
            {
                SetChargingStopReason(CHARGING_STOP_DEAD_BAT);
            }
            else
            {
                ClearChargingStopReason(CHARGING_STOP_DEAD_BAT);
            }
        }
    }
}

void StartActiveDeadBattery(void)
{
    if (0 == DeadBatteryActiveTimer)
    {
        DeadBatteryActiveTimer = 10;
    }
}


void StopActiveDeadBattery(void)
{
    DeadBatteryActiveTimer = 1;
}

void RestoreActiveDeadBatteryState(void)
{
    DeadBatteryActiveTimer = 0;
}

void CheckForceShutdownByBatteryVoltage(void)
{
    /*
        Addtional protection for low current discharging in S3/S0IX,
        to avoid battery drop into "protect mode" which will output 0V, 
        this wll lost all saved settings of BIOS setup !
    */
    //when only battery exist!
    
    if (IS_ADP_PRESENT_LO() && IS_BATTERY1_IN())
    {
        if( BAT1_SafeVoltageValue != 0)
        {
            if ((0x0 == BAT1_RelativeStateOfChgL && 0x0 == BAT1_RelativeStateOfChg) 
                || BAT1_Voltage <= BAT1_SafeVoltageValue)
            {
                xLowBattShutdownCnt++;
                if( xLowBattShutdownCnt > 6)
                {
                    xLowBattShutdownCnt = 0;
                    Oem_TriggerPowerOff(_ST_FORCE_SHUTDOWN);
                }
            }
        }
    }

}

void SetFakeBattInfo(BYTE Type)
{
    if ((BAT1_RemainingCapacity == 0) || (BAT1_FullChargeCapacity == 0))
    {
        BAT1_Temperature = 2730 + 333;
        BAT1_Voltage = 9123;
        BAT1_Current = 1000;
        BAT1_AverageCurrent = 1000;
        BAT1_RelativeStateOfChgL = 66;
        BAT1_RemainingCapacity = 2000;
        BAT1_FullChargeCapacity  = 3000;
        BAT1_ChargingCurrent = 1500;
        BAT1_ChargingVoltage = 8700;
        BAT1_CycleCount = 99;
        BAT1_DesignCapacity = 3200;
        BAT1_DesignVoltage = 8400;

        
    }
    PowerSource |= F_BAT1_PRESENT;
        SMBB_DEV0_DIR = 0;
        SMBB_DEV0_STS |= F_DEV_INIT;
        SMBB_DEV0_STS |= F_DEV_ON_LINE;

    SMBA_DEV0_DLY = 500;    //5ms x 500 = 2.5 sec (per loop)

}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_BIF1
 * @function - Update ACPI Control Method Battery Information
 * @Upstream - Update_ACPI_Battery,SCI_PowerEvent
 * @input    - Real Battery Data
 * @return   - None
 * @note     - None
 */
void Update_ACPI_BIF1(void)
{
#if SUPPORT_ACPI_BATT_MWH
    ITempW01 = (WORD)(BAT1_FullChargeCapacity / 10);
    ITempW01 *= (WORD)(BAT1_DesignVoltage / 100);
    ITempW01 /= 10;     /* Unit is 10mW */
    xEC_Bt1FullChrgCapacityL = ITempW01;
    xEC_Bt1FullChrgCapacityH = ITempW01 >> 8;
    ITempW01 = (WORD)(BAT1_DesignCapacity / 10);
    ITempW01 *= (WORD)(BAT1_DesignVoltage / 100);
    ITempW01 /= 10;     /* Unit is 10mW */
    xEC_Bt1DesignCapacityL = ITempW01;
    xEC_Bt1DesignCapacityH = ITempW01 >> 8;
#else
    xEC_Bt1FullChrgCapacityL = BAT1_FullChargeCapacity;
    xEC_Bt1FullChrgCapacityH = BAT1_FullChargeCapacity >> 8;
    xEC_Bt1DesignCapacityL = BAT1_DesignCapacity;
    xEC_Bt1DesignCapacityH = BAT1_DesignCapacity >> 8;
#endif
    xEC_Bt1DesignVoltageL = BAT1_DesignVoltage;
    xEC_Bt1DesignVoltageH = BAT1_DesignVoltage >> 8;
    xEC_Bt1SerialNumberL = BAT1_SerialNumber;
    xEC_Bt1SerialNumberH = BAT1_SerialNumber >> 8;
    xEC_Bt1TripPointL = 0x00;
    xEC_Bt1TripPointH = 0x00;
    xEC_Bt1ModelCode = 0x01;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_BST
 * @function - Update ACPI Control Method Battery Status
 * @Upstream - Update_ACPI_Battery,SCI_PowerEvent
 * @input    - PowerSource
 * @return   - None
 * @note     - None
 */
void Update_ACPI_BST1(void)
{
#if SUPPORT_ACPI_BATT_MWH
    ITempW01 = (WORD)(BAT1_RemainingCapacity / 10);
    ITempW01 *= (WORD)(BAT1_DesignVoltage / 100);
    ITempW01 /= 10;     /* Unit is 10mW */
    xEC_Bt1RemainCapacityL = ITempW01;
    xEC_Bt1RemainCapacityH = ITempW01 >> 8;

    ITempW01 = BAT1_Current;
    if (ITempW01 > 0x8000)
    {
        ITempW01 ^= 0xFFFF;
        ITempW01++;
    }
    ITempW01 /= 10;
    ITempW01 *= (WORD)(BAT1_DesignVoltage / 100);
    ITempW01 /= 10;
    xEC_Bt1PresentRateL = ITempW01;
    xEC_Bt1PresentRateH = ITempW01 >> 8;
#else
    xEC_Bt1RemainCapacityL = BAT1_RemainingCapacity;
    xEC_Bt1RemainCapacityH = BAT1_RemainingCapacity >> 8;

    ITempW01 = BAT1_Current;
    if (ITempW01 > 0x8000)
    {
        ITempW01 ^= 0xFFFF;
        ITempW01++;
    }
    xEC_Bt1PresentRateL = ITempW01;
    xEC_Bt1PresentRateH = ITempW01 >> 8;
#endif
    xEC_Bt1PresentVoltageL = BAT1_Voltage;
    xEC_Bt1PresentVoltageH = BAT1_Voltage >> 8;
    xEC_Bt1RSOC = BAT1_RelativeStateOfChgL;
    
    ITempW01 = BAT1_Current;
    if (ITempW01 > 0x8000)
    {
        ITempW01 ^= 0xFFFF;
        ITempW01++;
    }
    xEC_Bt1CurrentL = ITempW01;             // For BIOS read current in real time
    xEC_Bt1CurrentH = ITempW01 >> 8;        // For BIOS read current in real time

    if (xEC_PowerState & F_AC_ON_LINE)
    {
        if (IS_MASK_CLEAR(xEC_PowerState, F_BAT1_PRESENT))
        {
            xEC_Bt1State = 0;
        }
        else if ((BAT1_RelativeStateOfChgL >= 100) &&
                 (BAT1_RemainingCapacity >= BAT1_FullChargeCapacity))
        {
            xEC_Bt1State = 0;
            BAT1_LockPowerOnRSOC = 1;
            if (BAT1_RemainingCapacity < BAT1_LastFCC)
            {
#if SUPPORT_ACPI_BATT_MWH
                BAT1_RemainingCapacity = BAT1_LastFCC;
                ITempW01 = (WORD)(BAT1_RemainingCapacity / 10);
                ITempW01 *= (WORD)(BAT1_DesignVoltage / 100);
                ITempW01 /= 10;     /* Unit is 10mW */
                xEC_Bt1RemainCapacityL = ITempW01;
                xEC_Bt1RemainCapacityH = ITempW01 >> 8;
#else
                xEC_Bt1RemainCapacityL = BAT1_LastFCC;
                xEC_Bt1RemainCapacityH = BAT1_LastFCC >> 8;
#endif
            }
        }
        else
        {
            xEC_Bt1State = F_ACPI_CHARGING;
        }
    }
    else
    {
        xEC_Bt1State = F_ACPI_DISCHRGE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_Battery
 * @function - Update ACPI Control Method Battery
 * @Upstream - Hook_Timer500msEventC
 * @input    - PowerSource
 * @return   - None
 * @note     - None
 */
void Update_ACPI_Battery(void)
{
    BYTE    i;
#if 0   /* TEST MODE */
    BAT1_DesignCapacity = 4000;
    BAT1_FullChargeCapacity = 4000;
    BAT1_DesignVoltage = 8400;
    BAT1_SerialNumber = 0xABCD;
    BAT1_RemainingCapacity = 3500;
    BAT1_Voltage = 8000;
    BAT1_Current = 500;
    BAT1_RelativeStateOfChgL = 87;
    SET_MASK(PowerSource, F_AC_ON_LINE);
    SET_MASK(PowerSource, F_BAT1_PRESENT);
#endif
    /* Intel DPTF SEN 4 = BATTERY TEMPERATURE */
    if (BAT1_DebugMode != 0xDA)
    {
        xEC_BAT1_T4 = BAT1_Temperature;
        if (BAT1_Temperature > 2730)
        {
            ITempW01 = BAT1_Temperature - 2730;
            BAT1_CelsiusDegree = ITempW01 / 10;
        }
        else
        {
            BAT1_CelsiusDegree = 0;
        }
    }

    if (xEC_PowerState != PowerSource)
    {
        i = (xEC_PowerState ^ PowerSource);
        xEC_PowerState = PowerSource;
        Update_ACPI_BIF1();
        Update_ACPI_BST1();
#if 1   /* Process ACPI Event */
        if (i & F_AC_ON_LINE)
        {
            SendACiEventTimer = 5;
            WriteSCI_Buffer(_SCIEVT_ADAPTER);
        }
        else if (i & F_BAT1_PRESENT)
        {
            SendBatEventTimer = 5;
            BAT1_LastRSOC = BAT1_RelativeStateOfChgL;
        }
        BAT1_LastRSOC   = BAT1_RelativeStateOfChgL;
        BAT1_LastFCC    = BAT1_FullChargeCapacity;
        BAT1_0025FCC    = (BAT1_FullChargeCapacity * 25) / 1000;
        BAT1_005FCC     = (BAT1_FullChargeCapacity * 5) / 100;
        BAT1_02FCC      = (BAT1_FullChargeCapacity * 2) / 10;
        BAT1_05FCC      = (BAT1_FullChargeCapacity * 5) / 10;
        BAT1_08FCC      = (BAT1_FullChargeCapacity * 8) / 10;
        BAT1_LockPowerOnRSOC = 0;
#endif
    }
    else
    {
        if (IS_ADAPTER_IN() && (BAT1_LockPowerOnRSOC == 1))
        {
            if (BAT1_RelativeStateOfChgL > 96)
            {
                //Disable update information to os.
                return;
            }
            else
            {
                BAT1_LockPowerOnRSOC = 0;
            }
        }
#if SUPPORT_BATTERY_SMBA
        // Smart Battery connected to SMBus-A
        if (IS_MASK_SET(SMBA_DEV0_STS, F_DEV_UPDATED))
        {
            CLEAR_MASK(SMBA_DEV0_STS, F_DEV_UPDATED);
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
        }
#else
        // Smart Battery connected to SMBus-B
        if (IS_MASK_SET(SMBB_DEV0_STS, F_DEV_UPDATED))
        {
            CLEAR_MASK(SMBB_DEV0_STS, F_DEV_UPDATED);
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
        }
#endif

#if 0   /* TRUE: SCI update for Windows can't polling battery */
        if (BAT1_LastRSOC != BAT1_RelativeStateOfChgL)
        {
            SendBatEventTimer = 5;
            BAT1_LastRSOC = BAT1_RelativeStateOfChgL;
        }
#endif
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - SCI_PowerEvent
 * @function - Adapter/Battery SCI notify event.
 * @Upstream - Hook_Timer100msEventB
 * @input    - EventAdapterOut,EventBatteryOut
 * @return   - None
 * @note     - None
 */
void SCI_PowerEvent(void)
{
    if (SendACiEventTimer > 0)
    {
        SendACiEventTimer--;
        if (SendACiEventTimer == 0)
        {
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
            WriteSCI_Buffer(_SCIEVT_ADAPTER);
        }
        return;
    }

    if (SendBatEventTimer > 0)
    {
        SendBatEventTimer--;
        if (SendBatEventTimer == 0)
        {
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
            WriteSCI_Buffer(_SCIEVT_BATTERY);
        }
        return;
    }
}

#if INTEL_SMARTCHARGING_PHASE1
/*-----------------------------------------------------------------------------
 * @subroutine - Charging_CheckTimeRange
 * @function - Charging_CheckTimeRange
 * @Upstream -
 * @input    -
 * @return   - TRUE: Time in Limit Range
 * @note     -
 */
BYTE Charging_CheckTimeRange(void)
{
    CHGR_SmartPhaseMode = 0x01;
    /* Example: 22:00~05:00 ChargerLimitHourH=22, ChargerLimitHourL=05
                05:00~22:00 ChargerLimitHourH=05, ChargerLimitHourL=22
    */
    if (ChargerLimitHourStart == ChargerLimitHourEnd)
    {
        return FALSE;
    }
    if (ChargerLimitHourStart > ChargerLimitHourEnd)
    {
        if ((xTIME_HH >= ChargerLimitHourStart) ||
                (xTIME_HH < ChargerLimitHourEnd))
        {
            return TRUE;
        }
    }
    else
    {
        if ((xTIME_HH >= ChargerLimitHourStart) &&
                (xTIME_HH < ChargerLimitHourEnd))
        {
            return TRUE;
        }
    }
    return FALSE;
}
#endif


void CheckTypeCRejectPowerOn(void)
{
//     if((xCCG6_PORT1_Active_Watt >= 60) || (xCCG6_PORT2_Active_Watt >= 60) || IS_ADP_PRESENT_HI())
//     {
//         xCCG6_RejectPwrOn = 0;
//     }
//     else
//     {
//         xCCG6_RejectPwrOn = 1;
//     }
}

//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - ADP_Control
 * @function - For Power Source Selection Table.
 * @Upstream - Hook_Timer1msEvent
 * @input    - None
 * @return   - None
 * @note     - First come first serve (FCFS)
 */
void ADP_Control(void)
{
    // Battery present
//     if (IS_BATTERY1_IN())
//         {
//             if (BAT1_RelativeStateOfChgL >= 7)
//             {
//                 xCCG6_RejectPwrOn = 0;
//                 return;
//             }
//             else
//             {
//                 CheckTypeCRejectPowerOn();
//             }
//         }
//         else
//         {
//             CheckTypeCRejectPowerOn();
//         }

#if  SUPPORT_BATTERY_FASTCHARGE
    if((xPD1_pd_PowWatt > 90) || (xPD2_pd_PowWatt > 90))
    {
        CHGR_InputCurrent = 0x1400;   // 5A
    }
    else if((xPD1_pd_PowWatt > 65) || (xPD2_pd_PowWatt > 65))
    {
        CHGR_InputCurrent = 0x0DC0;   // 3.5A
    }
    else
    {
        if(xPD1_pd_PowWatt != 0)
        {
            CHGR_InputCurrent = xPD1_pd_mCurrent;   // Read from PD1 current
        }
        else if(xPD2_pd_PowWatt != 0)
        {
            CHGR_InputCurrent = xPD2_pd_mCurrent;   // Read from PD2 current
        }
        else
        {
            CHGR_InputCurrent = 0x0800;   // 2A
        }
    }
#endif


#if SUPPORT_PD_SINK_CONTROL_ITE
    if((xPD1_pd_PowWatt_tmp != xPD1_pd_PowWatt) || (xPD2_pd_PowWatt_tmp != xPD2_pd_PowWatt))
    {
        xPD1_pd_PowWatt_tmp = xPD1_pd_PowWatt;
        xPD2_pd_PowWatt_tmp = xPD2_pd_PowWatt;
        
        if ((xPD1_pd_PowWatt == 0) && (xPD2_pd_PowWatt == 0))
        {
            //TypeC1 out, TypeC2 out
            SinkSwitchControlPD1(SINK_CONTROL_OFF);
            SinkSwitchControlPD2(SINK_CONTROL_OFF);
        }
        else if ((xPD1_pd_PowWatt > 0) && (xPD2_pd_PowWatt == 0))
        {
            //TypeC1 in, TypeC2 out
            SinkSwitchControlPD1(SINK_CONTROL_ON);
            SinkSwitchControlPD2(SINK_CONTROL_OFF);
        }
        else if ((xPD1_pd_PowWatt == 0) && (xPD2_pd_PowWatt > 0))
        {
            // TypeC1 out, TypeC2 in
            SinkSwitchControlPD1(SINK_CONTROL_OFF);
            SinkSwitchControlPD2(SINK_CONTROL_ON);
        }
        else 
        {
            if (xPD1_pd_PowWatt > xPD2_pd_PowWatt)
            {
                SinkSwitchControlPD1(SINK_CONTROL_ON);
                SinkSwitchControlPD2(SINK_CONTROL_OFF);
            }
            else if (xPD1_pd_PowWatt < xPD2_pd_PowWatt)
            {
                SinkSwitchControlPD1(SINK_CONTROL_OFF);
                SinkSwitchControlPD2(SINK_CONTROL_ON);
            }
            else // if (xPD1_pd_PowWatt == xPD2_pd_PowWatt)
            {
                
            }
        }
    }
#endif

}
/*-----------------------------------------------------------------------------
 * End of OEM_BATTERY.C */
