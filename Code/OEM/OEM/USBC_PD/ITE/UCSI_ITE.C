/*-----------------------------------------------------------------------------
 * @file     | UCSI_ITE.C
 *-----------+-----------------------------------------------------------------
 * @function | USB Type-C Connector System Software Interface [UCSI] - ITE
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
#define SUPPORT_UCSI_MODULE             TRUE   /* TRUE:Enable this module code */
#define DEBUG_UCSI_PPM_STEP             FALSE
#define SUPPORT_PPM_CHARGING_STATUS     TRUE
#define SUPPORT_SLOW_CHARGE             FALSE /* Co-Work with Bios */

#if SUPPORT_UCSI_MODULE
/*-----------------------------------------------------------------------------
 * Resources & I2C Address & Interrupt pins define
 *---------------------------------------------------------------------------*/
/* Please use common Resources sizes >= 18 */
#define UcsiI2cReadBuf          SPIBuffer2
//#define IF_PD_INTR_ACTIVE()     IF_PD1_INTR_ACTIVE()
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_UCSI_PPM_STEP
#define PPM_STEP_RamDebug(x)    RamDebug(x)
#else
#define PPM_STEP_RamDebug(x)    {}
#endif

//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Ucsi_send_sci_event
 * @function - PD ucsi send SCI event to OPM
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ucsi_send_sci_event(void)
{
    WriteSCI_Buffer(_SCIEVT_USBTC);
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - ECi2cPd1CmdRead
 * @function - PD ucsi command read function.
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE ECi2cPd1CmdRead(BYTE PdCmd, XBYTE *DataPointer, BYTE RdLen)
{
    BYTE    UcsiI2cWriteBuf[2];

    UcsiI2cWriteBuf[0] = PdCmd;
    if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           1,
                           0,
                           DataPointer,
                           RdLen))
    {
        return TRUE;
    }
    xUCSI_i2c_fail++;
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ECi2cPd1CmdWrite
 * @function - PD ucsi command write function.
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE ECi2cPd1CmdWrite(BYTE PdCmd, XBYTE *DataPointer, BYTE WrLen)
{
    BYTE    i;
    BYTE    UcsiI2cWriteBuf[18];

    UcsiI2cWriteBuf[0] = PdCmd;
    for (i = 1; i < (WrLen + 1); i++)
    {
        UcsiI2cWriteBuf[i] = *DataPointer;
        DataPointer++;
    }
    if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           (WrLen + 1),
                           0,
                           DataPointer,
                           0))
    {
        return TRUE;
    }
    xUCSI_i2c_fail++;
    return FALSE;
}

#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - ECi2cPd2CmdRead
 * @function - PD ucsi command read function.
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE ECi2cPd2CmdRead(BYTE PdCmd, XBYTE *DataPointer, BYTE RdLen)
{
    BYTE    UcsiI2cWriteBuf[2];

    UcsiI2cWriteBuf[0] = PdCmd;
    if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           1,
                           0,
                           DataPointer,
                           RdLen))
    {
        return TRUE;
    }
    xUCSI_i2c_fail++;
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ECi2cPd2CmdWrite
 * @function - PD ucsi command write function.
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE ECi2cPd2CmdWrite(BYTE PdCmd, XBYTE *DataPointer, BYTE WrLen)
{
    BYTE    i;
    BYTE    UcsiI2cWriteBuf[18];

    UcsiI2cWriteBuf[0] = PdCmd;
    for (i = 1; i < (WrLen + 1); i++)
    {
        UcsiI2cWriteBuf[i] = *DataPointer;
        DataPointer++;
    }
    if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           (WrLen + 1),
                           0,
                           DataPointer,
                           0))
    {
        return TRUE;
    }
    xUCSI_i2c_fail++;
    return FALSE;
}

#endif // SUPPORT_PD_PORT2_ITE

#if SUPPORT_UCSI_MODULE
/*-----------------------------------------------------------------------------
 * @subroutine - clear_pd1_ucsi_event
 * @function - clear PD1 chip event function.
 * @Upstream - service_ucsi
 * @input    - None
 * @return   - xUCSI_init
 * @note     - None
 */
void clear_pd1_ucsi_event(void)
{
    /* Clear UCSI interrupt */
    UcsiI2cReadBuf[0] = 0x02;
    ECi2cPd1CmdWrite(_ITEPD_SET_ALERT_CLR,
                    &UcsiI2cReadBuf[0],
                    1);
}

/*-----------------------------------------------------------------------------
 * @subroutine - clear_pd2_ucsi_event
 * @function - clear PD2 chip event function.
 * @Upstream - service_ucsi
 * @input    - None
 * @return   - xUCSI_init
 * @note     - None
 */
void clear_pd2_ucsi_event(void)
{
    /* Clear UCSI interrupt */
    UcsiI2cReadBuf[0] = 0x02;
    ECi2cPd2CmdWrite(_ITEPD_SET_ALERT_CLR,
                    &UcsiI2cReadBuf[0],
                    1);
}

/*-----------------------------------------------------------------------------
 * @subroutine - service_ucsi_init
 * @function - Initial PD ucsi function.
 * @Upstream - service_ucsi
 * @input    - None
 * @return   - xUCSI_init
 * @note     - None
 */
BYTE service_ucsi_init(void)
{
    if (ECi2cPd1CmdRead(_ITEPD_UCSI_VERSION,
                       &xUCSI_DS_VERSION[0],
                       2))
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ucsi_merge_local_ec_data
 * @function - Ucsi Merge Local EC Data
 * @Upstream - service_ucsi
 * @input    - xUCSI_COMMAND
 * @return   - By Command changed MGI packets.
 * @note     - None
 */
void ucsi_merge_local_ec_data(void)
{
    if (xUCSI_COMMAND == UCSI_CMD_GET_CONNECTOR_STATUS)
    {
#if SUPPORT_PPM_CHARGING_STATUS
#if SUPPORT_SLOW_CHARGE
        /* Update Battery Charging Status */
        xUCSI_DS_MGI[8] &= 0xFC;    /* Clear Battery Charging Status */
        if ((xPD1_pd_PowWatt >= 45) || (xPD2_pd_PowWatt >= 45))
        {
            xUCSI_DS_MGI[8] |= _Normal_Charging;
        }
        else if ((xPD1_pd_PowWatt >= 27) || (xPD2_pd_PowWatt >= 27))
        {
            xUCSI_DS_MGI[8] |= _Slow_Charging;
        }
        else if ((xPD1_pd_PowWatt >= 15) || (xPD2_pd_PowWatt >= 15))
        {
            xUCSI_DS_MGI[8] |=  _Very_Slow_Charging;
        }
        else
        {
            xUCSI_DS_MGI[1] |= 0x40;    // Connect Change
            xUCSI_DS_MGI[8] |= _Not_Charging;
        }

#else
        /* Update Battery Charging Status */
        xUCSI_DS_MGI[8] &= 0xFC;    /* Clear Battery Charging Status */
        if (1)  //TODO: ODM Charging Status
        {
            xUCSI_DS_MGI[8] |= _Normal_Charging;
        }
        else
        {
            xUCSI_DS_MGI[8] |= _Not_Charging;
        }
#endif
#endif
        return;
    }
    if (xUCSI_COMMAND == UCSI_CMD_GET_CONNECTOR_CAPABILITY)
    {
		// For "USB Type-C UCM Data Role Swap" test case
        xUCSI_DS_MGI[0] = F_Supports_DFP_Only + F_Supports_USB_2 + F_Supports_Alternate_Mode;
        return;
    }
}
/*-----------------------------------------------------------------------------
 * @subroutine - ucsi_mgi_cci_clear
 * @function - Ucsi Merge Local EC Data
 * @Upstream - service_ucsi
 * @input    - xUCSI_COMMAND
 * @return   - Clear MGI CCI packets.
 * @note     - None
 */
void ucsi_mgi_cci_clear(void)
{
    BYTE i;
    
    for(i = 0; i < 16; i++)
    {
        xUCSI_DS_MGI[i] = 0;
    }
    xUCSI_DS_CCI0 = 0x00;
    xUCSI_DS_CCI1 = 0x00;
    xUCSI_DS_CCI2 = 0x00;
    xUCSI_DS_CCI3 = 0x00;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ucsi_mgi_control
 * @function - Ucsi Merge Local EC Data
 * @Upstream - service_ucsi
 * @input    - xUCSI_COMMAND
 * @return   - By Command changed MGI packets.
 * @note     - None
 */
void ucsi_mgi_control(void)
{
    BYTE i;
    
    if ((xUCSI1_DS_MGI[1] != 0x00) || (xUCSI1_DS_MGI[2] != 0x00))
    {
        for(i = 0; i < 16; i++)
        {
            xUCSI_DS_MGI[i] = xUCSI1_DS_MGI[i];
        }
    }
    else if ((xUCSI2_DS_MGI[1] != 0x00) || (xUCSI2_DS_MGI[2] != 0x00))
    {
        for(i = 0; i < 16; i++)
        {
            xUCSI_DS_MGI[i] = xUCSI2_DS_MGI[i];
        }
    }
    else
    {
        for(i = 0; i < 16; i++)
        {
            xUCSI_DS_MGI[i] = 0;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - ucsi_cci_control
 * @function - Ucsi Merge Local EC Data
 * @Upstream - service_ucsi
 * @input    - xUCSI_COMMAND
 * @return   - By Command changed CCI packets.
 * @note     - None
 */
void ucsi_cci_control(void)
{
    if ((xUCSI1_DS_CCI0 != 0x00) || (xUCSI1_DS_CCI1 != 0x00))
    {
        xUCSI_DS_CCI0 = xUCSI1_DS_CCI0;
        xUCSI_DS_CCI1 = xUCSI1_DS_CCI1;
        xUCSI_DS_CCI2 = xUCSI1_DS_CCI2;
        xUCSI_DS_CCI3 = xUCSI1_DS_CCI3;
    }
    else if ((xUCSI2_DS_CCI0 != 0x00) || (xUCSI2_DS_CCI1 != 0x00))
    {
        xUCSI_DS_CCI0 = xUCSI2_DS_CCI0;
        xUCSI_DS_CCI1 = xUCSI2_DS_CCI1;
        xUCSI_DS_CCI2 = xUCSI2_DS_CCI2;
        xUCSI_DS_CCI3 = xUCSI2_DS_CCI3;
    }
    else
    {
        if ((xUCSI1_DS_CCI3 != 0x00) && (xUCSI1_DS_CCI3 != 0xC0))
        {
            xUCSI_DS_CCI0 = xUCSI1_DS_CCI0;
            xUCSI_DS_CCI1 = xUCSI1_DS_CCI1;
            xUCSI_DS_CCI2 = xUCSI1_DS_CCI2;
            xUCSI_DS_CCI3 = xUCSI1_DS_CCI3;
        }
        else if ((xUCSI2_DS_CCI3 != 0x00) && (xUCSI2_DS_CCI3 != 0xC0))
        {
            xUCSI_DS_CCI0 = xUCSI2_DS_CCI0;
            xUCSI_DS_CCI1 = xUCSI2_DS_CCI1;
            xUCSI_DS_CCI2 = xUCSI2_DS_CCI2;
            xUCSI_DS_CCI3 = xUCSI2_DS_CCI3;
        }
        else if ((xUCSI1_DS_CCI3 == 0xC0) && (xUCSI2_DS_CCI3 == 0xC0))
        {
            xUCSI_DS_CCI0 = xUCSI1_DS_CCI0;
            xUCSI_DS_CCI1 = xUCSI1_DS_CCI1;
            xUCSI_DS_CCI2 = xUCSI1_DS_CCI2;
            xUCSI_DS_CCI3 = xUCSI1_DS_CCI3;
        }
        else
        {
            xUCSI_DS_CCI0 = 0x00;
            xUCSI_DS_CCI1 = 0x00;
            xUCSI_DS_CCI2 = 0x00;
            xUCSI_DS_CCI3 = 0x00;
        }
    }
}
/*-----------------------------------------------------------------------------
 * @subroutine - service_ucsi
 * @function - service & handle ucsi - ITE PD
 * @Upstream - Hook_Timer5msEvent
 * @input    - xUCSI_opm_cmd_ready
 * @return   -
 * @note     - None
 */
void service_ucsi(void)
{
    
    if (xITEPD_FlashUtilityEnable > 0)
    {
        // Read PD version again after flashing PD FW
        xPD1_fw_init = 0;
        xPD2_fw_init = 0;
        return;
    }
            
    if (xUCSI_ppm_step == _UCSI_PPM_IDLE)
    {
        service_pd_register();
    }
    
    if (SystemNotS0)
    {
        xUCSI_init = 0;
        return;
    }
    
    /* Initial UCSI */
    if (xUCSI_init == 0)
    {
        if (service_ucsi_init())
        {
            xUCSI_init = 1;
        }
        return;
    }
    if (wUCSI_task_running > 0)
    {
        wUCSI_task_running--;
        /* Check task timeout */
        if (wUCSI_task_running == 0)
        {
            xUCSI_ppm_step = _UCSI_PPM_IDLE;
        }
    }
    switch (xUCSI_ppm_step)
    {
    case _UCSI_PPM_IDLE:
        if (xUCSI_opm_cmd_ready > 0)
        {
#if 1	// For port2 
	        if((xUCSI_DS_CTL0 != 0x04) && (xUCSI_DS_CTL2 == 0x02))
	        {
	            xUCSI_DS_CTL2 = 0x01;   
	        }
#endif
            xUCSI_opm_cmd_ready = 0;            
            ucsi_mgi_cci_clear();
            xUCSI_ppm_step = _UCSI_OPM_MGO_TO_PD;
            wUCSI_task_running = 1000;  //1000 x 5ms=5sec
        }
        else if (IF_PD1_INTR_ACTIVE())  //PD Interrupt
        {
            /* Process UCSI async. event */
            xPD1_int_service |= BIT0;
            if (ECi2cPd1CmdRead(_ITEPD_GET_ALERT_REG,
                               &UcsiI2cReadBuf[0],
                               1))
            {
                //Bit3: Check if UCSI INT Status
                if (UcsiI2cReadBuf[0] & 0x02)
                {
                    /* Clear UCSI interrupt */
                    clear_pd1_ucsi_event();
                    ucsi_mgi_cci_clear();
                    xUCSI_ppm_step = _UCSI_PD_MGI_TO_OPM;
                }
            }
        }
        else if (IF_PD2_INTR_ACTIVE())  //PD Interrupt
        {
            /* Process UCSI async. event */
            xPD2_int_service |= BIT0;
            if (ECi2cPd2CmdRead(_ITEPD_GET_ALERT_REG,
                               &UcsiI2cReadBuf[0],
                               1))
            {
                //Bit3: Check if UCSI INT Status
                if (UcsiI2cReadBuf[0] & 0x02)
                {
                    /* Clear UCSI interrupt */
                    clear_pd2_ucsi_event();
                    ucsi_mgi_cci_clear();
                    xUCSI_ppm_step = _UCSI_PD_MGI_TO_OPM;
                }
            }
        }
        break;

    case _UCSI_OPM_MGO_TO_PD:
        ECi2cPd1CmdWrite(_ITEPD_UCSI_MESSAGE_OUT,
                        &xUCSI_DS_MGO[0],
                        16);
        ECi2cPd2CmdWrite(_ITEPD_UCSI_MESSAGE_OUT,
                        &xUCSI_DS_MGO[0],
                        16);
        ECi2cPd1CmdWrite(_ITEPD_UCSI_CONTROL,
                        &xUCSI_DS_CTL0,
                        8);
        ECi2cPd2CmdWrite(_ITEPD_UCSI_CONTROL,
                        &xUCSI_DS_CTL0,
                        8);
        xUCSI_ppm_step = _UCSI_WAIT_PD_INT;
        xITEPD_Check2port = 0;
        break;

    case _UCSI_WAIT_PD_INT:
#if 1   /* 0: Using polling Interupt */
            if (IF_PD1_INTR_ACTIVE())  //PD Interrupt
#endif
        {
            if (ECi2cPd1CmdRead(_ITEPD_GET_ALERT_REG,
                               &UcsiI2cReadBuf[0],
                               1))
            {
                //Bit3: Check if UCSI Int Status
                if (UcsiI2cReadBuf[0] & 0x02)
                {
                    SET_MASK(xITEPD_Check2port, F_PD_PORT1);
                }
            }
        }
#if 1   /* 0: Using polling Interupt */
            if (IF_PD2_INTR_ACTIVE())  //PD Interrupt
#endif
        {
            if (ECi2cPd2CmdRead(_ITEPD_GET_ALERT_REG,
                               &UcsiI2cReadBuf[0],
                               1))
            {
                //Bit3: Check if UCSI Int Status
                if (UcsiI2cReadBuf[0] & 0x02)
                {
                    SET_MASK(xITEPD_Check2port, F_PD_PORT2);
                }
            }
        }
        
        if( IS_MASK_SET(xITEPD_Check2port, F_PD_PORT1) && 
            IS_MASK_SET(xITEPD_Check2port, F_PD_PORT2))
        {
            xITEPD_Check2port = 0;
            xUCSI_ppm_step = _UCSI_READ_PD_MGI;
            return;
        }
        break;

    case _UCSI_READ_PD_MGI:
    	ECi2cPd1CmdRead(_ITEPD_UCSI_MESSAGE_IN,
        				&xUCSI1_DS_MGI[0],
                        16);
    	ECi2cPd1CmdRead(_ITEPD_UCSI_STATUS,
        				&xUCSI1_DS_CCI0,
                		4);
        ECi2cPd2CmdRead(_ITEPD_UCSI_MESSAGE_IN,
        				&xUCSI2_DS_MGI[0],
        				16);
            
        ECi2cPd2CmdRead(_ITEPD_UCSI_STATUS,
        				&xUCSI2_DS_CCI0,
                		4);

        ucsi_mgi_control();
        ucsi_cci_control();
        xUCSI_ppm_step = _UCSI_NOTIFY_EVENT;
        break;

    case _UCSI_NOTIFY_EVENT:
        ucsi_merge_local_ec_data();
        /* Clear UCSI interrupt */
        clear_pd1_ucsi_event();
        clear_pd2_ucsi_event();
        ucsi_send_sci_event();
        wUCSI_task_running = 0;
        xUCSI_ppm_step = _UCSI_PPM_IDLE;
        break;

    case _UCSI_PD_MGI_TO_OPM:
        ECi2cPd1CmdRead(_ITEPD_UCSI_MESSAGE_IN,
                       &xUCSI1_DS_MGI[0],
                       16);
        ECi2cPd2CmdRead(_ITEPD_UCSI_MESSAGE_IN,
                       &xUCSI2_DS_MGI[0],
                       16);
        ucsi_mgi_control();
        xUCSI_ppm_step = _UCSI_PD_CCI_TO_OPM;
        break;

    case _UCSI_PD_CCI_TO_OPM:
        ECi2cPd1CmdRead(_ITEPD_UCSI_STATUS,
                       &xUCSI1_DS_CCI0,
                       4);
        ECi2cPd2CmdRead(_ITEPD_UCSI_STATUS,
                       &xUCSI2_DS_CCI0,
                       4);
        ucsi_cci_control();
        xUCSI_ppm_step = _UCSI_NOTIFY_EVENT;
        break;

    default:
        wUCSI_task_running = 0;
        xUCSI_ppm_step = _UCSI_PPM_IDLE;
        break;
    }
}
//-----------------------------------------------------------------------------
#else
void service_ucsi(void)
{
    if (xITEPD_FlashUtilityEnable > 0)
    {
        return;
    }
    
    service_pd_register();
}
#endif //SUPPORT_UCSI_MODULE
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of UCSI_ITE.C */
