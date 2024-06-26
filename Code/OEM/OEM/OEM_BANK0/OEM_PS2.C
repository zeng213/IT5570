/*-----------------------------------------------------------------------------
 * @file     | OEM_PS2.C
 *-----------+-----------------------------------------------------------------
 * @function | PS/2 port function
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
#define DEBUG_OEM_PS2           FALSE




/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_OEM_PS2
#define OemPS2_RamDebug(x)   RamDebug(x)
#else
#define OemPS2_RamDebug(x)   {}
#endif


//*****************************************************************************
// CODE START
//*****************************************************************************
// ----------------------------------------------------------------------------
// To define "Hook_ECACKMouseDriver" is necessary
// If define "Hook_ECACKMouseDriver" EC firmware need Respond mouse driver
//  via Hook_ECRespondtoMouseDriver function
// ----------------------------------------------------------------------------
void Hook_ECRespondtoMouseDriver(BYTE mscmd)
{

}

// ----------------------------------------------------------------------------
// Hook kernel service_ps2 function
// ----------------------------------------------------------------------------
void Hook_service_ps2(BYTE ps2_channel, BYTE ps2_data)
{

}

// ----------------------------------------------------------------------------
// Disable port 0 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_0(void)
{
    DisablePS2Port_0();
}

// ----------------------------------------------------------------------------
// Disable port 1 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_1(void)
{
    DisablePS2Port_1();
}

// ----------------------------------------------------------------------------
// Disable port 2 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_2(void)
{
    DisablePS2Port_2();
}

// ----------------------------------------------------------------------------
// Enable port 0 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_0(void)
{
    EnablePS2Port_0();
}

// ----------------------------------------------------------------------------
// Enable port 1 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_1(void)
{
    EnablePS2Port_1();
}

// ----------------------------------------------------------------------------
// Enable port 0 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_2(void)
{
    EnablePS2Port_2();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void Hook_TPOnlyLowLevelFunc(void)
{

}

#ifdef Hook_Func_DisableTP     // For internal TB disable
//*****************************************************************************
// Hook function for disabling/enabling internal TB.
//
//  parameter :
//      none
//
//  return :
//      InternalTB_Disable : Internal TB is disabled.
//      InternalTB_Enable  : Internal TB is Enabled.
//
//  Note : Always return "InternalTB_Enable" if you don't understand the
//          the use of this function.
//
//*****************************************************************************
BYTE Hook_DisableInternalTB(void)
{
    BYTE result;

#if TouchPad_only               // For Touchpad only project.

    result = InternalTB_Enable;     // return internal tb enable or disable here by condition.

#else
    result = InternalTB_Enable;     // Always return Internal TB is Enabled here.
#endif

    return(result);
}
#endif
// ----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PS2.C */