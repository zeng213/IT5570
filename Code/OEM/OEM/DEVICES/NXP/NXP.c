/*-----------------------------------------------------------------------------
 * @file     | NXP.C
 *-----------+-----------------------------------------------------------------
 * @function | NXP USB PD and Type-C high voltage sink/source combo switch control
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
#define DEBUG_SINK_SOURCE_SWITCH    FALSE
#define SUPPORT_NXP_I2C_CHANNEL0    TRUE
#define SUPPORT_NXP_PD_PORT2        TRUE
/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_SINK_SOURCE_SWITCH
#define UPD_PD_RamDebug(x)          RamDebug(x)
#else
#define UPD_PD_RamDebug(x)          {}
#endif
 
//*****************************************************************************
// CODE START
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - NXP_ReadREG
 * @function - NXP PD Sink/Source Switch controller read register service
 * @Upstream - By call
 * @input    - register index, data buffer, Length
 * @return   - TRUE: success
 * @note     - None
 */
BYTE NXP_ReadREG(BYTE Addr, unsigned int reg, XBYTE *buf, BYTE len)
{
    BYTE    i, retry;

    xNXP_i2c_wbuf[0] = reg;

    retry = 0;
    while (1)
    {
#if SUPPORT_NXP_I2C_CHANNEL0
        i = I2C_CH0_WrToRdStream(Addr,
                                 &xNXP_i2c_wbuf[0],
                                 1,
                                 0,
                                 &xNXP_i2c_rbuf[0],
                                 len);
#else
        i = I2C_CH1_WrToRdStream(Addr,
                                 &xNXP_i2c_wbuf[0],
                                 1,
                                 0,
                                 &xNXP_i2c_rbuf[0],
                                 len);
#endif
        if (i == FALSE)
        {
            retry++;
            if (retry > 2)
            {
                *buf = 0;
                if (Addr == _NXP_PORT1_ADDR)
                {
                    xNXP_PORT1_FailCount1++;
                }
#if SUPPORT_NXP_PD_PORT2
                if (Addr == _NXP_PORT2_ADDR)
                {
                    xNXP_PORT2_FailCount1++;
                }
#endif
                return FALSE;
            }
            else
            {
                Delay1MS(5);
            }
        }
        else
        {
            break;
        }
    }
    *buf = xNXP_i2c_rbuf[0];
//     for (i = 0; i < len; i++)
//     {
//         *buf = xNXP_i2c_rbuf[i];
//         buf++;
//     }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - NXP_WriteREG
 * @function - NXP PD Sink/Source Switch controller write register service
 * @Upstream - By call
 * @input    - register index, data buffer, Length
 * @return   - TRUE: success
 * @note     - None
 */
BYTE NXP_WriteREG(BYTE Addr, unsigned int reg, XBYTE *buf, BYTE len)
{
    BYTE    i;

    xNXP_i2c_wbuf[0] = reg;
    xNXP_i2c_wbuf[1] = *buf;

#if SUPPORT_NXP_I2C_CHANNEL0
    if (I2C_CH0_WrToRdStream(Addr,
                             &xNXP_i2c_wbuf[0],
                             2,
                             0,
                             &xNXP_i2c_rbuf[0],
                             0))
    {
        return TRUE;
    }
#else
    if (I2C_CH1_WrToRdStream(Addr,
                             &xNXP_i2c_wbuf[0],
                             2,
                             0,
                             &xNXP_i2c_rbuf[0],
                             0))
    {
        return TRUE;
    }
#endif
    if (Addr == _NXP_PORT1_ADDR)
    {
        xNXP_PORT1_FailCount2++;
    }
#if SUPPORT_NXP_PD_PORT2
    if (Addr == _NXP_PORT2_ADDR)
    {
        xNXP_PORT2_FailCount2++;
    }
#endif
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - NXP_Init
 * @function - NXP PD Sink/Source Switch controller write register service
 * @Upstream - By call
 * @input    - register index, data buffer, Length
 * @return   - TRUE: success
 * @note     - None
 */
BYTE NXP_Init(void)
{
    if( xNXP_PORT1_InitComplete != 0xFF )
    {
        //Check if in dead battery mode
        xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                    _NXP_DEVICE_STATUS,
                                    &xNXP_i2c_data[0],
                                    1);
        xNXP_PORT1_Device_Control = xNXP_i2c_data[0];
        if(xNXP_PORT1_Device_Control != 0 )
        {
            SET_MASK(xNXP_PORT1_Device_Control, BIT2);
        }
        else 
        {
            // Reg 0x0B
            xNXP_i2c_data[0] = 0x04;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT1_ADDR,
                                        _NXP_DEVICE_CONTROL,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(5);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_DEVICE_CONTROL,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_Device_Control = xNXP_i2c_data[0];
            Delay1MS(5);
        }
        if(IS_MASK_SET(xNXP_PORT1_Device_Control, BIT2))
        {
            // NXP port 1
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_DEVICE_ID,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_Device_ID = xNXP_i2c_data[0];
            Delay1MS(5);
            
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_DEVICE_STATUS,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_Devcie_Status = xNXP_i2c_data[0];
            Delay1MS(5);
            
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_SWITCH_STATUS,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_Switch_Status = xNXP_i2c_data[0];                            
            Delay1MS(5);                            
            
            // NXP Initial setting
            // Reg 0x08
            xNXP_i2c_data[0] = 0x06;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT1_ADDR,
                                        _NXP_OVLO_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(5);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_OVLO_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_OVLO_Threshold = xNXP_i2c_data[0];                                
            Delay1MS(5);
            
            // Reg 0x09
            xNXP_i2c_data[0] = 0x0F;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT1_ADDR,
                                        _NXP_HV_SRC_OCP_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(5);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT1_ADDR,
                                        _NXP_HV_SRC_OCP_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT1_HV_SRC_OCP_Threshold = xNXP_i2c_data[0]; 
            Delay1MS(5);
            xNXP_PORT1_InitComplete = 0xFF;
        }
    }
        
    if( xNXP_PORT2_InitComplete != 0xFF )
    {
        xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                    _NXP_DEVICE_STATUS,
                                    &xNXP_i2c_data[0],
                                    1);
        xNXP_PORT2_Device_Control = xNXP_i2c_data[0];
        if(xNXP_PORT2_Device_Control != 0 )
        {
            SET_MASK(xNXP_PORT2_Device_Control, BIT2);
        }
        else 
        {       
            // Reg 0x0B
            xNXP_i2c_data[0] = 0x04;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT2_ADDR,
                                        _NXP_DEVICE_CONTROL,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(5);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_DEVICE_CONTROL,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_Device_Control = xNXP_i2c_data[0];
            Delay1MS(5);
        }
        if(IS_MASK_SET(xNXP_PORT2_Device_Control, BIT2))
        {         
            // NXP port 2 
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_DEVICE_ID,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_Device_ID = xNXP_i2c_data[0];
            Delay1MS(10);
            
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_DEVICE_STATUS,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_Devcie_Status = xNXP_i2c_data[0];
            Delay1MS(10);
            
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_SWITCH_STATUS,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_Switch_Status = xNXP_i2c_data[0];
            Delay1MS(10);  
    
            // NXP Initial setting
            // Reg 0x08
            xNXP_i2c_data[0] = 0x06;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT2_ADDR,
                                        _NXP_OVLO_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(10);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_OVLO_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_OVLO_Threshold = xNXP_i2c_data[0];                                
            Delay1MS(10);
    
            // Reg 0x09
            xNXP_i2c_data[0] = 0x0F;
            xNXP_i2c_ack = NXP_WriteREG( _NXP_PORT2_ADDR,
                                        _NXP_HV_SRC_OCP_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            Delay1MS(10);
            xNXP_i2c_ack = NXP_ReadREG( _NXP_PORT2_ADDR,
                                        _NXP_HV_SRC_OCP_THRESHOLD,
                                        &xNXP_i2c_data[0],
                                        1);
            xNXP_PORT2_HV_SRC_OCP_Threshold = xNXP_i2c_data[0]; 
            Delay1MS(10);
            xNXP_PORT2_InitComplete = 0xFF;
        }
    }
    
    return TRUE;
    
//     return FALSE;
}
/*-----------------------------------------------------------------------------*/
/* End of NXP.C */