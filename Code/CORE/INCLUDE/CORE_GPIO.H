/*-----------------------------------------------------------------------------
 * @file     | CORE_GPIO.H
 *-----------+-----------------------------------------------------------------
 * @function | CORE_GPIO.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2010-2016, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef CORE_GPIO_H
#define CORE_GPIO_H


//-----------------------------------------------------------------------------
// GPIO Control Definition
//-----------------------------------------------------------------------------
#define ALT       		0x00
#define INPUT        	0x80
#define OUTPUT     		0x40
#define PULL_UP       	0x04
#define PULL_DW        	0x02
#define PULL_DN        	0x02
#define MaxD    		0x38

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EGPC MODULE ***************************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*ExternalGPIO_8302.24pin*/
#define TMB         5   // Transmitted Data Bits (n+1)
#define CDIE        0   // Cycle Done Interrupt 0-> disable, 1->Enable
#define CREN        1   // Channel Ready Enable
#define EGPC_CTRL   ((TMB<<2) + (CDIE<<1) + CREN)

#define EGPC_ID0            0x00
#define EGPC_ID1            0x01
#define EGPC_ID2            0x02
#define EGPC_IN             0x00
#define EGPC_OUT            0x02
#define EGPC_PULL_UP        0x04
#define EGPC_PULL_DN        0x08
#define EGPC_PUSH_PULL      0x00
#define EGPC_OPEN_DRAIN     0x10
#define _HIGH				1
#define _LOW				0
#define CDS					BIT(0)

#define GPIO04  (0x04<<2)   // Pin06
#define GPIO05  (0x05<<2)   // Pin07
#define GPIO07  (0x07<<2)   // Pin08
#define GPIO09  (0x09<<2)   // Pin09
#define GPIO11  (0x0B<<2)   // Pin10
#define GPIO13  (0x0D<<2)   // Pin11
#define GPIO18  (0x12<<2)   // Pin14
#define GPIO20  (0x14<<2)   // Pin15
#define GPIO22  (0x16<<2)   // Pin16
#define GPIO24  (0x18<<2)   // Pin17
#define GPIO26  (0x1A<<2)   // Pin18
#define GPIO27  (0x1B<<2)   // Pin19
#define GPIO29  (0x1D<<2)   // Pin20
#define GPIO31  (0x1F<<2)   // Pin21
#define GPIO33  (0x21<<2)   // Pin22
#define GPIO35  (0x23<<2)   // Pin23
//-----------------------------------------------------------------------------
#endif  //CORE_GPIO
/*-----------------------------------------------------------------------------
 * End of CORE_GPIO.H */