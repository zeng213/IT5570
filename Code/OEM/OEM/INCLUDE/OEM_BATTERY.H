/*-----------------------------------------------------------------------------
 * @file     | OEM_BATTERY.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_BATTERY.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_BATTERY_H
#define OEM_BATTERY_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _SMB_BATT1_ADDR         0x16    // Smart Battery
#define _SMB_CHGRA_ADDR         0x12    // Smart Charger

#define CHARGING_STOP_NO_ERROR              0x00
#define CHARGING_STOP_NO_BATTERY            (BIT0)
#define CHARGING_STOP_FULL                  (BIT1)
#define CHARGING_STOP_FULL_PROTECTION       (BIT2)
#define CHARGING_STOP_NO_POWER_SOURCE       (BIT3)
#define CHARGING_STOP_NO_ENOUGH_POWER       (BIT4)
#define CHARGING_STOP_TEMP_OUT_OF_RANGE     (BIT5)
#define CHARGING_STOP_BAT_ALARM             (BIT6)
#define CHARGING_STOP_DEAD_BAT              (BIT7)

#define LOW_BATTERY_VOLTAGE                 (6800)
#define FORCE_SHUTODOWN_BATTERY_VOLTAGE     (11500)
#define PRECHARGE_BATTERY_VOLTAGE           (9000)
#define DEAD_BATTERY_VOLTAGE                (1000)
/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void PollSmartBattery(void);
extern void PollSmartCharger(void);
extern void Init_SmartCharger(void);

extern void Adapter_Detection(void);
extern void Battery_Detection(void);

extern void Update_ACPI_BIF1(void);
extern void Update_ACPI_BST1(void);
extern void Update_ACPI_Battery(void);
extern void SCI_PowerEvent(void);
extern void ADP_Control(void);

extern void Charger_Hook1SecTimer(void);

extern void CheckForceShutdownByBatteryVoltage(void);
extern void SetCharger_FastCharging(void);
extern void SetCharger_NormalCharging(void);
extern void SetCharger_StopCharging(void);

/* INTEL_SMARTCHARGING_PHASE1 */
extern BYTE Charging_CheckTimeRange(void);


//-----------------------------------------------------------------------------
#endif  //OEM_BATTERY_H
/*-----------------------------------------------------------------------------
 * End of OEM_BATTERY.H */