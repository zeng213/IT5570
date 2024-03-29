/*-----------------------------------------------------------------------------
 * @file     | OEM_POWER.C
 *-----------+-----------------------------------------------------------------
 * @function | System power sequence control
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_POWERSTEP             TRUE
#define SUPPORT_AUTO_S3             FALSE
#define SUPPORT_CHECK_TIMEOUT       FALSE
#define SUPPORT_S4_S5_WAKE_UP       TRUE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_POWERSTEP
#define Power_RamDebug(x)           RamDebug(x)
#else
#define Power_RamDebug(x)           {}
#endif
//-----------------------------------------------------------------------------
void HookMS_CheckLidStatus(void);
/*-----------------------------------------------------------------------------
 * @subroutine - PF_XXXXXXX
 * @function - Hook for power sequence control I/O
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* PUBLIC PF_XXXXXX Power Function  ******************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#if !SUPPORT_CHECK_TIMEOUT
void PF_PowerSwitchOFF(void)
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        PCH_PWRBTN_HI();
        return;
    }
    PCH_PWRBTN_LO();
    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwDownTimer < 2000)
    {
        PowSwDownTimer++;
    }
    else
    {
        PowSwDownTimer = 0;
        SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
        Oem_TriggerPowerOff(_ST_FORCE_SHUTDOWN);
    }
    //-------------------------------------------------------------------------
}
#endif
//-----------------------------------------------------------------------------
BYTE PF_CHECK_WITH_TIMEOUT(WORD OVER_T)
{
    PowSeqWait++;
    if (PowSeqWait > OVER_T)
    {
        PowSeqWait = 0;
        return (1);
    }
    return (0);
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_TIMEOUT(WORD OVER_T)
{
#if SUPPORT_CHECK_TIMEOUT
    PowSeqWait++;
    if (PowSeqWait > OVER_T)
    {
        PowSeqWait = 0;
        return (1);
    }
    return (0);
#else
    PF_PowerSwitchOFF();
    return (0);
#endif
}
//-----------------------------------------------------------------------------
void PF_PECI_ON(void)
{
#ifdef SUPPORT_PECI
#if SUPPORT_PECI
    Init_PECI();
    GPCRF6 = ALT;
    GCR2 |= PECIE;      /* Enable PECI */
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_PECI_OFF(void)
{
#ifdef SUPPORT_PECI
#if SUPPORT_PECI
    GPCRF6 = INPUT;
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_INIT_SIO(void)
{
    RSTS = 0x44;    //SIO Power On
    Init_SIO();
}
//-----------------------------------------------------------------------------
void PF_INIT_PMIO(void)
{
#if 0   //SUPPORT_LPC_PMIO
    GPCRB5 = OUTPUT;        // SIO_A20GATE
    SET_MASK(GPDRB, BIT(5));
    GPCRB6 = OUTPUT;        // SIO_RCIN#
    SET_MASK(GPDRB, BIT(6));
    GPCRD4 = OUTPUT;        // SIO_EXT_SMI#
    SET_MASK(GPDRD, BIT(4));
    //EC_SCI_HI();
    //EC_SMI_HI();
    //GATEA20_HI();
    //KBRST_HI();
#endif
#if SUPPORT_INTERFACE_eSPI
    /* eSPI PME#, WAKE# */
    VWIDX4 = (F_IDX4_PME_VALID +
              F_IDX4_WAKE_VALID +
              F_IDX4_PME +
              F_IDX4_WAKE);
    /* eSPI SCI#, SMI#, RCIN# */
    VWIDX6 |= (F_IDX6_RCIN_VALID +
               F_IDX6_SMI_VALID +
               F_IDX6_SCI_VALID +
               F_IDX6_RCIN +
               F_IDX6_SMI +
               F_IDX6_SCI);
#endif
}
//-----------------------------------------------------------------------------
void PF_PMIO_OFF(void)
{
    //GPCRB5 = INPUT;       // SIO_A20GATE
    //GPCRB6 = INPUT;       // SIO_RCIN#
    //GPCRG2 = INPUT;       // SIO_EXT_SCI#
    //GPCRD4 = INPUT;       // SIO_EXT_SMI#
}
//-----------------------------------------------------------------------------
void PF_INIT_PS2(void)
{
#if SUPPORT_SERVICE_PS2
    PS2DeviceInactive();    // For Touchpad issue
    GPCRF4 = ALT;           // PS2 interface
    GPCRF5 = ALT;
#endif
}
//-----------------------------------------------------------------------------
void PF_PS2_OFF(void)
{
#if SUPPORT_SERVICE_PS2
    GPCRF4 = OUTPUT;        // PS2 interface
    GPCRF5 = OUTPUT;
    CLEAR_MASK(GPDRF, BIT(4));
    CLEAR_MASK(GPDRF, BIT(5));

    MouseDriverIn = 0;
    SetPS2InhibitTime(InactiveTime);
#endif
}
//-----------------------------------------------------------------------------
void PF_SMBUS_ON(void)
{
    /* SMBUS-1 */
    //GPCRC1 = (ALT+PULL_UP);
    //GPCRC2 = (ALT+PULL_UP);
}
//-----------------------------------------------------------------------------
void PF_SMBUS_OFF(void)
{
    /* SMBUS-1 */
    //GPCRC1 = INPUT;
    //GPCRC2 = INPUT;
}
void PF_EC_USBPWR_EN_ON(void)
{
//     EC_USBPWR_EN_ON();
}
void PF_EC_USBPWR_EN_OFF(void)
{
//     EC_USBPWR_EN_OFF();
}
//-----------------------------------------------------------------------------
void PF_RSMRST_HI(void)
{
//-----------------------------------------------------------------------------
#if 0 // For AC only auto power on for G3 to S5
    if (SysPowState == _PST_G3_to_S5)
    {
        if (IS_BATTERY1_IN() && IS_ADAPTER_IN())
        {
            // AC+DC not auto power on in S5
            return;
        }
        else
        {
            // DC only will drop the power by power latch(not auto power on)
            // DC only will power on when press the power button
            // AC only(auto power on)
        }
    }
#endif
//-----------------------------------------------------------------------------

    if (IS_PCH_RSMRST_LO())
    {
        PCH_PWRBTN_HI();
    }
    if (ECHIPVER >= _CHIP_EX)
    {
        CLEAR_MASK(ESGCTRL2, F_ESPIIPG);
    }
    RSTS = 0x44;
    PCH_RSMRST_HI();
    AC_PRESENT_HI();

    GPCRD2 = ALT;
#if eSPI_RESET_FOR_DSW_PWROK
    VWCTRL2 |= F_DSW_PWROK_SOURCE;
#endif
#if SUPPORT_INTERFACE_eSPI
    /* eSPI PME#, WAKE# */
    VWIDX4 = (F_IDX4_PME_VALID +
              F_IDX4_WAKE_VALID +
              F_IDX4_PME +
              F_IDX4_WAKE);
    /* eSPI SCI#, SMI#, RCIN# */
    VWIDX6 |= (F_IDX6_RCIN_VALID +
               F_IDX6_SMI_VALID +
               F_IDX6_SCI_VALID +
               F_IDX6_RCIN +
               F_IDX6_SMI +
               F_IDX6_SCI);
#endif
}
//-----------------------------------------------------------------------------
void PF_RSMRST_LO(void)
{
    if (ECHIPVER >= _CHIP_EX)
    {    
        SET_MASK(ESGCTRL2, F_ESPIIPG);
    }
    RSTS = 0x04;
    PCH_RSMRST_LO();    //GPH0
    //Delay1MS(5);
    DSW_PWROK_R_LO();   //GPC4
}
//-----------------------------------------------------------------------------
void PF_PWRBTN_HI(void)
{
    PCH_PWRBTN_HI();
}
//-----------------------------------------------------------------------------
void PF_CHK_PWRBTN_HI(void)
{
	PCH_PWRBTN_HI();
}
//-----------------------------------------------------------------------------
void PF_CHK_PWRBTN_LO(void)
{
    if ((IS_ADAPTER_OUT()) || (IS_eSPI_SLP_S3_LO()))
    {
        PCH_PWRBTN_LO();
    }
}
//-----------------------------------------------------------------------------
void PF_PWRBTN_LO(void)
{
    if (IS_eSPI_SLP_S3_LO())
    {
        PCH_PWRBTN_LO();
    }
}
//-----------------------------------------------------------------------------
void PF_GATEA20_HI(void)
{
    //SET_MASK(GPDRB, BIT(5));
}
//-----------------------------------------------------------------------------
void PF_GATEA20_LO(void)
{
    //CLEAR_MASK(GPDRB, BIT(5));
}
//-----------------------------------------------------------------------------
void PF_FAN_PWR_ON(void)
{
    GPCRA7 = ALT;
#if SUPPORT_FAN1_TACH
    GPCRD6 = ALT;
#endif
}
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* OEM PF_XXXXXX Power Wait Signal Function  *********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S3_HI(void)
{
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S3_HI())    /* Use eSPI */
    {
        return (1); /* TRUE: Next Power Function */
    }
#else
    if (IS_PCH_SLP_S3_HI())     /* Use GPI  */
    {
        return (1); /* TRUE: Next Power Function */
    }
#endif
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S3_LO(void)
{
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S3_LO())    /* Use eSPI */
    {
        return (1); /* TRUE: Next Power Function */
    }
#else
    if (IS_PCH_SLP_S3_LO())     /* Use GPI  */
    {
        return (1); /* TRUE: Next Power Function */
    }
#endif
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S4_HI(void)
{
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S4_HI())    /* Use eSPI */
    {
        return (1); /* TRUE: Next Power Function */
    }
#else
    if (IS_PCH_SLP_S4_HI())     /* Use GPI  */
    {
        return (1); /* TRUE: Next Power Function */
    }
#endif
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S4_LO(void)
{
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S4_LO())    /* Use eSPI */
    {
        return (1); /* TRUE: Next Power Function */
    }
#else
    if (IS_PCH_SLP_S4_LO())     /* Use GPI  */
    {
        return (1); /* TRUE: Next Power Function */
    }
#endif
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S5_HI(void)
{
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S5_HI())    /* Use eSPI */
    {
        RSTS = 0x44;
        return (1); /* TRUE: Next Power Function */
    }
#else
    if (IS_PCH_SLP_S5_HI())     /* Use GPI  */
    {
        RSTS = 0x44;
        return (1); /* TRUE: Next Power Function */
    }
#endif
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* OEM PF_XXXXXX Power Function  *********************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
void PF_ADP_PRESENT(void)
{
    if (IS_ADAPTER_IN())
    {
        AC_PRESENT_HI();    //GPF7
        BATLOW_N_HI();      //GPD1
    }
    else
    {
        AC_PRESENT_LO();
        BATLOW_N_HI();
        // Check Battery Low
        // TODO:
    }
}
void PF_BATLOW_N_HI(void)
{
        BATLOW_N_HI();      //GPD1
}
void PF_BATLOW_N_LO(void)
{
        BATLOW_N_LO();      //GPD1
}
//-----------------------------------------------------------------------------
void PF_ALL_SYS_PWRGD_HI(void)
{
    ALL_SYS_PWRGD_HI();
    VCCST_PWRGD_OUT_EC_HI();
}
//-----------------------------------------------------------------------------
void PF_ALL_SYS_PWRGD_LO(void)
{
    ALL_SYS_PWRGD_LO();
}
//-----------------------------------------------------------------------------
void PF_PWR_LED_ON(void)
{
    GPCRA0 = OUTPUT;
    LED_PWR_N_ON();
    // For power saving with S5 AC mode
    SET_MASK(ZTIER, BIT1);
}
//-----------------------------------------------------------------------------
void PF_PWR_LED_OFF(void)
{
    LED_PWR_N_OFF();
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_V3P3A_PGOOD_HI(void)
{
    if (IS_V3P3A_PGOOD_HI())    /* Use eSPI */
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
void PF_EC_PWR_LATCH_HI(void)
{
    EC_PWR_LATCH_HI();
}
//-----------------------------------------------------------------------------
void PF_DSW_PWROK_R_HI(void)
{
    if (IS_DSW_PWROK_R_LO())
    {
        DSW_PWROK_R_HI();
    }
}
void PF_DSW_PWROK_R_LO(void)
{
    DSW_PWROK_R_LO();
}
//-----------------------------------------------------------------------------
void PF_KBRST_HI(void)
{
//     KB_RST_N_HI();
}
//-----------------------------------------------------------------------------
void PF_KBRST_LO(void)
{
//     KB_RST_N_LO();
}
//-----------------------------------------------------------------------------
void PF_SYS_PWROK_HI(void)
{
    SYS_PWROK_HI();
}
//-----------------------------------------------------------------------------
void PF_SYS_PWROK_LO(void)
{
    SYS_PWROK_LO();
}
//-----------------------------------------------------------------------------
void PF_PM_PCH_PWROK_HI(void)
{
    PM_PCH_PWROK_HI();
}
//-----------------------------------------------------------------------------
void PF_PM_PCH_PWROK_LO(void)
{
    PM_PCH_PWROK_LO();
}
//-----------------------------------------------------------------------------
void PF_EC_EC_SLP_SX_HI(void)
{
    EC_SLP_SX_HI();
}
//-----------------------------------------------------------------------------
void PF_EC_EC_SLP_SX_LO(void)
{
    EC_SLP_SX_LO();
}
//-----------------------------------------------------------------------------
void PF_BKLT_OFF_EC_HI(void)
{

}
//-----------------------------------------------------------------------------
void PF_BKLT_OFF_EC_LO(void)
{
    Key_BackLight_Off();
}
//-----------------------------------------------------------------------------
void PF_EC_VDDQ_EN_HI(void)
{

}
//-----------------------------------------------------------------------------
void PF_EC_VDDQ_EN_LO(void)
{

}
//-----------------------------------------------------------------------------
void PF_PROCHOT_HI(void)
{
    EC_PROCHOT_HI();
}
//-----------------------------------------------------------------------------
void PF_PROCHOT_LO(void)
{
    EC_PROCHOT_LO();
}
//-----------------------------------------------------------------------------
void PF_EC_STATE_LO(void)
{
    EC_STATE_LO();
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_PM_SLP_SUS_HI(void)
{
    if (IS_PM_SLP_SUS_N_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_RSMRST_PWRGD_HI(void)
{
    if (IS_RSMRST_PWRGD_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_VDD2_VR_PWRGD_HI(void)
{
// Disable for SMT
//    if (IS_VDD2_VR_PWRGD_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_VCCST_VR_PWRGD_IN_HI(void)
{
    //if (IS_VCCST_VR_PWRGD_IN_HI())
    if (Get_ADC_CH3())
    {
        if (xADC[3] >= 0x4C)    //0x4C:0.9V
        {
            return (1); /* TRUE: Next Power Function */
        }
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
BYTE PF_VCCANA_VR_PWRGD_HI(void)
{
    if (IS_VCCANA_VR_PWRGD_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
void PF_VCCST_PWRGD_OUT_EC_HI(void)
{
    VCCST_PWRGD_OUT_EC_HI();
}
//-----------------------------------------------------------------------------
void PF_VCCST_PWRGD_OUT_EC_LO(void)
{
    VCCST_PWRGD_OUT_EC_LO();
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_IMVP9_VR_READY_HI(void)
{
    if (IS_IMVP9_VR_READY_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    PF_PowerSwitchOFF();
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - PF_POWER_ON_PD_INIT
 * @function - PF_POWER_ON_PD_INIT
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void PF_POWER_ON_PD_INIT(void)
{
    SendSystemStatusToPD1(_SYSTEM_S0);   /* b00:S0 state */
    SendSystemStatusToPD2(_SYSTEM_S0);   /* b00:S0 state */
}

/*-----------------------------------------------------------------------------
 * @subroutine - PF_POWER_OFF_PD_INIT
 * @function - PF_POWER_OFF_PD_INIT
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void PF_POWER_OFF_PD_INIT(void)
{
    SendSystemStatusToPD1(_SYSTEM_S5);   /* b10:S4 state */
    SendSystemStatusToPD2(_SYSTEM_S5);   /* b10:S4 state */
}

void PF_LED_NOTIFY(void)
{
    //use LED notify user that shutdown already happend.
    if (_ST_FORCE_SHUTDOWN == xEC_ShutdownCode)
    {
        LED_NotifyForceShutdown();
    }
    else if ((_ST_SOC_TP_SHUTDOWN == xEC_ShutdownCode) || (_ST_SKIN_TP_SHUTDOWN == xEC_ShutdownCode))
    {
         LED_NotifyAbnormalShutodown();
    }
}
//-----------------------------------------------------------------------------
//*****************************************************************************
// Control code:
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - CheckResetSource
 * @function - CheckResetSource
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void CheckResetSource(void)
{
    //BRAM[0x3A] = RSTStatus;
    //RSTS |= 0x03;     // Clear Reset Flag
}

/*-----------------------------------------------------------------------------
 * @subroutine - SystemWarmBoot
 * @function - SystemWarmBoot
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void SystemWarmBoot(void)
{
    CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
    xAMP_EN_TestTimer = 50;  // For AMP_EN workaround every 100ms * 50 = 5s
    
    if(xEC_StateTimer == 0)
    {
        EC_STATE_LO();          // 100ms low pulse
        xEC_StateTimer = 11;    // Delay 100ms and pull up EC_STATE (Set 10 will less than 100ms)
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - INIT_COMMON_OFF
 * @function - INIT_COMMON_S3S4S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void INIT_COMMON_OFF(void)
{
    //-------------------------------------------------------------------------
    /* PROCESS PUBLIC INITIALIZE FOR POWER OFF */
    //-------------------------------------------------------------------------
    CLEAR_MASK(KBHISR, SYSF);
    Ccb42_SYS_FLAG = 0;
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif
    //ClearSCIEvent();
    SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
    //-------------------------------------------------------------------------
    /* GPIO FUNCTION POWER OFF */
    //-------------------------------------------------------------------------
    PF_PECI_OFF();
    //WIFI_DISABLE();
    AMP_EN_LO();
    //-------------------------------------------------------------------------
    /* OEM PLATFORM INITIALIZE FOR POWER OFF */
    //-------------------------------------------------------------------------
	// For power saving with S5 AC mode
    CLEAR_MASK(ADCCFG, ADCEN);
    Reload_EC_Ver();
    ResetSCIEvent();
    //-------------------------------------------------------------------------
    xOOB_PauseTimer = 200;
#if SUPPORT_OOB_CRASHLOG_KEY
    xOOB_GetCrashLogLock = 0;
    xOOB_RemindGetCrashLogLED = 0;
#endif
#if 1  /* PowerSwitch Long Press */
    if ((BRAM[0x3B] == 0xA5) &&
            (BRAM[0x3C] == 0x5A) &&
            (BRAM[0x3D] == 0xCC))
    {
        /* Reject Power Switch Power On */
        if (IS_ADP_PRESENT_LO())
        {
            POWER_LATCH_OFF();
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - INIT_COMMON_ON
 * @function - INIT_COMMON_ON
 * @upstream - GO_INIT_S0() ; GO_INIT_S3_TO_S0()
 * @input    - None
 * @return   - None
 * @note     - None
 */
void INIT_COMMON_ON(void)
{
    SysPowState = _SYSTEM_S0;
    //-------------------------------------------------------------------------
    /* PROCESS PUBLIC INITIALIZE FOR POWER ON */
    //-------------------------------------------------------------------------
    CLEAR_MASK(KBHISR, SYSF);
    SET_MASK(KBHISR, KEYL);
    Ccb42_SYS_FLAG = 0;
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif
    //ClearSCIEvent();
    SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
    /* Tag Power Switch Long Time Pressed */
    BRAM[0x3B] = 0xA5;  /* SET REJECT POWER ON TAG */
    BRAM[0x3C] = 0x5A;
    BRAM[0x3D] = 0xCC;
    
    // Avoid auto power on after force shutdown
    BRAM[0x3A] = 0x00;
#if SUPPORT_SAR_TEST_MODE
    SAR_Initial();
#endif
    //-------------------------------------------------------------------------
    /* GPIO FUNCTION POWER ON */
    //-------------------------------------------------------------------------
    //WIFI_ENABLE();
    AMP_EN_HI();
    V5A_POGO_EN_HI();
    SET_MASK(xEC_POGO_Status, BIT0);
    xEC_StateTimer = 30;    // Delay 300ms and pull up EC_STATE
    //-------------------------------------------------------------------------
    /* OEM PLATFORM INITIALIZE FOR POWER ON */
    //-------------------------------------------------------------------------
	// For power saving with S5 AC mode
    SET_MASK(ADCCFG, ADCEN);
    
    ResetSCIEvent();
    SET_MASK(xEC_LID_STATUS, F_LID_STA);
    //------------------------------------------------------------------------
    xEC_ShutdownCode = 0;
    xEC_Sensor_1_T = 0;
    xEC_Sensor_2_T = 0;
    xEC_Sensor_3_T = 0;
    System_CS_Mode = 0;
    PwrBtn_OVR_Mode = 1;
    xOOB_PauseTimer = 200;
#if 0 //1: Decrease CPU Power (only for test)
    ITempB06 = 0;
    while (1)
    {
        OOB_PECI_WritePowerLimit4(40);
        Delay1MS(100);
        OOB_PECI_WritePowerLimit4(40);
        Delay1MS(100);
        ITempB06++;
        if (ITempB06 > 5)
        {
            break;
        }
    }
#endif

#if INTEL_EC_FLASH_AUTO_POWER_ON
    if(BRAM[62] != 0)
    {
        SetAutoBootTimer = 0;
        BRAM[62] = 0;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S0
 * @function - GO_INIT_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void GO_INIT_S0(void)
{
#if ITE_CHIP_IT557X
    SPCTRL1 |= (P80LEN + ACP80 + ACP81);
    //SET_MASK(SPCTRL1, P80LEN);
    //SET_MASK(SPCTRL1, ACP80);     /* Accept Port 80h cycle */
    //SET_MASK(SPCTRL1, ACP81);     /* Accept Port 81h cycle */
#endif
    INIT_COMMON_ON();
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S3_TO_S0
 * @function - GO_INIT_S3_TO_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void GO_INIT_S3_TO_S0(void)
{
    INIT_COMMON_ON();
}
/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S3
 * @function - GO_INIT_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void GO_INIT_S3(void)
{
    INIT_COMMON_OFF();
    SysPowState = _SYSTEM_S3;
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S5
 * @function - GO_INIT_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void GO_INIT_S5(void)
{
	// For power saving with S5 AC mode
    CLEAR_MASK(ZTIER, BIT1);
    INIT_COMMON_OFF();
    // For G3 to S5 power on
    if (SysPowState == _PST_G3_to_S5)
    {
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
    }    
    SysPowState = _SYSTEM_S5;
    CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_G3
 * @function - GO_INIT_G3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void GO_INIT_G3(void)
{
    INIT_COMMON_OFF();
    SysPowState = _SYSTEM_G3;
    RSTS = 0x84;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PF_SET_ME_UNLOCK
 * @function - PF_SET_ME_UNLOCK
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void PF_SET_ME_UNLOCK(void)
{
    if (IS_MASK_SET(HOST_BIOS_REG1, F_ME_UNLOCK))
    {
        /* Only one time trigger so clear it. */
        CLEAR_MASK(HOST_BIOS_REG1, F_ME_UNLOCK);
        PCH_ME_UNLOCK_HI();
        PCH_ME_UNLOCK();    //REAL PIN
    }
    else
    {
        PCH_ME_UNLOCK_LO();
        PCH_ME_LOCK();      //REAL PIN
    }
}

/*-----------------------------------------------------------------------------
 * @table - sSEQ_S5_to_S0
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code ADL_N_sSEQ_S5_to_S0[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_PWR_LED_ON,                0,      0,  },
    
    { PF_ADP_PRESENT,               0,      0,  },  //
    { PF_CHK_V3P3A_PGOOD_HI,       10,      1,  },  //Step:10a  GPD5
    { PF_EC_PWR_LATCH_HI,           0,      0,  },  //Step:16  GPH5
    { PF_DSW_PWROK_R_HI,            0,      0,  },  //Step:9   GPC4
    { PF_PWRBTN_HI,                 0,      0,  },  //Step:17  GPF4
    { PF_CHK_PM_SLP_SUS_HI,         0,      1,  },  //Step:18  GPE6
    { PF_CHK_RSMRST_PWRGD_HI,      15,      1,  },  //Step:17  GPJ5 RSMRST_PWRGD_N
    { PF_RSMRST_HI,                20,      0,  },  //Step:18  GPH0
#if 1
    { PF_CHK_PWRBTN_LO,            20,      0,  },
    { PF_CHK_PWRBTN_HI,             0,      0,  },
#endif
    { PF_INIT_SIO,                  0,      0,  },
    { PF_INIT_PMIO,                 0,      0,  },
    { PF_EC_EC_SLP_SX_HI,           0,      0,  },  //Step:35  GPE4 Empty  
    { PF_CHECK_SLP_S4_HI,           0,      1,  },  //Step:36
    { PF_CHECK_SLP_S3_HI,           0,      1,  },  //Step:37  
    { PF_CHK_VCCST_VR_PWRGD_IN_HI,  0,      1,  },  //Step:23 GPI3 VCCST_VR_PWRGD_IN
    { PF_CHK_VDD2_VR_PWRGD_HI,      5,      1,  },  //Step:42 GPJ2 
//    { PF_VCCST_PWRGD_OUT_EC_HI,    10,      0,  },  //Step:43 GPA2
//    { PF_VCCANA_VR_PWRGD_HI,        0,      1,  },  //Step:48 GPD0
//     { PF_FAN_PWR_ON,                0,      0,  },
    { PF_ALL_SYS_PWRGD_HI,         10,      0,  },  //Step:50 GPC5
    { PF_CHK_IMVP9_VR_READY_HI,     0,      0,  },  //Step:26  GPH7
    { PF_SET_ME_UNLOCK,             0,      0,  },
    { PF_PM_PCH_PWROK_HI,          99,      0,  },  //Step:54 GPE5
    { PF_SYS_PWROK_HI,              0,      0,  },  //Step:55 GPB5
    { PF_PROCHOT_HI,                0,      0,  },
    //{ PF_GATEA20_HI,              0,      0,  },
    { PF_KBRST_HI,                  0,      0,  },
    { PF_POWER_ON_PD_INIT,          0,      0,  },
    { PF_PECI_ON,                   0,      0,  },
    { PF_INIT_PS2,                  0,      0,  },
    { PF_SMBUS_ON,                  0,      0,  },
    { PF_BKLT_OFF_EC_HI,            0,      0,  },
    { PF_EC_USBPWR_EN_ON,           0,      0,  },
    { GO_INIT_S0,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S0_to_S5
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S0_to_S5[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    //{ PF_GATEA20_LO,              0,      0,  },
    { PF_SYS_PWROK_LO,              0,      0,  },
    { PF_ALL_SYS_PWRGD_LO,          5,      0,  },
    { PF_PROCHOT_LO,                0,      0,  },
    { PF_PM_PCH_PWROK_LO,           0,      0,  },
    { PF_EC_EC_SLP_SX_LO,           0,      0,  },  //Step:12
    { PF_VCCST_PWRGD_OUT_EC_LO,     0,      0,  },  //Step:17  GPA2
    { PF_BKLT_OFF_EC_LO,            0,      0,  },
    { PF_PECI_OFF,                  0,      0,  },
    { PF_KBRST_LO,                  0,      0,  },
    { PF_POWER_OFF_PD_INIT,         0,      0,  },
    { PF_PS2_OFF,                   0,      0,  },
    { PF_SMBUS_OFF,                 0,      0,  },
    { PF_PWR_LED_OFF,               0,      0,  },
    { PF_EC_USBPWR_EN_OFF,          0,      0,  },
    { PF_EC_STATE_LO,               0,      0,  },
    { PF_LED_NOTIFY,                0,      0,  },
    { GO_INIT_S5,                   0,      0,  },  /* Sequence End */

};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S0_to_S3
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S0_to_S3[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    //{ PF_GATEA20_LO,              0,      0,  },
    { PF_SYS_PWROK_LO,              0,      0,  },
    { PF_PROCHOT_LO,                0,      0,  },
    { PF_ALL_SYS_PWRGD_LO,          5,      0,  },
    { PF_PM_PCH_PWROK_LO,           0,      0,  },
    { PF_EC_EC_SLP_SX_LO,           0,      0,  },  //Step:12
    { PF_VCCST_PWRGD_OUT_EC_LO,     0,      0,  },  //Step:17  GPA2
    { PF_BKLT_OFF_EC_LO,            0,      0,  },
    { PF_PECI_OFF,                  0,      0,  },
    { PF_KBRST_LO,                  0,      0,  },
    { PF_PS2_OFF,                   0,      0,  },
    { PF_SMBUS_OFF,                 0,      0,  },
    { PF_EC_STATE_LO,               0,      0,  },
    { GO_INIT_S3,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S3_to_S0
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S3_to_S0[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_EC_EC_SLP_SX_HI,           0,      0,  },
//     { PF_FAN_PWR_ON,                0,      0,  },
    { PF_VCCST_PWRGD_OUT_EC_HI,    10,      0,  },  //Step:17  GPA2
    { PF_ALL_SYS_PWRGD_HI,          0,      0,  },  //Step:18
    { PF_CHK_IMVP9_VR_READY_HI,     0,      1,  },  //Step:19  GPH7
    { PF_PM_PCH_PWROK_HI,          99,      0,  },  //Step:20  GPE5
    { PF_SYS_PWROK_HI,              0,      0,  },  //Step:21  GPB5
    { PF_PROCHOT_HI,                0,      0,  },
    //{ PF_GATEA20_HI,              0,      0,  },
    { PF_KBRST_HI,                  0,      0,  },
    { PF_PECI_ON,                   0,      0,  },
    { PF_INIT_PS2,                  0,      0,  },
    { PF_SMBUS_ON,                  0,      0,  },
    { PF_BKLT_OFF_EC_HI,            0,      0,  },
    { GO_INIT_S3_TO_S0,             0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S5_to_G3
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S5_to_G3[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_RSMRST_LO,                 0,      0,  },
    { PF_DSW_PWROK_R_LO,            0,      0,  },
    { GO_INIT_G3,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_G3_to_S5
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_G3_to_S5[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_CHK_V3P3A_PGOOD_HI,       10,      1,  },  //Step:10a  GPD5
    { PF_DSW_PWROK_R_HI,           10,      0,  },  //Step:13  GPC4
    { PF_BATLOW_N_HI,               0,      0,  },  //Step:14  GPD1
    { PF_EC_PWR_LATCH_HI,           0,      0,  },  //Step:16  GPH5
    { PF_PWRBTN_HI,                 0,      0,  },  //Step:17  GPF4
    { PF_CHK_PM_SLP_SUS_HI,         0,      1,  },  //Step:18  GPE6
    { PF_CHK_VCCST_VR_PWRGD_IN_HI,  0,      1,  },  //Step:27a GPI3 
    { PF_CHK_RSMRST_PWRGD_HI,      10,      1,  },  //Step:31  GPJ5 
#if 1
    { PF_RSMRST_HI,                 0,      0,  },  //Step:32  GPH0
#endif
    { GO_INIT_S5,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_G3_to_S5
 * @function - Oem_PST_G3_to_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_PST_G3_to_S5(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_G3_to_S5) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_G3_to_S5[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_G3_to_S5[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_G3_to_S5[CtrlPowStep].delay;
            Power_RamDebug(0xD5);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_G3_to_S5[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_G3_to_S5[CtrlPowStep].delay;
                Power_RamDebug(0xD5);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S5_to_G3
 * @function - Oem_PST_S5_to_G3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_PST_S5_to_G3(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S5_to_G3) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S5_to_G3[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S5_to_G3[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
            Power_RamDebug(0xD3);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S5_to_G3[CtrlPowStep].func)())
            {
                /* Check Status Pass */
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
                Power_RamDebug(0xD3);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S5_to_S0
 * @function - Oem_PST_S5_to_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S5_to_S0(void)
{
    while (CtrlPowStep < (sizeof(ADL_N_sSEQ_S5_to_S0) / sizeof(sPowerSEQ)))
    {
        if (ADL_N_sSEQ_S5_to_S0[CtrlPowStep].checkstatus == 0x00)
        {
            (ADL_N_sSEQ_S5_to_S0[CtrlPowStep].func)();
            PowSeqDelay = ADL_N_sSEQ_S5_to_S0[CtrlPowStep].delay;
            Power_RamDebug(0xC0);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((ADL_N_sSEQ_S5_to_S0[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = ADL_N_sSEQ_S5_to_S0[CtrlPowStep].delay;
                Power_RamDebug(0xC0);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S0_to_S5
 * @function - Oem_PST_S0_to_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_PST_S0_to_S5(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S0_to_S5) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S0_to_S5[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S0_to_S5[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S0_to_S5[CtrlPowStep].delay;
            Power_RamDebug(0xC5);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S0_to_S5[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S0_to_S5[CtrlPowStep].delay;
                Power_RamDebug(0xC5);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S0_to_S3
 * @function - Oem_PST_S0_to_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_PST_S0_to_S3(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S0_to_S3) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S0_to_S3[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S0_to_S3[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S0_to_S3[CtrlPowStep].delay;
            Power_RamDebug(0xC3);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S0_to_S3[CtrlPowStep].func)())
            {
                PowSeqDelay = sSEQ_S0_to_S3[CtrlPowStep].delay;
                Power_RamDebug(0xC3);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S3_to_S0
 * @function - Oem_PST_S3_to_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_PST_S3_to_S0(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S3_to_S0) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S3_to_S0[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S3_to_S0[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S3_to_S0[CtrlPowStep].delay;
            Power_RamDebug(0x30);
            Power_RamDebug(CtrlPowStep);
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S3_to_S0[CtrlPowStep].func)())
            {
                PowSeqDelay = sSEQ_S3_to_S0[CtrlPowStep].delay;
                Power_RamDebug(0x30);
                Power_RamDebug(CtrlPowStep);
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowSequence
 * @function - Oem_SysPowSequence
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_SysPowSequence(void)
{
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE QUICKLY TIMING
    /*-----------------------------------------------------------------------*/
    // TODO:
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE DELAY
    /*-----------------------------------------------------------------------*/
    if (PowSeqDelay != 0x00)
    {
        PowSeqDelay--;              //1m Sec count base

        if (PowSeqDelay != 0x00)
        {
            return;
        }
    }
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE STEP
    /*-----------------------------------------------------------------------*/
    switch (SysPowState)
    {
        //---------------------------------------------------------------------
    case _PST_G3_to_S5:     // Power State Transitions: G3 -> S5
        Oem_PST_G3_to_S5();
        break;
        //---------------------------------------------------------------------
    case _PST_S5_to_S0:     // Power State Transitions: S5 -> S0
        Oem_PST_S5_to_S0();
        break;
        //---------------------------------------------------------------------
    case _PST_S0_to_S3:     // Power State Transitions: S0 -> S3
        Oem_PST_S0_to_S3();
        break;
        //---------------------------------------------------------------------
    case _PST_S3_to_S0:     // Power State Transitions: S3 -> S0
        Oem_PST_S3_to_S0();
        break;
        //---------------------------------------------------------------------
    case _PST_S0_to_S5:     // Power State Transitions: S0 -> S5
        Oem_PST_S0_to_S5();
        break;
        //---------------------------------------------------------------------
    case _PST_S5_to_G3:     // Power State Transitions: S5 -> G3
        Oem_PST_S5_to_G3();
        break;
        //---------------------------------------------------------------------
    default:
        SysPowState = 0;
        return;
        //---------------------------------------------------------------------
    }
    /*-----------------------------------------------------------------------*/
}

/*-----------------------------------------------------------------------------
 * @subroutine - Set_SysPowState
 * @function - Set_SysPowState
 * @upstream - By call
 * @input    - SetValue
 * @return   - None
 * @note     - None
 */
void Set_SysPowState(BYTE SetValue)
{
    CtrlPowStep = 1;
    PowSeqDelay = 0;
    SysPowState = SetValue;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_TriggerPowerOn
 * @function - Oem_TriggerPowerOn
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_TriggerPowerOn(void)
{
    Set_SysPowState(_PST_S5_to_S0);
    PowerOnFailed = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_TriggerPowerOff
 * @function - Oem_TriggerPowerOff
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_TriggerPowerOff(BYTE ShutdownCode)
{
    xEC_ShutdownCode = ShutdownCode;
    if ((xEC_ShutdownCode == _ST_FORCE_SHUTDOWN) ||
        (xEC_ShutdownCode == _ST_SOC_TP_SHUTDOWN) ||
        (xEC_ShutdownCode == _ST_SKIN_TP_SHUTDOWN))
    {
        PowerLatchTimer = 5;
        BRAM[0x3B] = 0xA5;
        BRAM[0x3C] = 0x5A;
        BRAM[0x3D] = 0xCC;
    }
    // Avoid auto power on after force shutdown
    BRAM[0x3A] = 0x5A;
    Set_SysPowState(_PST_S0_to_S5);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PowSwToPWRBTN
 * @function - Oem_PowSwToPWRBTN
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PowSwToPWRBTN_S3(void)
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }

        PCH_PWRBTN_HI();
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        /* Clear Power Switch Long Time Pressed */
        BRAM[0x3B] = 0x00;  /* CLEAR REJECT POWER ON TAG */
        BRAM[0x3C] = 0x00;
        BRAM[0x3D] = 0x00;
        /* Solved quickly up/down power switch ON->OFF->ON issue */
        if (IS_MASK_SET(PowSwFlag, F_PSW_UP_DELAY))
        {
            wLockPWRBTN = 1000;
            CLEAR_MASK(PowSwFlag, F_PSW_UP_DELAY);
        }
        return;
    }

    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        PCH_PWRBTN_HI();
        return;
    }
    /* Solved quickly up/down power switch ON->OFF->ON issue */
    if (wLockPWRBTN > 0)
    {
        wLockPWRBTN = 1000;
        return;
    }
    SET_MASK(PowSwFlag, F_PSW_UP_DELAY);
    //-------------------------------------------------------------------------
    PCH_PWRBTN_LO();
    if (PowSwDownTimer <= FORCE_SHUTDOWN_TIME_IN_S3) /*ms*/
    {
        ++PowSwDownTimer;
    }
    else
    {
        PowSwDownTimer = 0;
        SET_MASK(PowSwFlag  , F_PSW_WAIT_UP);
        Oem_TriggerPowerOff(_ST_FORCE_SHUTDOWN);
        /* Tag Power Switch Long Time Pressed */
        BRAM[0x3B] = 0xA5;  /* SET REJECT POWER ON TAG */
        BRAM[0x3C] = 0x5A;
        BRAM[0x3D] = 0xCC;
    }
    //-------------------------------------------------------------------------
}



/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PowSwToPWRBTN
 * @function - Oem_PowSwToPWRBTN_S0_S1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PowSwToPWRBTN_S0_S1(void)
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }

        if (IS_MASK_SET(PowSwFlag, F_PSW_SEND_SOC_PWRBTN))
        {
            //for short pressing, trigger a SOC power button physical event
            PF_TrggerSOCPwrBtn(POWER_BTN_REASON_PHY_BTN);

            CLEAR_MASK(PowSwFlag, F_PSW_SEND_SOC_PWRBTN);
        }

        //no matter what happend before, remember to release SOC power button
        //when user released power button
        PCH_PWRBTN_HI();

        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        /* Clear Power Switch Long Time Pressed */
        BRAM[0x3B] = 0x00;  /* CLEAR REJECT POWER ON TAG */
        BRAM[0x3C] = 0x00;
        BRAM[0x3D] = 0x00;
        /* Solved quickly up/down power switch ON->OFF->ON issue */
        if (IS_MASK_SET(PowSwFlag, F_PSW_UP_DELAY))
        {
            wLockPWRBTN = 1000;
            CLEAR_MASK(PowSwFlag, F_PSW_UP_DELAY);
        }
        return;
    }

    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        PCH_PWRBTN_HI();
        return;
    }

    /* Solved quickly up/down power switch ON->OFF->ON issue */
    if (wLockPWRBTN > 0)
    {
        wLockPWRBTN = 1000;
        return;
    }
    SET_MASK(PowSwFlag, F_PSW_UP_DELAY);
    //-------------------------------------------------------------------------
    //PCH_PWRBTN_LO();
    if (PowSwDownTimer <= FORCE_SHUTDOWN_TIME_IN_NON_ACPI)  /*ms*/
    {
        ++PowSwDownTimer;
        SET_MASK(PowSwFlag, F_PSW_SEND_SOC_PWRBTN);
    }
    else
    {
        PowSwDownTimer = 0;

        CLEAR_MASK(PowSwFlag, F_PSW_SEND_SOC_PWRBTN);

        //PCH_PWRBTN_LO();
        Oem_TriggerPowerOff(_ST_FORCE_SHUTDOWN);

        SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
        /* Tag Power Switch Long Time Pressed */
        BRAM[0x3B] = 0xA5;  /* SET REJECT POWER ON TAG */
        BRAM[0x3C] = 0x5A;
        BRAM[0x3D] = 0xCC;
    }
    //-------------------------------------------------------------------------
}

void Oem_PowSwToPWRBTN_ACPI_MODE()
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }

        /*in acpi mode, we should not touch the power button actually
            but when switch from non-acpi mode to acpi mode, may the power button
            already pulled down, so we must release the powewr button here
        */
        PCH_PWRBTN_HI();

        if (PowSwDownTimer > 0)
        {
            if (PowSwDownTimer < PWRBTN_LONG_PRESS_TRIGGER_TIME_ACPI_MODE)
            {
                WriteSCI_Buffer(_SCIEVT_PWRBTN);
            }
            else
            {
                WriteSCI_Buffer(_SCIEVT_PWRBTN_LONG_PRESSED_RELEASE);
            }
        }

//      PCH_PWRBTN_HI();

        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        /* Clear Power Switch Long Time Pressed */
        BRAM[0x3B] = 0x00;  /* CLEAR REJECT POWER ON TAG */
        BRAM[0x3C] = 0x00;
        BRAM[0x3D] = 0x00;
        /* Solved quickly up/down power switch ON->OFF->ON issue */
        if (IS_MASK_SET(PowSwFlag, F_PSW_UP_DELAY))
        {
            wLockPWRBTN = 1000;
            CLEAR_MASK(PowSwFlag, F_PSW_UP_DELAY);
        }
        return;
    }
    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        PCH_PWRBTN_HI();
        return;
    }
    /* Solved quickly up/down power switch ON->OFF->ON issue */
    if (wLockPWRBTN > 0)
    {
        wLockPWRBTN = 1000;
        return;
    }
    SET_MASK(PowSwFlag, F_PSW_UP_DELAY);
    //-------------------------------------------------------------------------
    //PCH_PWRBTN_LO();

    if (PowSwDownTimer <= FORCE_SHUTDOWN_TIME_BY_PWRBTN_ACPI_MODE)
    {
        ++PowSwDownTimer;

        if (PWRBTN_LONG_PRESS_TRIGGER_TIME_ACPI_MODE == PowSwDownTimer)
        {
            WriteSCI_Buffer(_SCIEVT_PWRBTN_LONG_PRESSED);
        }

        //forward to soc's power button to active "power button override"
        //if this can NOT work, we can try pull down all power rails
        //directly to shutdown forcedly, like on APL
        if (PowSwDownTimer >= FORCE_SHUTDOWN_TRIGGER_TIME_BY_PWRBTN_ACPI_MODE)
        {
            PCH_PWRBTN_LO();
        }
    }
    else
    {
        PowSwDownTimer = 0;

        //force shutdown directly.
        PCH_PWRBTN_HI();

        SET_MASK(PowSwFlag  , F_PSW_WAIT_UP);
        Oem_TriggerPowerOff(_ST_FORCE_SHUTDOWN);
        /* Tag Power Switch Long Time Pressed */
        BRAM[0x3B] = 0xA5;  /* SET REJECT POWER ON TAG */
        BRAM[0x3C] = 0x5A;
        BRAM[0x3D] = 0xCC;
    }

}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_G3S5_PowSwitch
 * @function - Oem_G3S5_PowSwitch
 * @upstream - Oem_SysPowState_G3->Hook_Timer10msEventA
 * @input    -
 * @return   -
 * @note     -
 */
void Oem_G3S5_PowSwitch(void)
{
    //-----------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        //-------------------------------------------------
        /* System S5:RSMRST=Hi(Need PWRBTN#),
           System G3:RSMRST=Lo
        */
        if (IS_PCH_RSMRST_HI())
        {
            PCH_PWRBTN_HI();
        }
        if (PowSwLockTimer > 0)
        {
            PowSwLockTimer--;
            return;
        }
        PowSwDebounce = 0;
        PowSwDownTimer = 0;
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        /* Clear Power Switch Long Time Pressed */
        BRAM[0x3B] = 0x00;  /* CLEAR REJECT POWER ON TAG */
        BRAM[0x3C] = 0x00;
        BRAM[0x3D] = 0x00;
        //SysPowState = _SYSTEM_S5;
        return;
    }
    //-----------------------------------------------------
    /* System S5:RSMRST=Hi(Need PWRBTN#),
       System G3:RSMRST=Lo
    */
    if (IS_PCH_RSMRST_HI())
    {
        PCH_PWRBTN_HI();
    }
    //-----------------------------------------------------
    AutoBootTimer = 0;
    SetAutoBootTimer = 0;

// Disable for SMT

//     if (IS_BATTERY1_IN() && IS_ADAPTER_OUT())
//     {   // Battery only and RSOC < 7%
//         if (BAT1_RelativeStateOfChgL < 7)
//         {
//             /* Reject Power Switch Power On when battery RSOC lower then 7% */
//             return;
//         }
//     }
    
        
//     // CCG6 PD Source Selection Reject Power On
//     if (xCCG6_RejectPwrOn == 1)
//     {
//         /* Reject Power Switch Power On */
//         return;
//     }    
    
    //-----------------------------------------------------
    // Power Switch Override Stop Power On
    // Check Tag Power Switch Long Time Pressed */
    if ((BRAM[0x3B] == 0xA5) &&
            (BRAM[0x3C] == 0x5A) &&
            (BRAM[0x3D] == 0xCC))
    {
        /* Reject Power Switch Power On */
        return;
    }
    //-----------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        if (PowSwDownTimer < 5500)  //1ms * 5500 = 5.5sec
        {
            PowSwDownTimer++;
        }
        else
        {
            PowSwDownTimer = 0;
            /* Tag Power Switch Long Time Pressed */
            BRAM[0x3B] = 0xA5;  /* SET REJECT POWER ON TAG */
            BRAM[0x3C] = 0x5A;
            BRAM[0x3D] = 0xCC;
        }
        return;
    }
    //-----------------------------------------------------
    if (PowSwLockTimer > 0)
    {
        PowSwLockTimer--;
        return;
    }
    //-----------------------------------------------------
    if (PowSwDebounce < 50)
    {
        PowSwDebounce++;    //Debounce 50ms
    }
    else
    {
        PowSwDownTimer++;
        //1ms * 50 = 50ms + 50ms debounce = 100ms power on
        if (PowSwDownTimer > 50)
        {
            // Avoid auto power on after force shutdown
            BRAM[0x3A] = 0x00;
            
            PowSwDownTimer = 0;
            PowSwDebounce = 0;
            SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
            Oem_TriggerPowerOn();
        }
    }
    //-----------------------------------------------------
}

#if 0
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_S5_PowSwitch
 * @function - Oem_S5_PowSwitch
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_S5_PowSwitch(void)
{
    //-------------------------------------------------------------------------
#if SUPPORT_LID_SWITCH
    if (IS_LID_SW_CLOSE())
    {
        return;
    }
#endif
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (PowSwLockTimer > 0)
        {
            PowSwLockTimer--;
            return;
        }
        PowSwDebounce = 0;
        PowSwDownTimer = 0;
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        return;
    }
    //-------------------------------------------------------------------------
    AutoBootTimer = 0;
    SetAutoBootTimer = 0;
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwLockTimer > 0)
    {
        PowSwLockTimer--;
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwDebounce < 5)
    {
        PowSwDebounce++;
    }
    else
    {
        PowSwDownTimer++;
        if (PowSwDownTimer > 200)
        {
            PowSwDownTimer = 0;
            PowSwDebounce = 0;
            SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
            Oem_TriggerPowerOn();
        }
    }
    //-------------------------------------------------------------------------
}
#endif

#if SUPPORT_AUTO_BOOT /* Auto Power-Test sample code */
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_AutoBoot
 * @function - Automatic Power on (Test Utility)
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_AutoBoot(void)
{
    if (((SysPowState == _SYSTEM_S0) && (wMSBY_SLP_S0_LoT < 2000)) || (SetAutoBootTimer == 0))
    {
        return;
    }
    if (AutoBootTimer == 0)
    {
        AutoBootTimer = SetAutoBootTimer;
    }
    else
    {
        AutoBootTimer--;
        if (AutoBootTimer == 0)
        {
#if INTEL_EC_FLASH_AUTO_POWER_ON
            if(BRAM[62] != 0)
            {
                SetAutoBootTimer = 0;
                BRAM[62] = 0;
            }
#endif  
            PowSwDebounce = 0;
            PowSwDownTimer = 0;
            SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
            if (SysPowState == _SYSTEM_S5)
            {
                Oem_TriggerPowerOn();
            }
            else if (SysPowState == _SYSTEM_S3)
            {
#if SUPPORT_INTERFACE_eSPI
                if (IS_eSPI_SLP_S3_LO())
                {
                    PCH_PWRBTN_LO();
                    DelayXms(20);
                    PCH_PWRBTN_HI();
                }
#else
                if (IS_PCH_SLP_S3_LO())
                {
                    PCH_PWRBTN_LO();
                    DelayXms(20);
                    PCH_PWRBTN_HI();
                }
#endif
            }
            else
            {
                if ((SysPowState == _SYSTEM_S0) && (wMSBY_SLP_S0_LoT >= 2000))
                {
                    WriteSCI_Buffer(_SCIEVT_PWRBTN);
                }
            }
        }
    }
}

BYTE Oem_AutoBoot_CheckMS(void)
{
    if (IS_EC_PWRSW_DN() || (VWIDX2 != 0x77))
    {
        return FALSE;
    }
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return FALSE;
    }

    /**
     * @brief  Check SLP_S0# keep low 2 sec
     */
    if (IS_SLP_S0_CS_HI())
    {
        wMSBY_SLP_S0_HiT++;
        if (wMSBY_SLP_S0_HiT > 10)
        {
            wMSBY_SLP_S0_LoT = 0;
        }
        return FALSE;
    }
    wMSBY_SLP_S0_HiT = 0;
    if (wMSBY_SLP_S0_LoT < 2000)
    {
        wMSBY_SLP_S0_LoT++;
        return FALSE;
    }
    return TRUE;
}
#endif
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S0_S1
 * @function - Oem_SysPowState_S0_S1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_SysPowState_S0_S1(void)
{
    if (IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
    {
         Oem_PowSwToPWRBTN_ACPI_MODE();
    }
    else
    {
       Oem_PowSwToPWRBTN_S0_S1();
    }
#if 1 //[0]:Skip power off function.
#if SUPPORT_INTERFACE_eSPI
    if ((IS_eSPI_SLP_S3_LO()) && (IS_eSPI_SLP_S4_HI()))
    {
        Set_SysPowState(_PST_S0_to_S3);
    }
    else if ((IS_eSPI_SLP_S4_LO()) && (IS_eSPI_SLP_S3_LO()))
    {
        Set_SysPowState(_PST_S0_to_S5);
    }
#else
    if ((IS_PCH_SLP_S3_LO()) && (IS_PCH_SLP_S4_HI()))
    {
        Set_SysPowState(_PST_S0_to_S3);
    }
    else if ((IS_PCH_SLP_S4_LO()) && (IS_PCH_SLP_S3_LO()))
    {
        Set_SysPowState(_PST_S0_to_S5);
    }
#endif
#endif
}
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S3
 * @function - Oem_SysPowState_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_SysPowState_S3(void)
{
     Oem_PowSwToPWRBTN_S3();
#if SUPPORT_INTERFACE_eSPI
    if (IS_eSPI_SLP_S3_HI())
    {
        Set_SysPowState(_PST_S3_to_S0);
    }
    else if ((IS_eSPI_SLP_S3_LO()) && (IS_eSPI_SLP_S4_LO()))
    {
        Set_SysPowState(_PST_S0_to_S5);
    }
#else
    if (IS_PCH_SLP_S3_HI())
    {
        Set_SysPowState(_PST_S3_to_S0);
    }
    else if ((IS_PCH_SLP_S3_LO()) && (IS_PCH_SLP_S4_LO()))
    {
        Set_SysPowState(_PST_S0_to_S5);
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S4_S5
 * @function - Oem_SysPowState_S4_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_SysPowState_S4_S5(void)
{
    /*
        by YY:
        if battery exists, we wait for fuel guage reach EARLY INIT or INIT state, then process
        power switch event

        if battery NOT exist, directly process power switch event;
    */
//  Disable for SMT
//    if (IS_BATTERY1_IN() && (IS_ADP_PRESENT_LO())
//        && IS_MASK_CLEAR(SMBB_DEV0_STS, F_DEV_EARLY_INIT|F_DEV_INIT))
//    {
//        return;
//    }
        
#if SUPPORT_SW_MIRROR
    if (EC_SW_MIRROR & SW_MIRROR_EN)
    {
        return;
    }
#endif

    if ((BRAM[0x3B] == 0xA5) &&
            (BRAM[0x3C] == 0x5A) &&
            (BRAM[0x3D] == 0xCC))
    {
        /* Reject Power Switch Power On */
        if (IS_ADP_PRESENT_HI())
        {
            Set_SysPowState(_PST_S5_to_G3);
        }
    }
    
    Oem_G3S5_PowSwitch();
    
    // Avoid auto power on after force shutdown
    if (BRAM[0x3A] == 0x5A)
    {
        return;
    }
    
#if SUPPORT_S4_S5_WAKE_UP
#if SUPPORT_INTERFACE_eSPI
    if ((IS_eSPI_SLP_S4_HI()) && (IS_eSPI_SLP_S3_HI()))
    {
        Set_SysPowState(_PST_S5_to_S0);
    }
#else
    if ((IS_PCH_SLP_S4_HI()) && (IS_PCH_SLP_S3_HI()))
    {
        Set_SysPowState(_PST_S5_to_S0);
    }
#endif
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_G3
 * @function - Oem_SysPowState_G3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_SysPowState_G3(void)
{
    if (IS_BATTERY1_IN())
    {
        if (IS_ADP_PRESENT_LO() && (BAT1_Voltage <= BAT1_SafeVoltageValue))
        {
            if (IS_EC_PWRSW_UP())
            {
                if(xPowerOnBlinkLEDEn == 0)
                {
                    xPowerOnBlinkLEDEn++;
                    LED_NotifyPowerOnFail();
                }
            }
            else
            {
                xPowerOnBlinkLEDEn = 0;
            }
            return;
        }
        Set_SysPowState(_PST_G3_to_S5);
    }
    else
    {
        if(IS_ADP_PRESENT_HI())
        {
            Set_SysPowState(_PST_G3_to_S5);
        }
        else
        {
            Oem_G3S5_PowSwitch();
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_EC_ACK_eSPI_Reset
 * @function - Hook_EC_ACK_eSPI_Reset
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_EC_ACK_eSPI_Reset(void)
{


}

/*-----------------------------------------------------------------------------
 * @subroutine - POWER_LATCH_OFF
 * @function - POWER_LATCH_OFF
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void POWER_LATCH_OFF(void)
{
    SYS_PWROK_LO();     //GPB5 /* Make sure PWROK again */
    ALL_SYS_PWRGD_LO(); //GPC5
    Delay1MS(5);
    PM_PCH_PWROK_LO();  //GPE.5
    Delay1MS(20);
    /* G3 to S5 */
    PCH_RSMRST_LO();    //GPH0
    //Delay1MS(5);
    DSW_PWROK_R_LO();   //GPC4
    Delay1MS(5);
    EC_PWR_LATCH_LO();
    Delay1MS(2000);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_PowerLatch
 * @function - Service_PowerLatch
 * @upstream - Hook_Timer1SecEventC
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_PowerLatch(void)
{
    if (IS_ADP_PRESENT_HI() ||
            IS_eSPI_SLP_S4_HI() || IS_eSPI_SLP_S3_HI() ||
            IS_EC_PWRSW_DN())
    {
        PowerLatchTimer = 10;
        return;
    }
    if (IS_BATTERY1_OUT())
    {
        return;
    }
    if (PowerLatchTimer > 0)
    {
        PowerLatchTimer--;
        return;
    }
    //-----------------------------------------------------
    BRAM[0x3B] = 0x00;  /* CLEAR REJECT POWER ON TAG */
    BRAM[0x3C] = 0x00;
    BRAM[0x3D] = 0x00;
    //-----------------------------------------------------
    /* Make sure S5 */
    SYS_PWROK_LO(); /* Make sure PWROK again */
    ALL_SYS_PWRGD_LO();
    Delay1MS(5);
    PM_PCH_PWROK_LO();
    Delay1MS(20);
    /* G3 to S5 */
    PCH_RSMRST_LO();
    //Delay1MS(5);
    DSW_PWROK_R_LO();
    Delay1MS(5);

    // force pull low PMC_SLP_SUS_N
    
    GPOTE = 0xC9;
    GPDRE = 0x8;

    GPCRE6 = OUTPUT;

    Delay1MS(5);

    EC_PWR_LATCH_LO();
    Delay1MS(2000);
    //-----------------------------------------------------
#if 0 /* TURE: for system fully discharged timing too long */
    while (1)
    {
        if (IS_ADP_PRESENT_HI() || IS_EC_PWRSW_DN())
        {
            break;
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - IsThermalShutdowmHappen
 * @function - IsThermalShutdowmHappen
 * @upstream - Hook_Timer1SecEventC
 * @input    - None
 * @return   - Thermal Shutdown Happen
 * @note     - None
 */
BYTE IsThermalShutdowmHappen(void)
{
//      if(PF_H_THRMTRIP_N_EC_LO() || IS_H_CATERR_3P3V_N_HI())
//     {
//         return (1);
//     }
    return (0);
}

//-----------------------------------------------------------------------------
/*****************************************************************************/
/*****************************************************************************/
/*-----------------------------------------------------------------------------
 *-----------+-----------------------------------------------------------------
 * @function | Service for Windows Modern Standby
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | 1.0.0.0
 * @author   | Michael.Kuo@ite.com.tw
 * @note     | Copyright(c)201-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
/*****************************************************************************/
/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * @fn         Hook_Timer1SecEventD
 * @details    Hook EC 100ms event.
 * @upstream   EC 100ms service
 * @ingroup    Before ModernStandby Loop
 */
void Hook_Timer100msEventD(void)
{


}

/*-----------------------------------------------------------------------------
 * @fn         Hook_Timer1SecEventD
 * @details    Hook EC 1 Sec event.
 * @upstream   EC 1 sec service
 * @ingroup    Before ModernStandby Loop
 */
void Hook_Timer1SecEventD(void)
{
    if (xATNA_IdleTimer  > 0)
    {
        xATNA_IdleTimer--;
    }
    if (xECPW_DeepSleepDelay > 0)
    {
        xECPW_DeepSleepDelay--;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_DeepSleep
 * @details    Check the status can switch to DeepSleep idle mode.
 * @upstream - By call
 * @ingroup    system off and battery only
 */
void CheckCanGo_DeepSleep(void)
{
#if SUPPORT_BATT_S5_EC_SLEEP
    if (IS_ADAPTER_OUT() && IS_PCH_RSMRST_LO())
    {
        if (xECPW_DeepSleepDelay == 0)
        {
            xMSBY_Mode = _EC_POWER_DOWN_IDLE;
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_DeepSleep
 * @details    Initialize the chip setting before enter the DeepSleep.
 * @upstream - By call
 * @ingroup    ModernStandby (Battery Mode with system G3 state)
 */
void InitEntry_DeepSleep(void)
{
    DisableAllInterrupt();
    /**
     * @brief  Clear PowerDownRejectTag for check interrupt comes out when
     *         doing the enable step.
     */
    F_PowerDownRejectTag = 0;

#if 0   /* 1: Support Timer Wakeup */
    /**
     * @brief  Setting 2 sec wakeup timer for service ModernStandby.
     */
    /* Prescaler 32.768KHz, count 65535 = 2s. */
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    ET2PSR = 0x00;   // Prescaler 32.768K HZ
    ET2CNTLH2R = 0x00;
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x80;

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt
#endif
    /* Power Switch */
    GPCRB3 = ALT;
    //GPCRE4 = ALT;
    WUC_Enable_WUx_Interrupt(WU25, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER1, Int_WKO25);      //PWRSW@GPB.3

    /* AC Adpater In */
    WUC_Enable_WUx_Interrupt(WU81, WUC_Rising, Wake_Up_Enable);
    SET_MASK(IER8, Int_WKO81);      //ACIN@GPA.4

    /* Lid Switch */
    //WUC_Enable_WUx_Interrupt(WU97, WUC_Rising, Wake_Up_Enable);
    //SET_MASK(IER10, Int_WKO97);    //LIDSW@GPF.1

}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_DeepSleep
 * @details    Initialize the chip setting after exit the DeepSleep.
 * @upstream - By call
 * @ingroup    ModernStandby (Battery Mode with system G3 state)
 */
void InitExit_DeepSleep(void)
{
    xMSBY_Mode = _EC_GENERAL_IDLE;
    Init_Timers();
    //SET_MASK(IER3, Int_EXTimer);
    CLEAR_MASK(IER1, Int_WKO25);
    CLEAR_MASK(IER0, Int_WKINTAD);
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_AthenaIdle
 * @details    Check the status can switch to Athena idle mode.
 * @upstream - By call
 * @ingroup    ModernStandby (S0 Screen on power saving)
 */
BYTE CheckCanGo_AthenaIdle(void)
{
    /* Check I2C and Fan PWM need service */
#if SUPPORT_FAN1_CONTROL
    if ((CPU_PWM_FAN_DCR > 0) || (SMBB_CHN_STS & F_SMB_BUSY))
#else
    if (SMBB_CHN_STS & F_SMB_BUSY)
#endif
    {
        return FALSE;
    }
    if (IS_ADAPTER_IN() || IS_EC_PWRSW_DN())
    {
        xATNA_IdleTimer = _EC_ENTRY_ATHENA_TIME;
        return FALSE;
    }
    if (AnyKeyDownFlag)
    {
        xATNA_IdleTimer = _EC_ENTRY_ATHENA_TIME;
        AnyKeyDownFlag = 0;
        return FALSE;
    }
    if (xATNA_IdleTimer > 0)
    {
        return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @fn         CheckExit_AthenaIdle
 * @details    Check the status can exit to Athena idle mode.
 * @upstream - By call
 * @ingroup    ModernStandby (S0 Screen on power saving)
 */
BYTE CheckExit_AthenaIdle(void)
{
    if (IS_ADAPTER_IN() || IS_EC_PWRSW_DN())
    {
        return TRUE;
    }
    
#if SUPPORT_FAN1_CONTROL
    if (CPU_PWM_FAN_DCR > 0)
    {
        return TRUE;
    }
#endif

    if (AnyKeyDownFlag)
    {
        AnyKeyDownFlag = 0;
        return TRUE;
    }
    
    if (IS_VOLUME_UP_DN() || IS_VOLUME_DOWN_DN())
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_AthenaIdle
 * @details    Initialize the chip setting before enter the Athena idle.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_AthenaIdle(void)
{
    /**
     * @brief  Turns-off ADC/PWM clock.
     */
    CLEAR_MASK(ADCCFG, ADCEN);
    CLEAR_MASK(ZTIER, BIT1);
    DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /**
     * @brief  Clear PowerDownRejectTag for check interrupt comes out when
     *         doing the enable step.
     */
    F_PowerDownRejectTag = 0;
    /* Prescaler 1KHz, count 102 = 10ms. */
    ET2PSR = ET2_SOURCE_1024Hz;   // Prescaler 1KHz
    ET2CNTLH2R = 0x00;
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 102;

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt

    WUC_Enable_WUx_Interrupt(WU25, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER1, Int_WKO25);      //PWRSW@GPB.3

    /**
     * @brief  Latest enable important Host eSPI/LPC Bus interrupt.
     */
    SET_MASK(IER3, Int_KBCIBF);     //REG@1107.0
    SET_MASK(IER3, Int_PMCIBF);     //REG@1107.1
    WUC_Enable_WUx_Interrupt(WU42, WUC_Falling, Wake_Up_Enable);
    ISR0 = Int_WKINTAD;  //REG@1100.5
    SET_MASK(IER0, Int_WKINTAD);  //REG@1104.5 LPC|eSPI
}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_AthenaIdle
 * @details    Initialize the chip setting after wake up from Athena idle.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitWake_AthenaIdle(void)
{
    /* Enable ADC */
    SET_MASK(ADCCFG, ADCEN);
    /* Enable PWM */
    SET_MASK(ZTIER, BIT1);
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    //SET_MASK(IER3, Int_EXTimer);
    CLEAR_MASK(IER1, Int_WKO25);
    CLEAR_MASK(IER0, Int_WKINTAD);
    /* Wakeup by system event -> exit Athena idle */
    if (F_Service_PCI || F_Service_PCI2 ||
            (F_Service_KEY) || (VWIDX2 != 0x77))
    {
        xMSBY_Mode = _EC_GENERAL_IDLE;
        xATNA_IdleTimer = _EC_ENTRY_ATHENA_TIME;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_ModernStandby
 * @details    Initialize the chip setting before enter the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_S3ModernStandby(void)
{
    /**
     * @brief  Enable Lid wake up before entry Modern Standby.
     */
    if (IS_LID_SW_CLOSE())
    {
        xMSBY_EnLidOpenWake = 1;
        /* Lid State (Lid Open = 1) */
//         CLEAR_MASK(xEC_PWER, F_PWER_LSTE);
    }
    /**
     * @brief  Turns-off PECI, pull Low is better.
     */
    //GPCRF6 = OUTPUT;
    //PECI_EC_LO();
    /**
     * @brief  Turns-off ADC/PWM clock.
     */
    CLEAR_MASK(ADCCFG, ADCEN);
    CLEAR_MASK(ZTIER, BIT1);
    DCR0 = 0;
    xMSBY_ExitKey = 0;
    
    DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /**
     * @brief  Clear PowerDownRejectTag for check interrupt comes out when
     *         doing the enable step.
     */
    F_PowerDownRejectTag = 0;
    /**
     * @brief  Setting 2 sec wakeup timer for service ModernStandby.
     */
    /* Prescaler 32.768KHz, count 65535 = 2s. */
    ET2PSR = 0x00;   // Prescaler 32.768K HZ
    ET2CNTLH2R = 0x01;
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x00;
    
#if 1
    WUC_Enable_WUx_Interrupt(WU25, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER1, Int_WKO25);      //PWRSW@GPE.4

    WUC_Enable_WUx_Interrupt(WU105, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER13, Int_WKO105);      //PD2_INTP_OUT@GPB.6
    
    WUC_Enable_WUx_Interrupt(WU86, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER11, Int_WKO86);      //PD1_INTP_OUT@GPC.7
    
    /**
     * @brief  Latest enable important Host eSPI/LPC Bus interrupt.
     */
    SET_MASK(IER3, Int_KBCIBF);     //REG@1107.0
    SET_MASK(IER3, Int_PMCIBF);     //REG@1107.1
    WUC_Enable_WUx_Interrupt(WU42, WUC_Falling, Wake_Up_Enable);
    ISR0 = Int_WKINTAD;  //REG@1100.5
    SET_MASK(IER0, Int_WKINTAD);  //REG@1104.5 LPC|eSPI
#endif

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt
}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_S3ModernStandby
 * @details    Initialize the chip setting after exit the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitExit_S3ModernStandby(void)
{
    DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /* Prescaler 32.768KHz, count 65535 = 2s. */
    ET2PSR = 0x00;   // Prescaler 32.768K HZ
    ET2CNTLH2R = 0x00;
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x80;

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt

    Init_Timers();
    
    /* Enable ADC */
    SET_MASK(ADCCFG, ADCEN);
    /* Enable PWM */
    SET_MASK(ZTIER, BIT1);
    DCR0 = 0x50;
    Init_Timers();
    SET_MASK(IER3, Int_EXTimer);
    CLEAR_MASK(IER1, Int_WKO25);
    CLEAR_MASK(IER0, Int_WKINTAD);
    CLEAR_MASK(IER13, Int_WKO105);
    CLEAR_MASK(IER11, Int_WKO86);
    
    HookMS_CheckS3ExitCondition();
    if (xMSBY_ExitKey != 0x00)
    {
        xMSBY_Mode = _EC_GENERAL_IDLE;
    }
    else
    {
        xMSBY_Mode = _EC_S3_POWER_SAVING;
    }
    SMBB_DEV0_DLY = 0;  // Quick polling battery
    wMSBY_EnterDelay = 100;     //100ms enter again
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetThermalStatus
 * @details    Get thermal status in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_CheckS3ExitCondition(void)
{
    HookMS_CheckLidStatus();     
           
    if (IS_ADP_PRESENT_HI())
    {
        SET_ExitMS(0xAC, 8);
        return;
    }
    if (xEC_Battery4PWakeup == 1)
    {
        if (xEC_Bt1RSOC <= 4)
        {
            xEC_Battery4PWakeup = 0;
            PCH_PWRBTN_LO();
            Delay1MS(20);
            PCH_PWRBTN_HI();
        }
    }
//     if (IS_PD1_INTP_OUT_LO() || IS_PD2_INTP_OUT_LO())
//     {
//         SET_ExitMS(0xCC, 8);
//         return;
//     }
    
    if(IS_MASK_SET(xMSBY_WakeUpFlag, eSPI))
    {
        SET_ExitMS(0xE2, 8);
        CLEAR_MASK(xMSBY_WakeUpFlag, eSPI);
        return;
    }
        
    if (IS_LID_SW_OPEN())
    {        
        if (IS_EC_PWRSW_DN())
        {
            SET_ExitMS(0xBB, 2);
            return;
        }
    
//         if (IS_GPI_KEYDN_WIN())
//         {
//             SET_ExitMS(0xD1, 8);
//             return;
//         }
        
        if (F_Service_KEY)
        {
            SET_ExitMS(0x61, 4);
            return;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_ModernStandby
 * @details    Initialize the chip setting before enter the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_ModernStandby(void)
{
    /**
     * @brief  Enable Lid wake up before entry Modern Standby.
     */
    if (IS_LID_SW_CLOSE())
    {
        xMSBY_EnLidOpenWake = 1;
        /* Lid State (Lid Open = 1) */
        //CLEAR_MASK(xEC_PWER, F_PWER_LSTE);
    }
    /**
     * @brief  Turns-off PECI, pull Low is better.
     */
#if SUPPORT_PECI
    GPCRF6 = OUTPUT;
    CLEAR_MASK(GPDRF, BIT(6));
#endif
    Hook_NUMLED_OFF();
    Hook_CAPLED_OFF();
    /**
     * @brief  Turns-off ADC/PWM clock.
     */
    CLEAR_MASK(ADCCFG, ADCEN);
#if SUPPORT_FAN1_CONTROL
    CPU_PWM_FAN_DCR = 0;
#endif
    CLEAR_MASK(ZTIER, BIT1);
    xMSBY_ExitKey = 0;
    wMSBY_SLP_S0_HiT = 0;
}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_ModernStandby
 * @details    Initialize the chip setting after exit the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitExit_ModernStandby(void)
{
    OEM_Write_Leds(Led_Data);   //Hook Oem On-board LED control
    /* Enable ADC */
    SET_MASK(ADCCFG, ADCEN);
    /* Enable PWM */
    SET_MASK(ZTIER, BIT1);
#if SUPPORT_FAN1_CONTROL
    CPU_PWM_FAN_DCR = 0x50;
#endif
    Init_Timers();
    //SET_MASK(IER3, Int_EXTimer);
    CLEAR_MASK(IER1, Int_WKO25);
    CLEAR_MASK(IER0, Int_WKINTAD);
}

/*-----------------------------------------------------------------------------
 * @fn         SET_ExitMS
 * @details    Set exit ModernStandby with Exit Code.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void SET_ExitMS(BYTE ExitCode, BYTE ExitTsec)
{
    xMSBY_ExitKey = ExitCode;
    xMSBY_ServiceKey = 0xFF;
    wMSBY_EnterDelay = ExitTsec * 1000;
}

/*-----------------------------------------------------------------------------
 * @fn         InitSleep_ModernStandby
 * @details    Initialize the chip setting before enter the Chip power down.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitSleep_ModernStandby(void)
{
    DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /**
     * @brief  Clear PowerDownRejectTag for check interrupt comes out when
     *         doing the enable step.
     */
    F_PowerDownRejectTag = 0;
    /**
     * @brief  Setting 2 sec wakeup timer for service ModernStandby.
     */
    /* Prescaler 32.768KHz, count 65535 = 2s. */
    ET2PSR = 0x00;   // Prescaler 32.768K HZ
    ET2CNTLH2R = 0x01;
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x00;
#if 1
    ISR7 = Int_ET2Intr;             // Write to clear external timer 2 interrupt
    SET_MASK(IER7, Int_ET2Intr);    // Enable external timer 2 interrupt
#endif
#if 1
    WUC_Enable_WUx_Interrupt(WU25, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER1, Int_WKO25);      //PWRSW@GPB.3

    /**
     * @brief  Latest enable important Host eSPI/LPC Bus interrupt.
     */
    SET_MASK(IER3, Int_KBCIBF);     //REG@1107.0
    SET_MASK(IER3, Int_PMCIBF);     //REG@1107.1
    WUC_Enable_WUx_Interrupt(WU42, WUC_Falling, Wake_Up_Enable);
    ISR0 = Int_WKINTAD;  //REG@1100.5
    SET_MASK(IER0, Int_WKINTAD);  //REG@1104.5 LPC|eSPI
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         InitWake_ModernStandby
 * @details    Initialize the chip setting after exit the Chip power down.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitWake_ModernStandby(void)
{
    DisableAllInterrupt();

    ISR7 = Int_ET2Intr;             // Write to clear external timer 2 interrupt
    CLEAR_MASK(IER7, Int_ET2Intr);  // Enable external timer 2 interrupt

    Init_Timers();
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_ModernStandby
 * @details    Check the status can switch to Modern Standby mode.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
BYTE CheckCanGo_ModernStandby(void)
{
    if (IS_EC_PWRSW_DN() || (VWIDX2 != 0x77))
    {
        return FALSE;
    }
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return FALSE;
    }
    
    if (IS_ADP_PRESENT_HI())
    {
        return FALSE;
    }  
    
    if (wMSBY_EnterDelay > 0)
    {
        wMSBY_EnterDelay--;
        return FALSE;
    }
    /**
     * @brief  Check SLP_S0# keep low 2 sec
     */
    if (IS_SLP_S0_CS_HI())
    {
        wMSBY_SLP_S0_HiT++;
#if 0   /* Depends on system SLP_S0 Hi Lo pulse status. */
        wMSBY_SLP_S0_LoT = 0;
#else
        if (wMSBY_SLP_S0_HiT > 10)
        {
            wMSBY_SLP_S0_LoT = 0;
        }
#endif
        return FALSE;
    }
    wMSBY_SLP_S0_HiT = 0;
    if (wMSBY_SLP_S0_LoT < 2000)
    {
        if (xMSBY_Mode == _EC_ATHENA_IDLE)
        {
            /* _EC_ATHENA_IDLE: 10ms Base */
            wMSBY_SLP_S0_LoT += 10;
        }
        else
        {
            /* _EC_GENERAL_IDLE: 1ms Base */
            wMSBY_SLP_S0_LoT++;
        }
        return FALSE;
    }
    xMSBY_Mode = _EC_MODERN_STANDBY;
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_S3ModernStandby
 * @details    Check the status can switch to S3 Modern Standby mode.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void CheckCanGo_S3ModernStandby(void)
{
    if (IS_EC_PWRSW_DN())
    {
        return;
    }
    
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return;
    }
    
    if (IS_ADP_PRESENT_HI())
    {
        return;
    }    
    
    if (wMSBY_EnterDelay > 0)
    {
        wMSBY_EnterDelay--;
        return;
    }
    
    /**
     * @brief  Check SLP_S0# keep low 2 sec
     */
//     if (SysPowState != _SYSTEM_S3)
    if (IS_eSPI_SLP_S3_HI())
    {
        wMSBY_SLP_S3_LoT = 0;
        return;
    }
	
    xEC_Battery4PWakeup = 0;
    if (xEC_Bt1RSOC > 4)
    {
        xEC_Battery4PWakeup = 1;
    } 	
    if (wMSBY_SLP_S3_LoT < 2000)
    {
        wMSBY_SLP_S3_LoT++;
        return;
    }
    xMSBY_Mode = _EC_S3_POWER_SAVING;
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_CheckLidStatus
 * @details    Check Lid Stats in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_CheckLidStatus(void)
{
    if(xMSBY_EnLidOpenWake == 0)
    {
        if (IS_LID_SW_CLOSE())
        {
            xMSBY_EnLidOpenWake = 1;
            SET_ExitMS(0x1D, 4);
            WriteSCI_Buffer(_SCIEVT_LID_CLOSED);
            OEM_ACPI_Gen_Int();
            /* Lid State (Lid Closed = 0) */
            //CLEAR_MASK(xEC_PWER, F_PWER_LSTE);
        }
    }
    else
    {
        if (IS_LID_SW_OPEN())
        {
            /* Lid State (Lid Open = 1) */
            //SET_MASK(xEC_PWER, F_PWER_LSTE);
            if (xMSBY_EnLidOpenWake > 0)
            {
                xMSBY_EnLidOpenWake = 0;
                SET_ExitMS(0x1D, 4);
                WriteSCI_Buffer(_SCIEVT_LID_OPEN); 
                OEM_ACPI_Gen_Int(); 
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_DeviceContrlA
 * @details    Device Control in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_DeviceContrlA(void)
{
#if 0
    /**
     * @brief  Process Intel RVP Debug LED.
     */
    if ((Last_P81HDR != P81HDR) || (Last_P80HDR != P80HDR))
    {
        Process_DebugCodeLED();
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetBatteryStatus
 * @details    Get Battery status in ModernStandby wakeup service.
 * @upstream - By call - Sleep Duty: 2sec
 * @ingroup    ModernStandby
 */
void HookMS_GetBatteryStatus(void)
{

#ifdef _SUPPORT_BATT_FAKE_INFO_

    return ;
    
#endif
#if 1
    if (IS_MASK_CLEAR(xEC_PowerState , F_BAT1_PRESENT))
    {
        return;
    }
    
    if(wMSBY_BatteryPollingDelay > 0)
    {
        wMSBY_BatteryPollingDelay--;
        return;
    }
    xMSBY_GetBatteryStep++;
    wMSBY_BatteryPollingDelay = 10;
    if (xMSBY_GetBatteryStep == 1)
    {
        bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
                 _CMD_RemainingCapacity,
                 &I2C_BUF0[0],
                 0);
        BAT1_RemainingCapacity = (I2C_BUF0[1] << 8) +
                                 I2C_BUF0[0];
    }
    else if (xMSBY_GetBatteryStep == 2)
    {
        bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
                 _CMD_FullChargeCapacity,
                 &I2C_BUF0[0],
                 0);
        BAT1_FullChargeCapacity = (I2C_BUF0[1] << 8) +
                                  I2C_BUF0[0];
    }
    else if (xMSBY_GetBatteryStep == 3)
    {
        bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
                 _CMD_Current,
                 &I2C_BUF0[0],
                 0);
        BAT1_Current = (I2C_BUF0[1] << 8) +
                       I2C_BUF0[0];
    }
    else if (xMSBY_GetBatteryStep == 4)
    {
        bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
                 _CMD_RelativeStateOfCharge,
                 &I2C_BUF0[0],
                 0);
        BAT1_RelativeStateOfChgL = I2C_BUF0[0];

    }
    else
    {
        Update_ACPI_BST1();
        xMSBY_GetBatteryStep = 0;
    }
#endif

    CheckForceShutdownByBatteryVoltage();
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetThermalStatus
 * @details    Get thermal status in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_GetThermalStatus(void)
{
    /* Check critical thermal condition in ModernStandby */
    xMSBY_GetThermalStep++;
    if (xMSBY_GetThermalStep == 1)
    {

    }
    else if (xMSBY_GetThermalStep == 2)
    {

    }
    else
    {
        xMSBY_GetThermalStep = 0;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetThermalStatus
 * @details    Get thermal status in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_CheckExitCondition(void)
{
    if (IS_LID_SW_OPEN())
    {
        if (IS_EC_PWRSW_DN())
        {
            SET_ExitMS(0xBB, 4);
            return;
        }
    }
    
    if (IS_ADP_PRESENT_HI())
    {
        SET_ExitMS(0xAC, 8);
        return;
    }
    
    //if (IS_PD1_INTP_OUT_LO() || IS_PD2_INTP_OUT_LO())
    //{
    //    SET_ExitMS(0xCC, 8);
    //    return;
    //}
    
    //if (IS_GPI_KEYDN_WIN())
    //{
    //    SET_ExitMS(0xD1, 8);
    //    return;
    //}
    
    if (xEC_ShutdownCode == _ST_FORCE_SHUTDOWN)
    {
        SET_ExitMS(0xE1, 8);
        return;
    }
    
#if 1   // 0:Single EC Board Test (Without Host)
    if (VWIDX2 != 0x77)     /* System Keep S0 = 0x77 */
    {
        SET_ExitMS(0x77, 20);
        return;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         Hook_ModernStandbyService1ms
 * @details    Do the 1ms service steps after Wake from Modern Standby.
 * @upstream - By call
 * @ingroup    ModernStandby
 * @retval     End of service (enter power down) -> xMSBY_ServiceKey = 0
 * @retval     Keep in ModernStandby -> xMSBY_ExitKey = 0
 */
void Hook_ModernStandbyService1ms(void)
{
    if (xMSBY_SleepDelay > 0)
    {
        xMSBY_SleepDelay--;
    }
    switch (xMSBY_ServiceKey)
    {
    case 0:
        HookMS_CheckLidStatus();
        xMSBY_ServiceKey++;
        break;

    case 1:
        HookMS_DeviceContrlA();
        xMSBY_ServiceKey++;
        break;

    case 2:
        HookMS_GetBatteryStatus();
        xMSBY_ServiceKey++;
        break;

    case 3:
        HookMS_GetThermalStatus();
        xMSBY_ServiceKey++;
        break;

    case 4:
        HookMS_CheckExitCondition();
        xMSBY_ServiceKey++;
        break;

    default:
        if (IS_SLP_S0_CS_HI())
        {
            if (wMSBY_SLP_S0_HiT < 1000)    /* Detect SLP_S0# Hi 1sec */
            {
                wMSBY_SLP_S0_HiT++;
            }
            else
            {
                SET_ExitMS(0x51, 4);
            }
        }
        else
        {
            wMSBY_SLP_S0_HiT = 0;
            xMSBY_ServiceKey = 0xFF;    /* GoTo Sleep */
        }
        break;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         Hook_ModernStandbyService
 * @details    Do the loop service after Wake from Modern Standby.
 * @upstream - By call
 * @ingroup    ModernStandby
 * @retval     End of service (enter power down) -> xMSBY_ServiceKey = 0
 * @retval     Keep in ModernStandby -> xMSBY_ExitKey = 0
 */
void Hook_ModernStandbyService(void)
{
    xMSBY_ServiceKey = 0;
    while (1)
    {
        //xEC_CMDR = 0; /* Clear Intel MailBox command */
        /**
        * @brief  ACK eSPI Bus hand shake.
        */
        EC_ACK_eSPI_Reset();
        /**
        * @brief  Process Host Command/Data and setting 20ms delay into
        *         power down for quickly response next command.
        */
        if (IS_MASK_SET(KBHISR, P_IBF))
        {
            service_pci1();
            xMSBY_SleepDelay = 10;  /* Host command/data delay 10ms */
            continue;
        }
        if (IS_MASK_SET(PM1STS, P_IBF))
        {
            SetTotalBurstTime();
            service_pci2f();
            xMSBY_SleepDelay = 10;  /* Host command/data delay 10ms */
            continue;
        }
        if (F_Service_MS_1)
        {
            F_Service_MS_1 = 0;
            Hook_ModernStandbyService1ms();
            service_Low_LVEvent();
        }
        if (F_Service_KEY)
        {
            SET_ExitMS(0x60, 4);
        }
        if ((xMSBY_ExitKey != 0x00) ||
                (xMSBY_ServiceKey == 0xFF))
        {
            break;
        }
        EnableModuleInterrupt();
        xMSBY_DozeCounter++;
        PCON = 1;       // enter idle mode
        /* Wake-up Delay */
        _nop_();        /* 1st // Repeat "nop" eight times immediately */
        _nop_();        /* 2nd // for internal bus turn-around. */
        _nop_();        /* 3rd */
        _nop_();        /* 4th */
        _nop_();        /* 5th */
        _nop_();        /* 6th */
        _nop_();        /* 7th */
        _nop_();        /* 8th */
    }
}
void PF_TrggerSOCPwrBtn(BYTE Reason)
{
    PCH_PWRBTN_LO();
    DelayXms(100);
    PCH_PWRBTN_HI();

    Power_RamDebug(0xB1);
    Power_RamDebug(Reason);
    Power_RamDebug(0xB1);
}


//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_POWER.C */