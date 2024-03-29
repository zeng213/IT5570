/*-----------------------------------------------------------------------------
 * @file     | MPS2904.C
 *-----------+-----------------------------------------------------------------
 * @function | ITE DEVICES LIBARRY
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
#define DEBUG_MPS2904           FALSE
#define MPS2905_MODULE_CODE     FALSE   //FALSE: No-Build,Keep Sources



/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_MPS2904
#define MPS2904_RamDebug(x)      RamDebug(x)
#else
#define MPS2904_RamDebug(x)      {}
#endif
//-----------------------------------------------------------------------------


#if MPS2905_MODULE_CODE
//*****************************************************************************
// CODE START
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - Service_MPS_Programming
 * @function - Service_MPS_Programming
 * @upstream - By call
 * @input    -
 * @return   -
 * @note     -
 */
//-----------------------------------------------------------------------------
//*****************************************************************************
/* MPS MP2904A Table */
//*****************************************************************************
const sMpsTblStruct code _SMB_MPS_INIT_TBL[] =
{
    {   0x00, 0x01, 0x00    },
    {   0x01, 0x01, 0x80    },
    {   0x1B, 0x02, 0x0045  },
    {   0x1D, 0x02, 0x0008  },
    {   0x1E, 0x01, 0x02    },
    {   0x21, 0x02, 0x1EA1  },
    {   0x22, 0x02, 0x0000  },
    {   0x23, 0x02, 0x0000  },
    {   0x24, 0x02, 0x00FF  },
    {   0x25, 0x02, 0x0092  },
    {   0x26, 0x02, 0x145B  },
    {   0x2B, 0x02, 0x0000  },
    {   0x2E, 0x02, 0x6701  },
    {   0x30, 0x02, 0x07DF  },
    {   0x35, 0x02, 0xE828  },
    {   0x36, 0x02, 0xE824  },
    {   0x38, 0x02, 0x8A25  },
    {   0x39, 0x02, 0xF800  },
    {   0x3A, 0x02, 0x0080  },
    {   0x3B, 0x02, 0x0080  },
    {   0x3C, 0x02, 0x0080  },
    {   0x50, 0x01, 0x00    },
    {   0x51, 0x01, 0x00    },
    {   0x55, 0x02, 0xE8A8  },
    {   0x58, 0x02, 0xE82C  },
    {   0xB8, 0x01, 0x80    },
    {   0xBB, 0x02, 0x0115  },
    {   0xBD, 0x02, 0x88BC  },
    {   0xBE, 0x02, 0x497A  },
    {   0xBF, 0x02, 0x2540  },
    {   0xC0, 0x02, 0x821D  },
    {   0xC1, 0x01, 0x03    },
    {   0xC2, 0x02, 0xE181  },
    {   0xC3, 0x02, 0x300A  },
    {   0xC4, 0x02, 0x0119  },
    {   0xC5, 0x02, 0x0D14  },
    {   0xC6, 0x02, 0xE605  },
    {   0xCA, 0x01, 0x02    },
    {   0xCC, 0x02, 0x0EDB  },
    {   0xCD, 0x02, 0x0032  },
    {   0xCE, 0x02, 0xE50A  },
    {   0xCF, 0x02, 0x02C8  },
    {   0xD6, 0x02, 0x0009  },
    {   0xD7, 0x02, 0x001E  },
    {   0xD8, 0x02, 0x0009  },
    {   0xD9, 0x02, 0x0034  },
    {   0xDA, 0x02, 0x0009  },
    {   0xDB, 0x02, 0x0075  },
    {   0xDC, 0x02, 0x0009  },
    {   0xDD, 0x02, 0xB075  },
    {   0xDE, 0x02, 0x19CD  },
    {   0xDF, 0x02, 0x0004  },
    {   0xE1, 0x02, 0x20A0  },
    {   0xE2, 0x02, 0xF10A  },
    {   0xE3, 0x01, 0x1A    },
    {   0xE4, 0x02, 0x3C00  },
    {   0xE5, 0x02, 0x1400  },
    {   0xE6, 0x02, 0x0030  },
    {   0xE8, 0x02, 0x500A  },
    {   0xE9, 0x02, 0x007B  },
    {   0xEA, 0x01, 0xA4    },
    {   0xEB, 0x02, 0x0000  },
    {   0xEC, 0x02, 0x0000  },
    {   0xEE, 0x02, 0x192F  },
    {   0xEF, 0x01, 0x46    },
    {   0xF0, 0x02, 0xFF14  },
    {   0xF1, 0x02, 0x2B5D  },
    {   0xF2, 0x02, 0x411E  },
    {   0xF3, 0x02, 0x0078  },
    {   0xF5, 0x02, 0x5C1E  },
    {   0xF6, 0x02, 0xC0BC  },
    {   0xF7, 0x02, 0x0059  },
    {   0xF8, 0x02, 0x0064  },
    {   0xF9, 0x02, 0xC8C2  },
    {   0xFA, 0x02, 0x0243  },
    {   0xFB, 0x02, 0x0385  },
    {   0xFC, 0x02, 0x0080  },
    {   0xFD, 0x02, 0xD085  },
    {   0x00, 0x00, 0x0000  },  //<--End Mark
};
//-----------------------------------------------------------------------------
void Service_MPS_Programming(void)
{
    DisableAllInterrupt();

    ALL_SYS_PWRGD_HI();
    Delay1MS(100);

    while (1)
    {
        xMPS_SetAddress = 0x40;
        xMPS_SetCommand = _SMB_MPS_INIT_TBL[xMPS_TblIndex].CmdCode;
        ITempB01 = _SMB_MPS_INIT_TBL[xMPS_TblIndex].Length;
        if (ITempB01 == 0x00)
        {
            break;
        }
        ITempW01 = _SMB_MPS_INIT_TBL[xMPS_TblIndex].MpsData;
        xMPS_SetDataLo = (ITempW01 & 0xFF);
        xMPS_SetDataHi = (ITempW01 >> 4) & 0xFF;
        if (ITempB01 == 0x01)
        {
            SPI_BUF0[0] = xMPS_SetDataLo;
            xMPS_SMBusStatus = bRWSMBus(_SMB_CH1,
                                        SMbusWB,
                                        xMPS_SetAddress,
                                        xMPS_SetCommand,
                                        &SPI_BUF0[0],
                                        SMBus_NeedPEC);
            if (xMPS_SMBusStatus == 0)
            {
                xMPS_SMBusError++;
            }
        }
        else if (ITempB01 == 0x02)
        {
            SPI_BUF0[0] = xMPS_SetDataLo;
            SPI_BUF0[1] = xMPS_SetDataHi;
            xMPS_SMBusStatus = bRWSMBus(_SMB_CH1,
                                        SMbusWW,
                                        xMPS_SetAddress,
                                        xMPS_SetCommand,
                                        &SPI_BUF0[0],
                                        SMBus_NeedPEC);
            if (xMPS_SMBusStatus == 0)
            {
                xMPS_SMBusError++;
            }
        }
        Delay1MS(1);
    }
    /* Send command 0x15 to store data into EEPROM/MTP. */
    xMPS_SetAddress = 0x40;
    xMPS_SetCommand = 0x15;
    xMPS_SMBusStatus = bSMBusSendByte(_SMB_CH1,
                                      xMPS_SetAddress,
                                      xMPS_SetCommand,
                                      SMBus_NeedPEC);
    if (xMPS_SMBusStatus == 0)
    {
        xMPS_SMBusError++;
    }
    /* Store waiting time RAM->MTP... */
    Delay1MS(100);
    Delay1MS(100);
    Delay1MS(100);
    Delay1MS(100);
    Delay1MS(100);
    Delay1MS(100);
    Delay1MS(100);
    /* Restore command 0x16 MTP->RAM.. */
    xMPS_SetAddress = 0x40;
    xMPS_SetCommand = 0x16;
    xMPS_SMBusStatus = bSMBusSendByte(_SMB_CH1,
                                      xMPS_SetAddress,
                                      xMPS_SetCommand,
                                      SMBus_NeedPEC);
    if (xMPS_SMBusStatus == 0)
    {
        xMPS_SMBusError++;
    }
    Delay1MS(100);
    ALL_SYS_PWRGD_LO();
    Delay1MS(100);
    ETWCFG = EWDKEYEN;    /* Force Watchdog active */
    EWDCNTLLR = 0x01;   // for 1ms counter
    EWDKEYR = 0x5A;     // External WDTreset not match
    while (1);
}
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of MPS2904.C */