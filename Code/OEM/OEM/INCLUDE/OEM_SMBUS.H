/*-----------------------------------------------------------------------------
 * @file     | OEM_SMBUS.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_SMBUS.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_SMBUS_H
#define OEM_SMBUS_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _SMB_CH0                    0x00
#define _SMB_CH1                    0x01
#define _SMB_CH2                    0x02
#define _SMB_CH3                    0x03
#define _SMBA_CHN                   0x00
#define _SMBB_CHN                   0x04
#define _SMBC_CHN                   0x08
#define _SMBD_CHN                   0x0C
#define _SMB_DEV0                   0x00
#define _SMB_DEV1                   0x01
#define _SMB_DEV2                   0x02
#define _SMB_DEV3                   0x03
#define _SMB_ON                     0x01
#define _SMB_OFF                    0x00
#define _SMBC_CHN2                  0x0F
//-----------------------------------------------------------------------------
#define _SMB_QK_BYTE                0x40
#define _SMB_TX_BYTE                0x44
#define _SMB_RX_BYTE                0x45
#define _SMB_RD_BYTE                0x48
#define _SMB_WR_BYTE                0x49
#define _SMB_RD_WORD                0x4C
#define _SMB_WR_WORD                0x4D
#define _SMB_RD_BLCK                0x54
#define _SMB_WR_BLCK                0x55
//-----------------------------------------------------------------------------
#define _SMbusEXT                   0x1C    // Extend command
#define _SMBusPEC                   0x01
#define _SMBusNoPEC                 0x00
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * Reference Smart Battery Data Specification
 * The following definition summarizes the Smart Battery command set.
 *---------------------------------------------------------------------------*/
#define _SMB_BatteryAddr            0x16
#define _CMD_ManufacturerAccess     0x00
#define _CMD_RemainingCapacityAlarm 0x01
#define _CMD_RemainingTimeAlarm     0x02
#define _CMD_BatteryMode            0x03
#define _CMD_AtRate                 0x04
#define _CMD_AtRateTimeToFull       0x05
#define _CMD_AtRateTimeToEmpty      0x06
#define _CMD_AtRateOK               0x07
#define _CMD_Temperature            0x08
#define _CMD_Voltage                0x09
#define _CMD_Current                0x0A
#define _CMD_AverageCurrent         0x0B
#define _CMD_MaxError               0x0C
#define _CMD_RelativeStateOfCharge  0x0D
#define _CMD_AbsoluteStateOfCharge  0x0E
#define _CMD_RemainingCapacity      0x0F
#define _CMD_FullChargeCapacity     0x10
#define _CMD_RunTimeToEmpty         0x11
#define _CMD_AverageTimeToEmpty     0x12
#define _CMD_AverageTimeToFull      0x13
#define _CMD_ChargingCurrent        0x14
#define _CMD_ChargingVoltage        0x15
#define _CMD_BatteryStatus          0x16
#define _CMD_CycleCount             0x17
#define _CMD_DesignCapacity         0x18
#define _CMD_DesignVoltage          0x19
#define _CMD_SpecificationInfo      0x1A
#define _CMD_ManufactureDate        0x1B
#define _CMD_SerialNumber           0x1C
#define _CMD_ManufacturerName       0x20
#define _CMD_DeviceName             0x21
#define _CMD_DeviceChemistry        0x22
#define _CMD_ManufacturerData       0x23
#define _CMD_OptionalMfgFunction5   0x2F
#define _CMD_OptionalMfgFunction4   0x3C
#define _CMD_OptionalMfgFunction3   0x3D
#define _CMD_OptionalMfgFunction2   0x3E
#define _CMD_OptionalMfgFunction1   0x3F

#define _CMD_Cell_4                 0x3C
#define _CMD_Cell_3                 0x3D
#define _CMD_Cell_2                 0x3E
#define _CMD_Cell_1                 0x3F
#define _CMD_ManufacturerInfo       0x70

/*-----------------------------------------------------------------------------
 * Reference Smart Charger Specification
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/* BQ25720 */
#if 0/* 1:ADL_P */
#define _CMD_ChargerOption          0x12
#define _CMD_ChargerStatus          0x20
#define _CMD_ProchotStatus          0x21
#define _CMD_ChargerOption1         0x30
#define _CMD_ChargerOption2         0x31
#define _CMD_ChargerOption3         0x32
#define _CMD_ProchotOption0         0x33
#define _CMD_ProchotOption1         0x34
#define _CMD_ADCOption              0x35
#define _CMD_ChargerOption4         0x36
#define _CMD_VminActiveProtection   0x37
#define _CMD_OTGVoltage             0x3B
#define _CMD_OTGCurrent             0x3C
#define _CMD_InputVoltage           0x3D
#define _CMD_ChargerInputCurrent    0x3F
#define _CMD_ChargerManufacturerID  0xFE
#define _CMD_ChargerDeviceID        0xFF
#define _CMD_MinSystemVoltage       0x3E

#endif


/* The ROHm BD99950MUV supports battery-charger commands */
#if 1   /* 1:TGL_UP3, JSL, ADL_N */
#define _CMD_ChargerOption          0x12
#define _CMD_ChargerMinSysVoltage   0x3E
#define _CMD_ChargerInputCurrent    0x3F
#define _CMD_ChargerManufacturerID  0xFE
#define _CMD_ChargerDeviceID        0xFF
#define _CMD_ChargerREG3E           0x3E
#define _CMD_MinSystemVoltage       0x3E

#endif

/* The bq24715/7 supports seven battery-charger commands */
#if 0   /* 1:ICL-MRD */
/*
  0x12 ChargeOption() Read or Write
       Charger Options Control Default E144H
  0x14 ChargeCurrent() Read or Write
       7-Bit Charge Current Setting Default 0mA,64mA Step Range:128mA~8.128A
  0x15 MaxChargeVoltage() Read or Write
       11-Bit Charge Voltage Setting Default 2S-9V, 3S-13.5V, 4S-17.4V...
  0x3E MinSystemVoltage() Read or Write
       6-Bit Minimum System Voltage Setting Default 2S-6.144V, 3S-9.216V...
  0x3F InputCurrent() Read or Write
       7-Bit Input Current Setting Default 3.2A,64mA Step,Range:128mA-8.064A
  0xFE ManufacturerID() Read Only Manufacturer ID: 0x0040H
  0xFF DeviceID() Read Only Device ID 0x0010H (715) 0x0012H (717)
*/
#define _CMD_ChargerOption          0x12
#define _CMD_ChargerMinSysVoltage   0x3E
#define _CMD_ChargerInputCurrent    0x3F
#define _CMD_ChargerManufacturerID  0xFE
#define _CMD_ChargerDeviceID        0xFF
#define _CMD_ChargerREG3E           0x3E
#define _CMD_MinSystemVoltage       0x3E

#endif

/* The bq2477x supports battery-charger commands */
#if 0   /* 1:KBL-R-MRD */
/*
    0x12H ChargeOption0()    R/W Charger Option Control 0       0xE14EH
    0x3BH ChargeOption1()    R/W Charge Option Control 1        0x2011H
    0x38H ChargeOption2()    R/W Charge Options Control 2       0x0080H
    0x3CH ProchotOption0()   R/W PROCHOT Option 0               0x4854H
    0x3DH ProchotOption1()   R/W PROCHOT Option 1               0x8120H
    0x14H ChargeCurrent()    R/W 7-Bit Charge Current Setting   0x0000H
    0x15H MaxChargeVoltage() R/W 11-Bit Charge Voltage Setting 1S-4.4V,
                                2S-9.008V, 3S/4S-13.504V I
    0x3EH MinSystemVoltage() R/W 6-Bit Minimum System Voltage 1S-3.584V,
                                2S-6.144V, 3S/4S-9.216V
    0x3FH InputCurrent()     R/W 7-Bit Input Current Setting 3200mA (770)
    0xFEH ManufacturerID()   Read Only Manufacturer ID          0x0040H
    0xFFH DeviceAddress()    Read Only Device Address           0x0114H (770)
*/
#define _CMD_ChargeOption0          0x12
#define _CMD_ChargeOption1          0x3B
#define _CMD_ChargeOption2          0x38
#define _CMD_ChargeProchotOption0   0x3C
#define _CMD_ChargeProchotOption1   0x3D
#define _CMD_ChargeCurrent          0x14
#define _CMD_MaxChargeVoltage       0x15
#define _CMD_ChargeMinSystemVoltage 0x3E
#define _CMD_ChargerInputCurrent    0x3F
#define _CMD_ChargerManufacturerID  0xFE
#define _CMD_ChargerDeviceID        0xFF
#endif

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct RSmbusStruct
{
    BYTE    address;
    BYTE    cmd;
    XBYTE   *smbdata;

} sRSmbusStruct;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc);
extern bit SMB_DataToMem(BYTE SMBX_ID, WORD SMBX_MEMADR,
                         BYTE SMBX_CTL, BYTE D0REG_X, BYTE D1REG_X);
extern void SMBA_SetToRegs(BYTE SMBA_DEVX_ADDR, BYTE DEVX_ID);
extern void SMBB_SetToRegs(BYTE SMBB_DEVX_ADDR, BYTE DEVX_ID);
extern void SMBC_SetToRegs(BYTE SMBC_DEVX_ADDR, BYTE DEVX_ID);

extern void SMBusA_ScanCenter(void);
extern void SMBusB_ScanCenter(void);
extern void SMBusC_DataCenter(void);

//-----------------------------------------------------------------------------
#endif  //OEM_SMBUS_H
/*-----------------------------------------------------------------------------
 * End of OEM_SMBUS.H */