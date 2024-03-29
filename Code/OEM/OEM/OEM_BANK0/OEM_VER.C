/*-----------------------------------------------------------------------------
 * @file     | OEM_Ver.C
 *-----------+-----------------------------------------------------------------
 * @function | Firmware version control
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Kernel Copyright(c)2012, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// Project Information
//-----------------------------------------------------------------------------
const unsigned char code SIGN_MUFG[] = "INTEL ADL N MRD.$";
#if 1   //1: Support Build Date & Time */
const unsigned char code SIGN_DATE[] = {_BUILD_DATE};
const unsigned char code SIGN_TIME[] = {_BUILD_TIME};
#endif
#if 0
const unsigned char code SIGN_MODL[] = {_BUILD_MODEL};
const unsigned char code SIGN_GUST[] = {_BUILD_GUEST};
const unsigned char code SIGN_PCBV[] = {_BUILD_BOARD};
#endif
const unsigned char code SIGN_ECVR[] = {_BUILD_ECVER};

//-----------------------------------------------------------------------------
void Reload_EC_Ver(void)
{
    xEC_MainVersion = _EC_MAIN_VERSION;
    xEC_SubVersion = _EC_SUB_VERSION;
    xEC_TestVersion = _EC_TEST_VERSION;

}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_Ver.C */
