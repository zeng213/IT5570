/*-----------------------------------------------------------------------------
 * @file     | OEM_EVENT.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_EVENT.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_EVENT_H
#define OEM_EVENT_H

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
extern void Process_LID_Switch(void);
extern void Service_Key_BackLight(void);
extern void Key_BackLight_Off(void);
extern void Key_BackLight_On(void);
extern void Service_DPTF_Event(void);
extern void Service_GPI_Event(void);
extern void Service_DOCK_Event(void);
//-----------------------------------------------------------------------------
#endif  //OEM_EVENT_H
/*-----------------------------------------------------------------------------
 * End of OEM_EVENT.H */