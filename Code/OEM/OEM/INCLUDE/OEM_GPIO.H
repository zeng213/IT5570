/*-----------------------------------------------------------------------------
* @file     | OEM_GPIO.H
*-----------+-----------------------------------------------------------------
* @function | OEM_GPIO.C Function prototype include definition
*-----------+-----------------------------------------------------------------
* @model    | ITE Embedded Controller Firmware
* @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
* @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
* @note     | Copyright(c)2012-2020, ITE Tech. Inc. All rights reserved.
*---------------------------------------------------------------------------*/
#ifndef OEM_GPIO_H
#define OEM_GPIO_H
#include  <OEM_PROJECT.H>
/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
//PROJECT: INTEL

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Registers Definition
//-----------------------------------------------------------------------------
//*****************************************************************************
//-----------------------------------------------------------------------------
/* General Control Register (GCR)
 * BIT7     - GPIOB5 HIGH Follow LPCRST# HIGH-to-LOW
 * BIT[2:1] - [01] LPCRST# in GPIOB7
 *            [10] LPCRST# in GPIOD2
 *            [11] LPCRST# is disabled
 */
#define GCR_Init        0x04

//-----------------------------------------------------------------------------
/* General Control 1 Register (GCR1)
 * BIT6     - Support SSPI BUSY Pin (SSSPIBP)
 * BIT[5:4] - SPI Control (SPICTRL)
 * BIT[3:2] - UART2 Control (U2CTRL)
 * BIT[1:0] - UART1 Control (U1CTRL)
 */
#define GCR1_Init       0x00

//-----------------------------------------------------------------------------
/* General Control 2 Register (GCR2)
 * BIT7 - TACH2A Enable (TACH2AEN),        BIT6 - CK32K Out Enable (CK32OE)
 * BIT5 - SMBus Channel 3 Enable (SMB3EN), BIT4 - PECI Enable (PECIE)
 * BIT3 - TMB1 Enabled (TMB1EN),           BIT2 - TMB0 Enabled (TMB0EN)
 * BIT1 - TMA1 Enabled (TMA1EN),           BIT0 - TMA0 Enabled (TMA0EN)
 */
#define GCR2_Init       0x10

//-----------------------------------------------------------------------------
/* General Control 6 Register (GCR6)
 * BIT5 - Power Good Watch Pin Select (PGWPSEL),
 * BIT3 - UART SOUT1 Enable (SOUT1EN), BIT2 - UART SIN1 Enable (SIN1EN)
 * BIT1 - UART SOUT0 Enable (SOUT0EN), BIT0 - UART SIN0 Enable (SIN0EN)
 */
#define GCR6_Init       0x00

//-----------------------------------------------------------------------------
/* General Control 15 Register (GCR15)
 * BIT5 - SMBus Channel 5 Enable (SMB5EN),
 * BIT4 - SMBus Channel 4 Enable (SMB4EN),
 * BIT3 - TACH2B Enable (TACH2BEN),
 * BIT2 - Comparator 2 GPIO Enable (CMP2GPEN)
 * BIT1 - Comparator 1 GPIO Enable (CMP1GPEN),
 * BIT0 - Comparator 0 GPIO Enable (CMP0GPEN)
 */
#define GCR15_Init      0x00

//-----------------------------------------------------------------------------
/* General Control 19 Register (GCR19) Chip: IT8991E/IT8928E/VG/IT557X
 * BIT7:GPB5, BIT6:GPB6, BIT5:GPC1, BIT4:GPC2
 * BIT3:GPC7, BIT2:GPD0, BIT1:GPD1, BIT0:GPD2
 * Input Voltage Selection 0b:3.3V, 1b:1.8V, *Do not enable internal pull-up
 */
#define GCR19_Init      0x01

//-----------------------------------------------------------------------------
/* General Control 20 Register (GCR20)(16E5) Chip: IIT8991E/T8928E/VG/IT557X
 * BIT7:GPD3, BIT6:GPD4, BIT5:GPE0, BIT4:GPE6
 * BIT3:GPE7, BIT2:GPF2, BIT1:GPF3, BIT0:GPF4
 * Input Voltage Selection 0b:3.3V, 1b:1.8V, *Do not enable internal pull-up
 */
#define GCR20_Init      0x00

//-----------------------------------------------------------------------------
/* General Control 21 Register (GCR21) Chip: IT8991E/IT8928E/VG/IT557X
 * BIT7:GPF5, BIT6:GPF6, BIT5:GPF7, BIT4:GPG1
 * BIT3:GPG6, BIT2:GPH0, BIT1:GPH1, BIT0:GPH2
 * Input Voltage Selection 0b:3.3V, 1b:1.8V, *Do not enable internal pull-up
 */
#define GCR21_Init      0x00

//-----------------------------------------------------------------------------
/* General Control 22 Register (GCR22) Chip: IT8991E/IT8928E/VG/IT557X
 * BIT7-VCC Power Domain Select (VCCPDS) (1: eSPI/LPC = 1.8V)
 * BIT3:GPA4, BIT2:GPA5, BIT1:GPB3, BIT0:GPB4
 * Input Voltage Selection 0b:3.3V, 1b:1.8V, *Do not enable internal pull-up
 */
#define GCR22_Init      0x80

//-----------------------------------------------------------------------------
/* General Control 23 Register (GCR23) Chip: IT8991E/IT8928E/VG/IT557X
 * BIT0 - GPM6 Power Domain Select (GPM6PDS)
 *        0b: ALERT#/SERIRQ/GPM6 is supplied by VFSPI.
 *        1b: ALERT#/SERIRQ/GPM6 is supplied by VCC.
 */
#define GCR23_Init      0x01

//*****************************************************************************
//-----------------------------------------------------------------------------
// PROJECT: ADL_N, IT5570VG
//-----------------------------------------------------------------------------
//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port A Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortA_Init      0x09            // PORT Data

#define PortA0_Ctrl     OUTPUT          // LED_PWR 
#define PortA1_Ctrl     INPUT           // Set input for SMT OUTPUT          // TCP0_RT_USB_EN_EC (1.8V Output, set to OD)
#define PortA2_Ctrl     OUTPUT          // VCCST_PWRGD_OUT_EC
#define PortA3_Ctrl     OUTPUT          // LED_CHG
#define PortA4_Ctrl     INPUT           // CHG_ACOK_D
#define PortA5_Ctrl     INPUT           // NFC_ERR
#define PortA6_Ctrl     INPUT           // SUSCLK_EC
#define PortA7_Ctrl     INPUT           // NFC_I2C_INT
//----------------------------------------
#define GPOTA_Init      0x0C            // Out Type: 0:Push-pull, 1:Open-drain
//#define GPOTA_Init      0x06            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------

#define IS_LED_PWR_N_ON()           IS_MASK_CLEAR(GPDRA, BIT(0))
#define IS_LED_PWR_N_OFF()          IS_MASK_SET(GPDRA, BIT(0))
#define LED_PWR_N_ON()              CLEAR_MASK(GPDRA, BIT(0))
#define LED_PWR_N_OFF()             SET_MASK(GPDRA, BIT(0))


#define TCP0_RT_USB_EN_EC_HI()      SET_MASK(GPDRA, BIT(1))
#define TCP0_RT_USB_EN_EC_LO()      CLEAR_MASK(GPDRA, BIT(1))

// #define IS_KB_BKLT_EN_HI()          IS_MASK_SET(GPDRA, BIT(1))
// #define IS_KB_BKLT_EN_LO()          IS_MASK_CLEAR(GPDRA, BIT(1))
// #define KB_BKLT_PWM_DCR             DCR1
// #define KB_BKLT_GPCR                GPCRA1

#define VCCST_PWRGD_OUT_EC_HI()     SET_MASK(GPDRA, BIT(2))
#define VCCST_PWRGD_OUT_EC_LO()     CLEAR_MASK(GPDRA, BIT(2))

#define IS_LED_CHG_ON()             IS_MASK_CLEAR(GPDRA, BIT(3))
#define IS_LED_CHG_OFF()            IS_MASK_SET(GPDRA, BIT(3))
#define LED_CHG_ON()                CLEAR_MASK(GPDRA, BIT(3))
#define LED_CHG_OFF()               SET_MASK(GPDRA, BIT(3))

#define IS_ADAPTER_IN()             IS_MASK_SET(GPDRA, BIT(4))
#define IS_ADAPTER_OUT()            IS_MASK_CLEAR(GPDRA, BIT(4))
//#define IS_ADAPTER_IN()           IS_MASK_SET(PowerSource, F_AC_ON_LINE)
//#define IS_ADAPTER_OUT()          IS_MASK_CLEAR(PowerSource, F_AC_ON_LINE)
#define IS_CHG_ACOK_HI()            IS_MASK_SET(GPDRA, BIT(4))
#define IS_CHG_ACOK_LO()            IS_MASK_CLEAR(GPDRA, BIT(4))

#define IS_ADP_PRESENT_HI()         IS_ADAPTER_IN()                 // Need to check after SMT
#define IS_ADP_PRESENT_LO()         IS_ADAPTER_OUT()                // Need to check after SMT

#define IS_NFC_ERR_HI()             IS_MASK_SET(GPDRA, BIT(5))
#define IS_NFC_ERR_LO()             IS_MASK_CLEAR(GPDRA, BIT(5))

#define IS_SUSCLK_EC_DN()           IS_MASK_CLEAR(GPDRA, BIT(6))
#define IS_SUSCLK_EC_UP()           IS_MASK_SET(GPDRA, BIT(6))

#define IS_NFC_I2C_INT_HI()         IS_MASK_SET(GPDRA, BIT(7))
#define IS_NFC_I2C_INT_LO()         IS_MASK_CLEAR(GPDRA, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortB_Init      0x00            // PORT Data

#define PortB0_Ctrl     INPUT           // BRD_ID1
#define PortB1_Ctrl     INPUT           // BRD_ID2
#define PortB2_Ctrl     INPUT           // set to input for SMT // OUTPUT // TCPC_P0_SNK_PWRGD
#define PortB3_Ctrl     INPUT           // KB_PWRBTN_EC
#define PortB4_Ctrl     INPUT           // NC
#define PortB5_Ctrl     OUTPUT          // SYS_PWROK
#define PortB6_Ctrl     INPUT           // PD_1_EC_SMBUS1_ALERT_0_N
#define PortB7_Ctrl     INPUT           //
//----------------------------------------
// #define GPOTB_Init      0x04            // Out Type: 0:Push-pull, 1:Open-drain
#define GPOTB_Init      0x00            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------
#define IS_BRD_ID1_HI()     IS_MASK_SET(GPDRB, BIT(0))
#define IS_BRD_ID1_LO()     IS_MASK_CLEAR(GPDRB, BIT(0))

#define IS_BRD_ID2_HI()     IS_MASK_SET(GPDRB, BIT(1))
#define IS_BRD_ID12_LO()    IS_MASK_CLEAR(GPDRB, BIT(1))

#define IS_TCPC_P0_SNK_PWRGD_HI()   IS_MASK_SET(GPDRB, BIT(2))
#define IS_TCPC_P0_SNK_PWRGD_LO()   IS_MASK_CLEAR(GPDRB, BIT(2))

#define IS_EC_PWRSW_DN()            IS_MASK_CLEAR(GPDRB, BIT(3))
#define IS_EC_PWRSW_UP()            IS_MASK_SET(GPDRB, BIT(3))

#define SYS_PWROK_HI()              SET_MASK(GPDRB, BIT(5))
#define SYS_PWROK_LO()              CLEAR_MASK(GPDRB, BIT(5))

#define IS_PD_1_EC_SMBUS1_ALERT_0_N_HI()        IS_MASK_SET(GPDRB, BIT(6))
#define IS_PD_1_EC_SMBUS1_ALERT_0_N_LO()        IS_MASK_CLEAR(GPDRB, BIT(6))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortC_Init      0x00            // PORT Data

#define PortC0_Ctrl     INPUT           // SW2_INT_N_R
#define PortC1_Ctrl     ALT             // SM_BAT_CLK
#define PortC2_Ctrl     ALT             // SM_BAT_DATA
#define PortC3_Ctrl     INPUT           // PD_EC_SMBUS1_ALERT_0_N
#define PortC4_Ctrl     OUTPUT          // PCH_DPWROK
#define PortC5_Ctrl     OUTPUT          // ALL_SYS_PWRGD
#define PortC6_Ctrl     OUTPUT          // EC_SLP_SX
#define PortC7_Ctrl     INPUT           // LED_CHG_FULL
//----------------------------------------
#define IS_SW2_INT_N_R_HI()         IS_MASK_SET(GPDRC, BIT(0))
#define IS_SW2_INT_N_R_LO()         IS_MASK_CLEAR(GPDRC, BIT(0))

#define IS_TYPEC_I2C_INT1_HI()      IS_MASK_SET(GPDRC, BIT(3))
#define IS_TYPEC_I2C_INT1_LO()      IS_MASK_CLEAR(GPDRC, BIT(3))
#define IS_TYPEC_I2C_INT_HI()       IS_MASK_SET(GPDRC, BIT(3))
#define IS_TYPEC_I2C_INT_LO()       IS_MASK_CLEAR(GPDRC, BIT(3))

#define DSW_PWROK_R_HI()            SET_MASK(GPDRC, BIT(4))
#define DSW_PWROK_R_LO()            CLEAR_MASK(GPDRC, BIT(4))
#define IS_DSW_PWROK_R_HI()         IS_MASK_SET(GPDRC, BIT(4))
#define IS_DSW_PWROK_R_LO()         IS_MASK_CLEAR(GPDRC, BIT(4))

#define ALL_SYS_PWRGD_HI()          SET_MASK(GPDRC, BIT(5))
#define ALL_SYS_PWRGD_LO()          CLEAR_MASK(GPDRC, BIT(5))

#define EC_SLP_SX_HI()              SET_MASK(GPDRC, BIT(6))
#define EC_SLP_SX_LO()              CLEAR_MASK(GPDRC, BIT(6))
#define IS_EC_SLP_SX_HI()           IS_MASK_SET(GPDRC, BIT(6))

#define LED_CHG_FULL_OFF()          (GPCRC7 = INPUT)
#define LED_CHG_FULL_ON()           {(GPCRC7 = OUTPUT); CLEAR_MASK(GPDRC, BIT(7));}

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortD_Init      0x02            // PORT Data

#define PortD0_Ctrl     INPUT           // VCCANA_VR_PWRGD
#define PortD1_Ctrl     OUTPUT          // BATLOW_N
#define PortD2_Ctrl     ALT             // ESPI_RESET_N
#define PortD3_Ctrl     INPUT           // SOC_WAKE_SCI_N
#define PortD4_Ctrl     INPUT           // EC_SMI_LP_N
#define PortD5_Ctrl     INPUT           // V3P3A_PGOOD
#define PortD6_Ctrl     INPUT           // Set to input for SMT // OUTPUT          // PD1_SINK_CTRL_EC
#define PortD7_Ctrl     OUTPUT          // AMP_EN
//----------------------------------------
#define GPOTD_Init      0x00            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------
#define IS_VCCANA_VR_PWRGD_HI()     IS_MASK_SET(GPDRD, BIT(0))
#define IS_VCCANA_VR_PWRGD_LO()     IS_MASK_CLEAR(GPDRD, BIT(0))

#define BATLOW_N_HI()               SET_MASK(GPDRD, BIT(1))
#define BATLOW_N_LO()               CLEAR_MASK(GPDRD, BIT(1))

#define BATLOW_N_HI()               SET_MASK(GPDRD, BIT(1))
#define BATLOW_N_LO()               CLEAR_MASK(GPDRD, BIT(1))
#define IS_BATLOW_N_LO()            IS_MASK_CLEAR(GPDRD, BIT(1))

#define IS_V3P3A_PGOOD_HI()         IS_MASK_SET(GPDRD, BIT(5))
#define IS_V3P3A_PGOOD_LO()         IS_MASK_CLEAR(GPDRD, BIT(5))

#define PD1_SINK_CTRL_EC_HI()       SET_MASK(GPDRD, BIT(6))
#define PD1_SINK_CTRL_EC_LO()       CLEAR_MASK(GPDRD, BIT(6))

#define AMP_EN_HI()                 SET_MASK(GPDRD, BIT(7))
#define AMP_EN_LO()                 CLEAR_MASK(GPDRD, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortE_Init      0x00            // PORT Data

#define PortE0_Ctrl     INPUT           //set to input for SMT // OUTPUT          // EC_NFC_RST_N (5V Output, set to OD)
#define PortE1_Ctrl     INPUT           //set to input for SMT // OUTPUT          // NFC_SHUTDOWN_BUF (5V Output, set to OD)
#define PortE2_Ctrl     INPUT           // H_CATERR_3P3V_N
#define PortE3_Ctrl     INPUT           //set to input for SMT // OUTPUT          // PD2_SINK_CTRL_EC
#define PortE4_Ctrl     INPUT           // Set to input for SMT // OUTPUT          // IPDM_PWRDN_N
#define PortE5_Ctrl     OUTPUT          // PM_PCH_PWROK
#define PortE6_Ctrl     INPUT           // PM_SLP_SUS_N
#define PortE7_Ctrl     OUTPUT          // EC_PROCHOT_N
//----------------------------------------
//#define GPOTE_Init      0x93            // Out Type: 0:Push-pull, 1:Open-drain
#define GPOTE_Init      0x80            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------

#define EC_NFC_RST_N_HI()           SET_MASK(GPDRE, BIT(0))
#define EC_NFC_RST_N_LO()           CLEAR_MASK(GPDRE, BIT(0))

#define NFC_SHUTDOWN_BUF_HI()       SET_MASK(GPDRE, BIT(1))
#define NFC_SHUTDOWN_BUF_LO()       CLEAR_MASK(GPDRE, BIT(1))

#define IS_H_CATERR_3P3V_N_HI()     IS_MASK_SET(GPDRE, BIT(2))
#define IS_H_CATERR_3P3V_N_LO()     IS_MASK_CLEAR(GPDRE, BIT(2))

#define PD2_SINK_CTRL_EC_HI()       SET_MASK(GPDRE, BIT(3))
#define PD2_SINK_CTRL_EC_LO()       CLEAR_MASK(GPDRE, BIT(3))

#define IPDM_PWRDN_N_HI()           SET_MASK(GPDRE, BIT(4))
#define IPDM_PWRDN_N_LO()           CLEAR_MASK(GPDRE, BIT(4))

#define PM_PCH_PWROK_HI()           SET_MASK(GPDRE, BIT(5))
#define PM_PCH_PWROK_LO()           CLEAR_MASK(GPDRE, BIT(5))

#define IS_PM_SLP_SUS_N_HI()        IS_MASK_SET(GPDMRE, BIT(6))
#define IS_PM_SLP_SUS_N_LO()        IS_MASK_CLEAR(GPDMRE, BIT(6))

#define EC_PROCHOT_HI()             SET_MASK(GPDRE, BIT(7))
#define EC_PROCHOT_LO()             CLEAR_MASK(GPDRE, BIT(7))


//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortF_Init      0x90            // PORT Data

#define PortF0_Ctrl     INPUT           //Set to input for SMT // OUTPUT          // EC_PD1_SOURCE_CTRL
#define PortF1_Ctrl     INPUT           // HALL_SENSOR_INT
#define PortF2_Ctrl     ALT + PULL_UP   // PD_EC_SMBUS1_CLK
#define PortF3_Ctrl     ALT + PULL_UP   // PD_EC_SMBUS1_DATA
#define PortF4_Ctrl     OUTPUT          // GPD_3_PWRBTN_N
#define PortF5_Ctrl     INPUT           //Set to input for SMT OUTPUT          // EC_PD2_SOURCE_CTRL
#define PortF6_Ctrl     OUTPUT          // PECI_EC
#define PortF7_Ctrl     OUTPUT          // AC_PRESENT_R
//----------------------------------------
#define GPOTF_Init      0x00            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------
#define EC_PD1_SOURCE_CTRL_HI()     SET_MASK(GPDRF, BIT(0))
#define EC_PD1_SOURCE_CTRL_LO()     CLEAR_MASK(GPDRF, BIT(0))

#define IS_LID_INT_B_HI()           IS_MASK_SET(GPDRF, BIT(1))
#define IS_LID_INT_B_LO()           IS_MASK_CLEAR(GPDRF, BIT(1))
#define IS_LID_SW_CLOSE()           IS_MASK_CLEAR(GPDRF, BIT(1))
#define IS_LID_SW_OPEN()            IS_MASK_SET(GPDRF, BIT(1))

#define PCH_PWRBTN_HI()             SET_MASK(GPDRF, BIT(4))
#define PCH_PWRBTN_LO()             CLEAR_MASK(GPDRF, BIT(4))

#define EC_PD2_SOURCE_CTRL_HI()    SET_MASK(GPDRF, BIT(5))
#define EC_PD2_SOURCE_CTRL_LO()    CLEAR_MASK(GPDRF, BIT(5))

#define AC_PRESENT_HI()             SET_MASK(GPDRF, BIT(7))
#define AC_PRESENT_LO()             CLEAR_MASK(GPDRF, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortG_Init      0x02            // PORT Data

#define PortG0_Ctrl     INPUT           // PM_SLP_S3_N
#define PortG1_Ctrl     INPUT           // EC_ME_UNLOCK
#define PortG2_Ctrl     INPUT           // EC_STRAP
#define PortG6_Ctrl     INPUT           // 
//----------------------------------------
#define IS_PM_SLP_S3_N_HI()         IS_MASK_SET(GPDRG, BIT(0))
#define IS_PM_SLP_S3_N_LO()         IS_MASK_CLEAR(GPDRG, BIT(0))

#define IS_PCH_ME_UNLOCK_HI()       IS_MASK_SET(GPDRG, BIT(1))
#define PCH_ME_UNLOCK_HI()          SET_MASK(GPDRG, BIT(1))
#define PCH_ME_UNLOCK_LO()          CLEAR_MASK(GPDRG, BIT(1))
#define PCH_ME_UNLOCK()             (GPCRG1 = OUTPUT)
#define PCH_ME_LOCK()               (GPCRG1 = INPUT)

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortH_Init      0x20            // PORT Data

#define PortH0_Ctrl     OUTPUT          // PM_RSMRST_EC_N
#define PortH1_Ctrl     INPUT           // UART_EC_RXD
#define PortH2_Ctrl     INPUT           // UART_EC_TXD
#define PortH3_Ctrl     OUTPUT          // IMVP_PE_EC
#define PortH4_Ctrl     INPUT           // EC_SLP_S0IX_N/EC_SLP_S0_N
#define PortH5_Ctrl     OUTPUT          // EC_PWR_LATCH
#define PortH6_Ctrl     INPUT           // BATT_DET
#define PortH7_Ctrl     INPUT           // IMVP9_VR_READY
//----------------------------------------
#define GPOTH_Init      0x00            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------

#define EC_PM_RSMRST_HI()           SET_MASK(GPDRH, BIT(0))
#define EC_PM_RSMRST_LO()           CLEAR_MASK(GPDRH, BIT(0))
#define PCH_RSMRST_HI()             SET_MASK(GPDRH, BIT(0))
#define PCH_RSMRST_LO()             CLEAR_MASK(GPDRH, BIT(0))
#define IS_PCH_RSMRST_HI()          IS_MASK_SET(GPDRH, BIT(0))
#define IS_PCH_RSMRST_LO()          IS_MASK_CLEAR(GPDRH, BIT(0))

#define RSMRST_HI()                 EC_PM_RSMRST_HI()
#define RSMRST_LO()                 EC_PM_RSMRST_LO()

#define IMVP_PE_EC_HI()             SET_MASK(GPDRH, BIT(3))
#define IMVP_PE_EC_LO()             CLEAR_MASK(GPDRH, BIT(3))

#define IS_EC_SLP_S0IX_N_HI()       IS_MASK_SET(GPDRH, BIT(4))
#define IS_EC_SLP_S0IX_N_LO()       IS_MASK_CLEAR(GPDRH, BIT(4))
#define IS_SLP_S0_CS_HI()           IS_MASK_SET(GPDRH, BIT(4))
#define IS_SLP_S0_CS_LO()           IS_MASK_CLEAR(GPDRH, BIT(4))

#define EC_PWR_LATCH_HI()           SET_MASK(GPDRH, BIT(5))
#define EC_PWR_LATCH_LO()           CLEAR_MASK(GPDRH, BIT(5))

#define IS_BATTERY1_IN()            IS_MASK_CLEAR(GPDRH, BIT(6))
#define IS_BATTERY1_OUT()           IS_MASK_SET(GPDRH, BIT(6))

#define IS_IMVP9_VR_READY_HI()      IS_MASK_SET(GPDRH, BIT(7))
#define IS_IMVP9_VR_READY_LO()      IS_MASK_CLEAR(GPDRH, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortI_Init      0x00            // PORT Data

#define PortI0_Ctrl     INPUT           // EC_SOC_THRM_ALERT1
#define PortI1_Ctrl     INPUT           // EC_PD_THRM_ALERT2
#define PortI2_Ctrl     INPUT           // CHG_PSYS
#define PortI3_Ctrl     INPUT           // VCCST_VR_PWRGD_IN
#define PortI4_Ctrl     INPUT           // EC_CHG_THRM_ALERT3
#define PortI5_Ctrl     INPUT           // BATT_ID
#define PortI6_Ctrl     INPUT           // BATT_NTC
#define PortI7_Ctrl     INPUT           // VCHG_PWR_SENSE
//----------------------------------------
//PSYS is ADC, should add ADC feature after power on
#define IS_CHG_PSYS_HI()            IS_MASK_SET(GPDRI, BIT(2))
#define IS_CHG_PSYS_LO()            IS_MASK_CLEAR(GPDRI, BIT(2))

#define IS_VCCST_VR_PWRGD_IN_HI()   IS_MASK_SET(GPDRI, BIT(3))
#define IS_VCCST_VR_PWRGD_IN_LO()   IS_MASK_CLEAR(GPDRI, BIT(3))

#define IS_BATT_ID_HI()             IS_MASK_SET(GPDRI, BIT(5))
#define IS_BATT_ID_LO()             IS_MASK_CLEAR(GPDRI, BIT(5))

#define IS_BATT_NTC_HI()            IS_MASK_SET(GPDRI, BIT(6))
#define IS_BATT_NTC_LO()            IS_MASK_CLEAR(GPDRI, BIT(6))

#define IS_VCHG_PWR_SENSE_HI()      IS_MASK_SET(GPDRI, BIT(7))
#define IS_VCHG_PWR_SENSE_LO()      IS_MASK_CLEAR(GPDRI, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortJ_Init      0x00            // PORT Data

#define PortJ0_Ctrl     INPUT           // VOL_UP_EC
#define PortJ1_Ctrl     OUTPUT          // BATT_ON_OFF 
#define PortJ2_Ctrl     INPUT           // VDD2_VR_PWRGD_R(NC)
#define PortJ3_Ctrl     INPUT           // VOL_DOWN_EC
#define PortJ4_Ctrl     INPUT           // SW1_INT_N_R
#define PortJ5_Ctrl     INPUT           // RSMRST_PWRGD_N
#define PortJ6_Ctrl     INPUT           //
#define PortJ7_Ctrl     INPUT           // PM_SLP_S4_N
//----------------------------------------
#define GPOTJ_Init      0x02            // Out Type: 0:Push-pull, 1:Open-drain
//----------------------------------------

#define IS_VOLUME_UP_UP()               IS_MASK_SET(GPDRJ, BIT(0))
#define IS_VOLUME_UP_DN()               IS_MASK_CLEAR(GPDRJ, BIT(0))

#define BATT_ON_OFF_HI()                SET_MASK(GPDRJ, BIT(1))
#define BATT_ON_OFF_LO()                CLEAR_MASK(GPDRJ, BIT(1))

#define IS_VDD2_VR_PWRGD_HI()           IS_MASK_SET(GPDRJ, BIT(2))
#define IS_VDD2_VR_PWRGD_LO()           IS_MASK_CLEAR(GPDRJ, BIT(2))

#define IS_VOLUME_DOWN_UP()             IS_MASK_SET(GPDRJ, BIT(3))
#define IS_VOLUME_DOWN_DN()             IS_MASK_CLEAR(GPDRJ, BIT(3))

#define IS_SW1_INT_N_R_HI()             IS_MASK_SET(GPDRJ, BIT(4))
#define IS_SW1_INT_N_R_LO()             IS_MASK_CLEAR(GPDRJ, BIT(4))

#define IS_RSMRST_PWRGD_HI()            IS_MASK_SET(GPDRJ, BIT(5))
#define IS_RSMRST_PWRGD_LO()            IS_MASK_CLEAR(GPDRJ, BIT(5))

#define IS_PM_SLP_S4_N_HI()             IS_MASK_SET(GPDRJ, BIT(7))
#define IS_PM_SLP_S4_N_LO()             IS_MASK_CLEAR(GPDRJ, BIT(7))

//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port K Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortK_Init      0x00            // PORT Data

#define PortK0_Ctrl     INPUT           //
#define PortK1_Ctrl     INPUT           //
#define PortK2_Ctrl     INPUT           //
#define PortK3_Ctrl     INPUT           //
#define PortK4_Ctrl     INPUT           //
#define PortK5_Ctrl     INPUT           //
#define PortK6_Ctrl     INPUT           //
#define PortK7_Ctrl     INPUT           //
//----------------------------------------


//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port L Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortL_Init      0x00            // PORT Data

#define PortL0_Ctrl     INPUT           //
#define PortL1_Ctrl     INPUT           //
#define PortL2_Ctrl     INPUT           //
#define PortL3_Ctrl     INPUT           //
#define PortL4_Ctrl     INPUT           //
#define PortL5_Ctrl     INPUT           //
#define PortL6_Ctrl     INPUT           //
#define PortL7_Ctrl     INPUT           //
//----------------------------------------


//*****************************************************************************
//-----------------------------------------------------------------------------
// GPIO Port M Registers define
//-----------------------------------------------------------------------------
//*****************************************************************************
#define PortM_Init      0x00            // PORT Data

#define PortM0_Ctrl     0x06    //LPC_AD0      ESPI_IO_0_R
#define PortM1_Ctrl     0x06    //LPC_AD1      ESPI_IO_1_R
#define PortM2_Ctrl     0x06    //LPC_AD2      ESPI_IO_2_R
#define PortM3_Ctrl     0x06    //LPC_AD3      ESPI_IO_3_R
#define PortM4_Ctrl     0x06    //CLK_PCI_KBC  ESPI_CLK_R
#define PortM5_Ctrl     0x00    //LPC_FRAME_N  ESPI_CS_N_R
#define PortM6_Ctrl     INPUT   // set to input for SMT   // OUTPUT  //TCP0_BSSB_MUX_SEL_EC
//----------------------------------------

#define TCP0_BSSB_MUX_SEL_EC_HI()       SET_MASK(GPDRM, BIT(6))
#define TCP0_BSSB_MUX_SEL_EC_LO()       CLEAR_MASK(GPDRM, BIT(6))

//*****************************************************************************
//-----------------------------------------------------------------------------
// KSI/KSO setting to GPIO mode
//-----------------------------------------------------------------------------
//*****************************************************************************
#define KSIGCTRLR_Ctrl  0x3F        //Keyboard Scan In [7:0] GPIO Control, 1:GPIO 0:KBS
#define KSIGOENR_Ctrl   0x00        //Keyboard Scan In [7:0] GPIO Output Enable, 1:Output
#define KSIGDATR_Ctrl   0x00        //Keyboard Scan In [7:0] GPIO Data register


#define KSOLGCTRLR_Ctrl 0xFF        //Keyboard Scan Out [7:0] GPIO Control, 1:GPIO 0:KBS
// set to input for SMT
#define KSOLGOENR_Ctrl  0x81        //Keyboard Scan Out [7:0] GPIO Output Enable, 1:Output
// #define KSOLGOENR_Ctrl  0xAD        //Keyboard Scan Out [7:0] GPIO Output Enable, 1:Output
#define KSOL_Ctrl       0x00        //KSO[7:0]  Data Register


#define KSOHGCTRLR_Ctrl 0xFF        //Keyboard Scan Out [15:8] GPIO Control, 1:GPIO 0:KBS
// set to input for SMT
#define KSOHGOENR_Ctrl  0x00        //Keyboard Scan Out [15:8] GPIO Output Enable, 1:Output
// #define KSOHGOENR_Ctrl  0x04        //Keyboard Scan Out [15:8] GPIO Output Enable, 1:Output
#define KSOH1_Ctrl      0x00        //KSO[15:8] Data Register
//----------------------------------------

// KSI 0 NC

// KSI 1 NC

// KSI 2 NC

// KSI 3 NC

// KSI 4 NC

// KSI 5 NC

// KSI 6 SMB_BS_DATA

// KSI 7 SMB_BS_CLK


// KSO 0 EC_STATE
#define EC_STATE_HI()               SET_MASK(KSOL, BIT0)    //KSO 0
#define EC_STATE_LO()               CLEAR_MASK(KSOL, BIT0)  //KSO 0
#define IS_EC_STATE_LO()            IS_MASK_CLEAR(KSOLGDMRRR, BIT0)    //KSO 0

// KSO 1 NC

// KSO 2 EC_CTRL
#define IS_EC_CTRL_HI()             IS_MASK_SET(KSOLGDMRRR, BIT2)    //KSO 2
#define IS_EC_CTRL_LO()             IS_MASK_CLEAR(KSOLGDMRRR, BIT2)  //KSO 2

// KSO 3 POGO_IPDM_MUX_SEL_HI
#define IS_POGO_IPDM_MUX_SEL_HI()            IS_MASK_SET(KSOLGDMRRR, BIT(3))
#define IS_POGO_IPDM_MUX_SEL_LO()           IS_MASK_CLEAR(KSOLGDMRRR, BIT(3))

// KSO 4 NC

// KSO 5 NC EC_M2_SSD_PLN_DELAY
#define EC_M2_SSD_PLN_DELAY_EN()    SET_MASK(KSOL, BIT5)    //KSO 5
#define EC_M2_SSD_PLN_DELAY_DIS()   CLEAR_MASK(KSOL, BIT5)  //KSO 5

// KSO 6 NC

// KSO 7 V5A_POGO_EN
#define V5A_POGO_EN_HI()            SET_MASK(KSOL, BIT(7))      //KSO 7
#define V5A_POGO_EN_LO()            CLEAR_MASK(KSOL, BIT(7))    //KSO 7



// KSO 8 NC

// KSO 9 PLTRST_N
#define IS_PLTRST_N_ON()            IS_MASK_SET(KSOHGDMRRR, BIT(1))
#define IS_PLTRST_N_OFF()           IS_MASK_CLEAR(KSOHGDMRRR, BIT(1))

// KSO 10 EC_EDP1_BKLT_EN
#define EC_EDP1_BKLT_EN_HI()        SET_MASK(KSOH1, BIT(2))
#define EC_EDP1_BKLT_EN_LO()        CLEAR_MASK(KSOH1, BIT(2))

// KSO 11 NC

// KSO 12 NC

// KSO 13 PSENS_OUT_EC
#define IS_PSENS_OUT_EC_ON()        IS_MASK_SET(KSOHGDMRRR, BIT(5))
#define IS_PSENS_OUT_EC_OFF()       IS_MASK_CLEAR(KSOHGDMRRR, BIT(5))

// KSO 14 PSENS_OFFSET_EC
#define PSENS_OFFSET_EC_HI()        SET_MASK(KSOH1, BIT(6))
#define PSENS_OFFSET_EC_LO()        CLEAR_MASK(KSOH1, BIT(6))

// KSO 15 NC
#define IS_SAR_SENS_IO1_EC_HI()     IS_MASK_SET(KSOHGDMRRR, BIT(7))
#define IS_SAR_SENS_IO1_EC_LO()     IS_MASK_CLEAR(KSOHGDMRRR, BIT(7))

//*****************************************************************************
/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
//*****************************************************************************
typedef struct InitGPIOReg
{
    XBYTE   *reg;
    BYTE    value;
} sInitGPIOReg;

//*****************************************************************************
/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
//*****************************************************************************
extern void Init_GPIO(void);
extern void Hook_SCION(void);
extern void Hook_SCIOFF(void);
extern void Hook_SMION(void);
extern void Hook_SMIOFF(void);
extern void Hook_A20ON(void);
extern void Hook_A20OFF(void);
extern void Hook_KBRSTON(void);
extern void Hook_KBRSTOFF(void);
extern void Hook_NUMLED_ON(void);
extern void Hook_NUMLED_OFF(void);
extern void Hook_CAPLED_ON(void);
extern void Hook_CAPLED_OFF(void);
extern void Hook_ME_UNLOCK(void);
extern void Hook_ME_LOCK(void);

//-----------------------------------------------------------------------------
//*****************************************************************************
#endif  //OEM_GPIO_H
//*****************************************************************************
/* End of OEM_GPIO.H */
