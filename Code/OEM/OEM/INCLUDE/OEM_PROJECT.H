/*-----------------------------------------------------------------------------
 * @file     | OEM_PROJECT.H
 * ----------+-----------------------------------------------------------------
 * @function | Project function selection.
 * ----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_PROJECT_H
#define OEM_PROJECT_H

//*****************************************************************************
/* EC Firmware OEM Version */
//*****************************************************************************
#define _EC_MAIN_VERSION            0x00
#define _EC_SUB_VERSION             0x29
#ifdef _SUPPORT_BATT_FAKE_INFO_
#define _EC_TEST_VERSION            0xFF
#define _BUILD_ECVER                "VER:0.29.FF"
#else
#define _EC_TEST_VERSION            0x00
#define _BUILD_ECVER                "VER:0.29.00"
#endif
//*****************************************************************************
/* OEM Configuration */
//*****************************************************************************
#define SUPPORT_PECI                TRUE
#define SUPPORT_LID_SWITCH          TRUE
#define SUPPORT_FAN1_CONTROL        FALSE
#define SUPPORT_FAN1_TACH           FALSE
#define SUPPORT_FAN1_CALIBRATION    FALSE
#define SUPPORT_SMART_BATTERY       TRUE
#define SUPPORT_SMART_CHARGER       TRUE
#define SUPPORT_UART_BATT_MONITOR   FALSE
#define SUPPORT_ACPI_BATT_MWH       TRUE    //TRUE: For Intel Lab Only
#define SUPPORT_BATTERY_IN          TRUE
#define SUPPORT_BATTERY_SMBA        FALSE   //FALSE: Battery conn.to SMBus-B
#define SUPPORT_BATTERY_FASTCHARGE  TRUE
#define SUPPORT_WINAPP_ITE_RFDU     TRUE    //TRUE: Support WinApp ITE_RFDU 
#define SUPPORT_PD_CHIP_ITE         TRUE    
#define SUPPORT_PD_PORT2_ITE        TRUE
#define SUPPORT_PD_CHIP_FLASH_ITE   TRUE
#define SUPPORT_UCSI                TRUE    //UCSI Function
#define SUPPORT_PD_SINK_CONTROL_ITE FALSE
#define SUPPORT_SAR_TEST_MODE       FALSE 
#define SUPPORT_SAR_EVENT_TRIGGER   TRUE 
#define SUPPORT_SINK_SOURCE_SWITCH  FALSE 
#define SUPPORT_UCSI_NO_E0_CMD      TRUE
#define SUPPORT_BATT_S5_EC_SLEEP    FALSE
#define SUPPORT_AUTO_BOOT           TRUE
#define SUPPORT_DOCK_EVENT_TRIGGER  TRUE
#define INTEL_EC_FLASH_AUTO_POWER_ON    TRUE

#define INTEL_SMARTCHARGING_PHASE1  FALSE   //TRUE: Intel Lab Test Function
#define _PD_INT_OOB_DELAY           40


//*****************************************************************************
/* CHIP LEVEL CONFIGURATION */
//*****************************************************************************
#define ITE_CHIP_IT557X             TRUE
#define ITE_eSPI_LOW_FREQUENCY      FALSE   // TRUE: For Bring Up, LA Analyzer
#define SUPPORT_INTERFACE_eSPI      TRUE
#define ITE_eSPI_SAFS_MODE          FALSE
#define SUPPORT_FORCE_SPI_32MB      TRUE
#define eSPI_RESET_FOR_DSW_PWROK    TRUE    // TRUE: eSPI with None-DeepSx
#define SUPPORT_EN_VW_ACK_BOOT_LOAD FALSE   // TRUE: Boot Ack after VW enable
#define SUPPORT_LPC_BUS_1_8V        TRUE    // TRUE: Setting LPC Bus 1.8V
#define SUPPORT_MIRROR_ONCE         TRUE
#define SHARED_BIOS_TRI_STATE       TRUE
#define SUPPORT_PORT_I2EC           FALSE
#define SUPPORT_PWRSW_RESET         TRUE   // GPB.3
#define EC_SIGNATURE_FLAG           0xB5    // For 8518 crystal free
#define SUPPORT_OOB_CRASHLOG        TRUE
#define SUPPORT_OOB_CRASHLOG_KEY    FALSE
#define _OOB_CRASHLOG_LOCK_TIMER    8
#define SUPPORT_SW_MIRROR           TRUE

//*****************************************************************************
/* ITE EC KERNEL CODE FUNCTION SETTING */
//*****************************************************************************
#define SUPPORT_CORE_FLAH_API       TRUE
#define SUPPORT_SMBUS_E_F           TRUE
#define SUPPORT_CHECK_SMBUS_CAN_USE FALSE
#define REMOVE_CORE_INIT_SIO        FALSE
#define SUPPORT_FLASH_OFF_SEQUENCE  FALSE
#define SUPPORT_HOOK_WARMBOOT       TRUE
#define SUPPORT_SERVICE_PS2         FALSE   // TRUE: Support PS/2 devices
#define SUPPORT_REPEAT_CTRL_EFFECT  FALSE
#define SUPPORT_MODERN_STANDBY      TRUE
#define SUPPORT_S0_ATHENA_IDLE      FALSE
#define ENABLE_INT154_QUICK_CTRL	TRUE
#define UART1_DEBUG                 FALSE
#define UART2_DEBUG                 TRUE

//*****************************************************************************
/* PS2 interface */
//*****************************************************************************
/* Note: If TouchPad_only is set, remeber to call
         PowerOffClearTPPendingData() function in power off sequnce
         include (S3, S4, and S5)¡C
*/
#define TouchPad_only           TRUE    // TRUE : Only PS/2 touch pad device
#define Hook_ECACKMouseDriver
#define SUPPORT_PS2_VIRTUAL     FALSE

//*****************************************************************************
/* Switch to Switch */
//*****************************************************************************
#if TouchPad_only
#define MultiplexedModes        FALSE   // FALSE: Doesn't support multiplexed
//        modes.
#define PS2IFHotPlugHotSwap     FALSE   // FALSE: Support PS2 interface
//        hot-plug, hot-swap
//#define Hook_Func_DisableTP   // Support "Hook_DisableInternalTB" for
// EC on/off touchpad
#else
#define MultiplexedModes        TRUE    // TRUE: Support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // TRUE: Support PS2 interface
//       hot-plug, hot-swap
#endif

//*****************************************************************************
/* Keyboard scan */
//*****************************************************************************
#define KB_FnStickKey           FALSE   // TRUE: for Fn stick key function
//#define KB_HW_KeyScan                 // To support hardward keyscan


//*****************************************************************************
// UART debug interface
// Timer 2 baudrate IT557x
//*****************************************************************************
//#define MCU_UART_Debug        // Define : enable MCU Tx debug (GPIO E6)

#ifdef MCU_UART_Debug
#define R2HV                    0xFF
#define R2LV                    0xFB  //9600 bps
#endif

//*****************************************************************************
/* Power ON/ Force Shutdown Configuration */
//*****************************************************************************
#define FORCE_SHUTDOWN_TIME_IN_NON_ACPI                     (4000) //ms
#define FORCE_SHUTDOWN_TIME_IN_S3                           (4000) //ms
#define FORCE_SHUTDOWN_TIME_IN_POW_SEQ                      (4000) //ms


#define PWRBTN_LONG_PRESS_TRIGGER_TIME_ACPI_MODE            (500)  //ms
#define FORCE_SHUTDOWN_TRIGGER_TIME_BY_PWRBTN_ACPI_MODE     (2000) //ms
#define FORCE_SHUTDOWN_TIME_BY_PWRBTN_ACPI_MODE             (8000) //ms

#define PWRBTN_PWR_ON_DELAY_TIME                            (200) //ms

#define PWRLATCH_OFF_DETECT_DELAY                           10 //seconds

#define FORCE_SHUTDOWN_PWR_BTN_PRESSED_CHECK_TIME           (3900) //ms

//DNX hotkey scan code
#define COMBINE_KEY_ENTER_DNX  0x23
//-----------------------------------------------------------------------------
#endif  //OEM_PROJECT_H
/*-----------------------------------------------------------------------------
 * End of OEM_PROJECT.H */
