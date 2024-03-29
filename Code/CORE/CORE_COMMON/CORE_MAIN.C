/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.C - Main Program for KBC firmware.
 *
 * Main processing loop (interrupt driven) for the keyboard controller/scanner.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/* ----------------------------------------------------------------------------
 *  FUNCTION: main - Main service loop.
 *
 *  Wait in idle state until an IRQ causes an exit from idle.  If the IRQ
 *  handler posted a service request (via bSERVICE) then dispatch control to
 *  the appropriate service handler.  Otherwise, go back to idle state.  After
 *  all service requests have been handled, return to idle state.
 * ------------------------------------------------------------------------- */
void main(void)
{
    DisableAllInterrupt();
    SP = 0xC0;                  // Setting stack pointer
    ResetBANKDATA();            // init bank mechanism to code bank 0
    SCRA0H = 0x07;      // Clear Scratch SRAM
    //-------------------------------------------------------------------------
#if !ITE_CHIP_IT557X
    /* ITE IT852X,IT858X,IT898X,IT8991 */
    DCache = 0x03;      /* ITE Patch */
    ECINDAR3 = 0;
    ECINDAR2 = 0;
    ECINDAR1 = 0;
    ECINDAR0 = 0;
    ITempB01 = ECINDDR;
#else
    ECINDAR3 = 0;
    ECINDAR2 = 0;
    ECINDAR1 = 0;
    ECINDAR0 = 0;
    ITempB01 = ECINDDR;
#endif
    //-------------------------------------------------------------------------
#ifdef SUPPORT_MIRROR_ONCE
#if SUPPORT_MIRROR_ONCE
    if (eFlash_Read_1Byte(0x00, 0x00, 0x4D) != 00)
    {
        eFlash_Write_1Byte(0x00, 0x40, 0x00, 0x4D);
    }
#endif
#endif
    //-------------------------------------------------------------------------
#if ITE_eSPI_SAFS_MODE
    // FLHCTRL3R.0:0 FSCK/FSCE#/FMISO/FMOSI are normal operation.
    FLHCTRL3R = 0x08;
#else
#if SHARED_BIOS_TRI_STATE
    if (FLHCTRL3R & 0x80)
    {
        SET_MASK(FLHCTRL3R, BIT(7));    // Clear mirror code finish flag
    }
    // FLHCTRL3R.0:1 FSCK/FSCE#/FMISO/FMOSI are tri-state.
    SET_MASK(FLHCTRL3R, BIT(0));
#endif
#endif
    //-------------------------------------------------------------------------
    // Exit from follow mode or EC scatch ROM
    if (Hook_ECRetunrMainFuncKeepCondition() == 0x33)
    {
        CLEAR_MASK(FBCFG,SSMC); // Disable scatch ROM
        _nop_();
        MPRECF = 0x01;
        _nop_();
        MPRECF = 0x01;
        _nop_();
        MPRECF = 0x01;
        _nop_();
        MPRECF = 0x01;
        _nop_();
        _nop_();
        WinFlashMark = 0x00;
        //ResetBANKDATA();        // init bank mechanism to code bank 0
        Hook_ECExitFollowMode();
        Init_Timers();
        EnableModuleInterrupt();
    }
    else
    {
        /* eSPI & LPC Bus Function */
#if SUPPORT_INTERFACE_eSPI
        SCRA0H = 0x07;      // Clear Scratch SRAM
        GCR22 |= VCCPDS;    // Setting eSPI Bus 1.8V
#if ITE_eSPI_LOW_FREQUENCY
        REG_3105 = _eSPI_MAX_FREQ_20MHZ;
        //Low Frequency PLL change is not required
#else
        REG_3105 = _eSPI_MAX_FREQ_66MHZ;
#if ITE_eSPI_SAFS_MODE
        ChangePLLFrequency(_PLL_FREQ_64_5_MHZ);
#else
        ChangePLLFrequency(_PLL_FREQ_32_3_MHZ);
#endif
#endif
#else   //SUPPORT_INTERFACE_LPC
        SCRA0H = 0x07;      // Clear Scratch SRAM
#if SUPPORT_LPC_BUS_1_8V
        GCR22 |= VCCPDS;    // Setting LPC Bus 1.8V
#endif
#endif
#if ITE_eSPI_SAFS_MODE
        REG_3115 = _SUPPORT_SAFS;
        REG_10A2 = 0x80;
#else
        REG_3115 = _SUPPORT_MAFS;
#endif
        Core_Initialization();
        Oem_Initialization();
        InitEnableInterrupt();
#ifdef MCU_UART_Debug
        Init_UART_Debug();
        printf("\n************************************");
        printf("\nEC UART DEBUG Init OK !!!");
        printf("\n************************************");
#endif
    }

    while(1)
    {
        if(OEM_SkipMainServiceFunc()==Normal_MainService)
        {
            main_service();
            EnableModuleInterrupt();
            _nop_();
            _nop_();
            _nop_();
            _nop_();

            #if TouchPad_only

            #else
            if(PS2CheckPendingISR()==0x00)
            {
                ScanAUXDeviceStep();
            }
            #endif

            #ifdef SMBusServiceCenterFunc
            if((Service==0x00)&&(Service1==0x00)&&(CheckSMBusNeedService()==SMBus_ClearService))
            #else
            if((Service==0x00)&&(Service1==0x00))
            #endif
            {
#if SUPPORT_MODERN_STANDBY
                CheckCanGo_DeepSleep();
                /**
                * @brief  Branch EC chip power saving mode
                */
                switch(xMSBY_Mode)
                {
                case _EC_GENERAL_IDLE:
#if SUPPORT_S0_ATHENA_IDLE
                    if (CheckCanGo_AthenaIdle())
                    {
                        xMSBY_Mode = _EC_ATHENA_IDLE;
                    }
#endif
                    CheckCanGo_S3ModernStandby();
                    CheckCanGo_ModernStandby();
                    PCON = 1;           // enter idle mode
                    /* Wake-up Delay */
                    _nop_();        /* 1st // Repeat "nop" eight times immediately */
                    _nop_();        /* 2nd // for internal bus turn-around. */
                    _nop_();        /* 3rd */
                    _nop_();        /* 4th */
                    _nop_();        /* 5th */
                    _nop_();        /* 6th */
                    _nop_();        /* 7th */
                    _nop_();        /* 8th */
                    break;
        
                case _EC_ATHENA_IDLE:
                    if (CheckExit_AthenaIdle())
                    {
                        xMSBY_Mode = _EC_GENERAL_IDLE;
                        xATNA_IdleTimer = _EC_ENTRY_ATHENA_TIME;
                        break;
                    }
                    CheckCanGo_ModernStandby();
                    InitEntry_AthenaIdle();
                    // Enable All Interrupt
                    _nop_();
                    _nop_();
#if SUPPORT_FAN1_CONTROL
                    if ((CPU_PWM_FAN_DCR > 0) || (SMBB_CHN_STS & F_SMB_BUSY))
#else
                    if (SMBB_CHN_STS & F_SMB_BUSY)
#endif
                    {
                    	EA = 1;         /* Enable global interrupt */
                    	PCON = 1;       /* enter idle mode */
                    }
                    else
                    {
                    	EA = 1;         /* Enable global interrupt */
                    	if (!F_PowerDownRejectTag)
                    	{
                        	PLLCTRL = 0x03; /* 03h for Deep Doze mode */
                        	_nop_();        /* MCU into DeepDoze Mode */
                        	PCON = 0x02;    /* #02h for Doze/Deep Doze/Sleep mode */
                    	}
                    }
                    /* Wake-up Delay */
                    _nop_();        /* 1st // Repeat "nop" eight times immediately */
                    _nop_();        /* 2nd // for internal bus turn-around. */
                    _nop_();        /* 3rd */
                    _nop_();        /* 4th */
                    _nop_();        /* 5th */
                    _nop_();        /* 6th */
                    _nop_();        /* 7th */
                    _nop_();        /* 8th */
                    InitWake_AthenaIdle();
                    break;
                case _EC_S3_POWER_SAVING:
                    if (SMBB_CHN_STS & F_SMB_BUSY)
                    {
                        break;
                    }
                    InitEntry_S3ModernStandby();
                    xMSBY_S3SleepCounter++;
                    GPCRA0=OUTPUT;
                    PWM0LHE=0x00;
                    LED_PWR_N_OFF();
                    // Enable All Interrupt
                    _nop_();
                    _nop_();
                    EA = 1;         /* Enable global interrupt */
                    if (!F_PowerDownRejectTag)
                    {
                        PLLCTRL = 0x03; /* 03h for Deep Doze mode */
                        _nop_();        /* MCU into DeepDoze Mode */
                        PCON = 0x02;    /* #02h for Doze/Deep Doze/Sleep mode */
                    }
                    /* Wake-up Delay */
                    _nop_();        /* 1st // Repeat "nop" eight times immediately */
                    _nop_();        /* 2nd // for internal bus turn-around. */
                    _nop_();        /* 3rd */
                    _nop_();        /* 4th */
                    _nop_();        /* 5th */
                    _nop_();        /* 6th */
                    _nop_();        /* 7th */
                    _nop_();        /* 8th */
                    InitExit_S3ModernStandby();
                    LED_PWR_N_ON();
                    break;
                case _EC_MODERN_STANDBY:
                    InitEntry_ModernStandby();
                    while(1)
                    {
                        Hook_ModernStandbyService();
                        if (xMSBY_ExitKey != 0x00)
                        {
                            break;
                        }
                        InitSleep_ModernStandby();
                        xMSBY_SleepCounter++;
                        GPCRA0=OUTPUT;
                        PWM0LHE=0x00;
                        LED_PWR_N_OFF();
                        // Enable All Interrupt
                        _nop_();
                        _nop_();
                        EA = 1;         /* Enable global interrupt */
                        if (!F_PowerDownRejectTag)
                        {
                            PLLCTRL = 0x03; /* 03h for Deep Doze mode */
                            _nop_();        /* MCU into DeepDoze Mode */
                            PCON = 0x02;    /* #02h for Doze/Deep Doze/Sleep mode */
                        }
                        /* Wake-up Delay */
                        _nop_();        /* 1st // Repeat "nop" eight times immediately */
                        _nop_();        /* 2nd // for internal bus turn-around. */
                        _nop_();        /* 3rd */
                        _nop_();        /* 4th */
                        _nop_();        /* 5th */
                        _nop_();        /* 6th */
                        _nop_();        /* 7th */
                        _nop_();        /* 8th */
                        InitWake_ModernStandby();
                        LED_PWR_N_ON();
                    }
                    InitExit_ModernStandby();
                    xMSBY_Mode = _EC_GENERAL_IDLE;
                    break;
        
                case _EC_POWER_DOWN_IDLE:
                    InitEntry_DeepSleep();
                    // Enable All Interrupt
                    _nop_();
                    _nop_();
                    EA = 1;         /* Enable global interrupt */
                    if (!F_PowerDownRejectTag)
                    {
                        PLLCTRL = 0x01;
                        PCON = 0x02;        /* MCU into Sleep (Deep Sleep) mode. */
                    }
                    /* Wake-up Delay */
                    _nop_();        /* 1st // Repeat "nop" eight times immediately */
                    _nop_();        /* 2nd // for internal bus turn-around. */
                    _nop_();        /* 3rd */
                    _nop_();        /* 4th */
                    _nop_();        /* 5th */
                    _nop_();        /* 6th */
                    _nop_();        /* 7th */
                    _nop_();        /* 8th */
                    InitExit_DeepSleep();
                    xMSBY_Mode = _EC_GENERAL_IDLE;
                    xECPW_DeepSleepDelay = 8;
                    break;
        
                default:
                    xMSBY_Mode = _EC_GENERAL_IDLE;
                    break;
                }
#else
                PCON = 1;           // enter idle mode
                /* Wake-up Delay */
                _nop_();        /* 1st // Repeat "nop" eight times immediately */
                _nop_();        /* 2nd // for internal bus turn-around. */
                _nop_();        /* 3rd */
                _nop_();        /* 4th */
                _nop_();        /* 5th */
                _nop_();        /* 6th */
                _nop_();        /* 7th */
                _nop_();        /* 8th */
#endif
            }
        }
    }
}

/* ----------------------------------------------------------------------------
 * FUNCTION: main_service - Check for new/more service requests.
 *
 * Check for a request flag.  The check is done according to priority.  If a
 * request flag is set, handle the request and loop back to get the flags
 * again.  Do not follow through to check the next flag.  The flags are to be
 * checked in order.
 * ------------------------------------------------------------------------- */
void main_service(void)
{
    #ifdef SMBusServiceCenterFunc
    while((Service!=0x00)||(Service1!=0x00)||(CheckSMBusNeedService()==SMBus_NeedService))
    #else
    while((Service!=0x00)||(Service1!=0x00))
    #endif
    {
#if SUPPORT_INTERFACE_eSPI
        //-----------------------------------
        // eSPI Interface Control
        //-----------------------------------
        if (IS_PCH_RSMRST_HI())
        {
            if (VWIDX5 == (F_IDX5_SLAVE_BOOT_LOAD_STATUS_VALID +
                            F_IDX5_SLAVE_BOOT_LOAD_DONE_VALID +
                            F_IDX5_SLAVE_BOOT_LOAD_STATUS +
                            F_IDX5_SLAVE_BOOT_LOAD_DONE))
            {
                EC_ACK_eSPI_SUS_WARN();
                EC_ACK_eSPI_Reset();
#ifdef SUPPORT_HOOK_WARMBOOT
#if SUPPORT_HOOK_WARMBOOT
                if (eSPI_PLTRST_TAG == F_PLTRST_DETECTED)
                {
                    eSPI_PLTRST_TAG = F_PLTRST_HI_LEVEL;
                    SystemWarmBoot();
                }
#endif
#endif
            }
            else
            {
                EC_ACK_eSPI_Boot_Ready();
            }
        }
#endif
        //-----------------------------------
        // Host command/data service
        //-----------------------------------
        if(F_Service_PCI)
        {
            F_Service_PCI=0;
            service_pci1();
            continue;
        }

        //-----------------------------------
        // Service unlock
        //-----------------------------------
        if(F_Service_UNLOCK)
        {
            F_Service_UNLOCK=0;
            service_unlock();
            continue;
        }

        //-----------------------------------
        // Send byte from KBC
        //-----------------------------------
        if(F_Service_SEND)
        {
            F_Service_SEND=0;
            service_send();
            continue;
        }

        //-----------------------------------
        // Send PS2 interface data
        //-----------------------------------
        if(F_Service_Send_PS2)
        {
            F_Service_Send_PS2=0;
#if SUPPORT_SERVICE_PS2
            service_PS2_data();
            continue;
#endif
        }

        //-----------------------------------
        // process PS2 interface data
        //-----------------------------------
        if(F_Service_PS2)
        {
            F_Service_PS2=0;
#if SUPPORT_SERVICE_PS2
            service_ps2();
            continue;
#endif
        }

        //-----------------------------------
        // process SMBus interface data
        //-----------------------------------
        #ifdef SMBusServiceCenterFunc
        ServiceSMBus();
        #endif

        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        if(F_Service_MS_1)
        {
            F_Service_MS_1=0;
            service_1mS();
            continue;
        }

        //-----------------------------------
        // Secondary Host command/data service
        //-----------------------------------
        if(F_Service_PCI2)
        {
            F_Service_PCI2=0;
            service_pci2();
            continue;
        }

        //-----------------------------------
        // Keyboard scanner service
        //-----------------------------------
        if(F_Service_KEY)
        {
            F_Service_KEY=0;
//             service_scan();
            continue;
        }

        //-----------------------------------
        //
        //-----------------------------------
        Hook_main_service_H();

        //-----------------------------------
        // Low level event
        //-----------------------------------
        if(F_Service_Low_LV)
        {
            F_Service_Low_LV=0;
            service_Low_LVEvent();
            continue;
        }

        //-----------------------------------
        // Third Host command/data service
        //-----------------------------------
        if(F_Service_PCI3)
        {
            F_Service_PCI3=0;
            service_pci3();
            continue;
        }

        //-----------------------------------
        // CIR IRQ
        //-----------------------------------
        if(F_Service_CIR)
        {
            F_Service_CIR=0;
            service_cir();
            continue;
        }

        //-----------------------------------
        // fourth command/data service
        //-----------------------------------
        if(F_Service_PCI4)
        {
            F_Service_PCI4=0;
            service_pci4();
            continue;
        }

        //------------------------------------
        // service_OEM_1
        //------------------------------------
        if(F_Service_OEM_1)
        {
            F_Service_OEM_1=0;
            service_OEM_1();
            continue;
        }

        //------------------------------------
        // service_OEM_2
        //------------------------------------
        if(F_Service_OEM_2)
        {
            F_Service_OEM_2=0;
            service_OEM_2();
            continue;
        }

        //------------------------------------
        // service_OEM_3
        //------------------------------------
        if(F_Service_OEM_3)
        {
            F_Service_OEM_3=0;
            service_OEM_3();
            continue;
        }

        //------------------------------------
        // service_OEM_4
        //------------------------------------
        if(F_Service_OEM_4)
        {
            F_Service_OEM_4=0;
            service_OEM_4();
            continue;
        }

        //-----------------------------------
        //
        //-----------------------------------
        Hook_main_service_L();
    }
}

void service_Low_LVEvent(void)
{
    if((KBPendingTXCount != KBPendingRXCount )||(scan.kbf_head != scan.kbf_tail))
    {
        SetServiceSendFlag();
    }

    if(IS_MASK_SET(KBHISR,P_IBF))   // 60/64 input buffer full
    {
        F_Service_PCI = 1;
    }
    if(IS_MASK_SET(PM1STS,P_IBF))   // 62/66 input buffer full
    {
        F_Service_PCI2 = 1;
    }
    if(IS_MASK_SET(PM2STS, P_IBF))  // 68/6C input buffer full
    {
        F_Service_PCI3 = 1;
    }
}

//----------------------------------------------------------------------------
// FUNCTION: service_unlock
// Unlock aux devices and re-enable Host interface IRQ if it is ok to do so.
//----------------------------------------------------------------------------
static void service_unlock(void)
{
    Unlock_Scan();
}

//------------------------------------------------------------
// Polling events
//------------------------------------------------------------
void service_1mS(void)
{
    Timer1msEvent();
    Timer1msCnt++;
    if(Timer1msCnt>=10)
    {
        Timer1msCnt = 0x00;
    }

    if(Hook_Only_Timer1msEvent()==Only_Timer1msEvent)
    {
        return;
    }
#if SUPPORT_S0_ATHENA_IDLE
    if (xMSBY_Mode == _EC_ATHENA_IDLE)
    {
        Timer1msCnt = 0;
    }
#endif
    if((Timer1msCnt%5)==0x00)
    {
        Timer5msEvent();
        Timer5msCnt++;
        if ( Timer5msCnt & 1 )      // 10ms events
        {
            Timer10msEventA();
        }
        else
        {
            Timer10msEventB();
            switch( Timer5msCnt )   // Share Loading Branch Control
            {
                case 2: Timer50msEventA();
                    break;
                case 4: Timer50msEventB();
                    break;
                case 6: Timer50msEventC();
                    break;
                case 8: Timer100msCntB++;
                    if ( Timer100msCntB & 1 )
                    {
                        Timer100msEventA();
                    }
                    else
                    {
                        Timer100msEventB();
                    }
                    break;

                default:
                    Timer5msCnt=0;
                    break;
            }

            if ( Timer5msCnt == 0x00 )
            {                   // 50msec
                Timer100msCnt ++;
                if ( Timer100msCnt & 1 )
                {
                    Timer100msEventC();
                }
                else
                {               // 100msec
                    switch( Timer100msCnt )
                    {
                        case 2: Timer500msEventA();
                            break;
                        case 4: Timer500msEventB();
                            break;
                        case 6: Timer500msEventC();
                            break;
                        case 8: Timer1SecEventA();
                            break;
                        case 10:    Timer1SecEventB();
                            break;
                        case 12:    Timer500msEventA();
                            break;
                        case 14:    Timer500msEventB();
                            break;
                        case 16:    Timer500msEventC();
                            break;
                        case 18:    Timer1SecEventC();
                            break;
                        default:        // 1 Sec
                            Timer100msCnt = 0;
                            Timer1SecCnt ++;
                            if ( Timer1SecCnt == 60 )
                            {
                                Timer1MinEvent();
                                Timer1SecCnt=0;
                            }
                            break;
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------
// 1ms events
//------------------------------------------------------------
void Timer1msEvent(void)
{
    ReSendPS2PendingData();
    Hook_Timer1msEvent(Timer1msCnt);
}

//------------------------------------------------------------
// 5ms events
//------------------------------------------------------------
void Timer5msEvent(void)
{
    F_Service_Low_LV = 1;
    if (Timer_A.fbit.TMR_SCAN)
    {
        #ifdef KB_HW_KeyScan
        HW_KB_Check_TM();
        #else
        F_Service_KEY = 1;      // Request scanner service.
        #endif  // KB_HW_KeyScan
    }
    Hook_Timer5msEvent();
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventA(void)
{
    SetStartScanAUXFlag();
    Hook_Timer10msEventA();
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventB(void)
{
    Hook_Timer10msEventB();
}

//------------------------------------------------------------
// 50ms events A
//------------------------------------------------------------
void Timer50msEventA(void)
{
    Hook_Timer50msEventA();
}

//------------------------------------------------------------
// 50ms events B
//------------------------------------------------------------
void Timer50msEventB(void)
{
    Hook_Timer50msEventB();
}

//------------------------------------------------------------
// 50ms events C
//------------------------------------------------------------
void Timer50msEventC(void)
{
    Hook_Timer50msEventC();
}

//------------------------------------------------------------
// 100ms events A
//------------------------------------------------------------
void Timer100msEventA(void)
{
    Hook_Timer100msEventA();
}

//------------------------------------------------------------
// 100ms events B
//------------------------------------------------------------
void Timer100msEventB(void)
{
    Hook_Timer100msEventB();
}

//------------------------------------------------------------
// 100ms events C
//------------------------------------------------------------
void Timer100msEventC(void)
{
    Hook_Timer100msEventC();
    Hook_Timer100msEventD();
}

//------------------------------------------------------------
// 500ms events A
//------------------------------------------------------------
void Timer500msEventA(void)
{
    Hook_Timer500msEventA();
}

//------------------------------------------------------------
// 500ms events B
//------------------------------------------------------------
void Timer500msEventB(void)
{
    Hook_Timer500msEventB();
}

//------------------------------------------------------------
// 500ms events C
//------------------------------------------------------------
void Timer500msEventC(void)
{
    Hook_Timer500msEventC();
}

//------------------------------------------------------------
// 1sec events A
//------------------------------------------------------------
void Timer1SecEventA(void)
{
    Hook_Timer1SecEventA();
}

//------------------------------------------------------------
// 1sec events B
//------------------------------------------------------------
void Timer1SecEventB(void)
{
    Hook_Timer1SecEventB();
}

//------------------------------------------------------------
// 1sec events C
//------------------------------------------------------------
void Timer1SecEventC(void)
{
    Hook_Timer1SecEventC();
    Hook_Timer1SecEventD();
}

//------------------------------------------------------------
// 1min events
//------------------------------------------------------------
void Timer1MinEvent(void)
{
    Hook_Timer1MinEvent();
}

