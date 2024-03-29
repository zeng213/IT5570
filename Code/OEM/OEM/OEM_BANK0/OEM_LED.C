/*-----------------------------------------------------------------------------
 * @file     | OEM_LED.C
 *-----------+-----------------------------------------------------------------
 * @function | Process LED indicator control
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




/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//*****************************************************************************
// CODE START
//*****************************************************************************
/* ----------------------------------------------------------------------------
 * FUNCTION:   OEM_Write_Leds
 *
 * Write to SCROLL LOCK, NUM LOCK, CAPS LOCK, and any custom LEDs (including
 * an "Fn" key LED).
 *
 * Input: data (LED_ON bit) = Data to write to the LEDs
 *         bit 0 - SCROLL, Scroll Lock
 *         bit 1 - NUM,    Num Lock
 *         bit 2 - CAPS,   Caps Lock
 *         bit 3 - OVL,    Fn LED
 *         bit 4 - LED4,   Undefined
 *         bit 5 - LED5,   Undefined
 *         bit 6 - LED6,   Undefined
 *         bit 7 - LED7,   Undefined
 *
 * Updates Led_Data variable and calls send_leds if appropriate.
 */
void OEM_Write_Leds(BYTE data_byte)
{
    Led_Data = data_byte;
    if (data_byte & BIT1)
    {
        Hook_NUMLED_ON();
    }
    else
    {
        Hook_NUMLED_OFF();
    }

    if (data_byte & BIT2)
    {
        Hook_CAPLED_ON();
    }
    else
    {
        Hook_CAPLED_OFF();
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_LED_Indicator
 * @function - Service_LED_Indicator
 * @Upstream - Hook_Timer100msEventA
 * @input    - GPI
 * @return   - None
 * @note     - None
 */
void Service_LED_Indicator(void)
{

#if 1
    if (SystemIsS0 || SystemIsS3)
    {
        //-----------------------------------------------------
        // For thermal shutdown indicate
        //-----------------------------------------------------
        if (IsThermalShutdowmHappen())
        {
            if( ThermalBlinkEn <= 0 )
            {
                LED_NotifyAbnormalShutodown();
                ThermalBlinkEn = 1;
            }
        }
        else
        {
            ThermalBlinkEn = 0;
        }
    }
#endif

    //-----------------------------------------------------
    // System Power LED
    //-----------------------------------------------------
    if (IS_MASK_SET(SysPowState, F_PST_BUSY))
    {
        ;
    }
    else
    {
#if SUPPORT_OOB_CRASHLOG_KEY
        if((xOOB_GET_CRASHLOG == 0) && (xOOB_GetCrashLogLock > 0))
        {
            if (IS_LED_PWR_N_ON())
            {
                LED_PWR_N_OFF();
            }
            else
            {
                LED_PWR_N_ON();
            }
        }
        else if(xOOB_RemindGetCrashLogLED > 0)
        {
            if (PwrLedBlinkTimer > 0)
            {
                PwrLedBlinkTimer--;
            }
            else
            {
                PwrLedBlinkTimer = 19;
                if (IS_LED_PWR_N_ON())
                {
                    LED_PWR_N_OFF();
                }
                else
                {
                    LED_PWR_N_ON();
                }
            }
        } 
        else
        {
#endif
        if (SystemIsS0)
        {
            if (IS_SLP_S0_CS_HI())
            {
                if (IS_LED_PWR_N_OFF())
                {
                    PWM0LHE=0x00;
                    LED_PWR_N_ON();
                }
            }
            else
            {
#if 0
                if (PwrLedBlinkTimer > 0)
                {
                    PwrLedBlinkTimer--;
                }
                else
                {
                    PwrLedBlinkTimer = 19;
                    if (IS_LED_PWR_N_ON())
                    {
                        LED_PWR_N_OFF();
                    }
                    else
                    {
                        LED_PWR_N_ON();
                    }
                }
#else
                GPCRA0=ALT;
                PWM0LHE = 0x01;
#endif
            }
        }
        else if (SystemIsS3)
        {
#if 0
            if (PwrLedBlinkTimer > 0)
            {
                PwrLedBlinkTimer--;
            }
            else
            {
                PwrLedBlinkTimer = 19;
                if (IS_LED_PWR_N_ON())
                {
                    LED_PWR_N_OFF();
                }
                else
                {
                    LED_PWR_N_ON();
                }
            }
#else
            GPCRA0=ALT;
            PWM0LHE = 0x01;
#endif
        }
        else
        {
            LED_PWR_N_OFF();
        }
#if SUPPORT_OOB_CRASHLOG_KEY
        }
#endif
    }
    //-----------------------------------------------------
    // Battery & Charger LED
    // LED_CHG_FULL_OFF()   SET_MASK(GPDRJ, BIT(1))
    // LED_CHG_FULL_ON()    CLEAR_MASK(GPDRJ, BIT(1))
    // LED_CHG_ON()         CLEAR_MASK(GPDRA, BIT(3))
    // LED_CHG_OFF()        SET_MASK(GPDRA, BIT(3))
    //-----------------------------------------------------
    if (IS_BATTERY1_IN() && IS_ADP_PRESENT_HI())
    {
        if (xEC_Bt1RSOC >= 100)
        {
            LED_CHG_FULL_ON();  //GPJ.1
            LED_CHG_OFF();      //GPA.3
        }
        else
        {
            if (IS_MASK_SET(xEC_Bt1State, F_ACPI_CHARGING)
                 && IS_MASK_SET(SMBB_DEV0_STS, F_DEV_EARLY_INIT)
                 && (BAT1_Voltage <= LOW_BATTERY_VOLTAGE))
            {
                // Low Battery
                LED_CHG_FULL_OFF();
                if (IS_LED_CHG_ON())
                {
                    LED_CHG_OFF();
                }
                else
                {
                    LED_CHG_ON();
                }
            }
            else if (BAT1_RelativeStateOfChgL < 10)
            {
                // Dead Battery
                LED_CHG_FULL_OFF();
                if (PwrLedBlinkTimer > 0)
                {
                    PwrLedBlinkTimer--;
                }
                else
                {
                    PwrLedBlinkTimer = 19;
                    if (IS_LED_CHG_ON())
                    {
                        LED_CHG_OFF();
                    }
                    else
                    {
                        LED_CHG_ON();
                    }
                }
            }
            else
            {
                LED_CHG_FULL_OFF();
                LED_CHG_ON();
            }
        }
        return ;
    }
    if (IS_BATTERY1_OUT() && IS_ADP_PRESENT_HI())
    {
        LED_CHG_FULL_OFF();
        if (ChargerBlinkTimer > 0)
        {
            ChargerBlinkTimer--;
        }
        else
        {
            if (IS_LED_CHG_OFF())
            {   // 1s
                ChargerBlinkTimer = 9;
                LED_CHG_ON();
            }
            else
            {   // 5s
                ChargerBlinkTimer = 49;
                LED_CHG_OFF();
            }
        }
    }
    else
    {
        LED_CHG_FULL_OFF();
        LED_CHG_OFF();
    }
}

void LED_NotifyHardReset(void)
{
    LED_PWR_N_ON();
    DelayXms(200);
    LED_PWR_N_OFF();
    DelayXms(200);
}

void LED_NotifyForceShutdown(void)
{
    if (IS_LED_PWR_N_ON())
    {
        LED_PWR_N_OFF();
        DelayXms(100);
    }

    LED_PWR_N_ON();
    DelayXms(400);
    LED_PWR_N_OFF();
}


void LED_NotifyAbnormalShutodown(void)
{
    for (ITempB01 = 0; ITempB01 < 10; ++ITempB01)
    {
        LED_PWR_N_OFF();
        DelayXms(200);
        LED_PWR_N_ON();
        DelayXms(200);
    }
    LED_PWR_N_OFF();
 }
 
void LED_NotifyPowerOnFail(void)
{
    for (ITempB01 = 0; ITempB01 < 3; ++ITempB01)
    {
        LED_PWR_N_OFF();
        DelayXms(200);
        LED_PWR_N_ON();
        DelayXms(200);
    }
    LED_PWR_N_OFF();
 }
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_LED.C */
