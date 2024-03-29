/*-----------------------------------------------------------------------------
 * @file     | SAR231.H
 *-----------+-----------------------------------------------------------------
 * @function | SAR231.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef SAR231_H
#define SAR231_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * IQS231A REGISTERS FOR MEMORY MAPPING *
 *---------------------------------------------------------------------------*/
#define IQS231A_TEST_ADDR               0x45<<1
#define IQS231A_ADDR                    0x44<<1
#define _SAR_PRODUCT_NUM                0x00 // R
#define _SAR_VERSION_NUM                0x01 // R
#define _SAR_DEBUGGING_EVENTS           0x02 // R
#define _SAR_COMMANDS                   0x04 // R/W
#define _SAR_OTP_1                      0x05
#define _SAR_OTP_2                      0x06
#define _SAR_OTP_3                      0x07
#define _SAR_QUICK_RELEASE              0x08 // R/W
#define _SAR_MOVEMENT                   0x09 // R/W
#define _SAR_TOUCH_THR                  0x0A // R/W
#define _SAR_PROX_THR                   0x0B // R/W
#define _SAR_TEMP_THR                   0x0C // R/W
#define _SAR_CH0_Multi                  0x0D
#define _SAR_CH0_Comp                   0x0E
#define _SAR_CH1_Multi                  0x0F
#define _SAR_CH1_Comp                   0x10

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void SAR_Initial(void);
extern void SAR_Service(void);
extern void SAR_EventTrigger(void);

//-----------------------------------------------------------------------------
#endif  //SAR231_H
/*-----------------------------------------------------------------------------
 * End of SAR231.H */

