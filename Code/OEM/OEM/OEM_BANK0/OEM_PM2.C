/*-----------------------------------------------------------------------------
 * @file     | OEM_PM2.C
 * ----------+-----------------------------------------------------------------
 * @function | Power Management Channel-2 Command & Data Handle
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
#define DEBUG_PMC2              FALSE



/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_PMC2
#define PMC2_RamDebug(x)        RamDebug(x)
#else
#define PMC2_RamDebug(x)        {}
#endif
//-----------------------------------------------------------------------------


//*****************************************************************************
// CODE START
//*****************************************************************************

//----------------------------------------------------------------------------
// The function of debuging 68 port
//----------------------------------------------------------------------------
void Hook_68Port(BYTE PM2Data)
{

}

//----------------------------------------------------------------------------
// The function of debuging 6C port
//----------------------------------------------------------------------------
void Hook_6CPort(BYTE PM2Cmd)
{
    if (PM2Cmd == 0xC9)
    {
        ;
    }
    if (PM2Cmd == 0xDC)
    {
        EA = 0;
        CacheDma(0, ITE_WinFlash);
        EA = 0;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        ITE_WinFlash();
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        /* In ITE_WinFlash, exit will jump main() */
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        /* Notice: MCU not run to here. */
        //SCRA0H = 0x07;    // Clear Scratch SRAM
        //Reload_EC_Ver();
    }
    if (PM2Cmd == 0x10)
    {
        Hook_68Port(PM2Data);
    }
}

//----------------------------------------------------------------------------
// Process Command/Data received from System via 68/6C interface
//----------------------------------------------------------------------------
void service_pci3(void)
{
    if (IS_MASK_CLEAR(PM2STS, P_IBF))
    {
        return;
    }
    if (PM2STS & P_C_D)
    {
        /* Command In */
        PM2Cmd = PM2DI;

        PMC2_RamDebug(0x6C);
        PMC2_RamDebug(PM2Cmd);

        PM2DataCount = 0;
        PM2Data2 = 0;
        EnablePMCIBFInt();
        Hook_6CPort(PM2Cmd);
    }
    else
    {
        /* Data In */
        PM2Data = PM2DI;

        PMC2_RamDebug(0x68);
        PMC2_RamDebug(PM2Data);

        EnablePMCIBFInt();
        Hook_68Port(PM2Data);
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PM2.C */
