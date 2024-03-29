/*-----------------------------------------------------------------------------
 * @file     | OEM_FAN.C
 *-----------+-----------------------------------------------------------------
 * @function | FAN & Thermal control
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2019, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_FAN                   FALSE
#define SUPPORT_FAN_CURVE_CONTROL   FALSE
#define SUPPORT_FAN_ERROR_CHECK     FALSE
#define SUPPORT_FAN_CURVE_JUMP_STEP FALSE
#define _FLASH_EC_FAN_DCR           0xC8
#define _STARTUP_EC_FAN_DCR         0xB0
// #define CPU_PWM_FAN_DCR             DCR7

//-----------------------------------------------------------------------------
/* Fan Control & Fan Tachometer Parameter */
#define TACH1P                  2
#define TACH2P                  2
#define TACH1PT                 (4312500 / TACH1P)
#define TACH2PT                 (4312500 / TACH2P)

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_FAN
#define FAN_RamDebug(x)         RamDebug(x)
#else
#define FAN_RamDebug(x)         {}
#endif

//-----------------------------------------------------------------------------
// Host Processor(CPU) Fan Control Table
//-----------------------------------------------------------------------------
#define _FAN1_STEP      15
code BYTE _FAN1_DNT_TBL[] = {  0,  40,  47,  55,  65,  65,  65,  65,  65,  65,  65,  65,  65,  65,  65 };
code BYTE _FAN1_UPT_TBL[] = { 45,  52,  60,  70, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
code BYTE _FAN1_REQ_TBL[] = {  0,  77, 102, 128, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166 };
code BYTE _FAN1_RPM_TBL[] = {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
//-----------------------------------------------------------------------------
#if SUPPORT_FAN1_CONTROL
/*-----------------------------------------------------------------------------
 * @subroutine - ITE_Flash_FanCtrl
 * @function - Fan Control before enter flash utility
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ITE_Flash_FanCtrl(void)
{
    CPU_PWM_FAN_DCR = _FLASH_EC_FAN_DCR;
}

/*-----------------------------------------------------------------------------
 * @subroutine - GetFanRPM
 * @function - PWM/TACHX MODULE
 *             Calculation Fan Tachometer to Fan Speed (R.P.M)
 *             Fan Speed (R.P.M)=60/(1/fs sec * {FnTMRR,FnTLRR) * P )
 * @Upstream - Hook_Timer1SecEventA
 * @input    - FnTMRR, FnTLRR (From Fan Tach. Registers)
 * @return   - FanRPM (16Bits)
 * @note     - None
 */
WORD GetFanRPM(BYTE FnTMRR, BYTE FnTLRR)
{
    WORD    wFanRPM;

    /* 2020+ ITE FAE Update */
    ITempW01 = ((FnTMRR * 256) + FnTLRR);    //Get Base Counter
#if 0   /* 0: Limited Max. RPM Calculation. */
    if (ITempW01 == 0)
    {
        return (0);
    }
    else if (ITempW01 < 214)
    {
        return (10000); /* MAX */
    }
    else
    {
        wFanRPM = (TACH1PT / ITempW01);
    }
#else
    if (ITempW01 == 0)
    {
        wFanRPM = 0;
    }
    else
    {
        wFanRPM = (TACH1PT / ITempW01);
    }
#endif
    return (wFanRPM);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Load_Fan_RomTable
 * @function - System Fan Control
 * @Upstream - Fan_ControlCenter
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Load_Fan_RomTable(void)
{
    BYTE    i;
    for (i = 0; i < _FAN1_STEP; i++)
    {
        Fan1_T_Dn[i] = _FAN1_DNT_TBL[i];
        Fan1_T_Up[i] = _FAN1_UPT_TBL[i];
        Fan1_PWM[i] = _FAN1_REQ_TBL[i];
        Fan1_RPM_H[i] = _FAN1_RPM_TBL[i] >> 8;
        Fan1_RPM_L[i] = _FAN1_RPM_TBL[i];
    }
}
/*-----------------------------------------------------------------------------
 * @subroutine - Fan1_Control
 * @function - Fan Control
 * @Upstream - Hook_Timer1SecEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Fan1_Calibration(void)
{
    WORD WTEMP, WTEMP2;

    if (SysPowState != _SYSTEM_S0)  //|| (ModernStandbyFanDelay > 0))
    {
        CPU_PWM_FAN_DCR = 0;
        return ;
    }
    
    /* Automatic RPM calibration */
    WTEMP = wFan1_TargetRPM & 0xFFE0;
    WTEMP2 = wFan1_CurrentRPM & 0xFFE0;

    if (WTEMP > WTEMP2)
    {
        if (Fan1_NowDCR < 253)
        {
            Fan1_NowDCR++;
        }
    }
    else if (WTEMP < WTEMP2)
    {
        if (Fan1_NowDCR > 0)
        {
            Fan1_NowDCR--;
        }
    }
    
    CPU_PWM_FAN_DCR = Fan1_NowDCR;
}
#if 0   /* FULL-SPEED for Bring up */
/*-----------------------------------------------------------------------------
 * @subroutine - Fan1_Control
 * @function - Fan Control
 * @Upstream - Hook_Timer1SecEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Fan1_Control(void)
{
    if (SysPowState != _SYSTEM_S0)
    {
        PF_EC_FAN_OFF();
        return;
    }
    PF_EC_FAN_ON();
}
#else
/*-----------------------------------------------------------------------------
 * @subroutine - Fan1_Control
 * @function - Fan Control
 * @Upstream - Hook_Timer1SecEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Fan1_Control(void)
{
    //-------------------------------------------------------------------------
    if (SysPowState != _SYSTEM_S0)  //|| (ModernStandbyFanDelay > 0))
    {
        Fan1_DebugKey = 0;
        CPU_PWM_FAN_DCR = 0;
        Fan1_NeedInit = 1;
        Fan1_Up_Delay = 0;
        Fan1_LevelDir = 0;
        return ;
    }
    
    //wFan1_CurrentRPM = wEC_FAN_CurrentRPM;
#if SUPPORT_FAN_CURVE_CONTROL
    //-------------------------------------------------------------------------
    // DPTF FAN Control Specification (01.0A.0E.T01)
    // Fan rising   duty: 70% ~ 30% === 44'C ~ 35 'C
    // Fan dropping duty: 70% ~ 30% === 42'C ~ 33 'C
    //-------------------------------------------------------------------------
    if (wFan1_CurrentRPM == 0)
    {
        CPU_PWM_FAN_DCR = _STARTUP_EC_FAN_DCR;
        return;
    }
    //-------------------------------------------------------------------------
    // Shutdown system if T1 over temperature
    if (xEC_Sensor_1_T > 59)
    {
         Oem_TriggerPowerOff(59);
    }
    //-------------------------------------------------------------------------
    if (Fan1_LevelDir == 0)
    {
        if (xEC_Sensor_1_T >= Fan1_UpTempr)
        {
            Fan1_UpTempr = xEC_Sensor_1_T;
            Fan1_DnTempr = xEC_Sensor_1_T - 2;
        }
        else if (xEC_Sensor_1_T < Fan1_DnTempr)
        {
            Fan1_LevelDir = 1;  /* GoTo Temperature up */
        }

        if (xEC_Sensor_1_T >= 44)
        {
            CPU_PWM_FAN_DCR = 179;  //70%
            return;
        }
        else if (xEC_Sensor_1_T < 36)
        {
            CPU_PWM_FAN_DCR = 77;   //30%
            return;
        }
        ITempB01 = xEC_Sensor_1_T - 35;
    }
    else
    {
        if (xEC_Sensor_1_T < Fan1_DnTempr)
        {
            Fan1_DnTempr = xEC_Sensor_1_T;
            Fan1_UpTempr = Fan1_UpTempr + 2;
        }
        else if (xEC_Sensor_1_T > Fan1_UpTempr)
        {
            Fan1_LevelDir = 0;  /* GoTo Temperature down */
        }

        if (xEC_Sensor_1_T >= 42)
        {
            CPU_PWM_FAN_DCR = 179;
            return;
        }
        else if (xEC_Sensor_1_T < 34)
        {
            CPU_PWM_FAN_DCR = 77;
            return;
        }
        ITempB01 = xEC_Sensor_1_T - 33;
    }
    //ITempB01 = xEC_Sensor_1_T - 35;
    ITempB01 = (ITempB01 * 7) + 77;
    CPU_PWM_FAN_DCR = ITempB01;
#else
    //-------------------------------------------------------------------------
#if SUPPORT_PECI
#if 1   /* Support error temperature Fan always on */
    if ((PECI_ERRCNT > 4) && (PECI_CPU_T == 0))
    {
        /* Fan Full Run */
        SET_MASK(ZTIER, BIT1);
        CPU_PWM_FAN_DCR = CTR1;
        return;
    }
#endif
#else
    xEC_PECI_CPU_T = xOOB_PECI_CPU_T;
    if (xEC_PECI_CPU_T >= xEC_Sensor_1_T)
    {
        xEC_PLMX_T = xEC_PECI_CPU_T;
    }
    else
    {
        xEC_PLMX_T = xEC_Sensor_1_T;
    }
#endif
    //-------------------------------------------------------------------------
    SET_MASK(ZTIER, BIT1);
    //-------------------------------------------------------------------------
    // Fan1 Error Detected
    //-------------------------------------------------------------------------
#if SUPPORT_FAN_ERROR_CHECK
    if (wFan1_TargetRPM > 0)
    {
        if (wFan1_CurrentRPM == 0)
        {
            Fan1_ErrCheck++;
        }
        else
        {
            Fan1_ErrCheck = 0;
        }
        if (Fan1_ErrCheck > 0)
        {
            CPU_PWM_FAN_DCR = CTR1;
            return;
        }
    }
#endif
    //-------------------------------------------------------------------------
    // Fan1 Debug Mode
    //-------------------------------------------------------------------------
    if (Fan1_DebugKey > 0)
    {
        Fan1_NowDCR = CPU_PWM_FAN_DCR;
        if (Fan1_DebugKey == 0xCC)
        {
            Fan1_RefTempr = Fan1_DebugCmd;
        }
        else
        {
            Fan1_RefTempr = xEC_PECI_CPU_T;
        }
        if (Fan1_DebugKey == 0xDC)
        {
            CPU_PWM_FAN_DCR = Fan1_DebugCmd;
            return;
        }
    }
    else
    {
        Fan1_RefTempr = xEC_PLMX_T;
    }
    //-------------------------------------------------------------------------
#if 0
    //-------------------------------------------------------------------------
    // DOS Dan full on
    //-------------------------------------------------------------------------
    if (xEC_OS_Type == 0)
    {
        if (DOSModeSec > 300)   //DOS mode 300sec ->Fan Full-On
        {
            CPU_PWM_FAN_DCR = 200;
            return;
        }
    }
#endif
    //-------------------------------------------------------------------------
    // Fan1 Initial
    //-------------------------------------------------------------------------
    if (Fan1_T_Up[0] == 0)
    {
        Load_Fan_RomTable();
    }
    //-------------------------------------------------------------------------
    // Fan1 Control Center
    //-------------------------------------------------------------------------
    if ((Fan1_Step == 0) || (Fan1_Step == 2))
    {
        Fan1_Step++;
        if(Fan1_CurrentLevelDir != Fan1_LevelDir)
        {
            Fan1_CurrentLevelDir = Fan1_LevelDir;
            Fan1_DnTempr = _FAN1_DNT_TBL[Fan1_LevelDir];
            Fan1_UpTempr = _FAN1_UPT_TBL[Fan1_LevelDir];
#if SUPPORT_FAN_CURVE_JUMP_STEP
            Fan1_TargetDCR  = _FAN1_REQ_TBL[Fan1_LevelDir];
#else
            Fan1_NowDCR  = _FAN1_REQ_TBL[Fan1_LevelDir];
#endif
            wFan1_TargetRPM = _FAN1_RPM_TBL[Fan1_LevelDir] * 100;
        }
        
#if SUPPORT_FAN_CURVE_JUMP_STEP
        if( Fan1_NowDCR != Fan1_TargetDCR )
        {
            if(Fan1_NowDCR < Fan1_TargetDCR)
            {
                Fan1_NowDCR +=8;
                if(Fan1_NowDCR > Fan1_TargetDCR)
                {
                    Fan1_NowDCR = Fan1_TargetDCR;
                }
            }
            else
            {
                if(Fan1_NowDCR >= 8)
                {
                    Fan1_NowDCR -=8;
                }
                else
                {
                    Fan1_NowDCR = 0;
                }
                if(Fan1_NowDCR < Fan1_TargetDCR)
                {
                    Fan1_NowDCR = Fan1_TargetDCR;
                }
            }
        }
#endif
        return;
    }
    else if (Fan1_Step == 1)
    {
        Fan1_Step++;
        if ((Fan1_RefTempr >= Fan1_UpTempr) || (Fan1_RefTempr == 0xFF))
        {
            if ((Fan1_Up_Delay < 5) && (Fan1_LevelDir > 0) &&
                    (Fan1_RefTempr < 76))
            {
                Fan1_Up_Delay++;
            }
            else
            {
                Fan1_Up_Delay = 0;
                if (Fan1_LevelDir < (_FAN1_STEP - 1))
                {
                    Fan1_LevelDir++;                
                    if(Fan1_LevelDir == 1)
                    {
                        Fan1_NeedInit = 1;
                    }
                }
                else
                {
                    Fan1_LevelDir = (_FAN1_STEP - 1);
                }
            }
        }
        else
        {
            Fan1_Up_Delay = 0;
            if (Fan1_RefTempr < Fan1_DnTempr)
            {
                if (Fan1_LevelDir > 0)
                {
                    Fan1_LevelDir--;
                }
            }
        }
    }
    else
    {
        Fan1_Step = 0;
        if (Fan1_NeedInit > 0)
        {
            Fan1_NeedInit = 0;
            if (Fan1_LevelDir == 1)
            {
                CPU_PWM_FAN_DCR = 150;  //START UP
            }
        }
        else
        {
#if !SUPPORT_FAN1_CALIBRATION
            CPU_PWM_FAN_DCR = Fan1_NowDCR;
#endif
        }
    }
#endif
}
#endif
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_FAN.C */