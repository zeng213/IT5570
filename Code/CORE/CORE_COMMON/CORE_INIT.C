/*-----------------------------------------------------------------------------
 * TITLE: CORE_INIT.C
 *
 * Author : Dino
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// FUNCTION: cold_reset - Initialization when power goes on
//----------------------------------------------------------------------------
void cold_reset(void)
{
	Ext_Cb2.byte = EXT_CB2_INIT;
	Save_Typematic = SAVE_TYPEMATIC_INIT;
	Save_Kbd_State = (SAVE_KBD_STATE_INIT & ~maskLEDS) | (0 & maskLEDS);

    Led_Ctrl = LED_CTRL_INIT;
    Led_Data = 0;
    Gen_Info = 0;   /* Clear general control. */

    Int_Var.Ticker_10 = 10;

    Flag.PASS_READY = 0;    /* Password not loaded. */
    Int_Var.Ticker_100 = 50;

    Flag.SCAN_INH = 1;      /* Scanner transmission inhibited. */
    Flag.VALID_SCAN = 0;

    Flag.NEW_PRI_K = 0;
    Flag.NEW_PRI_M = 0;

    Flag.LED_ON = 1;
    Ccb42 = CCB42_INIT;

    Pass_On = 0;      /* Password enable send code. */
    Pass_Off = 0;     /* Password disable send code. */
    Pass_Make1 = 0;   /* Reject make code 1. */
    Pass_Make2 = 0;   /* Reject make code 2. */

    MULPX = 0;

}


//----------------------------------------------------------------------------
// FUNCTION:   general_reset1, general_reset2
// Initialize things common to both Cold/Warm reset.
//----------------------------------------------------------------------------
static void common_reset(void)  /* MCHT, 27/05/04 */ // static void general_reset1(void)
{
    Service  = 0;       /* Clear service requests */
    Service1 = 0;

    Kbd_Response = 0;   /* Clear response codes */
    Timer_A.byte = 0;   /* Clear Timer A events */
    Timer_B.byte = 0;   /* Clear Timer B events */
    Scanner_State = 0;  /* Clear scanner state */
}


//----------------------------------------------------------------------------
// FUNCTION: Init_Mouse - Initialize the Intelligent mouse variables.
//----------------------------------------------------------------------------
void Init_Mouse (void)
{

}

void Core_Initialization(void)
{
    Init_Kbd();
	cold_reset();
	common_reset();
	Init_Mouse();
	Init_Timers();
    Core_Init_Regs();
    Core_Init_SMBus();

#if SUPPORT_INTERFACE_eSPI
    ESGCTRL1 = 0x80;    /* REG@31A1.7: eSPI Interrupt Enable */
    ESGCTRL2 = 0x10;    /* REG@31A1.4: eSPI To WUC Enable */
#endif

#if	ITE_CHIP_IT557X
	Init_EC_Indirect_Selection(SPI_selection_internal);
#endif
    #if !TouchPad_only
    //
    // delay 600 ms for scaning aux devices
    //
    SetPS2SkipScanTime(60);
    #endif
}

//----------------------------------------------------------------------------
// The function of clearing internal and external ram for kernel code
// Clear external ram (0x000~0x0FF)
// Clear internal ram (0x20~0xCF)
//----------------------------------------------------------------------------
void Core_Init_ClearRam(void)
{
	IIBYTE *IdataIndex;
	PORT_BYTE_PNTR byte_register_pntr;

	IdataIndex = 0x20;
    byte_register_pntr=0;

    while (byte_register_pntr < 0x100)  // Clear external ram (0x000~0xFFF)
    {
        *byte_register_pntr = 0;
        byte_register_pntr ++;
    }

	while (IdataIndex < 0xC0)			// Clear internal ram (0x20~0xBF)
    {
        *IdataIndex = 0;
        IdataIndex ++;
    }

#if	ITE_CHIP_IT557X
    byte_register_pntr = 0x9000;
    while (byte_register_pntr < 0x9800) // Clear external ram (0x9000~0x97FF)
    {
        *byte_register_pntr = 0;
        byte_register_pntr++;
    }
#endif
}

//----------------------------------------------------------------------------
// The function of init. registers of kernel code
//----------------------------------------------------------------------------
const sREG_INIT code Core_reg_init_table[] =
{
 		{ &FMSSR 		,Core_Init_FMSSR    }, 	// share rom size
// HOST interface
    	{ &SPCTRL1      ,Core_Init_I2EC     },  // Enable I2EC R/W
    	{ &BADRSEL      ,Core_Init_BADR     },  // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define
    	{ &SWCBALR      ,Core_Init_SWCBALR  },
    	{ &SWCBAHR      ,Core_Init_SWCBAHR  },
		{ &RSTS			,0x84				},

// KBC and PM interface
		{ &KBIRQR 		,0x00              	}, 	// Disable KBC IRQ
        { &KBHICR 		,IBFCIE+PM1ICIE     }, 	// KBC port control IBFCIE+PMICIE
        { &PM1CTL		,IBFIE+SCINP        }, 	// EC port control  IBFCIE+SCI low active
        { &PM2CTL 		,IBFIE+SCINP        }, 	// EC port2 control IBFCIE+SCI low active
// PS2
        { &PSCTL1 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL2 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL3 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        #if TouchPad_only
		{ &PSINT1		,0x04				}, 	// Transation Done Interrupt
        { &PSINT2		,0x04				},	// Transation Done Interrupt
        { &PSINT3		,0x04				},	// Transation Done Interrupt
        #else
		{ &PSINT1		,0x06				}, 	// Transation Done,Start Clock Interrupt
        { &PSINT2		,0x06				},	// Transation Done,Start Clock Interrupt
        { &PSINT3		,0x06				},	// Transation Done,Start Clock Interrupt
        #endif

// Key Scan
        { &KSOCTRL   	,KSOOD + KSOPU      },	//
  		{ &KSICTRL   	,KSIPU       		},	//
};

void Core_Init_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(Core_reg_init_table)/sizeof(sREG_INIT)))
    {
        Tmp_XPntr = Core_reg_init_table[index].address;
		*Tmp_XPntr = Core_reg_init_table[index].initdata;
        index ++;
    }

    CLEAR_MASK(FLHCTRL2R,BIT3);
}


//-----------------------------------------------------------------------------
// Changing PLL frequency function
//-----------------------------------------------------------------------------
void ChangePLLFrequency(BYTE newseting)
{
    if (ECHIPVER >= _CHIP_EX)
    {
        SET_MASK(ESGCTRL2, F_ESPIIPG);  //eSPI Pad is gated.
    }
    RSTS &= 0x3F;	//Set VCC power status is power-off
    if (newseting != PLLFREQR)
    {
        PLLFREQR = newseting;   //REG@1E06
        PLLCTRL = 1;
        DisableAllInterrupt();
	    PCON = 2;             	// enter sleep mode
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
#if ITE_CHIP_IT557X
        ISR19 = Int_PLL_Change;    //REG@1150 Clear Interrupt Status
#endif
    }
}

//----------------------------------------------------------------------------
// INIT UART
//----------------------------------------------------------------------------
void Init_UART_Debug(void)
{
#ifdef MCU_UART_Debug
    //GPCRE6 = ALT;     /* Enable IT5570E TXD */
    //GCR15 |= 0x80;    /* IT5570E GPE6 is TX pin.*/

    GPCRB1 = ALT;       /* Enable IT5571E TXD */
    SCON = 0x40;        /* Mode 1 */
    T2CON &= 0xF0;      /* EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0; */
    T2CON |= 0x30;      /* RCLK = 1; TCLK=1; */
    T2MOD = 0x00;
    RCAP2H = R2HV;
    RCAP2L = R2LV;
    TR2 = 1;
    TI = 1;
#endif
}

/*-----------------------------------------------------------------------------
 * End of CORE_INIT.C */