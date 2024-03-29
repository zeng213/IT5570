/*-----------------------------------------------------------------------------
 * @file     | OEM_INIT.C
 * ----------+-----------------------------------------------------------------
 * @function | OEM Initialize
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
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//*****************************************************************************
// CODE START
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_StartUp
 * @function - Oem_StartUp
 * @upstream - hook from STARTUP.A51
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_StartUp(void)
{
    /* Sample Code: Power,Vol Up/Dn 3 buttons down trigger mirror code. */
#if 1   /* 1:Support "3 Buttons" entry recovery mirror function */
    if (IS_EC_PWRSW_DN())
    {
        if (IS_VOLUME_UP_DN() && IS_VOLUME_DOWN_DN())
        {
            GPCRD2 = OUTPUT;    //GPD2
            CLEAR_MASK(GPDRD, BIT(2));
            WNCKR = 0x00;       // Delay 15.26 us
            FLHCTRL3R = (AUTO_LOAD_AFTER_WDT + FIFE);
            ETWCFG = EWDKEYEN;  /* Force Watchdog active */
            EWDCNTLLR = 0x01;   /* for 1ms counter */
            EWDKEYR = 0x5A;     /* External WDTreset not match */
        }
    }
#endif
    /* Sample Code: Power, Matrix-[Home] Key down trigger mirror code. */
#if 0
    KSOCTRL = KSOOD + KSOPU;
    KSICTRL = KSIPU;
    KSOL = 0xFF;
    KSOH1 = 0xBF;
    WNCKR = 0x00;
    while (IS_EC_PWRSW_DN())
    {
        if (KSI == 0xFD)    //Home Key = KSO14,KSI1
        {
            ITempB01++;
            if (ITempB01 == 0)
            {
                GPCRD2 = OUTPUT;    //GPD2
                CLEAR_MASK(GPDRD, BIT(2));
                WNCKR = 0x00;       // Delay 15.26 us
                FLHCTRL3R = (AUTO_LOAD_AFTER_WDT + FIFE);
                ETWCFG = EWDKEYEN;  /* Force Watchdog active */
                EWDCNTLLR = 0x01;   // for 1ms counter
                EWDKEYR = 0x5A;     // External WDTreset not match
            }
        }
        else
        {
            break;
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_WDT
 * @function - The function of init. WDT Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_WDT(void)
{
#if SUPPORT_PWRSW_RESET
    GCR10 = PWRSW_WDT2_10S;
    GCR9 |= PWSW2EN2;
    SET_MASK(GCR8, BIT4);  // Enable 12s EC reset
#endif
}

#if 1   //1: PWM initialization
/*-----------------------------------------------------------------------------
 * @subroutine - Init_PWM_Regs
 * @function - The function of init. SMBus Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
const sREG_INIT_DEF code Init_PWM_table[] =
{
    { &ZTIER,       0x00    }, // Disable Before Setting
    { &CTR,         0xC8    }, // Group 0: Step 185
    { &CTR1,        0xFF    }, // Group 1: Step 255
    { &CTR2,        0xFF    }, // Group 2: Step 255
    { &CTR3,        0xFF    }, // Group 3: Step 255

    { &PCFSR,       0x00    }, // REG@180B
    { &CLK6MSEL,    0x00    },
    /* Prescaler Clock Frequency Select (PCFS3-0)
       {G6MSEL0, PCFS0}:
       00b: Select 32.768 kHz.
       01b: Select FreqEC (EC Clock).(9.2MHz)
       10b: Select FreqEC*2/3 (6.14 MHz)
       PWM Clock 6MHz Select Register (CLK6MSEL)
       Clock Group 6MHz Selection (G6MSEL3-0)
       Bit3:0 Refer to PCFS3-0 field in PCFSR register.
    */
    { &C0CPRS,      0x00    }, // 00: F = 163Hz Prescaler 0

    { &C4CPRS,      0x01    }, // 01: F = 23 KHZ Prescaler 1
    { &C4MCPRS,     0x00    },

    { &C6CPRS,      0xE3    }, // 10: F = 200 Hz Prescaler 2
    { &C6MCPRS,     0x00    },

    { &C7CPRS,      0x23    }, // 11: F = 1KHz Prescaler 3
    { &C7MCPRS,     0x00    },

    /* === PCSSGH ==== === PCSSGL ==== */
    /* PA7,PA6,PA5,PA4 PA3,PA2,PA1,PA0 */
    /* 01  00  00  00  00  00  00  00  */
    { &PCSSGH,      0x40    }, // PA7..PA4
    { &PCSSGL,      0x00    }, // PA3..PA0
#if 1
    /* Auto-Dimm(Breath) LED */
    { &PWM0LCR1,    0x30    },
    { &PWM0LCR2,    0x22    },
    { &PWM0LHE,     0x00    },
    { &PWM1LCR1,    0x30    },
    { &PWM1LCR2,    0x22    },
    { &PWM1LHE,     0x00    },
#endif
    { &ZTIER,       0x02    }, // Enable PWM output (PCCE)
    { &DCR0,        0xB0    }, //
    { &DCR1,        0x00    }, //
};
//-----------------------------------------------------------------------------
void Init_PWM(void)
{
    ITempB01 = 0;
    while (ITempB01 < (sizeof(Init_PWM_table) / sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_PWM_table[ITempB01].address;
        *Tmp_XPntr = Init_PWM_table[ITempB01].initdata;
        ITempB01++;
    }
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SMBus
 * @function - The function of init. SMBus Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
const sREG_INIT_DEF code Init_SMBus_table[] =
{
    { &SMB4P7USL,   0x28    },  /* 100KHz */
    { &SMB4P0USH,   0x25    },
    { &SMB300NS,    0x03    },
    { &SMB250NS,    0x02    },
    { &SMB25MS,     0x19    },
    { &SMB45P3USL,  0xA5    },
    { &SMBS4P3USH,  0x01    },
    { &SMB4P7A4P0H, 0x00    },

    { &HOCTL2_A,    0x01    },
    { &HOCTL_A,     0x03    },
    { &HOCTL_A,     0x01    },
    { &HOSTA_A,     0xFF    },
    { &SCLKTS_A,    0x12    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_B,    0x01    },
    { &HOCTL_B,     0x03    },
    { &HOCTL_B,     0x01    },
    { &HOSTA_B,     0xFF    },
    { &SCLKTS_B,    0x12    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_C,    0x01    },
    { &HOCTL_C,     0x03    },
    { &HOCTL_C,     0x01    },
    { &HOSTA_C,     0xFF    },
    { &SCLKTS_C,    0x12    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_D,    0x01    },
    { &HOCTL_D,     0x03    },
    { &HOCTL_D,     0x01    },
    { &HOSTA_D,     0xFF    },
    { &SCLKTS_D,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

#if SUPPORT_SMBUS_E_F
    { &HOCTL2_E,    0x01    },
    { &HOCTL_E,     0x03    },
    { &HOCTL_E,     0x01    },
    { &HOSTA_E,     0xFF    },
    { &SCLKTS_E,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_F,    0x01    },
    { &HOCTL_F,     0x03    },
    { &HOCTL_F,     0x01    },
    { &HOSTA_F,     0xFF    },
    { &SCLKTS_F,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */
#endif

#ifdef SUPPORT_SMB_SLAVE_A
#if SUPPORT_SMB_SLAVE_A   //Special Contrl
    { &SLVISEL,     _SMB_CH0    },
    //{ &SLVISEL,   _SMB_CH1    },
    //{ &SLVISEL,   _SMB_CH2    },
    //{ &SLVISEL,   _SMB_CH3    },
    { &HOCTL2_A,    0x21        },  // Enable SMBus Slave
    { &SICR_A,      0x03        },  // Enable slave interrupt
    { &RESLADR_A,   0x68        },  // HID slave address = 0x68
    { &RESLADR2_A,  0xF6        },  // Slave address 2 for ACPI = 0xEC
    { &HOCTL_A,     0x02        },  // Kill current host transaction
    { &HOCTL_A,     0x00        },  // Kill current host transaction
    { &HOSTA_A,     0xFF        },  // Clear all master status
    { &SLSTA_A,     0xFF        },  // Clear all slave status
    { &SCLKTS_A,    0x12        },
#endif
#endif
};
//-----------------------------------------------------------------------------
void Init_SMBus(void)
{
    ITempB01 = 0;
    while (ITempB01 < (sizeof(Init_SMBus_table) / sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[ITempB01].address;
        *Tmp_XPntr = Init_SMBus_table[ITempB01].initdata;
        ITempB01++;
    }
#if 0
    /* SMBus Channel D Enable. */
    GCR2 |= SMB3EN;
#endif
}

#if 1   //1: ADC initialization
/*-----------------------------------------------------------------------------
 * @subroutine - Init_ADC
 * @function - The function of init. ADC Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_ADC(void)
{
    /* Initial ADC registers */
    ADCCFG |= BIT0;
    ADCSTS |= (AINITB + DOVE + EOCE);
    VCH0CTL = 0x80;
    VCH1CTL = 0x81;
    VCH2CTL = 0x82;
    VCH3CTL = 0x83;
    ADCCFG |= BIT0;
    ADCGCR |= ADCDBKEN;
}
#endif

#if UART1_DEBUG
/*-----------------------------------------------------------------------------
 * @subroutine - Init_UART1
 * @function - The function of init. UART1 Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_UART1(void)
{
   GPCRE6 = ALT;     /* Enable IT5570E TXD */
   GCR15 |= 0x80;    /* IT5570E GPE6 is TX pin.*/

//     GPCRB1 = ALT;      /* Enable IT5571E TXD */
    AUTOCG = 0x00;

    GCR1 &= 0xFC;
    GCR1 |= 0x01;   //REG@16F0 SIN0/SOUT0 are enabled.
    GCR6 = 0x0F;
    GCR8 &= 0xFC;   //REG@16F7
    GCR8 |= 0x01;
    RSTDMMC = 0x1F;
    RSTC4 = BIT1;   //Reset UART1 (RUART1)

    UART1_LCR = 0x80;   //Bit7: DLAB=1
    UART1_RBR = 0x01;   //UART1_IER = UART1_DLL (DLAB=1)
    UART1_IER = 0x00;   //UART1_IER = UART1_DLM (DLAB=1)
    // 0x00 0x01 : 115200 Baud Rate
    UART1_LCR = 0x03;
    UART1_MCR = 0x00;

    UART1_IIR = 0xC7;   //(W)UART1_IIR = UART1_FCR (Use FIFO)
    UART1_IER = 0x01;
    
#if 0
    UART2_RBR = 'U';
    UART2_RBR = 'A';
    UART2_RBR = 'R';
    UART2_RBR = 'T';
    UART2_RBR = '1';
    UART2_RBR = ' ';
    UART2_RBR = 'O';
    UART2_RBR = 'K';
    UART2_RBR = ' ';
#else
    printf("\n************************************");
    printf("\nEC PRINTF UART1 OK !!!");
    printf("\n************************************");
#endif
}
#endif

#if UART2_DEBUG
/*-----------------------------------------------------------------------------
 * @subroutine - Init_UART2
 * @function - The function of init. UART2 Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_UART2(void)
{
    AUTOCG = 0x00;

    GCR1 &= 0xF3;       //SIN1/SOUT1 are enabled.
    GCR1 |= 0x04;
    GCR6 = 0x0F;
    GCR8 &= 0xF3;   //0x16F7
    GCR8 |= 0x04;
    RSTDMMC = 0x1F;
    RSTC4 = BIT2;   //Reset UART2 (RUART2)

    UART2_LCR = 0x80;   //Bit7: DLAB=1
    UART2_RBR = 0x01;   //UART2_IER = UART2_DLL (DLAB=1)
    UART2_IER = 0x00;   //UART2_IER = UART2_DLM (DLAB=1)
    // 0x00 0x01 : 115200 Baud Rate
    UART2_LCR = 0x03;
    UART2_MCR = 0x00;

    UART2_IIR = 0xC7;   //(W)UART2_IIR = UART2_FCR (Use FIFO)
    UART2_IER = 0x01;

    GPCRH2 = ALT;   //SOUT1
    //GPCRH1 = ALT;   //SIN1
    
#if 0
    UART2_RBR = 'U';
    UART2_RBR = 'A';
    UART2_RBR = 'R';
    UART2_RBR = 'T';
    UART2_RBR = '2';
    UART2_RBR = ' ';
    UART2_RBR = 'O';
    UART2_RBR = 'K';
    UART2_RBR = ' ';
#else
    printf("\n************************************");
    printf("\nEC PRINTF UART2 OK !!!");
    printf("\n************************************");
#endif
}
#endif

//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_Initialization
 * @function - Initialize the registers, data variables, and oem functions
 *             after kernel init. function.
 * @upstream - hook from CORE_MAIN.C
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Oem_Initialization(void)
{
    /* None-used Module Power Down */
    CGCTRL2R |= (EXGCG + CIRCG);

#if SUPPORT_FORCE_SPI_32MB
    FLHCTRL6R |= FSPI26AMEN;
#endif
    Init_SMBus();
    Init_GPIO();
    Init_PWM();
    Init_ADC();
    Init_Kbd();
    Init_WDT();
#if UART1_DEBUG
    Init_UART1();
#endif
#if UART2_DEBUG
    Init_UART2();
#endif
    Reload_EC_Ver();
    //-------------------------------------------------------------------------
    /* Set SAR sensor to test mode */
#if SUPPORT_SAR_TEST_MODE
    SPIBuffer[9] = 0x40;
    bRWSMBus(_SMB_CH1, SMbusWB, IQS231A_TEST_ADDR,
             0x11, &SPIBuffer[9], 0);
#endif
    //-------------------------------------------------------------------------
#if 1   /* Quick Initialize Charger */
    Init_SmartCharger();
#endif

    if (eFlash_Read_1Byte(0x01, 0xF0, 0x00) != 0xFF)
    {
        xEC_SafeVoltageValueL = eFlash_Read_1Byte(0x01, 0xF0, 0x00);
        xEC_SafeVoltageValueH = eFlash_Read_1Byte(0x01, 0xF0, 0x01);
        BAT1_SafeVoltageValue = (xEC_SafeVoltageValueH << 8) + xEC_SafeVoltageValueL;
    }
	else
	{
    	BAT1_SafeVoltageValue = FORCE_SHUTODOWN_BATTERY_VOLTAGE;
	}
    //-------------------------------------------------------------------------
#if SUPPORT_PORT_I2EC
    /* Port I2EC function:
    LPC I/O port with address equal to PORT_I2EC[15:0] + 1: I2EC_XADDR_H
    LPC I/O port with address equal to PORT_I2EC[15:0] + 2: I2EC_XADDR_L
    LPC I/O port with address equal to PORT_I2EC[15:0] + 3: I2EC_XDATA
    EC only accepts the LPC I/O cycle with PORT_I2EC address
    if PI2ECEN bit in SPCTRL2 register is set.
    PI2EC decode full EC RAM page: C000~D7FF
    Example: PI2EC = 0x0680 port setting.
    REG_1060 |= F_PI2EC_DECODE (Need Host side do this op)
    Host Set 0x0681 = 0x10, 0x0682 = 0x60, 0x0683 = 0x80 for switch
    */
    SPCTRL2 |= PI2ECEN;
    PI2ECH = 0x06;
    PI2ECL = 0x80;
#endif
    //-------------------------------------------------------------------------
    // Reset Project Parameter & Variable
    PowerLatchTimer = 5;
    xPowerOnBlinkLEDEn = 0;
    xLowBattShutdownCnt = 0;
    //-------------------------------------------------------------------------
    /* Check Board ID */
    xEC_BoardID_Value = (BYTE)(IS_BRD_ID2_HI() << 1) + (BYTE)IS_BRD_ID1_HI();
    //-------------------------------------------------------------------------
    /* Clear BRAM spaces */
//     for (ITempB01 = 0; ITempB01 < 0x3F; ITempB01++)
//     {
//         BRAM[ITempB01] = 0;
//     }
    for (ITempB01 = 0; ITempB01 < 0x7F; ITempB01++)
    {
        BRAM2[ITempB01] = 0;
    }
    //-------------------------------------------------------------------------

#if SUPPORT_WINAPP_ITE_RFDU
    Init_ReadFlashDataUtility();
#endif

#if SUPPORT_PD_CHIP_ITE
	#if 0
    i = 0;
    if (IS_EC_PWRSW_DN())
    {    
        i = 1;
    }
//     EC_3A = 1;
    Delay1MS(10);
    xPD1_fw_update = ITEi2c_FlashProgress(_ITE_PD1_FLASH_I2C_ADDR);  
//     xPD2_fw_update = ITEi2c_FlashProgress(_ITE_PD2_FLASH_I2C_ADDR); 
    if (i == 0)
    {
//         EC_3A = 0;
    }
	#endif
#endif 
    //-------------------------------------------------------------------------
    /* Set PD I2C address */
    xPD1_i2c_addr = _ITE_PD1_I2C_ADDR;
    xPD2_i2c_addr = _ITE_PD2_I2C_ADDR;
    //-------------------------------------------------------------------------
    // Enable fast charge
    SET_MASK(xEC_FeatureStatus, F_FASTCHARGE_EN_STA);
    // Enable SAR event trigger timer 
    xSAR_Event_Trigger_Timer = 10;
#if SUPPORT_DOCK_EVENT_TRIGGER
    // Enable DOCK in/out event timer 
    xDOCK_Event_In_Timer = 10;
    xDOCK_Event_Out_Timer = 10;
#endif
}

//-----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//-----------------------------------------------------------------------------
void Init_ClearRam(void)
{
    PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr = 0x100;
    while (byte_register_pntr < 0x1000) // Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr = 0;
        byte_register_pntr ++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_Cache
 * @function - Init. DMA for scratch sram
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
//-----------------------------------------------------------------------------
// Initial Table
//-----------------------------------------------------------------------------
const sDMAScratchSRAM code asDMAScratchSRAM[] =
{
    //  *scarh  *scarm  *scarl
#if ITE_CHIP_IT557X
    /* Only SCRA0 support and not use main RAM resources. */
    /* 1024 bytes IT557x  */
    {   &SCRA0H, &SCRA0M, &SCRA0L },
    {   &SCRA0H, &SCRA0M, &SCRA0L },
    {   &SCRA0H, &SCRA0M, &SCRA0L },
    {   &SCRA0H, &SCRA0M, &SCRA0L },
#else
    /* 1024 bytes (externl ram 0x800 ~ 0xBFF) */
    {   &SCRA1H, &SCRA1M, &SCRA1L },
    /* 512 bytes  (externl ram 0xC00 ~ 0xDFF) */
    {   &SCRA2H, &SCRA2M, &SCRA2L },
    /* 256 bytes  (externl ram 0xE00 ~ 0xEFF) */
    {   &SCRA3H, &SCRA3M, &SCRA3L },
    /* 256 bytes  (externl ram 0xF00 ~ 0xFFF) */
    {   &SCRA4H, &SCRA4M, &SCRA4L }
#endif
};
//-----------------------------------------------------------------------------
void CacheDma(BYTE sramnum, WORD addr)
{
    *asDMAScratchSRAM[sramnum].scarh = 0x80;
    /* low byte of function address */
    *asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;
    /* high byte of function address */
    *asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;
    /* start cache dma */
    *asDMAScratchSRAM[sramnum].scarh = 0x00;
}
//-----------------------------------------------------------------------------
void Init_Cache(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ECExitFollowMode
 * @function - EC leaves follow mode or EC scatch ROM and jump to main function
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Before jump to main function
 *             [WinFlashMark = 0x33;] is necessary.
 */
void Hook_ECExitFollowMode(void)
{
    Init_Cache();

#ifdef HSPI_DefferingMode
    /* Enable HSPI interrupt */
    SET_MASK(IER7, Int_DeferredSPI);
#endif

    Init_PWM();

    Reload_EC_Ver();    /* Flash update reload */
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ECRetunrMainFuncKeepCondition
 * @function - EC leaves follow mode or EC scatch ROM and jump to main function
 * @upstream - By call
 * @input    - None
 * @return   - 0x33 or 0x00
 * @note     - 1. Before jump to main function if want to keep EC setting
 *                [return(0x33);] is necessary.
 *             2. If you don't understand the use of
 *                Hook_ECRetunrMainFuncKeepCondition function, don't change
 *                anything.
 *             3. Always at bank0 (0x9000)
 */
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if (WinFlashMark == 0x33)
    {
        /* Flash update */
        Hook_Setup_Scanner_Pntr();
#if SUPPORT_FLASH_OFF_SEQUENCE
        SetShutdownType = 0;
        if (BRAM[63] == 0xAA)
        {
            /* If U mark out this Set_SysPowState, the code will waiting
               user shutdown and then Reset EC chip */
            Set_SysPowState(_PST_S0_to_S5);

            SetShutdownType = 0x44;
        }
#endif
        return(0x33);
    }
    else
    {
#if INTEL_EC_FLASH_AUTO_POWER_ON
        if ((BRAM[62] == 0xA5) && (BRAM[63] == 0x55))
        {
            SetAutoBootTimer = 5;
        }
#endif 
        return(0x00);
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_INIT.C */