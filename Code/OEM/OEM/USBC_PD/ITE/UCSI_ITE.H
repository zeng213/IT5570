/*-----------------------------------------------------------------------------
 * @file     | UCSI_ITE.H
 *-----------+-----------------------------------------------------------------
 * @function | UCSI.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2010-2021, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef __UCSI_ITE_H
#define __UCSI_ITE_H

/*-----------------------------------------------------------------------------
 * ITE PD i2c command control table
 *---------------------------------------------------------------------------*/
#define _ITEPD_UCSI_VERSION     0x80
#define _ITEPD_UCSI_STATUS      0x84
#define _ITEPD_UCSI_MESSAGE_IN  0x88
#define _ITEPD_UCSI_CONTROL     0x98
#define _ITEPD_UCSI_MESSAGE_OUT 0xA0

#define _ITEPD_GET_PD_FW_VER    0xB6    //Return 2 Bytes
#define _ITEPD_SET_ALERT_CLR    0xBC
#define _ITEPD_GET_ALERT_REG    0xBD    //Return 1 Byte
#define _ITEPD_EXIT_TCPC_MODE   0xBE
#define _ITEPD_PD_CHIP_VER      0xD5    //Return 1 Byte
#define _ITEPD_PD_CHIP_ID       0xD6    //Return 2 Bytes

/*-----------------------------------------------------------------------------
 * UCSI Data field & Data Structure Prototype
 *---------------------------------------------------------------------------*/
#define _CONN_PORT1                         1
#define _CONN_PORT2                         2
#define _UCSI_PORT1                         1 << 1
#define _UCSI_PORT2                         2 << 1

// Capability attributes: Table 4-14
#define CAP_ATTR_DISABLED_STATE_SUPPORT     BIT0
#define CAP_ATTR_BATTERY_CHARGING           BIT1
#define CAP_ATTR_USB_POWER_DELIVERY         BIT2
#define CAP_ATTR_USB_TYPE_C_CURRENT         BIT6

#define CAP_ATTR_POWER_SOURCE_AC            BIT0
#define CAP_ATTR_POWER_SOURCE_OTHER         BIT2
#define CAP_ATTR_POWER_SOURCE_VBUS          BIT6

/* bmOptionalFeatures Field Description */
// USBC UCSI Rev 1.0 Capability optional features: Table 4-50
#if 0
#define CAP_OPT_SET_UOM                     BIT0
#define CAP_OPT_SET_PDM                     BIT1
#define CAP_OPT_ALT_MODE_DETAILS            BIT2
#define CAP_OPT_ALT_MODE_OVERRIDE           BIT3
#define CAP_OPT_PDO_DETAILS                 BIT4
#define CAP_OPT_CABLE_DETAILS               BIT5
#define CAP_OPT_EXT_SUPPLY_NOTIFICATION     BIT6
#define CAP_OPT_PD_RESET_NOTIFICATION       BIT7
#endif
// USBC UCSI Rev 1.2 Capability optional features: Table 4-54
#define CAP_OPT_SET_CCOM                    BIT0
#define CAP_OPT_SET_POWER_LEVEL             BIT1
#define CAP_OPT_ALT_MODE_DETAILS            BIT2
#define CAP_OPT_ALT_MODE_OVERRIDE           BIT3
#define CAP_OPT_PDO_DETAILS                 BIT4
#define CAP_OPT_CABLE_DETAILS               BIT5
#define CAP_OPT_EXT_SUPPLY_NOTIFICATION     BIT6
#define CAP_OPT_PD_RESET_NOTIFICATION       BIT7

#define CAP_OPT_GET_PD_MESSAGE              BIT0    //BIT8

// Notification: Table 4-9
#define NT_CMD_COMPLETED                    BIT0  //Required
#define NT_EXT_SUPPLY_CHANGE                BIT1  //Optional
#define NT_POWER_OP_MODE_CHANGE             BIT2  //R
#define NT_SUPPORTED_PROVIDER_CAP_CHANGE    BIT5  //O  1
#define NT_NEGOTIATED_POWER_LV_CHANGE       BIT6  //O  1
#define NT_PD_RESET_COMPLETE                BIT7  //O

#define NT_SUPPORTED_CAM_CHANGE             BIT0  //O Bit8
#define NT_BATTERY_CHARGING_STATUS_CHANGE   BIT1  //R Bit9
#define NT_CONNECTOR_PARTNER_CHANGE         BIT3  //R Bit11
#define NT_POWER_DIRECTION_CHANGE           BIT4  //R Bit12
#define NT_CONNECT_CHANGE                   BIT6  //R Bit14
#define NT_ERROR                            BIT7  //R Bit15

#define _WITHOUT_EVENT                      0
#define _WITH_EVENT                         1

/* Connector Status */
#define MASK_POWER_OP_MODE                  (BIT0+BIT1+BIT2)
#define F_CONNECT_STATUS                    BIT3
#define F_POWER_DIRECTION                   BIT4
#define MASK_PARTNER_FLAG0                  (BIT5+BIT6+BIT7)
#define F_PARTNER_FLAG_USB                  BIT5
#define F_PARTNER_FLAG_ALTERNATE_MODE       BIT6

#define MASK_PARTNER_FLAG1                  (BIT0+BIT1+BIT2+BIT3+BIT4)
#define MASK_PARTNER_TYPE                   (BIT5+BIT6+BIT7)

/* Connector Capability */
#define F_Supports_DFP_Only                 BIT0
#define F_Supports_UFP_Only                 BIT1
#define F_Supports_DRP                      BIT2
#define F_Supports_AnlogAudioAccessMode     BIT3
#define F_Supports_DebugAccessoryMode       BIT4
#define F_Supports_USB_2                    BIT5
#define F_Supports_USB_3                    BIT6
#define F_Supports_Alternate_Mode           BIT7

#define F_Provider                          BIT0    //BIT8
#define F_Consumer                          BIT1    //BIT9

/* Connector Partner Type */
#define CPT_DFP_ATTACHED                    0x01<<5
#define CPT_UFP_ATTACHED                    0x02<<5
#define CPT_POWER_CABLE_NO_UFP_ATTACHED     0x03<<5
#define CPT_POWER_CABLE_UFP_ATTACHED        0x04<<5
#define CPT_DEBUG_ACCESSORY_ATTACHED        0x05<<5
#define CPT_AUDIO_ACCESSORY_ATTACHED        0x06<<5
/* Power Operation Mode */
#define POM_NO_COMSUMER                     0
#define POM_USB_TYPE_C_DEFAULT              1
#define POM_BC                              2
#define POM_PD                              3
#define POM_TYPE_C_CURRENT_1_5A             4
#define POM_TYPE_C_CURRENT_3A               5

/* Battery Charging Status in Connector Status(Byte[8]) */
#define _Not_Charging                       0x00
#define _Normal_Charging                    0x01
#define _Slow_Charging                      0x02
#define _Very_Slow_Charging                 0x03

/*-----------------------------------------------------------------------------
 * ITE Data Type & Data Structure Prototype
 *---------------------------------------------------------------------------*/
enum ucsi_command_code
{
    UCSI_CMD_RESERVED                 = 0x00,
    UCSI_CMD_PPM_RESET                = 0x01,
    UCSI_CMD_CANCEL                   = 0x02,
    UCSI_CMD_CONNECTOR_RESET          = 0x03,
    UCSI_CMD_ACK_CMD_CI               = 0x04,
    UCSI_CMD_SET_NOTIFICATION_ENABLE  = 0x05,
    UCSI_CMD_GET_CAPABILITY           = 0x06,
    UCSI_CMD_GET_CONNECTOR_CAPABILITY = 0x07,
    UCSI_CMD_SET_UOM                  = 0x08,
    UCSI_CMD_SET_UOR                  = 0x09,
    UCSI_CMD_SET_PDM                  = 0x0A,
    UCSI_CMD_SET_PDR                  = 0x0B,
    UCSI_CMD_GET_ALTERNATE_MODES      = 0x0C,
    UCSI_CMD_GET_CAM_SUPPORTED        = 0x0D,
    UCSI_CMD_GET_CURRENT_CAM          = 0x0E,
    UCSI_CMD_SET_NEW_CAM              = 0x0F,
    UCSI_CMD_GET_PDOS                 = 0x10,
    UCSI_CMD_GET_CABLE_PROPERTY       = 0x11,
    UCSI_CMD_GET_CONNECTOR_STATUS     = 0x12,
    UCSI_CMD_GET_ERROR_STATUS         = 0x13,
};

enum ucsi_service_step
{
    _UCSI_PPM_IDLE          = 0x00,
    _UCSI_OPM_MGO_TO_PD     = 0x01,
    _UCSI_OPM_CTRL_TO_PD    = 0x02,
    _UCSI_WAIT_PD_INT       = 0x03,
    _UCSI_READ_PD_MGI       = 0x04,
    _UCSI_READ_PD_CCI       = 0x05,
    _UCSI_NOTIFY_EVENT      = 0x06,
    _UCSI_PD_MGI_TO_OPM     = 0x07,
    _UCSI_PD_CCI_TO_OPM     = 0x08,
};

//*****************************************************************************
/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
//*****************************************************************************
extern void service_ucsi(void);
extern BYTE ECi2cPd1CmdWrite(BYTE PdCmd, XBYTE *DataPointer, BYTE WrLen);
extern BYTE ECi2cPd1CmdRead(BYTE PdCmd, XBYTE *DataPointer, BYTE RdLen);
extern BYTE ECi2cPd2CmdWrite(BYTE PdCmd, XBYTE *DataPointer, BYTE WrLen);
extern BYTE ECi2cPd2CmdRead(BYTE PdCmd, XBYTE *DataPointer, BYTE RdLen);

//-----------------------------------------------------------------------------
#endif  //__UCSI_ITE_H
/*-----------------------------------------------------------------------------
 * End of UCSI_ITE.H */