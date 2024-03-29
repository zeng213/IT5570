/*-----------------------------------------------------------------------------
 * @file     | OEM_SMBUS.C
 *-----------+-----------------------------------------------------------------
 * @function | OEM SMBus Data Service
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
 * @subroutine - Hook_GetSMBusReadBlockByteCount
 * @function - [rblk_bcis] the byte count of read smbus read block protocol
 * @Upstream - CORE_SMBUS.C
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - SMB_DataToMem
 * @function - SMBus data move to Memory
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - SMBX_ID, SMBX_MEMADR, SMBX_CTL, D0REG_X, D1REG_X
 * @return   - TRUE: All data finished
 *             FALSE: More data request (ex:block read)
 * @note     - None
 */
bit SMB_DataToMem(BYTE SMBX_ID, WORD SMBX_MEMADR,
                  BYTE SMBX_CTL, BYTE D0REG_X, BYTE D1REG_X)
{
    BYTE    SMB_BLK_DAT;

    //-------------------------------------------------------------------------
    Tmp_XPntr = 0;
    Tmp_XPntr += SMBX_MEMADR;
    //-------------------------------------------------------------------------
    /* Read Byte/Word Data */
    if (SMBX_CTL == _SMB_RD_WORD)
    {
        *Tmp_XPntr = D1REG_X;
        Tmp_XPntr++;
        *Tmp_XPntr = D0REG_X;
        return TRUE;
    }
    if (SMBX_CTL == _SMB_RD_BYTE)
    {
        *Tmp_XPntr = D0REG_X;
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_CTL != _SMB_RD_BLCK)
    {
        return TRUE;
    }
    //-------------------------------------------------------------------------
    /* Read Block Data */
    SMBX_ID &= 0x0C;    //Get Channel ID
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBA_CHN)
    {
        SMB_BLK_DAT = HOBDB_A;
        if (SMBA_BYTE_CNT == 0)
        {
            SMBA_BYTE_CNT = D0REG_X;
            if (SMBA_BYTE_CNT > 32)
            {
                SMBA_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBA_DEV_MEM++;
        SMBA_BYTE_CNT--;
        if (SMBA_BYTE_CNT > 0)
        {
            if (SMBA_BYTE_CNT == 1)
            {
                HOCTL_A |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBB_CHN)
    {
        SMB_BLK_DAT = HOBDB_B;
        if (SMBB_BYTE_CNT == 0)
        {
            SMBB_BYTE_CNT = D0REG_X;
            if (SMBB_BYTE_CNT > 32)
            {
                SMBB_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBB_DEV_MEM++;
        SMBB_BYTE_CNT--;
        if (SMBB_BYTE_CNT > 0)
        {
            if (SMBB_BYTE_CNT == 1)
            {
                HOCTL_B |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBC_CHN)
    {
        SMB_BLK_DAT = HOBDB_C;
        if (SMBC_BYTE_CNT == 0)
        {
            SMBC_BYTE_CNT = D0REG_X;
            if (SMBC_BYTE_CNT > 32)
            {
                SMBC_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBC_DEV_MEM++;
        SMBC_BYTE_CNT--;
        if (SMBC_BYTE_CNT > 0)
        {
            if (SMBC_BYTE_CNT == 1)
            {
                HOCTL_C |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBD_CHN)
    {
        SMB_BLK_DAT = HOBDB_D;
        if (SMBD_BYTE_CNT == 0)
        {
            SMBD_BYTE_CNT = D0REG_X;
            if (SMBD_BYTE_CNT > 32)
            {
                SMBD_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBD_DEV_MEM++;
        SMBD_BYTE_CNT--;
        if (SMBD_BYTE_CNT > 0)
        {
            if (SMBD_BYTE_CNT == 1)
            {
                HOCTL_D |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBA_SetToRegs
 * @function - SMBusA registers control
 * @upstream - By call
 * @input    - SMBA_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBA_SetToRegs(BYTE SMBA_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_A  = SMBA_CHN_CMD;
    TRASLA_A = SMBA_DEVX_ADDR;

    if (SMBA_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr = (unsigned int *)SMBA_DEV_MEM;
        D1REG_A = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_A = *Tmp_XPntr;
    }
    else if (SMBA_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr = (unsigned int *)SMBA_DEV_MEM;
        D0REG_A = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBA_CHN_CTL & 0x01) == 0)
    {
        TRASLA_A |= 0x01;
    }
    /* Start transimition. */
    HOCTL_A = (SMBA_CHN_CTL & 0xFC);
    SMBA_CHN_STS = (F_SMB_BUSY + _SMBA_CHN + DEVX_ID);
    SMBA_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBB_SetToRegs
 * @function - SMBusB registers control
 * @upstream - By call
 * @input    - SMBB_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBB_SetToRegs(BYTE SMBB_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_B  = SMBB_CHN_CMD;
    TRASLA_B = SMBB_DEVX_ADDR;

    if (SMBB_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr = (unsigned int *)SMBB_DEV_MEM;
        D1REG_B = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_B = *Tmp_XPntr;
    }
    else if (SMBB_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr = (unsigned int *)SMBB_DEV_MEM;
        D0REG_B = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBB_CHN_CTL & 0x01) == 0)
    {
        TRASLA_B |= 0x01;
    }
    /* Start transimition. */
    HOCTL_B = (SMBB_CHN_CTL & 0xFC);
    SMBB_CHN_STS = (F_SMB_BUSY + _SMBB_CHN + DEVX_ID);
    SMBB_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBC_SetToRegs
 * @function - SMBusC registers control
 * @upstream - By call
 * @input    - SMBC_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBC_SetToRegs(BYTE SMBC_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_C  = SMBC_CHN_CMD;
    TRASLA_C = SMBC_DEVX_ADDR;
    Tmp_XPntr = 0;
    if (SMBC_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr += SMBC_DEV_MEM;
        D1REG_C = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_C = *Tmp_XPntr;
    }
    else if (SMBC_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr += SMBC_DEV_MEM;
        D0REG_C = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBC_CHN_CTL & 0x01) == 0)
    {
        TRASLA_C |= 0x01;
    }
    /* Start transimition. */
    HOCTL_C = (SMBC_CHN_CTL & 0xFC);
    SMBC_CHN_STS = (F_SMB_BUSY + _SMBC_CHN + DEVX_ID);
    SMBC_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBusA_ScanCenter
 * @function - SMBusA_ScanCenter();     //GPB.3_SMCLK0, GPB.4_SMDAT0
 * @upstream - Hook_Timer5msEvent
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBusA_ScanCenter(void)
{
    //-------------------------------------------------------------------------
    /* Check & Process Channel-1 data in. */
    //-------------------------------------------------------------------------
    if (SMBA_CHN_STS & F_SMB_BUSY)
    {
        if (((HOSTA_A & 0x1C) > 0) || (SMBA_CHN_TIMER > 20))
        {
            /* SMBus timeout or error. */
            if (SMBA_ERR_STS[SMBA_CHN_STS & 0x03] < 0xFF)
            {
                SMBA_ERR_STS[SMBA_CHN_STS & 0x03]++;
            }
            /* Clear H/W I2C Status */
            HOSTA_A = 0xFF;
            SMBA_CHN_STS = 0;
            SMBA_CHN_TIMER = 0;

        }
        else if ((HOSTA_A & 0x82) > 0)
        {
            /* SMBus Data in. */
            if (SMB_DataToMem((SMBA_CHN_STS & 0x0F), SMBA_DEV_MEM,
                              SMBA_CHN_CTL, D0REG_A, D1REG_A))
            {
                SMBA_CHN_STS = 0;
                SMBA_CHN_TIMER = 0;
            }
            SMBA_ERR_STS[SMBA_CHN_STS & 0x03] = 0;
            /* SMBus Data-In Counter */
            if (SMBA_DAT_CNT[SMBA_CHN_STS & 0x0F] < 255)
            {
                SMBA_DAT_CNT[SMBA_CHN_STS & 0x0F] += 1;
            }
            /* Clear H/W I2C Status */
            HOSTA_A = 0xFF;
        }
        else
        {
            SMBA_CHN_TIMER++;
        }
        return;
    }
    //-----------------------------------------------------
    /* Device Service Hook. */
    //-----------------------------------------------------

    //-----------------------------------------------------
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - SMBusB_ScanCenter
 * @function - SMBusB_ScanCenter();
 * @upstream - Hook_Timer5msEvent
 * @input    - None
 * @return   - None
 * @note     - None
 */
void SMBusB_ScanCenter(void)
{
    //-----------------------------------------------------
    /* Check & Process Channel-1 data in. */
    //-----------------------------------------------------
    if (SMBB_CHN_STS & F_SMB_BUSY)
    {
        if (((HOSTA_B & 0x1C) > 0) || (SMBB_CHN_TIMER > 20))
        {
            /* SMBus timeout or error. */
            SMBB_ERR_STS[SMBB_CHN_STS & 0x03] += 1;
            /* Clear H/W I2C Status */
            HOSTA_B = 0xFF;
            SMBB_CHN_STS = 0;
            SMBB_CHN_TIMER = 0;

        }
        else if ((HOSTA_B & 0x82) > 0)
        {
            if((SMBB_CHN_STS & 0x03) == _SMB_DEV0)
            {
                if((SMBB_CHN_CMD == _CMD_ManufacturerName) || 
                    (SMBB_CHN_CMD == _CMD_DeviceName) || 
                    (SMBB_CHN_CMD == _CMD_ManufacturerData))
                {
                    if(D0REG_B > 14)
                    {
                        D0REG_B = 14;
                    }
                }
                if(SMBB_CHN_CMD == _CMD_DeviceChemistry)
                {
                    if(D0REG_B > 6)
                    {
                        D0REG_B = 6;
                    }
                }
            }
            
            /* SMBus Data in. */
            if (SMB_DataToMem((SMBB_CHN_STS & 0x0F), SMBB_DEV_MEM,
                              SMBB_CHN_CTL, D0REG_B, D1REG_B))
            {
                SMBB_CHN_STS = 0;
                SMBB_CHN_TIMER = 0;
            }
            SMBB_ERR_STS[SMBB_CHN_STS & 0x03] = 0;
            /* SMBus Data-In Counter */
            if (SMBB_DAT_CNT[SMBB_CHN_STS & 0x0F] < 255)
            {
                SMBB_DAT_CNT[SMBB_CHN_STS & 0x0F] += 1;
            }
            /* Clear H/W I2C Status */
            HOSTA_B = 0xFF;
        }
        else
        {
            SMBB_CHN_TIMER++;
        }
        return;
    }
    
// #ifdef SUPPORT_PD_CHIP_FLASH_ITE
//     if (xITEPD_FlashUtilityEnable > 0)
//     {
//         return;
//     }	
// #endif
    //-----------------------------------------------------
    /* Device 1 Service Hook. */
    //-----------------------------------------------------
    if (SMBB_DEV1_DLY > 0)
    {
        SMBB_DEV1_DLY--;
    }
    else
    {
#if SUPPORT_SMART_CHARGER
        PollSmartCharger();
#endif
        if (SMBB_DEV1_DLY == 0)
        {
            SMBB_DEV1_DLY = 5;
        }
        return;
    }
    //-----------------------------------------------------
    /* Device 0 Service Hook. */
    //-----------------------------------------------------
    if (SMBB_DEV0_DLY > 0)
    {
        SMBB_DEV0_DLY--;
    }
    else
    {
        if (IS_MASK_SET(SMBB_DEV0_STS, F_DEV_ON_LINE))
        {
#if SUPPORT_SMART_BATTERY
            PollSmartBattery();
#endif
            if (SMBB_DEV0_DLY == 0)
            {
                SMBB_DEV0_DLY = 5;
            }
        }
    }
    
    //-----------------------------------------------------
    /* Device 2 Service Hook. */
    //-----------------------------------------------------
    if (SMBB_DEV2_DLY > 0)
    {
        SMBB_DEV2_DLY--;
    }
    else
    {
#if SUPPORT_SAR_TEST_MODE
        SAR_Service();
#endif
        if (SMBB_DEV2_DLY == 0)
        {
            SMBB_DEV2_DLY = 5;
        }
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_SMBUS.C */