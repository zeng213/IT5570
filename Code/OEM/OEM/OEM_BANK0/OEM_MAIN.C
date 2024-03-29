/*-----------------------------------------------------------------------------
 * @file     | OEM_MAIN.C
 * ----------+-----------------------------------------------------------------
 * @function | OEM Kernel bridge link
 * ----------+-----------------------------------------------------------------
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
#define SUPPORT_APP_PL12_CONTROL    FALSE   // Intel Lab Test Only

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1ms events
// EventId is 0 ~ 9 cycle
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1msEvent(IBYTE EventId)
{
    //-------------------------------------------------------------------------
    // Power Status Branch
    //-------------------------------------------------------------------------
    if ((SysPowState == _SYSTEM_S0) || (SysPowState == _SYSTEM_S1))
    {
        Oem_SysPowState_S0_S1();
    }
    else if (SysPowState == _SYSTEM_S3)
    {
        Oem_SysPowState_S3();
        CheckForceShutdownByBatteryVoltage();
    }
    else if ((SysPowState == _SYSTEM_S4) || (SysPowState == _SYSTEM_S5))
    {
#if SUPPORT_SW_MIRROR
        if (IS_MASK_CLEAR(EC_SW_MIRROR, SW_MIRROR_EN))
        {
            Oem_SysPowState_S4_S5();
        }
#else
        Oem_SysPowState_S4_S5();
#endif
    }
    else if (IS_MASK_CLEAR(SysPowState, F_PST_BUSY))
    {
        Oem_SysPowState_G3();
    }
    //-------------------------------------------------------------------------
    // System Power Control
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(SysPowState, F_PST_BUSY))
    {
        Oem_SysPowSequence();       // System Power Control
    }
    else
    {
        if (EventId & 0x01)
        {
            /* Divide Timer2msEvent */
            SMBusA_ScanCenter();
        }
        else
        {
            /* Divide Timer2msEvent */
            SMBusB_ScanCenter();    // PollSmartCharger,PollSmartBattery
        }
    }
    if (IS_TYPEC_I2C_INT1_LO())     //GPC.3 Lo: PD1 Interrupt
    {
        xOOB_PauseTimer = _PD_INT_OOB_DELAY;
    }
#if SUPPORT_OOB_CRASHLOG_KEY
    // Special key for CrashLog
    if (IS_MASK_SET(xOOB_KEY_CRASHLOG, KEY_FCD_LOCK) &&
            IS_MASK_SET(xOOB_KEY_CRASHLOG, KEY_FLD_LOCK))
    {
        if (xOOB_GetCrashLogLock ==  0)
        {
            xOOB_GET_CRASHLOG = 1;
            xOOB_GetCrashLogLock = 1;
            xOOB_RemindGetCrashLogLED = 0;
        }
        CLEAR_MASK(xOOB_KEY_CRASHLOG, KEY_FCD_LOCK);
        CLEAR_MASK(xOOB_KEY_CRASHLOG, KEY_FCD_LOCK);
    }
    
    if((SysPowState == _SYSTEM_S0) && IS_H_CATERR_3P3V_N_HI())
    {
            xOOB_RemindGetCrashLogLED = 1;
    }
        
#endif

    ADP_Debounce++;
    if(ADP_Debounce > 1)
    {
        ADP_Control();
        ADP_Debounce = 0;
    }
    //---------------------------------------------------------------------
    // System Battery Low Pin Control
    //---------------------------------------------------------------------
    if (IS_BATTERY1_OUT() || IS_ADP_PRESENT_HI())
    {
        if (IS_BATLOW_N_LO())
        {
            BATLOW_N_HI();
        }
    }
    else
    {

        if (IS_MASK_SET(SMBB_DEV0_STS, F_DEV_EARLY_INIT|F_DEV_INIT))
        {
            if ((BAT1_Voltage < LOW_BATTERY_VOLTAGE) || (xEC_Bt1RSOC <= 2))
            {
                BATLOW_N_LO();
            }
            else
            {
                BATLOW_N_HI();
            }
        }
    }
#if SUPPORT_AUTO_BOOT /* Auto Power-Test sample code */
#if !SUPPORT_MODERN_STANDBY
    Oem_AutoBoot_CheckMS();
#endif
#endif
}
/*-----------------------------------------------------------------------------
 * @subroutine - APP_PL12_ControlA
 * @function - Support application control PL12
 * @upstream - Hook_Timer5msEvent
 * @input    - None
 * @return   - None
 * @note     - None
 */
#if SUPPORT_APP_PL12_CONTROL
void APP_PL12_ControlA(void)
{
    if (BRAM[_PL_WR_GO] > 0)
    {
        if (BRAM[_PL_WR_GO] == _PL_RW_PL1)
        {
            PECI_WritePowerLimit1(BRAM[_PLx_WR_ADDR], BRAM[_PLxT_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _PL_RW_PL2)
        {
            PECI_WritePowerLimit2(BRAM[_PLx_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _PL_RW_PL3)
        {
            PECI_WritePowerLimit3(BRAM[_PLx_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _PL_RW_PL4)
        {
            PECI_WritePowerLimit4(BRAM[_PLx_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _OOB_PL_RW_PL1)
        {
            OOB_PECI_WritePowerLimit1(BRAM[_PLx_WR_ADDR], BRAM[_PLxT_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _OOB_PL_RW_PL2)
        {
            OOB_PECI_WritePowerLimit2(BRAM[_PLx_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _OOB_PL_RW_PL3)
        {
            OOB_PECI_WritePowerLimit3(BRAM[_PLx_WR_ADDR]);
        }
        else if (BRAM[_PL_WR_GO] == _OOB_PL_RW_PL4)
        {
            OOB_PECI_WritePowerLimit4(BRAM[_PLx_WR_ADDR]);
        }

        BRAM[_PL_WR_GO] = 0;
    }
    if (BRAM[_PL_RD_GO] > 0)
    {
        if (BRAM[_PL_RD_GO] == _PL_RW_PL1)
        {
            PECI_ReadPowerLimit1();
        }
        else if (BRAM[_PL_RD_GO] == _PL_RW_PL2)
        {
            PECI_ReadPowerLimit2();
        }
        else if (BRAM[_PL_RD_GO] == _PL_RW_PL3)
        {
            PECI_ReadPowerLimit3();
        }
        else if (BRAM[_PL_RD_GO] == _PL_RW_PL4)
        {
            PECI_ReadPowerLimit4();
        }
        else if (BRAM[_PL_RD_GO] == _OOB_PL_RW_PL1)
        {
            OOB_PECI_ReadPowerLimit1();
        }
        else if (BRAM[_PL_RD_GO] == _OOB_PL_RW_PL2)
        {
            OOB_PECI_ReadPowerLimit2();
        }
        else if (BRAM[_PL_RD_GO] == _OOB_PL_RW_PL3)
        {
            OOB_PECI_ReadPowerLimit3();
        }
        else if (BRAM[_PL_RD_GO] == _OOB_PL_RW_PL4)
        {
            OOB_PECI_ReadPowerLimit4();
        }
        else
        {
            PECI_ReadPowerLimit1();
            PECI_ReadPowerLimit2();
            PECI_ReadPowerLimit3();
            PECI_ReadPowerLimit4();
        }
        BRAM[_PL1_RD_ADDR] = PECI_PowerLimit1;
        BRAM[_PL1T_RD_ADDR] = PECI_PowerLimit1T;
        BRAM[_PL2_RD_ADDR] = PECI_PowerLimit2;
        BRAM[_PL3_RD_ADDR] = PECI_PowerLimit3;
        BRAM[_PL4_RD_ADDR] = PECI_PowerLimit4;
        BRAM[_PL_RD_GO] = 0;
    }
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 5ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer5msEvent(void)
{
#if SUPPORT_PD_CHIP_ITE  
	service_ucsi();
#endif

#if SUPPORT_APP_PL12_CONTROL
    /* For Intel internal tools only */
    APP_PL12_ControlA();
#endif

#if SUPPORT_OOB_CRASHLOG
    /* Need Intel assign project to open. */
    if (xOOB_GET_CRASHLOG > 0)
    {
        Get_OOB_PMC_CrashLog();
    }
#endif
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 10ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer10msEventA(void)
{
    Service_Scan_ADC();
    
#if SUPPORT_SAR_EVENT_TRIGGER
    SAR_EventTrigger();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 10ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer10msEventB(void)
{
    SCI_EventCenter();
    if (xOOB_PauseTimer > 0)
    {
        xOOB_PauseTimer--;
        if (xOOB_PauseTimer == 0)
        {
            xOOB_Scan = 0;
            xOOB_GetPCH_Temper = 5;
            xOOB_GetPCH_RTC_Timer = 120;
            xOOB_PeciGetCpuT_Timer = 2;
        }
    }
    
    if (xEC_StateTimer > 0)
    {
        xEC_StateTimer--;
        if (xEC_StateTimer == 0)
        {
            if(IS_EC_STATE_LO())
            {
                EC_STATE_HI();
            }
        }
    }
    
#if SUPPORT_PD_CHIP_FLASH_ITE
    if (xITEPD_FlashUtilityEnable > 0)
    {
        ITE_PD_FlashUtility();
    }
#endif 

#if SUPPORT_DOCK_EVENT_TRIGGER
    Service_DOCK_Event();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventA(void)
{
    Adapter_Detection();
    /* System Battery Low Pin Control */
    if (IS_ADAPTER_IN() && IS_PCH_RSMRST_HI())
    {
        BATLOW_N_HI();
        AC_PRESENT_HI();
    }
    else
    {
        //AC_PRESENT_LO();
#if 0
        if (BAT1_Voltage > 6000)
        {
            BATLOW_N_HI();
        }
        else
        {
            BATLOW_N_LO();
        }
#endif
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventB(void)
{
    Battery_Detection();
	Service_GPI_Event();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventC(void)
{
    Service_LED_Indicator();
    
    if (IS_MASK_SET(HOST_BIOS_REG1, F_ME_UNLOCK))
    {
        Hook_ME_UNLOCK();
    }
#if SUPPORT_UART_BATT_MONITOR
    Service_UartBatteryMonitor();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventA(void)
{
// For AMP_EN workaround start
    if(xAMP_EN_TestTimer > 0)
    {
        xAMP_EN_TestTimer--;
        if(xAMP_EN_TestTimer == 0)
        {
            AMP_EN_HI();
        }
    }
// For AMP_EN workaround end
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventB(void)
{
    SCI_PowerEvent();
#if SUPPORT_LID_SWITCH
    Process_LID_Switch();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventC(void)
{
    if (xOOB_GET_CRASHLOG > 0)
    {
        return;
    }
    if (xOOB_PauseTimer == 0)
    {
        Service_OOB_Message();
    }

#if SUPPORT_PECI
    if (SysPowState == _SYSTEM_S0)
    {
        Service_PECI();
#if 0
        Service_PECI_Command();
        while (PECI_FLAG & F_PECI_BUSY)
        {
            Service_PECI_Data();
        }
#endif
        xEC_PECI_CPU_T = PECI_CPU_T;
        if (xEC_PECI_CPU_T >= xEC_Sensor_1_T)
        {
            xEC_PLMX_T = xEC_PECI_CPU_T;
        }
        else
        {
            xEC_PLMX_T = xEC_Sensor_1_T;
        }
    }
    else
    {
        PECI_FLAG = 0;
    }
#endif  //SUPPORT_PECI
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventA(void)
{
    Get_ADC0_Thermistor();
    Service_DPTF_Event();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventB(void)
{
    Get_ADC1_Thermistor();
    
#if SUPPORT_SINK_SOURCE_SWITCH
    /* Init NXP NX20P3483UK sink/source combo switch */
    NXP_Init();
#endif
   CheckShutdownTemp();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventC(void)
{
    Get_ADC4_Thermistor();
}

#if SUPPORT_SW_MIRROR
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// OEM_SW_Mirror
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void OEM_SW_Mirror(void)
{
    PF_PWR_LED_OFF();
    /* Close RSMRST# & Standby Power */
    RSTS = 0x84;
    SYS_PWROK_LO();     //GPB5 /* Make sure PWROK again */
    ALL_SYS_PWRGD_LO(); //GPC5
    Delay1MS(5);
    PM_PCH_PWROK_LO();  //GPE.5
    Delay1MS(20);
    /* G3 to S5 */
    PCH_RSMRST_LO();    //GPH0
    DSW_PWROK_R_LO();   //GPC4
    PCH_PWRBTN_LO();
    AC_PRESENT_LO();
    GPCRD2 = OUTPUT;    //GPD2
    CLEAR_MASK(GPDRD, BIT(2));
    Delay1MS(5);
    EC_PWR_LATCH_LO();
    Delay1MS(200);
    FLHCTRL3R = (AUTO_LOAD_AFTER_WDT + FIFE);
    ETWCFG = EWDKEYEN;
    EWDKEYR = 0x5A;
    while (1);
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventA(void)
{
    Update_ACPI_Battery();

#if SUPPORT_SW_MIRROR
    if (SysPowState == _SYSTEM_S5)
    {
        if (EC_SW_MIRROR & SW_MIRROR_EN)
        {
            if (EC_SW_MIRROR_DELAY)
            {
                EC_SW_MIRROR_DELAY--;
                if (EC_SW_MIRROR_DELAY == 0)
                {
                    EC_SW_MIRROR = 0;
                    OEM_SW_Mirror();
                }
            }
        }
    }
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventB(void)
{
#if SUPPORT_FAN1_TACH
    wFan1_CurrentRPM = GetFanRPM(F1TMRR, F1TLRR);
    xEC_Debug_Fan1Rpm = wFan1_CurrentRPM;
#endif
#if SUPPORT_FAN1_CONTROL
    Fan1_Control();
#endif

#if SUPPORT_FAN1_CALIBRATION
    Fan1_Calibration();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventC(void)
{
    Charger_Hook1SecTimer();
    Service_PowerLatch();

#if SUPPORT_AUTO_BOOT
    Oem_AutoBoot();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook1min events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1MinEvent(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_1
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_1(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_2
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_2(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_3
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_3(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_4
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_4(void)
{
#if SUPPORT_WINAPP_ITE_RFDU
    ITE_ReadFlashDataUtility();
#endif
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook_main_service_H
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_main_service_H(void)
{
    if ((PM1DataCount > 0) && (IS_MASK_CLEAR(PM1STS, P_OBF)))
    {
        PM1DataCount--;
        PM1DO = PM1Data;
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook_main_service_L
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_main_service_L(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
BYTE Hook_Only_Timer1msEvent(void)
{
    //-------------------------------------------------------------------------
    /* Return :
       Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
       All_TimerEvent : All timer events are OK.
    */
    //-------------------------------------------------------------------------
    return(All_TimerEvent);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service
//         function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc
//         function, don't change anything.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
BYTE OEM_SkipMainServiceFunc(void)
{
#if SUPPORT_WINAPP_ITE_RFDU
    if (xFREAD_Enabled > 0)
    {
        F_Service_OEM_4 = 1;
    }
#endif
    return(Normal_MainService);
}

/*-----------------------------------------------------------------------------
 * End of OEM_MAIN.C */