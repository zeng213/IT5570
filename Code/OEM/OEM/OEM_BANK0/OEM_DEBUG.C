/*-----------------------------------------------------------------------------
 * @file     | OEM_DEBUG.C
 *-----------+-----------------------------------------------------------------
 * @function | Process Debug Function
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
#define RAMDEBUG_FULL_STOP      FALSE


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//*****************************************************************************
// CODE START
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - RamDebug
 * @function - Debug code to RAM spaces
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void RamDebug(unsigned char dbgcode)
{
    PORT_BYTE_PNTR ClearIndex;
    PORT_BYTE_PNTR byte_register_pntr;
    BYTE    index;
    BYTE    i;

    byte_register_pntr = DebugRamAddr + DebugRamRange;
    index = *byte_register_pntr;

#if RAMDEBUG_FULL_STOP
    if (index == DebugRamRange)
    {
        return;
    }
#endif

    *byte_register_pntr += 1;

    if (*byte_register_pntr == DebugRamRange)
    {
        *byte_register_pntr = 0;
        ClearIndex = DebugRamAddr;

        for (i = 0; i < DebugRamRange; i++)
        {
            *ClearIndex = 0x00;
            ClearIndex++;
        }
    }

    byte_register_pntr = DebugRamAddr + index;
    *byte_register_pntr = dbgcode;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PRINT_BYTE_ASCII
 * @function - PRINT_BYTE_ASCII
 * @upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void PRINT_BYTE_ASCII(BYTE pcode)
{
    ITempB01 = ((pcode >> 4) & 0x0F) + 0x30;
    if (ITempB01 > 0x39)    {   ITempB01 += 7;  }
    UART2_RBR = ITempB01;
    ITempB01 = (pcode & 0x0F) + 0x30;
    if (ITempB01 > 0x39)    {   ITempB01 += 7;  }
    UART2_RBR = ITempB01;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PRINT_DEC_ASCII
 * @function - PRINT_DEC_ASCII
 * @upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void PRINT_DEC_ASCII(BYTE pcode)
{
    if (pcode > 99)
    {
        ITempB02 = pcode / 100;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
        pcode %= 100;
    }
    if (pcode > 9)
    {
        ITempB02 = pcode / 10;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
    }
    ITempB02 = pcode % 10;
    ITempB01 = (ITempB02 & 0x0F) + 0x30;
    UART2_RBR = ITempB01;
    UART2_RBR = 0x2C;   //','
}

/*-----------------------------------------------------------------------------
 * @subroutine - PRINT_DEC16_ASCII
 * @function - PRINT_DEC16_ASCII
 * @upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void PRINT_DEC16_ASCII(WORD pcode)
{
    if (pcode > 9999)
    {
        ITempB02 = pcode / 10000;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
        pcode %= 10000;
    }
    if (pcode > 999)
    {
        ITempB02 = pcode / 1000;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
        pcode %= 1000;
    }
    if (pcode > 99)
    {
        ITempB02 = pcode / 100;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
        pcode %= 100;
    }
    if (pcode > 9)
    {
        ITempB02 = pcode / 10;
        ITempB01 = (ITempB02 & 0x0F) + 0x30;
        UART2_RBR = ITempB01;
    }
    ITempB02 = pcode % 10;
    ITempB01 = (ITempB02 & 0x0F) + 0x30;
    UART2_RBR = ITempB01;
    UART2_RBR = 0x2C;   //','
}

#if SUPPORT_UART_BATT_MONITOR
/*-----------------------------------------------------------------------------
 * @subroutine - Service_UartBatteryMonitor
 * @function - Debug Batery by UART
 * @upstream - Hook_Timer50msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_UartBatteryMonitor(void)
{
    xUBM_Step++;
    switch (xUBM_Step)
    {
    case 1:
        PRINT_DEC_ASCII(xTIME_HH);
        break;
    case 2:
        PRINT_DEC_ASCII(xTIME_MM);
        break;
    case 3:
        PRINT_DEC_ASCII(xTIME_SS);
        break;
    case 4:
        PRINT_DEC_ASCII(BAT1_RelativeStateOfChgL);
    case 5:
        PRINT_DEC16_ASCII(BAT1_RemainingCapacity);
        break;
    case 6:
        PRINT_DEC16_ASCII(BAT1_FullChargeCapacity);
        break;
    case 7:
        PRINT_DEC16_ASCII(BAT1_Voltage);
        break;
    case 8:
        ITempW01 = BAT1_Current;
        if (ITempW01 & 0x8000)
        {
            UART2_RBR = '-';
            ITempW01 ^= 0xFFFF;
            ITempW01++;
        }
        PRINT_DEC16_ASCII(ITempW01);
        break;
    case 9:
        PRINT_DEC16_ASCII(BAT1_Temperature);
        break;
    case 10:
        PRINT_DEC16_ASCII(CHGR_ChargingVoltageR);
        break;
    case 11:
        PRINT_DEC16_ASCII(CHGR_ChargingCurrentR);
        break;
    case 12:
        PRINT_DEC_ASCII(ChargerLimitHourStart);
        break;
    case 13:
        PRINT_DEC_ASCII(ChargerLimitHourEnd);
        break;
    default:
        if (xUBM_Step > 99)
        {
            xUBM_Step = 0;
            UART2_RBR = 0x0D;
            UART2_RBR = 0x0A;
        }
        break;
    }
}
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_DEBUG.C */