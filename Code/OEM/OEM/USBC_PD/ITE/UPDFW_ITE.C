/*-----------------------------------------------------------------------------
 * @file     | UPDFW_ITE.C
 *-----------+-----------------------------------------------------------------
 * @function | USB Type-C PD Chip Update Firmware
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
#define SUPPORT_UPDFW_MODULE        TRUE
#define SUPPORT_BOOT_UPDFW_MODULE   FALSE   /* TRUE:Enable this module code */
#define SUPPORT_BOOT_UPDFW_EMPTY    FALSE   /* TRUE:Only update rmpty chip */
#define SUPPORT_APP_UPDFW_MODULE    TRUE    /* TRUE:Enable this module code */
#define USING_I2C_CHN_A_TO_PD       TRUE
#define USING_I2C_CHN_B_TO_PD       FALSE
#define USING_I2C_CHN_C_TO_PD       FALSE
#define USING_I2C_CHN_D_TO_PD       FALSE
#define PD_BIN_EXT_SPI_OVER_16M     FALSE
#define SUPPORT_IT8851_8853         FALSE
#define SUPPORT_IT8856              TRUE

/*-----------------------------------------------------------------------------
 * Resources & I2C Address & Interrupt pins define
 *---------------------------------------------------------------------------*/
/* Please use common Resources sizes >= 18 */
#define UpdI2cReadBuf               SPIBuffer2
/* Please use common Resources sizes = 256 */
#define PdSpiBuffer                 SPIBuffer

#define _ITE_PD1_FW_SIZE            0x200   /* 256 * 0x200 = 128K */
#define _ITE_FOLLOW_MODE_RETRY      3
#define _ITE_READ_ID_RETRY          3

/*
   Notice: Please place the EC+PD binary
   under external SPI address 1000000H(16M)
 */
#define _PD1_BIN_SPI_ROM_ADDR_H2    0x01
#define _PD1_BIN_SPI_ROM_ADDR_H     0x50    //0x1500000
#define _PD1_BIN_SPI_ROM_ADDR_M     0x00
#define _PD1_BIN_SPI_ROM_ADDR_L     0x00

#define _PD1_BIN_VER_ROM_ADDR_H     _PD1_BIN_SPI_ROM_ADDR_H
#define _PD1_BIN_VER_ROM_ADDR_M     _PD1_BIN_SPI_ROM_ADDR_M
#define _PD1_BIN_VER_ROM_ADDR_L     _PD1_BIN_SPI_ROM_ADDR_L+0x4C

#define _PD2_BIN_SPI_ROM_ADDR_H2    0x01
#define _PD2_BIN_SPI_ROM_ADDR_H     0x04    //Reserved for PD2
#define _PD2_BIN_SPI_ROM_ADDR_M     0x00
#define _PD2_BIN_SPI_ROM_ADDR_L     0x00

#define _PD2_BIN_VER_ROM_ADDR_H     _PD2_BIN_SPI_ROM_ADDR_H
#define _PD2_BIN_VER_ROM_ADDR_M     _PD2_BIN_SPI_ROM_ADDR_M
#define _PD2_BIN_VER_ROM_ADDR_L     _PD2_BIN_SPI_ROM_ADDR_L+0x4C

/*-----------------------------------------------------------------------------
 * DEBUG SWITCH
 *---------------------------------------------------------------------------*/
#define SUPPORT_UPDFW_UARTDEBUG     FALSE
#define SUPPORT_UPDFW_RAMDEBUG      TRUE
#define SUPPORT_UPDFW_SKIP_VERIFY   TRUE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if SUPPORT_UPDFW_RAMDEBUG
#define PdUpd_RamDebug(x)       RamDebug(x)
#else
#define PdUpd_RamDebug(x)       {}
#endif
#if SUPPORT_UPDFW_UARTDEBUG
#define PdUpd_UartDebug(x)      UPD_UartDebug(x)
#else
#define PdUpd_UartDebug(x)      {}
#endif
/*-----------------------------------------------------------------------------
 * Local Calling Prototype
 *---------------------------------------------------------------------------*/
//BYTE    xPD1_i2c_addr;

//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#if SUPPORT_UPDFW_UARTDEBUG
/*-----------------------------------------------------------------------------
 * @subroutine - UPD_UartDebug
 * @function - UPD_UartDebug
 * @upstream - By Call
 * @input    - uType, uCode
 * @return   - None
 * @note     - None
 */
void UPD_UartDebug(BYTE uType, BYTE uCode1, BYTE uCode2)
{
    if ((UART1_LSR & BIT5) == 0)
    {
        return;
    }
    UART1_RBR = 0x0D;
    UART1_RBR = 0x0A;
    ITempB01 = ((uCode1 >> 4) & 0x0F) + 0x30;
    ITempB02 = (uCode1 & 0x0F) + 0x30;
    if (ITempB01 > 0x39) { ITempB01 += 7; }
    if (ITempB02 > 0x39) { ITempB02 += 7; }
    ITempB03 = ((uCode2 >> 4) & 0x0F) + 0x30;
    ITempB04 = (uCode2 & 0x0F) + 0x30;
    if (ITempB03 > 0x39) { ITempB03 += 7; }
    if (ITempB04 > 0x39) { ITempB04 += 7; }
    if (uType == 0)
    {
        UART1_RBR = 'P';
        UART1_RBR = 'B';
    }
    else if (uType == 1)
    {
        UART1_RBR = 'U';
        UART1_RBR = 'C';
    }
    else if (uType == 2)
    {
        UART1_RBR = 'P';
        UART1_RBR = 'D';
    }
    UART1_RBR = ITempB01;
    UART1_RBR = ITempB02;
    UART1_RBR = ITempB03;
    UART1_RBR = ITempB04;
}
#endif


#if USING_I2C_CHN_A_TO_PD
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH0_WrToRdStream
 * @function - I2C Channel-2 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - if RdLen = 0 -> support Write Stream
 */
BYTE EC_PD_CH0_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen)
{
    BYTE    j, t;

    HOSTA_A = 0xFE;
    HOCTL2_A = (I2C_EN | SMHEN);
    if (WrLen > 0)
    {
        TRASLA_A = (I2C_Addr & 0xFE);
        HOBDB_A = *Var;
        HOCTL_A = (SMbusEXT | HOCTL_SRT);

        t = 0;
        while (1)
        {
            j = HOSTA_A;
            if ((j & HOSTA_BDS) != 0x00)
            {
                WrLen--;
                if (WrLen == 0)
                {
                    break;
                }
                if (WrDly > 0)
                {
                    for (t = 0; t < WrDly; t++)
                    {
                        WNCKR = 0x00;   /* Delay 15.26 us */
                    }
                }
                Var++;
                HOBDB_A = *Var;
                HOSTA_A = 0xFE;
                t = 0;
                continue;
            }
            WNCKR = 0x00;   /* Delay 15.26 us */
            t++;
            if (t > 250)
            {
                HOSTA_A = 0xFE;
                HOCTL_A = HOCTL_KILL;
                HOCTL_A = 0;
                return FALSE;
            }
        }
        /* Check Write Stream Only */
        if (RdLen == 0)
        {
            HOCTL2_A = SMHEN;
            HOSTA_A = HOSTA_BDS;
            WNCKR = 0x00;
            j = HOSTA_A;
            WNCKR = 0x00;
            HOCTL_A = 0;
            return TRUE;
        }
        /* Repeat Start + Address Read */
        HOCTL2_A |= (I2C_SW_EN + I2C_SW_WAIT);
        HOSTA_A = 0xFE;
        HOCTL2_A &= (~I2C_SW_WAIT);

        if (RdLen == 0x01)  { HOCTL_A |= HOCTL_LABY; }
    }
    else
    {
        if (RdLen == 0)
        {
            HOSTA_A = 0xFE;
            return TRUE;
        }
        TRASLA_A = (I2C_Addr | 0x01);
        HOSTA_A = 0xFE;
        D0REG_A = RdLen;
        if (RdLen == 0x01)
        {
            HOCTL_A = (SMbusEXT | HOCTL_SRT | HOCTL_LABY);
        }
        else
        {
            HOCTL_A = (SMbusEXT | HOCTL_SRT);
        }
    }
    t = 0;
    while (1)
    {
        j = HOSTA_A;
        if ((j & HOSTA_BDS) != 0x00)
        {
            RdLen--;
            if (RdLen == 0)
            {
                *Var2 = HOBDB_A;
                break;
            }
            /* RdLen=0xFF,Data first byte = "BYTE WrLen" */
            if (RdLen == 0x01)
            {
                HOCTL_A |= HOCTL_LABY;
            }
            else if (RdLen == 0xFE)
            {
                RdLen = HOBDB_A;   //Byte WrLen
            }
            *Var2 = HOBDB_A;
            Var2++;
            HOSTA_A = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_A = 0xFE;
            //HOCTL_A = HOCTL_KILL;
            WNCKR = 0x00;   /* Delay 15.26 us */
            WNCKR = 0x00;   /* Delay 15.26 us */
            HOSTA_A = 0xFE;
            return FALSE;
        }
    }
    HOCTL2_A = SMHEN;
    HOSTA_A = HOSTA_BDS;
    WNCKR = 0x00;
    j = HOSTA_A;
    WNCKR = 0x00;
    HOCTL_A = 0;
    return TRUE;
}
#endif

#if USING_I2C_CHN_B_TO_PD
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH2_WrToRdStream
 * @function - I2C Channel-2 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - if RdLen = 0 -> support Write Stream
 */
BYTE EC_PD_CH1_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen)
{
    BYTE    j, t;

    HOSTA_B = 0xFE;
    HOCTL2_B = (I2C_EN | SMHEN);
    if (WrLen > 0)
    {
        TRASLA_B = (I2C_Addr & 0xFE);
        HOBDB_B = *Var;
        HOCTL_B = (SMbusEXT | HOCTL_SRT);

        t = 0;
        while (1)
        {
            j = HOSTA_B;
            if ((j & HOSTA_BDS) != 0x00)
            {
                WrLen--;
                if (WrLen == 0)
                {
                    break;
                }
                if (WrDly > 0)
                {
                    for (t = 0; t < WrDly; t++)
                    {
                        WNCKR = 0x00;   /* Delay 15.26 us */
                    }
                }
                Var++;
                HOBDB_B = *Var;
                HOSTA_B = 0xFE;
                t = 0;
                continue;
            }
            WNCKR = 0x00;   /* Delay 15.26 us */
            t++;
            if (t > 250)
            {
                HOSTA_B = 0xFE;
                HOCTL_B = HOCTL_KILL;
                HOCTL_B = 0;
                return FALSE;
            }
        }
        /* Check Write Stream Only */
        if (RdLen == 0)
        {
            HOCTL2_B = SMHEN;
            HOSTA_B = HOSTA_BDS;
            WNCKR = 0x00;
            j = HOSTA_B;
            WNCKR = 0x00;
            HOCTL_B = 0;
            return TRUE;
        }
        /* Repeat Start + Address Read */
        HOCTL2_B |= (I2C_SW_EN + I2C_SW_WAIT);
        HOSTA_B = 0xFE;
        HOCTL2_B &= (~I2C_SW_WAIT);

        if (RdLen == 0x01)  { HOCTL_B |= HOCTL_LABY; }
    }
    else
    {
        if (RdLen == 0)
        {
            HOSTA_B = 0xFE;
            return TRUE;
        }
        TRASLA_B = (I2C_Addr | 0x01);
        HOSTA_B = 0xFE;
        D0REG_B = RdLen;
        if (RdLen == 0x01)
        {
            HOCTL_B = (SMbusEXT | HOCTL_SRT | HOCTL_LABY);
        }
        else
        {
            HOCTL_B = (SMbusEXT | HOCTL_SRT);
        }
    }
    t = 0;
    while (1)
    {
        j = HOSTA_B;
        if ((j & HOSTA_BDS) != 0x00)
        {
            RdLen--;
            if (RdLen == 0)
            {
                *Var2 = HOBDB_B;
                break;
            }
            /* RdLen=0xFF,Data first byte = "BYTE WrLen" */
            if (RdLen == 0x01)
            {
                HOCTL_B |= HOCTL_LABY;
            }
            else if (RdLen == 0xFE)
            {
                RdLen = HOBDB_B;   //Byte WrLen
            }
            *Var2 = HOBDB_B;
            Var2++;
            HOSTA_B = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_B = 0xFE;
            HOCTL_B = HOCTL_KILL;
            HOCTL_B = 0;
            return FALSE;
        }
    }
    HOCTL2_B = SMHEN;
    HOSTA_B = HOSTA_BDS;
    WNCKR = 0x00;
    j = HOSTA_B;
    WNCKR = 0x00;
    HOCTL_B = 0;
    return TRUE;
}
#endif

#if USING_I2C_CHN_C_TO_PD
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH3_WrToRdStream
 * @function - I2C Channel-3 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - if RdLen = 0 -> support Write Stream
 */
BYTE EC_PD_CH2_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen)
{
    BYTE    j, t;

    HOSTA_C = 0xFE;
    HOCTL2_C = (I2C_EN | SMHEN);
    if (WrLen > 0)
    {
        TRASLA_C = (I2C_Addr & 0xFE);
        HOBDB_C = *Var;
        HOCTL_C = (SMbusEXT | HOCTL_SRT);

        t = 0;
        while (1)
        {
            j = HOSTA_C;
            if ((j & HOSTA_BDS) != 0x00)
            {
                WrLen--;
                if (WrLen == 0)
                {
                    break;
                }
                if (WrDly > 0)
                {
                    for (t = 0; t < WrDly; t++)
                    {
                        WNCKR = 0x00;   /* Delay 15.26 us */
                    }
                }
                Var++;
                HOBDB_C = *Var;
                HOSTA_C = 0xFE;
                t = 0;
                continue;
            }
            WNCKR = 0x00;   /* Delay 15.26 us */
            t++;
            if (t > 250)
            {
                HOSTA_C = 0xFE;
                HOCTL_C = HOCTL_KILL;
                HOCTL_C = 0;
                return FALSE;
            }
        }
        /* Check Write Stream Only */
        if (RdLen == 0)
        {
            HOCTL2_C = SMHEN;
            HOSTA_C = HOSTA_BDS;
            WNCKR = 0x00;
            j = HOSTA_C;
            WNCKR = 0x00;
            HOCTL_C = 0;
            return TRUE;
        }
        /* Repeat Start + Address Read */
        HOCTL2_C |= (I2C_SW_EN + I2C_SW_WAIT);
        HOSTA_C = 0xFE;
        HOCTL2_C &= (~I2C_SW_WAIT);

        if (RdLen == 0x01)  { HOCTL_C |= HOCTL_LABY; }
    }
    else
    {
        if (RdLen == 0)
        {
            HOSTA_C = 0xFE;
            return TRUE;
        }
        TRASLA_C = (I2C_Addr | 0x01);
        HOSTA_C = 0xFE;
        D0REG_C = RdLen;
        if (RdLen == 0x01)
        {
            HOCTL_C = (SMbusEXT | HOCTL_SRT | HOCTL_LABY);
        }
        else
        {
            HOCTL_C = (SMbusEXT | HOCTL_SRT);
        }
    }
    t = 0;
    while (1)
    {
        j = HOSTA_C;
        if ((j & HOSTA_BDS) != 0x00)
        {
            RdLen--;
            if (RdLen == 0)
            {
                *Var2 = HOBDB_C;
                break;
            }
            /* RdLen=0xFF,Data first byte = "BYTE WrLen" */
            if (RdLen == 0x01)
            {
                HOCTL_C |= HOCTL_LABY;
            }
            else if (RdLen == 0xFE)
            {
                RdLen = HOBDB_C;   //Byte WrLen
            }
            *Var2 = HOBDB_C;
            Var2++;
            HOSTA_C = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_C = 0xFE;
            HOCTL_C = HOCTL_KILL;
            HOCTL_C = 0;
            return FALSE;
        }
    }
    HOCTL2_C = SMHEN;
    HOSTA_C = HOSTA_BDS;
    WNCKR = 0x00;
    j = HOSTA_C;
    WNCKR = 0x00;
    HOCTL_C = 0;
    return TRUE;
}
#endif


#if USING_I2C_CHN_D_TO_PD
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH4_WrToRdStream
 * @function - I2C Channel-4 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - if RdLen = 0 -> support Write Stream
 */
BYTE EC_PD_CH3_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen)
{
    BYTE    j, t;

    HOSTA_D = 0xFE;
    HOCTL2_D = (I2C_EN | SMHEN);
    if (WrLen > 0)
    {
        TRASLA_D = (I2C_Addr & 0xFE);
        HOBDB_D = *Var;
        HOCTL_D = (SMbusEXT | HOCTL_SRT);

        t = 0;
        while (1)
        {
            j = HOSTA_D;
            if ((j & HOSTA_BDS) != 0x00)
            {
                WrLen--;
                if (WrLen == 0)
                {
                    break;
                }
                if (WrDly > 0)
                {
                    for (t = 0; t < WrDly; t++)
                    {
                        WNCKR = 0x00;   /* Delay 15.26 us */
                    }
                }
                Var++;
                HOBDB_D = *Var;
                HOSTA_D = 0xFE;
                t = 0;
                continue;
            }
            WNCKR = 0x00;   /* Delay 15.26 us */
            t++;
            if (t > 250)
            {
                HOSTA_D = 0xFE;
                HOCTL_D = HOCTL_KILL;
                HOCTL_D = 0;
                return FALSE;
            }
        }
        /* Check Write Stream Only */
        if (RdLen == 0)
        {
            HOCTL2_D = SMHEN;
            HOSTA_D = HOSTA_BDS;
            WNCKR = 0x00;
            j = HOSTA_D;
            WNCKR = 0x00;
            HOCTL_D = 0;
            return TRUE;
        }
        /* Repeat Start + Address Read */
        HOCTL2_D |= (I2C_SW_EN + I2C_SW_WAIT);
        HOSTA_D = 0xFE;
        HOCTL2_D &= (~I2C_SW_WAIT);

        if (RdLen == 0x01)  { HOCTL_D |= HOCTL_LABY; }
    }
    else
    {
        if (RdLen == 0)
        {
            HOSTA_D = 0xFE;
            return TRUE;
        }
        TRASLA_D = (I2C_Addr | 0x01);
        HOSTA_D = 0xFE;
        D0REG_D = RdLen;
        if (RdLen == 0x01)
        {
            HOCTL_D = (SMbusEXT | HOCTL_SRT | HOCTL_LABY);
        }
        else
        {
            HOCTL_D = (SMbusEXT | HOCTL_SRT);
        }
    }
    t = 0;
    while (1)
    {
        j = HOSTA_D;
        if ((j & HOSTA_BDS) != 0x00)
        {
            RdLen--;
            if (RdLen == 0)
            {
                *Var2 = HOBDB_D;
                break;
            }
            /* RdLen=0xFF,Data first byte = "BYTE WrLen" */
            if (RdLen == 0x01)
            {
                HOCTL_D |= HOCTL_LABY;
            }
            else if (RdLen == 0xFE)
            {
                RdLen = HOBDB_D;   //Byte WrLen
            }
            *Var2 = HOBDB_D;
            Var2++;
            HOSTA_D = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_D = 0xFE;
            HOCTL_D = HOCTL_KILL;
            HOCTL_D = 0;
            return FALSE;
        }
    }
    HOCTL2_D = SMHEN;
    HOSTA_D = HOSTA_BDS;
    WNCKR = 0x00;
    j = HOSTA_D;
    WNCKR = 0x00;
    HOCTL_D = 0;
    return TRUE;
}
#endif

//-----------------------------------------------------------------------------
//*****************************************************************************
// UPDATE PD FIRMWARE CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
#if SUPPORT_UPDFW_MODULE
/*-----------------------------------------------------------------------------
 * @subroutine - Send_ITE_Special_Wave
 * @function - Send_ITE_Special_Wave
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
#pragma ot(7, SIZE)
void Send_ITE_Special_Wave(void)
{
    Delay1MS(10);

    DisableAllInterrupt();
    SLVISELR |= (BIT7 + BIT4);

#if USING_I2C_CHN_A_TO_PD
    GPCRF2 = OUTPUT;    //CLK
    GPCRF3 = OUTPUT;    //DAT
    GPDRF &= ~(BIT3 + BIT2);
    ITempW01 = 2000;
    do
    {
        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT3 + BIT2); //I2C_CHN_A
        ITempB01 |= 0x00;
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT3 + BIT2); //I2C_CHN_A
        ITempB01 |= BIT3;
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT3 + BIT2); //I2C_CHN_A
        ITempB01 |= BIT2;
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT3 + BIT2); //I2C_CHN_A
        ITempB01 |= (BIT3 + BIT2);
        GPDRF = ITempB01;
        ITempW01--;
    }
    while (ITempW01 > 0);

    GPDRF &= ~(BIT3 + BIT2);
    Delay1MS(2);
    GPDRF |= (BIT3 + BIT2);

    SLVISELR &= ~(BIT7 + BIT4);
    /* Init I2C Function for update speed. */
    /* SCLKTS: 0x11:50KHz,0x12:100KHz,0x13:400KHz */
    SCLKTS_A = 0x13;        //400KHZ
    GPCRF2 = ALT + PULL_UP;
    GPCRF3 = ALT + PULL_UP;
#endif
#if USING_I2C_CHN_B_TO_PD
    GPCRC1 = OUTPUT;    //CLK
    GPCRC2 = OUTPUT;    //DAT
    GPDRC &= ~(BIT1 + BIT2);  
    ITempW01 = 2000;
    do
    {
        ITempB01 = GPDRC;
        ITempB01 &= ~(BIT2 + BIT1); //I2C_CHN_B
        ITempB01 |= 0x00;
        GPDRC = ITempB01;

        ITempB01 = GPDRC;
        ITempB01 &= ~(BIT2 + BIT1); //I2C_CHN_B
        ITempB01 |= BIT2;
        GPDRC = ITempB01;

        ITempB01 = GPDRC;
        ITempB01 &= ~(BIT2 + BIT1); //I2C_CHN_B
        ITempB01 |= BIT1;
        GPDRC = ITempB01;

        ITempB01 = GPDRC;
        ITempB01 &= ~(BIT2 + BIT1); //I2C_CHN_B
        ITempB01 |= (BIT2 + BIT1);
        GPDRC = ITempB01;
        ITempW01--;
    }
    while (ITempW01 > 0);

    GPDRC &= ~(BIT2 + BIT1);
    Delay1MS(2);
    GPDRC |= (BIT2 + BIT1);
   
    SLVISELR &= ~(BIT7 + BIT4);
    /* Init I2C Function for update speed. */
    /* SCLKTS: 0x11:50KHz,0x12:100KHz,0x13:400KHz */
    SCLKTS_B = 0x13;        //400KHZ
    GPCRC1 = ALT + PULL_UP;
    GPCRC2 = ALT + PULL_UP;
#endif
#if USING_I2C_CHN_C_TO_PD
    GPCRF6 = OUTPUT;
    GPCRF7 = OUTPUT;
    GPDRF &= ~(BIT6 + BIT7);   
    ITempW01 = 2000;
    do
    {
        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT6 + BIT7); //I2C_CHN_C
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT6 + BIT7); //I2C_CHN_C
        ITempB01 |= BIT7;
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT6 + BIT7); //I2C_CHN_C
        ITempB01 |= BIT6;
        GPDRF = ITempB01;

        ITempB01 = GPDRF;
        ITempB01 &= ~(BIT6 + BIT7); //I2C_CHN_C
        ITempB01 |= (BIT6 + BIT7);
        GPDRF = ITempB01;
        ITempW01--;
    }
    while (ITempW01 > 0);

    GPDRF &= ~(BIT6 + BIT7);
    Delay1MS(2);
    GPDRF |= (BIT6 + BIT7);

    SLVISELR &= ~(BIT7 + BIT4);
    /* Init I2C Function for update speed. */
    /* SCLKTS: 0x11:50KHz,0x12:100KHz,0x13:400KHz */
    SCLKTS_C = 0x13;        //400KHZ
    GPCRF6 = ALT + PULL_UP;
    GPCRF7 = ALT + PULL_UP;
#endif
    //EnableAllInterrupt();
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_read_reg
 * @function - ITEi2c_read_reg
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_read_reg(BYTE RegAddrH, BYTE RegAddrL)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = RegAddrH;
    UpdI2cWriteBuf[1] = RegAddrL;
    
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            return UpdI2cReadBuf[0];
        }
        return 0x00;
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            return UpdI2cReadBuf[0];
        }
        return 0x00;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_write_reg
 * @function - ITEi2c_write_reg
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_write_reg(BYTE RegAddrH, BYTE RegAddrL, BYTE RegData)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = RegAddrH;
    UpdI2cWriteBuf[1] = RegAddrL;
    UpdI2cWriteBuf[2] = RegData;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               3,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               3,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_SpiCommand
 * @function - ITEi2c_SpiCommand
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_SpiCommand(BYTE cmd)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = 0xFF;
    UpdI2cWriteBuf[1] = 0xFE;
    UpdI2cWriteBuf[2] = cmd;
    UpdI2cWriteBuf[3] = 0x01;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               4,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               4,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_SpiAddress
 * @function - ITEi2c_SpiAddress
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_SpiAddress(BYTE AddrH, BYTE AddrM, BYTE AddrL)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = 0xFF;
    UpdI2cWriteBuf[1] = 0xFA;
    UpdI2cWriteBuf[2] = AddrL;
    UpdI2cWriteBuf[3] = AddrM;
    UpdI2cWriteBuf[4] = AddrH;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               5,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               5,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    return FALSE;
}


/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_StopCPU_F
 * @function - ITEi2c_StopCPU_F
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_StopCPU_F(void)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = 0x00;
    UpdI2cWriteBuf[1] = 0xFE;
    UpdI2cWriteBuf[2] = 0x5A;
    UpdI2cWriteBuf[3] = 0xA5;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               4,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               4,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_StopCPU_H
 * @function - ITEi2c_StopCPU_H
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_StopCPU_H(void)
{
    BYTE    UpdI2cWriteBuf[5];

    UpdI2cWriteBuf[0] = 0xFE;
    UpdI2cWriteBuf[1] = 0x5A;
    UpdI2cWriteBuf[2] = 0xA5;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               3,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               3,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiEnterFollowMode
 * @function - ITEi2c_FspiEnterFollowMode
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiEnterFollowMode(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    RetryCnt;

    RetryCnt = _ITE_FOLLOW_MODE_RETRY;
    while (RetryCnt > 0)
    {
        UpdI2cWriteBuf[0] = 0xFF;
        UpdI2cWriteBuf[1] = 0xF8;
        UpdI2cWriteBuf[2] = 0xA5;
        UpdI2cWriteBuf[3] = 0x5A;
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   4,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   0))
            {
                return TRUE;
            }
        }
        else
        {
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   4,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   0))
            {
                return TRUE;
            }
        }
        DelayXms(120);
        RetryCnt--;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiExitFollowMode
 * @function - ITEi2c_FspiExitFollowMode
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiExitFollowMode(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    RetryCnt;

    RetryCnt = _ITE_FOLLOW_MODE_RETRY;
    while (RetryCnt > 0)
    {
        UpdI2cWriteBuf[0] = 0xFF;
        UpdI2cWriteBuf[1] = 0xF8;
        UpdI2cWriteBuf[2] = 0x00;
        UpdI2cWriteBuf[3] = 0x00;
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   4,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   0))
            {
                return TRUE;
            }
        }
        else
        {
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   4,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   0))
            {
                return TRUE;
            }
        }
        DelayXms(120);
        RetryCnt--;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiWriteEnable
 * @function - ITEi2c_FspiWriteEnable
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiWriteEnable(void)
{
    BYTE    UpdI2cWriteBuf[5];

    if (!ITEi2c_SpiCommand(_SPI_CMD_WRITE_ENABLE))
    {
        return FALSE;
    }
    //Delay1MS(1);
    if (!ITEi2c_SpiCommand(_SPI_CMD_READ_STATUS))
    {
        return FALSE;
    }
#if SUPPORT_IT8856
    UpdI2cWriteBuf[0] = 0xFF;
    UpdI2cWriteBuf[1] = 0xF7;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            if (UpdI2cReadBuf[0] == 0xFE)
            {
                return TRUE;
            }
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            if (UpdI2cReadBuf[0] == 0xFE)
            {
                return TRUE;
            }
        }
    }
#endif

#if SUPPORT_IT8851_8853
    UpdI2cWriteBuf[0] = 0x00;
    UpdI2cWriteBuf[1] = 0x00;
    if (EC_PD_WrToRdStream(xPD1_i2c_addr,
                           &UpdI2cWriteBuf[0],
                           2,
                           0,
                           &UpdI2cReadBuf[0],
                           1))
    {
        if ((UpdI2cReadBuf[0] & 0x02) > 0)
        {
            return TRUE;
        }
    }
#endif
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiWriteDisable
 * @function - ITEi2c_FspiWriteDisable
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiWriteDisable(void)
{
    BYTE    UpdI2cWriteBuf[5];

    if (!ITEi2c_SpiCommand(_SPI_CMD_WRITE_DISABLE)) //0x05
    {
        return FALSE;
    }
    //Delay1MS(1);
    if (!ITEi2c_SpiCommand(_SPI_CMD_READ_STATUS))   //0x09
    {
        return FALSE;
    }
#if SUPPORT_IT8856
    UpdI2cWriteBuf[0] = 0xFF;
    UpdI2cWriteBuf[1] = 0xF7;
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            if (UpdI2cReadBuf[0] == 0xFC)
            {
                return TRUE;
            }
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               1))
        {
            if (UpdI2cReadBuf[0] == 0xFC)
            {
                return TRUE;
            }
        }
    }
#endif
#if SUPPORT_IT8851_8853
    UpdI2cWriteBuf[0] = 0x00;
    UpdI2cWriteBuf[1] = 0x00;
    if (EC_PD_WrToRdStream(xPD1_i2c_addr,
                           &UpdI2cWriteBuf[0],
                           2,
                           0,
                           &UpdI2cReadBuf[0],
                           1))
    {
        if ((UpdI2cReadBuf[0] & 0x02) == 0x00)
        {
            return TRUE;
        }
    }
#endif
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiSectorErase
 * @function - ITEi2c_FspiSectorErase
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiSectorErase(BYTE iteFwFlashSectorH, BYTE iteFwFlashSectorM)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    RetryCnt;
    
    if (!ITEi2c_SpiAddress(iteFwFlashSectorH, iteFwFlashSectorM, 0x00))
    {
        return FALSE;
    }
    //Delay1MS(1);
    if (!ITEi2c_SpiCommand(_SPI_CMD_SECTOR_ERASE))
    {
        return FALSE;
    }
    Delay1MS(10);
    RetryCnt = 0;
    while (1)
    {
        UpdI2cWriteBuf[0] = 0xFF;
        UpdI2cWriteBuf[1] = 0xFF;
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   2,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   1))
            {
                if ((UpdI2cReadBuf[0] & 0x10) == 0)
                {
                    return TRUE;
                }
                RetryCnt++;
                if (RetryCnt > 25)
                {
                    return FALSE;
                }
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   2,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   1))
            {
                if ((UpdI2cReadBuf[0] & 0x10) == 0)
                {
                    return TRUE;
                }
                RetryCnt++;
                if (RetryCnt > 25)
                {
                    return FALSE;
                }
            }
            else
            {
                return FALSE;
            }
        }
        Delay1MS(2);
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiBlockWrite256B
 * @function - ITEi2c_FspiBlockWrite256B
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiBlockWrite256B(BYTE iteFwFlashSectorH, BYTE iteFwFlashSectorM, BYTE ProcSign)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    i, aai_index;

    PdUpd_RamDebug(0xFB);
    PdUpd_RamDebug(iteFwFlashSectorH);
    PdUpd_RamDebug(iteFwFlashSectorM);
    PdUpd_RamDebug(ProcSign);

    aai_index = 0;
    if ((iteFwFlashSectorH == 0) && (iteFwFlashSectorM == 0) && (ProcSign == _SKIP_SIGN))
    {
        aai_index = 0x50;
    }
    if (!ITEi2c_SpiAddress(iteFwFlashSectorH, iteFwFlashSectorM, aai_index))
    {
        return FALSE;
    }

    if (!ITEi2c_SpiCommand(_SPI_CMD_AAIW_PROGRAM))
    {
        return FALSE;
    }

    while (1)
    {
        Tmp_XPntr = &PdSpiBuffer[aai_index];
        for (i = 0; i < _ITE_I2C_WRITE_SPI_SIZE; i++)
        {
            UpdI2cReadBuf[i + 2] = *Tmp_XPntr;
            Tmp_XPntr++;
        }
        UpdI2cReadBuf[0] = 0xFF;
        UpdI2cReadBuf[1] = 0xF7;
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (!EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                    &UpdI2cReadBuf[0],
                                    _ITE_I2C_WRITE_SPI_SIZE + 2,
                                    0,
                                    &UpdI2cReadBuf[0],
                                    0))
            {
                return FALSE;
            }
        }
        else
        {
            if (!EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                    &UpdI2cReadBuf[0],
                                    _ITE_I2C_WRITE_SPI_SIZE + 2,
                                    0,
                                    &UpdI2cReadBuf[0],
                                    0))
            {
                return FALSE;
            }
        }
        
        aai_index += _ITE_I2C_WRITE_SPI_SIZE;
        if (aai_index == 0)
        {
            break;
        }
        /* Check write first 64 Byes included Signature */
        if ((aai_index >= 0x50) && (ProcSign == _PROG_SIGN))
        {
            break;
        }
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FspiVerify
 * @function - ITEi2c_FspiVerify
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_FspiVerify(BYTE iteFwFlashSectorH, BYTE iteFwFlashSectorM, BYTE ProcSign)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    i, BlockAddr, WriteLen;

#if SUPPORT_UPDFW_SKIP_VERIFY
    if(xITEPD_FlashUtilitySkipVerifyEn == 0xAA)
    {
        return 1;
    }
#endif
    BlockAddr = 0;
    if ((iteFwFlashSectorH == 0) && (iteFwFlashSectorM == 0) && (ProcSign == _SKIP_SIGN))
    {
        BlockAddr = 0x50;
    }
    if (!ITEi2c_SpiAddress(iteFwFlashSectorH, iteFwFlashSectorM, BlockAddr))
    {
        return 0;
    }
    if (!ITEi2c_SpiCommand(_SPI_CMD_QUAL_DT_READ))
    {
        return 0;
    }
    PdUpd_RamDebug(0xEB);
    PdUpd_RamDebug(iteFwFlashSectorH);
    PdUpd_RamDebug(iteFwFlashSectorM);
    PdUpd_RamDebug(BlockAddr);

    UpdI2cWriteBuf[0] = 0xFF;
    UpdI2cWriteBuf[1] = 0xF7;
    WriteLen = 2;   /* First protocol is write 2 bytes and read */
    while (1)
    {
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   WriteLen,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   _ITE_I2C_READ_SPI_SIZE))
            {
                for (i = 0 ; i < _ITE_I2C_READ_SPI_SIZE ; i++)
                {
                    if (PdSpiBuffer[BlockAddr + i] != UpdI2cReadBuf[i])
                    {
                        return 2;
                    }
                }
                BlockAddr += _ITE_I2C_READ_SPI_SIZE;
                if (BlockAddr == 0x00)
                {
                    return 1;
                }
                WriteLen = 0;   /* Continues read */
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   WriteLen,
                                   0,
                                   &UpdI2cReadBuf[0],
                                   _ITE_I2C_READ_SPI_SIZE))
            {
                for (i = 0 ; i < _ITE_I2C_READ_SPI_SIZE ; i++)
                {
                    if (PdSpiBuffer[BlockAddr + i] != UpdI2cReadBuf[i])
                    {
                        return 2;
                    }
                }
                BlockAddr += _ITE_I2C_READ_SPI_SIZE;
                if (BlockAddr == 0x00)
                {
                    return 1;
                }
                WriteLen = 0;   /* Continues read */
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PDFW_GetVersion
 * @function - PDFW_GetVersion
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE PDFW_GetVersion(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    Retry;

    Retry = 3;
    while (Retry > 0)
    {
        UpdI2cReadBuf[0] = 0;
        UpdI2cReadBuf[1] = 0;

        UpdI2cWriteBuf[0] = _ITEPD_GET_PD_FW_VER;
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   1,
                                   0,
                                   &xPD1_FW_VERSION[0],
                                   2))
            {
                xEC_PD1FWVersion[0] = xPD1_FW_VERSION[0];
                xEC_PD1FWVersion[1] = xPD1_FW_VERSION[1];
                return TRUE;
            }
            else
            {
                /* Re-try */
                Delay1MS(20);
            }
        }
        else
        {
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   1,
                                   0,
                                   &xPD2_FW_VERSION[0],
                                   2))
            {
                xEC_PD2FWVersion[0] = xPD2_FW_VERSION[0];
                xEC_PD2FWVersion[1] = xPD2_FW_VERSION[1];
                return TRUE;
            }
            else
            {
                /* Re-try */
                Delay1MS(20);
            }
        }
        Retry--;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PDFW_FlashProgress
 * @function - PD FW Flash Progress
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE PDFW_CheckVersion(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    Retry;

    //PD1 ,128K+64K; 4C~4F for PD version
    xPD1_FW_VERSION[0] = 0;
    xPD1_FW_VERSION[1] = 0;
#if PD_BIN_EXT_SPI_OVER_16M
    ECFolllowModeRead256Bytes(_PD1_BIN_SPI_ROM_ADDR_H2,
                              _PD1_BIN_SPI_ROM_ADDR_H,
                              _PD1_BIN_SPI_ROM_ADDR_M,
                              _PD1_BIN_SPI_ROM_ADDR_L,
                              SPI_selection_external,
                              &PdSpiBuffer[0]);
    xPD1_BIN_VERSION[0] = PdSpiBuffer[_PD1_BIN_VER_ROM_ADDR_L];
    xPD1_BIN_VERSION[1] = PdSpiBuffer[_PD1_BIN_VER_ROM_ADDR_L+1];
    xPD1_BIN_VERSION[2] = PdSpiBuffer[_PD1_BIN_VER_ROM_ADDR_L+2];
    xPD1_BIN_VERSION[3] = PdSpiBuffer[_PD1_BIN_VER_ROM_ADDR_L+3];
#else
    ECIndirectFastRead(_PD1_BIN_VER_ROM_ADDR_H,
                       _PD1_BIN_VER_ROM_ADDR_M,
                       _PD1_BIN_VER_ROM_ADDR_L,
                       SPI_selection_external,
                       4,
                       &xPD1_BIN_VERSION[0]);
#endif
    xPD1_FW_VERSION[0] = 0;
    xPD1_FW_VERSION[1] = 0; 
    Retry = 3;
    while (Retry > 0)
    {
        UpdI2cReadBuf[0] = 0;
        UpdI2cReadBuf[1] = 0;
        
        UpdI2cWriteBuf[0] = _ITEPD_GET_PD_FW_VER;
        
        if(xITEPD_FlashUtilitySMBusSW == 0)
        {
            if(xPD1_i2c_addr == _ITE_PD1_FLASH_I2C_ADDR)
            {
                xPD1_i2c_addr = _ITE_PD1_I2C_ADDR;
            }
            if (xPD1_i2c_addr == _ITE_PD2_FLASH_I2C_ADDR)
            {
                xPD1_i2c_addr = _ITE_PD2_I2C_ADDR;
            }
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   1,
                                   0,
                                   &xPD1_FW_VERSION[0],
                                   2))
            {
                ITempB01 = ((xPD1_FW_VERSION[1] & 0xF0) >> 4) + 0x30;
                ITempB02 = (xPD1_FW_VERSION[1] & 0x0F) + 0x30;
                break;
            }
            else
            {
                /* Re-try */
                Delay1MS(20);
            }
            if(xPD1_i2c_addr == _ITE_PD1_I2C_ADDR)
            {
                xPD1_i2c_addr = _ITE_PD1_FLASH_I2C_ADDR;
            }
            if (xPD1_i2c_addr == _ITE_PD2_I2C_ADDR)
            {
                xPD1_i2c_addr = _ITE_PD2_FLASH_I2C_ADDR;
            }
        }
        else
        {
            if(xPD2_i2c_addr == _ITE_PD1_FLASH_I2C_ADDR)
            {
                xPD2_i2c_addr = _ITE_PD1_I2C_ADDR;
            }
            if (xPD2_i2c_addr == _ITE_PD2_FLASH_I2C_ADDR)
            {
                xPD2_i2c_addr = _ITE_PD2_I2C_ADDR;
            }
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UpdI2cWriteBuf[0],
                                   1,
                                   0,
                                   &xPD1_FW_VERSION[0],
                                   2))
            {
                ITempB01 = ((xPD1_FW_VERSION[1] & 0xF0) >> 4) + 0x30;
                ITempB02 = (xPD1_FW_VERSION[1] & 0x0F) + 0x30;
                break;
            }
            else
            {
                /* Re-try */
                Delay1MS(20);
            }
            if(xPD2_i2c_addr == _ITE_PD1_I2C_ADDR)
            {
                xPD2_i2c_addr = _ITE_PD1_FLASH_I2C_ADDR;
            }
            if (xPD2_i2c_addr == _ITE_PD2_I2C_ADDR)
            {
                xPD2_i2c_addr = _ITE_PD2_FLASH_I2C_ADDR;
            }
        }
        Retry--;
    }
    
    if(xPD1_i2c_addr == _ITE_PD1_I2C_ADDR)
    {
        xPD1_i2c_addr = _ITE_PD1_FLASH_I2C_ADDR;
    }
    if (xPD1_i2c_addr == _ITE_PD2_I2C_ADDR)
    {
        xPD1_i2c_addr = _ITE_PD2_FLASH_I2C_ADDR;
    }
    
#if SUPPORT_BOOT_UPDFW_EMPTY
    if ((xPD1_FW_VERSION[0] > 0) || (xPD1_FW_VERSION[1] > 0))
    {
        return TRUE;
    }  
#else
    if ((ITempB01 == xPD1_BIN_VERSION[2]) &&
            (ITempB02 == xPD1_BIN_VERSION[3]))
    {
        return TRUE;
    }
#endif
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - PDFW_CheckITEChipID
 * @function - PDFW_CheckITEChipID
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE PDFW_CheckITEChipID(void)
{
    BYTE    rty_cnt, RegD0, RegD1;

    for (rty_cnt = 0; rty_cnt < _ITE_READ_ID_RETRY ; rty_cnt++)
    {
        RegD0 = ITEi2c_read_reg(0xFF, 0xC0);
        RegD1 = ITEi2c_read_reg(0xFF, 0xC1);
        if ((RegD0 == 0x88) && (RegD1 == 0x51))
        {
            return TRUE;
        }
        if ((RegD0 == 0x88) && (RegD1 == 0x53))
        {
            return TRUE;
        }
        if ((RegD0 == 0x88) && (RegD1 == 0x56))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ReadPdFwBinFile
 * @function - Read Binary File fro SPI ROM
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ReadPdFwBinFile(WORD AddrM_Offset)
{
    BYTE    BinAddrH2, BinAddrH, BinAddrM, BinAddrL;

    BinAddrH2 = _PD1_BIN_SPI_ROM_ADDR_H2;
    BinAddrH = _PD1_BIN_SPI_ROM_ADDR_H;
    ITempW01 = AddrM_Offset + _PD1_BIN_SPI_ROM_ADDR_M;
    BinAddrL = _PD1_BIN_SPI_ROM_ADDR_L;
    BinAddrM = (ITempW01 & 0xFF);
    if (ITempW01 > 0xFF)
    {
        BinAddrH++;
    }
    PdUpd_RamDebug(0xDD);
    PdUpd_RamDebug(BinAddrH);
    PdUpd_RamDebug(BinAddrM);
    PdUpd_RamDebug(BinAddrL);
#if PD_BIN_EXT_SPI_OVER_16M
    ECFolllowModeRead256Bytes(BinAddrH2,
                              BinAddrH,
                              BinAddrM,
                              BinAddrL,
                              SPI_selection_external,
                              &PdSpiBuffer[0]);
#else
    Init_EC_Indirect_Selection(SPI_selection_external);
    ECIndirectFastRead(BinAddrH,
                       BinAddrM,
                       BinAddrL,
                       SPI_selection_external,
                       256,
                       &PdSpiBuffer[0]);
#endif
    return TRUE;
}

#if SUPPORT_BOOT_UPDFW_MODULE
/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_FlashProgress
 * @function - PD FW Flash Progress
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Flash PD FW Programming Flow
 * Step01. Special Waveform.
 * Step02. Stop CPU.
 * Step03. Enter SPI Test Mode.
 * Step04. Erase Flash.
 * Step05. Write FW code to flash exclude the signature area
 *         (To avoid the update flow be interrupted)
 * Step06. Read back compare ok
 * Step07. Write Signature to flash
 * Step08. Read back signature and check ok.
 * Step09. Exit SPI Test Mode.
 * Step10. Upgrade FW Done.
 * Step11. WDT Reset.
 */
BYTE ITEi2c_FlashProgress(BYTE PdI2cAddr)
{
    WORD    iteFwFlashSector;
    BYTE    iteFwFlashStep;
    BYTE    iteFwFlash256Cnt;
    BYTE    iteFwErrorCnt;
    BYTE    iteFwErrorCnt2;
    BYTE    RetVal;

    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        xPD1_i2c_addr = PdI2cAddr;
    }
    else
    {
        xPD2_i2c_addr = PdI2cAddr;
    }

    PdUpd_RamDebug(0xCC);
    PdUpd_RamDebug(0xF1);
    /* Check version before Programming PD Firmware */
    if (PDFW_CheckVersion())
    {
        return 0xF2;    //F2 = Not empty and then jump out the loop => Use flash utility to update
    }
    Delay1MS(250);
    Delay1MS(250);
    Delay1MS(250);
    Delay1MS(250);

    PdUpd_RamDebug(0xCC);
    PdUpd_RamDebug(0xF2);
    /* Enter D2EC Mode */
    //Send_ITE_Special_Wave();

    if (!PDFW_CheckITEChipID())
    {
        return 0xF3;    //Error Code = F3
    }

    PdUpd_RamDebug(0xCC);
    PdUpd_RamDebug(0xF3);

    ITEi2c_StopCPU_F();
    ITEi2c_StopCPU_H();

    //PD_FW_UPD_LED_ON();   //For ODM Design

    if (!ITEi2c_FspiEnterFollowMode())  //[40W][FF][F8][A5][5A]
    {
        return 0xF4;    //Error Code = F4
    }

    PdUpd_RamDebug(0xCC);
    PdUpd_RamDebug(0xF4);

    /*
      START ITE FLASH PROGRAMMING ...
    */
    iteFwFlashSector    = 0;
    iteFwErrorCnt       = 0;
    iteFwErrorCnt2      = 0;
    iteFwFlashStep = _ITE_FLASH_ERASE_1K;
    do
    {
        if ((iteFwErrorCnt >= 3) || (iteFwErrorCnt2 >= 3))
            {
                break;
            }
        switch (iteFwFlashStep)
        {
        case _ITE_FLASH_ERASE_1K:       //0x01
            if (ITEi2c_FspiWriteEnable())
            {
                if (ITEi2c_FspiSectorErase(iteFwFlashSector>>8, iteFwFlashSector))
                {
                    ITEi2c_FspiWriteDisable();
                    iteFwFlashStep = _ITE_FLASH_LOAD_BIN256B;
                    iteFwFlash256Cnt = 0;
                    PdUpd_RamDebug(0xE1);
                    PdUpd_RamDebug(iteFwFlashSector);
                }
            }
            break;

        case _ITE_FLASH_LOAD_BIN256B:   //0x02
            if (ReadPdFwBinFile(iteFwFlashSector))
            {
                iteFwFlashStep = _ITE_FLASH_WRITE_256B;
            }
            break;

        case _ITE_FLASH_WRITE_256B:     //0x03
            if (ITEi2c_FspiWriteEnable())
            {
                if (ITEi2c_FspiBlockWrite256B(iteFwFlashSector>>8, iteFwFlashSector,
                                              _SKIP_SIGN))
                {
                    iteFwFlashStep = _ITE_FLASH_VERIFY_256B;
                    PdUpd_RamDebug(0xE2);
                }
            }
            break;

        case _ITE_FLASH_VERIFY_256B:    //0x04
            if (ITEi2c_FspiWriteDisable())
            {
                RetVal = ITEi2c_FspiVerify(iteFwFlashSector>>8, iteFwFlashSector,
                                           _SKIP_SIGN);
                if (RetVal == 1)
                {
                    iteFwFlashSector++;
                    if (iteFwFlashSector == _ITE_PD1_FW_SIZE)
                    {
                        iteFwFlashStep = _ITE_FLASH_WRITE_SIG;
                    }
                    else
                    {
                        /* Erase 1K -> Write & Verify 4 times 256B */
                        iteFwFlash256Cnt++;
                        if (iteFwFlash256Cnt >= 4)
                        {
                            iteFwFlashStep = _ITE_FLASH_ERASE_1K;
                        }
                        else
                        {
                            /* Write & Verify 4 times 256B */
                            iteFwFlashStep = _ITE_FLASH_LOAD_BIN256B;
                        }
                    }
                    iteFwErrorCnt = 0;
                }
                else if (RetVal == 2)
                {
                    iteFwFlashSector &= (~0x03);
                    iteFwFlashStep = _ITE_FLASH_ERASE_1K;   
                    iteFwErrorCnt++;
                    PdUpd_RamDebug(0xFA);
                    PdUpd_RamDebug(0xE4);
                }
            }
            break;

        case _ITE_FLASH_WRITE_SIG:      //0x05
            /* Signature is in first sector 256 bytes offset 0x40 */
            if (ReadPdFwBinFile(0))
            {
                if (ITEi2c_FspiWriteEnable())
                {
                    /* Sector 0 Signature programming */
                    if (ITEi2c_FspiBlockWrite256B(0, 0, _PROG_SIGN))
                    {
                        iteFwFlashStep = _ITE_FLASH_VERIFY_SIG;
                        PdUpd_RamDebug(0xE5);
                    }
                }
            }
            break;

        case _ITE_FLASH_VERIFY_SIG:
            if (ITEi2c_FspiWriteDisable())
            {
                RetVal = ITEi2c_FspiVerify(0, 0, _PROG_SIGN);
                if (RetVal == 1)
                {
                    iteFwFlashStep = _ITE_FLASH_EXITFOLLOW;
                    iteFwErrorCnt2 = 0;
                    PdUpd_RamDebug(0xE6);
                }
                else if (RetVal == 2)
                {
                    iteFwFlashSector = 0;
                    iteFwFlashStep = _ITE_FLASH_ERASE_1K;
                    iteFwErrorCnt2++;
                }
            }
            break;

        case _ITE_FLASH_EXITFOLLOW:
            if (ITEi2c_FspiExitFollowMode())
            {
                iteFwFlashStep = _ITE_FLASH_WDT;
                PdUpd_RamDebug(0xE7);
            }
            break;

        case _ITE_FLASH_WDT:
            /* Chip WDT */
            if (ITEi2c_read_reg(0xFF, 0xD3) != 0x60)
            {
                break;
            }
            if (!ITEi2c_write_reg(0xFF, 0xD3, 0x70))
            {
                break;
            }
            if (ITEi2c_write_reg(0xFF, 0xD1, 0x01))
            {
                /* Disable DBGR */
                //ITEi2c_write_reg(0xFF, 0xC4, 0x10);
                iteFwFlashStep = _ITE_FLASH_FINISH;
                PdUpd_RamDebug(0xE8);
            }
            break;

        case _ITE_FLASH_FINISH:
            iteFwFlashStep = 0xF0;
            PdUpd_RamDebug(0xF0);
            PdUpd_RamDebug(0xF0);
            break;
        default:
            iteFwFlashStep = 0xFF;
            break;
        }

    }
    while (iteFwFlashStep < 0xF0);

    /* SCLKTS: 0x11:50KHz,0x12:100KHz,0x13:400KHz */
#if USING_I2C_CHN_A_TO_PD
    HOCTL2_A = 0x01;
    SCLKTS_A = 0x12;        //100KHz
#endif
#if USING_I2C_CHN_B_TO_PD
    HOCTL2_B = 0x01;
    SCLKTS_B = 0x12;        //100KHz
#endif
#if USING_I2C_CHN_C_TO_PD
    HOCTL2_C = 0x01;
    SCLKTS_C = 0x12;        //100KHz
#endif

    if (iteFwFlashStep == 0xFF)
    {
        return 0xFA;
    }

    /* TRUE: Update Ok. */
    return iteFwFlashStep;
}
#endif

#if SUPPORT_APP_UPDFW_MODULE
/*-----------------------------------------------------------------------------
 * @subroutine - ITE_PD_FlashUtility
 * @function - ITE PD Programming Utility Support
 * @Upstream - Timer10msEvent
 * @input    - None
 * @return   - None
 * @note     - Sign.Str: 'P','D',0,0,0x91,0x60,0,0
 * Step01. Special Waveform.
 * Step02. Stop CPU.
 * Step03. Enter SPI Test Mode.
 * Step04. Erase Flash.
 * Step05. Write FW code to flash exclude the signature area
 *         (To avoid the update flow be interrupted)
 * Step06. Read back compare ok
 * Step07. Write Signature to flash
 * Step08. Read back signature and check ok.
 * Step09. Exit SPI Test Mode.
 * Step10. Upgrade FW Done.
 * Step11. WDT Reset.
 */
void ITE_PD_FlashUtility(void)
{     
    
    if (xITEPD_FlashUtilityCmd == 0)
    {
        return;
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_GET_BUF_ADDR)
    {    
        /* PdSpiBuffer = SPIBuffer = ECRAM@0900 */
        xITEPD_FlashUtilityCmd2 = 0x0C;
        xITEPD_FlashUtilityCmd3 = 0x00;
        xITEPD_FlashUtilityCmd = 0;
        return;
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_GET_FW_VER)
    {        
        //Check PD FW Version      
        if (PDFW_GetVersion())
        {
            PdSpiBuffer[0] = xPD1_FW_VERSION[0];
            PdSpiBuffer[1] = xPD1_FW_VERSION[1];  
        }
        else
        {
            PdSpiBuffer[0] = 0xFF;
            PdSpiBuffer[1] = 0xFF;        
        }
        xITEPD_FlashUtilityCmd = 0;
        return;
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_SPECIAL_WAVE)
    {      
        /* Enter D2EC Mode */
        Send_ITE_Special_Wave();
        xITEPD_FlashUtilityCmd = 0;
        return;
    } 
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_STOP_CPU)
    {      
        ITEi2c_StopCPU_F();
//         ITEi2c_StopCPU_F();
//         ITEi2c_StopCPU_F();
        ITEi2c_StopCPU_H();
//         ITEi2c_StopCPU_H();
//         ITEi2c_StopCPU_H();
        xITEPD_FlashUtilityCmd = 0;
        return;        
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_ENTER_FOLLOW_MODE)
    {     
        xITEPD_FlashUtilityAck = 0;
        if (!ITEi2c_FspiEnterFollowMode())      //[40W][FF][F8][A5][5A]
        {
            xITEPD_FlashUtilityAck = 0xF4;    //Error Code = F4
        }
        xITEPD_FlashUtilityCmd = 0;
        return;          
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_EXIT_FOLLOW_MODE)
    {      
        xITEPD_FlashUtilityAck = 0xF5;    //Error Code = F5
        if (ITEi2c_FspiExitFollowMode())
        {
            xITEPD_FlashUtilityAck = 0;
        }
        xITEPD_FlashUtilityCmd = 0;
        return;          
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_SECTOR_ERASE)
    { 
        xITEPD_FlashUtilityAck = 0xF6;  //Error Code = F6
        if (ITEi2c_FspiWriteEnable())
        {
            if (ITEi2c_FspiSectorErase(xITEPD_FlashUtilityCmd3, xITEPD_FlashUtilityCmd2))
            {
                ITEi2c_FspiWriteDisable();
                xITEPD_FlashUtilityAck = 0;
            }
        }
        xITEPD_FlashUtilityCmd = 0;
        return;                
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_WRITE_256B)
    { 
        xITEPD_FlashUtilityAck = 0xF7;  //Error Code = F7
        if (ITEi2c_FspiWriteEnable())
        {
            if (ITEi2c_FspiBlockWrite256B(xITEPD_FlashUtilityCmd3, xITEPD_FlashUtilityCmd2,
                                         _SKIP_SIGN))
            {
                xITEPD_FlashUtilityAck = 0;
            }
        }   
        xITEPD_FlashUtilityCmd = 0;
        return;                
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_VERIFY_256B)
    {              
        if (ITEi2c_FspiWriteDisable())
        {
            xITEPD_FlashUtilityAck = ITEi2c_FspiVerify(xITEPD_FlashUtilityCmd3, xITEPD_FlashUtilityCmd2,
                                                       _SKIP_SIGN);
        }
        xITEPD_FlashUtilityCmd = 0;
        return;                
    }
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_WRITE_SIGN)
    {                       
        if (ITEi2c_FspiWriteEnable())
        {
            /* Sector 0 Signature programming */
            if (ITEi2c_FspiBlockWrite256B(0, 0, _PROG_SIGN))
            {   
                ;
            }
        }
        xITEPD_FlashUtilityCmd = 0;
        return;                
    }     
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_VERIFY_SIGN)
    {                       
        if (ITEi2c_FspiWriteDisable())
        {
            xITEPD_FlashUtilityAck = ITEi2c_FspiVerify(0, 0, _PROG_SIGN);
        }
        xITEPD_FlashUtilityCmd = 0;
        return;                
    }  
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_REG_READ)
    {    
        xITEPD_FlashUtilityAck = ITEi2c_read_reg(xITEPD_FlashUtilityCmd2,
                                                 xITEPD_FlashUtilityCmd3);
        xITEPD_FlashUtilityCmd = 0;
        return;        
    }    
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_REG_WRITE)
    {    
        ITEi2c_write_reg(xITEPD_FlashUtilityCmd2,
                         xITEPD_FlashUtilityCmd3, 
                         xITEPD_FlashUtilityAck);
        xITEPD_FlashUtilityCmd = 0;
        return;        
    }          
    if (xITEPD_FlashUtilityCmd == _ITE_UPD_APP_Finish)
    {      
        xPD1_i2c_addr = _ITE_PD1_I2C_ADDR;
        xPD2_i2c_addr = _ITE_PD2_I2C_ADDR;
    /* SCLKTS: 0x11:50KHz,0x12:100KHz,0x13:400KHz */
    #if USING_I2C_CHN_A_TO_PD
        HOCTL2_A = 0x01;
        SCLKTS_A = 0x12;        //100KHz
    #endif
    #if USING_I2C_CHN_B_TO_PD
        HOCTL2_B = 0x01;
        SCLKTS_B = 0x12;        //100KHz
    #endif
    #if USING_I2C_CHN_C_TO_PD
        HOCTL2_C = 0x01;
        SCLKTS_C = 0x12;        //100KHz
    #endif
        xITEPD_FlashUtilityCmd = 0;
        return;        
    }
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_APP_UPDFW_MODULE

#if 1
/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_TurnOn_5V
 * @function - ITEi2c_TurnOn_5V
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_TurnOn_5V(void)
{
    BYTE    UpdI2cWriteBuf[5];
    
    UpdI2cWriteBuf[0] = 0xDB;
    UpdI2cWriteBuf[1] = 0x81;   
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {       
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {       
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ITEi2c_TurnOff_5V
 * @function - ITEi2c_TurnOff_5V
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE ITEi2c_TurnOff_5V(void)
{
    BYTE    UpdI2cWriteBuf[4];
    
    UpdI2cWriteBuf[0] = 0xDB;
    UpdI2cWriteBuf[1] = 0x80;   
    if(xITEPD_FlashUtilitySMBusSW == 0)
    {
        if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {           
            return TRUE;
        }
    }
    else
    {
        if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                               &UpdI2cWriteBuf[0],
                               2,
                               0,
                               &UpdI2cReadBuf[0],
                               0))
        {           
            return TRUE;
        }
    }
    return FALSE;
}
#endif
//-----------------------------------------------------------------------------
#endif  //SUPPORT_UPDFW_MODULE
/*-----------------------------------------------------------------------------
 * End of UPDFW_ITE.C */