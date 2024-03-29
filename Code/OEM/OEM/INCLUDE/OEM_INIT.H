/*-----------------------------------------------------------------------------
 * @file     | OEM_INIT.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_INIT.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_INIT_H
#define OEM_INIT_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct REG_INIT_DEF
{
    XBYTE   *address;
    BYTE    initdata;
} sREG_INIT_DEF;
//-----------------------------------------------------------------------------
typedef struct DMAScratchSRAM
{
    XBYTE   *scarh;
    XBYTE   *scarm;
    XBYTE   *scarl;
} sDMAScratchSRAM;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Oem_StartUp(void);
extern void Oem_Initialization(void);
extern void Init_ClearRam(void);
extern void CacheDma(BYTE sramnum, WORD addr);
extern void Init_Cache(void);
extern void Hook_ECExitFollowMode(void);
extern BYTE Hook_ECRetunrMainFuncKeepCondition(void);
extern void Init_ADC(void);

//-----------------------------------------------------------------------------
#endif  //OEM_INIT_H
/*-----------------------------------------------------------------------------
 * End of OEM_INIT.H */
