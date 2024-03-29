/*-----------------------------------------------------------------------------
 * @file     | OEM_EVENT.C
 *-----------+-----------------------------------------------------------------
 * @function | Event Process
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
#define DISABLED_INTEL_DPTF_EVENT   FALSE
#define DEBUG_DPTF_EVT_UART2        FALSE


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//*****************************************************************************
// CODE START
//*****************************************************************************
#if SUPPORT_LID_SWITCH
/*-----------------------------------------------------------------------------
 * @subroutine - Process_LID_Switch
 * @function - LID Switch Module
 * @Upstream -
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_LID_Switch(void)
{
    if (IS_LID_SW_CLOSE())
    {
        LID_OpenDebounce = 0;
        /* LCD Cover Close (LID CLOSE) */
        if (LID_Debounce < 5)
        {
            LID_Debounce++;
            LID_Resend = 40;
        }
        else
        {

            SET_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
            CLEAR_MASK(xEC_LID_STATUS, F_LID_STA);

            if (LID_Resend == 40)
            {
                WriteSCI_Buffer(_SCIEVT_LID_CLOSED);
            }
            if (LID_Resend > 0)
            {
                LID_Resend--;
                if (LID_Resend == 0)
                {
                    WriteSCI_Buffer(_SCIEVT_LID_CLOSED);
                }
            }
        }

    }
    else
    {
        LID_Debounce = 0;
        /* LCD Cover Open (LID OPEN) */
        if (LID_OpenDebounce < 5)
        {
            LID_OpenDebounce++;
            LID_OpenResend = 40;
        }
        else
        {
            if (IS_MASK_SET(xEC_LID_STATUS, F_GPI_LID_STA))
            {

                if (SysPowState == _SYSTEM_S3)
                {
                    if (IS_eSPI_SLP_S3_LO())
                    {
                        PCH_PWRBTN_LO();
                        Delay1MS(80);
                        PCH_PWRBTN_HI();
                    }
                    LID_OpenResend = 40;
                }

                if (SysPowState == _SYSTEM_S0)
                {
                    if (LID_OpenResend == 40)
                    {
                        WriteSCI_Buffer(_SCIEVT_LID_OPEN);
                        //CLEAR_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
                        SET_MASK(xEC_LID_STATUS, F_LID_STA);
                    }
                    if (LID_OpenResend > 0)
                    {
                        LID_OpenResend--;
                        if (LID_OpenResend == 0)
                        {
                            WriteSCI_Buffer(_SCIEVT_LID_OPEN);
                            CLEAR_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
                        }
                    }
                }
            }
        }
    }
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Service_Key_BackLight
 * @function - Service_Key_BackLight
 * @upstream - 1sec
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_Key_BackLight(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - Key_BackLight_Off
 * @function - Key_BackLight_Off
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Key_BackLight_Off(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - Key_BackLight_On
 * @function - Key_BackLight_On
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Key_BackLight_On(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_GPI_Event
 * @function - Service_GPI_Event
 * @Upstream - Hook_Timer50msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Service_GPI_Event(void)
{
    //-------------------------------------------------------------------------
    if (IS_eSPI_SLP_S3_LO())
    {
        return;
    }
    if (PowSwDownTimer > 0)
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (IS_VOLUME_UP_DN())
    {
        if (DebounceGPJ0 < 1)
        {
            DebounceGPJ0++;
        }
        else if (DebounceGPJ0 == 1)
        {
            DebounceGPJ0++;
            //WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
            e0_prefix_code(_KBSET2_VOL_UP, MAKE_EVENT);
        }
        else if (DebounceGPJ0 < 11)
        {
            DebounceGPJ0++;
            if (DebounceGPJ0 == 11)
            {
                //WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
                e0_prefix_code(_KBSET2_VOL_UP, REPEAT_EVENT);//20141027
                DebounceGPJ0 = 10;
            }
        }
        else
        {
            DebounceGPJ0 = 10;
        }
    }
    else
    {
        if (DebounceGPJ0 > 1)
        {
            e0_prefix_code(_KBSET2_VOL_UP, BREAK_EVENT);
        }
        DebounceGPJ0 = 0;
    }

    //-------------------------------------------------------------------------
    if (IS_VOLUME_DOWN_DN())
    {
        if (DebounceGPJ3 < 1)
        {
            DebounceGPJ3++;
        }
        else if (DebounceGPJ3 == 1)
        {
            DebounceGPJ3++;
            //WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
            e0_prefix_code(_KBSET2_VOL_DN, MAKE_EVENT);
        }
        else if (DebounceGPJ3 < 12)
        {
            DebounceGPJ3++;
            if (DebounceGPJ3 == 12)
            {
                //WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
                e0_prefix_code(_KBSET2_VOL_DN, REPEAT_EVENT);//20141027
                DebounceGPJ3 = 10;
            }
        }
        else
        {
            DebounceGPJ3 = 10;
        }
    }
    else
    {
        if (DebounceGPJ3 > 1)
        {
            e0_prefix_code(_KBSET2_VOL_DN, BREAK_EVENT);
        }
        DebounceGPJ3 = 0;
    }
    
    //-----------------------------------------------------
    // Start sending keyboard data
    //
	if (scan.kbf_head != scan.kbf_tail)
	{
        F_Service_SEND = 1;         // Post service request
        SetServiceSendFlag();
	}
}

//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Service_DPTF_Event
 * @function - Service_DPTF_Event
 * @upstream - service_500mS_B
 * @input    - None
 * @return   - None
 * @note     - None
                Offset(0x62),
                TSR2, 8,
                TSI, 4,
                HYST, 4,
                TSHT, 8,
                TSLT, 8,
                TSSR, 8,
                CHGR, 16,
                Offset(0x72),
                TSR1, 8,
                TSR3, 8,
                TS4H, 8,
                TS4L, 8,
 */
void Service_DPTF_Event(void)
{
    //-------------------------------------------------------------------------
    if (IS_eSPI_SLP_S3_LO())
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))    //ECRAM@00D0
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (xEC_T1_EventTimer > 0)
    {
        xEC_T1_EventTimer--;
        return;
    }
    ITempB05 = 0;
    if (xEC_T1_SendEvent > 0)
    {
        ITempB05 = 0x31;
        SET_MASK(xEC_ThermalSource, F_SEN1_TRIP);
        xEC_T1_SendEvent --;
    }
    else if (xEC_T2_SendEvent > 0)
    {
        ITempB05 = 0x32;
        SET_MASK(xEC_ThermalSource, F_SEN2_TRIP);
        xEC_T2_SendEvent--;
    }
    else if (xEC_T3_SendEvent > 0)
    {
        ITempB05 = 0x33;
        SET_MASK(xEC_ThermalSource, F_SEN3_TRIP);
        xEC_T3_SendEvent--;
    }
    else if (xEC_T4_SendEvent > 0)
    {
        ITempB05 = 0x34;
        SET_MASK(xEC_ThermalSource, F_SEN4_TRIP);
        xEC_T4_SendEvent--;
    }
    //-------------------------------------------------------------------------
#if 0
    else if (xEC_CPUT_EventTimer > 0)
    {
        xEC_CPUT_EventTimer--;
    }
    else
    {
        if (xEC_CPUT_SendEvent > 0)
        {
            xEC_CPUT_SendEvent--;
            SET_MASK(xEC_ThermalSource, F_CPU_T_SEN1_TRIP);
            xEC_CPUT_EventTimer = 6;
        }
    }
#endif
    //-------------------------------------------------------------------------
    if (ITempB05 > 0)
    {
#if !DISABLED_INTEL_DPTF_EVENT
        WriteSCI_Buffer(_SCIEVT_THERMAL_DPTF);
#if DEBUG_DPTF_EVT_UART2
        UART2_RBR = 0x0D;
        UART2_RBR = 0x0A;
        UART2_RBR = 0x53;   //'S'
        UART2_RBR = 0x43;   //'C'
        UART2_RBR = 0x49;   //'I'
        UART2_RBR = ITempB05;
        UART2_RBR = 0x20;   //' '
#endif
#endif
        xEC_T1_EventTimer  = 6;
    }
    //-------------------------------------------------------------------------
#if 0
    if (xEC_PECI_CPU_T >= xEC_CPUT_HiLimit)
    {
        xEC_CPUT_HiLimit += 2;
        if (xEC_CPUT_HiLimit >= 2)
        {
            xEC_CPUT_LoLimit = xEC_CPUT_HiLimit - 2;
        }
        xEC_CPUT_SendEvent = 1;
    }
    else if (xEC_PECI_CPU_T < xEC_CPUT_LoLimit)
    {
        xEC_CPUT_HiLimit = xEC_PECI_CPU_T + 2;
        if (xEC_CPUT_LoLimit >= 2)
        {
            xEC_CPUT_LoLimit = xEC_CPUT_LoLimit - 2;
            xEC_CPUT_SendEvent = 1;
        }
    }
#endif
#if 1
    xEC_T4_AVG = (xEC_BAT1_T4 - 2730) / 10;

    if (xEC_T4_AVG >= xEC_T4_HiLimit)
    {
        xEC_T4_HiLimit = xEC_T4_AVG + 2;
        if (xEC_T4_AVG >= 2)
        {
            xEC_T4_LoLimit = xEC_T4_AVG - 2;
        }
        xEC_T4_SendEvent = 1;
    }
    else
    {
        ITempB05 = 0;
        if (xEC_T4_LoLimit > 2)
        {
            ITempB05 = xEC_T4_LoLimit - 2;
        }
        if (xEC_T4_AVG < ITempB05)
        {
            xEC_T4_HiLimit = xEC_T4_AVG + 2;
            if (xEC_T4_AVG >= 2)
            {
                xEC_T4_LoLimit = xEC_T4_AVG - 2;
                xEC_T4_SendEvent = 1;
            }
        }
    }
#endif
    //-------------------------------------------------------------------------
}

#if SUPPORT_DOCK_EVENT_TRIGGER
/*-----------------------------------------------------------------------------
 * @subroutine - Service_DOCK_Event
 * @function - Service_DOCK_Event
 * @Upstream - Hook_Timer10msEventB
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Service_DOCK_Event(void)
{
    if(IS_POGO_IPDM_MUX_SEL_LO())
    {
        V5A_POGO_EN_HI();
        SET_MASK(xEC_POGO_Status, BIT0);
        if(xDOCK_Event_In_Timer > 0)
        {
            xDOCK_Event_In_Timer--;
            if(xDOCK_Event_In_Timer == 0)
            {
                WriteSCI_Buffer(_SCIEVT_DOCK_IN);
                xDOCK_Event_Out_Timer = 10;
            }
        }
    }
    else
    {
        V5A_POGO_EN_LO();
        CLEAR_MASK(xEC_POGO_Status, BIT0);
        if(xDOCK_Event_Out_Timer > 0)
        {
            xDOCK_Event_Out_Timer--;
            if(xDOCK_Event_Out_Timer == 0)
            {
                WriteSCI_Buffer(_SCIEVT_DOCK_OUT);
                xDOCK_Event_In_Timer = 10;
            }
        }
    }
}
#endif

/*-----------------------------------------------------------------------------
 * End */
