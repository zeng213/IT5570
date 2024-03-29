/*-----------------------------------------------------------------------------
 * @file     | OEM_PECI.C
 *-----------+-----------------------------------------------------------------
 * @function | Process CPU PECI
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define SUPPORT_PECI_SUBROUTINE     TRUE
#define SUPPORT_PECI_POWER_CTRL     TRUE
#define SUPPORT_SOFTWARE_AWFCS      FALSE
#define DEBUG_PECI                  FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#ifndef SUPPORT_PECI
#define SUPPORT_PECI            FALSE
#endif

#if DEBUG_PECI
#define PECI_RamDebug(x)        RamDebug(x)
#else
#define PECI_RamDebug(x)        {}
#endif

BYTE PECI_RdPkgConfig(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
                      BYTE Index, BYTE LSB, BYTE MSB,
                      BYTE ReadLen, BYTE WriteLen);
                      
//-----------------------------------------------------------------------------
#if SUPPORT_PECI
/*-----------------------------------------------------------------------------
 * @subroutine - Init_PECI
 * @function - Init_PECI
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
#if 1
void Init_PECI(void)
{
    GPCRF6 = ALT;
    GCR2 |= PECIE;      // Enable PECI EC_REG@16F1.4

    //PADCTLR = 0x00;   // PECI VTT level. = 1.10V
    PADCTLR = 0x01;   // PECI VTT level. = 1.05V    <- ADL-P
    //PADCTLR = 0x02;   // PECI VTT level. = 1.00V
    //PADCTLR = 0x03;     // PECI VTT level. = 0.90V

    HOCTL2R &= 0xF8;
    //HOCTL2R |= 0x00;  //PECI host optimal transfer rate. = 1.8MHz
    HOCTL2R |= 0x01;    //PECI host optimal transfer rate. = 1MHz <-KBL
    //HOCTL2R |= 0x04;  //PECI host optimal transfer rate. = 1.5MHz
    PECI_ERRCNT = 0;
}
#endif
/*-----------------------------------------------------------------------------
 * @subroutine - Service_PECI
 * @function - Service_PECI
 * @upstream - Hook_Timer500msEventA
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_PECI(void)
{
    if (PECI_DELAY > 0)
    {
        PECI_DELAY--;
        return;
    }
    
    HOCTLR = 0x08;      /* PECI module only enable one time */
    HOSTAR = 0xFE;      /* ResetPECIStatus  */
//-------------------------------------------------------------------------
    if (!(PECI_FLAG & F_PECI_INIT))
    {
        if(PECI_ReadDIB())
        {
            PECI_FLAG |= F_PECI_INIT;
        }
        return;
    }
#if SUPPORT_PECI_POWER_CTRL
    else if (!(PECI_FLAG & F_PECI_INIT2))
    {
        if(PECI_ReadPowerUnit())
        {
            PECI_FLAG |= F_PECI_INIT2;
        }
        return;
    }
//     else if (!(PECI_FLAG & F_PECI_INIT3))
//     {
//         if (IS_ADAPTER_IN() && IS_BATTERY1_OUT())
//         {
//             if(PECI_WritePowerLimit2(45))
//             {
//                 PECI_FLAG |= F_PECI_INIT3;
//             }
//         }
//         else
//         {
//             PECI_FLAG |= F_PECI_INIT3;
//         }
//         return;
//     }
//     else if (!(PECI_FLAG & F_PECI_INIT4))
//     {
//         if (IS_ADAPTER_IN() && IS_BATTERY1_OUT())
//         {
//             if(PECI_WritePowerLimit4(66))
//             {
//                 PECI_FLAG |= F_PECI_INIT4;
//             }
//         }
//         else
//         {
//             PECI_FLAG |= F_PECI_INIT4;
//         }
//         return;
//     }
//     else if (!(PECI_FLAG & F_PECI_INIT5))
//     {
//         PECI_FLAG |= F_PECI_INIT5;
//         //PECI_WritePowerLimit3(32);       
//         return;
//     }
#endif
    else
    {
        if ((PECI_RdPkgCfg_Idx16[2] < 80) || (PECI_RdPkgCfg_Idx16[2] > 120))
        {   // Read TjMax again if the value is zero or not normal(lower than 80'c, larger than 120'c).
            if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_RdPkgCfg_Idx16, _PECI_Domain_0,
                                 0, _PECI_Index_TTR, 0, 0, 5, 5))
            {
                PECI_RdPkgCfg_Idx16_CC = PECI_CompletionCode;
            }
        }
        else
        {
#if 0
            if(PECI_ReadTemp())
            {
                Calc_CPU_Temperature();
            }
#else
             switch (PECI_CNT)
             {
                 case 0:
                     if(PECI_ReadTemp())
                     {
                         Calc_CPU_Temperature();
                     }
//                      PECI_CNT++;
                     PECI_CNT = 0;
                     break;
//                  case 1:
//                      if (IS_ADAPTER_IN() && IS_BATTERY1_OUT())
//                      {
//                         if (PECI_PowerLimit2 != 45)
//                         {
//                             if (PECI_WritePowerLimit2(45))
//                             {
//                                 PECI_ReadPowerLimit2();
//                                 if(PECI_PowerLimit2 == 0xFF)
//                                 {
//                                     break;
//                                 }
//                             }
//                         }
//                      }
//                      PECI_CNT++;
//                      break;
//                  case 2:
//                      if (IS_ADAPTER_IN() && IS_BATTERY1_OUT())
//                      {
//                         if (PECI_PowerLimit4 != 66)
//                         {
//                             if (PECI_WritePowerLimit4(66))
//                             {
//                                 PECI_ReadPowerLimit4();
//                                 if(PECI_PowerLimit4 == 0xFF)
//                                 {
//                                     break;
//                                 }
//                             }
//                         }
//                      }
// //                     PECI_CNT++;
//                      PECI_CNT = 0;
//                      break;
//                 case 3:
////                     PECI_ReadPowerLimit3();
//                     PECI_CNT++;
//                     break;
//                 case 4:
////                     PECI_ReadPowerLimit4();
//                     PECI_CNT++;
//                     break;
//                 case 5:
////                     PECI_WritePowerLimit4_Offset(100);
//                     PECI_CNT++;
//                     break;
//                 case 6:
//                     PECI_ReadPowerLimit4_Offset();
//                     PECI_CNT = 0;
//                     break;
                 default:
                     PECI_CNT = 0;
                     break;
             }
#endif
        }
    }
    
    PECI_DELAY = 20;    /* 20 x 100ms = 2 sec */
}
#if 0
/*-----------------------------------------------------------------------------
 * @subroutine - Service_PECI_Data
 * @function - Service_PECI_Data
 * @upstream - Hook_Timer10msEventB
 * @input    - None
 * @return   - None
 * @note     - Max:~38us,
 */
void Service_PECI_Data(void)
{
    BYTE    i;
    BYTE    PeciBuffer[16];

    while (PECI_FLAG & F_PECI_BUSY)
    {
        if ((HOSTAR & 0xEC) != 0)
        {
            /* Error Bit */
            if (PECI_ERRCNT < 255)
            {
                PECI_ERRCNT++;
            }
            PECI_ERRSTS = HOSTAR;
            HOCTLR = 0x08;      /* PECI module only enable one time */
            //HOCTLR = 0x00;    /* PECI_HostDisable (Will have Glitch Noise)*/
            HOSTAR = 0xFE;  /* ResetPECIStatus  */
            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
        }
        else if (IS_MASK_SET(HOSTAR, FINISH))
        {
            PECI_ERRCNT = 0;
            PECI_ERRSTS = HOSTAR;
            // Tmp_XPntr = (unsigned int *)PECI_MEMADR;
            if (PECI_CMD == _PECI_CMD_GetTemp)
            {
                for (i = 0; i < HORDLR; i++)
                {
                    PECI_GetTemp[i] = HORDDR;
                }
            }
            else if (PECI_CMD == _PECI_CMD_GetDIB)
            {
                for (i = 0; i < HORDLR; i++)
                {
                    PECI_GetDIB[i] = HORDDR;
                }
            }
            else if (PECI_CMD == _PECI_CMD_RdPkgConfig)
            {
                PECI_RdPkgCfg_Idx16_CC = HORDDR;
                for (i = 0; i < HORDLR; i++)
                {
                    PECI_RdPkgCfg_Idx16[i] = HORDDR;
                }
            }
            else
            {
                for (i = 0x00; i < HORDLR; i++)
                {
                    PeciBuffer[i] = HORDDR;
                    //PeciDataPointer++;
                }
            }
            HOCTLR = 0x08;      /* PECI module only enable one time */
            //HOCTLR = 0x00;    /* PECI_HostDisable (Will have Glitch Noise)*/
            HOSTAR = 0xFE;  /* ResetPECIStatus  */

            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            PECI_FLAG |= F_PECI_UPDATED;

            if (PECI_CMD == _PECI_CMD_GetDIB)
            {
                PECI_FLAG |= F_PECI_INIT;
            }
            if (PECI_CMD == _PECI_CMD_GetTemp)
            {
                Calc_CPU_Temperature();
            }
        }
        else
        {
            PECI_TIMER++;
            if (PECI_TIMER > 200)
            {
                PECI_TIMER = 0;
                PECI_OVTCT++;
                HOCTLR = 0x00;  /* PECI_HostDisable */
                HOSTAR = 0xFE;  /* ResetPECIStatus  */
                CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            }
        }
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_PECI_Command
 * @function - Service_PECI_Command
 * @upstream - Hook_Timer100msEventA
 * @input    - None
 * @return   - None
 * @note     - Max:~33us,
 */
void Service_PECI_Command(void)
{
    //-------------------------------------------------------------------------
    //if (SysPowState != _SYSTEM_S0)
    //{
    //    PECI_FLAG = 0;
    //    return;
    //}
    //-------------------------------------------------------------------------
    if (PECI_DELAY > 0)
    {
        PECI_DELAY--;
        return;
    }
    if (PECI_FLAG & F_PECI_BUSY)
    {
        return;
    }
    //-------------------------------------------------------------------------
    HOCTLR = 0x08;      /* PECI module only enable one time */
    //HOCTLR = 0x00;    /* PECI_HostDisable (Will have Glitch Noise)*/
    HOSTAR = 0xFE;      /* ResetPECIStatus  */
    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    if (!(PECI_FLAG & F_PECI_INIT))
    {
        HOTRADDR = _PECI_CPU_ADDR;
        HOWRLR = 0x01;
        HORDLR = 0x08;
        PECI_CMD = _PECI_CMD_GetDIB;
        PeciDataPointer = &PECI_GetDIB[0];
    }
#if SUPPORT_PECI_POWER_CTRL
    else if (!(PECI_FLAG & F_PECI_INIT2))
    {
        PECI_FLAG |= F_PECI_INIT2;
        PECI_ReadPowerUnit();
        return;
    }
    else if (!(PECI_FLAG & F_PECI_INIT3))
    {
        PECI_FLAG |= F_PECI_INIT3;
        // PECI_WritePowerLimit2(15);      /* Example */
        // PECI_WritePowerLimit1(13, 20);  /* Example 13Watt, 20sec */
        return;
    }
    else if (!(PECI_FLAG & F_PECI_INIT4))
    {
        PECI_FLAG |= F_PECI_INIT4;
        PECI_ReadPowerLimit1();
        PECI_ReadPowerLimit2();
        PECI_ReadPowerLimit3();
        PECI_ReadPowerLimit4();
        return;
    }
#endif
    else
    {
        if (PECI_RdPkgCfg_Idx16[2] == 0x00)
        {
            HOTRADDR = _PECI_CPU_ADDR;
            HOWRLR = 0x05;
            HORDLR = 0x05;
            PECI_CMD = _PECI_CMD_RdPkgConfig;
            PeciDataPointer = &PECI_RdPkgCfg_Idx16_CC;
        }
        else
        {
            HOTRADDR = _PECI_CPU_ADDR;
            HOWRLR = 0x01;
            HORDLR = 0x02;
            PECI_CMD = _PECI_CMD_GetTemp;
            PeciDataPointer = &PECI_GetTemp[0];
        }
    }
    HOCMDR = PECI_CMD;

    if (PECI_CMD == _PECI_CMD_RdPkgConfig)
    {
        HOWRDR = 0x02;
        HOWRDR = 16;
        HOWRDR = 0x00;
        HOWRDR = 0x00;
    }
    HOCTLR |= START;    /* PECI_HostControl(START) */
    PECI_TIMER = 0;

    PECI_DELAY = 4;    /* 4 x 500ms = 2.0sec */
    PECI_FLAG |= F_PECI_BUSY;
}
#endif
/*-----------------------------------------------------------------------------
 * @subroutine - Calc_CPU_Temperature
 * @function - Calc_CPU_Temperature
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Calc_CPU_Temperature(void)
{
    if (PECI_FLAG & F_PECI_UPDATED)
    {
        CLEAR_MASK(PECI_FLAG, F_PECI_UPDATED);
        //---------------------------------------------------------------------
        ITempW01 = (PECI_GetTemp[1] << 8) + PECI_GetTemp[0];
        ITempW01 = (~ITempW01) + 1;     /* 2's complement */
        ITempB05 = ITempW01 >> 6;       /* 1/64 degrees centigrade */
        if (Processor_Tj_max == 0)
        {
            PECI_CPU_T = 100 - ITempB05;
            //CPU_Shutdown_T = 100;
            //SCI_Shutdown_T = 95;
            ITempW01 = (PECI_CPU_T * 10);
            xEC_TSR1 = ITempW01;
            xEC_TSR1H = ITempW01 >> 8;
        }
        else
        {
            //CPU_Shutdown_T = Processor_Tj_max + 3;
            //SCI_Shutdown_T = Processor_Tj_max + 0;
            if ((ITempB05 & 0x80) == 0x00)
            {
                PECI_CPU_T = Processor_Tj_max - ITempB05;
            }
            else
            {
                ITempB05 = (~ITempB05);
                PECI_CPU_T = Processor_Tj_max + ITempB05;
            }
            ITempW01 = (PECI_CPU_T * 10);
            xEC_TSR1 = ITempW01;
            xEC_TSR1H = ITempW01 >> 8;
        }
    }
}
#endif
//-----------------------------------------------------------------------------

#if SUPPORT_PECI_SUBROUTINE
/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CheckHostBusy
 * @function - Check PECI interface busy or not
 * @upstream - By call
 * @input    - None
 * @return   - 0 : 30 ms time out,  1 : OK
 * @note     - None
 */
BYTE PECI_CheckHostBusy(void)
{
#if 1
    ITempW01 = 1000;
    while (ITempW01 > 0)
    {
        if (IS_MASK_CLEAR(HOSTAR, HOBY))
        {
            return 1;
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
        ITempW01--;
    }
    return 0;
#else
    /* Init TimeOut Timer for PECI access */
    SettingTimer1(Timer_30ms);

    while (!TF1)
    {
        if (IS_MASK_CLEAR(HOSTAR, HOBY))
        {
            TR1 = 0;
            TF1 = 0;
            ET1 = 1;
            break;
        }
    }

    if (TF1)
    {
        TR1 = 0;
        TF1 = 0;
        ET1 = 1;
        return(0);
    }
    return(1);
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CheckHostFinish
 * @function - Check PECI interface finish or not
 * @upstream - By call
 * @input    - None
 * @return   - 0 : time-out or error
 * @note     - None
 */
BYTE PECI_CheckHostFinish(void)
{
    BYTE    error, status, result;

    error = 0x04;   /* Preset error */

    /* Init TimeOut Timer for PECI access */
    // SettingTimer1(Timer_30ms);
    ITempW01 = 1000;
    while (ITempW01 > 0)
    {
        status = HOSTAR;

        if (status != 0x00)
        {
            if (IS_MASK_SET(status, FINISH))
            {
                error = 0x00;
                break;
            }
            else if (IS_MASK_SET(status, RD_FCS_ERR))
            {
                error = 0x01;
                break;
            }
            else if (IS_MASK_SET(status, WR_FCS_ERR))
            {
                error = 0x01;
                break;
            }
            else if (IS_MASK_SET(status, EXTERR))
            {
                SET_MASK(RSTC4, RPECI);  /* Reset PECI interface */
                error = 0x02;
                break;
            }
            else if (IS_MASK_SET(status, BUSERR))
            {
                SET_MASK(RSTC4, RPECI);  /* Reset PECI interface */
                error = 0x02;
                break;
            }
            else if (IS_MASK_SET(status, TEMPERR))
            {
                error = 0x03;
                break;
            }
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
        ITempW01--;
    }

    if (ITempW01 == 0x00)
    {
        result = 0x00;    /* Error */
    }
    else
    {
        result = 0x01;    /* Finish */
    }
    return(result);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CalcCRC8
 * @function - CRC-8 polynomial
 * @upstream - By call
 * @input    - sourcebyte
 * @return   - PECI_CRC8
 * @note     - None
 */
void PECI_CalcCRC8(BYTE sourcebyte)
{
#if SUPPORT_SOFTWARE_AWFCS
    BYTE    temp;

    PECI_CRC8 ^= sourcebyte;
    temp = PECI_CRC8;

    if (IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp << 1;
        PECI_CRC8 ^= temp;
    }
    else
    {
        temp = temp << 1;
        PECI_CRC8 ^= 0x09;
        PECI_CRC8 ^= temp;
    }

    if (IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp << 1;
        PECI_CRC8 ^= temp;
    }
    else
    {
        temp = temp << 1;
        PECI_CRC8 ^= 0x07;
        PECI_CRC8 ^= temp;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WrPkgConfig
 * @function - Write to the package configuration space (PCS) within the
 *             processor
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *ReadData : the start address of variable to save data
 *             (3) Domain : 0 or 1?
 *                          0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) Index
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 2 or 3 or 5
 *             (9) WriteLen write length 5
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 */
BYTE PECI_RdPkgConfig(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
                      BYTE Index, BYTE LSB, BYTE MSB,
                      BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    HOTRADDR = addr;
    HOWRLR = WriteLen;
    HORDLR = ReadLen;

    if (Domain < 2)
    {
        HOCMDR = _PECI_CMD_RdPkgConfig + Domain;
    }
    else
    {
        HOCMDR = _PECI_CMD_RdPkgConfig;
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
    }

    HOWRDR = Index;
    HOWRDR = LSB;
    HOWRDR = MSB;

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START); */
        if (PECI_CheckHostFinish())
        {
            if (HORDLR != 0x00)
            {
                for (loop = 0; loop < HORDLR; loop++)
                {
                    if (loop == 0x00)
                    {
                        PECI_CompletionCode = HORDDR;
                    }
                    else
                    {
                        *(ReadData + loop - 1) = HORDDR;
                    }
                }

                if (PECI_CompletionCode == _PECI_CC_Valid)
                {
                    done = 0x01;
                }
                else
                {
                    done = 0x00;
                }
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */
    return(done);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WrPkgConfig
 * @function - Write to the package configuration space (PCS) within the
 *             processor
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *WriteData : the start address of variable to wirte data
 *             (3) Domain : 0 or 1?
 *                           0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) Index
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 1
 *             (9) WriteLen write length 0x07 or 0x08 or 0x0A
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 */
BYTE PECI_WrPkgConfig(BYTE addr, XBYTE *WriteData, BYTE Domain, BYTE Retry,
                      BYTE Index, BYTE LSB, BYTE MSB,
                      BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    PECI_CompletionCode = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);

#if SUPPORT_SOFTWARE_AWFCS
    PECI_CRC8 = 0x00;
#else
    /* PECI_HostControl(AWFCS_EN); */
    HOCTLR |= AWFCS_EN;
#endif

    HOTRADDR = addr;
    PECI_CalcCRC8(addr);
    HOWRLR = WriteLen;
    PECI_CalcCRC8(WriteLen);
    HORDLR = ReadLen;
    PECI_CalcCRC8(ReadLen);

    if (Domain < 2)
    {
        HOCMDR = (_PECI_CMD_WrPkgConfig + Domain);
        PECI_CalcCRC8(_PECI_CMD_WrPkgConfig + Domain);
    }
    else
    {
        HOCMDR = _PECI_CMD_WrPkgConfig;
        PECI_CalcCRC8(_PECI_CMD_WrPkgConfig);
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
        PECI_CalcCRC8((_PECI_HostID << 1) + Retry);
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
        PECI_CalcCRC8(_PECI_HostID << 1);
    }

    HOWRDR = Index;
    PECI_CalcCRC8(Index);
    HOWRDR = LSB;
    PECI_CalcCRC8(LSB);
    HOWRDR = MSB;
    PECI_CalcCRC8(MSB);

    for (loop = 0; loop < (WriteLen - 6); loop++)
    {
        HOWRDR = *(WriteData + loop);
        PECI_CalcCRC8(*(WriteData + loop));
    }

#if SUPPORT_SOFTWARE_AWFCS
    /* Inverted MSb of preliminary FCS reslut */
    PECI_CRC8 ^= 0x80;
    HOWRDR = PECI_CRC8;
#endif

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START) */

        if (PECI_CheckHostFinish())
        {
            PECI_CompletionCode = HORDDR;

            if (PECI_CompletionCode == _PECI_CC_Valid)
            {
                done = 0x01;
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */
    return(done);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_RdIAMSR
 * @function - Read to Model Specific Registers function
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *ReadData : the start address of variable to save data
 *             (3) Domain : 0 or 1?
 *                          0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) ProcessorID
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 0x02 or 0x03 or 0x05 or 0x09
 *             (9) WriteLen write length 0x05
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 */
BYTE PECI_RdIAMSR(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
                  BYTE ProcessorID, BYTE LSB, BYTE MSB,
                  BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    HOTRADDR = addr;
    HOWRLR = WriteLen;
    HORDLR = ReadLen;

    if (Domain < 2)
    {
        HOCMDR = (_PECI_CMD_RdIAMSR + Domain);
    }
    else
    {
        HOCMDR = _PECI_CMD_RdIAMSR;
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
    }

    HOWRDR = ProcessorID;
    HOWRDR = LSB;
    HOWRDR = MSB;

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START) */

        if (PECI_CheckHostFinish())
        {
            for (loop = 0; loop < HORDLR; loop++)
            {
                if (loop == 0x00)
                {
                    PECI_CompletionCode = HORDDR;
                }
                else
                {
                    *(ReadData + loop - 1) = HORDDR;
                }
            }

            if (PECI_CompletionCode == _PECI_CC_Valid)
            {
                done = 0x01;
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */

    return(done);
}
#endif  //SUPPORT_PECI_SUBROUTINE
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadDIB
 * @function - The function of PECI3.0 Package read DIB
 * @upstream - By call
 * @input    - None
 * @return   - 1 : done     0 : error
 * @note     - None
 */
BYTE PECI_ReadDIB(void)
{
    BYTE done, index;
    done = 0x00;
    
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    HOTRADDR = _PECI_CPU_ADDR;
    HOWRLR = 0x01;
    HORDLR = 0x08;
    HOCMDR = _PECI_CMD_GetDIB;
    
    if(PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START) */
        if(PECI_CheckHostFinish())
        {
            for(index=0x00;index<HORDLR;index++)
            {
                PECI_GetDIB[index]=HORDDR;
            }
            done = 0x01;
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;      /* ResetPECIStatus  */
    return(done);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadTemp
 * @function - The function of PECI3.0 Package read temp
 * @upstream - By call
 * @input    - None
 * @return   - 1 : done     0 : error
 * @note     - None
 */
BYTE PECI_ReadTemp(void)
{
    BYTE done, i;
    done = 0x00;
    
    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);

    if (!(PECI_FLAG & F_PECI_BUSY))
    {
        HOTRADDR = _PECI_CPU_ADDR;
        HOWRLR = 0x01;
        HORDLR = 0x02;
        HOCMDR = _PECI_CMD_GetTemp;
        HOCTLR |= START;    /* PECI_HostControl(START) */
        PECI_TIMER = 0;
        PECI_FLAG |= F_PECI_BUSY;
    }
    
    while (PECI_FLAG & F_PECI_BUSY)
    {
        if ((HOSTAR & 0xEC) != 0)
        {
            /* Error Bit */
            if (PECI_ERRCNT < 255)
            {
                PECI_ERRCNT++;
            }
            PECI_ERRSTS = HOSTAR;
            HOCTLR = 0x08;      /* PECI module only enable one time */
            //HOCTLR = 0x00;    /* PECI_HostDisable (Will have Glitch Noise)*/
            HOSTAR = 0xFE;  /* ResetPECIStatus  */
            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            done = 0x00;
        }
        else if (IS_MASK_SET(HOSTAR, FINISH))
        {
            PECI_ERRCNT = 0;
            PECI_ERRSTS = HOSTAR;
            for (i = 0; i < HORDLR; i++)
            {
                PECI_GetTemp[i] = HORDDR;
            }

            HOCTLR = 0x08;      /* PECI module only enable one time */
            //HOCTLR = 0x00;    /* PECI_HostDisable (Will have Glitch Noise)*/
            HOSTAR = 0xFE;  /* ResetPECIStatus  */

            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            PECI_FLAG |= F_PECI_UPDATED;
            done = 0x01;
        }
        else
        {
            PECI_TIMER++;
            if (PECI_TIMER > 200)
            {
                PECI_TIMER = 0;
                PECI_OVTCT++;
                HOCTLR = 0x00;  /* PECI_HostDisable */
                HOSTAR = 0xFE;  /* ResetPECIStatus  */
                CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            }
            done = 0x00;
        }
    }
    return(done);
}

#if SUPPORT_PECI_POWER_CTRL
/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerUnit
 * @function - The function of PECI3.0 Package read power unit
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Package Power SKU UNIT Read
 * This feature enables the PECI host to read the units of time, energy and
 * power used in the processor and DRAM power control registers for
 * calculating power and timing parameters. The default value of the power
 * unit field [19:16] is 0111b,energy unit [11:8] is 0000b
 * Power Control Register Unit Calculations:
 * Time:   1s / 2^TIME UNIT,   Default Value: 1s / 2^10 = 976 ¢Ggs
 * Energy: 1J / 2^ENERGY UNIT, Default Value: 1J / 2^16 = 15.3 ¢GgJ
 * Power:  1W / 2^POWER UNIT,  Default Value: 1W / 2^3 = 1/8 W
 */
BYTE PECI_ReadPowerUnit(void)
{
    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer, _PECI_Domain_0,
                         0, _PECI_Index_PPSH, 0, 0, 5, 5))
    {
        PECI_PowerUnit = (PECI_ReadBuffer[0] & 0x0F);    /* Bit[3:0] */
        PECI_EnergyUnit = (PECI_ReadBuffer[1] & 0x1F);   /* Bit[12:8] */
        PECI_TimeUnit = (PECI_ReadBuffer[2] & 0x0F);     /* Bit[19:16] */
#if 1
        PECI_UnitPower = 0x0008;
        PECI_UnitTime = 0x0400;
        PECI_UnitEnergy = 0x4000;
#else
        if (PECI_PowerUnit > 0)
        {
            PECI_UnitPower = 1 << PECI_PowerUnit;
            PECI_UnitEnergy = 1 << PECI_EnergyUnit;
            PECI_UnitTime = 1 << PECI_TimeUnit;
        }
        else
        {
            PECI_UnitPower = 0x0008;
            PECI_UnitTime = 0x0400;
            PECI_UnitEnergy = 0x4000;
        }
#endif
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit1
 * @function - The function of PECI3.0 Package read power limit 1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE PECI_ReadPowerLimit1(void)
{
    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }
    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL1, 0, 0, 5, 5))
    {

        ITempW01 = (PECI_ReadBuffer[1] << 8) + PECI_ReadBuffer[0];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit1 = (ITempW01 / PECI_UnitPower);

        ITempB01 = PECI_ReadBuffer[2] >> 1;
        PECI_PowerLimit1T = (ITempB01 / PECI_UnitTime);
        return TRUE;
    }
    else
    {
        PECI_PowerLimit1 = 0xFF;
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit2
 * @function - The function of PECI3.0 Package read power limit 2
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE PECI_ReadPowerLimit2(void)
{
    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL2, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[1] << 8) + PECI_ReadBuffer[0];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit2 = (ITempW01 / PECI_UnitPower);
        return TRUE;
    }
    else
    {
        PECI_PowerLimit2 = 0xFF;
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit1
 * @function - The function of PECI3.0 Package write power limit 1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE PECI_WritePowerLimit1(BYTE SettingWatts, BYTE SettingTimer)
{
    WORD    wTEMP;

    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    wTEMP = (SettingWatts * PECI_UnitPower);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;

    ITempB01 = 0x11 << 1;    //(SettingTimer * PECI_UnitTime) << 1;
    PECI_WriteBuffer[2] = ITempB01 | 0x01;  //Bit0: Clamp Mode
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0], _PECI_Domain_0,
                         0, _PECI_Index_PPL1, 0, 0, 1, 10))
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit2
 * @function - The function of PECI3.0 Package write power limit 2
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE PECI_WritePowerLimit2(BYTE SettingWatts)
{
    WORD    wTEMP;

    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    wTEMP = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;

    ITempB01 = 0x11 << 1;    //(SettingTimer * PECI_UnitTime) << 1;
    PECI_WriteBuffer[2] = ITempB01 | 0x01;  //Bit0: Clamp Mode
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL2, 0, 0, 1, 10))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit3
 * @function - The function of PECI3.0 Package read power limit 3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_ReadPowerLimit3(void)
{
    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL3, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[1] << 8) + PECI_ReadBuffer[0];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit3 = (ITempW01 / PECI_UnitPower);
        return TRUE;
    }
    else
    {
        PECI_PowerLimit3 = 0xFF;
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit3
 * @function - The function of PECI3.0 Package write power limit 3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_WritePowerLimit3(BYTE SettingWatts)
{
    WORD    wTEMP;

    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    wTEMP = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL3, 0, 0, 1, 10))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit4
 * @function - The function of PECI3.0 Package read power limit 4
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_ReadPowerLimit4(void)
{
    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL4, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[1] << 8) + PECI_ReadBuffer[0];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit4 = (ITempW01 / PECI_UnitPower);
        return TRUE;
    }
    else
    {
        PECI_PowerLimit4 = 0xFF;
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit4
 * @function - The function of PECI3.0 Package write power limit 4
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_WritePowerLimit4(BYTE SettingWatts)
{
    WORD    wTEMP;

    if (!PECI_ReadPowerUnit())
    {
        return FALSE;
    }

    wTEMP = (SettingWatts * PECI_UnitPower);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                         _PECI_Domain_0,
                         0, _PECI_Index_PPL4, 0, 0, 1, 10))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_PECI_POWER_CTRL
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PECI.C */

