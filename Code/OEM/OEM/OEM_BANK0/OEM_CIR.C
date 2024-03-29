/*-----------------------------------------------------------------------------
 * @file     | OEM_CIR.C
 *-----------+-----------------------------------------------------------------
 * @function | CIR Interrupt service routine and customer feature
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_CIR               FALSE
#define DEBUG_RX_CODE           TRUE
#define _CIR_PROTOCOL           0x41    /* 0x41:NEC, 0x33:RC6 */

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#ifndef SUPPORT_SERVICE_CIR
#define SUPPORT_SERVICE_CIR     FALSE
#endif

#if DEBUG_CIR
#define CIR_RamDebug(x)         RamDebug(x)
#else
#define CIR_RamDebug(x)         {}
#endif


/*-----------------------------------------------------------------------------
 * CIR Key Table
 *---------------------------------------------------------------------------*/
#define CIR_RX_CODE_LEN     24
#define CIR_TX_CODE_LEN     24
#define CIR_RX_TIMEOUT      3
#define CIR_RX_RESET        35
#define CIR_RX_TBL_LEN      8
#define CIR_CHECK_KEY_LEN   5
#define CIR_RX_KEY_NUM      21      /* 3 x 7 = 21 Keys */
//-----------------------------------------------------------------------------

#if SUPPORT_SERVICE_CIR
//*****************************************************************************
// CIR CODE START
//*****************************************************************************
const BYTE code CIR_RX_HEADER[] =
{
    0xFF, 0xFF, 0x00, 0x11, 0x55, 0x54, 0x14, 0x55
};
//-----------------------------------------------------------------------------
const BYTE code CIR_KEY_TBL[CIR_RX_KEY_NUM][CIR_RX_TBL_LEN] =
{
    /* First byte is Key ID for OEM */
    0x72, 0x54, 0x51, 0x54, 0x11, 0x45, 0x11, 0x11, //0x00 [MUTE]
    0x71, 0x54, 0x15, 0x51, 0x11, 0x11, 0x15, 0x11, //0x01 [+]
    0x70, 0x54, 0x45, 0x54, 0x11, 0x51, 0x11, 0x11, //0x02 [POW]

    0x75, 0x14, 0x51, 0x55, 0x15, 0x11, 0x11, 0x11, //0x03 [<<]
    0x74, 0x14, 0x11, 0x55, 0x55, 0x11, 0x11, 0x11, //0x04 [SEL]
    0x73, 0x14, 0x55, 0x44, 0x15, 0x11, 0x15, 0x11, //0x05 [>>]

    0x78, 0x14, 0x51, 0x51, 0x55, 0x44, 0x11, 0x11, //0x06 [MODE]
    0x77, 0x54, 0x54, 0x54, 0x51, 0x44, 0x11, 0x11, //0x07 [-]
    0x76, 0x14, 0x11, 0x51, 0x55, 0x15, 0x11, 0x11, //0x08 [APS]

    0x01, 0x14, 0x55, 0x55, 0x11, 0x11, 0x11, 0x11, //0x09 [1]
    0x02, 0x14, 0x51, 0x54, 0x55, 0x14, 0x11, 0x11, //0x0A [2]
    0x03, 0x54, 0x54, 0x55, 0x14, 0x11, 0x11, 0x11, //0x0B [3]

    0x04, 0x54, 0x55, 0x51, 0x44, 0x44, 0x44, 0x11, //0x0C [4]
    0x05, 0x14, 0x55, 0x51, 0x45, 0x44, 0x14, 0x11, //0x0D [5]
    0x06, 0x54, 0x54, 0x44, 0x45, 0x11, 0x15, 0x11, //0x0E [6]

    0x07, 0x14, 0x51, 0x45, 0x55, 0x44, 0x14, 0x11, //0x0F [7]
    0x08, 0x54, 0x51, 0x51, 0x11, 0x45, 0x14, 0x11, //0x10 [8]
    0x09, 0x14, 0x45, 0x45, 0x15, 0x45, 0x14, 0x11, //0x11 [9]

    0x79, 0x14, 0x51, 0x11, 0x55, 0x11, 0x15, 0x11, //0x12 [CLK]
    0x10, 0x14, 0x11, 0x15, 0x55, 0x45, 0x14, 0x11, //0x13 [0]
    0x7A, 0x54, 0x51, 0x44, 0x45, 0x14, 0x15, 0x11, //0x14 [BAND]
};
//-----------------------------------------------------------------------------
#define CIR_RX_HEAD_LEN     sizeof(CIR_RX_HEADER)
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - CIR_ClearFIFO
 * @function - CIR Clear FIFO
 * @Upstream - Interrupt
 * @input    - None
 * @return   - None
 * @note     - None
 */
void CIR_ClearFIFO(void)
{
    WORD    CIRWaitTimer;

    CIRWaitTimer = 3000;
    SET_MASK(C0MSTCR, CIR_FIFOCLR);
    _nop_();
    /* Wait receiver enter an inactive mode */
    while (CIRWaitTimer > 0)
    {
        if (IS_MASK_CLEAR(C0MSTCR, CIR_FIFOCLR))
        {
            break;
        }
        CIRWaitTimer--;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - CIR_ClearFIFO
 * @function - The function of confirming CIR receiver inactive mode
 * @Upstream - Interrupt
 * @input    - None
 * @return   - None
 * @note     - None
 */
void CIR_ConfirmRIM(void)
{
    WORD    CIRWaitTimer;

    SET_MASK(C0RCR, CIR_RXACT);
    _nop_();

    /* Wait receiver enter an inactive mode */
    while (CIRWaitTimer > 0)
    {
        if (IS_MASK_CLEAR(C0RCR, CIR_RXACT))
        {
            break;
        }
        CIRWaitTimer--;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_CIR
 * @function - Init CIR
 * @Upstream - Interrupt
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_CIR(void)
{
    GPCRC0 = 0x00;              // CIR RX Set GPIO to ALT function.
    SET_MASK(C0MSTCR, CIR_RESET);
    CLEAR_MASK(C0RCR, CIR_RXEN);    // RX Disable
    C0BDHR = 0x00;              // BaudRate
    C0BDLR = _CIR_PROTOCOL;
    C0MSTCR = 0x08;             // FIFO Threshold = 17 Bytes
    C0CFR = 0x0B;               // Carrier Freqency = 38KHz

    CIR_ConfirmRIM();           // Write receiver enter an inactive mode
    CIR_ClearFIFO();            // Clear FIFO

    C0IER = 0x82;               // CIR Interrupt Enable
    // CIR receive available interrupt
    SET_MASK(IELMR1, Int_CIR);  // CIR Interrupt must use Edge-Trig
    SET_MASK(IER1, Int_CIR);    // Enable INT15 CIR Interrupt
    ISR1 = Int_CIR;             // Clear INT15 pending Status
    SET_MASK(C0RCR, CIR_RXEN);  // RX enable

}

/*-----------------------------------------------------------------------------
 * @subroutine - CIR_ClearBuffer
 * @function - CIR Clear Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void CIR_ClearBuffer(void)
{
    BYTE  i;

    SET_MASK(C0MSTCR, CIR_FIFOCLR);
    SET_MASK(C0RCR, CIR_RXACT);

    //CIR_RX_DIR_LAST = CIR_RX_DIR;
    CIR_RX_DIR = 0;
    CIR_RX_Timer = 0;

#if (DEBUG_RX_CODE == 0)
    for (i = 0; i < 32; i++)
    {
        CIR_RX_BUF[i] = 0x00;
        CIR_RX_KEY[i] = 0x00;
    }
#endif

}

/*-----------------------------------------------------------------------------
 * @subroutine - Check_CIR_Timeout
 * @function - Check CIR Timeout
 * @Upstream - Hook_Timer10msEventA
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Check_CIR_Timeout(void)
{
    if (CIR_CodeTimer < 255)
    {
        CIR_CodeTimer++;
    }
    if (CIR_ResetTimer == 0xFF)
    {
        CIR_ResetTimer = 0;
        Init_CIR();
    }
    if (IS_MASK_SET(C0RCR, CIR_RXACT))
    {
        CIR_ResetTimer++;
        if (CIR_ResetTimer > 20)
        {
            CIR_ResetTimer = 0;
            Init_CIR();
        }
    }

}

/*-----------------------------------------------------------------------------
 * @subroutine - service_cir
 * @function - CIR Interrupt service routine
 * @Upstream - Interrupt
 * @input    - None
 * @return   - None
 * @note     - None
 */
void service_cir(void)
{
    BYTE    i, j;
    //-------------------------------------------------------------------------
    if (C0TFSR > 0)
    {
        return;
    }
    //-------------------------------------------------------------------------
    if ((C0RFSR & 0x1F) == 0)
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (CIR_RX_DIR < CIR_RX_CODE_LEN)
    {
        i = C0DR;
        CIR_RX_BUF[(CIR_RX_DIR & 0x1F)] = (i ^ 0xFF);
        /* Use TX For Debug */
        CIR_TX_BUF[(CIR_RX_DIR & 0x1F)] = (i ^ 0xFF);
        CIR_RX_DIR++;
        CIR_RX_Timer = 0;
        CIR_ResetTimer = 0;
        return;
    }
    //-------------------------------------------------------------------------
    CIR_KEY_CODE = 0;
#if 0   /* Reserved for Shift Trim */
    for (j = 0; j < 32; j++)
    {
        if (CIR_RX_BUF[j] == CIR_RX_HEADER[0])
        {
            break;
        }
    }
#endif
    //-------------------------------------------------------------------------
    for (i = 0; i < CIR_RX_HEAD_LEN; i++)
    {
        if (CIR_RX_HEADER[i] != CIR_RX_BUF[i])
        {
            break;
        }
    }
    //-------------------------------------------------------------------------
    if (i == CIR_RX_HEAD_LEN)
    {
        for (i = 0; i < (32 - CIR_RX_HEAD_LEN); i++)
        {
            CIR_RX_KEY[i] = CIR_RX_BUF[i + CIR_RX_HEAD_LEN];
        }
    }
    //-------------------------------------------------------------------------
    for (j = 0; j < CIR_RX_KEY_NUM; j++)
    {
        for (i = 0; i < CIR_CHECK_KEY_LEN; i++)
        {
            if (CIR_RX_KEY[i] != CIR_KEY_TBL[j][i + 1])
            {
                break;
            }
        }
        if (i == CIR_CHECK_KEY_LEN)
        {
            CIR_KEY_CODE = CIR_KEY_TBL[j][0];
            break;
        }
    }
    CIR_RX_KEY[0] = 0x00;
    //-------------------------------------------------------------------------
    if (CIR_KEY_CODE == LAST_CIR_KEY_CODE)
    {
        if (CIR_CodeTimer > 20)
        {
            CIR_KEY_CODE2 = CIR_KEY_CODE;
            CIR_CodeTimer = 0;
        }
        else
        {
            CIR_KEY_COUNT++;
            if (CIR_KEY_COUNT > 10)
            {
                CIR_KEY_CODE2 = (CIR_KEY_CODE | 0x80);
                CIR_KEY_COUNT = 0;
            }
            CIR_CodeTimer = 0;
        }
    }
    else
    {
        CIR_KEY_CODE2 = CIR_KEY_CODE;
        CIR_CodeTimer = 0;
        CIR_KEY_COUNT = 0;
        LAST_CIR_KEY_CODE = CIR_KEY_CODE;
    }
    CIR_ClearBuffer();
    CIR_ResetTimer = 0;
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
#else
void service_cir(void)
{

}
#endif  //SUPPORT_SERVICE_CIR
/*-----------------------------------------------------------------------------
 * End of OEM_CIR.C */