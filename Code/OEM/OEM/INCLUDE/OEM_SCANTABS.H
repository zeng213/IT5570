/*-----------------------------------------------------------------------------
 * @file     | OEM_SCANTABS.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_SCANTABS.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_SCANTABS_H
#define OEM_SCANTABS_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _KBSET2_VOL_UP              0x32
#define _KBSET2_VOL_DN              0x21
#define _Windows_Key            0x1F

#define _KBSET2_P               0x4D
/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
const BYTE code ADL_P_Rc_ROM_Tables[];
const BYTE code KB_S3WakeUP_Tables[];
const BYTE code EtKey_S3WakeUP_Tables[];
const FUNCT_PTR_V_B code HotKey_Fn_Fx[];

extern void Hook_Setup_Scanner_Pntr(void);
extern void Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Hook_SetGPIOScanPinH(void);
extern void Hook_SetGPIOScanPinL(void);
extern void Hook_SetGPIOScanPinCtrl(void);
extern void OEM_Hook_Send_Key(BYTE table_entry, BYTE event);
extern BYTE OEM_Hook_Skip_Send_Key(void);
extern void Hook_Fn_Key_Make(void);
extern void Hook_Fn_Key_Break(void);
extern BYTE Hook_calc_index_comb_BIT6(void);
extern BYTE Hook_calc_index_comb_BIT7(void);
extern void Hook_scan_activity(void);

//-----------------------------------------------------------------------------
#endif  //OEM_SCANTABS_H
/*-----------------------------------------------------------------------------
 * End of OEM_SCANTABS.H */