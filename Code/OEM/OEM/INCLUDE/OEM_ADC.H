/*-----------------------------------------------------------------------------
 * @file     | OEM_ADC.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_ADC.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_ADC_H
#define OEM_ADC_H

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
extern void Service_Scan_ADC(void);
extern void Get_ADC0_Thermistor(void);
extern void Get_ADC1_Thermistor(void);
extern BYTE Get_ADC_CH3(void);
extern void Get_ADC4_Thermistor(void);

extern void Intel_DPTF_Set_TSHT(void);
extern void Intel_DPTF_Set_TSLT(void);

//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of OEM_ADC.H */