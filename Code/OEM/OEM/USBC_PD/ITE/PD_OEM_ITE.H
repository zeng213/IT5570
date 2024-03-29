/*-----------------------------------------------------------------------------
 * @file     | PD_OEM_ITE.H
 *-----------+-----------------------------------------------------------------
 * @function | PD_OEM_ITE.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2021, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef _PD_OEM_ITE_H
#define _PD_OEM_ITE_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define IF_PD1_INTR_ACTIVE()     IS_MASK_CLEAR(GPDMRC, BIT(3))
#define IF_PD2_INTR_ACTIVE()     IS_MASK_CLEAR(GPDMRB, BIT(6))


#define SINK_CONTROL_ON          1
#define SINK_CONTROL_OFF         0
/*-----------------------------------------------------------------------------
 * Data Type & Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void service_pd_register(void);
extern void clear_pd1_chip_event(BYTE ClrEvt);
extern void clear_pd2_chip_event(BYTE ClrEvt);
extern void SendSystemStatusToPD1(BYTE SysStatus);
extern void SendSystemStatusToPD2(BYTE SysStatus);
extern void SendSystemACPIToPD1(void);
extern void SendSystemACPIToPD2(void);
extern void SinkSwitchControlPD1(BYTE Onoff);
extern void SinkSwitchControlPD2(BYTE Onoff);
BYTE EnterPD1ComplianceMode(void);
BYTE EnterPD2ComplianceMode(void);
void EnterRetimerFwUpdate(void);
void ExitRetimerFwUpdate(void);
//-----------------------------------------------------------------------------
#endif  //_PD_OEM_ITE_H
/*-----------------------------------------------------------------------------
 * End of PD_OEM_ITE.H */