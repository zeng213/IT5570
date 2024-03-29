/*-----------------------------------------------------------------------------
 * @file     | OEM_INCLUDE.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_INCLUDE.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#ifndef OEM_INCLUDE_H
#define OEM_INCLUDE_H

//----------------------------------------------------------------------------
// OEM Bank0
//----------------------------------------------------------------------------
#include <OEM_GPIO.H>
#include <OEM_PROJECT.H>
#include <OEM_INIT.H>
#include <OEM_MAIN.H>
#include <OEM_LED.H>
#include <OEM_FAN.H>
#include <OEM_BATTERY.H>
#include <OEM_MEMORY.H>
#include <OEM_POWER.H>
#include <OEM_EVENT.H>
#include <OEM_SMBUS.H>
#include <OEM_SCANTABS.H>
#include <OEM_ADC.H>
#include <OEM_MMB.H>
#include <OEM_ACPI.H>
#include <OEM_CIR.H>
#include <OEM_FLASH.H>
#include <OEM_HOSTIF.H>
#include <OEM_6064.H>
#include <OEM_MAILBOX.H>
#include <OEM_VER.H>
#include <OEM_LCD.H>
#include <OEM_PORT686C.H>
#include <OEM_PECI.H>
#include <OEM_PM3.H>
#include <OEM_LPC.H>
#include <OEM_SPI.H>
#include <OEM_IRQ.H>
#include <OEM_PM2.H>
#include <OEM_PS2.H>
#include <OEM_SPI.H>
#include <OEM_LPC.H>
#include <OEM_TIMER.H>
#include <OEM_HSPI.H>
#include <OEM_ASM.H>
#include <OEM_DEBUG.H>
#include <OEM_TIME.H>

//----------------------------------------------------------------------------
// USBC PD - CHIP ITE 
//----------------------------------------------------------------------------
#include <UPDFW_ITE.H>
#include <UCSI_ITE.H>
#include <PD_OEM_ITE.H>
#include <SAR231.h>
#include <NXP.h>
//----------------------------------------------------------------------------
// OEM Bank1
//----------------------------------------------------------------------------
#include <OEM_BANK1_FUNC.H>

//----------------------------------------------------------------------------
// OEM Bank2
//----------------------------------------------------------------------------
#include <OEM_BANK2_FUNC.H>
#include <API_INCLUDE.H>

//----------------------------------------------------------------------------
// OEM Ban3
//----------------------------------------------------------------------------
#include <OEM_BANK3_FUNC.H>

//-----------------------------------------------------------------------------
#endif  //OEM_INCLUDE_H
/*-----------------------------------------------------------------------------
 * End of OEM_INCLUDE.H */