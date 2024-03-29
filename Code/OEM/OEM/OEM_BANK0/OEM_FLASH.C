/*-----------------------------------------------------------------------------
 * @file     | OEM_FLASH.C
 *-----------+-----------------------------------------------------------------
 * @function | SPI Flash & Programming
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2021, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
static void ITE_WinFlash6266_Cmd(void);
static void ITE_WinFlash6266_SCI(void);
static void ITE_WinFlash6266_Data(void);

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - ITE_WinFlash
 * @function - ITE_WinFlash
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ITE_WinFlash(void)
{
    RamcodeCmd = 0x00;
    RamcodeSend = 0x00;

    PM2DO = 0x33;       // ACK

    while (1)
    {
        if (IS_MASK_SET(KBHISR, IBF))
        {
            RamcodeCmd = KBHIDIR;
            //continue;
        }
        if (IS_MASK_SET(PM1STS, IBF))
        {
            if (PM1STS & P_C_D)     // Command port
            {
                PM1Cmd  = PM1DI;    // Load command
                PM1Step = 0x00;
                ITE_WinFlash6266_Cmd();
            }
            else                    // Data port
            {
                PM1Data = PM1DI;    // Load data
                if (PM1Step != 0x00)
                {
                    ITE_WinFlash6266_Data();
                    PM1Step--;
                }
            }
            //continue;
        }
        if (IS_MASK_CLEAR(PM2STS, P_IBF)) { continue; }
        if (IS_MASK_CLEAR(PM2STS, P_C_D)) { continue; }
        RamcodeCmd = PM2DI;

        if (RamcodeSend == 1)
        {
            ECINDDR = RamcodeCmd;
            RamcodeSend = 0x00;
            continue;
        }

        if (RamcodeCmd == 0x01)
        {
            ECINDAR3 = EC_Indirect_Selection;   // Enter follow mode
            ECINDAR2 = 0xFF;
            ECINDAR1 = 0xFE;
            ECINDAR0 = 0x00;        // FFFFExx = 0xFF
            ECINDDR = 0x00;         // SCE# high level
        }
        else if (RamcodeCmd == 0x02)
        {
            // Send SPI command
            ECINDAR1 = 0xFD;
            RamcodeSend = 1;
        }
        else if (RamcodeCmd == 0x03)
        {
            // write byte to spi
            RamcodeSend = 1;
        }
        else if (RamcodeCmd == 0x04)
        {
            //while(IS_MASK_SET(PM2STS,P_OBF));
            PM2DO = ECINDDR;        // Read byte from spi
        }
        else if (RamcodeCmd == 0x05)
        {
            ECINDAR3 = 0x00;        //Exit follow mode
            ECINDAR2 = 0x00;
        }
        else if (RamcodeCmd == 0xFC)
        {
            WinFlashMark = 0x33;
            break;
        }
        else if (RamcodeCmd == 0xFE)
        {
#if INTEL_EC_FLASH_AUTO_POWER_ON
            BRAM[62] = 0xA5;    // 0x3E
#endif

#if SUPPORT_FLASH_OFF_SEQUENCE
            WinFlashMark = 0x33;    //Keep Service Mark.
            BRAM[63] = 0xAA;
            break;                  //GoTo Main Service
#else
            /* Used WDT Reset */
            BRAM[63] = 0x55;
#if ITE_CHIP_IT557X
            ETWCFG = EWDKEYEN;      /* Force Watchdog active */
            EWDCNTLLR = 0x01;       // for 1ms counter
            EWDKEYR = 0x5A;         // External WDTreset not match
#else
            WDTRST = 1;             // Reset watch dog timer
            WDTEB = 1;              // Enable watch dog
#endif
            while (1);              // Wait for watch dog time-out
#endif
        }
    }

    main();
}
//-----------------------------------------------------------------------------
void ITE_WinFlash6266_SCI(void)
{
#if SUPPORT_INTERFACE_eSPI
    SET_MASK(VWIDX6, F_IDX6_SCI_VALID);
    CLEAR_MASK(VWIDX6, F_IDX6_SCI);     /* eSPI SCI# */
    SET_MASK(VWIDX6, F_IDX6_SCI_VALID);
    SET_MASK(VWIDX6, F_IDX6_SCI);       /* eSPI SCI# */
#else
    CLEAR_MASK(GPDRD, BIT(4));
    WNCKR = 0x00;       // Delay 15.26 us
    WNCKR = 0x00;       // Delay 15.26 us
    SET_MASK(GPDRD, BIT(4));
#endif
}
//-----------------------------------------------------------------------------
void ITE_WinFlash6266_Cmd(void)
{
    if (PM1Cmd == 0x80)
    {
        ITE_WinFlash6266_SCI();
        PM1Step = 0x01;
    }
    else if (PM1Cmd == 0x81)
    {
        ITE_WinFlash6266_SCI();
        PM1Step = 0x02;
    }
    else if (PM1Cmd == 0x82)
    {
        SET_MASK(PM1STS, BURST); // PM1STS.4 Set Burst mode flag
        // Set Burst Acknowledge byte to send to Host.
        PM1DO = 0x90;
        ITE_WinFlash6266_SCI();
    }
    else if (PM1Cmd == 0x83)
    {
        CLEAR_MASK(PM1STS, BURST);  // PM1STS.4 Set Burst mode flag
        ITE_WinFlash6266_SCI();
    }
    else if (PM1Cmd == 0x84)
    {
        //Query Embedded Controller, QR_EC (0x84)
        PM1DO = 0x00;
        ITE_WinFlash6266_SCI();
        CLEAR_MASK(PM1STS, SCIEVT);
    }
}
//-----------------------------------------------------------------------------
void ITE_WinFlash6266_Data(void)
{
    if (PM1Cmd == 0x80)
    {
        //SendFromAcpi(Hook_ReadMapECSpace(PM1Data));
        Tmp_XPntr = (MEM_EC_SPACE | PM1Data);
        PM1DO = *Tmp_XPntr;
        ITE_WinFlash6266_SCI();
    }
    else if (PM1Cmd == 0x81)
    {
        ITE_WinFlash6266_SCI();
        if (PM1Step == 2)
        {
            PM1Data1 = PM1Data;
        }
        else if (PM1Step == 1)
        {
            //Hook_WriteMapECSpace(PM1Data1, PM1Data);
            Tmp_XPntr = (MEM_EC_SPACE | PM1Data1);
            *Tmp_XPntr = PM1Data;
        }
    }
}

#if SUPPORT_WINAPP_ITE_RFDU
/*-----------------------------------------------------------------------------
 * @subroutine - Init_ReadFlashDataUtility
 * @function - Init_ReadFlashDataUtility
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_ReadFlashDataUtility(void)
{
    /* SPIBuffer[256] addrss = 0x0C00 */
    xFREAD_BufferAddrH = 0x0C;
    xFREAD_BufferAddrL = 0x00;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITE_ReadFlashDataUtility
 * @function - ITE_ReadFlashDataUtility
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ITE_ReadFlashDataUtility(void)
{
    if (xFREAD_Enabled > 0)
    {
        F_Service_OEM_4 = 1;
    }
    if (xFREAD_StartNext > 0)
    {
        return;
    }

    if (xFREAD_Enabled == 0xDD)
    {
        // Erase e-flash
        Do_SPI_Read_ID();
        Do_SPI_Write_Enable();
        Do_SPI_Write_Status(SPIStatus_UnlockAll);
        Do_SPI_Write_Enable();
        Do_SPI_Erase(SPICmd_SectorErase,
                     xFREAD_eFlashAddrH,
                     xFREAD_eFlashAddrM,
                     xFREAD_eFlashAddrL);
        Do_SPI_Write_Disable();
        xFREAD_StartNext = 0xBB;
    }
    if (xFREAD_Enabled == 0xEE)
    {
        // Read e-flash
        Tmp_XPntr = (xFREAD_BufferAddrH << 8 +
                     xFREAD_BufferAddrL);
        ECIndirectFastRead(xFREAD_eFlashAddrH,
                           xFREAD_eFlashAddrM,
                           xFREAD_eFlashAddrL,
                           SPI_selection_internal,
                           256,
                           Tmp_XPntr);
        xFREAD_StartNext = 0xAA;
        /* Auto Increase Address Pointer */
        xFREAD_eFlashAddrM++;
        if (xFREAD_eFlashAddrM == 0)
        {
            xFREAD_eFlashAddrH++;
        }
    }
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_WINAPP_ITE_RFDU

/*-----------------------------------------------------------------------------
 * End of OEM_FLASH.C */
