/*-----------------------------------------------------------------------------
 * @file     | OEM_HOSTIF.C
 * ----------+-----------------------------------------------------------------
 * @function | LPC & Host interface process
 * ----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition (Can move to OEM_Project.H)
 *---------------------------------------------------------------------------*/
//#define   SUPPORT_SIO_UART1
//#define   SUPPORT_SIO_UART2
#define     SUPPORT_SIO_MOUSE
//#define   SUPPORT_SIO_CIR
//#define   SUPPORT_SIO_H2RAM
//#define   SUPPORT_SIO_SSPI
//#define   SUPPORT_SIO_PECI
//#define   SUPPORT_SIO_PMC3
//#define   SUPPORT_SIO_PMC4
//#define   SUPPORT_SIO_PMC5    //SUPPORT_NVIDA_ONE_BYTE
//#define   SUPPORT_SHARED_MEM

/*-----------------------------------------------------------------------------
 * eSPI Module Proess Definition
 *---------------------------------------------------------------------------*/
#define SUPPORT_OOB_SERVICE_MODULE      TRUE
#define DEBUG_OOB_MESSAGE               FALSE

/* eSPI <-> OOB <-> PCH */
#define SUPPORT_OOB_PCH_TEMPERATURE     TRUE
#define PCH_TEMP_GET_OOB_SEC            5

#define SUPPORT_OOB_PCH_RTC_TIME        TRUE
#define RTC_TIME_ONLY_S0                TRUE
#define RTC_TIME_AUTO_COUNT             TRUE
#define RTC_TIME_GET_OOB_SEC            120

/* eSPI <-> OOB <-> PECI */
#define SUPPORT_OOB_PECI_POWER_CTRL     TRUE
#define SUPPORT_OOB_PECI_GetTemp        TRUE
#define OOB_PECI_GetTemp_SEC            1

/* eSPI <-> OOB <-> Intel CrashLog */
#define SUPPORT_OOB_INTEL_CRASHLOG      FALSE
#define _EFLASH_CRASHLOG_ERASE_ADDR     0x01B000
#define _EFLASH_CRASHLOG_SIZE_K         20
#define _EFLASH_CRASHLOG_CPU_ADDR       0x01B000
#define _EFLASH_CRASHLOG_PCH_ADDR       0x01D000
#define _EFLASH_CRASHLOG_INFO_ADDR      0x01FE00
#define _EFLASH_CRASHLOG_CPU_ADRH       (_EFLASH_CRASHLOG_CPU_ADDR >> 16)
#define _EFLASH_CRASHLOG_CPU_ADRM       (_EFLASH_CRASHLOG_CPU_ADDR >> 8)
#define _EFLASH_CRASHLOG_CPU_ADRL       (_EFLASH_CRASHLOG_CPU_ADDR)
#define _EFLASH_CRASHLOG_PCH_ADRH       (_EFLASH_CRASHLOG_PCH_ADDR >> 16)
#define _EFLASH_CRASHLOG_PCH_ADRM       (_EFLASH_CRASHLOG_PCH_ADDR >> 8)
#define _EFLASH_CRASHLOG_PCH_ADRL       (_EFLASH_CRASHLOG_PCH_ADDR)
#define _EFLASH_CRASHLOG_INFO_ADRH      (_EFLASH_CRASHLOG_INFO_ADDR >> 16)
#define _EFLASH_CRASHLOG_INFO_ADRM      (_EFLASH_CRASHLOG_INFO_ADDR >> 8)
#define _EFLASH_CRASHLOG_INFO_ADRL      (_EFLASH_CRASHLOG_INFO_ADDR)

//*****************************************************************************
/* eSPI Slave to PCH OOB PACKET */
//*****************************************************************************
const BYTE code TO_PCH_TEMPERATURE[] =
{   0x21, 0x00, 0x04, 0x02, 0x01, 0x01, 0x0F    };
const BYTE code TO_PCH_RTC_TIME[] =
{   0x21, 0x00, 0x04, 0x02, 0x02, 0x01, 0x0F    };
const BYTE code TO_PCH_PMC_CRASHLOG[] =
{   0x21, 0x00, 0x04, 0x20, 0x20, 0x01, 0x0F    };
/* Intel OOB Crash Log Debug */
//Byte#2: Length[7:0] = 04h
//Byte#3: Dest Slave Addr [7:1] 10h (Intel PCH PMC SMBus MCTP)
//Byte#4: Command Code = 20h-24h(Trigger_CrashLog_and_Extract),Bit0:0
//Byte#5: Byte Count = 01h
//Byte#6: Source Slave Address[7:0] = 0Fh(eSPI slave 0/EC),Bit0:1

/* eSPI OOB <--> PECI */
const BYTE code TO_PCH_PECI_GET_DIB[] =
{   0x21, 0x00, 0x08, 0x20, 0x01, 0x05, 0x0F, 0x30, 0x01, 0x08, 0xF7 };
const BYTE code TO_PCH_PECI_GET_TEMP[] =
{   0x21, 0x00, 0x08, 0x20, 0x01, 0x05, 0x0F, 0x30, 0x01, 0x02, 0x01 };


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_OOB_MESSAGE
#define OOB_RamDebug(x)     RamDebug(x)
#else
#define OOB_RamDebug(x)     {}
#endif

//*****************************************************************************
/* initsio_table */
//*****************************************************************************
const BYTE code initsio_table[] =
{
#ifdef SUPPORT_SIO_UART1
    // Configure and Enable Logical Device 01h(UART1)
    0x07, 0x01, // Select Logical Device 01h(UART1)
    0x60, 0x03, // I/O Base Address 3F8h
    0x61, 0xF8, // I/O Base Address 3F8h
    0x70, 0x04, // Set IRQ=05h for Logical Device 01h(UART1)
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable Logical Device 01h(UART1)
#endif
#ifdef SUPPORT_SIO_UART2
    // Configure and Enable Logical Device 02h(UART2)
    0x07, 0x02, // Select Logical Device 02h(UART2)
    0x30, 0x02, // Enable Logical Device 02h(UART2)
#endif
    // Enable Logical Device 04h(MSWC)
    0x07, 0x04, // Logical Device 04h(MSWC)
    0x30, 0x00, // Enable MSWC
#ifdef SUPPORT_SIO_MOUSE
    // Configure and Enable Logical Device 05h(Mouse)
    0x07, 0x05, // Select Logical Device 05h(Mouse)
    0x70, 0x0C, // Set IRQ=0Ch for Logical Device 05h(Mouse)
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable Logical Device 05h(Mouse)
#endif
    // Configure and Enable Logical Device 06h(KBD)
    0x07, 0x06, // Select Logical Device 06h(KBD)
    0x70, 0x01, // Set IRQ=01h for Logical Device 06h(KBD)
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable Logical Device 06h(Mouse)

#ifdef SUPPORT_SIO_CIR
    0x07, 0x0A, // Enable Logical Device 0Ah(CIR)
    0x60, 0x03, // IO Port 300
    0x61, 0x00, //
    0x70, 0x0A, // IRQ=10 for CIR
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable CIR
#endif
    // Enable Logical Device 10h(RTCT)
    0x07, 0x10, // Logical Device 10h(BRAM)
//  0x60, 0x09,
//  0x61, 0x12, // BRAMLD address is 0x912 (index) and 0x913 (data)
//  0x62, 0x09,
//  0x63, 0x10, // BRAMLD address is 0x910 (index) and 0x911 (data)
    0x60, 0x06,
    0x61, 0x80, // BRAMLD address is 0x680 (index) and 0x681 (data)
    0x62, 0x06,
    0x63, 0x82, // BRAMLD address is 0x682 (index) and 0x683 (data)
    0xF3, 0x3F, // P80 value begin of BRAM (Need 200DH.BIT(7))
    0xF4, 0x3F, // P80 value end of BRAM
    0xF5, 0x3F, // P80 value index of BRAM
    0x70, 0x00, // Clear IRQ=0 for Logical Device 10h(BRAM)
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable BRAM
    // Enable Logical Device 11h(PM1)(Default:62h,66h)
    0x07, 0x11, // Select Logical Device 11h(PM1)
    0x70, 0x00, // Clear IRQ=0 for Logical Device 11h(PM1)
    0x30, 0x01, // Enable Logical Device 11h(PM1)

    // Enable Logical Device 12h(PM2)(Default:68h,6Ch)
    0x07, 0x12, // Select Logical Device 12h(PM2)
    0x60, 0x02,
    0x61, 0x68, // I/O data Address 0268h
    0x62, 0x02,
    0x63, 0x6C, // I/O command Address 026Ch
    0x70, 0x00, // Clear IRQ=0 for Logical Device 12h(PM2)
#if SUPPORT_INTERFACE_eSPI
    0x71, 0x03,
#endif
    0x30, 0x01, // Enable Logical Device 12h(PM2)
#ifdef  SUPPORT_SIO_SSPI
    // Enable Logical Device 13h(SSPI)
    0x07, 0x13, // Select Logical Device 13h(SSPI)
    0x30, 0x01, // Enable Logical Device 13h(SSPI)
#endif
#ifdef  SUPPORT_SIO_PECI
    // Enable Logical Device 14h(PECI)
    0x07, 0x14, // Select Logical Device 14h(PECI)
    0x30, 0x01, // Enable Logical Device 14h(PECI)
#endif
#ifdef SUPPORT_SIO_PMC3
    0x07, 0x17, // Select Logical Device 17h(PMC3)
    0x60, 0x06, // IO Port 6A0
    0x61, 0xA0, //
    0x62, 0x06, // IO Port 6A4
    0x63, 0xA4, //
    0x70, 0x00, // Clear IRQ for Logical Device 17h(PMC3)
    0x71, 0x03,
    0x30, 0x01, // Enable Logical Device 17h(PMC3)
#endif
#ifdef SUPPORT_SIO_PMC4
    0x07, 0x18, // Select Logical Device 18h(PMC4)
    0x60, 0x06, // IO Port 6A2
    0x61, 0xA2, //
    0x62, 0x06, // IO Port 6A6
    0x63, 0xA6, //
    0x70, 0x00, // Clear IRQ for Logical Device 18h(PMC4)
    0x71, 0x03,
    0x30, 0x01, // Enable Logical Device 18h(PMC4)
#endif
#ifdef SUPPORT_SIO_PMC5 //For NVIDA One Byte Mailbox
    0x07, 0x19, // Select Logical Device 19h(PMC5)
    0x60, 0x05, // IO Port 0580
    0x61, 0x80, //
    0x62, 0x05, // IO Port 0584
    0x63, 0x84, //
    0x70, 0x00, // Clear IRQ for Logical Device 19h(PMC5)
    0x71, 0x03,
    0x30, 0x01, // Enable Logical Device 19h(PMC5)
#endif
    // Enable Logical Device 0Fh(Shared Memory)
    0x07, 0x0F, // Logical Device 0Fh(Shared Memory)
    0x60, 0x02, // Set Base address 200h
    0x61, 0x00,
#ifdef SUPPORT_SIO_H2RAM
    // Define EC internal RAM base address on LPC memory space(0xFFD70000).
    0xF5, 0x00, // Host LPC RAM Base Address b7-b4[15:12]  b3-b0 always=0
    0xF6, 0xD7, // Host LPC RAM Base Address b7-b0[23:16]
    0xFC, 0x01, // Host LPC RAM Base Address [24]
    0x70, 0x00, // Clear IRQ for Logical Device 0Fh(Shared Memory)
    0x71, 0x03,
    0x30, 0x01, // MSWC Shared Memory
#endif
#ifdef SUPPORT_SHARED_MEM
    0xF4, 0x09, // MSWC Shared Memory
    0x30, 0x01, // MSWC Shared Memory
#endif
};
//----------------------------------------------------------------------------
#if 0
const BYTE ResetP80Idx_table[] =
{
    0x30, 0x00, // Enable BRAM
    0xF3, 0x3E, // P80 value begin of BRAM (Need 200DH.BIT(7))
    0xF4, 0x3F, // P80 value end of BRAM
    0xF5, 0x3F, // P80 value index of BRAM
    0x30, 0x01, // Enable BRAM
};
#endif
/*-----------------------------------------------------------------------------
 * @subroutine - Init_SIO
 * @function - Initialize EC SuperIO registers
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_SIO(void)
{
    BYTE    code *data_pntr;

    SET_MASK(LSIOHA, LKCFG);
    SET_MASK(IBMAE, CFGAE);
    SET_MASK(IBCTL, CSAE);

    ITempB01 = 0;
    data_pntr = initsio_table;
    while (ITempB01 < (sizeof(initsio_table) / 2))
    {
        IHIOA = 0;      // Set indirect Host I/O Address
        IHD = *data_pntr;
        while (IS_MASK_SET(IBCTL, CWIB));
        data_pntr++;

        IHIOA = 1;      // Set indirect Host I/O Address
        IHD = *data_pntr;
        while (IS_MASK_SET(IBCTL, CWIB));
        data_pntr++;
        ITempB01++;
    }
    CLEAR_MASK(LSIOHA, LKCFG);
    CLEAR_MASK(IBMAE, CFGAE);
    CLEAR_MASK(IBCTL, CSAE);

#ifdef SUPPORT_SIO_H2RAM
    Init_SysMemory2ECRam();
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SysMemory2ECRam
 * @function - Init system memory cycle to EC external ram
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_SysMemory2ECRam(void)
{
#ifdef SUPPORT_SIO_H2RAM
    HRAMW0BA = 0x10;    // Define RAM window 0 base address 0xA00(RAM : 0x80A00 ~ 0x80AFF)
    HRAMW1BA = 0x00;    // Host RAM Windows 1 Base Address
    HRAMW0AAS = HostRamSize256Byte;    // Host RAM Window 0 Size 256 bytes
    HRAMW1AAS = 0x00;   // Host RAM Windows 1 Access Allow Size
    HRAMWC = Window0En; // Enable H2RAM Window 0 and use LPC memory cycle
#endif
}

#if SUPPORT_OOB_SERVICE_MODULE
/*-----------------------------------------------------------------------------
 * @subroutine - Get_OOB_RTC_Time
 * @function - Get_OOB_RTC_Time
 * @Upstream - Service_OOB_Message
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Get_OOB_RTC_Time(void)
{
#if RTC_TIME_ONLY_S0
    if (SysPowState != _SYSTEM_S0)
    {
        return;
    }
#else
    if (IS_MASK_SET(SysPowState, F_PST_BUSY))
    {
        xOOB_GetPCH_RTC_Timer = RTC_TIME_GET_OOB_SEC;
        return;
    }
#endif
    if (xOOB_GetPCH_RTC_Timer > 0)
    {
        xOOB_GetPCH_RTC_Timer--;
#if RTC_TIME_AUTO_COUNT
        xTIME_SS++;
        if (xTIME_SS > 59)
        {
            xTIME_SS = 0x00;
            xTIME_MM++;
            if (xTIME_MM > 59)
            {
                xTIME_MM = 0x00;
                xTIME_HH++;
                if (xTIME_HH > 23)
                {
                    xTIME_HH = 0x00;
                }
            }
        }
#endif
    }
    else
    {
        xOOB_GetPCH_RTC_Timer = RTC_TIME_GET_OOB_SEC;
        OOB_Table_Pntr = &TO_PCH_RTC_TIME;
        Tmp_XPntr = &eSPI_RTC_DATA[0];
        xOOB_PacketMaxLength = 12;
        Process_eSPI_OOB_Message();
        /* Check & Transfer BCD to Dec */
        ITempB01 = (eSPI_RTC_DATA[5] & 0x0F);
        if (ITempB01 > 9) { return; }
        ITempB02 = ((eSPI_RTC_DATA[5] >> 4) & 0x0F) * 10;
        if (ITempB02 > 50) { return; }
        ITempB03 = (eSPI_RTC_DATA[6] & 0x0F);
        if (ITempB03 > 9) { return; }
        ITempB04 = ((eSPI_RTC_DATA[6] >> 4) & 0x0F) * 10;
        if (ITempB04 > 50) { return; }
        ITempB05 = (eSPI_RTC_DATA[7] & 0x0F);
        if (ITempB05 > 9) { return; }
        ITempB06 = ((eSPI_RTC_DATA[7] >> 4) & 0x0F) * 10;
        if (ITempB06 > 20) { return; }
        xTIME_SS = ITempB01 + ITempB02;
        xTIME_MM = ITempB03 + ITempB04;
        xTIME_HH = ITempB05 + ITempB06;
        xTIME_SYNC++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Get_OOB_PCH_Temperature
 * @function - Get_OOB_PCH_Temperature
 * @Upstream - Service_OOB_Message
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Get_OOB_PCH_Temperature(void)
{
    OOB_Table_Pntr = &TO_PCH_TEMPERATURE;
    Tmp_XPntr = &eSPI_PCH_TMPR[0];
    xOOB_PacketMaxLength = 16;
    if (Process_eSPI_OOB_Message())
    {
        xOOB_PCH_Temperature = eSPI_PCH_TMPR[4];
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - OOB_PECI_GetDIB
 * @function - OOB_PECI_GetDIB
 * @Upstream - Service_OOB_Message
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_GetDIB(void)
{
    OOB_Table_Pntr = &TO_PCH_PECI_GET_DIB;
    Tmp_XPntr = &PECI_ReadBuffer[0];
    xOOB_PacketMaxLength = 16;
    Process_eSPI_OOB_Message();
}

/*-----------------------------------------------------------------------------
 * @subroutine - OOB_PECI_GetTemp
 * @function - OOB_PECI_GetTemp
 * @Upstream - Service_OOB_Message
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_GetTemp(void)
{
    OOB_Table_Pntr = &TO_PCH_PECI_GET_TEMP;
    Tmp_XPntr = &PECI_ReadBuffer[0];
    xOOB_PacketMaxLength = 16;
    if (Process_eSPI_OOB_Message())
    {
        xOOB_PECI_Temper[0] = PECI_ReadBuffer[5];
        xOOB_PECI_Temper[1] = PECI_ReadBuffer[6];
        ITempW01 = (WORD)(xOOB_PECI_Temper[1] << 8) + xOOB_PECI_Temper[0];
        ITempW01 = (~ITempW01) + 1;     /* 2's complement */
        ITempB05 = ITempW01 >> 6;       /* 1/64 degrees centigrade */
        if (xOOB_PECI_Tj_max == 0)
        {
            xOOB_PECI_CPU_T = 100 - ITempB05;
        }
        else
        {
            if ((ITempB05 & 0x80) == 0x00)
            {
                xOOB_PECI_CPU_T = xOOB_PECI_Tj_max - ITempB05;
            }
            else
            {
                ITempB05 = (~ITempB05);
                xOOB_PECI_CPU_T = xOOB_PECI_Tj_max + ITempB05;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - OOB_Check_Upstream_Done
 * @function - OOB_Check_Upstream_Done
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE OOB_Check_Upstream_Done(void)
{
    /* Check upstream done */
    xOOB_Failed = 0;
    xOOB_Timeout = 255;
    while (1)
    {
        if (ESUCTRL0 & Upstream_Done)
        {
            break;
        }
        if (xOOB_Timeout > 0)
        {
            xOOB_Timeout--;
        }
        else
        {
            xOOB_Failed = 1;
            break;
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
    }

    if (xOOB_Failed > 0)
    {
        xOOB_FailedCounter++;
        ESUCTRL0 |= Upstream_Done;  /* Wrtie-1 to clear Upstream Done */
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return FALSE;
    }
    ESUCTRL0 |= Upstream_Done;
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - OOB_Check_OOB_Status
 * @function - OOB_Check_OOB_Status
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE OOB_Check_OOB_Status(void)
{
    /* Check OOB status */
    xOOB_Failed = 0;
    xOOB_Timeout = 255;
    while (1)
    {
        if (ESOCTRL0 & PUT_OOB_STATUS)
        {
            break;
        }
        if (xOOB_Timeout > 0)
        {
            xOOB_Timeout--;
        }
        else
        {
            xOOB_Failed = 1;
            break;
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
    }
    if (xOOB_Failed > 0)
    {
        xOOB_FailedCounter++;
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_eSPI_OOB_Message
 * @function - Process_eSPI_OOB_Message
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE Process_eSPI_OOB_Message(void)
{
    ITempB01 = *OOB_Table_Pntr;
    OOB_Table_Pntr++;
    ITempB02 = OOB_Message;
    if (ITempB01 == 0x21)
    {
        ITempB02 = OOB_Message;
    }
    OOB_RamDebug(ITempB02);
    ESUCTRL1 = ITempB02;            //cycle type
    ITempB03 = *OOB_Table_Pntr;
    OOB_Table_Pntr++;
    ESUCTRL2 = ITempB03;     //tag + length[11:8],
    OOB_RamDebug(ITempB03);

    ITempB03 = *OOB_Table_Pntr;
    OOB_Table_Pntr++;
    xOOB_PacketLength = ITempB03;
    ESUCTRL3 = xOOB_PacketLength;   //length[7:0],
    OOB_RamDebug(xOOB_PacketLength);

    ITempB02 = xOOB_PacketLength;
    for (ITempB01 = 0; ITempB01 < ITempB02; ITempB01++)
    {
        ITempB03 = *OOB_Table_Pntr;
        OOB_Table_Pntr++;
        UPSTREAM_DATA[ITempB01] = ITempB03;
        OOB_RamDebug(ITempB03);
    }
#if 1
    /* Patch this can let data stable ? */
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
#endif
    ESUCTRL0 |= Upstream_EN;    //Set upstream enable
    ESUCTRL0 |= Upstream_GO;    //Set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    /* Check upstream done */
    if (!OOB_Check_OOB_Status())
    {
        return FALSE;
    }
    /* Store Put_OOB Length to xOOB_PacketLength */
    ITempB01 = ESOCTRL4;
    xOOB_PacketLength = ITempB01;
    if (ITempB01 > xOOB_PacketMaxLength)
    {
        ITempB01 = xOOB_PacketMaxLength;
    }
    ITempB02 = 0;
    while (ITempB01 > 0)
    {
        /* Read OOB return data */
        *Tmp_XPntr = PUT_OOB_DATA[ITempB02];
        ITempB02++;
        Tmp_XPntr++;
        ITempB01--;
    }
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    xOOB_DataCounter++;
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_eSPI_OOB_CrashLog
 * @function - Process_eSPI_OOB_CrashLog
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_eSPI_OOB_CrashLog(void)
{
    ITempB01 = *OOB_Table_Pntr;
    OOB_Table_Pntr++;
    ITempB02 = OOB_Message;
    if (ITempB01 == 0x21)
    {
        ITempB02 = OOB_Message;
    }
    ESUCTRL1 = ITempB02;            //cycle type
    ESUCTRL2 = *OOB_Table_Pntr;     //tag + length[11:8],
    OOB_Table_Pntr++;
    xOOB_PacketLength = *OOB_Table_Pntr;
    OOB_Table_Pntr++;
    ITempB02 = xOOB_PacketLength;
    for (ITempB01 = 0; ITempB01 < ITempB02; ITempB01++)
    {
        UPSTREAM_DATA[ITempB01] = *OOB_Table_Pntr;
        OOB_Table_Pntr++;
    }
    ESUCTRL3 = xOOB_PacketLength;   //length[7:0],

    ESUCTRL0 |= Upstream_EN;        //set upstream enable
    ESUCTRL0 |= Upstream_GO;        //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return;
    }
    /* Check OOB status */
    xOOB_Failed = 0;
    xOOB_Timeout = 255;
    while (1)
    {
        if (ESOCTRL0 & PUT_OOB_STATUS)
        {
            break;
        }
        if (xOOB_Timeout > 0)
        {
            xOOB_Timeout--;
        }
        else
        {
            xOOB_Failed = 1;
            break;
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
    }
#if 0   /* 1: Skip Failed */
    if (xOOB_Failed > 0)
    {
        xOOB_FailedCounter++;
        ESUCTRL0 |= Upstream_Done;
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return;
    }
#endif
    /* Store Put_OOB Length to xOOB_PacketLength */
    ITempB01 = ESOCTRL4;
    xOOB_PacketLength = ITempB01;
    if (ITempB01 > xOOB_PacketMaxLength)
    {
        ITempB01 = xOOB_PacketMaxLength;
    }
    ITempB02 = 0;
    while (ITempB01 > 0)
    {
        /* Read OOB return data */
        *Tmp_XPntr = PUT_OOB_DATA[ITempB02];
        ITempB02++;
        Tmp_XPntr++;
        ITempB01--;
    }
    ESUCTRL0 |= Upstream_Done;
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    xOOB_DataCounter++;
}

/*-----------------------------------------------------------------------------
 * @subroutine - eSPI_Flash_Read
 * @function - eSPI_Flash_Read
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE eSPI_Flash_Read(BYTE addr3, BYTE addr2, BYTE addr1, BYTE addr0,
                     BYTE length, XBYTE *bufferindex)
{
    if ((IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_READY)) ||
            (IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_ENABLE)))
    {
        return FALSE;
    }
    if ((length == 0) || (length > 64))
    {
        return FALSE;
    }
    ESUCTRL1 = OOB_Flash_Read;  //cycle type
    ESUCTRL2 = 0x20;    //tag + length[11:8],
    ESUCTRL3 = length;  //length[7:0]   ,max support  64 bytes
    UPSTREAM_DATA[0] = addr3;   //address 31-24
    UPSTREAM_DATA[1] = addr2;   //address 23-16
    UPSTREAM_DATA[2] = addr1;   //address 15-8
    UPSTREAM_DATA[3] = addr0;   //address 7-0

    ESUCTRL0 |= Upstream_EN;        //set upstream enable
    ESUCTRL0 |= Upstream_GO;        //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    /* Check upstream done */
    xOOB_Failed = 0;
    xOOB_Timeout = 255;
    while (1)
    {
        /* Check PUT_FLASH_C cycle Type */
        if ((ESUCTRL6 & 0x0F) ==
                Successful_Completion_With_Data_the_only_Completion)
        {
            break;
        }
        if (xOOB_Timeout > 0)
        {
            xOOB_Timeout--;
        }
        else
        {
            xOOB_Failed = 1;
            break;
        }
        /* Delay 15.26 us */
        WNCKR = 0x00;
    }
    if (xOOB_Failed > 0)
    {
        xOOB_FailedCounter++;
        ESUCTRL0 |= Upstream_Done;
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return FALSE;
    }
    /* Store Put_OOB Length to xOOB_PacketLength */
    ITempB01 = length;
    ITempB02 = 0;
    while (ITempB01 > 0)
    {
        /* Read OOB return data */
        *bufferindex = UPSTREAM_DATA[ITempB02];
        ITempB02++;
        bufferindex++;
        ITempB01--;
    }
    ESUCTRL0 |= Upstream_Done;
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - eSPI_Flash_Erase
 * @function - eSPI_Flash_Erase
 * @upstream - By call
 * @input    - mode: 0x01:4K Byte erase 0x02:64K Byte erase
 * @return   - None
 * @note     - None
 */
BYTE eSPI_Flash_Erase(BYTE addr3, BYTE addr2, BYTE addr1, BYTE addr0,
                      BYTE mode)
{
    if ((IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_READY)) ||
            (IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_ENABLE)))
    {
        return FALSE;
    }
    ESUCTRL1 = OOB_Flash_Erase; //cycle type
    ESUCTRL2 = 0x20;        //tag + length[11:8],
    /* ESUCTRL3 001:Support 4K Byte erase
                010:Support 64K Byte erase
                011:Support 4K && 64K Byte erase
    */
    ESUCTRL3 = mode;

    UPSTREAM_DATA[0] = addr3;   //address 31-24
    UPSTREAM_DATA[1] = addr2;   //address 23-16
    UPSTREAM_DATA[2] = addr1;   //address 15-8
    UPSTREAM_DATA[3] = addr0;   //address 7-0

    ESUCTRL0 |= Upstream_EN;        //set upstream enable
    ESUCTRL0 |= Upstream_GO;        //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    /* Check PUT_FLASH_C cycle Type */
    if ((ESUCTRL6 & 0x0F) == Successful_Completion_Without_Data)
    {
        ESUCTRL0 |= Upstream_Done;
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return TRUE;
    }
    ESUCTRL0 |= Upstream_Done;
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - eSPI_Flash_Write
 * @function - eSPI_Flash_Write
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE eSPI_Flash_Write(BYTE addr3, BYTE addr2, BYTE addr1, BYTE addr0,
                      BYTE length, XBYTE *bufferindex)
{
    if ((IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_READY)) ||
            (IS_MASK_CLEAR(REG_3117, F_FLASH_CHN_ENABLE)))
    {
        return FALSE;
    }
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    ESUCTRL1 = OOB_Flash_Write; //cycle type
    ESUCTRL2 = 0x20;        //tag + length[11:8],
    ESUCTRL3 = length;      //length[7:0]   ,max support  64 bytes


    UPSTREAM_DATA[0] = addr3;   //address 31-24
    UPSTREAM_DATA[1] = addr2;   //address 23-16
    UPSTREAM_DATA[2] = addr1;   //address 15-8
    UPSTREAM_DATA[3] = addr0;   //address 7-0

    ITempB01 = 0;
    ITempB02 = 4;
    while (1)
    {
        UPSTREAM_DATA[ITempB02] = *bufferindex;
        ITempB02++;
        bufferindex++;
        ITempB01++;
        if (ITempB01 >= length)
        {
            break;
        }
    }
    ESUCTRL0 |= Upstream_EN;        //set upstream enable
    ESUCTRL0 |= Upstream_GO;        //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    ESUCTRL0 |= Upstream_Done;      //upstream done write 1 clear
    /* Check PUT_FLASH_C cycle Type */
    if ((ESUCTRL6 & 0x0F) == Successful_Completion_Without_Data)
    {
        ESUCTRL0 |= Upstream_Done;
        ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
        return TRUE;
    }
    ESUCTRL0 |= Upstream_Done;  /* Wrtie-1 to clear Upstream Done */
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    return FALSE;
}

#if SUPPORT_OOB_PECI_POWER_CTRL
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
 */
void OOB_PECI_ReadPowerUnit(void)
{
    if (OOB_PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPSH, 0, 0, 5, 5))
    {
        PECI_PowerUnit = (PECI_ReadBuffer[0] & 0x0F);    /* Bit[3:0] */
        PECI_EnergyUnit = (PECI_ReadBuffer[1] & 0x1F);   /* Bit[12:8] */
        PECI_TimeUnit = (PECI_ReadBuffer[2] & 0x0F);     /* Bit[19:16] */

        PECI_UnitEnergy = 1 << PECI_EnergyUnit;
        PECI_UnitTime = 1 << PECI_TimeUnit;
        PECI_UnitPower = 1 << PECI_PowerUnit;
    }
    if (PECI_UnitEnergy == 0)
    {
        PECI_UnitEnergy = 1;
    }
    if (PECI_UnitTime == 0)
    {
        PECI_UnitTime = 1;
    }
    if (PECI_UnitPower == 0)
    {
        PECI_UnitPower = 1;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_RdPkgConfig
 * @function - Read to the package configuration space (PCS) within the
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
BYTE OOB_PECI_RdPkgConfig(BYTE addr, BYTE *ReadData,
                          BYTE Domain, BYTE Retry, BYTE Index,
                          BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
    ESUCTRL1 = OOB_Message;     //eSPI Cycle Type
    ESUCTRL2 = 0x20;            //Tag[3:0]+Length[11:8],
    ESUCTRL3 = 12;             //Length[7:0]=N+3

    UPSTREAM_DATA[0] = 0x20;    //PCH
    UPSTREAM_DATA[1] = 0x01;    //PECI Command
    UPSTREAM_DATA[2] = 9;       //Byte Count N
    UPSTREAM_DATA[3] = 0x0F;    //eSPI Slave 0/EC
    UPSTREAM_DATA[4] = addr;    //PECI Target Address
    UPSTREAM_DATA[5] = WriteLen;
    UPSTREAM_DATA[6] = ReadLen;
    if (Domain < 2)
    {
        UPSTREAM_DATA[7] = _PECI_CMD_RdPkgConfig + Domain;
    }
    else
    {
        UPSTREAM_DATA[7] = _PECI_CMD_RdPkgConfig;
    }
    if (Retry < 2)
    {
        UPSTREAM_DATA[8] = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        UPSTREAM_DATA[8] = (_PECI_HostID << 1);
    }
    UPSTREAM_DATA[9] = Index;
    UPSTREAM_DATA[10] = LSB;
    UPSTREAM_DATA[11] = MSB;

    ESUCTRL0 |= Upstream_EN;    //set upstream enable
    ESUCTRL0 |= Upstream_GO;    //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    /* Check upstream done */
    if (!OOB_Check_OOB_Status())
    {
        return FALSE;
    }
    /* Store Put_OOB Length to xOOB_PacketLength */
    ITempB01 = ESOCTRL4;
    xOOB_PacketLength = ITempB01;
    if (ITempB01 > 16)
    {
        ITempB01 = 16;
    }
    ITempB02 = 0;
    while (ITempB01 > 0)
    {
        /* Read OOB return data */
        *ReadData = PUT_OOB_DATA[ITempB02];
        ITempB02++;
        ReadData++;
        ITempB01--;
    }
    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    xOOB_DataCounter++;
    return TRUE;
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
BYTE OOB_PECI_WrPkgConfig(BYTE addr, BYTE *WriteData,
                          BYTE Domain, BYTE Retry, BYTE Index,
                          BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
    ESUCTRL1 = OOB_Message;     //eSPI Cycle Type
    ESUCTRL2 = 0x20;            //Tag[3:0]+Length[11:8],
    ESUCTRL3 = 5 + WriteLen;    //Length[7:0]=N+3

    UPSTREAM_DATA[0] = 0x20;    //PCH
    UPSTREAM_DATA[1] = 0x01;    //PECI Command
    UPSTREAM_DATA[2] = 2 + WriteLen; //Byte Count N
    UPSTREAM_DATA[3] = 0x0F;    //eSPI Slave 0/EC
    UPSTREAM_DATA[4] = addr;    //PECI Target Address
    UPSTREAM_DATA[5] = WriteLen;
    UPSTREAM_DATA[6] = ReadLen;
    if (Domain < 2)
    {
        UPSTREAM_DATA[7] = _PECI_CMD_WrPkgConfig + Domain;
    }
    else
    {
        UPSTREAM_DATA[7] = _PECI_CMD_WrPkgConfig;
    }
    if (Retry < 2)
    {
        UPSTREAM_DATA[8] = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        UPSTREAM_DATA[8] = (_PECI_HostID << 1);
    }
    UPSTREAM_DATA[9] = Index;
    UPSTREAM_DATA[10] = LSB;
    UPSTREAM_DATA[11] = MSB;

    ITempB02 = 12;
#if 0
    /* Removed Reserved Bytes */
    //for (ITempB01 = 0; ITempB01 < (WriteLen - 7); ITempB01++)
#endif
    /* 20210827+ Added one byte */
    for (ITempB01 = 0; ITempB01 < (WriteLen - 6); ITempB01++)
    {
        UPSTREAM_DATA[ITempB02] = *WriteData;
        WriteData++;
        ITempB02++;
    }

    ESUCTRL0 |= Upstream_EN;    //set upstream enable
    ESUCTRL0 |= Upstream_GO;    //set upstream go

    /* Check upstream done */
    if (!OOB_Check_Upstream_Done())
    {
        return FALSE;
    }
    /* Check upstream done */
    if (!OOB_Check_OOB_Status())
    {
        return FALSE;
    }

    ESOCTRL0 = PUT_OOB_STATUS;  /* Write clear for next OOB receive */
    xOOB_DataCounter++;
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit1
 * @function - The function of PECI3.0 Package read power limit 1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_ReadPowerLimit1(void)
{
    if (PECI_UnitPower == 0)
    {
        OOB_PECI_ReadPowerUnit();
        if (PECI_UnitPower == 0)
        {
            return;
        }
    }
    if (OOB_PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL1, 0, 0, 5, 5))
    {

        ITempW01 = (PECI_ReadBuffer[7] << 8) + PECI_ReadBuffer[6];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit1 = (ITempW01 / PECI_UnitPower);

        ITempB01 = PECI_ReadBuffer[8] >> 1;
        if (PECI_UnitTime > 0)
        {
            PECI_PowerLimit1T = (ITempB01 / PECI_UnitTime);
        }
    }
    else
    {
        PECI_PowerLimit1 = 0xFF;
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
void OOB_PECI_WritePowerLimit1(BYTE SettingWatts, BYTE SettingTimer)
{
    ITempW01 = (SettingWatts * PECI_UnitPower);
    PECI_WriteBuffer[0] = ITempW01;
    PECI_WriteBuffer[1] = (ITempW01 >> 8) | 0x80;

    ITempB01 = (SettingTimer * PECI_UnitTime) << 1;
    PECI_WriteBuffer[2] = ITempB01 | 0x01;  //Bit0: Clamp Mode

    if (OOB_PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL1, 0, 0, 1, 10))
    {
        ;
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
void OOB_PECI_ReadPowerLimit2(void)
{
    if (PECI_UnitPower == 0)
    {
        OOB_PECI_ReadPowerUnit();
        if (PECI_UnitPower == 0)
        {
            return;
        }
    }
    if (OOB_PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL2, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[7] << 8) + PECI_ReadBuffer[6];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit2 = (ITempW01 / PECI_UnitPower);
    }
    else
    {
        PECI_PowerLimit2 = 0xFF;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit2
 * @function - The function of PECI3.0 Package write power limit 2
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_WritePowerLimit2(BYTE SettingWatts)
{
    ITempW01 = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = ITempW01;
    PECI_WriteBuffer[1] = (ITempW01 >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (OOB_PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL2, 0, 0, 1, 10))
    {
        ;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit3
 * @function - The function of PECI3.0 Package read power limit 3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_ReadPowerLimit3(void)
{
    if (PECI_UnitPower == 0)
    {
        OOB_PECI_ReadPowerUnit();
        return;
    }
    if (OOB_PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL3, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[7] << 8) + PECI_ReadBuffer[6];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit3 = (ITempW01 / PECI_UnitPower);
    }
    else
    {
        PECI_PowerLimit3 = 0xFF;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit3
 * @function - The function of PECI3.0 Package write power limit 3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_WritePowerLimit3(BYTE SettingWatts)
{
    ITempW01 = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = ITempW01;
    PECI_WriteBuffer[1] = (ITempW01 >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (OOB_PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL3, 0, 0, 1, 10))
    {
        ;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit4
 * @function - The function of PECI3.0 Package read power limit 4
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_ReadPowerLimit4(void)
{
    if (PECI_UnitPower == 0)
    {
        OOB_PECI_ReadPowerUnit();
        return;
    }
    if (OOB_PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL4, 0, 0, 5, 5))
    {
        ITempW01 = (PECI_ReadBuffer[7] << 8) + PECI_ReadBuffer[6];
        ITempW01 &= 0x7FFF;
        PECI_PowerLimit4 = (ITempW01 / PECI_UnitPower);
    }
    else
    {
        PECI_PowerLimit4 = 0xFF;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit4
 * @function - The function of PECI3.0 Package write power limit 4
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OOB_PECI_WritePowerLimit4(BYTE SettingWatts)
{
    if (PECI_UnitPower == 0)
    {
        OOB_PECI_ReadPowerUnit();
        if (PECI_UnitPower == 0)
        {
            return;
        }
    }
    ITempW01 = (SettingWatts * PECI_UnitPower);
    PECI_WriteBuffer[0] = ITempW01;
    PECI_WriteBuffer[1] = (ITempW01 >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (OOB_PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer[0],
                             _PECI_Domain_0,
                             0, _PECI_Index_PPL4, 0, 0, 1, 10))
    {
        ;
    }
}

#endif // SUPPORT_OOB_PECI_POWER_CTRL

/*-----------------------------------------------------------------------------
 * @subroutine - Service_OOB_Message
 * @function - Service_OOB_Messages
 * @Upstream - Hook_Timer100msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_OOB_Message(void)
{
    if ((IS_MASK_CLEAR(REG_3113, F_OOB_CHN_READY)) ||
            (IS_MASK_CLEAR(REG_3113, F_OOB_CHN_ENABLE)))
    {
        return;
    }
#if SUPPORT_OOB_INTEL_CRASHLOG
    if (xOOB_GET_CRASHLOG > 0)
    {
        return;
    }
#endif
    xOOB_Scan++;
    switch (xOOB_Scan)
    {
    case 1:
#if SUPPORT_OOB_PCH_RTC_TIME
        Get_OOB_RTC_Time();
#else
        /* Manual Debug Mode */
        if (xOOB_GET_RTC_DATA > 0)
        {
            xOOB_GET_RTC_DATA = 0;
            xOOB_GetPCH_RTC_Timer = 0;
            Get_OOB_RTC_Time();
        }
#endif
        break;
    case 2:
#if SUPPORT_OOB_PCH_TEMPERATURE
        if (SysPowState == _SYSTEM_S0)
        {
            if (xOOB_GetPCH_Temper > 1)
            {
                xOOB_GetPCH_Temper--;
            }
            else
            {
                xOOB_GetPCH_Temper = PCH_TEMP_GET_OOB_SEC;
                Get_OOB_PCH_Temperature();
            }
        }
#else
        /* Manual Debug Mode */
        if (xOOB_GET_PCH_TMPR > 0)
        {
            xOOB_GET_PCH_TMPR = 0;
            xOOB_GetPCH_Temper = 0;
            Get_OOB_PCH_Temperature();
        }
#endif
        break;
    case 3:
#if 0   //GET_FLASH TEST SAMPLE CODE
        if (xOOB_GET_FLASH_ADR3 & 0x80)
        {
            eSPI_Flash_Read((xOOB_GET_FLASH_ADR3 & 0x7F),
                            xOOB_GET_FLASH_ADR2,
                            xOOB_GET_FLASH_ADR1,
                            xOOB_GET_FLASH_ADR0,
                            64,
                            &eSPI_FLASH_DATA[0]);
            xOOB_GET_FLASH_ADR3 = 0;
        }
#endif
        break;
    case 4:
        break;
    case 5:
#if 1   //OOB->PECI TEST SAMPLE CODE
        if (xOOB_PECI_TEST == 1)
        {
            OOB_PECI_GetDIB();
            xOOB_PECI_TEST = 0;
        }
#endif
        break;
    case 6:
        break;
    case 7:
#if SUPPORT_OOB_PECI_GetTemp
        if (SysPowState == _SYSTEM_S0)
        {
            if (xOOB_PeciGetCpuT_Timer > 1)
            {
                xOOB_PeciGetCpuT_Timer--;
            }
            else
            {
                xOOB_PeciGetCpuT_Timer = OOB_PECI_GetTemp_SEC;
                OOB_PECI_GetTemp();
            }
        }
#endif
        break;
    case 8:
        break;
    case 9:
#if 1   //OOB->PECI TEST SAMPLE CODE
        if (xOOB_PECI_PLx_Index == 1)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_ReadPowerLimit1();
        }
        if (xOOB_PECI_PLx_Index == 2)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_ReadPowerLimit2();
        }
        if (xOOB_PECI_PLx_Index == 3)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_ReadPowerLimit3();
        }
        if (xOOB_PECI_PLx_Index == 4)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_ReadPowerLimit4();
        }
        if (xOOB_PECI_PLx_Index == 0x81)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_WritePowerLimit1(xOOB_PECI_PLx_Data0, xOOB_PECI_PLx_Data1);
        }
        if (xOOB_PECI_PLx_Index == 0x82)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_WritePowerLimit2(xOOB_PECI_PLx_Data0);
        }
        if (xOOB_PECI_PLx_Index == 0x83)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_WritePowerLimit3(xOOB_PECI_PLx_Data0);
        }
        if (xOOB_PECI_PLx_Index == 0x84)
        {
            xOOB_PECI_PLx_Index = 0;
            OOB_PECI_WritePowerLimit4(xOOB_PECI_PLx_Data0);
        }
#endif
        break;
    default:
        if (xOOB_Scan > 9)
        {
            xOOB_Scan = 0;
        }
        break;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Get_OOB_PMC_CrashLog
 * @function - Get_OOB_PMC_CrashLog
 * @Upstream - Service_OOB_Message
 * @input    - None
 * @return   - None
 * @note     - How to get failure log? Access Memory 4C000000 in Windows OS.
 */
void Get_OOB_PMC_CrashLog(void)
{
    BYTE    i, j;

    if (xOOB_GET_CRASHLOG == _CRASHLOG_ERASE_DATA)
    {
        /* Erase eFlash Data Sectors 0x01B000 ~ 0x01FFFF */
        xOOB_CrashLogAddrH = _EFLASH_CRASHLOG_ERASE_ADDR >> 16;
        xOOB_CrashLogAddrM = _EFLASH_CRASHLOG_ERASE_ADDR >> 8;
#if 1   /* 0: Debug */
        Do_SPI_Read_ID();
        Do_SPI_Write_Enable();
        Do_SPI_Write_Status(SPIStatus_UnlockAll);
        i = 0;
        while (1)
        {
            Do_SPI_Write_Enable();
            Do_SPI_Erase(SPICmd_SectorErase,
                         xOOB_CrashLogAddrH,
                         xOOB_CrashLogAddrM,
                         0x00);
            Do_SPI_Write_Disable();
            xOOB_CrashLogAddrM += 0x04;
            if (xOOB_CrashLogAddrM == 0)
            {
                xOOB_CrashLogAddrH++;
            }
            i++;
            if (i >= _EFLASH_CRASHLOG_SIZE_K)
            {
                break;
            }
        }
#endif
        xOOB_GET_CRASHLOG = _CRASHLOG_GET_CPU_SIZES;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_GET_CPU_SIZES)
    {
    	PECI_RdPkgConfig(_PECI_CPU_ADDR,
        				&PECI_ReadBuffer[0],
        				_PECI_Domain_0,
        				0,
                        73,
                        0,
                        0,
                        9,
                        5);
		wOOB_CrashCpuDataLines = (WORD)(PECI_ReadBuffer[1] << 8) +
        							PECI_ReadBuffer[0];
		wOOB_CrashCpuDataBytes = wOOB_CrashCpuDataLines * 8;     
        wOOB_CrashLogDataIndex = 0;
        xOOB_CrashCpuIndex = 0;
        xOOB_CrashCpuIndexH = 0;
        xOOB_CrashLogAddrH = _EFLASH_CRASHLOG_CPU_ADRH;
        xOOB_CrashLogAddrM = _EFLASH_CRASHLOG_CPU_ADRM;
        xOOB_GET_CRASHLOG = _CRASHLOG_READ_CPU_LOG;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_READ_CPU_LOG)
    {
        i = 0;
        while (1)
        {
        	PECI_RdPkgConfig(_PECI_CPU_ADDR,
            				&eSPI_OOB_DATA[i],
                            _PECI_Domain_0,
                            0,
                            74,
                            xOOB_CrashCpuIndex,
                            xOOB_CrashCpuIndexH,
                            9,
                            5);
            /* Get First 16 Bytes length inforamtion and update total bytes. */
            if ((xOOB_CrashCpuIndexH == 0) &&  (xOOB_CrashCpuIndex == 0))
            {
            	/* eSPI_OOB_DATA[4][5]:= DWORD unit. (4 Bytes) */
                wOOB_CrashCpuDataBytes = (WORD)(eSPI_OOB_DATA[5] << 8) +
                						eSPI_OOB_DATA[4];
                /* Protocol is 8 Bytes per read */
                wOOB_CrashCpuDataBytes <<= 2;
			}

            xOOB_CrashCpuIndex++;
            if (xOOB_CrashCpuIndex == 0)
            {
                xOOB_CrashCpuIndexH++;
            }
            wOOB_CrashLogDataIndex += 8;
            i += 8;
            if (i == 0)
            {
                break;
            }
        }
        xOOB_GET_CRASHLOG = _CRASHLOG_SAVE_CPU_LOG;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_SAVE_CPU_LOG)
    {
#if 1   /* 0: Debug */
        Do_SPI_Read_ID();
        Do_SPI_Write_Enable();
        Do_SPI_Write_Status(SPIStatus_UnlockAll);
        Do_SPI_Write_Enable();
        Do_SPI_Write_256Bytes(&eSPI_OOB_DATA[0],
                              xOOB_CrashLogAddrH,
                              xOOB_CrashLogAddrM,
                              0x00);
        xOOB_CrashLogAddrM += 1;
        Do_SPI_Write_Disable();
#endif
        if (wOOB_CrashLogDataIndex >= wOOB_CrashCpuDataBytes)
        {
            xOOB_GET_CRASHLOG = _CRASHLOG_EXIT_CPU_LOG;
            return;
        }
        xOOB_GET_CRASHLOG = _CRASHLOG_READ_CPU_LOG;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_EXIT_CPU_LOG)
    {
        xOOB_CrashLogAddrH = _EFLASH_CRASHLOG_PCH_ADRH;
        xOOB_CrashLogAddrM = _EFLASH_CRASHLOG_PCH_ADRM;
        wOOB_CrashPchDataSizes = 0;
        wOOB_CrashLogDataIndex = 0;
        xOOB_GET_CRASHLOG = _CRASHLOG_READ_PCH_LOG;
        if (ECHIPVER <= _CHIP_CX)
        {
            xOOB_GET_CRASHLOG = _CRASHLOG_SAVE_INFO;
        }
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_READ_PCH_LOG)
    {
        OOB_Table_Pntr = &TO_PCH_PMC_CRASHLOG;
        Tmp_XPntr = &eSPI_FLASH_DATA[0];
        xOOB_PacketMaxLength = 128;
        Process_eSPI_OOB_CrashLog();
        if (xOOB_PacketLength == 4)
        {
            xOOB_GET_CRASHLOG = _CRASHLOG_EXIT_PCH_LOG;
            return;
        }
        i = 4;   /* Data Start at 4th Byte */
        while (1)
        {
            j = (wOOB_CrashLogDataIndex & 0xFF);
            eSPI_OOB_DATA[j] = eSPI_FLASH_DATA[i];
            wOOB_CrashLogDataIndex++;
            wOOB_CrashPchDataSizes++;
            i++;
            if (i > 67)
            {
                break;
            }
        }
        xOOB_GET_CRASHLOG = _CRASHLOG_SAVE_PCH_LOG;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_SAVE_PCH_LOG)
    {
        if (wOOB_CrashLogDataIndex > 255)
        {
            wOOB_CrashLogDataIndex = 0;
#if 1   /* 0: Debug */
            Do_SPI_Read_ID();
            Do_SPI_Write_Enable();
            Do_SPI_Write_Status(SPIStatus_UnlockAll);
            Do_SPI_Write_Enable();
            Do_SPI_Write_256Bytes(&eSPI_OOB_DATA[0],
                                  xOOB_CrashLogAddrH,
                                  xOOB_CrashLogAddrM,
                                  0x00);
            Do_SPI_Write_Disable();
#endif
            xOOB_CrashLogAddrM++;
            /* Clear 256 Bytes Buffer */
            i = 0;
            while (1)
            {
                eSPI_OOB_DATA[i] = 0;
                eSPI_FLASH_DATA[i] = 0;
                i++;
                if (i == 0)
                {
                    break;
                }
            }
        }
        if (xOOB_PacketLength == 0x44)
        {
            xOOB_GET_CRASHLOG = _CRASHLOG_READ_PCH_LOG;
            return;
        }
        /* Save last data */
        xOOB_GET_CRASHLOG = _CRASHLOG_EXIT_PCH_LOG;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_EXIT_PCH_LOG)
    {
        if (wOOB_CrashLogDataIndex > 0)
        {
            wOOB_CrashLogDataIndex = 0;
#if 1   /* 0: Debug */
            Do_SPI_Read_ID();
            Do_SPI_Write_Enable();
            Do_SPI_Write_Status(SPIStatus_UnlockAll);
            Do_SPI_Write_Enable();
            Do_SPI_Write_256Bytes(&eSPI_OOB_DATA[0],
                                  xOOB_CrashLogAddrH,
                                  xOOB_CrashLogAddrM,
                                  0x00);
            Do_SPI_Write_Disable();
#endif
        }
        xOOB_GET_CRASHLOG = _CRASHLOG_SAVE_INFO;
        return;
    }
    else if (xOOB_GET_CRASHLOG == _CRASHLOG_SAVE_INFO)
    {
        /* Write Information to tail of eFlash */
        eSPI_OOB_DATA[0] = 'C';
        eSPI_OOB_DATA[1] = 'R';
        eSPI_OOB_DATA[2] = 'A';
        eSPI_OOB_DATA[3] = ':';

        eSPI_OOB_DATA[4] = 0x00;
        eSPI_OOB_DATA[5] = _EFLASH_CRASHLOG_CPU_ADRH;
        eSPI_OOB_DATA[6] = _EFLASH_CRASHLOG_CPU_ADRM;
        eSPI_OOB_DATA[7] = _EFLASH_CRASHLOG_CPU_ADRL;
        eSPI_OOB_DATA[8] = wOOB_CrashCpuDataBytes & 0xFF;
        eSPI_OOB_DATA[9] = wOOB_CrashCpuDataBytes >> 8;

        eSPI_OOB_DATA[10] = 0x00;
        eSPI_OOB_DATA[11] = _EFLASH_CRASHLOG_PCH_ADRH;
        eSPI_OOB_DATA[12] = _EFLASH_CRASHLOG_PCH_ADRM;
        eSPI_OOB_DATA[13] = _EFLASH_CRASHLOG_PCH_ADRL;
        eSPI_OOB_DATA[14] = wOOB_CrashPchDataSizes & 0xFF;
        eSPI_OOB_DATA[15] = wOOB_CrashPchDataSizes >> 8;

        eSPI_OOB_DATA[16] = 0x00;
        eSPI_OOB_DATA[17] = _EFLASH_CRASHLOG_PCH_ADRH;
        eSPI_OOB_DATA[18] = _EFLASH_CRASHLOG_PCH_ADRM;
        eSPI_OOB_DATA[19] = _EFLASH_CRASHLOG_PCH_ADRL;
        eSPI_OOB_DATA[20] = wOOB_CrashCpuDataLines & 0xFF;
        eSPI_OOB_DATA[21] = wOOB_CrashCpuDataLines >> 8;
        
        i = 16;
        while (1)
        {
            eSPI_OOB_DATA[i] = 0xFF;
            i++;
            if (i == 0)
            {
                break;
            }
        }
#if 1   /* 0: Debug */
        Do_SPI_Write_Enable();
        Do_SPI_Write_Status(SPIStatus_UnlockAll);
        Do_SPI_Write_Enable();
        Do_SPI_Write_256Bytes(&eSPI_OOB_DATA[0],
                              _EFLASH_CRASHLOG_INFO_ADRH,
                              _EFLASH_CRASHLOG_INFO_ADRM,
                              _EFLASH_CRASHLOG_INFO_ADRL);
        Do_SPI_Write_Disable();
#endif
    }
    xOOB_GET_CRASHLOG = _CRASHLOG_END;
}

//-----------------------------------------------------------------------------
#endif // SUPPORT_OOB_SERVICE_MODULE
/*-----------------------------------------------------------------------------
 * End of OEM_HOSTIF.C */