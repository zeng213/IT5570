/*-----------------------------------------------------------------------------
 * @file     | SAR231.C
 * ----------+-----------------------------------------------------------------
 * @function | SAR231
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#if SUPPORT_SAR_TEST_MODE
/*-----------------------------------------------------------------------------
 * @subroutine - SAR_Initial
 * @function - SAR_Initial
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SAR_Initial(void)
{
    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                _SAR_PRODUCT_NUM, &SPIBuffer[8], 0);
    xSAR_PRODUCT_NUM = SPIBuffer[9];

    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                _SAR_VERSION_NUM, &SPIBuffer[8], 0);
    xSAR_VERSION_NUM = SPIBuffer[9];

    /* Initial Registers */
    SPIBuffer[0] = 0x30;
    bRWSMBus(_SMB_CH1, SMbusWB, IQS231A_ADDR,
                _SAR_OTP_2, &SPIBuffer[0], 0);

    SPIBuffer[0] = 0x04;
    bRWSMBus(_SMB_CH1, SMbusWB, IQS231A_ADDR,
                _SAR_PROX_THR, &SPIBuffer[0], 0);
                    
    SPIBuffer[0] = 0x20;
    bRWSMBus(_SMB_CH1, SMbusWB, IQS231A_ADDR,
                0x04, &SPIBuffer[0], 0);
}

/*-----------------------------------------------------------------------------
 * @subroutine - SAR_Service
 * @function - SAR_Service
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SAR_Service(void)
{

    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                0x12, &SPIBuffer[8], 0);
    xSAR_UI_FLAG = SPIBuffer[9];

    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                0x14, &SPIBuffer[8], 0);
    xSAR_EVENT_FLAG = SPIBuffer[9];

    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                0x15, &SPIBuffer[8], 0);
    xSAR_CH0_ACF_H = SPIBuffer[9];

    bRWSMBus(_SMB_CH1, SMbusRW, IQS231A_ADDR,
                0x16, &SPIBuffer[8], 0);
    xSAR_CH0_ACF_L = SPIBuffer[9];
    
    
    SMBB_DEV2_DLY = 250;   //2ms x 250 = 500 ms
}

#endif  // SUPPORT_SAR_TEST_MODE

#if SUPPORT_SAR_EVENT_TRIGGER
/*-----------------------------------------------------------------------------
 * @subroutine - SAR_EventTrigger
 * @function - SAR_EventTrigger
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SAR_EventTrigger(void)
{
    if (IS_SAR_SENS_IO1_EC_LO())     //KSO15 SAR INT
    {
        if(xSAR_Event_Trigger_Timer > 0)
        {
            xSAR_Event_Trigger_Timer--;
            if(xSAR_Event_Trigger_Timer == 0)
            {
                WriteSCI_Buffer(_SCIEVT_SAR_TRIGGER);
                xSAR_Event_Release_Timer = 10;
            }
        }
    }
    else
    {
        if(xSAR_Event_Release_Timer > 0)
        {
            xSAR_Event_Release_Timer--;
            if(xSAR_Event_Release_Timer == 0)
            {
                WriteSCI_Buffer(_SCIEVT_SAR_RELEASE);
                xSAR_Event_Trigger_Timer = 10;
            }
        }
    }
}
#endif  // SUPPORT_SAR_EVENT_TRIGGER