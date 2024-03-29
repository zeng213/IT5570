/*-----------------------------------------------------------------------------
 * @file     | PD_OEM_ITE.C
 *-----------+-----------------------------------------------------------------
 * @function | USB Type-C PD Chip OEM/ODM function
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
/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/



//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - clear_pd1_chip_event
 * @function - clear PD1 chip event function.
 * @Upstream - service_ucsi
 * @input    - None
 * @return   - xUCSI_init
 * @note     - None
 */
void clear_pd1_chip_event(BYTE ClrEvt)
{
    BYTE    TempI2cWriteBuf[2];

    /* Clear PD interrupt */
    TempI2cWriteBuf[0] = ClrEvt;
    ECi2cPd1CmdWrite(_ITEPD_SET_ALERT_CLR,
                    &TempI2cWriteBuf[0],
                    1);
}

#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - clear_pd2_chip_event
 * @function - clear PD2 chip event function.
 * @Upstream - service_ucsi
 * @input    - None
 * @return   - xUCSI_init
 * @note     - None
 */
void clear_pd2_chip_event(BYTE ClrEvt)
{
    BYTE    TempI2cWriteBuf[2];

    /* Clear PD interrupt */
    TempI2cWriteBuf[0] = ClrEvt;
    ECi2cPd2CmdWrite(_ITEPD_SET_ALERT_CLR,
                    &TempI2cWriteBuf[0],
                    1);
}
#endif  // SUPPORT_PD_PORT2_ITE

/*-----------------------------------------------------------------------------
 * @subroutine - SendSystemStatusToPD1
 * @function - SendSystemStatusToPD1
 * @Upstream - By call
 * @input    - 0x01: _SYSTEM_S0
 *             0x03: _SYSTEM_S3
 *             0x04: _SYSTEM_S4
 *             0x05: _SYSTEM_S5
 * @return   - None
 * @note     - None
 */
void SendSystemStatusToPD1(BYTE SysStatus)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    if(SysStatus ==_SYSTEM_S0)
    {
        UcsiI2cWriteBuf[0] = 0xD8;
        UcsiI2cWriteBuf[1] = 0x00;
        EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
    }
    if(SysStatus ==_SYSTEM_S5)
    {
        UcsiI2cWriteBuf[0] = 0xD8;
        UcsiI2cWriteBuf[1] = 0x01;
        EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
        UcsiI2cWriteBuf[0] = 0xE5;
        UcsiI2cWriteBuf[1] = 0x00;
        EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - SendSystemACPIToPD1
 * @function - SendSystemACPIToPD1
 * @Upstream - By call
 * @input    - 0x01: _SYSTEM_S0
 *             0x03: _SYSTEM_S3
 *             0x04: _SYSTEM_S4
 *             0x05: _SYSTEM_S5
 * @return   - None
 * @note     - None
 */
void SendSystemACPIToPD1(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xE5;
    UcsiI2cWriteBuf[1] = 0x01;
    EC_PD1_WrToRdStream(xPD1_i2c_addr,
                        &UcsiI2cWriteBuf[0],
                        2,
                        0,
                        &TempI2cReadBuf,
                        0);
}
#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - SendSystemStatusToPD2
 * @function - SendSystemStatusToPD2
 * @Upstream - By call
 * @input    - 0x01: _SYSTEM_S0
 *             0x03: _SYSTEM_S3
 *             0x04: _SYSTEM_S4
 *             0x05: _SYSTEM_S5
 * @return   - None
 * @note     - None
 */
void SendSystemStatusToPD2(BYTE SysStatus)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    if(SysStatus ==_SYSTEM_S0)
    {
        UcsiI2cWriteBuf[0] = 0xD8;
        UcsiI2cWriteBuf[1] = 0x00;
        EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
    }
    if(SysStatus ==_SYSTEM_S5)
    {
        UcsiI2cWriteBuf[0] = 0xD8;
        UcsiI2cWriteBuf[1] = 0x01;
        EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
        UcsiI2cWriteBuf[0] = 0xE5;
        UcsiI2cWriteBuf[1] = 0x00;
        EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           2,
                           0,
                           &TempI2cReadBuf,
                           0);
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - SendSystemACPIToPD2
 * @function - SendSystemACPIToPD2
 * @Upstream - By call
 * @input    - 0x01: _SYSTEM_S0
 *             0x03: _SYSTEM_S3
 *             0x04: _SYSTEM_S4
 *             0x05: _SYSTEM_S5
 * @return   - None
 * @note     - None
 */
void SendSystemACPIToPD2(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xE5;
    UcsiI2cWriteBuf[1] = 0x01;
    EC_PD2_WrToRdStream(xPD2_i2c_addr,
                        &UcsiI2cWriteBuf[0],
                        2,
                        0,
                        &TempI2cReadBuf,
                        0);
}
#endif // #if SUPPORT_PD_PORT2_ITE


/*-----------------------------------------------------------------------------
 * @subroutine - SinkSwitchControlPD1
 * @function - SinkSwitchControlPD1
 * @Upstream - By call
 * @input    - 
 * @return   - None
 * @note     - None
 */
void SinkSwitchControlPD1(BYTE Onoff)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xE6;
    if ( EC_PD1_WrToRdStream(xPD1_i2c_addr,
                        &UcsiI2cWriteBuf[0],
                        1,
                        0,
                        &TempI2cReadBuf,
                        1))
    {
        if(Onoff == SINK_CONTROL_ON)
        {   // On
            if((TempI2cReadBuf[0] & 0x10) == 0x00)    
            {
                UcsiI2cWriteBuf[0] = 0xE6;
                UcsiI2cWriteBuf[1] = TempI2cReadBuf[0] | 0x10; // bit4 on: 0x10
                EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                    &UcsiI2cWriteBuf[0],
                                    2,
                                    0,
                                    &TempI2cReadBuf,
                                    0);
            }
            else
            {
                // Do nothing
            }
        }
        else
        {   // Off
            if((TempI2cReadBuf[0] & 0x10) == 0x10)    
            {
                UcsiI2cWriteBuf[0] = 0xE6;
                UcsiI2cWriteBuf[1] = TempI2cReadBuf[0] & ~0x10; // bit4 off: 0x00
                EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                    &UcsiI2cWriteBuf[0],
                                    2,
                                    0,
                                    &TempI2cReadBuf,
                                    0);
            }
            else
            {
                // Do nothing
            }
        }
    }
}
#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - SinkSwitchControlPD2
 * @function - SinkSwitchControlPD2
 * @Upstream - By call
 * @input    - 
 * @return   - None
 * @note     - None
 */
void SinkSwitchControlPD2(BYTE Onoff)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xE6;
    if ( EC_PD2_WrToRdStream(xPD2_i2c_addr,
                        &UcsiI2cWriteBuf[0],
                        1,
                        0,
                        &TempI2cReadBuf,
                        1))
    {
        if(Onoff == SINK_CONTROL_ON)
        {   // On
            if((TempI2cReadBuf[0] & 0x10) == 0x00)    
            {
                UcsiI2cWriteBuf[0] = 0xE6;
                UcsiI2cWriteBuf[1] = TempI2cReadBuf[0] | 0x10; // bit4 on: 0x10
                EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                    &UcsiI2cWriteBuf[0],
                                    2,
                                    0,
                                    &TempI2cReadBuf,
                                    0);
            }
            else
            {
                // Do nothing
            }
        }
        else
        {   // Off
            if((TempI2cReadBuf[0] & 0x10) == 0x10)    
            {
                UcsiI2cWriteBuf[0] = 0xE6;
                UcsiI2cWriteBuf[1] = TempI2cReadBuf[0] & ~0x10; // bit4 off: 0x00
                EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                    &UcsiI2cWriteBuf[0],
                                    2,
                                    0,
                                    &TempI2cReadBuf,
                                    0);
            }
            else
            {
                // Do nothing
            }
        }
    }
}
#endif // #if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - GetPD1adapterWatt
 * @function - GetPD1adapterWatt
 * @Upstream - By call
 * @input    -
 * @return   - None
 * @note     - None
 */
BYTE GetPD1adapterWatt(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xD8;
    EC_PD1_WrToRdStream(xPD1_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       2,
                       0,
                       &TempI2cReadBuf[0],
                       1);
    return TempI2cReadBuf[0];
}

#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - GetPD2adapterWatt
 * @function - GetPD2adapterWatt
 * @Upstream - By call
 * @input    -
 * @return   - None
 * @note     - None
 */
BYTE GetPD2adapterWatt(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xD8;
    EC_PD2_WrToRdStream(xPD2_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       2,
                       0,
                       &TempI2cReadBuf[0],
                       1);
    return TempI2cReadBuf[0];
}
#endif // #if SUPPORT_PD_PORT2_ITE

/*-----------------------------------------------------------------------------
 * @subroutine - GetPD1adapterVoltAmpWatt
 * @function - GetPD1adapterVoltAmpWatt
 * @Upstream - By call
 * @input    -
 * @return   - None
 * @note     - None
 */
void GetPD1adapterVoltAmpWatt(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[4];
    
    UcsiI2cWriteBuf[0] = 0xBD;
    if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           1,
                           0,
                           &TempI2cReadBuf[0],
                           1))
    {
        if((TempI2cReadBuf[0] & 0x01) == 0x01)    
        {
            UcsiI2cWriteBuf[0] = 0xB0;
            if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                   &UcsiI2cWriteBuf[0],
                                   1,
                                   0,
                                   &TempI2cReadBuf[0],
                                   1))
            {
                if((TempI2cReadBuf[0] & 0x13) == 0x03)    
                {
                    UcsiI2cWriteBuf[0] = 0xDE;
                    if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                           &UcsiI2cWriteBuf[0],
                                           1,
                                           0,
                                           &TempI2cReadBuf[0],
                                           2))
                    {
                        xPD1_pd_mVoltage = ((WORD)(TempI2cReadBuf[0]<<8) + (WORD)TempI2cReadBuf[1]);
                        xPD1_pd_Voltage = (BYTE)(xPD1_pd_mVoltage / 1000);
                    }
                    
                    UcsiI2cWriteBuf[0] = 0xDA;
                    if (EC_PD1_WrToRdStream(xPD1_i2c_addr,
                                           &UcsiI2cWriteBuf[0],
                                           1,
                                           0,
                                           &TempI2cReadBuf[0],
                                           2))
                    {
                        xPD1_pd_mCurrent = ((WORD)(TempI2cReadBuf[0]<<8) + (WORD)TempI2cReadBuf[1]);
                        xPD1_pd_Current = (BYTE)(xPD1_pd_mCurrent / 1000);
                    }
                    xPD1_pd_PowWatt =   ((xPD1_pd_mVoltage / 1000) *
                                        (xPD1_pd_mCurrent / 10)) / 100;
                }
                else// if((TempI2cReadBuf[0] & 0x01) == 0x00)   
                {
                    xPD1_pd_mVoltage    = 0;
                    xPD1_pd_Voltage     = 0;
                    xPD1_pd_mCurrent    = 0;
                    xPD1_pd_Current     = 0;
//                    xPD1_pd_mWatt       = 0;
                    xPD1_pd_PowWatt     = 0;
                }
            }
            else
            {
                xPD1_i2c_error++;
                xPD1_pd_mVoltage    = 0;
                xPD1_pd_Voltage     = 0;
                xPD1_pd_mCurrent    = 0;
                xPD1_pd_Current     = 0;
//                xPD1_pd_mWatt       = 0;
                xPD1_pd_PowWatt     = 0;
            }
            clear_pd1_chip_event(0x01);
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - GetPD1Version
 * @function - GetPD1Version
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE GetPD1Version(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    Retry;

    Retry = 3;
    while (Retry > 0)
    {
        xPD1_i2c_addr = _ITE_PD1_I2C_ADDR;
        UpdI2cWriteBuf[0] = _ITEPD_GET_PD_FW_VER;
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
        Retry--;
    }
    return FALSE;
}
#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - GetPD2Version
 * @function - GetPD2Version
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     -
 */
BYTE GetPD2Version(void)
{
    BYTE    UpdI2cWriteBuf[5];
    BYTE    Retry;

    Retry = 3;
    while (Retry > 0)
    {
        xPD2_i2c_addr = _ITE_PD2_I2C_ADDR;
        UpdI2cWriteBuf[0] = _ITEPD_GET_PD_FW_VER;
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
        Retry--;
    }
    return FALSE;
}
#endif // #if SUPPORT_PD_PORT2_ITE

#if SUPPORT_PD_PORT2_ITE
/*-----------------------------------------------------------------------------
 * @subroutine - GetPD2adapterVoltAmpWatt
 * @function - GetPD2adapterVoltAmpWatt
 * @Upstream - By call
 * @input    -
 * @return   - None
 * @note     - None
 */
void GetPD2adapterVoltAmpWatt(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[4];
    
    UcsiI2cWriteBuf[0] = 0xBD;
    if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                           &UcsiI2cWriteBuf[0],
                           1,
                           0,
                           &TempI2cReadBuf[0],
                           1))
    {
        if((TempI2cReadBuf[0] & 0x01) == 0x01)    
        {
            UcsiI2cWriteBuf[0] = 0xB0;
            if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                   &UcsiI2cWriteBuf[0],
                                   1,
                                   0,
                                   &TempI2cReadBuf[0],
                                   1))
            {
                if((TempI2cReadBuf[0] & 0x13) == 0x03)    
                {
                    UcsiI2cWriteBuf[0] = 0xDE;
                    if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                           &UcsiI2cWriteBuf[0],
                                           1,
                                           0,
                                           &TempI2cReadBuf[0],
                                           2))
                    {
                        xPD2_pd_mVoltage = ((WORD)(TempI2cReadBuf[0]<<8) + (WORD)TempI2cReadBuf[1]);
                        xPD2_pd_Voltage = (BYTE)(xPD2_pd_mVoltage / 1000);
                    }
                    
                    UcsiI2cWriteBuf[0] = 0xDA;
                    if (EC_PD2_WrToRdStream(xPD2_i2c_addr,
                                           &UcsiI2cWriteBuf[0],
                                           1,
                                           0,
                                           &TempI2cReadBuf[0],
                                           2))
                    {
                        xPD2_pd_mCurrent = (WORD)((DWORD)(TempI2cReadBuf[0]<<8) + (WORD)TempI2cReadBuf[1]);
                        xPD2_pd_Current = (BYTE)(xPD2_pd_mCurrent / 1000);
                    }
                    xPD2_pd_PowWatt =   ((xPD2_pd_mVoltage / 1000) *
                                        (xPD2_pd_mCurrent / 10)) / 100;
                }
                else// if((TempI2cReadBuf[0] & 0x01) == 0x00)   
                {
                    xPD2_pd_mVoltage    = 0;
                    xPD2_pd_Voltage     = 0;
                    xPD2_pd_mCurrent    = 0;
                    xPD2_pd_Current     = 0;
//                    xPD2_pd_mWatt       = 0;
                    xPD2_pd_PowWatt     = 0;
                }
            }
            else
            {
                xPD2_i2c_error++;
                xPD2_pd_mVoltage    = 0;
                xPD2_pd_Voltage     = 0;
                xPD2_pd_mCurrent    = 0;
                xPD2_pd_Current     = 0;
//                xPD2_pd_mWatt       = 0;
                xPD2_pd_PowWatt     = 0;
            }          
            clear_pd2_chip_event(0x01);
        }
    }

}
#endif  // SUPPORT_PD_PORT2_ITE

BYTE EnterPD1ComplianceMode(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xEB;
    EC_PD1_WrToRdStream(xPD1_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       1,
                       0,
                       &TempI2cReadBuf[0],
                       1);
    return TempI2cReadBuf[0];

}
//-----------------------------------------------------------------------------
#if SUPPORT_PD_PORT2_ITE
BYTE EnterPD2ComplianceMode(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];
    
    UcsiI2cWriteBuf[0] = 0xEB;
    EC_PD1_WrToRdStream(xPD2_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       1,
                       0,
                       &TempI2cReadBuf[0],
                       1);
    return TempI2cReadBuf[0];
}
#endif
//-----------------------------------------------------------------------------
/* Tiger Lake UP3/UP4 Retimer Capsule Enabling Guide (Doc#631742)
*/
//-----------------------------------------------------------------------------
void EnterRetimerFwUpdate(void)
{
    BYTE    UcsiI2cWriteBuf[2];
    BYTE    TempI2cReadBuf[2];

    UcsiI2cWriteBuf[0] = 0xEA;
    EC_PD1_WrToRdStream(xPD1_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       1,
                       0,
                       &TempI2cReadBuf[0],
                       1);

#if SUPPORT_PD_PORT2_ITE
    UcsiI2cWriteBuf[0] = 0xEA;
    EC_PD1_WrToRdStream(xPD2_i2c_addr,
                       &UcsiI2cWriteBuf[0],
                       1,
                       0,
                       &TempI2cReadBuf[0],
                       1);
#endif
}
//-----------------------------------------------------------------------------
void ExitRetimerFwUpdate(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - service_pd_register
 * @function - service_pd_register
 * @Upstream - By call
 * @input    - xPD1_int_service
 * @return   - None
 * @note     - None
 */
void service_pd_register(void)
{
    if (SystemIsS0)
    {
        if(xPD1_fw_init == 0xFF)
        {   // Retry to read PD1 version in S0
            xPD1_fw_init = 0;
        }
#if SUPPORT_PD_PORT2_ITE
        if(xPD2_fw_init == 0xFF)
        {   // Retry to read PD2 version in S0
            xPD2_fw_init = 0;
        }
#endif

        if (xITEPD_SetCtrl & BIT0)
        {
            CLEAR_MASK(xITEPD_SetCtrl, BIT0);
            EnterPD1ComplianceMode();
        }
        if (xITEPD_SetCtrl & BIT1)
        {
            CLEAR_MASK(xITEPD_SetCtrl, BIT1);
            EnterPD2ComplianceMode();
        }
    }
    /* Read PD FW Version */
    if (xPD1_fw_init == 0)
    {
        if (GetPD1Version())
        {
            xPD1_fw_init = 1;
        }
        else
        {
            xPD1_fw_init = 0xFF;
        }
    }
    
#if SUPPORT_PD_PORT2_ITE
    if (xPD2_fw_init == 0)
    {
        if (GetPD2Version())
        {
            xPD2_fw_init = 1;
        }
        else
        {
            xPD2_fw_init = 0xFF;
        }
    }
#endif

    if (IF_PD1_INTR_ACTIVE())  //PD1 Interrupt
    {
        GetPD1adapterVoltAmpWatt();
        return;
    }
    
#if SUPPORT_PD_PORT2_ITE
    if (IF_PD2_INTR_ACTIVE())  //PD1 Interrupt
    {
        GetPD2adapterVoltAmpWatt();
        return;
    }
#endif
    //TODO: ODM FUNCTION
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of PD_OEM_ITE.C */
