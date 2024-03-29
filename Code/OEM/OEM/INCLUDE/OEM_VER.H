/*-----------------------------------------------------------------------------
 * @file     | OEM_VER.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_VER.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_VER_H
#define OEM_VER_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/
extern const unsigned char code SIGN_MUFG[];
extern const unsigned char code SIGN_DATE[];
extern const unsigned char code SIGN_MODL[];
extern const unsigned char code SIGN_GUST[];
extern const unsigned char code SIGN_PCBV[];
extern const unsigned char code SIGN_ECVR[];
extern const unsigned char code ECVER[];

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Reload_EC_Ver(void);

//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of OEM_VER.H */