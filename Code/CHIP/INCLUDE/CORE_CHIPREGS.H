/*----------------------------------------------------------------------------
 * @file     | CORE_CHIPREGS.C          | @Chip | ITE Embedded Controller
 * ----------+-----------------------------------------------------------------
 * @function | Registers definition for extern all code base reference
 * ----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2019, ITE Tech. Inc. All rights reserved.
 * ----------+-----------------------------------------------------------------
 * 20160504 Add IT8991E registers.
 * 20180616 Add IT557xE registers.
 * 20190415 Add IT557xE registers.
 *---------------------------------------------------------------------------*/
#ifndef CORE_CHIPREGS_H
#define CORE_CHIPREGS_H

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI)
//-----------------------------------------------------------------------------
extern ECReg    FBCFG;              // FBIU Configuration
extern ECReg    FPCFG;              // Flash Programming Configuration Register
#define AFSTBY          BIT(6)  // Auto Flash Standby

extern ECReg    FECBSR;             // Flash EC Code Banking Select Register
extern ECReg    FMSSR;              // Flash Memory Size Select Registe
extern ECReg    SMECCS;             // Shared Memory EC Control and Status
#define HSEMIE          BIT(7)  // Host Semaphore Interrupt Enable
#define HSEMW           BIT(6)  // Host Semaphore Write
#define HOSTWA          BIT(5)  // Host Write Allow

extern ECReg    SMHSR;              // Shared Memory Host Semaphore
extern ECReg    FLHCTRL1R;          // Flash Control Register 1
#define SPIFR1          BIT(5)  // SPI Flash Read Mode
#define SPIFR0          BIT(4)  // SPI Flash Read Mode
                                //11b: Uses ¡§Fast Read Dual Input/Output (DIOFR)¡¨ cycle (instruction = BBh)
                                //10b: Uses ¡§Fast Read Dual Output (DOFR)¡¨ cycle (instruction = 3Bh)
                                //01b: Uses ¡§Fast Read (FREAD)¡¨ cycle (instruction = 0Bh)
                                //00b: Uses ¡§Read¡¨ cycle (instruction = 03h)
#define LFSW1T          BIT(3)  // Serial Wait 1T

extern ECReg    FLHCTRL2R;          // Flash Control Register 2
extern ECReg    DCache;             // 256 bytes cache
extern ECReg    UCCTRLR;            // uC Control Register
#define UCBST           BIT(7)  // uC Burst Mode

extern ECReg    HCTRL2R;            // Host Control 2 Register
#define HBREN           BIT(7)  // Host Bridge Enable
#define HFW1EN          BIT(5)  // HLPC Follow Mode 1 Enable

extern ECReg    HSPICTRL2R;         // HSPI Control 2 Register
extern ECReg    HSPICTRL3R;         // HSPI Control Register 3
extern ECReg    ECINDAR0;           // EC-Indirect Memory Address Register 0
extern ECReg    ECINDAR1;           // EC-Indirect Memory Address Register 1
extern ECReg    ECINDAR2;           // EC-Indirect Memory Address Register 2
extern ECReg    ECINDAR3;           // EC-Indirect Memory Address Register 3
extern ECReg    ECINDDR;            // EC-Indirect Memory Data Register
extern ECReg    SCRA0L;             // Scratch SRAM 0 Address Low Byte
extern ECReg    SCRA0M;             // Scratch SRAM 0 Address Middle Byte
extern ECReg    SCRA0H;             // Scratch SRAM 0 Address High Byte

#if !ITE_CHIP_IT557X    //0: IT557x No DMA1~4
extern ECReg    SCRA1L;             // Scratch SRAM 1 Address Low Byte
extern ECReg    SCRA1M;             // Scratch SRAM 1 Address Middle Byte
extern ECReg    SCRA1H;             // Scratch SRAM 1 Address High Byte
extern ECReg    SCRA2L;             // Scratch SRAM 2 Address Low Byte
extern ECReg    SCRA2M;             // Scratch SRAM 2 Address Middle Byte
extern ECReg    SCRA2H;             // Scratch SRAM 2 Address High Byte
extern ECReg    SCRA3L;             // Scratch SRAM 3 Address Low Byte
extern ECReg    SCRA3M;             // Scratch SRAM 3 Address Middle Byte
extern ECReg    SCRA3H;             // Scratch SRAM 3 Address High Byte
extern ECReg    SCRA4L;             // Scratch SRAM 4 Address Low Byte
extern ECReg    SCRA4M;             // Scratch SRAM 4 Address Middle Byte
extern ECReg    SCRA4H;             // Scratch SRAM 4 Address High Byte
#endif  //ITE_CHIP_IT557X

/*      FBCFG       */
#define SSMC    BIT(7)
/*      SMECCS      */
#define HOSTWA  BIT(5)
#define LKPRR   BIT(2)

extern ECReg    P0BA0R;             // Protect 0 Base Addr Register 0
extern ECReg    P0BA1R;             // Protect 0 Base Addr Register 1
extern ECReg    P0ZR;               // Protect 0 Size Register
extern ECReg    P1BA0R;             // Protect 1 Base Addr Register 0
extern ECReg    P1BA1R;             // Protect 1 Base Addr Register 1
extern ECReg    P1ZR;               // Protect 1 Size Register
extern ECReg    DSINST;             // Deferred SPI Instruction
extern ECReg    DSADR1;             // Deferred SPI Address Deferred SPI Address 15-12 (DSA15-12)
extern ECReg    DSADR2;             // Deferred SPI Address Deferred SPI Address 23-16 (DSA23-16)
extern ECReg    HINSTC1;            // Host Instruction Control 1
#define DISSV       BIT(3)
#define DISS        BIT(2)
#define ENDPI       BIT(1)
#define ENDEI       BIT(0)

extern ECReg    HINSTC2;            // Host Instruction Control 2
#define DISEID8     BIT(3)
#define DISEID7     BIT(2)
#define DISEI52     BIT(1)
#define DISEI20     BIT(0)

extern ECReg    HRAMWC;             // Host RAM Window Control
#define Window0En   BIT(0)       // Window 0 enabled
#define Window1En   BIT(1)       // Window 1 enabled
#define H2RAMS      BIT(4)          // 0 : H2RAM-HLPC selected,
// 1 : H2RAM-HSPI selected

extern ECReg    HRAMW0BA;           // Host RAM Window 0 Base Address external ram 0x800 ~ 0xFFF
extern ECReg    HRAMW1BA;           // Host RAM Window 1 Base Address external ram 0x000 ~ 0x7FF
extern ECReg    HRAMW0AAS;          // Host RAM Window 0 Access Allow Size
extern ECReg    HRAMW1AAS;          // Host RAM Window 1 Access Allow Size
#define HostRamSize16Byte       0x00
#define HostRamSize32Byte       0x01
#define HostRamSize64Byte       0x02
#define HostRamSize128Byte      0x03
#define HostRamSize256Byte      0x04
#define HostRamSize512Byte      0x05
#define HostRamSize1024Byte     0x06
#define HostRamSize2048Byte     0x07

extern ECReg    REG_1060;
#define F_PI2EC_DECODE           BIT(7)

extern ECReg    SCAR5H;
extern ECReg    FLHCTRL3R;          //REG@1063h Flash Control 3 Register
#define LAST_COMPARE_MISMATCH   BIT(7)  //R/WC  0b  Last Compare mismatch
#define MIRROR_SPECIFIED_RANGE  BIT(5)  //R/W   0b  Mirror code with specified range 
#define AUTO_LOAD_AFTER_WDT     BIT(4)  //R/W   0b  Auto load code after WDT
#define FIFE                    BIT(3)  //R/W   0b  FSPI I/F Enable (FIFE)
#define FFSPITRI                BIT(0)  //R/W   0b  Force FSPI I/F Tri-state (FFSPITRI)

extern ECReg    FLHCTRL4R;          // Flash Control 4 Register
extern ECReg    HSPICTRL;           // HSPI Control Register 4

extern ECReg    EC106B;
extern ECReg    EC106C;


extern ECReg    P2BA0R;             // Protect 2 Base Addr Register 0
extern ECReg    P2BA1R;             // Protect 2 Base Addr Register 1
extern ECReg    P2ZR;               // Protect 2 Size Register
extern ECReg    P3BA0R;             // Protect 3 Base Addr Register 0
extern ECReg    P3BA1R;             // Protect 3 Base Addr Register 1
extern ECReg    P3ZR;               // Protect 3 Size Register
extern ECReg    HRAMW2BA;           // Host RAM Windows 2 Base Address
extern ECReg    HRAMW3BA;           // Host RAM Windows 3 Base Address
extern ECReg    HRAMW2AAS;          // Host RAM Windows 2 Access Allow Size
extern ECReg    HRAMW3AAS;          // Host RAM Windows 3 Access Allow Size
extern ECReg    H2RAMECSIE;         // H2RAM EC Semaphore Interrupt Enable
extern ECReg    H2RAMECSA;          // H2RAM EC Semaphore Address
extern ECReg    H2RAMHSS;           // H2RAM Host Semaphore Status
extern ECReg    HPADR;              // Host Protect Authentication Data Register
extern ECReg    FLHCTRL5R;          // Flash Control 5
extern ECReg    FLHCTRL6R;          // Flash Control 6
#define FSPI26AMEN  BIT(4)          // 0 : H2RAM-HLPC selected,

extern ECReg    SCARSL;             // Scratch SRAM SMBus Address Low
extern ECReg    SCARSM;             // Scratch SRAM SMBus Address Middle
extern ECReg    SCARSH;             // Scratch SRAM SMBus Address High

extern ECReg    REG_10A2;

//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC)
//-----------------------------------------------------------------------------
extern ECReg    ISR0;               // Interrupt Status Register 0
extern ECReg    ISR1;               // Interrupt Status Register 1
extern ECReg    ISR2;               // Interrupt Status Register 2
extern ECReg    ISR3;               // Interrupt Status Register 3
extern ECReg    ISR4;               // Interrupt Status Register 4
extern ECReg    ISR5;               // Interrupt Status Register 5
extern ECReg    ISR6;               // Interrupt Status Register 6
extern ECReg    ISR7;               // Interrupt Status Register 7
extern ECReg    ISR8;               // Interrupt Status Register 8
extern ECReg    ISR9;               // Interrupt Status Register 9
extern ECReg    ISR10;              // Interrupt Status Register 10
extern ECReg    ISR11;              // Interrupt Status Register 11
extern ECReg    ISR12;              // Interrupt Status Register 12
extern ECReg    ISR13;              // Interrupt Status Register 13
extern ECReg    ISR14;              // Interrupt Status Register 14
extern ECReg    ISR15;              // Interrupt Status Register 15
extern ECReg    ISR16;              // Interrupt Status Register 16
extern ECReg    ISR17;              // Interrupt Status Register 17
extern ECReg    ISR18;              // Interrupt Status Register 18
extern ECReg    ISR19;              // Interrupt Status Register 19
extern ECReg    ISR20;              // Interrupt Status Register 20
extern ECReg    ISR21;              // Interrupt Status Register 21

extern ECReg    IER0;               // Interrupt Enable Register 0
extern ECReg    IER1;               // Interrupt Enable Register 1
extern ECReg    IER2;               // Interrupt Enable Register 2
extern ECReg    IER3;               // Interrupt Enable Register 3
extern ECReg    IER4;               // Interrupt Enable Register 4
extern ECReg    IER5;               // Interrupt Enable Register 5
extern ECReg    IER6;               // Interrupt Enable Register 6
extern ECReg    IER7;               // Interrupt Enable Register 7
extern ECReg    IER8;               // Interrupt Enable Register 8
extern ECReg    IER9;               // Interrupt Enable Register 9
extern ECReg    IER10;              // Interrupt Enable Register 10
extern ECReg    IER11;              // Interrupt Enable Register 11
extern ECReg    IER12;              // Interrupt Enable Register 12
extern ECReg    IER13;              // Interrupt Enable Register 13
extern ECReg    IER14;              // Interrupt Enable Register 14
extern ECReg    IER15;              // Interrupt Enable Register 15
extern ECReg    IER16;              // Interrupt Enable Register 16
extern ECReg    IER17;              // Interrupt Enable Register 17
extern ECReg    IER18;              // Interrupt Enable Register 18
extern ECReg    IER19;              // Interrupt Enable Register 19
extern ECReg    IER20;              // Interrupt Enable Register 20
extern ECReg    IER21;              // Interrupt Enable Register 21

extern ECReg    IELMR0;             // Interrupt Edge/Level-Triggered Mode Register 0
extern ECReg    IELMR1;             // Interrupt Edge/Level-Triggered Mode Register 1
extern ECReg    IELMR2;             // Interrupt Edge/Level-Triggered Mode Register 2
extern ECReg    IELMR3;             // Interrupt Edge/Level-Triggered Mode Register 3
extern ECReg    IELMR4;             // Interrupt Edge/Level-Triggered Mode Register 4
extern ECReg    IELMR5;             // Interrupt Edge/Level-Triggered Mode Register 5
extern ECReg    IELMR6;             // Interrupt Edge/Level-Triggered Mode Register 6
extern ECReg    IELMR7;             // Interrupt Edge/Level-Triggered Mode Register 7
extern ECReg    IELMR8;             // Interrupt Edge/Level-Triggered Mode Register 8
extern ECReg    IELMR9;             // Interrupt Edge/Level-Triggered Mode Register 9
extern ECReg    IELMR10;            // Interrupt Edge/Level-Triggered Mode Register 10
extern ECReg    IELMR11;            // Interrupt Edge/Level-Triggered Mode Register 11
extern ECReg    IELMR12;            // Interrupt Edge/Level-Triggered Mode Register 12
extern ECReg    IELMR13;            // Interrupt Edge/Level-Triggered Mode Register 13
extern ECReg    IELMR14;            // Interrupt Edge/Level-Triggered Mode Register 14
extern ECReg    IELMR15;            // Interrupt Edge/Level-Triggered Mode Register 15
extern ECReg    IELMR16;            // Interrupt Edge/Level-Triggered Mode Register 16
extern ECReg    IELMR17;            // Interrupt Edge/Level-Triggered Mode Register 17
extern ECReg    IELMR18;            // Interrupt Edge/Level-Triggered Mode Register 18
extern ECReg    IELMR19;            // Interrupt Edge/Level-Triggered Mode Register 19
extern ECReg    IELMR20;            // Interrupt Edge/Level-Triggered Mode Register 20
extern ECReg    IELMR21;            // Interrupt Edge/Level-Triggered Mode Register 21

extern ECReg    IPOLR0;             // Interrupt Polarity Register 0
extern ECReg    IPOLR1;             // Interrupt Polarity Register 1
extern ECReg    IPOLR2;             // Interrupt Polarity Register 2
extern ECReg    IPOLR3;             // Interrupt Polarity Register 3
extern ECReg    IPOLR4;             // Interrupt Polarity Register 4
extern ECReg    IPOLR5;             // Interrupt Polarity Register 5
extern ECReg    IPOLR6;             // Interrupt Polarity Register 6
extern ECReg    IPOLR7;             // Interrupt Polarity Register 7
extern ECReg    IPOLR8;             // Interrupt Polarity Register 8
extern ECReg    IPOLR9;             // Interrupt Polarity Register 9
extern ECReg    IPOLR10;            // Interrupt Polarity Register 10
extern ECReg    IPOLR11;            // Interrupt Polarity Register 11
extern ECReg    IPOLR12;            // Interrupt Polarity Register 12
extern ECReg    IPOLR13;            // Interrupt Polarity Register 13
extern ECReg    IPOLR14;            // Interrupt Polarity Register 14
extern ECReg    IPOLR15;            // Interrupt Polarity Register 15
extern ECReg    IPOLR16;            // Interrupt Polarity Register 16
extern ECReg    IPOLR17;            // Interrupt Polarity Register 17
extern ECReg    IPOLR18;            // Interrupt Polarity Register 18
extern ECReg    IPOLR19;            // Interrupt Polarity Register 19
extern ECReg    IPOLR20;            // Interrupt Polarity Register 20
extern ECReg    IPOLR21;            // Interrupt Polarity Register 21

extern ECReg    IVECT;              // Interrupt Vector Register
extern ECReg    INT0ST;             // INT0# status
extern ECReg    PFAILR;             // Power Fail Register

// IER0 / ISR0
//      -                   BIT(0)  // -
#define Int_WKO20           BIT(1)  // WKO[20]
#define Int_KBCOBFE         BIT(2)  // KBC Output Buffer Empty Interrupt
#define Int_PMCOBFE         BIT(3)  // PMC Output Buffer Empty Interrupt
#define Int_SMBUS3          BIT(4)  // SMBUS3 Interrupt, SMBus D Interrupt
#define Int_WKINTAD         BIT(5)  // WKINTAD (WKINTA or WKINTD)
#define Int_WKO23           BIT(6)  // WKO[23]
#define Int_PWM             BIT(7)  // PWM Interrupt

// IER1 / ISR1
#define Int_ADC             BIT(0)  // ADC Interrupt
#define Int_SMBUS0          BIT(1)  // SMBus A Interrupt
#define Int_SMBUS1          BIT(2)  // SMBus B Interrupt
#define Int_KB              BIT(3)  // KB Matrix Scan Interrupt
#define Int_WKO26           BIT(4)  // WKO[26]
#define Int_WKINTC          BIT(5)  // WKINTC
#define Int_WKO25           BIT(6)  // WKO[25]
#define Int_CIR             BIT(7)  // CIR Interrupt

// IER2 / ISR2
#define Int_SMBUS2          BIT(0)  // SMBus C Interrupt
#define Int_WKO24           BIT(1)  // WKO[24] GPD2
#define Int_PS2_2           BIT(2)  // PS/2 Interrupt 2
#define Int_PS2_1           BIT(3)  // PS/2 Interrupt 1
#define Int_PS2_0           BIT(4)  // PS/2 Interrupt 0
#define Int_WKO22           BIT(5)  // WKO[22]
#define SMFIS               BIT(6)  // SMFI Semaphore Interrupt
#define SMFIL               BIT(7)  // SMFI Lock Error Interrupt

// IER3 / ISR3
#define Int_KBCIBF          BIT(0)  // KBC Input Buffer Full Interrupt
#define Int_PMCIBF          BIT(1)  // PMC Input Buffer Full Interrupt
#define Int_PMC2OBE         BIT(2)  // PMC2 Output Buffer Empty Intr.
#define Int_PMC2IBF         BIT(3)  // PMC2 Input Buffer Full Intr.
#define Int_GINT            BIT(4)  // GINT from function 1 of GPD5
#define Int_EGPC            BIT(5)  // EGPC Interrupt
#define Int_EXTimer         BIT(6)  // External Timer Interrupt
#define Int_WKO21           BIT(7)  // WKO[21]

// IER4 / ISR4
#define Int_GPINT0          BIT(0)  // GPINT0
#define Int_GPINT1          BIT(1)  // GPINT1
#define Int_GPINT2          BIT(2)  // GPINT2
#define Int_GPINT3          BIT(3)  // GPINT3
#define Int_CIRGPINT        BIT(4)  // CIR GPINT
#define Int_SSPI            BIT(5)  // SSPI Interrupt
#define Int_UART1           BIT(6)  // UART1 Interrupt
#define Int_UART2           BIT(7)  // UART2 Interrupt

// IER5 / ISR5
//#define   Int_            BIT(0)  //
//#define   Int_            BIT(1)  //
//#define   Int_            BIT(2)  //
//#define   Int_            BIT(3)  //
//#define   Int_            BIT(4)  //
//#define   Int_            BIT(5)  //
//#define   Int_            BIT(6)  //
//#define   Int_            BIT(7)  //

// IER6 / ISR6
#define Int_WKO60           BIT(0)  // WKO[60]
#define Int_WKO61           BIT(1)  // WKO[61]
#define Int_WKO62           BIT(2)  // WKO[62]
#define Int_WKO63           BIT(3)  // WKO[63]
#define Int_WKO64           BIT(4)  // WKO[64]
#define Int_WKO65           BIT(5)  // WKO[65]
#define Int_WKO66           BIT(6)  // WKO[66]
#define Int_WKO67           BIT(7)  // WKO[67]

// IER7 / ISR7
#define Int_RTCT_Alarm1     BIT(0)  // RTCT Alarm 1
#define Int_RTCT_Alarm2     BIT(1)  // RTCT Alarm 2
#define Int_ET2Intr         BIT(2)  // External Timer 2 Interrupt
#define Int_DeferredSPI     BIT(3)  // Deferred SPI Instruction Interrupt
#define Int_TMRINTA0        BIT(4)  // TMRINTA0
#define Int_TMRINTA1        BIT(5)  // TMRINTA1
#define Int_TMRINTB0        BIT(6)  // TMRINTB0
#define Int_TMRINTB1        BIT(7)  // TMRINTB1

// IER8 / ISR8
#define Int_PMC2EXOBE       BIT(0)  // PMC2EX Output Buffer Empty Intr.
#define Int_PMC2EXIBF       BIT(1)  // PMC2EX Input Buffer Full Intr.
#define Int_PMC3OBE         BIT(2)  // PMC3 Output Buffer Empty Intr.
#define Int_PMC3IBF         BIT(3)  // PMC3 Input Buffer Full Interrupt
#define Int_PMC4OBE         BIT(4)  // PMC4 Output Buffer Empty Intr.
#define Int_PMC4IBF         BIT(5)  // PMC4 Input Buffer Full Intr.
//#define   Int_            BIT(6)  //
#define Int_I2BRAM          BIT(7)  // I2BRAM Interrupt

// IER9 / ISR9
#define Int_WKO70           BIT(0)  // WKO[70]
#define Int_WKO71           BIT(1)  // WKO[71]
#define Int_WKO72           BIT(2)  // WKO[72]
#define Int_WKO73           BIT(3)  // WKO[73]
#define Int_WKO74           BIT(4)  // WKO[74]
#define Int_WKO75           BIT(5)  // WKO[75]
#define Int_WKO76           BIT(6)  // WKO[76]
#define Int_WKO77           BIT(7)  // WKO[77]

// IER10 / ISR10
//#define   Int_            BIT(0)
#define Int_SMBCLK_Held     BIT(1)  // SMbus Clock Held intr.
#define Int_CEC             BIT(2)  // CEC Interrupt
#define Int_H2RAMLPC        BIT(3)  // H2RAM LPC Trigger
#define Int_KBSCAN_Valid    BIT(4)  // KB Scan Data Valid Interrupt
#define Int_WKO88           BIT(5)  // WKO[88]
#define Int_WKO89           BIT(6)  // WKO[89]
#define Int_WKO90           BIT(7)  // WKO[90]

// IER11 / ISR11
#define Int_WKO80           BIT(0)  // WKO[80]
#define Int_WKO81           BIT(1)  // WKO[81]
#define Int_WKO82           BIT(2)  // WKO[82]
#define Int_WKO83           BIT(3)  // WKO[83]
#define Int_WKO84           BIT(4)  // WKO[84]
#define Int_WKO85           BIT(5)  // WKO[85]
#define Int_WKO86           BIT(6)  // WKO[86]
#define Int_WKO87           BIT(7)  // WKO[87]

// IER12 / ISR12
#define Int_WKO91           BIT(0)  // WKO[91]
#define Int_WKO92           BIT(1)  // WKO[92]
#define Int_WKO93           BIT(2)  // WKO[93]
#define Int_WKO94           BIT(3)  // WKO[94]
#define Int_WKO95           BIT(4)  // WKO[95]
#define Int_WKO96           BIT(5)  // WKO[96]
#define Int_WKO97           BIT(6)  // WKO[97]
#define Int_WKO98           BIT(7)  // WKO[98]

// IER13 / ISR13
#define Int_WKO99           BIT(0)  // WKO[99]
#define Int_WKO100          BIT(1)  // WKO[100]
#define Int_WKO101          BIT(2)  // WKO[101]
#define Int_WKO102          BIT(3)  // WKO[102]
#define Int_WKO103          BIT(4)  // WKO[103]
#define Int_WKO104          BIT(5)  // WKO[104]
#define Int_WKO105          BIT(6)  // WKO[105]
#define Int_WKO106          BIT(7)  // WKO[106]

// IER14 / ISR14
#define Int_WKO107          BIT(0)  // WKO[107]
#define Int_WKO108          BIT(1)  // WKO[108]
#define Int_WKO109          BIT(2)  // WKO[109]
#define Int_WKO110          BIT(3)  // WKO[110]
#define Int_WKO111          BIT(4)  // WKO[111]
#define Int_WKO112          BIT(5)  // WKO[112]
#define Int_WKO113          BIT(6)  // WKO[113]
#define Int_WKO114          BIT(7)  // WKO[114]

// IER15 / ISR15
#define Int_WKO115          BIT(0)  // WKO[115]
#define Int_WKO116          BIT(1)  // WKO[116]
#define Int_WKO117          BIT(2)  // WKO[117]
#define Int_WKO118          BIT(3)  // WKO[118]
#define Int_WKO119          BIT(4)  // WKO[119]
#define Int_WKO120          BIT(5)  // WKO[120]
#define Int_WKO121          BIT(6)  // WKO[121]
#define Int_WKO122          BIT(7)  // WKO[122]

// IER16 / ISR16
#define Int_WKO128          BIT(0)  // WKO[128]
#define Int_WKO129          BIT(1)  // WKO[129]
#define Int_WKO130          BIT(2)  // WKO[130]
#define Int_WKO131          BIT(3)  // WKO[131]
#define Int_WKO132          BIT(4)  // WKO[132]
#define Int_WKO133          BIT(5)  // WKO[133]
#define Int_WKO134          BIT(6)  // WKO[134]
#define Int_WKO135          BIT(7)  // WKO[135]

// IER18 / ISR18
//#define Int_              BIT(0)
//#define Int_              BIT(1)
//#define Int_              BIT(2)
//#define Int_              BIT(3)
//#define Int_              BIT(4)
#define Int_PMC5OBE         BIT(5)  // PMC5 Output Buffer Empty Intr.
#define Int_PMC5IBF         BIT(6)  // PMC5 Input Buffer Full Intr.
#define Int_VCI             BIT(7)  // Voltage Compare Interrupt

// IER19 / ISR19
#define Int_PECI            BIT(0)  // INT152
#define Int_eSPI            BIT(1)  // INT153
#define Int_eSPI_VW         BIT(2)  // INT154
#define Int_P80_P81         BIT(3)  // INT155
//#define Int_              BIT(4)
#define Int_ET3Intr         BIT(5)  // INT157 External Timer 3 Interrupt
//#define Int_              BIT(6)
#define Int_PLL_Change      BIT(7)  // INT159 PLL Frequency Change Event

// IER20 / ISR20
#define Int_SMBUS4          BIT(0)  // INT160 SMBus E Interrupt
#define Int_SMBUS5          BIT(1)  // INT161 SMBus F Interrupt
//#define Int_              BIT(2)
//#define Int_              BIT(3)
//#define Int_              BIT(4)
//#define Int_              BIT(5)
//#define Int_              BIT(6)
//#define Int_              BIT(7)

// IER21 / ISR21
//#define Int_              BIT(0)
//#define Int_              BIT(1)
//#define Int_              BIT(2)
//#define Int_              BIT(3)
//#define Int_              BIT(4)
//#define Int_              BIT(5)
//#define Int_              BIT(6)
#define Int_ET4Intr         BIT(7)  // INT175 External Timer 4 Interrupt

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge)
//-----------------------------------------------------------------------------
extern ECReg    IHIOA;              // Indirect Host I/O Address
extern ECReg    IHD;                // Indirect Host Data
extern ECReg    LSIOHA;             // Lock Super I/O Host Access
extern ECReg    SIOLV;              // Super I/O Access Lock Violation
extern ECReg    IBMAE;              // EC to I-Bus Modules Access Enable
extern ECReg    IBCTL;              // I-Bus Control

// Lock Super I/O Host Access Register
#define LKCFG               BIT(0)  // Lock PNPCFG Registers Host Access

// Super I/O Access Lock Violation Register
#define CFGLV               BIT(0)  // PNPCFG Register Lock Violation

// EC to I-Bus Modules Access Enable Register
#define SWUCAE              BIT(2)  // Mobile System Wake-Up Control Access Enable
#define CFGAE               BIT(0)  // PNPCFG Register EC Access Enable

// I-Bus Control Register
#define CWIB                BIT(2)  // EC Write to I-Bus
#define CRIB                BIT(1)  // EC Read from I-Bus
#define CSAE                BIT(0)  // EC to I-Bus Access Enabled

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC)
//-----------------------------------------------------------------------------
extern ECReg    KBHICR          ;// 0x1300   KBC Host Interface Control Register
extern ECReg    KBIRQR          ;// 0x1302   KBC Interrupt Control Register
extern ECReg    KBHISR          ;// 0x1304   KBC Host Interface Keyboard/Mouse Status Register
extern ECReg    KBHIKDOR        ;// 0x1306   KBC Host Interface Keyboard Data Output Register
extern ECReg    KBHIMDOR        ;// 0x1308   KBC Host Interface Mouse Data Output Register
extern ECReg    KBHIDIR         ;// 0x130A   KBC Host Interface Keyboard/Mouse Data Input Register

// KBC Host Interface Control Register
#define PM1ICIE             BIT(6)  // PM Channel 1 Input Buffer Full 8032 Interrupt Enable
#define PM1OCIE             BIT(5)  // PM Channel 1 Output Buffer Empty 8032 Interrupt Enable
#define PM1HIE              BIT(4)  // PM Channel 1 Host Interface Interrupt Enable
#define IBFCIE              BIT(3)  // Input Buffer Full 8032 Interrupt Enable
#define OBECIE              BIT(2)  // Output Buffer Empty 8032 Interrupt Enable
#define OBFMIE              BIT(1)  // Output Buffer Full Mouse Interrupt Enable
#define OBFKIE              BIT(0)  // Output Buffer Full Keyboard Interrupt Enable

// KBC Interrupt Control Register
#define IRQNP               BIT(6)  // Interrupt Negative Polarity
#define IRQ11B              BIT(2)  // IRQ11 Control Bit
#define IRQ12B              BIT(1)  // IRQ12 Control Bit
#define IRQ1B               BIT(0)  // IRQ1 Control Bit

// KBC Host Interface Keyboard/Mouse Status Register
#define PARE                BIT(7)  // Programming Data
#define GTIM                BIT(6)  // Programming Data
#define AOBF                BIT(5)  // Programming Data
#define KEYL                BIT(4)  // Programming Data
#define C_D                 BIT(3)  // Command or data port
#define SYSF                BIT(2)  // Programming Data (System flag)
#define IBF                 BIT(1)  // Input Buffer Full
#define OBF                 BIT(0)  // Output Buffer Full

//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC)
//-----------------------------------------------------------------------------
extern ECReg    SWCTL1;             // SWUC Control Status 1 Register
extern ECReg    SWCTL2;             // SWUC Control Status 2 Register
extern ECReg    SWCTL3;             // SWUC Control Status 3 Register
extern ECReg    SWCBALR;            // SWUC Host Configuration Base Address Low Byte Register
extern ECReg    SWCBAHR;            // SWUC Host Configuration Base Address High Byte Register
extern ECReg    SWCIER;             // SWUC Interrupt Enable Register
extern ECReg    SWCHSTR;            // SWUC Host Event Status Register
extern ECReg    SWCHIER;            // SWUC Host Event Interrupt Enable Register

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC)
//-----------------------------------------------------------------------------
extern ECReg    PM1STS;             // Host Interface PM Channel 1 Status
extern ECReg    PM1DO;              // Host Interface PM Channel 1 Data Out Port
extern ECReg    PM1DOSCI;           // Host Interface PM Channel 1 Data Out Port with SCI
extern ECReg    PM1DOSMI;           // Host Interface PM Channel 1 Data Out Port with SMI
extern ECReg    PM1DI;              // Host Interface PM Channel 1 Data In Port
extern ECReg    PM1DISCI;           // Host Interface PM Channel 1 Data In Port with SCI
extern ECReg    PM1CTL;             // Host Interface PM Channel 1 Control
extern ECReg    PM1IC;              // Host Interface PM Channel 1 Interrupt Control
#define PMIC_SMI            BIT(1)
#define PMIC_SCI            BIT(2)
extern ECReg    PM1IE;              // Host Interface PM Channel 1 Interrupt Enable

extern ECReg    PM2STS;             // Host Interface PM Channel 2 Status
extern ECReg    PM2DO;              // Host Interface PM Channel 2 Data Out Port
extern ECReg    PM2DOSCI;           // Host Interface PM Channel 2 Data Out Port with SCI
extern ECReg    PM2DOSMI;           // Host Interface PM Channel 2 Data Out Port with SMI
extern ECReg    PM2DI;              // Host Interface PM Channel 2 Data In Port
extern ECReg    PM2DISCI;           // Host Interface PM Channel 2 Data In Port with SCI
extern ECReg    PM2CTL;             // Host Interface PM Channel 2 Control
extern ECReg    PM2IC;              // Host Interface PM Channel 2 Interrupt Control
extern ECReg    PM2IE;              // Host Interface PM Channel 2 Interrupt Enable

extern ECReg    MBXCTRL;            // Mailbox Control

extern ECReg    PM3STS;             // Host Interface PM Channel 3 Status
extern ECReg    PM3DO;              // Host Interface PM Channel 3 Data Out Port
extern ECReg    PM3DI;              // Host Interface PM Channel 3 Data In Port
extern ECReg    PM3CTL;             // Host Interface PM Channel 3 Control
extern ECReg    PM3IC;              // Host Interface PM Channel 3 Interrupt Control
extern ECReg    PM3IE;              // Host Interface PM Channel 3 Interrupt Enable

extern ECReg    PM4STS;             // Host Interface PM Channel 4 Status
extern ECReg    PM4DO;              // Host Interface PM Channel 4 Data Out Port
extern ECReg    PM4DI;              // Host Interface PM Channel 4 Data In Port
extern ECReg    PM4CTL;             // Host Interface PM Channel 4 Control
extern ECReg    PM4IC;              // Host Interface PM Channel 4 Interrupt Control
extern ECReg    PM4IE;              // Host Interface PM Channel 4 Interrupt Enable

extern ECReg    PM5STS;             // Host Interface PM Channel 5 Status
extern ECReg    PM5DO;              // Host Interface PM Channel 5 Data Out Port
extern ECReg    PM5DI;              // Host Interface PM Channel 5 Data In Port
extern ECReg    PM5CTL;             // Host Interface PM Channel 5 Control
extern ECReg    PM5IC;              // Host Interface PM Channel 5 Interrupt Control
extern ECReg    PM5IE;              // Host Interface PM Channel 5 Interrupt Enable

// PM Status Register
#define SMIEVT              BIT(6)
#define SCIEVT              BIT(5)
#define BURST               BIT(4)
#define P_C_D               BIT(3)  // Command or data port
#define P_IBF               BIT(1)  // Input Buffer Full
#define P_OBF               BIT(0)  // Output Buffer Full

// PM Control
#define APM                 BIT(7)  // Enhance PM Mode
#define SCINP               BIT(6)  // SCI Negative Polarity
#define OBEIE               BIT(1)  // Output Buffer Empty Interrupt Enable
#define IBFIE               BIT(0)  // Input Buffer Full Interrupt Enable

// PM Interrupt Control
#define SMINP               BIT(6)  // SMI Negative Polarity
#define SCIB                BIT(2)  // Host SCI Control Bit
#define SMIB                BIT(1)  // Host SMI Control Bit
#define IRQB                BIT(0)  // Host IRQ Control Bit

// PM Interrupt Enable
#define HWSMIEN             BIT(5)  // Hardware SMI Enable
#define HWSCIEN             BIT(4)  // Hardware SCI Enable
#define HWIRQEN             BIT(3)  // Hardware IRQ Enable
#define SMIEN               BIT(2)  // SMI Enable
#define SCIEN               BIT(1)  // SCI Enable
#define IRQEN               BIT(0)  // IRQ Enable

// PM Interrupt Enable
#define MBXEN               BIT(7)  // Mailbox Enable

extern ECReg    MBXEC[];            // 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control Register
//-----------------------------------------------------------------------------
extern ECReg    GCR;                // General Control Register
extern ECReg    GCR1;               // General Control 1 Register
#define SPICTRL_0   BIT(4)
#define SPICTRL_1   BIT(5)  // SPI interface control
#define SSSPIBP     BIT(6)  // Support SSPI BUSY Pin

extern ECReg    GCR2;               // General Control 2 Register
#define TACH2E      BIT(7)  // TACH2 Enable
#define CK32OE      BIT(6)  // CK32K Out Enable
#define SMB3E       BIT(5)  // SMBus Channel 4 Enable
#define SMB3EN      BIT(5)  // SMBus Channel 4 Enable
#define PECIE       BIT(4)  // PECI Enable
#define TMB1EN      BIT(3)
#define TMB0EN      BIT(2)
#define TMA1EN      BIT(1)
#define TMA0EN      BIT(0)

extern ECReg    GCR3;               // General Control 3 Register
extern ECReg    GCR4;               // General Control 4 Register
extern ECReg    GCR5;               // General Control 5 Register
extern ECReg    GCR6;               // General Control 6 Register
extern ECReg    GCR7;               // General Control 7 Register
extern ECReg    GCR8;               // General Control 8 Register
/* GCR8 0x16F7  General Control 8 Register */
#define CECEN           BIT(5)
#define PWSW2EN1        BIT(4)

extern ECReg    GCR9;               // General Control 9 Register
/* GCR9 0x16F8  General Control 9 Register */
#define PWSW2RPP        BIT(6)
#define PWSW2EN2        BIT(5)
#define PWSWDTGPEN      BIT(3)
#define PWSW1EN2        BIT(2)
#define PWSWlEN1        BIT(1)
#define CHKPWRSW        BIT(0)

extern ECReg    GCR10;              // General Control 10 Register
/* GCR10 0x16F9  General Control 10 Register */
#define PWDT2CNTR_2     BIT(2)
#define PWDT2CNTR_1     BIT(1)
#define PWDT2CNTR_0     BIT(0)
#define PWRSW_WDT2_10S  0x00
#define PWRSW_WDT2_8S   0x01
#define PWRSW_WDT2_12S  0x02
#define PWRSW_WDT2_7d5S 0x04
#define PWRSW_WDT2_15S  0x07

extern ECReg    GCR11;              // General Control 11 Register
/* GCR11 0x16FA  General Control 11 Register */
#define PWDR1CNTR_3     BIT(3)
#define PWDR1CNTR_2     BIT(2)
#define PWDR1CNTR_1     BIT(1)
#define PWDR1CNTR_0     BIT(0)
#define PWRSW_WDT1_4S   0x00
#define PWRSW_WDT1_5S   0x01
#define PWRSW_WDT1_6S   0x02
#define PWRSW_WDT1_7S   0x03
#define PWRSW_WDT1_8S   0x04
#define PWRSW_WDT1_9S   0x05
#define PWRSW_WDT1_10S  0x06
#define PWRSW_WDT1_11S  0x07
#define PWRSW_WDT1_12S  0x08

extern ECReg    GCR12;              // General Control 12 Register
extern ECReg    GCR13;              // General Control 13 Register
/* GCR13 0x16FC  General Control 13 Register */
#define GPJ0LE          BIT(2)
#define GPD7LE          BIT(1)
#define GPD6LE          BIT(0)

extern ECReg    GCR14;              // General Control 14 Register
#define WUIDIE          BIT(3)  // WUI Debounce Independent Enable
#define WUIDS_Disable   0x00
#define WUIDS_16ms      0x01
#define WUIDS_64ms      0x02
#define WUIDS_1sec      0x03
#define WUIDS_2sec      0x04

extern ECReg    GCR15;              // General Control 15 Register
#define SMB5EN          BIT(5)  // SMBus Channel 5 Enable
#define SMB4EN          BIT(4)  // SMBus Channel 4 Enable
#define TACH2BEN        BIT(3)  // TACH2B Enable, 1b: GPJ1 will select
                                // TACH2B as its alternative function
#define CMP2GPEN        BIT(2)  // Comparator 2 GPIO Enable
#define CMP1GPEN        BIT(1)  // Comparator 1 GPIO Enable
#define CMP0GPEN        BIT(0)  // Comparator 0 GPIO Enable

extern ECReg    PGWCR;              // Power Good Watch Control Register
#define PGWM1EN         BIT(7)  // Power Good Watch Mode 1 Enable
#define PGWFS           BIT(6)  // Power Good Watch Flag Status
#define PWSW2DLEN       BIT(3)  // PWRSW WDT 2 to Drop Low Enable
#define PWDT2TDLF       BIT(2)  // PWRSW WDT 2 to Drop Low Flag

extern ECReg    GCR16;              // General Control 16 Register
#define WUI1DS_Disable  0x00
#define WUI1DS_16ms     0x10
#define WUI1DS_64ms     0x20
#define WUI1DS_1sec     0x30
#define WUI1DS_2sec     0x40
#define WUI0DS_Disable  0x00
#define WUI0DS_16ms     0x01
#define WUI0DS_64ms     0x02
#define WUI0DS_1sec     0x03
#define WUI0DS_2sec     0x04

extern ECReg    GCR17;              // General Control 17 Register
#define WUI3DS_Disable  0x00    // WUI3 Debounce Select
#define WUI3DS_16ms     0x10
#define WUI3DS_64ms     0x20
#define WUI3DS_1sec     0x30
#define WUI3DS_2sec     0x40
#define WUI2DS_Disable  0x00    // WUI2 Debounce Select
#define WUI2DS_16ms     0x01
#define WUI2DS_64ms     0x02
#define WUI2DS_1sec     0x03
#define WUI2DS_2sec     0x04

extern ECReg    GCR18;              // General Control 18 Register
#define WUI5DS_Disable  0x00    // WUI5 Debounce Select
#define WUI5DS_16ms     0x10
#define WUI5DS_64ms     0x20
#define WUI5DS_1sec     0x30
#define WUI5DS_2sec     0x40
#define PWRSWDS_Disable 0x00    // PWRSW Debounce Select
#define PWRSWDS_16ms    0x01
#define PWRSWDS_64ms    0x02
#define PWRSWDS_1sec    0x03
#define PWRSWDS_2sec    0x04

extern ECReg    GCR19;              // General Control 19 Register
#define GPB5VS          BIT(7)  // Input Voltage Selection, 0b:3.3V,1b:1.8V
#define GPB6VS          BIT(6)
#define GPC1VS          BIT(5)
#define GPC2VS          BIT(4)
#define GPC7VS          BIT(3)
#define GPD0VS          BIT(2)
#define GPD1VS          BIT(1)
#define GPD2VS          BIT(0)

extern ECReg    GCR20;              // General Control 20 Register
#define GPD3VS          BIT(7)  // Input Voltage Selection, 0b:3.3V,1b:1.8V
#define GPD4VS          BIT(6)
#define GPE0VS          BIT(5)
#define GPE6VS          BIT(4)
#define GPE7VS          BIT(3)
#define GPF2VS          BIT(2)
#define GPF3VS          BIT(1)
#define GPF4VS          BIT(0)

extern ECReg    GCR21;              // General Control 21 Register
#define GPF5VS          BIT(7)  // Input Voltage Selection, 0b:3.3V,1b:1.8V
#define GPF6VS          BIT(6)
#define GPF7VS          BIT(5)
#define GPG1VS          BIT(4)
#define GPG6VS          BIT(3)
#define GPH0VS          BIT(2)
#define GPH1VS          BIT(1)
#define GPH2VS          BIT(0)

extern ECReg    GCR22;              // General Control 22 Register
#define VCCPDS          BIT(7)  // Input Voltage Selection, 0b:3.3V,1b:1.8V
#define GPA4VS          BIT(3)
#define GPA5VS          BIT(2)
#define GPB3VS          BIT(1)
#define GPB4VS          BIT(0)

extern ECReg    GCR23;
#define GPM6PDS         BIT(0)  // GPM6 Power Domain Select
/* 0b: ALERT#/SERIRQ/GPM6 is supplied by VFSPI.
   1b: ALERT#/SERIRQ/GPM6 is supplied by VCC.
*/

extern ECReg    GCR24;
extern ECReg    GCR25;

extern ECReg    GPDRA;              // Port A Data Register
extern ECReg    GPDRB;              // Port B Data Register
extern ECReg    GPDRC;              // Port C Data Register
extern ECReg    GPDRD;              // Port D Data Register
extern ECReg    GPDRE;              // Port E Data Register
extern ECReg    GPDRF;              // Port F Data Register
extern ECReg    GPDRG;              // Port G Data Register
extern ECReg    GPDRH;              // Port H Data Register
extern ECReg    GPDRI;              // Port I Data Register
extern ECReg    GPDRJ;              // Port J Data Register
extern ECReg    GPDRM;              // Port M Data Register

extern ECReg    GPCRA0;             // Port Control A0 Registers
extern ECReg    GPCRA1;             // Port Control A1 Registers
extern ECReg    GPCRA2;             // Port Control A2 Registers
extern ECReg    GPCRA3;             // Port Control A3 Registers
extern ECReg    GPCRA4;             // Port Control A4 Registers
extern ECReg    GPCRA5;             // Port Control A5 Registers
extern ECReg    GPCRA6;             // Port Control A6 Registers
extern ECReg    GPCRA7;             // Port Control A7 Registers

extern ECReg    GPCRB0;             // Port Control B0 Registers
extern ECReg    GPCRB1;             // Port Control B1 Registers
extern ECReg    GPCRB2;             // Port Control B2 Registers
extern ECReg    GPCRB3;             // Port Control B3 Registers
extern ECReg    GPCRB4;             // Port Control B4 Registers
extern ECReg    GPCRB5;             // Port Control B5 Registers
extern ECReg    GPCRB6;             // Port Control B6 Registers
extern ECReg    GPCRB7;             // Port Control B7 Registers

extern ECReg    GPCRC0;             // Port Control C0 Registers
extern ECReg    GPCRC1;             // Port Control C1 Registers
extern ECReg    GPCRC2;             // Port Control C2 Registers
extern ECReg    GPCRC3;             // Port Control C3 Registers
extern ECReg    GPCRC4;             // Port Control C4 Registers
extern ECReg    GPCRC5;             // Port Control C5 Registers
extern ECReg    GPCRC6;             // Port Control C6 Registers
extern ECReg    GPCRC7;             // Port Control C7 Registers

extern ECReg    GPCRD0;             // Port Control D0 Registers
extern ECReg    GPCRD1;             // Port Control D1 Registers
extern ECReg    GPCRD2;             // Port Control D2 Registers
extern ECReg    GPCRD3;             // Port Control D3 Registers
extern ECReg    GPCRD4;             // Port Control D4 Registers
extern ECReg    GPCRD5;             // Port Control D5 Registers
extern ECReg    GPCRD6;             // Port Control D6 Registers
extern ECReg    GPCRD7;             // Port Control D7 Registers

extern ECReg    GPCRE0;             // Port Control E0 Registers
extern ECReg    GPCRE1;             // Port Control E1 Registers
extern ECReg    GPCRE2;             // Port Control E2 Registers
extern ECReg    GPCRE3;             // Port Control E3 Registers
extern ECReg    GPCRE4;             // Port Control E4 Registers
extern ECReg    GPCRE5;             // Port Control E5 Registers
extern ECReg    GPCRE6;             // Port Control E6 Registers
extern ECReg    GPCRE7;             // Port Control E7 Registers

extern ECReg    GPCRF0;             // Port Control F0 Registers
extern ECReg    GPCRF1;             // Port Control F1 Registers
extern ECReg    GPCRF2;             // Port Control F2 Registers
extern ECReg    GPCRF3;             // Port Control F3 Registers
extern ECReg    GPCRF4;             // Port Control F4 Registers
extern ECReg    GPCRF5;             // Port Control F5 Registers
extern ECReg    GPCRF6;             // Port Control F6 Registers
extern ECReg    GPCRF7;             // Port Control F7 Registers

extern ECReg    GPCRG0;             // Port Control G0 Registers
extern ECReg    GPCRG1;             // Port Control G1 Registers
extern ECReg    GPCRG2;             // Port Control G2 Registers
extern ECReg    GPCRG3;             // Port Control G3 Registers
extern ECReg    GPCRG4;             // Port Control G4 Registers
extern ECReg    GPCRG5;             // Port Control G5 Registers
extern ECReg    GPCRG6;             // Port Control G6 Registers
extern ECReg    GPCRG7;             // Port Control G7 Registers

extern ECReg    GPCRH0;             // Port Control H0 Registers
extern ECReg    GPCRH1;             // Port Control H1 Registers
extern ECReg    GPCRH2;             // Port Control H2 Registers
extern ECReg    GPCRH3;             // Port Control H3 Registers
extern ECReg    GPCRH4;             // Port Control H4 Registers
extern ECReg    GPCRH5;             // Port Control H5 Registers
extern ECReg    GPCRH6;             // Port Control H6 Registers
extern ECReg    GPCRH7;             // Port Control H7 Registers

extern ECReg    GPCRI0;             // Port Control I0 Registers
extern ECReg    GPCRI1;             // Port Control I1 Registers
extern ECReg    GPCRI2;             // Port Control I2 Registers
extern ECReg    GPCRI3;             // Port Control I3 Registers
extern ECReg    GPCRI4;             // Port Control I4 Registers
extern ECReg    GPCRI5;             // Port Control I5 Registers
extern ECReg    GPCRI6;             // Port Control I6 Registers
extern ECReg    GPCRI7;             // Port Control I7 Registers

extern ECReg    GPCRJ0;             // Port Control J0 Registers
extern ECReg    GPCRJ1;             // Port Control J1 Registers
extern ECReg    GPCRJ2;             // Port Control J2 Registers
extern ECReg    GPCRJ3;             // Port Control J3 Registers
extern ECReg    GPCRJ4;             // Port Control J4 Registers
extern ECReg    GPCRJ5;             // Port Control J5 Registers
extern ECReg    GPCRJ6;             // Port Control J6 Registers
extern ECReg    GPCRJ7;             // Port Control J7 Registers

extern ECReg    GPCRM0;             // Port Control M0 Registers
extern ECReg    GPCRM1;             // Port Control M1 Registers
extern ECReg    GPCRM2;             // Port Control M2 Registers
extern ECReg    GPCRM3;             // Port Control M3 Registers
extern ECReg    GPCRM4;             // Port Control M4 Registers
extern ECReg    GPCRM5;             // Port Control M5 Registers
extern ECReg    GPCRM6;             // Port Control M6 Registers

extern ECReg    GPDMRA;             // Port A Data Mirror Register
extern ECReg    GPDMRB;             // Port B Data Mirror Register
extern ECReg    GPDMRC;             // Port C Data Mirror Register
extern ECReg    GPDMRD;             // Port D Data Mirror Register
extern ECReg    GPDMRE;             // Port E Data Mirror Register
extern ECReg    GPDMRF;             // Port F Data Mirror Register
extern ECReg    GPDMRG;             // Port G Data Mirror Register
extern ECReg    GPDMRH;             // Port H Data Mirror Register
extern ECReg    GPDMRI;             // Port I Data Mirror Register
extern ECReg    GPDMRJ;             // Port J Data Mirror Register
extern ECReg    GPDMRM;             // Port M Data Mirror Register
#define ESPI_CS_PIN         BIT(5)

extern ECReg    GPOTA;              // Output Type Register
extern ECReg    GPOTB;              // Output Type Register
extern ECReg    GPOTD;              // Output Type Register
extern ECReg    GPOTE;              // Output Type Register
extern ECReg    GPOTF;              // Output Type Register
extern ECReg    GPOTH;              // Output Type Register
extern ECReg    GPOTJ;              // Output Type Register

// General Control Register
#define GFLE                BIT(7)  // GPB5 Follow LPCRST# Enable
#define WUI7EN              BIT(6)  // WUI7 Enabled
#define WUI6EN              BIT(5)  // WUI6 Enabled
//      -                   BIT(4)  // -
//      -                   BIT(3)  // -
#define LPCRSTEN_GPB7       BIT(2)  // LPC Reset is enabled on GPB7
#define LPCRSTEN_GPD2       BIT(1)  // LPC Reset is enabled on GPD2
//      -                   BIT(0)  // -

// Port Control n Registers
#define PM_Input            BIT(7)  // Input
#define PM_Output           BIT(6)  // Outpur
#define PM_ALT              0x00    // Alternate Function
#define PM_PullUp           BIT(2)  // Port Pin Pull Up
#define PM_PullDown         BIT(1)  // Port Pin Pull Down
#define PM_8mA              0x10    // sourcing/sinking 8mA/8mA
#define PM_12mA             0x18    // sourcing/sinking 12mA/12mA
#define PM_16mA             0x38    // sourcing/sinking 16mA/16mA

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface Register
//-----------------------------------------------------------------------------
extern ECReg    PSCTL1;             // PS/2 Control Register 1
extern ECReg    PSCTL2;             // PS/2 Control Register 2
extern ECReg    PSCTL3;             // PS/2 Control Register 3
extern ECReg    PSINT1;             // PS/2 Interrupt Control Register 1
extern ECReg    PSINT2;             // PS/2 Interrupt Control Register 2
extern ECReg    PSINT3;             // PS/2 Interrupt Control Register 3
extern ECReg    PSSTS1;             // PS/2 Status Register 1
extern ECReg    PSSTS2;             // PS/2 Status Register 2
extern ECReg    PSSTS3;             // PS/2 Status Register 3
extern ECReg    PSDAT1;             // PS/2 Data Register 1
extern ECReg    PSDAT2;             // PS/2 Data Register 2
extern ECReg    PSDAT3;             // PS/2 Data Register 3

// PS/2 Control Register
#define DCEN                BIT(4)  // Debounce Circuit Enable
#define TRMS                BIT(3)  // Transmit,Receive Mode Selection
#define PSHE                BIT(2)  // PS/2 Hardware Enable
#define CCLK                BIT(1)  // Control CLK Line
#define CDAT                BIT(0)  // Control DATA Line

// PS/2 Interrupt Control Register
#define TDIE                BIT(2)  // Transaction Done Interrupt Enable
#define SIE                 BIT(1)  // Start Interrupt Enable
#define SMIE                BIT(0)  // Software Mode Interrupt Enable

// PS/2 Status Register
#define FER                 BIT(5)  // Frame Error
#define PER                 BIT(4)  // Parity Error
#define TDS                 BIT(3)  // Transaction Done Status
#define SS                  BIT(2)  // Start Status
#define CLS                 BIT(1)  // CLK Line Status
#define DLS                 BIT(0)  // DATA Line Status

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM)
//-----------------------------------------------------------------------------
extern ECReg    C0CPRS;             // Channel 0 Clock Prescaler Register
extern ECReg    CTR0;               // Cycle Time 0
#define CTR         CTR0     
extern ECReg    DCR0;               // Channel 0 PWM Duty Cycle
extern ECReg    DCR1;               // Channel 1 PWM Duty Cycle
extern ECReg    DCR2;               // Channel 2 PWM Duty Cycle
extern ECReg    DCR3;               // Channel 3 PWM Duty Cycle
extern ECReg    DCR4;               // Channel 4 PWM Duty Cycle
extern ECReg    DCR5;               // Channel 5 PWM Duty Cycle
extern ECReg    DCR6;               // Channel 6 PWM Duty Cycle
extern ECReg    DCR7;               // Channel 7 PWM Duty Cycle
extern ECReg    PWMPOL;             // PWM Polarity
#define PWM_INVP7           BIT(7)  // PWM7 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP6           BIT(6)  // PWM6 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP5           BIT(5)  // PWM5 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP4           BIT(4)  // PWM4 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP3           BIT(3)  // PWM3 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP2           BIT(2)  // PWM2 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP1           BIT(1)  // PWM1 Inverse PWM Outputs 0:Non-inverting, 1:Inverting
#define PWM_INVP0           BIT(0)  // PWM0 Inverse PWM Outputs 0:Non-inverting, 1:Inverting

extern ECReg    PCFSR;              // Prescaler Clock Frequency Select Register
extern ECReg    PCSSGL;             // Prescaler Clock Source Select Group Low
extern ECReg    PCSSGH;             // Prescaler Clock Source Select Group High
extern ECReg    CR256PCSSG;         // CR256 Prescaler Clock Source Select Group
extern ECReg    PCSGR;              // Prescaler Clock Source Gating Register
extern ECReg    F1TLRR;             // Fan 1 Tachometer LSB Reading
extern ECReg    F1TMRR;             // Fan 1 Tachometer MSB Reading
extern ECReg    F2TLRR;             // Fan 2 Tachometer LSB Reading
extern ECReg    F2TMRR;             // Fan 2 Tachometer MSB Reading
extern ECReg    ZINTSCR;            // Zone Interrupt Status Control
#define T0DIE               BIT(5)  // TACH0A/TACH0B Data-valid Interrupt Enable
#define T0DIC               BIT(4)  // TACH0A/TACH0B Data-valid Interrupt Clear
#define T0DIS               BIT(3)  // TACH0A/TACH0B Data-valid Interrupt Status
#define T1DIE               BIT(2)  // TACH1A/TACH1B Data-valid Interrupt Enable
#define T1DIC               BIT(1)  // TACH1A/TACH1B Data-valid Interrupt Clear
#define T1DIS               BIT(0)  // TACH1A/TACH1B Data-valid Interrupt Status

extern ECReg    ZTIER;              // PWM Clock Control Register
#define PCCE                BIT(1)  // PWM Clock Counter Enable
#define PWMTM               BIT(0)  // PWM Test Mode

extern ECReg    TSWCTLR;            // Tachometer Switch Control Register
extern ECReg    C4CPRS;             // Channel 4 Clock Prescaler Register
extern ECReg    C4MCPRS;            // Channel 4 Clock Prescaler MSB Register
extern ECReg    C6CPRS;             // Channel 6 Clock Prescaler Register
extern ECReg    C6MCPRS;            // Channel 6 Clock Prescaler MSB Register
extern ECReg    C7CPRS;             // Channel 7 Clock Prescaler Register
extern ECReg    C7MCPRS;            // Channel 7 Clock Prescaler MSB Register
extern ECReg    CLK6MSEL;           // Clock 6MHz Select Register
#define CTRMODE             BIT(4)  // Cycle Time Register Mode

extern ECReg    CTR1;               // Cycle Time 1
extern ECReg    CTR2;               // Cycle Time 2
extern ECReg    CTR3;               // Cycle Time 3
extern ECReg    PWM5TOCTRL;         // PWM5 Timeout Control Register
#define BME                 BIT(4)  // Backlight Mode Enable

extern ECReg    F3TLRR;             // Fan 3 Tachometer LSB Reading
extern ECReg    F3TMRR;             // Fan 3 Tachometer MSB Reading

extern ECReg    ZINTSCR2;           // Zone Interrupt Status Control Register 2
#define T2DIE               BIT(2)  // TACH2 Data-valid Interrupt Enable
#define T2DIC               BIT(1)  // TACH2 Data-valid Interrupt Clear
#define T2DIS               BIT(0)  // TACH2 Data-valid Interrupt Status

extern ECReg    TSWCTRL;            // Tachometer Switch Control Register
#define T0DVS               BIT(3)  // TACH0A/TACH0B Data-valid Status
#define T0CHSEL             BIT(2)  // TACH0A/TACH0B Channel Selection
#define T1DVS               BIT(1)  // TACH1A/TACH1B Data-valid Status
#define T1CHSEL             BIT(0)  // TACH1A/TACH1B Channel Selection

extern ECReg    PWMODENR;           // PWM Output Open-Drain Enable Register
#define PWM7ODEN            BIT(7)  // PWM7 Output Open-Drain Enable
#define PWM6ODEN            BIT(6)  // PWM6 Output Open-Drain Enable
#define PWM5ODEN            BIT(5)  // PWM5 Output Open-Drain Enable
#define PWM4ODEN            BIT(4)  // PWM4 Output Open-Drain Enable
#define PWM3ODEN            BIT(3)  // PWM3 Output Open-Drain Enable
#define PWM2ODEN            BIT(2)  // PWM2 Output Open-Drain Enable
#define PWM1ODEN            BIT(1)  // PWM1 Output Open-Drain Enable
#define PWM0ODEN            BIT(0)  // PWM0 Output Open-Drain Enable

extern ECReg    BLDR;               // Backlight Duty Register
extern ECReg    TSWCTLR2;           // Tachometer Switch Control Register 2
extern ECReg    PWM0LHE;            // PWM0 LED Dimming Enable Register
#define PWM0HE              BIT(0)  // PWM0 Dimming Enable

extern ECReg    PWM0LCR1;           // PWM0 LED Dimming Control Register 1
extern ECReg    PWM0LCR2;           // PWM0 LED Dimming Control Register 2
extern ECReg    PWM1LHE;            // PWM1 LED Dimming Enable Register
#define PWM1HE              BIT(0)  // PWM1 Dimming Enable

extern ECReg    PWM1LCR1;           // PWM1 LED Dimming Control Register 1
extern ECReg    PWM1LCR2;           // PWM1 LED Dimming Control Register 2
extern ECReg    PWMLCCR;            // PWM Load Counter Control
#define PWM7LC              BIT(7)  // PWM7 Load Control
#define PWM6LC              BIT(6)  // PWM6 Load Control
#define PWM5LC              BIT(5)  // PWM5 Load Control
#define PWM4LC              BIT(4)  // PWM7 Load Control
#define PWM3LC              BIT(3)  // PWM3 Load Control
#define PWM2LC              BIT(2)  // PWM2 Load Control
#define PWM1LC              BIT(1)  // PWM1 Load Control
#define PWM0LC              BIT(0)  // PWM0 Load Control

extern ECReg    CTR1M;              // Cycle Time Register 1 MSB
extern ECReg    DCR2M;              // PWM Duty Cycle Register 2 MSB
extern ECReg    DCR3M;              // PWM Duty Cycle Register 3 MSB


//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC)
//-----------------------------------------------------------------------------
extern ECReg    ADCSTS;             // ADC Status
// ADC Status Register
#define ADCCTS1             BIT(7)  // ADC Conversion Time Select 1
#define SDIVSRC             BIT(5)  // Clock Source Select
                                    // 0: Select EC Clock (frequency = FreqEC)
                                    // 1: Select PLL Clock (frequency = FreqPLL)
#define AINITB              BIT(3)  // Analog Accuracy Initialization Bit
#define ADCPS               BIT(2)  // ADC Power Statement
#define DOVE                BIT(1)  // Data Overflow Event
#define EOCE                BIT(0)  // End-of-Cycle Event

extern ECReg    ADCCFG;             // ADC Configuration
// ADC Configuration Register
#define ADCCTS0             BIT(5)  // ADC Conversion Time Select 0
#define DFILEN              BIT(5)  // Digital Filter Enable (IT858X)
#define INTECEN             BIT(2)  // Interrupt from End-of-Cycle Event Enable
#define ADCEN               BIT(0)  // ADC Module Enable

extern ECReg    ADCCTL;             // ADC Clock Control
extern ECReg    ADCGCR;             // ADC General Control Register
#define ADCDBKEN            BIT(7)  // ADC Data Buffer Keep Enable

extern ECReg    VCH0CTL;            // Voltage Channel 0 Channel Control
// Voltage Channel Control Register
#define DATVAL              BIT(7)  // Data Valid
#define INTDVEN             BIT(5)  // Interrupt from Data Valid Enable
#define SELIN_CHANNEL_0     0x00
#define SELIN_CHANNEL_1     0x01
#define SELIN_CHANNEL_2     0x02
#define SELIN_CHANNEL_3     0x03
#define SELIN_CHANNEL_4     0x04
#define SELIN_CHANNEL_5     0x05
#define SELIN_CHANNEL_6     0x06
#define SELIN_CHANNEL_7     0x07
#define SELIN_CHANNEL_8     0x08
#define SELIN_CHANNEL_9     0x09
#define SELIN_CHANNEL_10    0x0A
#define SELIN_CHANNEL_11    0x0B
#define SELIN_CHANNEL_12    0x0C
#define SELIN_DISABLED      0x1F

extern ECReg    KDCTL;              // Calibration Data Control Register
// Calibration Data Control Register
#define AHCE                BIT(7)  // Automatic Hardware Calibration Enable
#define HCDATVAL            BIT(5)  // High-Scaler Calibration Data Valid
#define GCDATVAL            BIT(4)  // Gain_Error Calibration Data Valid
#define VHSCKE              BIT(1)  // Volt High Scale Calibration Enable
#define GECKE               BIT(0)  // Gain_Error Calibration Enable

extern ECReg    VCH1CTL;            // Voltage Channel 1 Control
extern ECReg    VCH1DATL;           // Voltage Channel 1 Data Buffer LSB
extern ECReg    VCH1DATM;           // Voltage Channel 1 Data Buffer MSB
extern ECReg    VCH2CTL;            // Voltage Channel 2 Control
extern ECReg    VCH2DATL;           // Voltage Channel 2 Data Buffer LSB
extern ECReg    VCH2DATM;           // Voltage Channel 2 Data Buffer MSB
extern ECReg    VCH3CTL;            // Voltage Channel 3 Control
extern ECReg    VCH3DATL;           // Voltage Channel 3 Data Buffer LSB
extern ECReg    VCH3DATM;           // Voltage Channel 3 Data Buffer MSB
extern ECReg    VHSCDBL;            // Voltage High Scale Calibration Data Buffer LSB
extern ECReg    VHSCDBM;            // Voltage High Scale Calibration Data Buffer MSB
extern ECReg    VCH0DATL;           // Voltage Channel 0 Data Buffer LSB
extern ECReg    VCH0DATM;           // Voltage Channel 0 Data Buffer MSB
extern ECReg    VHSGCDBL;           // Voltage High Scale Gain-error Calibration Data Buffer LSB
extern ECReg    VHSGCDBM;           // Voltage High Scale Gain-error Calibration Data Buffer MSB

extern ECReg    VCMPSCP;            // Voltage Compare Scan Period
extern ECReg    VCH4CTL;            // Voltage Channel 4 Control Register
extern ECReg    VCH4DATM;           // Volt Channel 4 Data Buffer MSB
extern ECReg    VCH4DATL;           // Volt Channel 4 Data Buffer LSB
extern ECReg    VCH5CTL;            // Voltage Channel 5 Control Register
extern ECReg    VCH5DATM;           // Volt Channel 5 Data Buffer MSB
extern ECReg    VCH5DATL;           // Volt Channel 5 Data Buffer LSB
extern ECReg    VCH6CTL;            // Voltage Channel 6 Control Register
#define VCHEN               BIT(4)  // Voltage Channel Enable

extern ECReg    VCH6DATM;           // Volt Channel 6 Data Buffer MSB
extern ECReg    VCH6DATL;           // Volt Channel 6 Data Buffer LSB
extern ECReg    VCH7CTL;            // Voltage Channel 7 Control Register
extern ECReg    VCH7DATM;           // Volt Channel 7 Data Buffer MSB
extern ECReg    VCH7DATL;           // Volt Channel 7 Data Buffer LSB
extern ECReg    ADCDVSTS;           // ADC Data Vaild Status
#define DAT7VAL         BIT(7)  // Data Valid of Channel 7
#define DAT6VAL         BIT(6)  // Data Valid of Channel 6
#define DAT5VAL         BIT(5)  // Data Valid of Channel 5
#define DAT4VAL         BIT(4)  // Data Valid of Channel 4
#define DAT3VAL         BIT(3)  // Data Valid of Channel 3
#define DAT2VAL         BIT(2)  // Data Valid of Channel 2
#define DAT1VAL         BIT(1)  // Data Valid of Channel 1
#define DAT0VAL         BIT(0)  // Data Valid of Channel 0

extern ECReg    VCMPSTS;            // Voltage Compare Status
#define CMP2RTS         BIT(6)  // Comparator 2 Reach Threshold Status
#define CMP1RTS         BIT(5)  // Comparator 1 Reach Threshold Status
#define CMP0RTS         BIT(4)  // Comparator 0 Reach Threshold Status
#define CMP2RTIS        BIT(2)  // Comparator 2 Reach Threshold Interrupt Status
#define CMP1RTIS        BIT(1)  // Comparator 1 Reach Threshold Interrupt Status
#define CMP0RTIS        BIT(0)  // Comparator 0 Reach Threshold Interrupt Status

extern ECReg    VCMP0CTL;           // Voltage Compare Channel 0 Control Register
#define CMP0EN          BIT(7)  // Comparator 0 enable
#define CMP0INTEN       BIT(6)  // Comparator 0 interrupt enable
#define CMP0TMOD        BIT(5)  // Comparator 0 Trigger Mode
#define CMP0ELSM        BIT(4)  // Comparator 0 Edge/Level Sense Mode 0: Level-sensed
#define CMP0GPOL        BIT(3)  // Comparator 0 GPIO Polarity 0: Active-high, 1: Active-low
#define CMP0CSEL_ADC0   0x00    // Comparator 0 Channel Select
#define CMP0CSEL_ADC1   0x01
#define CMP0CSEL_ADC2   0x02
#define CMP0CSEL_ADC3   0x03
#define CMP0CSEL_ADC4   0x04
#define CMP0CSEL_ADC5   0x05
#define CMP0CSEL_ADC6   0x06
#define CMP0CSEL_ADC7   0x07

extern ECReg    VCMP0THRDATM;       // Voltage Compare 0 Threshold Data Buffer MSB
extern ECReg    VCMP0THRDATL;       // Voltage Compare 0 Threshold Data Buffer LSB

extern ECReg    VCMP1CTL;           // Voltage Compare Channel 1 Control Register
#define CMP1EN          BIT(7)  // Comparator 1 enable
#define CMP1INTEN       BIT(6)  // Comparator 1 interrupt enable
#define CMP1TMOD        BIT(5)  // Comparator 1 Trigger Mode
#define CMP1ELSM        BIT(4)  // Comparator 1 Edge/Level Sense Mode 0: Level-sensed
#define CMP1GPOL        BIT(3)  // Comparator 1 GPIO Polarity 0: Active-high, 1: Active-low
#define CMP1CSEL_ADC0   0x00    // Comparator 1 Channel Select
#define CMP1CSEL_ADC1   0x01
#define CMP1CSEL_ADC2   0x02
#define CMP1CSEL_ADC3   0x03
#define CMP1CSEL_ADC4   0x04
#define CMP1CSEL_ADC5   0x05
#define CMP1CSEL_ADC6   0x06
#define CMP1CSEL_ADC7   0x07

extern ECReg    VCMP1THRDATM;       // Voltage Compare 1 Threshold Data Buffer MSB
extern ECReg    VCMP1THRDATL;       // Voltage Compare 1 Threshold Data Buffer LSB

extern ECReg    VCMP2CTL;           // Voltage Compare Channel 2 Control Register
#define CMP2EN          BIT(7)  // Comparator 2 enable
#define CMP2INTEN       BIT(6)  // Comparator 2 interrupt enable
#define CMP2TMOD        BIT(5)  // Comparator 2 Trigger Mode
#define CMP2ELSM        BIT(4)  // Comparator 2 Edge/Level Sense Mode 0: Level-sensed
#define CMP2GPOL        BIT(3)  // Comparator 2 GPIO Polarity 0: Active-high, 1: Active-low
#define CMP2CSEL_ADC0   0x00    // Comparator 2 Channel Select
#define CMP2CSEL_ADC1   0x01
#define CMP2CSEL_ADC2   0x02
#define CMP2CSEL_ADC3   0x03
#define CMP2CSEL_ADC4   0x04
#define CMP2CSEL_ADC5   0x05
#define CMP2CSEL_ADC6   0x06
#define CMP2CSEL_ADC7   0x07

extern ECReg    VCMP2THRDATM;       // Voltage Compare 2 Threshold Data Buffer MSB
extern ECReg    VCMP2THRDATL;       // Voltage Compare 2 Threshold Data Buffer LSB

extern ECReg    VCMPOTR;            // Voltage Comparator Output Type Register
#define CMP0HYSEN       BIT(4)  // Comparator 0 Hysteresis Enable
#define CMP2OT          BIT(2)  // Comparator 2 Output Type 0: Push-pull, 1: Open-drain
#define CMP1OT          BIT(1)  // Comparator 1 Output Type 0: Push-pull, 1: Open-drain
#define CMP0OT          BIT(0)  // Comparator 0 Output Type 0: Push-pull, 1: Open-drain

extern ECReg    VCMP0HYDATM;        // Voltage Comparator 0 Hysteresis Data Buffer MSB
extern ECReg    VCMP0HYDATL;        // Voltage Comparator 0 Hysteresis Data Buffer LSB

extern ECReg    VCMPLR;             // Voltage Comparator Lock Register
#define CMP2LE          BIT(2)  // Comparator 2 Lock Enable
#define CMP1LE          BIT(1)  // Comparator 1 Lock Enable
#define CMP0LE          BIT(0)  // Comparator 0 Lock Enable

extern ECReg    ADCIVMFSCS1;        // ADC Input Voltage Mapping Full-Scale Code Selection 1
#define C7SFSC          BIT(7)  // Channel7 Select Full-Scale Code
#define C6SFSC          BIT(6)  // Channel6 Select Full-Scale Code
#define C5SFSC          BIT(5)  // Channel5 Select Full-Scale Code
#define C4SFSC          BIT(4)  // Channel4 Select Full-Scale Code
#define C3SFSC          BIT(3)  // Channel3 Select Full-Scale Code
#define C2SFSC          BIT(2)  // Channel2 Select Full-Scale Code
#define C1SFSC          BIT(1)  // Channel1 Select Full-Scale Code
#define C0SFSC          BIT(0)  // Channel0 Select Full-Scale Code

extern ECReg    ADCIVMFSCS2;        // ADC Input Voltage Mapping Full-Scale Code Selection 2
#define C10SFSC         BIT(2)  // Channel10 Select Full-Scale Code
#define C9SFSC          BIT(1)  // Channel9 Select Full-Scale Code
#define C8SFSC          BIT(0)  // Channel8 Select Full-Scale Code

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC)
//-----------------------------------------------------------------------------
extern ECReg    DACPDREG;           // DAC Power Down Register
#define DACPWRDN    DACPDREG
extern ECReg    DACDAT0;            // DAC Data Channel 0 (IT8991E None)
extern ECReg    DACDAT1;            // DAC Data Channel 1 (IT8991E None)
extern ECReg    DACDAT2;            // DAC Data Channel 2
extern ECReg    DACDAT3;            // DAC Data Channel 3
extern ECReg    DACDAT4;            // DAC Data Channel 4
extern ECReg    DACDAT5;            // DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC)
//-----------------------------------------------------------------------------
extern ECReg    WUEMR1;             // Wake-Up Edge Mode Register 1
extern ECReg    WUEMR2;             // Wake-Up Edge Mode Register 2
extern ECReg    WUEMR3;             // Wake-Up Edge Mode Register 3
extern ECReg    WUEMR4;             // Wake-Up Edge Mode Register 4
extern ECReg    WUEMR6;             // Wake-Up Edge Mode Register 6
extern ECReg    WUEMR7;             // Wake-Up Edge Mode Register 7
extern ECReg    WUEMR8;             // Wake-Up Edge Mode Register 8
extern ECReg    WUEMR9;             // Wake-Up Edge Mode Register 9
extern ECReg    WUEMR10;            // Wake-Up Edge Mode Register 10
extern ECReg    WUEMR11;            // Wake-Up Edge Mode Register 11
extern ECReg    WUEMR12;            // Wake-Up Edge Mode Register 12
extern ECReg    WUEMR13;            // Wake-Up Edge Mode Register 13
extern ECReg    WUEMR14;            // Wake-Up Edge Mode Register 14

extern ECReg    WUESR1;             // Wake-Up Edge Sense Register 1
extern ECReg    WUESR2;             // Wake-Up Edge Sense Register 2
extern ECReg    WUESR3;             // Wake-Up Edge Sense Register 3
extern ECReg    WUESR4;             // Wake-Up Edge Sense Register 4
extern ECReg    WUESR6;             // Wake-Up Edge Sense Register 6
extern ECReg    WUESR7;             // Wake-Up Edge Sense Register 7
extern ECReg    WUESR8;             // Wake-Up Edge Sense Register 8
extern ECReg    WUESR9;             // Wake-Up Edge Sense Register 9
extern ECReg    WUESR10;            // Wake-Up Edge Sense Register 10
extern ECReg    WUESR11;            // Wake-Up Edge Sense Register 11
extern ECReg    WUESR12;            // Wake-Up Edge Sense Register 12
extern ECReg    WUESR13;            // Wake-Up Edge Sense Register 13
extern ECReg    WUESR14;            // Wake-Up Edge Sense Register 14

extern ECReg    WUENR1;             // Wake-Up Enable Register 1
extern ECReg    WUENR2;             // Wake-Up Enable Register 2
extern ECReg    WUENR3;             // Wake-Up Enable Register 3
extern ECReg    WUENR4;             // Wake-Up Enable Register 4
extern ECReg    WUENR6;             // Wake-Up Enable Register 6
extern ECReg    WUENR7;             // Wake-Up Enable Register 7
extern ECReg    WUENR8;             // Wake-Up Enable Register 8
extern ECReg    WUENR9;             // Wake-Up Enable Register 9

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB)
//-----------------------------------------------------------------------------
extern ECReg    HOSTA_A;            // Host Status A
extern ECReg    HOSTA_B;            // Host Status B
extern ECReg    HOSTA_C;            // Host Status C
extern ECReg    HOSTA_D;            // Host Status D
extern ECReg    HOSTA_E;            // Host Status E
extern ECReg    HOSTA_F;            // Host Status F
#define HOSTA_BDS           BIT(7)  // Byte Done Status
#define HOSTA_TMOE          BIT(6)  // Time-out Error
#define HOSTA_NACK          BIT(5)  // Not Response ACK
#define HOSTA_FAIL          BIT(4)  // Fail
#define HOSTA_BSER          BIT(3)  // Bus Error
#define HOSTA_DVER          BIT(2)  // Device Error
#define HOSTA_FINTR         BIT(1)  // Finish Interrupt
#define HOSTA_HOBY          BIT(0)  // Host Busy

extern ECReg    HOCTL_A;            // Host Control A
extern ECReg    HOCTL_B;            // Host Control B
extern ECReg    HOCTL_C;            // Host Control C
extern ECReg    HOCTL_D;            // Host Control D
extern ECReg    HOCTL_E;            // Host Control E
extern ECReg    HOCTL_F;            // Host Control F
#define HOCTL_PEC_EN        BIT(7)  // PEC Enable
#define HOCTL_SRT           BIT(6)  // Start
#define HOCTL_LABY          BIT(5)  // Last Byte
#define HOCTL_SMCD2         BIT(4)  // SMBus Command
#define HOCTL_SMCD1         BIT(3)  // SMBus Command
#define HOCTL_SMCD0         BIT(2)  // SMBus Command
#define HOCTL_KILL          BIT(1)  // Kill
#define HOCTL_INTREN        BIT(0)  // Host Interrupt Enable

extern ECReg    HOCMD_A;            // Host Command A
extern ECReg    HOCMD_B;            // Host Command B
extern ECReg    HOCMD_C;            // Host Command C
extern ECReg    HOCMD_D;            // Host Command D
extern ECReg    HOCMD_E;            // Host Command E
extern ECReg    HOCMD_F;            // Host Command F

extern ECReg    TRASLA_A;           // Transmit Slave Address A
extern ECReg    TRASLA_B;           // Transmit Slave Address B
extern ECReg    TRASLA_C;           // Transmit Slave Address C
extern ECReg    TRASLA_D;           // Transmit Slave Address D
extern ECReg    TRASLA_E;           // Transmit Slave Address E
extern ECReg    TRASLA_F;           // Transmit Slave Address F
#define TRASLA_DIR          BIT(0)  // Direction of the host transfer. 0: Write 1: Read

extern ECReg    D0REG_A;            // Host Data 0 A
extern ECReg    D0REG_B;            // Host Data 0 B
extern ECReg    D0REG_C;            // Host Data 0 C
extern ECReg    D0REG_D;            // Host Data 0 D
extern ECReg    D0REG_E;            // Host Data 0 E
extern ECReg    D0REG_F;            // Host Data 0 F

extern ECReg    D1REG_A;            // Host Data 1 A
extern ECReg    D1REG_B;            // Host Data 1 B
extern ECReg    D1REG_C;            // Host Data 1 C
extern ECReg    D1REG_D;            // Host Data 1 D
extern ECReg    D1REG_E;            // Host Data 1 E
extern ECReg    D1REG_F;            // Host Data 1 F

extern ECReg    HOBDB_A;            // Host Block Data Byte A
extern ECReg    HOBDB_B;            // Host Block Data Byte B
extern ECReg    HOBDB_C;            // Host Block Data Byte C
extern ECReg    HOBDB_D;            // Host Block Data Byte D
extern ECReg    HOBDB_E;            // Host Block Data Byte E
extern ECReg    HOBDB_F;            // Host Block Data Byte F

extern ECReg    PECERC_A;           // Packet Error Check A
extern ECReg    PECERC_B;           // Packet Error Check B
extern ECReg    PECERC_C;           // Packet Error Check C
extern ECReg    PECERC_D;           // Packet Error Check D
extern ECReg    PECERC_E;           // Packet Error Check E
extern ECReg    PECERC_F;           // Packet Error Check F

extern ECReg    RESLADR_A;          // Receive Slave Adress A
extern ECReg    RESLADR_B;          // Receive Slave Adress B
extern ECReg    RESLADR_C;          // Receive Slave Adress C

extern ECReg    RESLADR2_A;         // Receive Slave Adress_2 A
#define RESLADR_2_A     RESLADR2_A
extern ECReg    RESLADR2_B;         // Receive Slave Adress_2 B
#define RESLADR_2_B     RESLADR2_B
extern ECReg    RESLADR2_C;         // Receive Slave Adress_2 C
#define RESLADR_2_C     RESLADR2_C
#define RESLADR2_EN         BIT(7)  // Slave Address 2 Enable

extern ECReg    SLDA_A;             // Slave Data A
extern ECReg    SLDA_B;             // Slave Data B
extern ECReg    SLDA_C;             // Slave Data C

extern ECReg    SMBPCTL_A;          // SMBUS Pin Control A
extern ECReg    SMBPCTL_B;          // SMBUS Pin Control B
extern ECReg    SMBPCTL_C;          // SMBUS Pin Control C
extern ECReg    SMBPCTL_D;          // SMBUS Pin Control D
extern ECReg    SMBPCTL_E;          // SMBUS Pin Control E
extern ECReg    SMBPCTL_F;          // SMBUS Pin Control F
#define SDACTLE         BIT(4)      // SMDAT Control Enable
#define SDACTL          BIT(3)      // SMDAT Control
#define SCLCTL          BIT(2)      // SMCLK Control
#define SMBDCS          BIT(1)      // SMDAT Current State
#define SMBCS           BIT(0)      // SMCLK Current State

extern ECReg    SLSTA_A;            // Slave Status A
extern ECReg    SLSTA_B;            // Slave Status B
extern ECReg    SLSTA_C;            // Slave Status C
#define SSSLS           BIT(7)
#define SPDS            BIT(5)
#define MSLA2           BIT(4)
#define RCS             BIT(3)
#define STS             BIT(2)
#define SDS             BIT(1)

extern ECReg    SICR_A;             // Slave Interrupt Control A
extern ECReg    SICR_B;             // Slave Interrupt Control B
extern ECReg    SICR_C;             // Slave Interrupt Control C
#define SDSEN           BIT(3)      // Slave Detect STOP Condition Interrupt Enable
#define SDLTOEN         BIT(2)      // Slave SMDAT Low Timeout Enable
#define SITEN           BIT(1)      // Slave Interrupt Enable
#define HONOIN          BIT(0)      // Host Notify Interrupt Enable

extern ECReg    NDADR_A;            // Notify Device Adress A
extern ECReg    NDADR_B;            // Notify Device Adress B
extern ECReg    NDADR_C;            // Notify Device Adress C
#define DVADR           BIT(7)      // Device Address

extern ECReg    NDLB_A;             // Notify Data Low Byte A
extern ECReg    NDLB_B;             // Notify Data Low Byte B
extern ECReg    NDLB_C;             // Notify Data Low Byte C

extern ECReg    NDHB_A;             // Notify Data High Byte A
extern ECReg    NDHB_B;             // Notify Data High Byte B
extern ECReg    NDHB_C;             // Notify Data High Byte C

extern ECReg    HOCTL2_A;           // Host Control2 A
extern ECReg    HOCTL2_B;           // Host Control2 B
extern ECReg    HOCTL2_C;           // Host Control2 C
extern ECReg    HOCTL2_D;           // Host Control2 D
extern ECReg    HOCTL2_E;           // Host Control2 E
extern ECReg    HOCTL2_F;           // Host Control2 F
#define SSCL            BIT(7)      // Slave Stretch Clock Low
#define SLVEN           BIT(5)
#define SMD_TO_EN       BIT(4)
#define I2C_SW_EN       BIT(3)
#define I2C_SW_WAIT     BIT(2)
#define I2C_EN          BIT(1)
#define SMHEN           BIT(0)

extern ECReg    SMB4P7USL;          // 4.7 £gs Low Register
extern ECReg    SMB4P0USH;          // 4.7 £gs High Register
extern ECReg    SMB300NS;           // 300 ns Register
extern ECReg    SMB250NS;           // 250 ns Register
extern ECReg    SMB25MS;            // 25 ms Register
extern ECReg    SMB45P3USL;         // 45.3 £gs Low Register
extern ECReg    SMBS4P3USH;         // 45.3 £gs High Register
extern ECReg    SMB4P7A4P0H;        // 4.7 £gs and 4.0 £gs High Register

extern ECReg    SLVISELR;           // Slave Interface Select
#define SBBF            BIT(6)      // Slave B Bridge Function
#define SABF            BIT(5)      // Slave A Bridge Function
#define OVRSMDBG        BIT(4)      // Override Debug Mode through SMBus

extern ECReg    SCLKTS_A;           // SMCLK Timing Setting Register A
extern ECReg    SCLKTS_B;           // SMCLK Timing Setting Register B
extern ECReg    SCLKTS_C;           // SMCLK Timing Setting Register C
extern ECReg    SCLKTS_D;           // SMCLK Timing Setting Register D
extern ECReg    SCLKTS_E;           // SMCLK Timing Setting Register E
extern ECReg    SCLKTS_F;           // SMCLK Timing Setting Register F
#define FRSST           BIT(4)      // Fix Repeat Start Setup Time
#define SCLKA1M         BIT(2)      // SMCLK 1MHz Setting
#define _SCLKS_50KHz    0x01
#define _SCLKS_100KHz   0x02
#define _SCLKS_400KHz   0x03
#define SCLKB1M         BIT(2)      // SMCLK 1MHz Setting
#define SCLKC1M         BIT(2)      // SMCLK 1MHz Setting
#define SCLKD1M         BIT(2)      // SMCLK 1MHz Setting
#define SCLKE1M         BIT(2)      // SMCLK 1MHz Setting
#define SCLKF1M         BIT(2)      // SMCLK 1MHz Setting

extern ECReg    SMBMSTFCTRL1;       // SMBus FIFO Control 1 Register
#define BLKDS1          BIT(4)      // Block Done Status 1
#define FF1EN           BIT(3)      // FIFO 1 Enable

extern ECReg    SMBMSTFSTS1;        // SMBus FIFO Status 1 Register
#define FIFO1_EMPTY     BIT(7)      // FIFO 1 Empty
#define FIFO1_FULL      BIT(6)      // FIFO 1 Full

extern ECReg    SMBMSTFCTRL2;       // SMBus FIFO Control 2 Register
#define BLKDS2          BIT(4)      // Block Done Status 2
#define FFEN2           BIT(3)      // FIFO 2 Enable
#define _FIFO_TO_B      0x00
#define _FIFO_TO_C      0x01
#define _FIFO_TO_D      0x02
#define _FIFO_TO_E      0x03
#define _FIFO_TO_F      0x04

extern ECReg    SMBMSTFSTS2;        // SMBus FIFO Status 2 Register
#define FIFO2_EMPTY     BIT(7)      // FIFO 2 Empty
#define FIFO2_FULL      BIT(6)      // FIFO 2 Full

extern ECReg    HONACKSRC_A;        // HOST Nack Source A
extern ECReg    HONACKSRC_B;        // HOST Nack Source B
extern ECReg    HONACKSRC_C;        // HOST Nack Source C
extern ECReg    HONACKSRC_D;        // HOST Nack Source D
extern ECReg    HONACKSRC_E;        // HOST Nack Source E
extern ECReg    HONACKSRC_F;        // HOST Nack Source F
#define SMCDTD          BIT(4)      // SMCLK & SMDAT Timeout Disable

extern ECReg    SLVFTH;             // Slave FIFO Threshold
extern ECReg    DFTSDFSEL;          // DMA from Flash to SMB Dedicated FIFO Selection
extern ECReg    MSTHTH;             // Master FIFO Threshold
extern ECReg    MFTHEN;             // Master FIFO Threshold Enable
#define MARDA           BIT(7)      // Master A Receive Data Available Function
#define MBRDA           BIT(6)      // Master B Receive Data Available Function
#define MCRDA           BIT(5)      // Master C Receive Data Available Function
#define MDRDA           BIT(4)      // Master D Receive Data Available Function
#define MATDA           BIT(3)      // Master A Transmitter Data Available Function
#define MBTDA           BIT(2)      // Master B Transmitter Data Available Function
#define MCTDA           BIT(1)      // Master C Transmitter Data Available Function
#define MDTDA           BIT(0)      // Master D Transmitter Data Available Function

extern ECReg    MFTISTA;            // Master FIFO Threshold Interrupt Status
#define MARID           BIT(7)      // Master A RX Interrupt Detected
#define MBRID           BIT(6)      // Master B RX Interrupt Detected
#define MCRID           BIT(5)      // Master C RX Interrupt Detected
#define MDRID           BIT(4)      // Master D RX Interrupt Detected
#define MATID           BIT(3)      // Master A TX Interrupt Detected
#define MBTID           BIT(2)      // Master B TX Interrupt Detected
#define MCTID           BIT(1)      // Master C TX Interrupt Detected
#define MDTID           BIT(0)      // Master D TX Interrupt Detected

extern ECReg    SFTHEN;             // Slave FIFO Threshold Enable
#define SCRDAF          BIT(5)      // Slave C Receive Data Available Function
#define SCTDAF          BIT(4)      // Slave C Transmitter Data Available Function
#define SBRDAF          BIT(3)      // Slave B Receive Data Available Function
#define SBTDAF          BIT(2)      // Slave B Transmitter Data Available Function
#define SARDAF          BIT(1)      // Slave A Receive Data Available Function
#define SATDAF          BIT(0)      // Slave A Transmitter Data Available Function

extern ECReg    SFTISTA;            // Slave FIFO Threshold Interrupt Status
#define SCRIDSC         BIT(5)      // Slave C RX Interrupt Detected for Slave C
#define SCTXIDSC        BIT(4)      // Slave C TX Interrupt Detected for Slave C
#define SBRIDSB         BIT(3)      // Slave B RX Interrupt Detected for Slave C
#define SBTXIDSB        BIT(2)      // Slave B TX Interrupt Detected for Slave C
#define RIDSA           BIT(1)      // Slave A RX Interrupt Detected for Slave C
#define TXIDSA          BIT(0)      // Slave A TX Interrupt Detected for Slave C

extern ECReg    SADFPCTL;           // Slave FIFO Control Register
#define HSAPFME         BIT(3)      // Hardware Slave A (For Pre-defined) Follow Mode Enable
#define SABBS           BIT(2)      // Slave A Bridge Busy Status
#define HSAPE           BIT(1)      // Hardware Slave A (for Pre-defined) Enable
#define SADFE           BIT(0)      // Slave A Dedicated FIFO Enable

extern ECReg    SFFSTA;             // Slave FIFO Status
#define FIFO_EMPTY      BIT(7)      // FIFO Empty
#define FIFO_FULL       BIT(6)      // FIFO Full

extern ECReg    SDSIC;              // SMBus Design Switch Interface Control
extern ECReg    SDSIC2;             // SMBus Design Switch Interface Control 2
extern ECReg    SBDFPCTL;           // Slave B Dedicated FIFO Pre-defined Control Register
#define HSBPFME         BIT(3)      // Hardware Slave B (For Pre-defined) Follow Mode Enable
#define SBBBS           BIT(2)      // Slave B Bridge Busy Status
#define HSBPE           BIT(1)      // Hardware Slave B (for Pre-defined) Enable
#define SBDFE           BIT(0)      // Slave B Dedicated FIFO Enable

extern ECReg    SBDFFSTA;           // Slave B Dedicated FIFO Status
extern ECReg    SCDFFCTL;           // Slave C Dedicated FIFO Control Register
#define SCDFE           BIT(0)      // Slave C Dedicated FIFO Enable

extern ECReg    SCDFFSTA;           // Slave C Dedicated FIFO Status

extern ECReg    I2CW2RF;            // I2C Wr to Rd FIFO Register
#define MAIF            BIT(7)      // Master A I2C Wr->Rd FIFO Function
#define MBCDEFIF        BIT(6)      // Master BCDEF I2C Wr->Rd FIFO Function
#define MDIFI           BIT(3)      // Master D I2C Wr->Rd FIFO Interrupt
#define MCIFI           BIT(2)      // Master C I2C Wr->Rd FIFO Interrupt
#define MBIFI           BIT(1)      // Master B I2C Wr->Rd FIFO Interrupt
#define MAIFI           BIT(0)      // Master A I2C Wr->Rd FIFO Interrupt

extern ECReg    IWRFISTA;           // I2C Wr to Rd FIFO Interrupt Status
#define MFIFI           BIT(7)      // Master F I2C Wr->Rd FIFO Interrupt
#define MEIFI           BIT(6)      // Master E I2C Wr->Rd FIFO Interrupt
#define MFIFID          BIT(5)      // Master F I2C Wr->Rd FIFO Interrupt Detected
#define MEIFID          BIT(4)      // Master E I2C Wr->Rd FIFO Interrupt Detected
#define MDIFID          BIT(3)      // Master D I2C Wr->Rd FIFO Interrupt Detected
#define MCIFID          BIT(2)      // Master C I2C Wr->Rd FIFO Interrupt Detected
#define MBIFID          BIT(1)      // Master B I2C Wr->Rd FIFO Interrupt Detected
#define MAIFID          BIT(0)      // Master A I2C Wr->Rd FIFO Interrupt Detected

extern ECReg    SFFE;               // Shared FIFO Function Enable
#define SFSCE           BIT(6)      // Shared FIFO For Slave C Enable
#define SFSBE           BIT(5)      // Shared FIFO For Slave B Enable
#define SFSAE           BIT(4)      // Shared FIFO For Slave A Enable
#define SFMBCDEFE       BIT(1)      // Shared FIFO For Master B, C, D, E, F Enable
#define SFMAE           BIT(0)      // Shared FIFO For Master A Enable

extern ECReg    SISPC;              // SMBus Interface Switch Pin control
#define SMBIF5SC        BIT(5)      // SMBus Interface 5 Switch Control
#define SMBIF4SC        BIT(4)      // SMBus Interface 4 Switch Control
#define SMBIF3SC        BIT(3)      // SMBus Interface 3 Switch Control
#define SMBIF2SC        BIT(2)      // SMBus Interface 2 Switch Control
#define SMBIF1SC        BIT(1)      // SMBus Interface 1 Switch Control
#define SMBIF0SC        BIT(0)      // SMBus Interface 0 Switch Control

extern ECReg    MSFSS;              // Master Shared FIFO Size Select
extern ECReg    SSFSS1;             // Slave Shared FIFO Size Select 1
extern ECReg    SFBAMA;             // Shared FIFO Base Address for Master A
extern ECReg    SFBAMBCD;           // Shared FIFO Base Address for Master BCD
extern ECReg    SFBASA;             // Shared FIFO Base Address for Slave A
extern ECReg    SFBASB;             // Shared FIFO Base Address for Slave B
extern ECReg    SFBASC;             // Shared FIFO Base Address for Slave C
extern ECReg    SSFSS2;             // Slave Shared FIFO Size Select 2
#define FSHI_16BYTES    0x00        // BIT6-4 000: 16 bytes.
#define FSHI_16BYTEs    0x10        // BIT6-4 001: 16 bytes.
#define FSHI_32BYTES    0x20        // BIT6-4 010: 32 bytes.
#define FSHI_64BYTES    0x30        // BIT6-4 011: 64 bytes.
#define FSHI_128BYTES   0x40        // BIT6-4 100: 128 bytes.
#define FSHI_256BYTES   0x50        // BIT6-4 101: 256 bytes.
#define FSLO_16BYTES    0x00        // BIT2-0 000: 16 bytes.
#define FSLO_16BYTEs    0x01        // BIT2-0 001: 16 bytes.
#define FSLO_32BYTES    0x02        // BIT2-0 010: 32 bytes.
#define FSLO_64BYTES    0x03        // BIT2-0 011: 64 bytes.
#define FSLO_128BYTES   0x04        // BIT2-0 100: 128 bytes.
#define FSLO_256BYTES   0x05        // BIT2-0 101: 256 bytes.

extern ECReg    HWPEC;              // Hardwired PEC Register
#define SCHPF           BIT(6)      // Slave C Hardwired PEC Function
#define SBHPF           BIT(5)      // Slave B Hardwired PEC Function
#define SAHPF           BIT(4)      // Slave A Hardwired PEC Function
#define MDHPF           BIT(3)      // Master D Hardwired PEC Function
#define MCHPF           BIT(2)      // Master C Hardwired PEC Function
#define MBHPF           BIT(1)      // Master B Hardwired PEC Function
#define MAHPF           BIT(0)      // Master A Hardwired PEC Function

extern ECReg    HWPES;              // Hardwired PEC Error Status
#define SCHPCE          BIT(6)      // Slave C Hardwired PEC Check Error
#define SBHPCE          BIT(5)      // Slave B Hardwired PEC Check Error
#define SAHPCE          BIT(4)      // Slave A Hardwired PEC Check Error
#define MDHPCE          BIT(3)      // Master D Hardwired PEC Check Error
#define MCHPCE          BIT(2)      // Master C Hardwired PEC Check Error
#define MBHPCE          BIT(1)      // Master B Hardwired PEC Check Error
#define MAHPCE          BIT(0)      // Master A Hardwired PEC Check Error

extern ECReg    SLVTPECC;           // Slave Transaction PEC Control
#define SLVCTCP         BIT(2)      // Slave C Transaction Contains PEC
#define SLVBTCP         BIT(1)      // Slave B Transaction Contains PEC
#define SLVATCP         BIT(0)      // Slave A Transaction Contains PEC

extern ECReg    SHWPECV_A;          // Slave Hardwired PEC VALUE A
extern ECReg    SHWPECV_B;          // Slave Hardwired PEC VALUE B
extern ECReg    SHWPECV_C;          // Slave Hardwired PEC VALUE C

extern ECReg    BTOIER;             // Bridge Timeout Interrupt Enabled
#define MDBTOIE         BIT(7)      // Master D Bridge Timeout Interrupt Enable
#define SBBTOIE         BIT(6)      // Slave B Bridge Timeout Interrupt Enable
#define MCBTOIE         BIT(5)      // Master C Bridge Timeout Interrupt Enable
#define SABTOIE         BIT(4)      // Slave A Bridge Timeout Interrupt Enable
#define MDBTOS          BIT(3)      // Master D Bridge Timeout Status
#define SBBTOS          BIT(2)      // Slave B Bridge Timeout Status
#define MCBTOS          BIT(1)      // Master C Bridge Timeout Status
#define SABTOS          BIT(0)      // Slave A Bridge Timeout Status

extern ECReg    ISFBCH_A;           // I2C Shared FIFO Byte Count H A
extern ECReg    ISFBCH_B;           // I2C Shared FIFO Byte Count H B
extern ECReg    ISFBCH_C;           // I2C Shared FIFO Byte Count H C
extern ECReg    ISFBCH_D;           // I2C Shared FIFO Byte Count H D
extern ECReg    ISFBCH_E;           // I2C Shared FIFO Byte Count H E
extern ECReg    ISFBCH_F;           // I2C Shared FIFO Byte Count H F

extern ECReg    SDSIC3;             // SMBus Design Switch Interface Control 3
extern ECReg    MFTHEN2;            // Master Dedicated FIFO Threshold Enable 2
#define MERDA           BIT(7)      // Master E Receive Data Available Function
#define MFRDA           BIT(6)      // Master F Receive Data Available Function
#define METDA           BIT(3)      // Master E Transmitter Data Available Function
#define MFTDA           BIT(2)      // Master F Transmitter Data Available Function

extern ECReg    MFTISTA2;           // Master Dedicated FIFO Threshold Interrupt Status 2
#define MERID           BIT(7)      // Master E RX Interrupt Detected
#define MFRID           BIT(6)      // Master F RX Interrupt Detected
#define METID           BIT(3)      // Master E TX Interrupt Detected
#define MFTID           BIT(2)      // Master F TX Interrupt Detected

extern ECReg    HWPEC2;             // Hardwired PEC Register 2
#define MFHPF           BIT(1)      // Master F Hardwired PEC Function
#define MEHPF           BIT(0)      // Master E Hardwired PEC Function

extern ECReg    HWPES2;             // Hardwired PEC Error Status 2
#define MFHPCE          BIT(1)      // Master F Hardwired PEC Check Error
#define MEHPCE          BIT(0)      // Master E Hardwired PEC Check Error

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS)
//-----------------------------------------------------------------------------
extern ECReg    KSOL;               // Keyboard Scan Out
extern ECReg    KSOH1;              // Keyboard Scan Out
extern ECReg    KSOCTRL;            // Keyboard Scan Out Control
#define KSOPU               BIT(2)  // KSO Pull Up
#define KSOOD               BIT(0)  // KSO Open Drain

extern ECReg    KSOH2;              // Keyboard Scan Out
extern ECReg    KSI;                // Keyboard Scan In
extern ECReg    KSICTRL;            // Keyboard Scan In Control
#define OVRPPK              BIT(4)  // Override PP from KBS
#define KSIPU               BIT(2)  // KSI Pull Up

extern ECReg    KSIGCTRLR;          // Keyboard Scan In [7:0] GPIO Control
#define KSI7GCTRL           BIT(7)  // KSI7 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI6GCTRL           BIT(6)  // KSI6 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI5GCTRL           BIT(5)  // KSI5 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI4GCTRL           BIT(4)  // KSI4 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI3GCTRL           BIT(3)  // KSI3 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI2GCTRL           BIT(2)  // KSI2 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI1GCTRL           BIT(1)  // KSI1 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSI0GCTRL           BIT(0)  // KSI0 GPIO Control 0:KBS mode, 1: GPIO mode

extern ECReg    KSIGOENR;           // Keyboard Scan In [7:0] GPIO Output Enable
#define KSI7GOEN            BIT(7)  // KSI7 GPIO Output Enable 0:Disable GPIO
#define KSI6GOEN            BIT(6)  // KSI6 GPIO Output Enable 0:Disable GPIO
#define KSI5GOEN            BIT(5)  // KSI5 GPIO Output Enable 0:Disable GPIO
#define KSI4GOEN            BIT(4)  // KSI4 GPIO Output Enable 0:Disable GPIO
#define KSI3GOEN            BIT(3)  // KSI3 GPIO Output Enable 0:Disable GPIO
#define KSI2GOEN            BIT(2)  // KSI2 GPIO Output Enable 0:Disable GPIO
#define KSI1GOEN            BIT(1)  // KSI1 GPIO Output Enable 0:Disable GPIO
#define KSI0GOEN            BIT(0)  // KSI0 GPIO Output Enable 0:Disable GPIO

extern ECReg    KSIGDATR;           // Keyboard Scan In [7:0] GPIO DATA
#define KSI7GDAT            BIT(7)  // KSI7 GPIO Data, In GPIO mode, KSI7 Out Hi/Lo
#define KSI6GDAT            BIT(6)  // KSI6 GPIO Data, In GPIO mode, KSI6 Out Hi/Lo
#define KSI5GDAT            BIT(5)  // KSI5 GPIO Data, In GPIO mode, KSI5 Out Hi/Lo
#define KSI4GDAT            BIT(4)  // KSI4 GPIO Data, In GPIO mode, KSI4 Out Hi/Lo
#define KSI3GDAT            BIT(3)  // KSI3 GPIO Data, In GPIO mode, KSI3 Out Hi/Lo
#define KSI2GDAT            BIT(2)  // KSI2 GPIO Data, In GPIO mode, KSI2 Out Hi/Lo
#define KSI1GDAT            BIT(1)  // KSI1 GPIO Data, In GPIO mode, KSI1 Out Hi/Lo
#define KSI0GDAT            BIT(0)  // KSI0 GPIO Data, In GPIO mode, KSI0 Out Hi/Lo

extern ECReg    KSIGDMRRR;          // Keyboard Scan In [7:0] GPIO DATA Mirror
#define KSI7GDMRR           BIT(7)  // KSI7 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI6GDMRR           BIT(6)  // KSI6 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI5GDMRR           BIT(5)  // KSI5 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI4GDMRR           BIT(4)  // KSI4 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI3GDMRR           BIT(3)  // KSI3 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI2GDMRR           BIT(2)  // KSI2 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI1GDMRR           BIT(1)  // KSI1 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSI0GDMRR           BIT(0)  // KSI0 GPIO Data Mirror, In GPIO mode read Hi/Lo

extern ECReg    KSOHGCTRLR;         // Keyboard Scan Out [15:8] GPIO Control
#define KSO15GCTRL          BIT(7)  // KSO15 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO14GCTRL          BIT(6)  // KSO14 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO13GCTRL          BIT(5)  // KSO13 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO12GCTRL          BIT(4)  // KSO12 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO11GCTRL          BIT(3)  // KSO11 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO10GCTRL          BIT(2)  // KSO10 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO9GCTRL           BIT(1)  // KSO9 GPIO Control  0:KBS mode, 1: GPIO mode
#define KSO8GCTRL           BIT(0)  // KSO8 GPIO Control  0:KBS mode, 1: GPIO mode

extern ECReg    KSOHGOENR;          // Keyboard Scan Out [15:8] GPIO Output Enable
#define KSO15GOEN           BIT(7)  // KSO15 GPIO Output Enable 0:Disable GPIO
#define KSO14GOEN           BIT(6)  // KSO14 GPIO Output Enable 0:Disable GPIO
#define KSO13GOEN           BIT(5)  // KSO13 GPIO Output Enable 0:Disable GPIO
#define KSO12GOEN           BIT(4)  // KSO12 GPIO Output Enable 0:Disable GPIO
#define KSO11GOEN           BIT(3)  // KSO11 GPIO Output Enable 0:Disable GPIO
#define KSO10GOEN           BIT(2)  // KSO10 GPIO Output Enable 0:Disable GPIO
#define KSO9GOEN            BIT(1)  // KSO9 GPIO Output  Enable 0:Disable GPIO
#define KSO8GOEN            BIT(0)  // KSO8 GPIO Output  Enable 0:Disable GPIO

extern ECReg    KSOHGDMRRR;         // Keyboard Scan Out [15:8] GPIO DATA Mirror
#define KSO15GDMRR          BIT(7)  // KSO15 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO14GDMRR          BIT(6)  // KSO14 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO13GDMRR          BIT(5)  // KSO13 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO12GDMRR          BIT(4)  // KSO12 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO11GDMRR          BIT(3)  // KSO11 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO10GDMRR          BIT(2)  // KSO10 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO9GDMRR           BIT(1)  // KSO9 GPIO Data Mirror,  In GPIO mode read Hi/Lo
#define KSO8GDMRR           BIT(0)  // KSO8 GPIO Data Mirror,  In GPIO mode read Hi/Lo

extern ECReg    KSOLGCTRLR;         // Keyboard Scan Out [7:0] GPIO Control
#define KSO7GCTRL           BIT(7)  // KSO7 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO6GCTRL           BIT(6)  // KSO6 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO5GCTRL           BIT(5)  // KSO5 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO4GCTRL           BIT(4)  // KSO4 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO3GCTRL           BIT(3)  // KSO3 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO2GCTRL           BIT(2)  // KSO2 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO1GCTRL           BIT(1)  // KSO1 GPIO Control 0:KBS mode, 1: GPIO mode
#define KSO0GCTRL           BIT(0)  // KSO0 GPIO Control 0:KBS mode, 1: GPIO mode

extern ECReg    KSOLGOENR;          // Keyboard Scan Out [7:0] GPIO Output Enable
#define KSO7GOEN            BIT(7)  // KSO7 GPIO Output Enable 0:Disable GPIO
#define KSO6GOEN            BIT(6)  // KSO6 GPIO Output Enable 0:Disable GPIO
#define KSO5GOEN            BIT(5)  // KSO5 GPIO Output Enable 0:Disable GPIO
#define KSO4GOEN            BIT(4)  // KSO4 GPIO Output Enable 0:Disable GPIO
#define KSO3GOEN            BIT(3)  // KSO3 GPIO Output Enable 0:Disable GPIO
#define KSO2GOEN            BIT(2)  // KSO2 GPIO Output Enable 0:Disable GPIO
#define KSO1GOEN            BIT(1)  // KSO1 GPIO Output Enable 0:Disable GPIO
#define KSO0GOEN            BIT(0)  // KSO0 GPIO Output Enable 0:Disable GPIO

extern ECReg    KSOLGDMRRR;         // Keyboard Scan Out [7:0] GPIO DATA Mirror
#define KSO7GDMRR           BIT(7)  // KSO7 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO6GDMRR           BIT(6)  // KSO6 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO5GDMRR           BIT(5)  // KSO5 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO4GDMRR           BIT(4)  // KSO4 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO3GDMRR           BIT(3)  // KSO3 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO2GDMRR           BIT(2)  // KSO2 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO1GDMRR           BIT(1)  // KSO1 GPIO Data Mirror, In GPIO mode read Hi/Lo
#define KSO0GDMRR           BIT(0)  // KSO0 GPIO Data Mirror, In GPIO mode read Hi/Lo

extern ECReg    KSO0LSDR;           // KSO 0 Low Scan Data Register
extern ECReg    KSO1LSDR;           // KSO 1 Low Scan Data Register
extern ECReg    KSO2LSDR;           // KSO 2 Low Scan Data Register
extern ECReg    KSO3LSDR;           // KSO 3 Low Scan Data Register
extern ECReg    KSO4LSDR;           // KSO 4 Low Scan Data Register
extern ECReg    KSO5LSDR;           // KSO 5 Low Scan Data Register
extern ECReg    KSO6LSDR;           // KSO 6 Low Scan Data Register
extern ECReg    KSO7LSDR;           // KSO 7 Low Scan Data Register
extern ECReg    KSO8LSDR;           // KSO 8 Low Scan Data Register
extern ECReg    KSO9LSDR;           // KSO 9 Low Scan Data Register
extern ECReg    KSO10LSDR;          // KSO 10 Low Scan Data Register
extern ECReg    KSO11LSDR;          // KSO 11 Low Scan Data Register
extern ECReg    KSO12LSDR;          // KSO 12 Low Scan Data Register
extern ECReg    KSO13LSDR;          // KSO 13 Low Scan Data Register
extern ECReg    KSO14LSDR;          // KSO 14 Low Scan Data Register
extern ECReg    KSO15LSDR;          // KSO 15 Low Scan Data Register
extern ECReg    KSO16LSDR;          // KSO 16 Low Scan Data Register
extern ECReg    KSO17LSDR;          // KSO 17 Low Scan Data Register
extern ECReg    SDC1R;              // Scan Data Control 1 Register
#define SDEN            BIT(7)      // Scan data enable
#define INTSDVEN        BIT(5)      // Interrupt from scan data valid enable
//---------------------------------
// BIT2~BIT0 Scan loop select
#define SLS_00_Round    0x00
#define SLS_02_Round    0x01
#define SLS_03_Round    0x02
#define SLS_04_Round    0x03
#define SLS_05_Round    0x04
#define SLS_06_Round    0x05
#define SLS_07_Round    0x06
#define SLS_08_Round    0x07

extern ECReg    SDC2R;              // Scan Data Control 2 Register
#define KSOPCS1         BIT(7)      // KSO pin count select
#define KSOPCS0         BIT(6)      // KSO pin count select
//---------------------------------
// BIT3 ~ BIT0  Wait KSO high delay
#define WKSOHDLY_23us   0x00
#define WKSOHDLY_31us   0x01
#define WKSOHDLY_39us   0x02
#define WKSOHDLY_47us   0x03
#define WKSOHDLY_55us   0x04
#define WKSOHDLY_63us   0x05
#define WKSOHDLY_71us   0x06
#define WKSOHDLY_79us   0x07
#define WKSOHDLY_87us   0x08
#define WKSOHDLY_95us   0x09

extern ECReg    SDC3R;              // Scan Data Control 3 Register
//---------------------------------
// BIT7 ~ BIT4  Wait KSO low delay
#define WKSOLDLY_11us   (0x00 << 4)
#define WKSOLDLY_13us   (0x01 << 4)
#define WKSOLDLY_15us   (0x02 << 4)
#define WKSOLDLY_17us   (0x03 << 4)
#define WKSOLDLY_19us   (0x04 << 4)
#define WKSOLDLY_21us   (0x05 << 4)
#define WKSOLDLY_23us   (0x06 << 4)
#define WKSOLDLY_25us   (0x07 << 4)
#define WKSOLDLY_27us   (0x08 << 4)
#define WKSOLDLY_29us   (0x09 << 4)
//---------------------------------
// BIT3 ~ BIT0  Spacing delay between rounds
#define SDLYBR_00ms     0x00
#define SDLYBR_01ms     0x01
#define SDLYBR_02ms     0x02
#define SDLYBR_03ms     0x03
#define SDLYBR_04ms     0x04
#define SDLYBR_05ms     0x05
#define SDLYBR_06ms     0x06
#define SDLYBR_07ms     0x07
#define SDLYBR_08ms     0x08
#define SDLYBR_09ms     0x09
#define SDLYBR_10ms     0x0A
#define SDLYBR_11ms     0x0B
#define SDLYBR_12ms     0x0C
#define SDLYBR_13ms     0x0D
#define SDLYBR_14ms     0x0E
#define SDLYBR_15ms     0x0F

extern ECReg    SDSR;               // Scan Data Control 4 Register
#define SDV             BIT(0)      // Scan data valid

extern ECReg    KSIGPODR;           // Keyboard Scan In [7:0] GPIO Open-Drain Register
// 0b: Configure KSIx as push-pull if this pin is set GPO.
// 1b: Configure KSIx as open-drain if this pin is set GPO.
#define KSI7ODEN            BIT(7)  // KSI7 Configure 0:push-pull, 1:open-drain
#define KSI6ODEN            BIT(6)  // KSI6 Configure 0:push-pull, 1:open-drain
#define KSI5ODEN            BIT(5)  // KSI5 Configure 0:push-pull, 1:open-drain
#define KSI4ODEN            BIT(4)  // KSI4 Configure 0:push-pull, 1:open-drain
#define KSI3ODEN            BIT(3)  // KSI3 Configure 0:push-pull, 1:open-drain
#define KSI2ODEN            BIT(2)  // KSI2 Configure 0:push-pull, 1:open-drain
#define KSI1ODEN            BIT(1)  // KSI1 Configure 0:push-pull, 1:open-drain
#define KSI0ODEN            BIT(0)  // KSI0 Configure 0:push-pull, 1:open-drain

extern ECReg    KSOHGPODR;          // Keyboard Scan Out [15:8] GPIO Open-Drain Register
// 0b: Configure KSOx as push-pull if this pin is set GPO.
// 1b: Configure KSOx as open-drain if this pin is set GPO.
#define KSO15ODEN           BIT(7)  // KSO15 Configure 0:push-pull, 1:open-drain
#define KSO14ODEN           BIT(6)  // KSO14 Configure 0:push-pull, 1:open-drain
#define KSO13ODEN           BIT(5)  // KSO13 Configure 0:push-pull, 1:open-drain
#define KSO12ODEN           BIT(4)  // KSO12 Configure 0:push-pull, 1:open-drain
#define KSO11ODEN           BIT(3)  // KSO11 Configure 0:push-pull, 1:open-drain
#define KSO10ODEN           BIT(2)  // KSO10 Configure 0:push-pull, 1:open-drain
#define KSO9ODEN            BIT(1)  // KSO9 Configure  0:push-pull, 1:open-drain
#define KSO8ODEN            BIT(0)  // KSO8 Configure  0:push-pull, 1:open-drain

extern ECReg    KSOLGPODR;          // Keyboard Scan Out [7:0] GPIO Open-Drain Register
// 0b: Configure KSOx as push-pull if this pin is set GPO.
// 1b: Configure KSOx as open-drain if this pin is set GPO.
#define KSO7ODEN            BIT(7)  // KSO7 Configure 0:push-pull, 1:open-drain
#define KSO6ODEN            BIT(6)  // KSO6 Configure 0:push-pull, 1:open-drain
#define KSO5ODEN            BIT(5)  // KSO5 Configure 0:push-pull, 1:open-drain
#define KSO4ODEN            BIT(4)  // KSO4 Configure 0:push-pull, 1:open-drain
#define KSO3ODEN            BIT(3)  // KSO3 Configure 0:push-pull, 1:open-drain
#define KSO2ODEN            BIT(2)  // KSO2 Configure 0:push-pull, 1:open-drain
#define KSO1ODEN            BIT(1)  // KSO1 Configure 0:push-pull, 1:open-drain
#define KSO0ODEN            BIT(0)  // KSO0 Configure 0:push-pull, 1:open-drain

//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM)
//-----------------------------------------------------------------------------
// 0: Operation
// 1: Clock to this module is gated
extern ECReg    CGCTRL1R;           // Clock Gating Control 1
extern ECReg    CGCTRL2R;           // Clock Gating Control 2
#define EXGCG               BIT(6)  // EGPC Clock Gating
#define CIRCG               BIT(5)  // CIR Clock Gating
#define SWUCCG              BIT(4)  // SWUC Clock Gating

extern ECReg    CGCTRL3R;           // Clock Gating Control 3
#define PECICG              BIT(3)  // PECI Clock Gating
#define UART12CG            BIT(2)  // UART Clock Gating
#define SSPICG              BIT(1)  // SSPI Clock Gating
#define DBGRCG              BIT(0)  // DBGR Clock Gating

extern ECReg    PLLCTRL;            // PLL Control
#define DDMC                BIT(1)  // Deep Doze Mode Control
#define PPDC                BIT(0)  // PLL Power Down Control

extern ECReg    AUTOCG;             // Auto Clock Gating
#define AUART1CG            BIT(6)  // Auto UART1 Clock Gating
#define AUART2CG            BIT(5)  // Auto UART2 Clock Gating
#define ASSPICG             BIT(4)  // Auto SSPI Clock Gating
#define ACIRCG              BIT(2)  // Auto CIR Clock Gating

extern ECReg    PLLFREQR;           // PLL Frequency
#define _PLL_FREQ_18_4_MHZ  0x00
#define _PLL_FREQ_32_3_MHZ  0x03
#define _PLL_FREQ_64_5_MHZ  0x07

extern ECReg    PLLSSCR;            // PLL Frequency
#define DDGME               BIT(7)  // Deep-Doze Gating Mode Enable

extern ECReg    PLLCSS;             // PLL Clock Source Status
extern ECReg    CGCTRL4R;           // Clock Gating Control 4 Register
#define CECCG               BIT(0)  // CEC Clock Gating

//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD)
//-----------------------------------------------------------------------------
extern ECReg    ETWCFG;             // External Timer/WDT Configuration Register
#define EWDKEYEN            BIT(5)  // External WDT Key Enabled
#define EWDSRC              BIT(4)  // External WDT Clock Source
#define LEWDCNTL            BIT(3)  // Lock EWDCNTLx Register
#define LET1CNTL            BIT(2)  // Lock ET1CNTLx Registers
#define LET1PS              BIT(1)  // Lock ET1PS Register
#define LETWCFG             BIT(0)  // Lock ETWCFG Register

extern ECReg    ET1PSR;             // External Timer Prescaler Register
#define ET_SOURCE_32768Hz   0x00
#define ET_SOURCE_1024Hz    0x01
#define ET_SOURCE_32Hz      0x02

extern ECReg    ET1CNTLHR;          // External Timer Counter High Byte
extern ECReg    ET1CNTLLR;          // External Timer Counter Low Byte
extern ECReg    ETWCTRL;            // External Timer/WDT Control Register
extern ECReg    EWDCNTLLR;          // External WDT Counter Low Byte
extern ECReg    EWDKEYR;            // External WDT Key Register
#define EWDKEY      EWDKEYR
/* External WDT is re-started (touched) if 5Ch is written to this
   register. Writing with other values causes an External Watchdog Reset.
   This function is enabled by EWDKEYEN bit.
   Read returns unpredictable value.
*/
extern ECReg    EWDCNTLHR;          // External WDT Counter High Byte

extern ECReg    ET2PSR;             // External Timer 2 Prescaler Register
#define ET2_SOURCE_32768Hz  0x00
#define ET2_SOURCE_1024Hz   0x01
#define ET2_SOURCE_32Hz     0x02

extern ECReg    ET2CNTLHR;          // External Timer 2 Counter High Byte
extern ECReg    ET2CNTLLR;          // External Timer 2 Counter Low Byte
extern ECReg    ET2CNTLH2R;         // External Timer 2 Counter High Byte 2

extern ECReg    ET3PSR;             // External Timer 3 Prescaler Register
#define ET3_SOURCE_32768Hz  0x00
#define ET3_SOURCE_1024Hz   0x01
#define ET3_SOURCE_32Hz     0x02

extern ECReg    ET3CNTLHR;          // External Timer 3 Counter High Byte
extern ECReg    ET3CNTLLR;          // External Timer 3 Counter Low Byte
extern ECReg    ET3CNTLH2R;         // External Timer 3 Counter High Byte 2

extern ECReg    ET4CNTLLR;          // External Timer 2 Counter Low Byte

//-----------------------------------------------------------------------------
// (20xxh) General Control (GCTRL)
//-----------------------------------------------------------------------------
extern ECReg    ECHIPID1;           // Chip ID Byte 1
extern ECReg    ECHIPID2;           // Chip ID Byte 2
extern ECReg    ECHIPVER;           // Chip Version
#define _CHIP_AX        0
#define _CHIP_BX        1
#define _CHIP_CX        2
#define _CHIP_DX        8
#define _CHIP_EX        5
#define _CHIP_EX2       6

extern ECReg    IDR;                // Identify Input Register
#define IDR_ID7             BIT(7)
#define IDR_ID6             BIT(6)
#define IDR_ID5             BIT(5)
#define IDR_ID4             BIT(4)
#define IDR_ID3             BIT(3)
#define IDR_ID2             BIT(2)
#define IDR_ID1             BIT(1)
#define IDR_ID0             BIT(0)

extern ECReg    RSTS;               // Reset Status
#define VFSPIPG             BIT(5)  // VFSPI Power Good
#define HGRST               BIT(3)  // Host Global Reset
#define GRST                BIT(2)  // Global Reset

extern ECReg    RSTC1;              // Reset Control 1
#define RSMFI               BIT(7)  // Reset SMFI
#define RINTC               BIT(6)  // Reset INTC
#define REC2I               BIT(5)  // Reset EC2I
#define RKBC                BIT(4)  // Reset KBC
#define RSWUC               BIT(3)  // Reset SWUC
#define RPMC                BIT(2)  // Reset PMC
#define RGPIO               BIT(1)  // Reset GPIO
#define RPWM                BIT(0)  // Reset PWM

extern ECReg    RSTC2;              // Reset Control 2
#define RADC                BIT(7)  // Reset ADC
#define RDAC                BIT(6)  // Reset DAC
#define RWUC                BIT(5)  // Reset WUC
#define RKBS                BIT(4)  // Reset KBS
//#define --                BIT(3)  // Reserved
#define REXGPIO             BIT(2)  // Reset EGPC
#define RCIR                BIT(1)  // Reset CIR
//#define --                BIT(0)  // Reserved

extern ECReg    RSTC3;              // Reset Control 3
//#define --                BIT(7)  // Reserved
#define RPS23               BIT(6)  // Reset PS/2 Channel 3
#define RPS22               BIT(5)  // Reset PS/2 Channel 2
#define RPS21               BIT(4)  // Reset PS/2 Channel 1
// To reset the logic of PS/2 shared with all channels, write 1111b to
// bit 7-4 at the same time and writing 0111b is reserved.
#define RSMBD               BIT(3)  // Reset SMBus Channel D
#define RSMBC               BIT(2)  // Reset SMBus Channel C
#define RSMBB               BIT(1)  // Reset SMBus Channel B
#define RSMBA               BIT(0)  // Reset SMBus Channel A
// To reset the logic of SMBus shared with all channels,
// write 1111b to bit 3-0 at the same time and writing 0111b is reserved.

extern ECReg    RSTC4;              // Reset Control 4
#define RCEC                BIT(7)  // Reset CEC
//#define --                BIT(6)  // Reserved
//#define --                BIT(5)  // Reserved
#define RPECI               BIT(4)  // Reset PECI
#define RTMR                BIT(3)  // Reset TMR
#define RUART2              BIT(2)  // Reset UART2
#define RUART1              BIT(1)  // Reset UART1
#define RSPI                BIT(0)  // Reset SSPI

extern ECReg    RSTC6;              // Reset Control 6

extern ECReg    RSTDMMC;            // Reset Control DMMC
// 1: belongs to the EC side.
// 0: belongs to the host side
#define UART1SD             BIT(3)  // UART1 SIDE
#define UART2SD             BIT(2)  // UART2 SIDE
#define SSPISD              BIT(1)  // SSPI SIDE
#define CIRSD               BIT(0)  // CIR SIDE

extern ECReg    BADRSEL;            // Base Address Select
extern ECReg    WNCKR;              // Wait Next Clock Rising
extern ECReg    SPCTRL5;            // Oscillator Control Register
#define ECRTCRAM            BIT(4)  // ECRTCT RAM Only
/* If HRTCRAM or ECRTCRAM is one,
   Index 80h-FFh in RTCT Bank 0/1 is RAM bytes.
   Otherwise,
   Bit 7 of index in RTCT Bank 0/1 is not decoded.
*/

extern ECReg    SPCTRL1;            // Special Control 1
#define P80LEN              BIT(7)  // P80L Enable
#define ACP80               BIT(6)  // Accept Port 80h Cycle
#define ACP81               BIT(3)  // Accept Port 81h Cycle
#define _I2EC_OFF           0x00    // BIT1-0:00b I2EC is disabled.
#define _I2EC_RD_ONLY       0x01    // BIT1-0:10b I2EC is read-only.
#define _I2EC_EN_RW         0x03    // BIT1-0:11b I2EC is read-write.

extern ECReg    RSTCH;              // Reset Control Host Side
#define RSTPNP              BIT(2)  // Reset PNPCFG

extern ECReg    GENIRQ;             // Generate IRQ
extern ECReg    SPCTRL2;            // Special Control 2
#define PI2ECEN             BIT(0)  // Decode I2EC cycles via address I2EC_XADDR

extern ECReg    SPCTRL3;            // Special Control 3
#define ESPIP80CM           BIT(5)  // eSPI Port80 Catch Mode

extern ECReg    SPCTRL4;            // Special Control 4
#define LRSIPDR             BIT(3)  // Last Reset Source Is Pre-defined Reset
#define LRSIWR              BIT(2)  // Last Reset Source Is Warm Reset
#define LRSIPWRSWTR         BIT(1)  // Last Reset Source Is PWRSW Timeout Reset
#define LRSIPGWR            BIT(0)  // Last Reset Source Is Power Good Watch Reset

extern ECReg    PI2ECH;             // Port I2EC High-Byte Register
extern ECReg    PI2ECL;             // Port I2EC Low-Byte Register
/*
  LPC I/O port with address equal to PORT_I2EC[15:0] + 1: I2EC_XADDR_H
  LPC I/O port with address equal to PORT_I2EC[15:0] + 2: I2EC_XADDR_L
  LPC I/O port with address equal to PORT_I2EC[15:0] + 3: I2EC_XDATA
  EC only accepts the LPC I/O cycle with PORT_I2EC address
  if PI2ECEN bit in SPCTRL2 register is set.
*/

extern ECReg    BINTADDR0R;         // BRAM Interrupt Address 0 Register
extern ECReg    BINTADDR1R;         // BRAM Interrupt Address 1 Register
extern ECReg    BINTCTRLR;          // BRAM Interrupt Control Register
#define BINTA1MSTS          BIT(5)  // BRAM Interrupt Address 1 Match Status
#define BINTA0MSTS          BIT(4)  // BRAM Interrupt Address 0 Match Status
#define BINTA1EN            BIT(1)  // BRAM Interrupt Address 1 Enable
#define BINTA0EN            BIT(0)  // BRAM Interrupt Address 0 Enable

extern ECReg    REG_201D;

extern ECReg    SHA1HASHCTRLR;      // SHA1 Hash Control Register
extern ECReg    SHA1HBADDR;         // SHA1 Hash Base Address Register
extern ECReg    P80H81HSR;          // Port 80h/81h Status Register
#define P80H81HRS           BIT(0)  // Port 80h/81h Receive Status

extern ECReg    P80HDR;             // Port 80h Data Register
extern ECReg    P81HDR;             // Port 81h Data Register

//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC)
//-----------------------------------------------------------------------------
extern ECReg    EADDR;              // External GPIO Address
extern ECReg    EDAT;               // External GPIO Data
extern ECReg    ECNT;               // External GPIO Control

extern ECReg    ESTS;               // External GPIO Status
#define CDS                 BIT(0)  // Cycle Done Status

extern ECReg    EARCR;              // External GPIO Auto Read Control
#define ARE                 BIT(4)  // Cycle Done Status
#define ARIE                BIT(3)  // Cycle Done Status
#define SAPM                BIT(2)  // Cycle Done Status
#define ASPS1               BIT(1)  // Cycle Done Status
#define ASPS0               BIT(0)  // Cycle Done Status

extern ECReg    ERE1R;              // External GPIO Read Enable 1
#define EG7RE               BIT(7)  // Cycle Done Status
#define EG6RE               BIT(6)  // Cycle Done Status
#define EG5RE               BIT(5)  // Cycle Done Status
#define EG4RE               BIT(4)  // Cycle Done Status
#define EG3RE               BIT(3)  // Cycle Done Status
#define EG2RE               BIT(2)  // Cycle Done Status
#define EG1RE               BIT(1)  // Cycle Done Status
#define EG0RE               BIT(0)  // Cycle Done Status

extern ECReg    ERE2R;              // External GPIO Read Enable 2
#define EG15RE              BIT(7)  // Cycle Done Status
#define EG14RE              BIT(6)  // Cycle Done Status
#define EG13RE              BIT(5)  // Cycle Done Status
#define EG12RE              BIT(4)  // Cycle Done Status
#define EG11RE              BIT(3)  // Cycle Done Status
#define EG10RE              BIT(2)  // Cycle Done Status
#define EG9RE               BIT(1)  // Cycle Done Status
#define EG8RE               BIT(0)  // Cycle Done Status

extern ECReg    ERE3R;              // External GPIO Read Enable 3
#define EG23RE              BIT(7)  // Cycle Done Status
#define EG22RE              BIT(6)  // Cycle Done Status
#define EG21RE              BIT(5)  // Cycle Done Status
#define EG20RE              BIT(4)  // Cycle Done Status
#define EG19RE              BIT(3)  // Cycle Done Status
#define EG18RE              BIT(2)  // Cycle Done Status
#define EG17RE              BIT(1)  // Cycle Done Status
#define EG16RE              BIT(0)  // Cycle Done Status

extern ECReg    ERE4R;              // External GPIO Read Enable 4
#define EG31RE              BIT(7)  // Cycle Done Status
#define EG30RE              BIT(6)  // Cycle Done Status
#define EG29RE              BIT(5)  // Cycle Done Status
#define EG28RE              BIT(4)  // Cycle Done Status
#define EG27RE              BIT(3)  // Cycle Done Status
#define EG26RE              BIT(2)  // Cycle Done Status
#define EG25RE              BIT(1)  // Cycle Done Status
#define EG24RE              BIT(0)  // Cycle Done Status


extern ECReg    ERE5R;              // External GPIO Read Enable 5
#define EG37RE              BIT(5)  // Cycle Done Status
#define EG36RE              BIT(4)  // Cycle Done Status
#define EG35RE              BIT(3)  // Cycle Done Status
#define EG34RE              BIT(2)  // Cycle Done Status
#define EG33RE              BIT(1)  // Cycle Done Status
#define EG32RE              BIT(0)  // Cycle Done Status

extern ECReg    ESVR;               // External GPIO Status Vector
extern ECReg    ESCF1R;             // External GPIO Status Change Flag 1
extern ECReg    ESCF2R;             // External GPIO Status Change Flag 2
extern ECReg    ESCF3R;             // External GPIO Status Change Flag 3
extern ECReg    ESCF4R;             // External GPIO Status Change Flag 4
extern ECReg    ESCF5R;             // External GPIO Status Change Flag 5

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM)
//-----------------------------------------------------------------------------
extern ECReg    BRAM2[];            // 128 bytes bram
extern ECReg    BRAM[];             // 64 bytes bram

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR)
//-----------------------------------------------------------------------------
extern ECReg    C0DR;               // CIR Data Register
extern ECReg    C0MSTCR;            // CIR Master Control Register
#define CIR_CTXSEL          BIT(7)  // CTX Channel Select
#define CIR_CRXSEL          BIT(6)  // CRX Channel Select
#define CIR_ILSEL           BIT(5)  // Internal Loopback Select
#define CIR_ILE             BIT(4)  // Internal Loopback Enable
#define CIR_FIFOTL1         BIT(3)  // FIFO Threshold Level
#define CIR_FIFOTL0         BIT(2)  // FIFO Threshold Level
#define CIR_FIFOCLR         BIT(1)  // FIFO Clear
#define CIR_RESET           BIT(0)  // RESET

extern ECReg    C0IER;              // CIR Interrupt Enable Register
extern ECReg    C0IIR;              // CIR Interrupt Identification Register
extern ECReg    C0CFR;              // CIR Carrier Frequency Register
extern ECReg    C0RCR;              // CIR Receive Control Register
#define CIR_RXEN            BIT(7)  // Receiver Enable
//#define   CIR_            BIT(6)  // Reserved
#define CIR_RDWOS           BIT(5)  // Receiver Data Without Sync.
#define CIR_RXEND           BIT(4)  // Receiver Demodulation Enable
#define CIR_RXACT           BIT(3)  // Receiver Active
#define CIR_RXDCR2          BIT(2)  // Receiver Demodulation Carrier Range
#define CIR_RXDCR1          BIT(1)  // Receiver Demodulation Carrier Range
#define CIR_RXDCR0          BIT(0)  // Receiver Demodulation Carrier Range

extern ECReg    C0TCR;              // CIR Transmitter Register
extern ECReg    C0SCK;              // CIR for sleep mode
#define DLLOCK              BIT(7)  // DLL Lock
#define BRCM2               BIT(6)  // Baud Rate Count Mode
#define BRCM1               BIT(5)  // Baud Rate Count Mode
#define BRCM0               BIT(4)  // Baud Rate Count Mode
#define DLLTE               BIT(3)  // DLL Test Enable
#define DLL1P8E             BIT(2)  // DLL 1.8432M Enable
#define TXDCKG              BIT(1)  // TXD Clock Gating
#define SCKS                BIT(0)  // Slow Clock Select

extern ECReg    C0BDLR;             // CIR Baud Rate Divisor Low Byte Register
extern ECReg    C0BDHR;             // CIR Baud Rate Divisor High Byte Register
extern ECReg    C0TFSR;             // CIR Transmitter FIFO Status Register
extern ECReg    C0RFSR;             // CIR Receiver FIFO Status Register
extern ECReg    C0WCSSR;            // CIR Wakeup Code Set Select Register
extern ECReg    C0WCL;              // CIR Wakeup Code Length Register
extern ECReg    C0WCR;              // CIR Wakeup Code Read/Write Register
extern ECReg    C0WPS;              // CIR Wakeup Code Power Control/Status Register
extern ECReg    CSCRR;              // CIR Scratch Register

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR)
//-----------------------------------------------------------------------------
extern ECReg    BKA1L;              // Trigger 1 Address Low Byte
extern ECReg    BKA1M;              // Trigger 1 Address Middle Byte
extern ECReg    BKA1H;              // Trigger 1 Address High Byte
extern ECReg    BKA2L;              // Trigger 2 Address Low Byte
extern ECReg    BKA2M;              // Trigger 2 Address Middle Byte
extern ECReg    BKA2H;              // Trigger 2 Address High Byte
extern ECReg    BKA3L;              // Trigger 3 Address Low Byte
extern ECReg    BKA3M;              // Trigger 3 Address Middle Byte
extern ECReg    BKA3H;              // Trigger 3 Address High Byte

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI)
//-----------------------------------------------------------------------------
extern ECReg    SPIDATA;            // SPI Data
extern ECReg    SPICTRL1;           // SPI Control 1
#define CHPOL               BIT(7)  // Chip Select Polarity
#define CLPOL               BIT(6)  // Clock Polarity
#define CLPHS               BIT(5)  // Clock Phase
#define SCKFREQ2            BIT(4)
#define SCKFREQ1            BIT(3)
#define SCKFREQ0            BIT(2)  // SSCK Frequency
#define NTREN               BIT(1)  // Interrupt Enable
#define WIRECH0             BIT(0)  // Device0 3-Wire Mode,
// 0: Disable (4-wire), 1: Enable (3-wire)

extern ECReg    SPICTRL2;           // SPI Control 2
#define HBANK               BIT(7)  // Host Side Bank
#define DEVBUSYPOL          BIT(6)  // Device Busy Polarity
#define BYTEWIDTH2          BIT(5)  // Byte Width
#define BYTEWIDTH1          BIT(4)  // Byte Width
#define BYTEWIDTH0          BIT(3)  // Byte Width
#define CHRW                BIT(2)  // Channel Read/Write Cycle
#define BLKSEL              BIT(1)  // Block Select
#define WIRECH1             BIT(0)  // Device1 3-Wire Mode,
//0: Disable (4-wire), 1: Enable (3-wire)

extern ECReg    SPICTRL3;           // SPI Control 3
#define DEVBUSYMODE         BIT(3)  // Device Busy Mode
#define CSPOLSEL            BIT(2)  // Chip Select Polarity Select
#define CHPOL1              BIT(1)  // Chip Select Polarity 1
#define BUSYNOCLK           BIT(0)  // No BUSY Clock

extern ECReg    SPISTS;             // SPI Status
#define WAITBUSYSTART       BIT(7)  // Wait Busy Start Signal
#define DEVBUSY             BIT(6)  // Device Busy Signal
#define TRANEND             BIT(5)  // SPI Transmission End
#define CH0START            BIT(4)  // Channel 0 Start Signal
#define CH1START            BIT(3)  // Channel 1 Start Signal
#define TRANIP              BIT(2)  // Transfer In Progress
#define TRANENDIF           BIT(1)  // Transfer End Flag
#define SPIBUSY             BIT(0)  // SPI Busy

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1)
//-----------------------------------------------------------------------------
extern ECReg    UART1_RBR;          // Receiver Buffer
#define UART1_THR       UART1_RBR   // Transmitter Holding Register
#define UART1_DLL       UART1_RBR   // Divisor Latch LSB
extern ECReg    UART1_IER;          // Interrupt Enable
#define UART1_DLM       UART1_IER   // Divisor Latch MSB
extern ECReg    UART1_IIR;          // Interrupt Identification
extern ECReg    UART1_LCR;          // Line Control
extern ECReg    UART1_MCR;          // Modem Control
extern ECReg    UART1_LSR;          // Line Status
extern ECReg    UART1_MSR;          // Modem Status
extern ECReg    UART1_SCR;          // Scratch Pad
extern ECReg    UART1_ECSPMR;       // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2)
//-----------------------------------------------------------------------------
extern ECReg    UART2_RBR;          // Receiver Buffer
#define UART2_THR       UART2_RBR   // Transmitter Holding Register
#define UART2_DLL       UART2_RBR   // Divisor Latch LSB
extern ECReg    UART2_IER;          // Interrupt Enable
#define UART2_DLM       UART2_IER   // Divisor Latch MSB
extern ECReg    UART2_IIR;          // Interrupt Identification
extern ECReg    UART2_LCR;          // Line Control
extern ECReg    UART2_MCR;          // Modem Control
extern ECReg    UART2_LSR;          // Line Status
extern ECReg    UART2_MSR;          // Modem Status
extern ECReg    UART2_SCR;          // Scratch Pad
extern ECReg    UART2_ECSPMR;       // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
extern ECReg    PRSC;               // TMR Prescaler
extern ECReg    GCSMS;              // Group Clock Source and Mode Select
extern ECReg    CTR_A0;             // A0 Cycle Time
extern ECReg    CTR_A1;             // A1 Cycle Time
extern ECReg    CTR_B0;             // B0 Cycle Time
extern ECReg    CTR_B1;             // B1 Cycle Time
extern ECReg    DCR_A0;             // A0 Duty Time
extern ECReg    DCR_A1;             // A1 Duty Time
extern ECReg    DCR_B0;             // B0 Duty Time
extern ECReg    DCR_B1;             // B1 Duty Time
extern ECReg    CCGSR;              // Channel Clock Group Select
extern ECReg    TMRCE;              // TMR Clock Enable
extern ECReg    TMEIE;              // TMR Interrupt Enable

//-----------------------------------------------------------------------------
// (2Exxh) Consumer Electronics Control (CEC)
//-----------------------------------------------------------------------------
extern ECReg    CECDR;              // CEC Data
extern ECReg    CECFSTS;            // CEC FIFO Status
extern ECReg    CECDLA;             // CEC Device Logical Address
extern ECReg    CECCTRL;            // CEC Control
extern ECReg    CECSTS;             // CEC Status
extern ECReg    CECIE;              // CEC Interrupt Enable
extern ECReg    CECOPSTS;           // CEC Operation Status
extern ECReg    CECCRH;             // CEC Received Header

//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
extern ECReg    HOSTAR;             // Host Status Register
#define TEMPERR             BIT(7)  // PECI Get Temperature Error
#define BUSERR              BIT(6)  // PECI Bus Abnormal/Contention Error
#define EXTERR              BIT(5)  // PECI Slave Message Phase t-bit Extend over Error
#define WR_FCS_ERR          BIT(3)  // Write_FCS Error
#define RD_FCS_ERR          BIT(2)  // Read_FCS Error
#define FINISH              BIT(1)  // Finish
#define HOBY                BIT(0)  // Host Busy

extern ECReg    HOCTLR;             // Host Control Register
#define FIFOCLR             BIT(5)  // Data FIFO Pointer Clear
#define FCSERR_ABT          BIT(4)  // PECI Host Auto-abort at FCS_Error
#define PECIHEN             BIT(3)  // PECI Host Enable
#define CONCTRL             BIT(2)  // PECI Contention Control
#define AWFCS_EN            BIT(1)  // Assured Write FCS Enable
#define START               BIT(0)  // Start

extern ECReg    HOCMDR;             // Host Command Register
extern ECReg    HOTRADDR;           // Host Target Address Register
extern ECReg    HOWRLR;             // Host Write Length Register
extern ECReg    HORDLR;             // Host Read Length Register
extern ECReg    HOWRDR;             // Host Write Data Register
extern ECReg    HORDDR;             // Host Read Data Register

extern ECReg    HOCTL2R;            // Host Control 2 Register
extern ECReg    RWFCSV;             // Received Write FCS Value
extern ECReg    RRFCSV;             // Received Read FCS Value
extern ECReg    WFCSV;              // Write FCS Value
extern ECReg    RFCSV;              // Read FCS Value
extern ECReg    AWFCSV;             // Assured Write FCS Value
extern ECReg    PADCTLR;            // Pad Control Register

//-----------------------------------------------------------------------------
// (31xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
/* Device Identification 00h-03h */
extern ECReg    REG_3100;
extern ECReg    REG_3101;
extern ECReg    REG_3102;
extern ECReg    REG_3103;
#define eSPI_Version_ID             REG_3103
/* General Capabilities and Configurations     04h-07h */
extern ECReg    REG_3104;
#define F_CRC_Checking_Enable       BIT(7) 
#define F_Response_Modifier_Enable  BIT(6) 
#define F_ALERT_MODE                BIT(4)  //0b: EIO1 (I/O[1] ) pin is used to  
                                            //    signal the Alert event

extern ECReg    REG_3105;
#define _eSPI_MAX_FREQ_20MHZ        0x00
#define _eSPI_MAX_FREQ_25MHZ        0x01
#define _eSPI_MAX_FREQ_33MHZ        0x02
#define _eSPI_MAX_FREQ_50MHZ        0x03
#define _eSPI_MAX_FREQ_66MHZ        0x04
#define _eSPI_OP_FREQ_20MHZ         0x00
#define _eSPI_OP_FREQ_25MHZ         0x10
#define _eSPI_OP_FREQ_33MHZ         0x20
#define _eSPI_OP_FREQ_50MHZ         0x30
#define _eSPI_OP_FREQ_66MHZ         0x40

extern ECReg    REG_3106;
extern ECReg    REG_3107;
#define F_Flash_Access_Channel      BIT(3)
#define F_OOB_Message_Channel       BIT(2)
#define F_Virtual_Wire_Channel      BIT(1)
#define F_Peripheral_Channel        BIT(0)

/* Channel 0 Capabilities and Configurations   08h-0Bh */
extern ECReg    REG_3108;
extern ECReg    REG_3109;
extern ECReg    REG_310A;
extern ECReg    REG_310B;
#define F_Bus_Master_Enable         BIT(2)
#define F_Peripheral_Channel_Ready  BIT(1)
#define F_PeripheralChannelEnable   BIT(0)

/* Channel 1 Capabilities and Configurations   0Ch-0Fh */
extern ECReg    REG_310C;
extern ECReg    REG_310D;
extern ECReg    REG_310E;

extern ECReg    REG_310F;
#define F_VW_CHN_READY              BIT(1)
#define F_VW_CHN_ENABLE             BIT(0)

/* Channel 2 Capabilities and Configurations   10h-13h */
extern ECReg    REG_3110;
extern ECReg    REG_3111;
extern ECReg    REG_3112;

extern ECReg    REG_3113;
#define F_OOB_CHN_READY             BIT(1)
#define F_OOB_CHN_ENABLE            BIT(0)

/* Channel 3 Capabilities and Configurations   14h-17h */
extern ECReg    REG_3114;
extern ECReg    REG_3115;
/* REG_3115: Flash Sharing Capability Supported
   This field indicates the flash sharing capability supported by the slave.
   00b: MAFS supported.
   01b: MAFS supported.
   10b: SAFS supported.
   11b: MAFS/SAFS supported.
*/
#define _SUPPORT_MAFS               0x00
#define _SUPPORT_MAFS1              0x01
#define _SUPPORT_SAFS               0x02
#define _SUPPORT_MAFS_SAFS          0x03

extern ECReg    REG_3116;
extern ECReg    REG_3117;
#define F_FLASH_CHN_READY           BIT(1)
#define F_FLASH_CHN_ENABLE          BIT(0)

/* Channel 3 Capabilities and Configurations 2 18h-1Bh */
extern ECReg    REG_3118;
extern ECReg    REG_3119;
extern ECReg    REG_311A;
extern ECReg    REG_311B;

extern ECReg    ESPCTRL0;           //eSPI PC Control 0 (ESPCTRL0) 90h
#define F_PUT_PC_STATUS             BIT(7)  // PUT_PC Status

extern ECReg    ESPCTRL1;           //eSPI PC Control 1 (ESPCTRL1) 91h
extern ECReg    ESPCTRL2;           //eSPI PC Control 2 (ESPCTRL2) 92h
extern ECReg    ESPCTRL3;           //eSPI PC Control 3 (ESPCTRL3) 93h
extern ECReg    ESPCTRL4;           //eSPI PC Control 4 (ESPCTRL4) 94h
extern ECReg    ESPCTRL5;           //eSPI PC Control 5 (ESPCTRL5) 95h
extern ECReg    ESPCTRL6;           //eSPI PC Control 6 (ESPCTRL6) 96h
extern ECReg    ESPCTRL7;           //eSPI PC Control 7 (ESPCTRL7) 97h
extern ECReg    ESPCTRL8;           //eSPI PC Control 8 (ESPCTRL8) 98h
extern ECReg    ESPCTRL9;           //eSPI PC Control 9 (ESPCTRL9) 99h

extern ECReg    ESGCTRL0;           //eSPI General Control 0 (ESGCTRL0) A0h
extern ECReg    ESGCTRL1;           //eSPI General Control 1 (ESGCTRL1) A1h
#define F_eSPI_INT_ENABLE           BIT(7)

extern ECReg    ESGCTRL2;           //eSPI General Control 2 (ESGCTRL2) A2h
#define F_ESPIQCSE                  BIT(7)
#define F_ESPIIPG                   BIT(6)
#define F_eSPI_TO_WUC_ENABLE        BIT(4)

extern ECReg    ESGCTRL3;           //eSPI General Control 3 (ESGCTRL3) A3h
#define F_SESPIPC                   BIT(0)  // Suspend eSPI Peripheral Channel
#define CH0_not_RDY					BIT(0)  // Suspend eSPI Peripheral Channel

extern ECReg    ESUCTRL0;           //eSPI Upstream Control 0 (ESUCTRL0) B0h
#define Upstream_EN 0x80
#define Upstream_GO 0x40
#define Upstream_INT_EN 0x20
#define Upstream_Channe_Disable 0x04
#define Upstream_Done   0x02
#define Upstream_Busy   0x01

extern ECReg    ESUCTRL1;           //eSPI Upstream Control 1 (ESUCTRL1) B1h
//Upstream cycle Type
#define OOB_Message         0x07
#define OOB_Flash_Read      0x08
#define OOB_Flash_Write     0x09
#define OOB_Flash_Erase     0x0A

extern ECReg    ESUCTRL2;           //eSPI Upstream Control 2 (ESUCTRL2) B2h
extern ECReg    ESUCTRL3;           //eSPI Upstream Control 3 (ESUCTRL3) B3h
#define UpstreamLength              ESUCTRL3

extern ECReg    ESUCTRL4;           //eSPI Upstream Control 4 (ESUCTRL4) B4h
extern ECReg    ESUCTRL5;           //eSPI Upstream Control 5 (ESUCTRL5) B5h
extern ECReg    ESUCTRL6;           //eSPI Upstream Control 6 (ESUCTRL6) B6h
//PUT_FLASH_C cycle Type
#define Successful_Completion_Without_Data                          0x00
#define Successful_Completion_With_Data_the_only_Completion         0x04
#define Unsuccessful_Completion_Without_Data_the_last_Completion    0x05
#define Unsuccessful_Completion_Without_Data_the_only_Completion    0x06
#define Invalid_Cycle_Type                                          0x0F

extern ECReg    ESUCTRL7;           //eSPI Upstream Control 7 (ESUCTRL7) B7h
extern ECReg    ESUCTRL8;           //eSPI Upstream Control 8 (ESUCTRL8) B8h

extern ECReg    ESOCTRL0;           //eSPI OOB Control 0 (ESOCTRL0) C0h
#define PUT_OOB_STATUS      0x80

extern ECReg    ESOCTRL1;           //eSPI OOB Control 1 (ESOCTRL1) C1h
#define F_PUT_OOB_INT_ENABLE        BIT(7)

extern ECReg    ESOCTRL2;           //eSPI OOB Control 2 (ESOCTRL2) C2h
extern ECReg    ESOCTRL3;           //eSPI OOB Control 3 (ESOCTRL3) C3h
extern ECReg    ESOCTRL4;           //eSPI OOB Control 4 (ESOCTRL4) C4h
extern ECReg    ESOCTRL5;           //eSPI OOB Control 5 (ESOCTRL5) C5h
extern ECReg    ESOCTRL6;           //eSPI OOB Control 6 (ESOCTRL6) C6h
extern ECReg    ESOCTRL7;           //eSPI OOB Control 7 (ESOCTRL7) C7h

extern ECReg    ESPISAFSC0;         //eSPI SAFS Control 0 (ESPISAFSC0)
extern ECReg    ESPISAFSC1;         //eSPI SAFS Control 1 (ESPISAFSC1)
#define PUT_FLASH_NP_STATUS         BIT(7)

extern ECReg    ESPISAFSC2;         //eSPI SAFS Control 2 (ESPISAFSC2)
extern ECReg    ESPISAFSC3;         //eSPI SAFS Control 3 (ESPISAFSC3)
extern ECReg    ESPISAFSC4;         //eSPI SAFS Control 4 (ESPISAFSC4)
extern ECReg    ESPISAFSC5;         //eSPI SAFS Control 5 (ESPISAFSC5)
extern ECReg    ESPISAFSC6;         //eSPI SAFS Control 6 (ESPISAFSC6)
extern ECReg    ESPISAFSC7;         //eSPI SAFS Control 7 (ESPISAFSC7)

//-----------------------------------------------------------------------------
// (32xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
extern ECReg    VWIDX0;             //eSPI VW Index 0

extern ECReg    VWIDX2;             //eSPI VW Index 2
/* System Event Virtual Wires for Index=2
   Virtual Wire Group: System Event
   Reset: eSPI Reset#
   Direction: Master to Slave
*/
#define F_IDX2_BIT7_RESERVED        BIT(7)
#define F_IDX2_SLP_S5_VALID         BIT(6)
#define F_IDX2_SLP_S4_VALID         BIT(5)
#define F_IDX2_SLP_S3_VALID         BIT(4)
#define F_IDX2_BIT3_RESERVED        BIT(3)
#define F_IDX2_SLP_S5               BIT(2)
#define F_IDX2_SLP_S4               BIT(1)
#define F_IDX2_SLP_S3               BIT(0)

#define IS_eSPI_SLP_S5_VALID()  IS_MASK_SET(VWIDX2, F_IDX2_SLP_S5_VALID)
#define IS_eSPI_SLP_S4_VALID()  IS_MASK_SET(VWIDX2, F_IDX2_SLP_S4_VALID)
#define IS_eSPI_SLP_S3_VALID()  IS_MASK_SET(VWIDX2, F_IDX2_SLP_S3_VALID)

#define IS_eSPI_SLP_S5_HI()     IS_MASK_SET(VWIDX2, F_IDX2_SLP_S5)
#define IS_eSPI_SLP_S5_LO()     IS_MASK_CLEAR(VWIDX2, F_IDX2_SLP_S5)

#define IS_eSPI_SLP_S4_HI()     IS_MASK_SET(VWIDX2, F_IDX2_SLP_S4)
#define IS_eSPI_SLP_S4_LO()     IS_MASK_CLEAR(VWIDX2, F_IDX2_SLP_S4)

#define IS_eSPI_SLP_S3_HI()     IS_MASK_SET(VWIDX2, F_IDX2_SLP_S3)
#define IS_eSPI_SLP_S3_LO()     IS_MASK_CLEAR(VWIDX2, F_IDX2_SLP_S3)


extern ECReg    VWIDX3;             //eSPI VW Index 3
/* System Event Virtual Wires for Index=3
   Virtual Wire Group: System Event
   Reset: eSPI Reset#
   Direction: Master to Slave
*/
#define F_IDX3_BIT7_RESERVED        BIT(7)
#define F_IDX3_OOB_RST_WARN_VALID   BIT(6)
#define F_IDX3_PLTRST_VALID         BIT(5)
#define F_IDX3_SUS_STAT_VALID       BIT(4)
#define F_IDX3_BIT3_RESERVED        BIT(3)
#define F_IDX3_OOB_RST_WARN         BIT(2)
#define F_IDX3_PLTRST               BIT(1)
#define F_IDX3_SUS_STAT             BIT(0)

extern ECReg    VWIDX4;             //eSPI VW Index 4
/* System Event Virtual Wires for Index=4
   Virtual Wire Group: System Event
   Reset: eSPI Reset#
   Direction: Slave to Master
*/
#define F_IDX4_PME_VALID            BIT(7)
#define F_IDX4_WAKE_VALID           BIT(6)
#define F_IDX4_BIT5_RESERVED        BIT(5)
#define F_IDX4_OOB_RST_ACK_VALID    BIT(4)
#define F_IDX4_PME                  BIT(3)
#define F_IDX4_WAKE                 BIT(2)
#define F_IDX4_BIT1_RESERVED        BIT(1)
#define F_IDX4_OOB_RST_ACK          BIT(0)

extern ECReg    VWIDX5;             //eSPI VW Index 5
/* System Event Virtual Wires for Index=5
   Virtual Wire Group: System Event
   Reset: eSPI Reset#
   Direction: Slave to Master
*/
#define F_IDX5_SLAVE_BOOT_LOAD_STATUS_VALID BIT(7)
#define F_IDX5_ERROR_NONFATAL_VALID         BIT(6)
#define F_IDX5_ERROR_FATAL_VALID            BIT(5)
#define F_IDX5_SLAVE_BOOT_LOAD_DONE_VALID   BIT(4)
#define F_IDX5_SLAVE_BOOT_LOAD_STATUS       BIT(3)
#define F_IDX5_ERROR_NONFATAL               BIT(2)
#define F_IDX5_ERROR_FATAL                  BIT(1)
#define F_IDX5_SLAVE_BOOT_LOAD_DONE         BIT(0)

extern ECReg    VWIDX6;             //eSPI VW Index 6
/* System Event Virtual Wires for Index=6
   Virtual Wire Group: System Event
   Reset: PLTRST#
   Direction: Slave to Master
*/
#define F_IDX6_HOST_RST_ACK_VALID   BIT(7)
#define F_IDX6_RCIN_VALID           BIT(6)
#define F_IDX6_SMI_VALID            BIT(5)
#define F_IDX6_SCI_VALID            BIT(4)
#define F_IDX6_HOST_RST_ACK         BIT(3)
#define F_IDX6_RCIN                 BIT(2)
#define F_IDX6_SMI                  BIT(1)
#define F_IDX6_SCI                  BIT(0)

extern ECReg    VWIDX7;             //eSPI VW Index 7
/* System Event Virtual Wires for Index=7
   Virtual Wire Group: System Event
   Reset: PLTRST#
   Direction: Master to Slave
*/
#define F_IDX7_BIT7_RESERVED        BIT(7)
#define F_IDX7_NMIOUT_VALID         BIT(6)
#define F_IDX7_SMIOUT_VALID         BIT(5)
#define F_IDX7_HOST_RST_WARN_VALID  BIT(4)
#define F_IDX7_BIT3_RESERVED        BIT(3)
#define F_IDX7_NMIOUT               BIT(2)
#define F_IDX7_SMIOUT               BIT(1)
#define F_IDX7_HOST_RST_WARN        BIT(0)

extern ECReg    VWIDX40;            //eSPI VW Index 40
#define F_IDX40_SUSACK              BIT(0)
#define F_IDX40_VALID               BIT(4)

extern ECReg    VWIDX41;            //eSPI VW Index 41
#define F_IDX41_SUS_WARN            BIT(0)
#define F_IDX41_VALID               BIT(4)

extern ECReg    VWIDX42;            //eSPI VW Index 42
extern ECReg    VWIDX43;            //eSPI VW Index 43
extern ECReg    VWIDX44;            //eSPI VW Index 44
extern ECReg    VWIDX45;            //eSPI VW Index 45
extern ECReg    VWIDX46;            //eSPI VW Index 46
extern ECReg    VWIDX47;            //eSPI VW Index 47

extern ECReg    VWCTRL0;            //eSPI VW Contrl 0
#define F_VW_INT_ENABLE             BIT(7)  // VW Interrupt Enable
#define F_ASVWSIE_ENABLE            BIT(1)  // Auto Send VW SUS_ACK# Interrupt Enable
#define F_ASVWBIE_ENABLE            BIT(0)  // Auto Send VW Boot_Load_Done/Status Interrupt Enable

extern ECReg    VWCTRL1;            //eSPI VW Contrl 1
#define F_VWIDX47_UPDATED           BIT(7)
#define F_VWIDX44_UPDATED           BIT(6)
#define F_VWIDX43_UPDATED           BIT(5)
#define F_VWIDX42_UPDATED           BIT(4)
#define F_VWIDX41_UPDATED           BIT(3)
#define F_VWIDX7_UPDATED            BIT(2)
#define F_VWIDX3_UPDATED            BIT(1)
#define F_VWIDX2_UPDATED            BIT(0)

extern ECReg    VWCTRL2;            //eSPI VW Contrl 2
#define F_DSW_PWROK_SOURCE          BIT(7)
#define F_SW_DSW_PWROK              BIT(6)
#define F_PLATFORM_RESET_CONTROL    BIT(5)

extern ECReg    VWCTRL3;            //eSPI VW Contrl 3
#define F_VW_INDEX_46_RESEND        BIT(5)
#define F_VW_INDEX_45_RESEND        BIT(4)
#define F_VW_INDEX_40_RESEND        BIT(3)
#define F_VW_INDEX_6_RESEND         BIT(2)
#define F_VW_INDEX_5_RESEND         BIT(1)
#define F_VW_INDEX_4_RESEND         BIT(0)

extern ECReg    VWCTRL5;            //eSPI VW Contrl 5
#define F_VWSS                      BIT(4)  // VW SUS_WARN# Select
#define EN_ASVWSE                   BIT(1)  // Auto Send VW SUS_ACK# Enable
#define EN_ASVWBE                   BIT(0)  // Auto Send VW Boot_Load_Done/Status Enable

extern ECReg    VWCTRL6;            //eSPI VW Contrl 6
#define F_ASVWSF                    BIT(1)  // Auto Send VW SUS_ACK# Flag
#define F_ASVWBF                    BIT(0)  // Auto Send VW Boot_Load_Done/Status Flag

extern ECReg    VWCTRL7;            //eSPI VW Contrl 7
#define F_ASVWSS                    BIT(0)  // Auto Send VW SUS_ACK# Select
// 0b: If ASVWSE is 1, EC sends SUS_ACK# =0.
// 1b: If ASVWSE is 1, EC sends SUS_ACK# =1.

extern ECReg    REG_32A6;

//-----------------------------------------------------------------------------
// (33xxh) EC Interface Registers, eSI Queue 0 - PUT_PC DATA , PUT_OOB DATA
//-----------------------------------------------------------------------------
extern ECReg    PUT_PC_DATA[];      // 64 bytes PUT_PC_DATA buffer
extern ECReg    PUT_OOB_DATA[];     // 80 bytes PUT_OOB_DATA buffer

//-----------------------------------------------------------------------------
// (34xxh) EC Interface Registers, eSI Queue 1 - UPSTEAM DATA
//-----------------------------------------------------------------------------
extern ECReg    UPSTREAM_DATA[];    // 80 bytes UPSTREAM_DATA buffer
extern ECReg    PUTFLASHNPDB[];

//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of CORE_CHIPREGS.C */
