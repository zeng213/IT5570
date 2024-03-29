/*-----------------------------------------------------------------------------
 * @file     | ITE_PREDEF.C
 *-----------+-----------------------------------------------------------------
 * @function | ITE Pre-Define I2C
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
#define DEBUG_PREDEF_RAMDEBUG       FALSE
#define SMBusEXT                    0x1C    // Read Write Extend command
#define _ITE_PREDEF_ID              0x5B << 1
#define _ITE_SPI_READ_ID            0x9F
#define _ITE_SPI_WRITE_ENABLE       0x06
#define _ITE_SPI_WRITE_DISABLE      0x04
#define _ITE_SPI_SECTOR_ERASE       0xD7
#define _ITE_SPI_CHIP_ERASE         0x60
#define _ITE_SPI_READ_STATUS        0x05
#define _ITE_SPI_AAI_WRITE          0xAD
#define _ITE_SPI_FAST_READ          0x0B

#define _SPI_FW1_START_ADDRH        0x03    //FW1:56K
#define _SPI_FW1_START_ADDRM        0x00
#define _SPI_FW1_START_ADDRL        0x00
#define _SPI_FW1_END_ADDRH          0x03
#define _SPI_FW1_END_ADDRM          0xDF
#define _SPI_FW1_END_ADDRL          0xFF
#define _SPI_FW1_VER_ADDRH          0x03
#define _SPI_FW1_VER_ADDRM          0x20
#define _SPI_FW1_VER_ADDRL          0x20

#define xI2C_MemBase                0x94D0
XBYTE   xI2C_COMMAND[8]             _at_ xI2C_MemBase + 0x00;
XBYTE   xI2C_READBUF[8]             _at_ xI2C_MemBase + 0x08;
XBYTE   xI2C_FLASHCMD1              _at_ xI2C_MemBase + 0x10;
XBYTE   xI2C_FLASHCMD2              _at_ xI2C_MemBase + 0x11;
XBYTE   xI2C_FLASHCMD3              _at_ xI2C_MemBase + 0x12;
XBYTE   xI2C_SpiStatus              _at_ xI2C_MemBase + 0x13;
XBYTE   xI2C_SpiTimer               _at_ xI2C_MemBase + 0x14;
XBYTE   xI2C_SpiErrorCount          _at_ xI2C_MemBase + 0x15;
XBYTE   xI2C_BinAddrH               _at_ xI2C_MemBase + 0x16;
XBYTE   xI2C_BinAddrM               _at_ xI2C_MemBase + 0x17;
XBYTE   xI2C_BinAddrL               _at_ xI2C_MemBase + 0x18;
XBYTE   xI2C_BuffIndex              _at_ xI2C_MemBase + 0x19;
XBYTE   xI2C_SpiID[4]               _at_ xI2C_MemBase + 0x1C;
XBYTE   xBIN_VerString[4]           _at_ xI2C_MemBase + 0x20;
XBYTE   xI2C_FwVerString[4]         _at_ xI2C_MemBase + 0x24;

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_PREDEF_RAMDEBUG
#define PREDEF_RamDebug(x)          RamDebug(x)
#else
#define PREDEF_RamDebug(x)          {}
#endif
//-----------------------------------------------------------------------------

#if 1
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH1_WrToRdStream
 * @function - I2C Channel-1 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - FALSE : Failed
 * @note     - SMCLK1/GPC.1, SMDAT1/GPC.2
 */
BYTE I2C_CH1_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, WORD Count, BYTE WrDly,
                          XBYTE *Var2, WORD Count2)
{
    BYTE    j, t;

    if (Count == 0)
    {
        HOSTA_B = 0xFE;                     //REG@1C32
        HOCTL2_B = (I2C_EN | SMHEN);
        TRASLA_B = (I2C_Addr | 0x01);       //REG@1C2C
        HOCTL_B = (SMBusEXT | HOCTL_SRT);   //REG@1C2A
    }
    else
    {
        HOSTA_B = 0xFE;
        HOCTL2_B = (I2C_EN | SMHEN);
        TRASLA_B = (I2C_Addr & 0xFE);
        HOBDB_B = *Var;
        HOCTL_B = (SMBusEXT | HOCTL_SRT);

        t = 0;
        while (1)
        {
            j = HOSTA_B;
            if ((j & HOSTA_BDS) != 0x00)
            {
                Count--;
                if (Count == 0)
                {
                    break;
                }
                while (1)
                {
                    if (WrDly > 0)
                    {
                        WrDly--;
                        WNCKR = 0x00;   /* Delay 15.26 us */
                    }
                    else
                    {
                        break;
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
        if (Count2 == 0)
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
    }

    if (Count2 == 0x01) { HOCTL_B |= HOCTL_LABY; }

    t = 0;
    while (1)
    {
        j = HOSTA_B;
        if ((j & HOSTA_BDS) != 0x00)
        {
            Count2--;
            if (Count2 == 0)
            {
                *Var2 = HOBDB_B;
                break;
            }
            if (Count2 == 0x01)
            {
                HOCTL_B |= HOCTL_LABY;
            }
            j = HOBDB_B;
            *Var2 = j;
            if (Count2 == 0xFFFE)
            {
                Count2 = j;
                if ((j == 0) || (j > 31))
                {
                    Count2 = 32;
                }
            }
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

/*-----------------------------------------------------------------------------
 * @subroutine - ite_i2c_predef_send
 * @function - ite_i2c_predef_send
 * @Upstream - By Call
 * @input    - SpiCmd
 * @return   - None
 * @note     -
 */
void ite_i2c_predef_send(BYTE SpiCmd)
{
    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x18;
    xI2C_COMMAND[1] = SpiCmd;
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 2, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
}

/*-----------------------------------------------------------------------------
 * @subroutine - ite_i2c_predef_status
 * @function - ite_i2c_predef_status
 * @Upstream - By Call
 * @input    - SpiCmd
 * @return   - None
 * @note     -
 */
BYTE ite_i2c_predef_status(BYTE ChkBit, BYTE ChkHoLo)
{
    xI2C_SpiErrorCount = 0;
    xI2C_SpiTimer = 5;
    while (1)
    {
        Delay1MS(1);
        xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                             &xI2C_READBUF[0], 0);
        xI2C_COMMAND[0] = 0x18;
        xI2C_COMMAND[1] = _ITE_SPI_READ_STATUS;
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 2, 0,
                             &xI2C_READBUF[0], 1);
        xI2C_SpiStatus = xI2C_READBUF[0];
        //xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
        //I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
        //                     &xI2C_READBUF[0], 0);
        if ((xI2C_SpiStatus & ChkBit) == ChkHoLo)
        {
            break;
        }
        if (xI2C_SpiTimer > 0)
        {
            xI2C_SpiTimer--;
        }
        else
        {
            xI2C_SpiErrorCount++;
            PREDEF_RamDebug(0xBB);
            break;
        }
    }
    return xI2C_SpiErrorCount;
}

/*-----------------------------------------------------------------------------
 * @subroutine - it8295_eflash_erase
 * @function - it8295_eflash_erase
 * @Upstream - By Call
 * @input    - None
 * @return   - None
 * @note     -
 */
void it8295_eflash_erase(void)
{
#if 0   /* Chip Erase All */
    ite_i2c_predef_send(_ITE_SPI_WRITE_ENABLE);
    ite_i2c_predef_send(_ITE_SPI_CHIP_ERASE);
    if (ite_i2c_predef_status(BIT0, 0) > 0)
    {
        return; //ERROR
    }
#else   /* Sector Erase */
    /* IT8295 ERASE 56KB */
    xI2C_FLASHCMD2 = 0x00;
    while (1)
    {
        ite_i2c_predef_send(_ITE_SPI_WRITE_ENABLE);
        xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                             &xI2C_READBUF[0], 0);
        xI2C_COMMAND[0] = 0x18;
        xI2C_COMMAND[1] = _ITE_SPI_SECTOR_ERASE;
        xI2C_COMMAND[2] = 0x00;
        xI2C_COMMAND[3] = xI2C_FLASHCMD2;
        xI2C_COMMAND[4] = 0x00;
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 5, 0,
                             &xI2C_READBUF[0], 0);
        xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                             &xI2C_READBUF[0], 0);
        if (ite_i2c_predef_status(BIT0, 0) > 0)
        {
            break;  //ERROR
        }
        ite_i2c_predef_send(_ITE_SPI_WRITE_DISABLE);
        xI2C_FLASHCMD2 += 4;
        if (xI2C_FLASHCMD2 == 0xE0)     /* 0x0000~0xDFFF = 56K */
        {
            break;
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - it8295_eflash_write32bytes
 * @function - it8295_eflash_write32bytes
 * @Upstream - By Call
 * @input    - None
 * @return   - None
 * @note     -
 */
void it8295_eflash_write32bytes(void)
{
    xI2C_BuffIndex = 0;

    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x18;
    xI2C_COMMAND[1] = _ITE_SPI_WRITE_ENABLE;
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 2, 0,
                         &xI2C_READBUF[0], 0);

#if 0
    if (ite_i2c_predef_status(0x02, 0x02) > 0)
    {
        ;   //ERROR
    }
#endif

    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x18;
    xI2C_COMMAND[1] = _ITE_SPI_AAI_WRITE;
    xI2C_COMMAND[2] = xI2C_FLASHCMD1;
    xI2C_COMMAND[3] = xI2C_FLASHCMD2;
    xI2C_COMMAND[4] = xI2C_FLASHCMD3;
    xI2C_COMMAND[5] = SPIBuffer[xI2C_BuffIndex];
    xI2C_BuffIndex++;
    xI2C_COMMAND[6] = SPIBuffer[xI2C_BuffIndex];
    xI2C_BuffIndex++;
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 7, 0,
                         &xI2C_READBUF[0], 0);

    if (ite_i2c_predef_status(BIT0, 0) > 0)
    {
        ;  //ERROR
    }
    while (1)
    {
        xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                             &xI2C_READBUF[0], 0);
        xI2C_COMMAND[0] = 0x18;
        xI2C_COMMAND[1] = _ITE_SPI_AAI_WRITE;
        xI2C_COMMAND[2] = SPIBuffer[xI2C_BuffIndex];
        xI2C_BuffIndex++;
        xI2C_COMMAND[3] = SPIBuffer[xI2C_BuffIndex];
        xI2C_BuffIndex++;
        I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 4, 0,
                             &xI2C_READBUF[0], 0);

        if (ite_i2c_predef_status(BIT0, 0) > 0)
        {
            ;  //ERROR
        }
        if (xI2C_BuffIndex >= 32)
        {
            break;
        }
    }
    ite_i2c_predef_send(_ITE_SPI_WRITE_DISABLE);
}

/*-----------------------------------------------------------------------------
 * @subroutine - it8295_update_fw
 * @function - it8295_update_fw
 * @Upstream - By Call
 * @input    - None
 * @return   - None
 * @note     -
 */
void it8295_update_fw(void)
{
    /* Send enter eFlash mode command */
    /* Read Bin Version. */
    ECIndirectFastRead(_SPI_FW1_VER_ADDRH,
                       _SPI_FW1_VER_ADDRM,
                       _SPI_FW1_VER_ADDRL,
                       SPI_selection_external,
                       16,
                       &SPIBuffer[0]);
    xBIN_VerString[0] = (SPIBuffer[2] << 4) & 0xF0 + (SPIBuffer[3] & 0x0F);
    xBIN_VerString[1] = (SPIBuffer[5] << 4) & 0xF0 + (SPIBuffer[6] & 0x0F);
    xBIN_VerString[2] = (SPIBuffer[8] << 4) & 0xF0 + (SPIBuffer[9] & 0x0F);
    xBIN_VerString[3] = (SPIBuffer[11] << 4) & 0xF0 + (SPIBuffer[12] & 0x0F);
    /* Read Chip FW Version. */
    xI2C_COMMAND[0] = 0x07;
    I2C_CH1_WrToRdStream(0x5C, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_FwVerString[0], 2);
    xI2C_COMMAND[0] = 0x08;
    I2C_CH1_WrToRdStream(0x5C, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_FwVerString[2], 2);
    /* Compare Version difference ... */
    if ((xBIN_VerString[0] == xI2C_FwVerString[1]) &&
            (xBIN_VerString[1] == xI2C_FwVerString[0]) &&
            (xBIN_VerString[2] == xI2C_FwVerString[3]) &&
            (xBIN_VerString[3] == xI2C_FwVerString[2]))
    {
        /* No need update, Exit... */
        return;
    }
    /* Read SPI ID */
    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x18;
    xI2C_COMMAND[1] = _ITE_SPI_READ_ID;
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 2, 0,
                         &xI2C_SpiID[8], 3);
    /* Process Erase Block */
    it8295_eflash_erase();
    Delay1MS(50);

    xI2C_FLASHCMD1 = 0x00;
    xI2C_FLASHCMD2 = 0x00;
    xI2C_FLASHCMD3 = 0x00;
    xI2C_BinAddrH = _SPI_FW1_START_ADDRH;
    xI2C_BinAddrM = _SPI_FW1_START_ADDRM;
    xI2C_BinAddrL = _SPI_FW1_START_ADDRL;
    while (1)
    {
#if 1
        /* Load external SPI rom data. */
        ECIndirectFastRead(xI2C_BinAddrH,
                           xI2C_BinAddrM,
                           xI2C_BinAddrL,
                           SPI_selection_external,
                           32,
                           &SPIBuffer[0]);
        xI2C_BinAddrL += 32;
        if (xI2C_BinAddrL == 0)
        {
            xI2C_BinAddrM++;
            if (xI2C_BinAddrM == 0)
            {
                xI2C_BinAddrH++;
            }
        }
#else
        /* TEST DATA */
        for (ITempB01 = 0; ITempB01 < 32; ITempB01++)
        {
            SPIBuffer[ITempB01] = ITempB01 + 0x90;
        }
#endif

        /* Programming to i2c pre-define e-Flash */
        it8295_eflash_write32bytes();

        xI2C_FLASHCMD3 += 32;
        if (xI2C_FLASHCMD3 == 0)
        {
            xI2C_FLASHCMD2++;
            if (xI2C_FLASHCMD2 == 0)
            {
                xI2C_FLASHCMD1++;
            }
        }
        //if (xI2C_FLASHCMD2 == 0x01)   /* 0x0000~0x0100 = 256B TEST*/
        if (xI2C_FLASHCMD2 == 0xE0)     /* 0x0000~0xDFFF = 56K */
        {
            break;
        }
    }

    Delay1MS(25);
#if 1   /* Reserved for Read Verify */
    xI2C_FLASHCMD1 = 0x00;
    xI2C_FLASHCMD2 = 0x00;
    xI2C_FLASHCMD3 = 0x00;

    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
    xI2C_COMMAND[0] = 0x18;
    xI2C_COMMAND[1] = _ITE_SPI_FAST_READ;
    xI2C_COMMAND[2] = xI2C_FLASHCMD1;
    xI2C_COMMAND[3] = xI2C_FLASHCMD2;
    xI2C_COMMAND[4] = xI2C_FLASHCMD3;
    xI2C_COMMAND[5] = 0x00;     //Dummy
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 6, 0,
                         &xI2C_READBUF[0], 0);
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 0, 0,
                         &SPIBuffer[0], 256);

    xI2C_COMMAND[0] = 0x17;    /* CS HIGH */
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 1, 0,
                         &xI2C_READBUF[0], 0);
#endif

    Delay1MS(10);
#if 1 /* Reset */
    /* Reset througn I2C - reset i2c pre-deine command. */
    xI2C_COMMAND[0] = 0x5A;
    xI2C_COMMAND[1] = 0xA5;
    I2C_CH1_WrToRdStream(_ITE_PREDEF_ID, &xI2C_COMMAND[0], 2, 0,
                         &xI2C_READBUF[0], 0);
#endif
    Delay1MS(10);
}

/*-----------------------------------------------------------------------------
 * End of ITE_PREDEF.C */