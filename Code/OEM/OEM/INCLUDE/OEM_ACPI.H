/*-----------------------------------------------------------------------------
 * @file     | OEM_ACPI.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_ACPI.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_ACPI_H
#define OEM_ACPI_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _SCIEVT_NULL                0x00    //Can't use
#define _SCIEVT_FnF1                0x01    //Hotkey Fn+ F1 Event
#define _SCIEVT_FnF2                0x02    //Hotkey Fn+ F2 Event
#define _SCIEVT_FnF3                0x03    //Hotkey Fn+ F3 Event
#define _SCIEVT_FnF4                0x04    //Hotkey Fn+ F4 Event
#define _SCIEVT_FnF5                0x05    //Hotkey Fn+ F5 Event
#define _SCIEVT_FnF6                0x06    //Hotkey Fn+ F6 Event
#define _SCIEVT_FnF7                0x07    //Hotkey Fn+ F7 Event
#define _SCIEVT_FnF8                0x08    //Hotkey Fn+ F8 Event
#define _SCIEVT_FnF9                0x09    //Hotkey Fn+ F9 Event
#define _SCIEVT_FnF10               0x10    //Hotkey Fn+F10 Event
#define _SCIEVT_FnF11               0x11    //Hotkey Fn+F11 Event
#define _SCIEVT_FnF12               0x12    //Hotkey Fn+F12 Event
#define _SCIEVT_ADAPTER             0x0A    //Adapter status changed
#define _SCIEVT_BATTERY             0x0B    //Battery status changed
#define _SCIEVT_LID_CLOSED          0x0C    //LID closed event
#define _SCIEVT_LID_OPEN            0x0D
#define _SCIEVT_SLEEP               0x0E
#define _SCIEVT_BRIGHTNESS          0x13
#define _SCIEVT_CPU_T               0x20
#define _SCIEVT_SKIN_T              0x21
#define _SCIEVT_CHARGER_T           0x22
#define _SCIEVT_THROT_OFF           0x30
#define _SCIEVT_THROT_LV1           0x31
#define _SCIEVT_THROT_LV2           0x32
#define _SCIEVT_THROT_LV3           0x33
#define _SCIEVT_THROT_LV4           0x34
#define _SCIEVT_THROT_LV5           0x35
#define _SCIEVT_THROT_LV6           0x36
#define _SCIEVT_THROT_LV7           0x37
#define _SCIEVT_CPU_DN_SPEED        0x3B
#define _SCIEVT_CPU_UP_SPEED        0x3C
#define _SCIEVT_CPU_TURBO_OFF       0x3D
#define _SCIEVT_CPU_TURBO_ON        0x3E
#define _SCIEVT_SHUTDOWN            0x3F

#define _SCIEVT_BRIGHTNESS_DN       0x06
#define _SCIEVT_BRIGHTNESS_UP       0x07
#define _SCIEVT_WIRELESS_CTRL       0x08

#define _SCIEVT_PWRBTN              0x54
#define _SCIEVT_PWRBTN_MAKE         0x54
#define _SCIEVT_PWRBTN_BREAK        0x53

#define _SCIEVT_SAR_RELEASE         0x77
#define _SCIEVT_SAR_TRIGGER         0x78
#define _SCIEVT_USBTC               0x79    //USB TYPE C Q EVENT
#define _SCIEVT_USBTC_OUT           0x7A    //USB TYPE C PLUG-OUT EVENT

#define _SCIEVT_VOLUME_UP           0x80
#define _SCIEVT_VOLUME_DOWN         0x81
#define _SCIEVT_WINDOWS_HOME        0x85

#define _SCIEVT_DOCK_IN             0x87
#define _SCIEVT_DOCK_OUT            0x88

//for windows graceful shtudown UI display case
#define _SCIEVT_PWRBTN_LONG_PRESSED         0xD5
#define _SCIEVT_PWRBTN_LONG_PRESSED_RELEASE 0xD6

#define _SCIEVT_TEMP_REPORT         0xF0
#define _SCIEVT_THERMAL_DPTF        0xF1

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Hook_62Port(BYTE PM1_Cmd);
extern void Hook_66Port(BYTE PM1_Cmd);
extern void Hook_ACPICommand(void);

extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);

extern void SCI_EventCenter(void);
extern void ReadSCI_Buffer(void);
extern void WriteSCI_Buffer(BYTE SCI_NUM);
extern void OEM_ACPI_Gen_Int(void);
extern void ResetSCIEvent(void);
extern void CheckShutdownTemp(void);

//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of OEM_ACPI.H */