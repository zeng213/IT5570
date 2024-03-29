/*-----------------------------------------------------------------------------
 * @file     | OEM_LED.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_LED.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 * ----------+---------------------------------------------------------------*/
#ifndef OEM_LED_H
#define OEM_LED_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void OEM_Write_Leds(BYTE data_byte);
extern void Service_LED_Indicator(void);

extern void LED_NotifyHardReset(void);
extern void LED_NotifyForceShutdown(void);
extern void LED_NotifyAbnormalShutodown(void);
extern void LED_NotifyPowerOnFail(void);
//-----------------------------------------------------------------------------
#endif  //OEM_LED_H
/*-----------------------------------------------------------------------------
 * End of OEM_LED.H */