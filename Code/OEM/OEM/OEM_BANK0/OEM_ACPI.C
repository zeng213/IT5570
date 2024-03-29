/*-----------------------------------------------------------------------------
 * @file     | OEM_ACPI.C
 *-----------+-----------------------------------------------------------------
 * @function | OEM ACPI control method process
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
#define DEBUG_EC6266            FALSE
#define DEBUG_EC6266_READ       FALSE
#define DEBUG_EC6266_WRITE      FALSE
#define DEBUG_SCIEVT            TRUE
#define DEBUG_DISABLE_SCIEVT    FALSE

#define DEBUG_UCSI_UART2        FALSE   //UCSI UART2 Debug
#define DEBUG_DPTF_UART2        FALSE   //DPTF UART2 Debug

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_EC6266
#define EC6266_RamDebug(x)      RamDebug(x)
#else
#define EC6266_RamDebug(x)      {}
#endif
#if DEBUG_SCIEVT
#define SCIEVT_RamDebug(x)      RamDebug(x)
#else
#define SCIEVT_RamDebug(x)      {}
#endif
//-----------------------------------------------------------------------------



//*****************************************************************************
// CODE START
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * @subroutine - SCI_EventCenter
 * @function - SCI_EventCenter
 * @upstream - Hook_Timer50msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 */
void SCI_EventCenter(void)
{
#if DEBUG_DISABLE_SCIEVT
    return;
#endif
    if (SCIEVT_DELAY != 0)
    {
        SCIEVT_DELAY--;
        return;
    }
    if (SysPowState != _SYSTEM_S0)
    {
        return;
    }
    if (SCIEVT_OUT != 0)
    {
        OEM_ACPI_Gen_Int();
        SCIEVT_DELAY = 20;  //20*50=1000ms
        SCIEVT_OVT++;
        return;
    }
    if (SCIEVT_RIDX == SCIEVT_WIDX)
    {
        SCIEVT_WIDX = 0;
        SCIEVT_RIDX = 0;
        return;
    }
    ReadSCI_Buffer();
    OEM_ACPI_Gen_Int();
    //SCIEVT_DELAY = 2;     //Next Event Delay: 2*50ms=100ms
}

/*-----------------------------------------------------------------------------
 * @subroutine - ReadSCI_Buffer
 * @function - Read SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ReadSCI_Buffer(void)
{
    if (SCIEVT_RIDX >= SCIEVT_WIDX)
    {
        SCIEVT_OUT = 0;
        SCIEVT_RIDX = 0;
        SCIEVT_WIDX = 0;
    }
    else
    {
        SCIEVT_OUT = SCIEVT_BUF[SCIEVT_RIDX];
        SCIEVT_LAST = SCIEVT_OUT;
        SCIEVT_RIDX++;
        SET_MASK(PM1STS, SCIEVT);
        SCIEVT_RamDebug(SCIEVT_LAST);
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - WriteSCI_Buffer
 * @function - Write SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void WriteSCI_Buffer(BYTE SCI_NUM)
{
    if (IS_eSPI_SLP_S3_LO())
    {
        return;
    }
#if 0
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return;
    }
#endif
    SCIEVT_CNT++;

    if (SCIEVT_WIDX >= 7)
    {
        SCIEVT_WIDX = 7;
        SCIEVT_BUF[SCIEVT_WIDX] = SCI_NUM;
        SCIEVT_LOSE++;
    }
    else
    {
        SCIEVT_BUF[SCIEVT_WIDX] = SCI_NUM;
        SCIEVT_WIDX++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_62Port
 * @function - The hook function of 62 port data
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - PM1Step != 0x00 is necessary.
 */
void Hook_62Port(BYTE PM1_Cmd)
{
    EC6266_RamDebug(0x62);
    EC6266_RamDebug(PM1_Cmd);
    EC6266_RamDebug(PM1Data);
    
    if (PM1_Cmd == 0x1D)    /* Re Timer F/W Enabled */
    {
        if (PM1Data == 0x00)
        {
            ExitRetimerFwUpdate();
            xITEPD_UPD_TBT_Entry = 0;
        }
        else if (PM1Data == 0x01)
        {
            EnterRetimerFwUpdate();
            xITEPD_UPD_TBT_Entry = 1;
        }
        return;
    }

    if (PM1_Cmd == 0x1F)    /* TPT Enabled */
    {
        xITEPD_SetCtrl = PM1Data;
        return;
    }
    
    if (PM1Cmd == 0xAA)
    {
      	if (PM1Step == 2)
    	{
         	xEC_SafeVoltageValueH = PM1Data;
    	}
    	else if(PM1Step == 1)
    	{
            xEC_SafeVoltageValueL = PM1Data;
            BAT1_SafeVoltageValue = (xEC_SafeVoltageValueH << 8) + xEC_SafeVoltageValueL;
            
            if (eFlash_Read_1Byte(0x01, 0xF0, 0x00) != xEC_SafeVoltageValueL)
            {
                // erase
                Do_SPI_Read_ID();
                Do_SPI_Write_Enable();
                Do_SPI_Write_Status(SPIStatus_UnlockAll);
                Do_SPI_Write_Enable();
                Do_SPI_Erase(SPICmd_SectorErase, 0x01, 0xF0, 0x00);
                Do_SPI_Write_Disable();
                
                // Write
                Do_SPI_Read_ID();
                Do_SPI_Write_Enable();
                Do_SPI_Write_Status(SPIStatus_UnlockAll);
                Do_SPI_Write_Enable();
                eFlash_Write_1Byte(xEC_SafeVoltageValueL, 0x01, 0xF0, 0x00);
                eFlash_Write_1Byte(xEC_SafeVoltageValueH, 0x01, 0xF0, 0x01);
                Do_SPI_Write_Disable();

            }
     	}
		return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Cmd_00_7F
 * @function - The hook function of 66 port command 00 - 7Fh
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_66Cmd_00_7F(BYTE PM1_Cmd)
{
    if (PM1_Cmd == 0x1D)
    {
        PM1Step = 1;
        return;
    }
    if (PM1_Cmd == 0x1F)
    {
        PM1Step = 1;
        return;
    }
	
    if (PM1_Cmd == 0x50)
    {
        System_CS_Mode = 1;
        return;
    }
    if (PM1_Cmd == 0x51)
    {
        PwrBtn_OVR_Mode = 1;
        return;
    }
    if (PM1_Cmd == 0x52)
    {
        PwrBtn_OVR_Mode = 0;
        return;
    }
    if (PM1_Cmd == 0x58)
    {
        PM1Step = 1;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Cmd_90_FF
 * @function - The hook function of 66 port command 90 - FFh
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_66Cmd_90_FF(BYTE PM1_Cmd)
{
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0x90)
    {
        PM1DO = 0x00;
        PM1Data = 0x00;
        PM1DataCount = 3;
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0x94)
    {
        return;
    }
    
    if (PM1Cmd == 0x95)
    {
        SinkSwitchControlPD1(SINK_CONTROL_ON);
        return;
    }
    if (PM1Cmd == 0x96)
    {
        SinkSwitchControlPD2(SINK_CONTROL_ON);
        return;
    }
    
    if (PM1Cmd == 0x97)
    {
        SinkSwitchControlPD1(SINK_CONTROL_OFF);
        return;
    }

    if (PM1Cmd == 0x98)
    {
        SinkSwitchControlPD2(SINK_CONTROL_OFF);
        return;
    }
#if SUPPORT_SW_MIRROR
    //-------------------------------------------------------------------------
    if (PM1Cmd == 0xA0)
    {
        /* Force SW Mirror on S5. */
        SET_MASK(EC_SW_MIRROR, SW_MIRROR_EN);
        EC_SW_MIRROR_DELAY = 3;
    }
#endif
    //-------------------------------------------------------------------------
    if (PM1Cmd == 0xA1)
    {
        /* Return Board ID Value */
        PM1DO = xEC_BoardID_Value;
    }
    //test ec, add special commad
    if (PM1Cmd == 0xA2)
    {
        PM1DO = xEC_MainVersion;
    }
    if (PM1Cmd == 0xA3)
    {
        PM1DO = xEC_SubVersion;
    }
    //_at_ MEM_EC_SPACE + 0x13/0x14/0x15/0x16
    if (PM1Cmd == 0xA4)
    {
//        PM1DO = xEC_PDPort0MainVersion;
    }
    if (PM1Cmd == 0xA5)
    {
//        PM1DO = xEC_PDPort0SubVersion;
    }
    if (PM1Cmd == 0xA6)
    {
//        PM1DO = xEC_PDPort1MainVersion;
    }
    if (PM1Cmd == 0xA7)
    {
//        PM1DO = xEC_PDPort1SubVersion;
    }
    if (PM1Cmd == 0xA8)
    {   // Enable fast charge 
        SET_MASK(xEC_FeatureStatus, F_FASTCHARGE_EN_STA);
    }
    if (PM1Cmd == 0xA9)
    {
        CLEAR_MASK(xEC_FeatureStatus, F_FASTCHARGE_EN_STA);
    }
    if (PM1Cmd == 0xAA)
    {
        PM1Step = 2;
        return;
    }
    if (PM1Cmd == 0xAB)
    {
        AMP_EN_HI();
        return;
    }
    if (PM1Cmd == 0xAC)
    {
        AMP_EN_LO();
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0xE0)
    {
#if SUPPORT_UCSI
        //UCSI CMD (OPM->PPM READY)
        xUCSI_opm_cmd_ready = 1;
#endif
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0xE1)
    {
        SET_MASK(HOST_BIOS_REG1, F_ME_UNLOCK);
        return;
    }
    if (PM1_Cmd == 0xE2)
    {
        CLEAR_MASK(HOST_BIOS_REG1, F_ME_UNLOCK);
        return;
    }
    if (PM1_Cmd == 0xE3)    /* Read ME LOCK / UNLOCK Status */
    {
        //if (IS_PCH_ME_UNLOCK_HI())    //REAL PIN
        //{
        //    PM1DO = 0xE1;
        //}
        //else
        //{
        //    PM1DO = 0xE2;
        //}
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0xFC)
    {
        F_EN_CMD66_RESET = 1;
        return;
    }
    if (PM1_Cmd == 0xFD)
    {
        if (F_EN_CMD66_RESET)
        {
            F_EN_CMD66_RESET = 0;
            WDTRST = 1;             // Reset watch dog timer
            WDTEB = 1;              // Enable watch dog
            while (1);              // Wait for watch dog time-out
        }
        return;
    }
    //-------------------------------------------------------------------------
    PM1Step = 1;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Port
 * @function - The hook function of 66 port command.
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_66Port(BYTE PM1_Cmd)
{
    BYTE    i;
    EC6266_RamDebug(0x66);
    EC6266_RamDebug(PM1_Cmd);
    //-------------------------------------------------------------------------
    if (PM1_Cmd < 0x80)
    {
        Hook_66Cmd_00_7F(PM1_Cmd);
        return;
    }
    else if (PM1_Cmd > 0x8F)
    {
        Hook_66Cmd_90_FF(PM1_Cmd);
        return;
    }
    //F_EN_CMD66_RESET = 0;
    //-------------------------------------------------------------------------
    if ((PM1_Cmd == 0x80) || (PM1_Cmd == 0x81))
    {
        if (IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
        {
            if (IS_MASK_CLEAR(PM1STS, BURST))
            {
                ECCheckBurstMode = 1;
            }
        }
        return;
    }
    else if (PM1_Cmd == 0x82)
    {
        // Auto ACPI Enable
        SET_MASK(SystemFlag1, F_ACPI_MODE);
        // Burst Enable Embedded Controller, BE_EC (0x82)
        ECCheckBurstMode = 1;
        return;
    }
    else if (PM1_Cmd == 0x83)
    {
        // Burst Disable Embedded Controller, BD_EC (0x83)
        ECCheckBurstMode = 0;
        return;
    }
    else if (PM1_Cmd == 0x84)
    {
        // Query Embedded Controller, QR_EC (0x84)
        SendFromAcpi(SCIEVT_OUT);
        CLEAR_MASK(PM1STS, SCIEVT);
        if (SCIEVT_OUT == _SCIEVT_USBTC)    //0x79;
        {
#if DEBUG_UCSI_UART2
            UART2_RBR = 0xAA;
            UART2_RBR = _SCIEVT_USBTC;
#endif
        }
        SCIEVT_OUT = 0x00;
        EC6266_RamDebug(SCIEVT_OUT);
        return;
    }
    else if (PM1_Cmd == 0x86)
    {
        // Enable EC ACPI mode.
        SET_MASK(SystemFlag1, F_ACPI_MODE);
        SCIEVT_OVT = 0;
        SCIEVT_DELAY = 200;  // Event out after 1Sec
        
        SendSystemACPIToPD1();
        SendSystemACPIToPD2();
        return;
    }
    else if (PM1_Cmd == 0x87)
    {
        // Disable EC ACPI mode. (Legacy Mode)
        CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
        return;
    }
    else if (PM1_Cmd == 0x8A)
    {
        PM1DO = 0x00;
        return;
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ACPICommand
 * @function - Hook function of ACPI command
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_ACPICommand(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - OEM_ACPI_Gen_Int
 * @function - Parameter "QeventSCI" only, For a pulsed SCI
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

/*-----------------------------------------------------------------------------
 * @subroutine - ClearSCIEvent
 * @function - ClearSCIEvent
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ResetSCIEvent(void)
{
    BYTE    i;

    for (i = 0; i < 8; i++)
    {
        SCIEVT_BUF[i] = 0x00;
    }
    SCIEVT_WIDX = 0;
    SCIEVT_RIDX = 0;
    SCIEVT_OUT = 0;
    CLEAR_MASK(PM1STS, SCIEVT);
    ECCheckBurstMode = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
void ECQEvent(BYTE sci_number, BYTE sci_mode)
{
    SET_MASK(PM1STS, SCIEVT);
    OEM_ACPI_Gen_Int();
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ReadMapECSpace
 * @function - Read EC Ram Space
 * @upstream - By call
 * @input    - MapIndex: EC Space offset address (0x00~0xFF)
 * @return   - EC space data
 * @note     - None
 */
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
    EC6266_RamDebug(MapIndex);
    Tmp_XPntr = (MEM_EC_SPACE | MapIndex);  //EC_RAM@0400
    ITempB05 = *Tmp_XPntr;
    EC6266_RamDebug(ITempB05);

#if DEBUG_DPTF_UART2
    if ((MapIndex > 0x61) && (MapIndex < 0x76))
    {
        UART2_RBR = 0x52;   //'R'
        PRINT_BYTE_ASCII(MapIndex);
        UART2_RBR = 0x3D;   //'='
        PRINT_BYTE_ASCII(ITempB05);
        UART2_RBR = 0x20;   //' '
    }
#endif

#if DEBUG_UCSI_UART2
    if (MapIndex >= 0xE0)
    {
        UART2_RBR = 0xAE;
        UART2_RBR = MapIndex;
        UART2_RBR = ITempB05;
    }
    else if (MapIndex >= 0xD0)
    {
        UART2_RBR = 0xAD;
        UART2_RBR = MapIndex;
        UART2_RBR = ITempB05;
    }
    else if (MapIndex >= 0xC8)
    {
        UART2_RBR = 0xAC;
        UART2_RBR = MapIndex;
        UART2_RBR = ITempB05;
    }
    else if (MapIndex >= 0xC4)
    {
        UART2_RBR = 0xAB;
        UART2_RBR = MapIndex;
        UART2_RBR = ITempB05;
    }
    else if (MapIndex >= 0xC0)
    {
        UART2_RBR = 0xAF;
        UART2_RBR = MapIndex;
        UART2_RBR = ITempB05;
    }
#endif

    return (ITempB05);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_WriteMapECSpace
 * @function - Write EC Ram Space
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
    EC6266_RamDebug(MapIndex);
    Tmp_XPntr = (MEM_EC_SPACE | MapIndex);
    *Tmp_XPntr = data1;
    EC6266_RamDebug(data1);

#if 1   //SUPPPORT_INTEL_DPTF
    if (MapIndex == 0x64)
    {
#if DEBUG_DPTF_UART2
        UART2_RBR = 0x48;   //'H'
        PRINT_BYTE_ASCII(MapIndex);
        UART2_RBR = 0x3D;   //'='
        PRINT_BYTE_ASCII(data1);
        UART2_RBR = 0x20;   //' '
#endif
        Intel_DPTF_Set_TSHT();
    }
    else if (MapIndex == 0x65)
    {
#if DEBUG_DPTF_UART2
        UART2_RBR = 0x4C;   //'L'
        PRINT_BYTE_ASCII(MapIndex);
        UART2_RBR = 0x3D;   //'='
        PRINT_BYTE_ASCII(data1);
        UART2_RBR = 0x20;   //' '
#endif
        Intel_DPTF_Set_TSLT();
    }
#endif

#if DEBUG_DPTF_UART2
    if (MapIndex == 0x63)   //xEC_Sensor_F
    {
        UART2_RBR = 0x0D;
        UART2_RBR = 0x0A;
        UART2_RBR = 0x46;   //'F'
        PRINT_BYTE_ASCII(MapIndex);
        UART2_RBR = 0x3D;   //'='
        PRINT_BYTE_ASCII(data1);
        UART2_RBR = 0x20;   //' '
    }
#endif

#if SUPPORT_UCSI_NO_E0_CMD
    if (MapIndex == 0xC8)   //xUCSI_DS_CTL0
    {
        //UCSI CMD (OPM->PPM READY)
        xUCSI_opm_cmd_ready = 1;
//         xUCSI_DS_CCI3 = F_BusyIndicator;
    }
#endif

#if DEBUG_UCSI_UART2
    if (MapIndex >= 0xE0)
    {
        UART2_RBR = 0xBE;
        UART2_RBR = MapIndex;
        UART2_RBR = data1;
    }
    else if (MapIndex >= 0xD0)
    {
        UART2_RBR = 0xBD;
        UART2_RBR = MapIndex;
        UART2_RBR = data1;
    }
    else if (MapIndex >= 0xC8)
    {
        UART2_RBR = 0xBC;
        UART2_RBR = MapIndex;
        UART2_RBR = data1;
    }
    else if (MapIndex >= 0xC4)
    {
        UART2_RBR = 0xBB;
        UART2_RBR = MapIndex;
        UART2_RBR = data1;
    }
    else if (MapIndex >= 0xC0)
    {
        UART2_RBR = 0xBF;
        UART2_RBR = MapIndex;
        UART2_RBR = data1;
    }
#endif  //DEBUG_UCSI_UART2

}
void CheckShutdownTemp(void)
{
    if (SysPowState == _SYSTEM_S0)
    {
        if (xEC_SOCCriTripPoint > 0)
        {
            if (xEC_PECI_CPU_T >= xEC_SOCCriTripPoint)
            {
                xSOCTripPointCnt++;
                if (xSOCTripPointCnt >= 10)
                {
                    Oem_TriggerPowerOff(_ST_SOC_TP_SHUTDOWN);
                }
            }
            else
            {
                 xSOCTripPointCnt = 0;
            }
        }

        if (xEC_SkinCriTripPoint > 0)
        {
            if (xEC_Sensor_1_T >= xEC_SkinCriTripPoint) 
            {
                xSkinTripPointCnt++;
                if (xSkinTripPointCnt >= 20)
                {
                    Oem_TriggerPowerOff(_ST_SKIN_TP_SHUTDOWN);
                }
            }
            else
            {
                xSkinTripPointCnt = 0;
            }
        }
        
    }
    
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_ACPI.C */
