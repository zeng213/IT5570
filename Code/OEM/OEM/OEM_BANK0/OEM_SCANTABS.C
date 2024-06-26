/*-----------------------------------------------------------------------------
 * @file     | OEM_SCANTABS.C
 *-----------+-----------------------------------------------------------------
 * @function | Matrix keyboard scan table and OEM key hook
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
#define DEBUG_SCTB              FALSE



/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_SCTB
#define SCTB_RamDebug(x)    RamDebug(x)
#else
#define SCTB_RamDebug(x)    {}
#endif

//*****************************************************************************
// CODE START
//*****************************************************************************
const unsigned char code ADL_P_Rc_ROM_Tables[] =
{
    /* Scanner Table 1  - 16 x 8 Scan Table - General US/UK
     KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO   KSO
      00    01    02    03    04    05    06    07    08    09    10    11    12    13    14    15   */
    0x8E, 0xEC, 0x00, 0x00, 0x00, 0xAF, 0x00, 0xB1, 0xB2, 0xB3, 0xB5, 0xE2, 0xB6, 0xB7, 0x7E, 0x95,   // KSI0
    0x00, 0xAD, 0x88, 0x00, 0x00, 0xAE, 0x00, 0xB0, 0x36, 0x3E, 0xB4, 0x91, 0x46, 0xB8, 0x94, 0xE3,   // KSI1
    0x00, 0x0E, 0x00, 0x8C, 0x00, 0x1E, 0x00, 0x25, 0x2E, 0x3D, 0x43, 0x51, 0x44, 0x45, 0x55, 0x66,   // KSI2
    0x00, 0x0D, 0x00, 0x00, 0x82, 0x1D, 0x00, 0x24, 0x2D, 0x35, 0x42, 0x5D, 0xBB, 0x54, 0x61, 0x5A,   // KSI3
    0x00, 0x58, 0x89, 0x00, 0x00, 0x1B, 0x00, 0x23, 0x34, 0x33, 0x3A, 0x2F, 0x97, 0x96, 0x98, 0x5D,   // KSI4
    0x00, 0x1C, 0x00, 0x00, 0x00, 0x22, 0x8A, 0xBA, 0x2B, 0x31, 0x41, 0x83, 0x49, 0x4A, 0x00, 0x4C,   // KSI5
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x8B, 0x27, 0x2A, 0x32, 0xB9, 0x84, 0x52, 0x00, 0x9A, 0x99,   // KSI6
    0x00, 0x16, 0x00, 0x8D, 0x00, 0x15, 0x00, 0x26, 0x2C, 0x3C, 0x3B, 0x00, 0x4D, 0x4E, 0x5B, 0x9B,   // KSI7
};
//;-----------------------------------------------------------------------------------------
const unsigned char code EtKey_ROM_Tables[] =
{
    //16   17   18      // 19X8 Scan Table
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
};
//;-----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// The function of hotkey Fn + F1
//----------------------------------------------------------------------------

void HotKey_Fn_F1(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))
    {
        WriteSCI_Buffer(_SCIEVT_BRIGHTNESS_DN);
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F2
//----------------------------------------------------------------------------
void HotKey_Fn_F2(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))
    {
        WriteSCI_Buffer(_SCIEVT_BRIGHTNESS_UP);
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F3
//----------------------------------------------------------------------------
void HotKey_Fn_F3(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))  //win+P  ;Demo
    {
        Buffer_Key(0xE0);   //L-Win Make
        Buffer_Key(0x1F);
        Buffer_Key(0x4D);
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xF0);
            Buffer_Key(0x4D);

            Buffer_Key(0xE0);
            Buffer_Key(0xF0);
            Buffer_Key(0x1F);
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F4
//----------------------------------------------------------------------------
void HotKey_Fn_F4(BYTE event)
{
    if ((event == MAKE_EVENT)/*||(event == REPEAT_EVENT)*/)     //VOLUME mute
    {
        Buffer_Key(0xE0);   /* Buffer E0h prefix */
        Buffer_Key(0x23);   /* Buffer base code */
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xE0);   /* Buffer E0h prefix */
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x23);   /* Buffer base code */
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F5
//----------------------------------------------------------------------------
void HotKey_Fn_F5(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))   //VOLUME DOWN
    {
        Buffer_Key(0xE0);   /* Buffer E0h prefix */
        Buffer_Key(0x21);   /* Buffer base code */
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xE0);   /* Buffer E0h prefix */
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x21);   /* Buffer base code */
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F6
//----------------------------------------------------------------------------
void HotKey_Fn_F6(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))   //VOLUME UP
    {
        Buffer_Key(0xE0);   /* Buffer E0h prefix */
        Buffer_Key(0x32);   /* Buffer base code */
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xE0);   /* Buffer E0h prefix */
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x32);   /* Buffer base code */
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F7
//----------------------------------------------------------------------------
void HotKey_Fn_F7(BYTE event)
{
    if ((event == MAKE_EVENT))      //VOLUME mute
    {
        Buffer_Key(0x14);   /* Buffer base code */  //L-Ctrl 14-->F0,14

        Buffer_Key(0xE0);   /* Buffer E0h prefix */    //L-Gui      E0 1F  -->E0 F0 1F
        Buffer_Key(0x1F);   /* Buffer E0h prefix */    //L-Gui      E0 1F  -->E0 F0 1F

        Buffer_Key(0x5F);   /* Buffer E0h prefix */  //F24  5F  -->F0 5F
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x14);   /* Buffer base code */  //  L-Ctrl       14-->F0,14

            Buffer_Key(0xE0);   /* Buffer E0h prefix */    //L-Gui      E0 1F  -->E0 F0 1F
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x1F);   /* Buffer E0h prefix */    //L-Gui      E0 1F  -->E0 F0 1F

            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x5F);   /* Buffer E0h prefix */  //   F24--      5F  -->F0 5F
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F8
//----------------------------------------------------------------------------
void HotKey_Fn_F8(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))
    {
        WriteSCI_Buffer(_SCIEVT_WIRELESS_CTRL);
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F9
//----------------------------------------------------------------------------
void HotKey_Fn_F9(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F10
//----------------------------------------------------------------------------
void HotKey_Fn_F10(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F11
//----------------------------------------------------------------------------
void HotKey_Fn_F11(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F12
//----------------------------------------------------------------------------
void HotKey_Fn_F12(BYTE event)
{
    if ((event == MAKE_EVENT) || (event == REPEAT_EVENT))   //Print Screen
    {
        Buffer_Key(0xE0);   /* Buffer E0h prefix */
        Buffer_Key(0x7C);   /* Buffer base code */
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xE0);   /* Buffer E0h prefix */
            Buffer_Key(0xF0);   /* Buffer E0h prefix */
            Buffer_Key(0x7C);   /* Buffer base code */
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + ESC
//----------------------------------------------------------------------------
void HotKey_Fn_ESC(BYTE event)
{
    if (event == MAKE_EVENT)         //Sleep
    {
        Buffer_Key(0xE0);   /* Buffer E0h prefix */
        Buffer_Key(0x3F);   /* Buffer base code */
        //      WriteSCI_QueryValue(_SCIEVT_FnF1);
    }
    else
    {
        if (event == BREAK_EVENT)
        {
            Buffer_Key(0xE0);   /* Buffer E0h prefix */
            Buffer_Key(0xF0);   /* Buffer base code */
            Buffer_Key(0x3F);   /* Buffer base code */
        }
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + up arrow
//----------------------------------------------------------------------------
void HotKey_Fn_UP(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + down arrow
//----------------------------------------------------------------------------
void HotKey_Fn_DOWN(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + left arrow
//----------------------------------------------------------------------------
void HotKey_Fn_LEFT(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + right arrow
//----------------------------------------------------------------------------
void HotKey_Fn_RIGHT(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Space
//---------------------------------------------------------------------------
void HotKey_Fn_SPACE(BYTE event)
{

}

#if SUPPORT_OOB_CRASHLOG_KEY
//----------------------------------------------------------------------------
// The function of hotkey Fn + C (For Crashlog)
//---------------------------------------------------------------------------
void HotKey_Fn_C(BYTE event)
{
    if (event == MAKE_EVENT)
    {
        SET_MASK(xOOB_KEY_CRASHLOG, KEY_FCD_LOCK);
    }
    else
    {
        CLEAR_MASK(xOOB_KEY_CRASHLOG, KEY_FCD_LOCK);
    }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + L (For Crashlog)
//---------------------------------------------------------------------------
void HotKey_Fn_L(BYTE event)
{
    if (event == MAKE_EVENT)
    {
        SET_MASK(xOOB_KEY_CRASHLOG, KEY_FLD_LOCK);
    }
    else
    {
        CLEAR_MASK(xOOB_KEY_CRASHLOG, KEY_FLD_LOCK);
    }
}
#endif

const FUNCT_PTR_V_B code HotKey_Fn_Fx[] =
{
    HotKey_Fn_F1,       // Fn + F1 D0
    HotKey_Fn_F2,       // Fn + F2 D1
    HotKey_Fn_F3,       // Fn + F3 D2
    HotKey_Fn_F4,       // Fn + F4 D3
    HotKey_Fn_F5,       // Fn + F5 D4
    HotKey_Fn_F6,       // Fn + F6 D5
    HotKey_Fn_F7,       // Fn + F7 D6
    HotKey_Fn_F8,       // Fn + F8 D7
    HotKey_Fn_F9,       // Fn + F9 D8
    HotKey_Fn_F10,      // Fn + F10 D9
    HotKey_Fn_F11,      // Fn + F11 DA
    HotKey_Fn_F12,      // Fn + F12 DB
    HotKey_Fn_ESC,      // Fn + ESC DC
    HotKey_Fn_UP,       // Fn + up arrow    DD
    HotKey_Fn_DOWN,     // Fn + down arrow  DE
    HotKey_Fn_LEFT,     // Fn + left arrow  DF
    HotKey_Fn_RIGHT,    // Fn + right arrow E0
    HotKey_Fn_SPACE,    // Fn + Space       E1
#if SUPPORT_OOB_CRASHLOG_KEY
    HotKey_Fn_C,        // Fn + C           E2
    HotKey_Fn_L,        // Fn + L           E3
#endif
};

//---------------------------------------------------------------------------
//  Numpad 7 Home   [B0h]
//  Numpad 8 UP     [B1h]
//  Numpad 9 PGUp   [B2h]
//  Numpad *        [B3h]
//  Numpad 4 Left   [B4h]
//  Numpad 5        [B5h]
//  Numpad 6 Right  [B6h]
//  Numpad -        [B7h]
//  Numpad 1 End    [B8h]
//  Numpad 2 Down   [B9h]
//  Numpad 3 PGDn   [BAh]
//  Numpad +        [BBh]
//  Numpad 0 Ins    [BCh]
//  Numpad . Del    [BDh]
//  Numpad /        [BEh]
//---------------------------------------------------------------------------

const BYTE code ss2_9C[] =  // Numpad 7
{
    0x3D,   // Normal       // 7
    0xB0,   // Numlock
    0xB0,   // Fn
    0xB0    // Fn+Numlock
};

const BYTE code ss2_9D[] =  // Numpad 8
{
    0x3E,   // Normal       // 8
    0xB1,   // Numlock
    0xB1,   // Fn
    0xB1    // Fn+Numlock
};

const BYTE code ss2_9E[] =  // Numpad 9
{
    0x46,   // Normal       // 9
    0xB2,   // Numlock
    0xB2,   // Fn
    0xB2    // Fn+Numlock
};

const BYTE code ss2_9F[] =  // Numpad 0
{
    0x45,   // Normal       // 0
    0xB3,   // Numlock
    0xB3,   // Fn
    0xB3    // Fn+Numlock
};

const BYTE code ss2_A0[] =  // Numpad U
{
    0x3C,   // Normal       // U
    0xB4,   // Numlock
    0xB4,   // Fn
    0xB4    // Fn+Numlock
};

const BYTE code ss2_A1[] =  // Numpad I
{
    0x43,   // Normal       // I
    0xB5,   // Numlock
    0xB5,   // Fn
    0xB5    // Fn+Numlock
};

const BYTE code ss2_A2[] =  // Numpad O
{
    0x44,   // Normal       // O
    0xB6,   // Numlock
    0xB6,   // Fn
    0xB6    // Fn+Numlock
};

const BYTE code ss2_A3[] =  // Numpad P
{
    0x4D,   // Normal       // P
    0xB7,   // Numlock -
    0xB7,   // Fn
    0xB7    // Fn+Numlock
};

const BYTE code ss2_A4[] =  // Numpad J
{
    0x3B,   // Normal       // J
    0xB8,   // Numlock
    0xB8,   // Fn
    0xB8    // Fn+Numlock
};

const BYTE code ss2_A5[] =  // Numpad K
{
    0x42,   // Normal       // K
    0xB9,   // Numlock
    0xB9,   // Fn
    0xB9    // Fn+Numlock
};

const BYTE code ss2_A6[] =  // Numpad L
{
    0x4B,   // Normal       // L
    0xBA,   // Numlock
    0xBA,   // Fn
    0xBA    // Fn+Numlock
};

const BYTE code ss2_A7[] =  // Numpad ;:
{
    0x4C,   // Normal       // ;:
    0xBB,   // Numlock
    0xBB,   // Fn
    0xBB    // Fn+Numlock
};

const BYTE code ss2_A8[] =  // Numpad M
{
    0x3A,   // Normal       // M
    0xBC,   // Numlock
    0xBC,   // Fn
    0xBC    // Fn+Numlock
};

const BYTE code ss2_A9[] =  // Numpad ,<
{
    0x41,   // Normal       // ,<
    0x41,   // Numlock
    0x41,   // Fn
    0x41    // Fn+Numlock
};

const BYTE code ss2_AA[] =  // Numpad .>
{
    0x49,   // Normal       // .>
    0xBD,   // Numlock
    0xBD,   // Fn
    0xBD    // Fn+Numlock
};

const BYTE code ss2_AB[] =  // Numpad /?
{
    0x4A,   // Normal       // /?
    0xBE,   // Numlock
    0xBE,   // Fn
    0xBE    // Fn+Numlock
};

const BYTE code ss2_AC[] =
{
    0x5A,   // Normal
    0x81,   // Fn
};
//----------------------------------------------------------------
// Function key F1 ~ F12
//----------------------------------------------------------------
const BYTE code ss2_AD[] =  // F1
{
    0x05,   // Normal
    0xD0,   // Fn
};

const BYTE code ss2_AE[] =  // F2
{
    0x06,   // Normal
    0xD1,   // Fn
};

const BYTE code ss2_AF[] =  // F3
{
    0x04,   // Normal
    0xD2,   // Fn
};

const BYTE code ss2_B0[] =  // F4
{
    0x0C,   // Normal
    0xD3,   // Fn
};

const BYTE code ss2_B1[] =  // F5
{
    0x03,   // Normal
    0xD4,   // Fn
};

const BYTE code ss2_B2[] =  // F6
{
    0x0B,   // Normal
    0xD5,   // Fn
};

const BYTE code ss2_B3[] =  // F7
{
    0x80,   // Normal
    0xD6,   // Fn
};

const BYTE code ss2_B4[] =  // F8
{
    0x0A,   // Normal
    0xD7,   // Fn
};

const BYTE code ss2_B5[] =  // F9
{
    0x01,   // Normal
    0xD8,   // Fn
    //0x01,   // Normal
};

const BYTE code ss2_B6[] =  // F10
{
    0x09,   // Normal
    0xD9,   // Fn
};

const BYTE code ss2_B7[] =  // F11
{
    0x78,   // Normal
    0xDA,   // Fn
};

const BYTE code ss2_B8[] =  // F12
{
    0x07,   // Normal
    0xDB,   // Fn
};

const BYTE code ss2_B9[] =  // Fn + Space
{
    0x29,   // Space
    0xE1,   // Fn
};

const BYTE code ss2_BA[] =  // Fn + C
{
    0x21,   // Normal
    0xE2,
};

const BYTE code ss2_BB[] =  // Fn + L
{
    0x4B,   // Normal
    0xE3,   // Fn
};

/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_A2_table
 *
 * The A2_TABLE structure contains the following.
 *
 * BYTE comb;  Bit   Setting Combination Key
 *            ---   -----------------------
 *             7    Hook_calc_index_comb_BIT7
 *             6    Hook_calc_index_comb_BIT6
 *             5    Fn
 *             4    Numlock
 *             3    Ctrl
 *             2    Alt
 *             1    Shift
 *             0    reserved
 *
 * BYTE *pntr; Pointer to array for key.
 * ------------------------------------------------------------------------- */
const A2_TABLE sskey2_A2_table[] =
{
    // Keyboard matrix index
    // Keypad -->
    {0x30, ss2_9C },    /* index = 00h */   // 0x9C
    {0x30, ss2_9D },    /* index = 01h */   // 0x9D
    {0x30, ss2_9E },    /* index = 02h */   // 0x9E
    {0x30, ss2_9F },    /* index = 03h */   // 0x9F
    {0x30, ss2_A0 },    /* index = 04h */   // 0xA0
    {0x30, ss2_A1 },    /* index = 05h */   // 0xA1
    {0x30, ss2_A2 },    /* index = 06h */   // 0xA2
    {0x30, ss2_A3 },    /* index = 07h */   // 0xA3
    {0x30, ss2_A4 },    /* index = 08h */   // 0xA4
    {0x30, ss2_A5 },    /* index = 09h */   // 0xA5
    {0x30, ss2_A6 },    /* index = 0Ah */   // 0xA6
    {0x30, ss2_A7 },    /* index = 0Bh */   // 0xA7
    {0x30, ss2_A8 },    /* index = 0Ch */   // 0xA8
    {0x30, ss2_A9 },    /* index = 0Dh */   // 0xA9
    {0x30, ss2_AA },    /* index = 0Eh */   // 0xAA
    {0x30, ss2_AB },    /* index = 0Fh */   // 0xAB
    {0x20, ss2_AC },    /* index = 10h */   // 0xAC
    // Keypad <--

    // F1~F12 hotkeys -->
    {0x20, ss2_AD },    /* index = 11h */   // 0xAD
    {0x20, ss2_AE },    /* index = 12h */   // 0xAE
    {0x20, ss2_AF },    /* index = 13h */   // 0xAF
    {0x20, ss2_B0 },    /* index = 14h */   // 0xB0
    {0x20, ss2_B1 },    /* index = 15h */   // 0xB1
    {0x20, ss2_B2 },    /* index = 16h */   // 0xB2
    {0x20, ss2_B3 },    /* index = 17h */   // 0xB3
    {0x20, ss2_B4 },    /* index = 18h */   // 0xB4
    {0x20, ss2_B5 },    /* index = 19h */   // 0xB5
    {0x20, ss2_B6 },    /* index = 1Ah */   // 0xB6
    {0x20, ss2_B7 },    /* index = 1Bh */   // 0xB7
    {0x20, ss2_B8 },    /* index = 1Ch */   // 0xB8

    {0x20, ss2_B9 },    /* index = 1Dh */   // 0xB9    // Fn + Space
    {0x20, ss2_BA },    /* index = 1Eh */   // 0xBA    // Fn + C  for CrashLog
    {0x20, ss2_BB }     /* index = 1Fh */   // 0xBB    // Fn + L  for CrashLog
};
// Reserved 0xB9 ~ 0xDF

/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_overlay_table
 * ------------------------------------------------------------------------- */
const BYTE code sskey2_overlay_table[] =
{
    //  Normal      Fn              // Keyboard matrix index
    0xC0, 0xC0, //  Print Scr   SysRq           // 0xE0
    0x77, 0x7E, //  Num Lk      Scr LK          // 0xE1
    0xC0, 0xC0, //  Del         Del             // 0xE2
    0xC2, 0xC2, //  Insert      Insert          // 0xE3

    0x98, 0xDD, //  Up arrow    Function key up arrow  (HotKey_Fn_Up)       // 0xE4
    0x99, 0xDE, //  Down arrow  Function key down arrow  (HotKey_Fn_Down)   // 0xE5
    0x9A, 0xA2, //  Left arrow  Function key Left arrow  (HotKey_Fn_LEFT)   // 0xE6
    0x9B, 0xA1, //  Right arrow Function key Right arrow (HotKey_Fn_RIGHT)  // 0xE7

    0x94, 0x9F, //  Home        Play/Pause event// 0xE8
    0x96, 0x9E, //  PgUp        Stop event      // 0xE9
    0x97, 0x9D, //  PgDn        Prev Track event// 0xEA
    0x95, 0x9C, //  End         Next Track event// 0xEB

    0x76, 0xDC, //  ESC         ESC             // 0xEC
    0xBE, 0xBE, //  KeyPad_/    KeyPad_/        // 0xED

    0xC4, 0xC4, // Euro Sign    // Euro Sign    // 0xEE
    0xC5, 0xC5, // Dollar Sign  // Dollar Sign  // 0xEF

    0x09, 0xC3, // F10          PrtScr          // 0xF0
    0x78, 0x7E, // F11          Scr LK          // 0XF1
    0x07, 0x77, // F12          Num Lk          // 0XF2
    0xC0, 0xC2, // Del          Insert          // 0xF3
};


/* ----------------------------------------------------------------------------
 * Insyde Software Key Number 2
 *
 * 00h         Null
 * 01h - 7Fh   Same as IBM Scan Code, Set2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * C0h - DFh   Pre-Index for PPK function
 * C0h - DFh   Pre-Index for SMI function
 * ------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 * FUNCTION: sskey3_80_table - Insyde Software Key Number 2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * ------------------------------------------------------------------------- */
const BYTE code sskey3_80_table[] =
{
    //-----------------------------------------------------------------
    // Index from keyboard matrix
    //-----------------------------------------------------------------
    // Keyboard matrix index
    0x83,   DO_SIMPLE_CODE,         // [80h] F7 (118)
    0x5A,   DO_E0_PREFIX_CODE,      // [81h] Numpad Enter (108)
    0x1F,   DO_E0_PREFIX_CODE,      // [82h] Windows Left
    0x27,   DO_E0_PREFIX_CODE,      // [83h] Windows Right
    0x2F,   DO_E0_PREFIX_CODE,      // [84h] Application
    0x37,   DO_E0_PREFIX_CODE,      // [85h] Power event
    0x3F,   DO_E0_PREFIX_CODE,      // [86h] Sleep event
    0x5E,   DO_E0_PREFIX_CODE,      // [87h] Wake event
    LShift, DO_CONTROL_EFFECT,      // [88h] 12 Shift(L)
    RShift, DO_CONTROL_EFFECT,      // [89h] 59 Shift(R)
    LAlt,   DO_CONTROL_EFFECT,      // [8Ah] 11 Alt(L)
    RAlt,   DO_CONTROL_EFFECT_E0,   // [8Bh] E0 11 Alt(R)
    LCtrl,  DO_CONTROL_EFFECT,      // [8Ch] 14 Crtl(L)
    RCtrl,  DO_CONTROL_EFFECT_E0,   // [8Dh] E0 14 Ctrl(R)
    FN,     DO_CONTROL_EFFECT,      // [8Eh] Fn
    OVLAY,  DO_CONTROL_EFFECT,      // [8Fh] Overlay
    0x00,   DO_SIMPLE_CODE,         // [90h] Reserved
    0x00,   DO_SPECIAL_CODE,        // [91h] Pause (126)
    0x01,   DO_SPECIAL_CODE,        // [92h] Break
    0x84,   DO_SIMPLE_CODE,         // [93h] (124) Alt-Case (SysRq)
    0x6C,   DO_E0_PREFIX_CODE,      // [94h] Home
    0x69,   DO_E0_PREFIX_CODE,      // [95h] End
    0x7D,   DO_E0_PREFIX_CODE,      // [96h] Page up
    0x7A,   DO_E0_PREFIX_CODE,      // [97h] Page down
    0x75,   DO_E0_PREFIX_CODE,      // [98h] UP arrow
    0x72,   DO_E0_PREFIX_CODE,      // [99h] Down arrow
    0x6B,   DO_E0_PREFIX_CODE,      // [9Ah] Left arrow
    0x74,   DO_E0_PREFIX_CODE,      // [9Bh] Right arrow

    //-----------------------------------------------------------------
    // For MicroSoft enhance keyboard feature.
    //-----------------------------------------------------------------
    0x4D, DO_E0_PREFIX_CODE,        // [9Ch] Next Track event
    0x15, DO_E0_PREFIX_CODE,        // [9Dh] Prev Track event
    0x3B, DO_E0_PREFIX_CODE,        // [9Eh] Stop event
    0x34, DO_E0_PREFIX_CODE,        // [9Fh] Play/Pause event
    0x23, DO_E0_PREFIX_CODE,        // [A0h] Mute event
    0x32, DO_E0_PREFIX_CODE,        // [A1h] Volume Up event
    0x21, DO_E0_PREFIX_CODE,        // [A2h] Volume Down event
    0x48, DO_E0_PREFIX_CODE,        // [A3h] Mail event
    0x10, DO_E0_PREFIX_CODE,        // [A4h] Search event
    0x3A, DO_E0_PREFIX_CODE,        // [A5h] Web/Home event
    0x38, DO_E0_PREFIX_CODE,        // [A6h] Back event
    0x30, DO_E0_PREFIX_CODE,        // [A7h] Forward event
    0x28, DO_E0_PREFIX_CODE,        // [A8h] Stop event
    0x20, DO_E0_PREFIX_CODE,        // [A9h] Refresh event
    0x18, DO_E0_PREFIX_CODE,        // [AAh] Favorites event
    0x2B, DO_E0_PREFIX_CODE,        // [ABh] Caluator event
    0x40, DO_E0_PREFIX_CODE,        // [ACh] My Computer event
    0x50, DO_E0_PREFIX_CODE,        // [ADh] Media event
    0x00, DO_SIMPLE_CODE,           // [AEh] Reserved
    0x00, DO_SIMPLE_CODE,           // [AFh] Reserved

    //-----------------------------------------------------------------
    // Index from sskey2_A2_table
    //-----------------------------------------------------------------
    0x6C, DO_SIMPLE_CODE,           // Numpad 7 Home    [B0h]
    0x75, DO_SIMPLE_CODE,           // Numpad 8 UP      [B1h]
    0x7D, DO_SIMPLE_CODE,           // Numpad 9 PGUp    [B2h]
    0x7C, DO_SIMPLE_CODE,           // Numpad *         [B3h]
    0x6B, DO_SIMPLE_CODE,           // Numpad 4 Left    [B4h]
    0x73, DO_SIMPLE_CODE,           // Numpad 5         [B5h]
    0x74, DO_SIMPLE_CODE,           // Numpad 6 Right   [B6h]
    0x7B, DO_SIMPLE_CODE,           // Numpad -         [B7h]
    0x69, DO_SIMPLE_CODE,           // Numpad 1 End     [B8h]
    0x72, DO_SIMPLE_CODE,           // Numpad 2 Down    [B9h]
    0x7A, DO_SIMPLE_CODE,           // Numpad 3 PGDn    [BAh]
    0x79, DO_SIMPLE_CODE,           // Numpad +         [BBh]
    0x70, DO_SIMPLE_CODE,           // Numpad 0 Ins     [BCh]
    0x71, DO_SIMPLE_CODE,           // Numpad . Del     [BDh]
    0x4A, DO_E0_PREFIX_CODE,        // Numpad /         [BEh]

    0x00, DO_SIMPLE_CODE,           // Reserved         [BFh]

    0x71, DO_E0_PREFIX_CODE,        // Delete           [C0h]
    0x84, DO_SIMPLE_CODE,           // SysRq            [C1h]
    0x70, DO_E0_PREFIX_CODE,        // Insert           [C2h]
    0x7C, DO_E0_PREFIX_CODE,        // Print Screen     [C3h]
    0x41, DO_E0_PREFIX_CODE,        // Euro Sign        [C4h]
    0x49, DO_E0_PREFIX_CODE,        // Dollar Sign      [C5h]
    0x00, DO_SIMPLE_CODE,           // Reserved         [C6h]
    0x00, DO_SIMPLE_CODE,           // Reserved         [C7h]
    0x00, DO_SIMPLE_CODE,           // Reserved         [C8h]
    0x00, DO_SIMPLE_CODE,           // Reserved         [C9h]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CAh]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CBh]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CCh]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CDh]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CEh]
    0x00, DO_SIMPLE_CODE,           // Reserved         [CFh]

    // Function key F1 ~ F12
    0   , DO_COSTOMER_FUNCTION,     // Function key F1  [D0h]
    1   , DO_COSTOMER_FUNCTION,     // Function key F2  [D1h]
    2   , DO_COSTOMER_FUNCTION,     // Function key F3  [D2h]
    3   , DO_COSTOMER_FUNCTION,     // Function key F4  [D3h]
    4   , DO_COSTOMER_FUNCTION,     // Function key F5  [D4h]
    5   , DO_COSTOMER_FUNCTION,     // Function key F6  [D5h]
    6   , DO_COSTOMER_FUNCTION,     // Function key F7  [D6h]
    7   , DO_COSTOMER_FUNCTION,     // Function key F8  [D7h]
    8   , DO_COSTOMER_FUNCTION,     // Function key F9  [D8h]
    9   , DO_COSTOMER_FUNCTION,     // Function key F10 [D9h]
    10  , DO_COSTOMER_FUNCTION,     // Function key F11 [DAh]
    11  , DO_COSTOMER_FUNCTION,     // Function key F12 [DBh]
    12  , DO_COSTOMER_FUNCTION,     // Function key Esc [DCh]
    13  , DO_COSTOMER_FUNCTION,     // Function key Up arrow    [DDh]
    14  , DO_COSTOMER_FUNCTION,     // Function key Down arrow  [DEh]
    15  , DO_COSTOMER_FUNCTION,     // Function key Left arrow  [DFh]
    16  , DO_COSTOMER_FUNCTION,     // Function key Right arrow [E0h]
    17  , DO_COSTOMER_FUNCTION,     // Function key Space   [E1h]
#if SUPPORT_OOB_CRASHLOG_KEY
    18  , DO_COSTOMER_FUNCTION,     // Function key C       [E2h]
    19  , DO_COSTOMER_FUNCTION,     // Function key L       [E3h]
#endif
};

// Reserved 0xE0 ~ 0xFF

//----------------------------------------------------------------------------
// table_entry : value of keyboard matrix table. for example Rc_ROM_Tables[]
// event : key MAKE_EVENT or BREAK_EVENT or REPEAT_EVENT
//----------------------------------------------------------------------------
void OEM_Hook_Send_Key(BYTE table_entry, BYTE event)
{

}

//----------------------------------------------------------------------------
// Return : 0xFF --> Send_Key function will be break; (no any scan code to host)
//----------------------------------------------------------------------------
BYTE OEM_Hook_Skip_Send_Key(void)
{
    return(0x00);
}

//-----------------------------------------------------------------------------
// Keyboard hook function (KSO0 - KSO15)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{

}

//-----------------------------------------------------------------------------
// Keyboard hook function (KSO16 - KSO17 and GPIO KSO)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{

}

/* ---------------------------------------------------------------------------
 * FUNCTION: Hook_Setup_Scanner_Pntr - to define the possible scanner tables
 *
 *     0   Rc_RAM_Table
 *     1   ROM Table 1
 *     ...
 * ------------------------------------------------------------------------ */
void Hook_Setup_Scanner_Pntr(void)
{
    Scanner_Table_Pntr = &ADL_P_Rc_ROM_Tables;
    Extendkey_Table_Pntr = &EtKey_ROM_Tables;
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to high
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinH(void)
{

}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to low
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinL(void)
{

}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin output
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinCtrl(void)
{

}

//-----------------------------------------------------------------------------
// Fn key make
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Make(void)
{

}

//-----------------------------------------------------------------------------
// Fn key break
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Break(void)
{

}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit6
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT6(void)
{
    return(0x00);
}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit7
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT7(void)
{
    return(0x00);
}

//-----------------------------------------------------------------------------
// Hook Scan Key activity
//-----------------------------------------------------------------------------
void Hook_scan_activity(void)
{
    AnyKeyDownFlag = 1;
    Key_BackLight_On();
}

//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * End of OEM_SCANTABS.C */