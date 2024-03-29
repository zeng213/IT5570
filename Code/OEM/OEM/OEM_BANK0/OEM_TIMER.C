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
/*-----------------------------------------------------------------------------
 * @subroutine - SettingTimer1
 * @function - Setting Timer1
 * @Upstream - By call
 * @input    - SET_TMR
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SettingTimer1(WORD SET_TMR)
{
    TR1 = 0;                // Disable timer1
    ET1 = 0;                // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = SET_TMR >> 8;     // Set timer1 counter 30ms
    TL1 = SET_TMR;          // Set timer1 counter 30ms
    TF1 = 0;                // Clear overflow flag
    TR1 = 1;                // Enable timer1
}


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//*****************************************************************************
// CODE START
//*****************************************************************************