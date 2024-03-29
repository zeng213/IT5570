/*-----------------------------------------------------------------------------
 * @file     | CORE_ITESTRING.C
 * ----------+-----------------------------------------------------------------
 * @function | To occupy code space 0x40 - 0x6F
 *           | 0x40 - 0x4F is 16B-Signature
 * ----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2019, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
/* Notice: Only one "TRUE" accept */
#define ITE_CHIP_IT557x_eSPI_MIRROR     TRUE
#define ITE_CHIP_IT557x_eSPI_NoMIRROR   FALSE
#define ITE_CHIP_IT557x_LPC_MIRROR      FALSE
#define ITE_CHIP_IT557x_LPC_NoMIRROR    FALSE
//#define ITE_CHIP_IT8991_eSPI_MIRROR     FALSE
//#define ITE_CHIP_IT8991_eSPI_NoMIRROR   FALSE
//#define ITE_CHIP_IT8991_MIRROR          FALSE
//#define ITE_CHIP_IT8991_NoMIRROR        FALSE
//#define ITE_CHIP_IT8110_MIRROR          FALSE
//#define ITE_CHIP_IT8110_NoMIRROR        FALSE
#define ITE_CHIP_IT851X_IT852X          FALSE

/*-----------------------------------------------------------------------------
 * @subroutine - ITEString
 * @function - Rom Table for ITE chip configuration
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const unsigned char code ITEString[] =
{
#if ITE_CHIP_IT557x_eSPI_MIRROR
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA4, 0x95, //For IT557xE eSPI Mirror
    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x7F, 0x55, 0x55,
#endif

#if ITE_CHIP_IT557x_eSPI_NoMIRROR
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA4, 0x95, //For IT557xE eSPI Non-Mirror
    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x00, 0x55, 0x55,
#endif
#if ITE_CHIP_IT557x_LPC_MIRROR
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x95, //For IT557xE LPC Mirror
    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x7F, 0x55, 0x55,
#endif

#if ITE_CHIP_IT557x_LPC_NoMIRROR
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x95, //For IT557xE LPC Non-Mirror
    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x00, 0x55, 0x55,
#endif
//#if ITE_CHIP_IT8991_eSPI_MIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA4, 0x95, //For IT8991E eSPI Mirror
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x7F, 0x55, 0x55,
//#endif
//
//#if ITE_CHIP_IT8991_eSPI_NoMIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA4, 0x95, //For IT8991E eSPI Non-Mirror
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x00, 0x55, 0x55,
//#endif
//
//#if ITE_CHIP_IT8991_MIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x95,
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x7F, 0x55, 0x55, //For IT8991E Mirror
//#endif
//
//#if ITE_CHIP_IT8991_NoMIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xB5,
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x00, 0x55, 0x55, //For IT8991E Non-Mirror
//#endif
//
//#if ITE_CHIP_IT8110_MIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x94,
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x7F, 0x55, 0x55, //For IT8110E Mirror
//#endif
//
//#if ITE_CHIP_IT8110_NoMIRROR
//    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x94,
//    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0x00, 0x55, 0x55, //For IT8110E Non-Mirror
//#endif

#if ITE_CHIP_IT851X_IT852X
    /* IT8518E/IT8528E/IT8527E... */
    0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,EC_SIGNATURE_FLAG,
    0x85, 0x12, 0x5A, 0x5A, 0xAA, 0xAA, 0x55, 0x55,
#endif
};
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - VersionString
 * @function - Rom Table for Kernel version
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
const unsigned char code VersionString[] =  "ITE EC-V14.6   ";
/*-----------------------------------------------------------------------------
HW Load code:
1. H/W Strapping: GPG2 (pin 100) pull high. (GPG2 can・t be floating.)
2. 16 Byte Signature:
1st 2nd 3rd 4th 5th 6th 7th 8th 9th 10th 11th 12th 13th 14th 15th 16th
A5h A5h A5h A5h A5h A5h A5h flag 85h 12h 5Ah  5Ah  AAh  cmp  55h  55h
7th byte・s bit 0:
    1b: LPC Bus.
    0b: eSPI Bus.
8th byte・s bit 7:
    1b: Disable.
    0b: Enable PWM blinking during hardware started mirror sequence.
8th byte・s bit 6:
    0b: Disable.
    1b: Suspend internal-to-external clock switching request.
        When this bit is set, the internal clock would act as a temporary
        clock to enable EC to configure some GPIO setting
        before the external crystal is ready to work.
        This bit is available only when the 8th byte・s bit 4 is 0.
        Refer to section 0 on page.
8th byte・s bit 5:
    1b: Disable
    14th byte must be AAh.
    0b: Enable FSPI I/F and mirror function.
8th byte・s bit 4:
    0b: 32.768 kHz is oscillated by the external crystal connected to
        CK32K and CK32KE pins.
    1b: The：Crystal-Free； feature is enabled and 32.768kHz is from the
        internal clock generator.
8th byte・s bit 3:
    0b: Use implicit format to describe the EC code base and the
        16B-signature must be inside the EC code.
        15th and 16th byte must be 55h and 55h and the EC code base
        is located at the origin of this 4K block of 16B-signature.
        For example, let the address of 1st byte be ADDR1[23:0],
        then the EC code base is loated at
        (ADDR1[23:12] * 2^12).
    1b: Use explicit format to describe the EC code base and the
        16B-signature must be outside the EC code.
        15th byte indicates the EC code base address bit 23-16.
        16th byte indicates the EC code base address bit 15-12.
8th byte・s bit 2:
    1b: Don・t check the CRC-16 after mirror
    11th and 12th byte must be 5Ah and 5Ah.
    0b: Check the CRC-16 after mirror and uC halt if CRC is corrupted.
    11th byte indicates the expected high byte of CRC-16 after mirror
         code from SPI flash to eflash.
    12th byte indicates the expected low byte of CRC-16 after mirror
        code from SPI flash to eflash.
    The CRC-16 calculate except 16B-signature.
8th byte・s bit 1:
    It must be 0b.
8th byte・s bit 0:
    0b: Blinking on PWM0 if b7 = 0
    1b: Blinking on PWM1 if b7 = 0
    1st byte must be located at 16-byte boundary.
        For example, let the address of 1st byte be ADDR1[23:0],
        then ADDR1[3:0] must be 0000b.
    14st byte indicates the compared range ADDR [17:10] between
         e-flash and SPI flash. The compared range is up to
    128K-byte and is multiple of 1K-byte. ADDR[17] must be 0b.
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Flash Control Register 3 (FLHCTRL3R)
Address Offset:1063h
Bit R/W Default Description
7 R/WC 0b Last Compare mismatch
    0b: Otherwise
    1b: Mirror code occur mismatch
6 R/W 0b Mirror code with full 128k
    0b: Disable
    1b: Start auto load code with full 128k
5 R/W 0b Mirror code with specified range
    0b: Disable
    1b: Start Mirror code with specified range.
4 R/W 0b Mirror code after WDT
    0b: Otherwise
    1b: Start Mirror code to Eflash after WDT Reset.
3 R/W 0b FSPI I/F Enable (FIFE)
    0b: Otherwise
    1b: Enable FSPI
2 - - Reserved
1 - - Reserved
0 R/W 0b Force FSPI I/F Tri-state (FFSPITRI)
    1: FSCK/FSCE#/FMISO/FMOSI are tri-state.
    0: FSCK/FSCE#/FMISO/FMOSI are normal operation.
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *  End of CORE_ITESTRING.C */