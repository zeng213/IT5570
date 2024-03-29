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
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI)
//-----------------------------------------------------------------------------
ECReg   FBCFG           _at_ 0x1000;    // FBIU Configuration
ECReg   FPCFG           _at_ 0x1001;    // Flash Programming Configuration
ECReg   FECBSR          _at_ 0x1005;    // Flash EC Code Banking Select
ECReg   FMSSR           _at_ 0x1007;    // Flash Memory Size Select
ECReg   SMECCS          _at_ 0x1020;    // Shared Memory EC Control and Status
ECReg   SMHSR           _at_ 0x1022;    // Shared Memory Host Semaphore
ECReg   FLHCTRL1R       _at_ 0x1031;    // Flash Control   1
ECReg   FLHCTRL2R       _at_ 0x1032;    // Flash Control   2
ECReg   DCache          _at_ 0x1033;    // 256 bytes cache
ECReg   UCCTRLR         _at_ 0x1034;    // uC Control
ECReg   HCTRL2R         _at_ 0x1036;    // Host Control 2
ECReg   HSPICTRL2R      _at_ 0x1039;    // HSPI Control 2
ECReg   HSPICTRL3R      _at_ 0x103A;    // HSPI
ECReg   ECINDAR0        _at_ 0x103B;    // EC-Indirect Memory Address   0
ECReg   ECINDAR1        _at_ 0x103C;    // EC-Indirect Memory Address   1
ECReg   ECINDAR2        _at_ 0x103D;    // EC-Indirect Memory Address   2
ECReg   ECINDAR3        _at_ 0x103E;    // EC-Indirect Memory Address   3
ECReg   ECINDDR         _at_ 0x103F;    // EC-Indirect Memory Data
ECReg   SCRA0L          _at_ 0x1040;    // Scratch SRAM 0 Address Low Byte
ECReg   SCRA0M          _at_ 0x1041;    // Scratch SRAM 0 Address Middle Byte
ECReg   SCRA0H          _at_ 0x1042;    // Scratch SRAM 0 Address High Byte

#if !ITE_CHIP_IT557X   //0: IT557x No DMA1~4
ECReg   SCRA1L          _at_ 0x1043;    // Scratch SRAM 1 Address Low Byte
ECReg   SCRA1M          _at_ 0x1044;    // Scratch SRAM 1 Address Middle Byte
ECReg   SCRA1H          _at_ 0x1045;    // Scratch SRAM 1 Address High Byte
ECReg   SCRA2L          _at_ 0x1046;    // Scratch SRAM 2 Address Low Byte
ECReg   SCRA2M          _at_ 0x1047;    // Scratch SRAM 2 Address Middle Byte
ECReg   SCRA2H          _at_ 0x1048;    // Scratch SRAM 2 Address High Byte
ECReg   SCRA3L          _at_ 0x1049;    // Scratch SRAM 3 Address Low Byte
ECReg   SCRA3M          _at_ 0x104A;    // Scratch SRAM 3 Address Middle Byte
ECReg   SCRA3H          _at_ 0x104B;    // Scratch SRAM 3 Address High Byte
ECReg   SCRA4L          _at_ 0x104C;    // Scratch SRAM 4 Address Low Byte
ECReg   SCRA4M          _at_ 0x104D;    // Scratch SRAM 4 Address Middle Byte
ECReg   SCRA4H          _at_ 0x104E;    // Scratch SRAM 4 Address High Byte
#endif  //ITE_CHIP_IT557X

ECReg   P0BA0R          _at_ 0x104F;    // Protect 0 Base Addr   0
ECReg   P0BA1R          _at_ 0x1050;    // Protect 0 Base Addr   1
ECReg   P0ZR            _at_ 0x1051;    // Protect 0 Size
ECReg   P1BA0R          _at_ 0x1052;    // Protect 1 Base Addr   0
ECReg   P1BA1R          _at_ 0x1053;    // Protect 1 Base Addr   1
ECReg   P1ZR            _at_ 0x1054;    // Protect 1 Size
ECReg   DSINST          _at_ 0x1055;    // Deferred SPI Instruction
ECReg   DSADR1          _at_ 0x1056;    // Deferred SPI Address
ECReg   DSADR2          _at_ 0x1057;    // Deferred SPI Address
ECReg   HINSTC1         _at_ 0x1058;    // Host Instruction Control 1
ECReg   HINSTC2         _at_ 0x1059;    // Host Instruction Control 2
ECReg   HRAMWC          _at_ 0x105A;    // Host RAM Window Control
ECReg   HRAMW0BA        _at_ 0x105B;    // Host RAM Window 0 Base Address
ECReg   HRAMW1BA        _at_ 0x105C;    // Host RAM Window 1 Base Address
ECReg   HRAMW0AAS       _at_ 0x105D;    // Host RAM Window 0 Access Allow Size
ECReg   HRAMW1AAS       _at_ 0x105E;    // Host RAM Window 1 Access Allow Size
ECReg   SCAR5H          _at_ 0x105F;
ECReg   REG_1060        _at_ 0x1060;
ECReg   FLHCTRL3R       _at_ 0x1063;    // Flash Control 3
ECReg   FLHCTRL4R       _at_ 0x1064;    // Flash Control 4
ECReg   HSPICTRL        _at_ 0x1068;    // HSPI Control Register 4
ECReg   P2BA0R          _at_ 0x1070;    // Protect 2 Base Addr Register 0
ECReg   P2BA1R          _at_ 0x1071;    // Protect 2 Base Addr Register 1
ECReg   P2ZR            _at_ 0x1072;    // Protect 2 Size
ECReg   P3BA0R          _at_ 0x1073;    // Protect 3 Base Addr Register 0
ECReg   P3BA1R          _at_ 0x1074;    // Protect 3 Base Addr Register 1
ECReg   P3ZR            _at_ 0x1075;    // Protect 3 Size
ECReg   HRAMW2BA        _at_ 0x1076;    // Host RAM Windows 2 Base Address
ECReg   HRAMW3BA        _at_ 0x1077;    // Host RAM Windows 3 Base Address
ECReg   HRAMW2AAS       _at_ 0x1078;    // Host RAM Windows 2 Access Allow Size
ECReg   HRAMW3AAS       _at_ 0x1079;    // Host RAM Windows 3 Access Allow Size
ECReg   H2RAMECSIE      _at_ 0x107A;    // H2RAM EC Semaphore Interrupt Enable
ECReg   H2RAMECSA       _at_ 0x107B;    // H2RAM EC Semaphore Address
ECReg   H2RAMHSS        _at_ 0x107C;    // H2RAM Host Semaphore Status
ECReg   HPADR           _at_ 0x107E;    // Host Protect Authentication Data
ECReg   FLHCTRL5R       _at_ 0x1080;    // Flash Control 5
ECReg   FLHCTRL6R       _at_ 0x1081;    // Flash Control 6

ECReg   SCARSL          _at_ 0x109F;    // Scratch SRAM SMBus Address Low
ECReg   SCARSM          _at_ 0x10A0;    // Scratch SRAM SMBus Address Middle
ECReg   SCARSH          _at_ 0x10A1;    // Scratch SRAM SMBus Address High
ECReg   REG_10A2        _at_ 0x10A2;

//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC)
//-----------------------------------------------------------------------------
ECReg   ISR0            _at_ 0x1100;    // Interrupt Status 0
ECReg   ISR1            _at_ 0x1101;    // Interrupt Status 1
ECReg   ISR2            _at_ 0x1102;    // Interrupt Status 2
ECReg   ISR3            _at_ 0x1103;    // Interrupt Status 3
ECReg   ISR4            _at_ 0x1114;    // Interrupt Status 4
ECReg   ISR5            _at_ 0x1118;    // Interrupt Status 5
ECReg   ISR6            _at_ 0x111C;    // Interrupt Status 6
ECReg   ISR7            _at_ 0x1120;    // Interrupt Status 7
ECReg   ISR8            _at_ 0x1124;    // Interrupt Status 8
ECReg   ISR9            _at_ 0x1128;    // Interrupt Status 9
ECReg   ISR10           _at_ 0x112C;    // Interrupt Status 10
ECReg   ISR11           _at_ 0x1130;    // Interrupt Status 11
ECReg   ISR12           _at_ 0x1134;    // Interrupt Status 12
ECReg   ISR13           _at_ 0x1138;    // Interrupt Status 13
ECReg   ISR14           _at_ 0x113C;    // Interrupt Status 14
ECReg   ISR15           _at_ 0x1140;    // Interrupt Status 15
ECReg   ISR16           _at_ 0x1144;    // Interrupt Status 16
ECReg   ISR17           _at_ 0x1148;    // Interrupt Status 17
ECReg   ISR18           _at_ 0x114C;    // Interrupt Status 18
ECReg   ISR19           _at_ 0x1150;    // Interrupt Status 19
ECReg   ISR20           _at_ 0x1154;    // Interrupt Status 20
ECReg   ISR21           _at_ 0x1158;    // Interrupt Status 21

ECReg   IER0            _at_ 0x1104;    // Interrupt Enable 0
ECReg   IER1            _at_ 0x1105;    // Interrupt Enable 1
ECReg   IER2            _at_ 0x1106;    // Interrupt Enable 2
ECReg   IER3            _at_ 0x1107;    // Interrupt Enable 3
ECReg   IER4            _at_ 0x1115;    // Interrupt Enable 4
ECReg   IER5            _at_ 0x1119;    // Interrupt Enable 5
ECReg   IER6            _at_ 0x111D;    // Interrupt Enable 6
ECReg   IER7            _at_ 0x1121;    // Interrupt Enable 7
ECReg   IER8            _at_ 0x1125;    // Interrupt Enable 8
ECReg   IER9            _at_ 0x1129;    // Interrupt Enable 9
ECReg   IER10           _at_ 0x112D;    // Interrupt Enable 10
ECReg   IER11           _at_ 0x1131;    // Interrupt Enable 11
ECReg   IER12           _at_ 0x1135;    // Interrupt Enable 12
ECReg   IER13           _at_ 0x1139;    // Interrupt Enable 13
ECReg   IER14           _at_ 0x113D;    // Interrupt Enable 14
ECReg   IER15           _at_ 0x1141;    // Interrupt Enable 15
ECReg   IER16           _at_ 0x1145;    // Interrupt Enable 16
ECReg   IER17           _at_ 0x1149;    // Interrupt Enable 17
ECReg   IER18           _at_ 0x114D;    // Interrupt Enable 18
ECReg   IER19           _at_ 0x1151;    // Interrupt Enable 19
ECReg   IER20           _at_ 0x1155;    // Interrupt Enable 20
ECReg   IER21           _at_ 0x1159;    // Interrupt Enable 21

ECReg   IELMR0          _at_ 0x1108;    // Interrupt Edge/Level-Triggered Mode 0
ECReg   IELMR1          _at_ 0x1109;    // Interrupt Edge/Level-Triggered Mode 1
ECReg   IELMR2          _at_ 0x110A;    // Interrupt Edge/Level-Triggered Mode 2
ECReg   IELMR3          _at_ 0x110B;    // Interrupt Edge/Level-Triggered Mode 3
ECReg   IELMR4          _at_ 0x1116;    // Interrupt Edge/Level-Triggered Mode 4
ECReg   IELMR5          _at_ 0x111A;    // Interrupt Edge/Level-Triggered Mode 5
ECReg   IELMR6          _at_ 0x111E;    // Interrupt Edge/Level-Triggered Mode 6
ECReg   IELMR7          _at_ 0x1122;    // Interrupt Edge/Level-Triggered Mode 7
ECReg   IELMR8          _at_ 0x1126;    // Interrupt Edge/Level-Triggered Mode 8
ECReg   IELMR9          _at_ 0x112A;    // Interrupt Edge/Level-Triggered Mode 9
ECReg   IELMR10         _at_ 0x112E;    // Interrupt Edge/Level-Triggered Mode 10
ECReg   IELMR11         _at_ 0x1132;    // Interrupt Edge/Level-Triggered Mode 11
ECReg   IELMR12         _at_ 0x1136;    // Interrupt Edge/Level-Triggered Mode 12
ECReg   IELMR13         _at_ 0x113A;    // Interrupt Edge/Level-Triggered Mode 13
ECReg   IELMR14         _at_ 0x113E;    // Interrupt Edge/Level-Triggered Mode 14
ECReg   IELMR15         _at_ 0x1142;    // Interrupt Edge/Level-Triggered Mode 15
ECReg   IELMR16         _at_ 0x1146;    // Interrupt Edge/Level-Triggered Mode 16
ECReg   IELMR17         _at_ 0x114A;    // Interrupt Edge/Level-Triggered Mode 17
ECReg   IELMR18         _at_ 0x114E;    // Interrupt Edge/Level-Triggered Mode 18
ECReg   IELMR19         _at_ 0x1152;    // Interrupt Edge/Level-Triggered Mode 19
ECReg   IELMR20         _at_ 0x1156;    // Interrupt Edge/Level-Triggered Mode 20
ECReg   IELMR21         _at_ 0x115A;    // Interrupt Edge/Level-Triggered Mode 21

ECReg   IPOLR0          _at_ 0x110C;    // Interrupt Polarity 0
ECReg   IPOLR1          _at_ 0x110D;    // Interrupt Polarity 1
ECReg   IPOLR2          _at_ 0x110E;    // Interrupt Polarity 2
ECReg   IPOLR3          _at_ 0x110F;    // Interrupt Polarity 3
ECReg   IPOLR4          _at_ 0x1117;    // Interrupt Polarity 4
ECReg   IPOLR5          _at_ 0x111B;    // Interrupt Polarity 5
ECReg   IPOLR6          _at_ 0x111F;    // Interrupt Polarity 6
ECReg   IPOLR7          _at_ 0x1123;    // Interrupt Polarity 7
ECReg   IPOLR8          _at_ 0x1127;    // Interrupt Polarity 8
ECReg   IPOLR9          _at_ 0x112B;    // Interrupt Polarity 9
ECReg   IPOLR10         _at_ 0x112F;    // Interrupt Polarity 10
ECReg   IPOLR11         _at_ 0x1133;    // Interrupt Polarity 11
ECReg   IPOLR12         _at_ 0x1137;    // Interrupt Polarity 12
ECReg   IPOLR13         _at_ 0x113B;    // Interrupt Polarity 13
ECReg   IPOLR14         _at_ 0x113F;    // Interrupt Polarity 14
ECReg   IPOLR15         _at_ 0x1143;    // Interrupt Polarity 15
ECReg   IPOLR16         _at_ 0x1147;    // Interrupt Polarity 16
ECReg   IPOLR17         _at_ 0x114B;    // Interrupt Polarity 17
ECReg   IPOLR18         _at_ 0x114F;    // Interrupt Polarity 18
ECReg   IPOLR19         _at_ 0x1153;    // Interrupt Polarity 19
ECReg   IPOLR20         _at_ 0x1157;    // Interrupt Polarity 20
ECReg   IPOLR21         _at_ 0x115B;    // Interrupt Polarity 21

ECReg   IVECT           _at_ 0x1110;    // Interrupt Vector
ECReg   INT0ST          _at_ 0x1111;    // INT0# status
ECReg   PFAILR          _at_ 0x1112;    // Power Fail

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge)
//-----------------------------------------------------------------------------
ECReg   IHIOA           _at_ 0x1200;    // Indirect Host I/O Address
ECReg   IHD             _at_ 0x1201;    // Indirect Host Data
ECReg   LSIOHA          _at_ 0x1202;    // Lock Super I/O Host Access
ECReg   SIOLV           _at_ 0x1203;    // Super I/O Access Lock Violation
ECReg   IBMAE           _at_ 0x1204;    // EC to I-Bus Modules Access Enable
ECReg   IBCTL           _at_ 0x1205;    // I-Bus Control

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC)
//-----------------------------------------------------------------------------
ECReg   KBHICR          _at_ 0x1300;    // KBC Host Interface Control
ECReg   KBIRQR          _at_ 0x1302;    // KBC Interrupt Control
ECReg   KBHISR          _at_ 0x1304;    // KBC Host Interface Keyboard/Mouse Status
ECReg   KBHIKDOR        _at_ 0x1306;    // KBC Host Interface Keyboard Data Output
ECReg   KBHIMDOR        _at_ 0x1308;    // KBC Host Interface Mouse Data Output
ECReg   KBHIDIR         _at_ 0x130A;    // KBC Host Interface Keyboard/Mouse Data Input

//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC)
//-----------------------------------------------------------------------------
ECReg   SWCTL1          _at_ 0x1400;    // SWUC Control Status 1
ECReg   SWCTL2          _at_ 0x1402;    // SWUC Control Status 2
ECReg   SWCTL3          _at_ 0x1404;    // SWUC Control Status 3
ECReg   SWCBALR         _at_ 0x1408;    // SWUC Host Configuration Base Address Low Byte
ECReg   SWCBAHR         _at_ 0x140A;    // SWUC Host Configuration Base Address High Byte
ECReg   SWCIER          _at_ 0x140C;    // SWUC Interrupt Enable
ECReg   SWCHSTR         _at_ 0x140E;    // SWUC Host Event Status
ECReg   SWCHIER         _at_ 0x1410;    // SWUC Host Event Interrupt Enable

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC)
//-----------------------------------------------------------------------------
ECReg   PM1STS          _at_ 0x1500;    // Host Interface PM Channel 1 Status
ECReg   PM1DO           _at_ 0x1501;    // Host Interface PM Channel 1 Data Out Port
ECReg   PM1DOSCI        _at_ 0x1502;    // Host Interface PM Channel 1 Data Out Port with SCI
ECReg   PM1DOSMI        _at_ 0x1503;    // Host Interface PM Channel 1 Data Out Port with SMI
ECReg   PM1DI           _at_ 0x1504;    // Host Interface PM Channel 1 Data In Port
ECReg   PM1DISCI        _at_ 0x1505;    // Host Interface PM Channel 1 Data In Port with SCI
ECReg   PM1CTL          _at_ 0x1506;    // Host Interface PM Channel 1 Control
ECReg   PM1IC           _at_ 0x1507;    // Host Interface PM Channel 1 Interrupt Control
ECReg   PM1IE           _at_ 0x1508;    // Host Interface PM Channel 1 Interrupt Enable

ECReg   PM2STS          _at_ 0x1510;    // Host Interface PM Channel 2 Status
ECReg   PM2DO           _at_ 0x1511;    // Host Interface PM Channel 2 Data Out Port
ECReg   PM2DOSCI        _at_ 0x1512;    // Host Interface PM Channel 2 Data Out Port with SCI
ECReg   PM2DOSMI        _at_ 0x1513;    // Host Interface PM Channel 2 Data Out Port with SMI
ECReg   PM2DI           _at_ 0x1514;    // Host Interface PM Channel 2 Data In Port
ECReg   PM2DISCI        _at_ 0x1515;    // Host Interface PM Channel 2 Data In Port with SCI
ECReg   PM2CTL          _at_ 0x1516;    // Host Interface PM Channel 2 Control
ECReg   PM2IC           _at_ 0x1517;    // Host Interface PM Channel 2 Interrupt Control
ECReg   PM2IE           _at_ 0x1518;    // Host Interface PM Channel 2 Interrupt Enable

ECReg   MBXCTRL         _at_ 0x1519;    // Mailbox Control

ECReg   PM3STS          _at_ 0x1520;    // Host Interface PM Channel 3 Status
ECReg   PM3DO           _at_ 0x1521;    // Host Interface PM Channel 3 Data Out Port
ECReg   PM3DI           _at_ 0x1522;    // Host Interface PM Channel 3 Data In Port
ECReg   PM3CTL          _at_ 0x1523;    // Host Interface PM Channel 3 Control
ECReg   PM3IC           _at_ 0x1524;    // Host Interface PM Channel 3 Interrupt Control
ECReg   PM3IE           _at_ 0x1525;    // Host Interface PM Channel 3 Interrupt Enable

ECReg   PM4STS          _at_ 0x1530;    // Host Interface PM Channel 4 Status
ECReg   PM4DO           _at_ 0x1531;    // Host Interface PM Channel 4 Data Out Port
ECReg   PM4DI           _at_ 0x1532;    // Host Interface PM Channel 4 Data In Port
ECReg   PM4CTL          _at_ 0x1533;    // Host Interface PM Channel 4 Control
ECReg   PM4IC           _at_ 0x1534;    // Host Interface PM Channel 4 Interrupt Control
ECReg   PM4IE           _at_ 0x1535;    // Host Interface PM Channel 4 Interrupt Enable

ECReg   PM5STS          _at_ 0x1540;    // Host Interface PM Channel 5 Status
ECReg   PM5DO           _at_ 0x1541;    // Host Interface PM Channel 5 Data Out Port
ECReg   PM5DI           _at_ 0x1542;    // Host Interface PM Channel 5 Data In Port
ECReg   PM5CTL          _at_ 0x1543;    // Host Interface PM Channel 5 Control
ECReg   PM5IC           _at_ 0x1544;    // Host Interface PM Channel 5 Interrupt Control
ECReg   PM5IE           _at_ 0x1545;    // Host Interface PM Channel 5 Interrupt Enable

ECReg   MBXEC[16]       _at_ 0x15F0;    // 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control
//-----------------------------------------------------------------------------
ECReg   GCR             _at_ 0x1600;    // General Control

ECReg   GCR1            _at_ 0x16F0;    // General Control 1
ECReg   GCR2            _at_ 0x16F1;    // General Control 2
ECReg   GCR3            _at_ 0x16F2;    // General Control 3
ECReg   GCR4            _at_ 0x16F3;    // General Control 4
ECReg   GCR5            _at_ 0x16F4;    // General Control 5
ECReg   GCR6            _at_ 0x16F5;    // General Control 6
ECReg   GCR7            _at_ 0x16F6;    // General Control 7
ECReg   GCR8            _at_ 0x16F7;    // General Control 8
ECReg   GCR9            _at_ 0x16F8;    // General Control 9
ECReg   GCR10           _at_ 0x16F9;    // General Control 10
ECReg   GCR11           _at_ 0x16FA;    // General Control 11
ECReg   GCR12           _at_ 0x16FB;    // General Control 12
ECReg   GCR13           _at_ 0x16FC;    // General Control 13
ECReg   GCR14           _at_ 0x16FD;    // General Control 14
ECReg   GCR15           _at_ 0x16FE;    // General Control 15
ECReg   PGWCR           _at_ 0x16FF;    // Power Good Watch Control Register

ECReg   GCR16           _at_ 0x16E0;    // General Control 16
ECReg   GCR17           _at_ 0x16E1;    // General Control 17
ECReg   GCR18           _at_ 0x16E2;    // General Control 18
ECReg   GCR19           _at_ 0x16E4;    // General Control 19
ECReg   GCR20           _at_ 0x16E5;    // General Control 20
ECReg   GCR21           _at_ 0x16E6;    // General Control 21
ECReg   GCR22           _at_ 0x16E7;    // General Control 22
ECReg   GCR23           _at_ 0x16E8;    // General Control 23

ECReg   GCR24           _at_ 0x16E9;    // General Control 24
ECReg   GCR25           _at_ 0x16EA;    // General Control 25

ECReg   GPDRA           _at_ 0x1601;    // Port A Data
ECReg   GPDRB           _at_ 0x1602;    // Port B Data
ECReg   GPDRC           _at_ 0x1603;    // Port C Data
ECReg   GPDRD           _at_ 0x1604;    // Port D Data
ECReg   GPDRE           _at_ 0x1605;    // Port E Data
ECReg   GPDRF           _at_ 0x1606;    // Port F Data
ECReg   GPDRG           _at_ 0x1607;    // Port G Data
ECReg   GPDRH           _at_ 0x1608;    // Port H Data
ECReg   GPDRI           _at_ 0x1609;    // Port I Data
ECReg   GPDRJ           _at_ 0x160A;    // Port J Data
ECReg   GPDRM           _at_ 0x160D;    // Port M Data

ECReg   GPCRA0          _at_ 0x1610;    // Port Control A0
ECReg   GPCRA1          _at_ 0x1611;    // Port Control A1
ECReg   GPCRA2          _at_ 0x1612;    // Port Control A2
ECReg   GPCRA3          _at_ 0x1613;    // Port Control A3
ECReg   GPCRA4          _at_ 0x1614;    // Port Control A4
ECReg   GPCRA5          _at_ 0x1615;    // Port Control A5
ECReg   GPCRA6          _at_ 0x1616;    // Port Control A6
ECReg   GPCRA7          _at_ 0x1617;    // Port Control A7

ECReg   GPCRB0          _at_ 0x1618;    // Port Control B0
ECReg   GPCRB1          _at_ 0x1619;    // Port Control B1
ECReg   GPCRB2          _at_ 0x161A;    // Port Control B2
ECReg   GPCRB3          _at_ 0x161B;    // Port Control B3
ECReg   GPCRB4          _at_ 0x161C;    // Port Control B4
ECReg   GPCRB5          _at_ 0x161D;    // Port Control B5
ECReg   GPCRB6          _at_ 0x161E;    // Port Control B6
ECReg   GPCRB7          _at_ 0x161F;    // Port Control B7

ECReg   GPCRC0          _at_ 0x1620;    // Port Control C0
ECReg   GPCRC1          _at_ 0x1621;    // Port Control C1
ECReg   GPCRC2          _at_ 0x1622;    // Port Control C2
ECReg   GPCRC3          _at_ 0x1623;    // Port Control C3
ECReg   GPCRC4          _at_ 0x1624;    // Port Control C4
ECReg   GPCRC5          _at_ 0x1625;    // Port Control C5
ECReg   GPCRC6          _at_ 0x1626;    // Port Control C6
ECReg   GPCRC7          _at_ 0x1627;    // Port Control C7

ECReg   GPCRD0          _at_ 0x1628;    // Port Control D0
ECReg   GPCRD1          _at_ 0x1629;    // Port Control D1
ECReg   GPCRD2          _at_ 0x162A;    // Port Control D2
ECReg   GPCRD3          _at_ 0x162B;    // Port Control D3
ECReg   GPCRD4          _at_ 0x162C;    // Port Control D4
ECReg   GPCRD5          _at_ 0x162D;    // Port Control D5
ECReg   GPCRD6          _at_ 0x162E;    // Port Control D6
ECReg   GPCRD7          _at_ 0x162F;    // Port Control D7

ECReg   GPCRE0          _at_ 0x1630;    // Port Control E0
ECReg   GPCRE1          _at_ 0x1631;    // Port Control E1
ECReg   GPCRE2          _at_ 0x1632;    // Port Control E2
ECReg   GPCRE3          _at_ 0x1633;    // Port Control E3
ECReg   GPCRE4          _at_ 0x1634;    // Port Control E4
ECReg   GPCRE5          _at_ 0x1635;    // Port Control E5
ECReg   GPCRE6          _at_ 0x1636;    // Port Control E6
ECReg   GPCRE7          _at_ 0x1637;    // Port Control E7

ECReg   GPCRF0          _at_ 0x1638;    // Port Control F0
ECReg   GPCRF1          _at_ 0x1639;    // Port Control F1
ECReg   GPCRF2          _at_ 0x163A;    // Port Control F2
ECReg   GPCRF3          _at_ 0x163B;    // Port Control F3
ECReg   GPCRF4          _at_ 0x163C;    // Port Control F4
ECReg   GPCRF5          _at_ 0x163D;    // Port Control F5
ECReg   GPCRF6          _at_ 0x163E;    // Port Control F6
ECReg   GPCRF7          _at_ 0x163F;    // Port Control F7

ECReg   GPCRG0          _at_ 0x1640;    // Port Control G0
ECReg   GPCRG1          _at_ 0x1641;    // Port Control G1
ECReg   GPCRG2          _at_ 0x1642;    // Port Control G2
ECReg   GPCRG3          _at_ 0x1643;    // Port Control G3
ECReg   GPCRG4          _at_ 0x1644;    // Port Control G4
ECReg   GPCRG5          _at_ 0x1645;    // Port Control G5
ECReg   GPCRG6          _at_ 0x1646;    // Port Control G6
ECReg   GPCRG7          _at_ 0x1647;    // Port Control G7

ECReg   GPCRH0          _at_ 0x1648;    // Port Control H0
ECReg   GPCRH1          _at_ 0x1649;    // Port Control H1
ECReg   GPCRH2          _at_ 0x164A;    // Port Control H2
ECReg   GPCRH3          _at_ 0x164B;    // Port Control H3
ECReg   GPCRH4          _at_ 0x164C;    // Port Control H4
ECReg   GPCRH5          _at_ 0x164D;    // Port Control H5
ECReg   GPCRH6          _at_ 0x164E;    // Port Control H6
ECReg   GPCRH7          _at_ 0x164F;    // Port Control H7

ECReg   GPCRI0          _at_ 0x1650;    // Port Control I0
ECReg   GPCRI1          _at_ 0x1651;    // Port Control I1
ECReg   GPCRI2          _at_ 0x1652;    // Port Control I2
ECReg   GPCRI3          _at_ 0x1653;    // Port Control I3
ECReg   GPCRI4          _at_ 0x1654;    // Port Control I4
ECReg   GPCRI5          _at_ 0x1655;    // Port Control I5
ECReg   GPCRI6          _at_ 0x1656;    // Port Control I6
ECReg   GPCRI7          _at_ 0x1657;    // Port Control I7

ECReg   GPCRJ0          _at_ 0x1658;    // Port Control J0
ECReg   GPCRJ1          _at_ 0x1659;    // Port Control J1
ECReg   GPCRJ2          _at_ 0x165A;    // Port Control J2
ECReg   GPCRJ3          _at_ 0x165B;    // Port Control J3
ECReg   GPCRJ4          _at_ 0x165C;    // Port Control J4
ECReg   GPCRJ5          _at_ 0x165D;    // Port Control J5
ECReg   GPCRJ6          _at_ 0x165E;    // Port Control J6
ECReg   GPCRJ7          _at_ 0x165F;    // Port Control J7

ECReg   GPCRM0          _at_ 0x16A0;    // Port Control M0
ECReg   GPCRM1          _at_ 0x16A1;    // Port Control M1
ECReg   GPCRM2          _at_ 0x16A2;    // Port Control M2
ECReg   GPCRM3          _at_ 0x16A3;    // Port Control M3
ECReg   GPCRM4          _at_ 0x16A4;    // Port Control M4
ECReg   GPCRM5          _at_ 0x16A5;    // Port Control M5
ECReg   GPCRM6          _at_ 0x16A6;    // Port Control M6

ECReg   GPDMRA          _at_ 0x1661;    // Port A Data Mirror
ECReg   GPDMRB          _at_ 0x1662;    // Port B Data Mirror
ECReg   GPDMRC          _at_ 0x1663;    // Port C Data Mirror
ECReg   GPDMRD          _at_ 0x1664;    // Port D Data Mirror
ECReg   GPDMRE          _at_ 0x1665;    // Port E Data Mirror
ECReg   GPDMRF          _at_ 0x1666;    // Port F Data Mirror
ECReg   GPDMRG          _at_ 0x1667;    // Port G Data Mirror
ECReg   GPDMRH          _at_ 0x1668;    // Port H Data Mirror
ECReg   GPDMRI          _at_ 0x1669;    // Port I Data Mirror
ECReg   GPDMRJ          _at_ 0x166A;    // Port J Data Mirror
ECReg   GPDMRM          _at_ 0x166D;    // Port M Data Mirror

ECReg   GPOTA           _at_ 0x1671;    // Output Type
ECReg   GPOTB           _at_ 0x1672;    // Output Type
ECReg   GPOTD           _at_ 0x1674;    // Output Type
ECReg   GPOTE           _at_ 0x1675;    // Output Type
ECReg   GPOTF           _at_ 0x1676;    // Output Type
ECReg   GPOTH           _at_ 0x1678;    // Output Type
ECReg   GPOTJ           _at_ 0x167A;    // Output Type

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface
//-----------------------------------------------------------------------------
ECReg   PSCTL1          _at_ 0x1700;    // PS/2 Control 1
ECReg   PSCTL2          _at_ 0x1701;    // PS/2 Control 2
ECReg   PSCTL3          _at_ 0x1702;    // PS/2 Control 3
ECReg   PSINT1          _at_ 0x1704;    // PS/2 Interrupt Control 1
ECReg   PSINT2          _at_ 0x1705;    // PS/2 Interrupt Control 2
ECReg   PSINT3          _at_ 0x1706;    // PS/2 Interrupt Control 3
ECReg   PSSTS1          _at_ 0x1708;    // PS/2 Status 1
ECReg   PSSTS2          _at_ 0x1709;    // PS/2 Status 2
ECReg   PSSTS3          _at_ 0x170A;    // PS/2 Status 3
ECReg   PSDAT1          _at_ 0x170C;    // PS/2 Data 1
ECReg   PSDAT2          _at_ 0x170D;    // PS/2 Data 2
ECReg   PSDAT3          _at_ 0x170E;    // PS/2 Data 3

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM)
//-----------------------------------------------------------------------------
ECReg   C0CPRS          _at_ 0x1800;    // Channel 0 Clock Pre-Scaler
ECReg   CTR0            _at_ 0x1801;    // Cycle Time 0
ECReg   DCR0            _at_ 0x1802;    // Channel 0 PWM Duty Cycle
ECReg   DCR1            _at_ 0x1803;    // Channel 0 PWM Duty Cycle
ECReg   DCR2            _at_ 0x1804;    // Channel 0 PWM Duty Cycle
ECReg   DCR3            _at_ 0x1805;    // Channel 0 PWM Duty Cycle
ECReg   DCR4            _at_ 0x1806;    // Channel 0 PWM Duty Cycle
ECReg   DCR5            _at_ 0x1807;    // Channel 0 PWM Duty Cycle
ECReg   DCR6            _at_ 0x1808;    // Channel 0 PWM Duty Cycle
ECReg   DCR7            _at_ 0x1809;    // Channel 0 PWM Duty Cycle
ECReg   PWMPOL          _at_ 0x180A;    // PWM Polarity
ECReg   PCFSR           _at_ 0x180B;    // Prescaler Clock Frequency Select
ECReg   PCSSGL          _at_ 0x180C;    // Prescaler Clock Source Select Group Low
ECReg   PCSSGH          _at_ 0x180D;    // Prescaler Clock Source Select Group High
ECReg   CR256PCSSG      _at_ 0x180E;    // CR256 Prescaler Clock Source Select Group
ECReg   PCSGR           _at_ 0x180F;    // Prescaler Clock Source Gating
ECReg   F1TLRR          _at_ 0x181E;    // Fan 1 Tachometer LSB Reading
ECReg   F1TMRR          _at_ 0x181F;    // Fan 1 Tachometer MSB Reading
ECReg   F2TLRR          _at_ 0x1820;    // Fan 2 Tachometer LSB Reading
ECReg   F2TMRR          _at_ 0x1821;    // Fan 2 Tachometer MSB Reading
ECReg   ZINTSCR         _at_ 0x1822;    // Zone Interrupt Status Control
ECReg   ZTIER           _at_ 0x1823;    // PWM Clock Control
ECReg   TSWCTLR         _at_ 0x1824;    // Tachometer Switch Control
ECReg   C4CPRS          _at_ 0x1827;    // Channel 4 Clock Prescaler
ECReg   C4MCPRS         _at_ 0x1828;    // Channel 4 Clock Prescaler MSB
ECReg   C6CPRS          _at_ 0x182B;    // Channel 6 Clock Prescaler
ECReg   C6MCPRS         _at_ 0x182C;    // Channel 6 Clock Prescaler MSB
ECReg   C7CPRS          _at_ 0x182D;    // Channel 7 Clock Prescaler
ECReg   C7MCPRS         _at_ 0x182E;    // Channel 7 Clock Prescaler MSB
ECReg   CLK6MSEL        _at_ 0x1840;    // PWM Clock 6MHz Select
ECReg   CTR1            _at_ 0x1841;    // Cycle Time 1
ECReg   CTR2            _at_ 0x1842;    // Cycle Time 2
ECReg   CTR3            _at_ 0x1843;    // Cycle Time 3
ECReg   PWM5TOCTRL      _at_ 0x1844;    // PWM5 Timeout Control
ECReg   F3TLRR          _at_ 0x1845;    // Fan 3 Tachometer LSB Reading
ECReg   F3TMRR          _at_ 0x1846;    // Fan 3 Tachometer MSB Reading

ECReg   ZINTSCR2        _at_ 0x1847;    // Zone Interrupt Status Control Register 2

ECReg   TSWCTRL         _at_ 0x1848;    // Tachometer Switch Control
ECReg   PWMODENR        _at_ 0x1849;    // PWM Output Open-Drain Enable

ECReg   BLDR            _at_ 0x184C;    // Backlight Duty Register
ECReg   TSWCTLR2        _at_ 0x184F;    // Tachometer Switch Control Register 2
ECReg   PWM0LHE         _at_ 0x1850;    // PWM0 LED DIMMING ENABLE
ECReg   PWM0LCR1        _at_ 0x1851;    // PWM0 LED DIMMING CONTROL 1
ECReg   PWM0LCR2        _at_ 0x1852;    // PWM0 LED DIMMING CONTROL 2
ECReg   PWM1LHE         _at_ 0x1853;    // PWM1 LED DIMMING ENABLE
ECReg   PWM1LCR1        _at_ 0x1854;    // PWM1 LED DIMMING CONTROL 1
ECReg   PWM1LCR2        _at_ 0x1855;    // PWM1 LED DIMMING CONTROL 2
ECReg   PWMLCCR         _at_ 0x185A;    // PWM Load Counter Control
ECReg   CTR1M           _at_ 0x185B;    // Cycle Time Register 1 MSB
ECReg   DCR2M           _at_ 0x185C;    // PWM Duty Cycle Register 2 MSB
ECReg   DCR3M           _at_ 0x185D;    // PWM Duty Cycle Register 3 MSB

//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC)
//-----------------------------------------------------------------------------
ECReg   ADCSTS          _at_ 0x1900;    // ADC Status
ECReg   ADCCFG          _at_ 0x1901;    // ADC Configuration
ECReg   ADCCTL          _at_ 0x1902;    // ADC Clock Control
ECReg   ADCGCR          _at_ 0x1903;    // ADC General Control
ECReg   VCH0CTL         _at_ 0x1904;    // Voltage Channel 0 Channel Control
ECReg   KDCTL           _at_ 0x1905;    // Calibration Data Control
ECReg   VCH1CTL         _at_ 0x1906;    // Voltage Channel 1 Control
ECReg   VCH1DATL        _at_ 0x1907;    // Voltage Channel 1 Data Buffer LSB
ECReg   VCH1DATM        _at_ 0x1908;    // Voltage Channel 1 Data Buffer MSB
ECReg   VCH2CTL         _at_ 0x1909;    // Voltage Channel 2 Control
ECReg   VCH2DATL        _at_ 0x190A;    // Voltage Channel 2 Data Buffer LSB
ECReg   VCH2DATM        _at_ 0x190B;    // Voltage Channel 2 Data Buffer MSB
ECReg   VCH3CTL         _at_ 0x190C;    // Voltage Channel 3 Control
ECReg   VCH3DATL        _at_ 0x190D;    // Voltage Channel 3 Data Buffer LSB
ECReg   VCH3DATM        _at_ 0x190E;    // Voltage Channel 3 Data Buffer MSB
ECReg   VHSCDBL         _at_ 0x1914;    // Voltage High Scale Calibration Data Buffer LSB
ECReg   VHSCDBM         _at_ 0x1915;    // Voltage High Scale Calibration Data Buffer MSB
ECReg   VCH0DATL        _at_ 0x1918;    // Voltage Channel 0 Data Buffer LSB
ECReg   VCH0DATM        _at_ 0x1919;    // Voltage Channel 0 Data Buffer MSB
ECReg   VHSGCDBL        _at_ 0x191C;    // Voltage High Scale Gain-error Calibration Data Buffer LSB
ECReg   VHSGCDBM        _at_ 0x191D;    // Voltage High Scale Gain-error Calibration Data Buffer MSB

ECReg   VCMPSCP         _at_ 0x1937;    // Voltage Compare Scan Period
ECReg   VCH4CTL         _at_ 0x1938;    // Voltage Channel 4 Control
ECReg   VCH4DATM        _at_ 0x1939;    // Volt Channel 4 Data Buffer MSB
ECReg   VCH4DATL        _at_ 0x193A;    // Volt Channel 4 Data Buffer LSB
ECReg   VCH5CTL         _at_ 0x193B;    // Voltage Channel 5 Control
ECReg   VCH5DATM        _at_ 0x193C;    // Volt Channel 5 Data Buffer MSB
ECReg   VCH5DATL        _at_ 0x193D;    // Volt Channel 5 Data Buffer LSB
ECReg   VCH6CTL         _at_ 0x193E;    // Voltage Channel 6 Control
ECReg   VCH6DATM        _at_ 0x193F;    // Volt Channel 6 Data Buffer MSB
ECReg   VCH6DATL        _at_ 0x1940;    // Volt Channel 6 Data Buffer LSB
ECReg   VCH7CTL         _at_ 0x1941;    // Voltage Channel 7 Control
ECReg   VCH7DATM        _at_ 0x1942;    // Volt Channel 7 Data Buffer MSB
ECReg   VCH7DATL        _at_ 0x1943;    // Volt Channel 7 Data Buffer LSB
ECReg   ADCDVSTS        _at_ 0x1944;    // ADC Data Vaild Status
ECReg   VCMPSTS         _at_ 0x1945;    // Voltage Compare Status
ECReg   VCMP0CTL        _at_ 0x1946;    // Voltage Compare Channel 0 Control
ECReg   VCMP0THRDATM    _at_ 0x1947;    // Voltage Compare 0 Threshold Data Buffer MSB
ECReg   VCMP0THRDATL    _at_ 0x1948;    // Voltage Compare 0 Threshold Data Buffer LSB
ECReg   VCMP1CTL        _at_ 0x1949;    // Voltage Compare Channel 1 Control
ECReg   VCMP1THRDATM    _at_ 0x194A;    // Voltage Compare 1 Threshold Data Buffer MSB
ECReg   VCMP1THRDATL    _at_ 0x194B;    // Voltage Compare 1 Threshold Data Buffer LSB
ECReg   VCMP2CTL        _at_ 0x194C;    // Voltage Compare Channel 2 Control
ECReg   VCMP2THRDATM    _at_ 0x194D;    // Voltage Compare 2 Threshold Data Buffer MSB
ECReg   VCMP2THRDATL    _at_ 0x194E;    // Voltage Compare 2 Threshold Data Buffer LSB
ECReg   VCMPOTR         _at_ 0x194F;    // Voltage Comparator Output Type
ECReg   VCMP0HYDATM     _at_ 0x1950;    // Voltage Comparator 0 Hysteresis Data Buffer MSB
ECReg   VCMP0HYDATL     _at_ 0x1951;    // Voltage Comparator 0 Hysteresis Data Buffer LSB
ECReg   VCMPLR          _at_ 0x1952;    // Voltage Comparator Lock
ECReg   ADCIVMFSCS1     _at_ 0x1955;    // ADC Input Voltage Mapping Full-Scale Code Selection 1
ECReg   ADCIVMFSCS2     _at_ 0x1956;    // ADC Input Voltage Mapping Full-Scale Code Selection 2

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC)
//-----------------------------------------------------------------------------
ECReg   DACPDREG        _at_ 0x1A01;    // DAC Power Down
ECReg   DACDAT0         _at_ 0x1A02;    // DAC Data Channel 0 (IT8991E/IT557X None)
ECReg   DACDAT1         _at_ 0x1A03;    // DAC Data Channel 1 (IT8991E/IT557X None)
ECReg   DACDAT2         _at_ 0x1A04;    // DAC Data Channel 2
ECReg   DACDAT3         _at_ 0x1A05;    // DAC Data Channel 3
ECReg   DACDAT4         _at_ 0x1A06;    // DAC Data Channel 4
ECReg   DACDAT5         _at_ 0x1A07;    // DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC)
//-----------------------------------------------------------------------------
ECReg   WUEMR1          _at_ 0x1B00;    // Wake-Up Edge Mode 1
ECReg   WUEMR2          _at_ 0x1B01;    // Wake-Up Edge Mode 2
ECReg   WUEMR3          _at_ 0x1B02;    // Wake-Up Edge Mode 3
ECReg   WUEMR4          _at_ 0x1B03;    // Wake-Up Edge Mode 4
ECReg   WUEMR6          _at_ 0x1B10;    // Wake-Up Edge Mode 6
ECReg   WUEMR7          _at_ 0x1B14;    // Wake-Up Edge Mode 7
ECReg   WUEMR8          _at_ 0x1B18;    // Wake-Up Edge Mode 8
ECReg   WUEMR9          _at_ 0x1B1C;    // Wake-Up Edge Mode 9
ECReg   WUEMR10         _at_ 0x1B20;    // Wake-Up Edge Mode 10
ECReg   WUEMR11         _at_ 0x1B24;    // Wake-Up Edge Mode 11
ECReg   WUEMR12         _at_ 0x1B28;    // Wake-Up Edge Mode 12
ECReg   WUEMR13         _at_ 0x1B2C;    // Wake-Up Edge Mode 13
ECReg   WUEMR14         _at_ 0x1B30;    // Wake-Up Edge Mode 14

ECReg   WUESR1          _at_ 0x1B04;    // Wake-Up Edge Sense 1
ECReg   WUESR2          _at_ 0x1B05;    // Wake-Up Edge Sense 2
ECReg   WUESR3          _at_ 0x1B06;    // Wake-Up Edge Sense 3
ECReg   WUESR4          _at_ 0x1B07;    // Wake-Up Edge Sense 4
ECReg   WUESR6          _at_ 0x1B11;    // Wake-Up Edge Sense 6
ECReg   WUESR7          _at_ 0x1B15;    // Wake-Up Edge Sense 7
ECReg   WUESR8          _at_ 0x1B19;    // Wake-Up Edge Sense 8
ECReg   WUESR9          _at_ 0x1B1D;    // Wake-Up Edge Sense 9
ECReg   WUESR10         _at_ 0x1B21;    // Wake-Up Edge Sense 10
ECReg   WUESR11         _at_ 0x1B25;    // Wake-Up Edge Sense 11
ECReg   WUESR12         _at_ 0x1B29;    // Wake-Up Edge Sense 12
ECReg   WUESR13         _at_ 0x1B2D;    // Wake-Up Edge Sense 13
ECReg   WUESR14         _at_ 0x1B31;    // Wake-Up Edge Sense 14

ECReg   WUENR1          _at_ 0x1B08;    // Wake-Up Enable 1
ECReg   WUENR2          _at_ 0x1B09;    // Wake-Up Enable 2
ECReg   WUENR3          _at_ 0x1B0A;    // Wake-Up Enable 3
ECReg   WUENR4          _at_ 0x1B0B;    // Wake-Up Enable 4
ECReg   WUENR6          _at_ 0x1B12;    // Wake-Up Enable 6
ECReg   WUENR7          _at_ 0x1B16;    // Wake-Up Enable 7
ECReg   WUENR8          _at_ 0x1B1A;    // Wake-Up Enable 8
ECReg   WUENR9          _at_ 0x1B1E;    // Wake-Up Enable 9

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB)
//-----------------------------------------------------------------------------
ECReg   HOSTA_A         _at_ 0x1C00;    // Host Status A
ECReg   HOSTA_B         _at_ 0x1C11;    // Host Status B
ECReg   HOSTA_C         _at_ 0x1C29;    // Host Status C
ECReg   HOSTA_D         _at_ 0x1C35;    // Host Status D
ECReg   HOSTA_E         _at_ 0x1CA0;    // Host Status E
ECReg   HOSTA_F         _at_ 0x1CB0;    // Host Status F

ECReg   HOCTL_A         _at_ 0x1C01;    // Host Control A
ECReg   HOCTL_B         _at_ 0x1C12;    // Host Control B
ECReg   HOCTL_C         _at_ 0x1C2A;    // Host Control C
ECReg   HOCTL_D         _at_ 0x1C36;    // Host Control D
ECReg   HOCTL_E         _at_ 0x1CA1;    // Host Control E
ECReg   HOCTL_F         _at_ 0x1CB1;    // Host Control F

ECReg   HOCMD_A         _at_ 0x1C02;    // Host Command A
ECReg   HOCMD_B         _at_ 0x1C13;    // Host Command B
ECReg   HOCMD_C         _at_ 0x1C2B;    // Host Command C
ECReg   HOCMD_D         _at_ 0x1C37;    // Host Command D
ECReg   HOCMD_E         _at_ 0x1CA2;    // Host Command E
ECReg   HOCMD_F         _at_ 0x1CB2;    // Host Command F

ECReg   TRASLA_A        _at_ 0x1C03;    // Transmit Slave Address A
ECReg   TRASLA_B        _at_ 0x1C14;    // Transmit Slave Address B
ECReg   TRASLA_C        _at_ 0x1C2C;    // Transmit Slave Address C
ECReg   TRASLA_D        _at_ 0x1C38;    // Transmit Slave Address D
ECReg   TRASLA_E        _at_ 0x1CA3;    // Transmit Slave Address E
ECReg   TRASLA_F        _at_ 0x1CB3;    // Transmit Slave Address F

ECReg   D0REG_A         _at_ 0x1C04;    // Host Data 0 A
ECReg   D0REG_B         _at_ 0x1C15;    // Host Data 0 B
ECReg   D0REG_C         _at_ 0x1C2D;    // Host Data 0 C
ECReg   D0REG_D         _at_ 0x1C39;    // Host Data 0 D
ECReg   D0REG_E         _at_ 0x1CA4;    // Host Data 0 E
ECReg   D0REG_F         _at_ 0x1CB4;    // Host Data 0 F

ECReg   D1REG_A         _at_ 0x1C05;    // Host Data 1 A
ECReg   D1REG_B         _at_ 0x1C16;    // Host Data 1 B
ECReg   D1REG_C         _at_ 0x1C2E;    // Host Data 1 C
ECReg   D1REG_D         _at_ 0x1C3A;    // Host Data 1 D
ECReg   D1REG_E         _at_ 0x1CA6;    // Host Data 1 E
ECReg   D1REG_F         _at_ 0x1CB6;    // Host Data 1 F

ECReg   HOBDB_A         _at_ 0x1C06;    // Host Block Data Byte A
ECReg   HOBDB_B         _at_ 0x1C17;    // Host Block Data Byte B
ECReg   HOBDB_C         _at_ 0x1C2F;    // Host Block Data Byte C
ECReg   HOBDB_D         _at_ 0x1C3B;    // Host Block Data Byte D
ECReg   HOBDB_E         _at_ 0x1CA7;    // Host Block Data Byte E
ECReg   HOBDB_F         _at_ 0x1CB7;    // Host Block Data Byte F

ECReg   PECERC_A        _at_ 0x1C07;    // Packet Error Check A
ECReg   PECERC_B        _at_ 0x1C18;    // Packet Error Check B
ECReg   PECERC_C        _at_ 0x1C30;    // Packet Error Check C
ECReg   PECERC_D        _at_ 0x1C3C;    // Packet Error Check D
ECReg   PECERC_E        _at_ 0x1CA8;    // Packet Error Check E
ECReg   PECERC_F        _at_ 0x1CB8;    // Packet Error Check F

ECReg   RESLADR_A       _at_ 0x1C08;    // Receive Slave Address A
ECReg   RESLADR_B       _at_ 0x1C19;    // Receive Slave Address B
ECReg   RESLADR_C       _at_ 0x1C5A;    // Receive Slave Address C

ECReg   RESLADR2_A      _at_ 0x1C3F;    // Receive Slave Address_2 A
ECReg   RESLADR2_B      _at_ 0x1C44;    // Receive Slave Address_2 B
ECReg   RESLADR2_C      _at_ 0x1C54;    // Receive Slave Address_2 C

ECReg   SLDA_A          _at_ 0x1C09;    // Slave Data A
ECReg   SLDA_B          _at_ 0x1C1A;    // Slave Data B
ECReg   SLDA_C          _at_ 0x1C5B;    // Slave Data C

ECReg   SMBPCTL_A       _at_ 0x1C0A;    // SMBUS Pin Control A
ECReg   SMBPCTL_B       _at_ 0x1C1B;    // SMBUS Pin Control B
ECReg   SMBPCTL_C       _at_ 0x1C31;    // SMBUS Pin Control C
ECReg   SMBPCTL_D       _at_ 0x1C3D;    // SMBUS Pin Control D
ECReg   SMBPCTL_E       _at_ 0x1CA9;    // SMBUS Pin Control E
ECReg   SMBPCTL_F       _at_ 0x1CB9;    // SMBUS Pin Control F

ECReg   SLSTA_A         _at_ 0x1C0B;    // Slave Status A
ECReg   SLSTA_B         _at_ 0x1C1C;    // Slave Status B
ECReg   SLSTA_C         _at_ 0x1C52;    // Slave Status C

ECReg   SICR_A          _at_ 0x1C0C;    // Slave Interrupt Control A
ECReg   SICR_B          _at_ 0x1C1D;    // Slave Interrupt Control B
ECReg   SICR_C          _at_ 0x1C53;    // Slave Interrupt Control C

ECReg   NDADR_A         _at_ 0x1C0D;    // Notify Device Address A
ECReg   NDADR_B         _at_ 0x1C1E;    // Notify Device Address B
ECReg   NDADR_C         _at_ 0x1C55;    // Notify Device Address C

ECReg   NDLB_A          _at_ 0x1C0E;    // Notify Data Low Byte A
ECReg   NDLB_B          _at_ 0x1C1F;    // Notify Data Low Byte B
ECReg   NDLB_C          _at_ 0x1C56;    // Notify Data Low Byte C

ECReg   NDHB_A          _at_ 0x1C0F;    // Notify Data High Byte A
ECReg   NDHB_B          _at_ 0x1C20;    // Notify Data High Byte B
ECReg   NDHB_C          _at_ 0x1C57;    // Notify Data High Byte C

ECReg   HOCTL2_A        _at_ 0x1C10;    // Host Control2 A
ECReg   HOCTL2_B        _at_ 0x1C21;    // Host Control2 B
ECReg   HOCTL2_C        _at_ 0x1C32;    // Host Control2 C
ECReg   HOCTL2_D        _at_ 0x1C3E;    // Host Control2 D
ECReg   HOCTL2_E        _at_ 0x1CAA;    // Host Control2 E
ECReg   HOCTL2_F        _at_ 0x1CBA;    // Host Control2 F

ECReg   SMB4P7USL       _at_ 0x1C22;    // 4.7 £gs Low
ECReg   SMB4P0USH       _at_ 0x1C23;    // 4.7 £gs High
ECReg   SMB300NS        _at_ 0x1C24;    // 300 ns
ECReg   SMB250NS        _at_ 0x1C25;    // 250 ns
ECReg   SMB25MS         _at_ 0x1C26;    // 25 ms
ECReg   SMB45P3USL      _at_ 0x1C27;    // 45.3 £gs Low
ECReg   SMBS4P3USH      _at_ 0x1C28;    // 45.3 £gs High
ECReg   SMB4P7A4P0H     _at_ 0x1C33;    // 4.7 £gs and 4.0 £gs High

ECReg   SLVISELR        _at_ 0x1C34;    // Slave Interface Select
ECReg   SCLKTS_A        _at_ 0x1C40;    // SMCLK Timing Setting   A
ECReg   SCLKTS_B        _at_ 0x1C41;    // SMCLK Timing Setting   B
ECReg   SCLKTS_C        _at_ 0x1C42;    // SMCLK Timing Setting   C
ECReg   SCLKTS_D        _at_ 0x1C43;    // SMCLK Timing Setting   D

ECReg   SMBMSTFCTRL1    _at_ 0x1C45;    // SMBus FIFO Control 1
ECReg   SMBMSTFSTS1     _at_ 0x1C46;    // SMBus FIFO Status 1
ECReg   SMBMSTFCTRL2    _at_ 0x1C47;    // SMBus FIFO Control 2
ECReg   SMBMSTFSTS2     _at_ 0x1C48;    // SMBus FIFO Status 2

ECReg   HONACKSRC_A     _at_ 0x1C49;    // HOST NACK Source A
ECReg   HONACKSRC_B     _at_ 0x1C4A;    // HOST NACK Source B
ECReg   HONACKSRC_C     _at_ 0x1C4B;    // HOST NACK Source C
ECReg   HONACKSRC_D     _at_ 0x1C4C;    // HOST NACK Source D
ECReg   HONACKSRC_E     _at_ 0x1CAC;    // HOST NACK Source E
ECReg   HONACKSRC_F     _at_ 0x1CBC;    // HOST NACK Source F

ECReg   SLVFTH          _at_ 0x1C4D;    // Slave FIFO Threshold
ECReg   DFTSDFSEL       _at_ 0x1C4E;    // DMA from Flash to SMB Dedicated FIFO Selection
ECReg   MSTHTH          _at_ 0x1C4F;    // Master FIFO Threshold
ECReg   MFTHEN          _at_ 0x1C50;    // Master FIFO Threshold Enable
ECReg   MFTISTA         _at_ 0x1C51;    // Master FIFO Threshold Interrupt Status
ECReg   SFTHEN          _at_ 0x1C58;    // Slave FIFO Threshold Enable
ECReg   SFTISTA         _at_ 0x1C59;    // Slave FIFO Threshold Interrupt Status
ECReg   SADFPCTL        _at_ 0x1C5E;    // Slave FIFO Control
ECReg   SFFSTA          _at_ 0x1C5F;    // Slave FIFO Status
ECReg   SDSIC           _at_ 0x1C60;    // SMBus Design Switch Interface Control
ECReg   SDSIC2          _at_ 0x1C61;    // SMBus Design Switch Interface Control 2
ECReg   SBDFPCTL        _at_ 0x1C62;    // Slave B Dedicated FIFO Pre-defined Control Register
ECReg   SBDFFSTA        _at_ 0x1C63;    // Slave B Dedicated FIFO Status
ECReg   SCDFFCTL        _at_ 0x1C64;    // Slave C Dedicated FIFO Control Register
ECReg   SCDFFSTA        _at_ 0x1C65;    // Slave C Dedicated FIFO Status

ECReg   I2CW2RF         _at_ 0x1C69;    // I2C Wr to Rd FIFO
ECReg   IWRFISTA        _at_ 0x1C6A;    // I2C Wr to Rd FIFO Interrupt Status

ECReg   SFFE            _at_ 0x1C6F;    // Shared FIFO Function Enable
ECReg   SISPC           _at_ 0x1C73;    // SMBus Interface Switch Pin control
ECReg   MSFSS           _at_ 0x1C76;    // Master Shared FIFO Size Select
ECReg   SSFSS1          _at_ 0x1C77;    // Slave Shared FIFO Size Select 1
ECReg   SFBAMA          _at_ 0x1C78;    // Shared FIFO Base Address for Master A
ECReg   SFBAMBCD        _at_ 0x1C7E;    // Shared FIFO Base Address for Master BCD
ECReg   SFBASA          _at_ 0x1C80;    // Shared FIFO Base Address for Slave A
ECReg   SFBASB          _at_ 0x1C82;    // Shared FIFO Base Address for Slave B
ECReg   SFBASC          _at_ 0x1C84;    // Shared FIFO Base Address for Slave C
ECReg   SSFSS2          _at_ 0x1C87;    // Slave Shared FIFO Size Select 2
ECReg   HWPEC           _at_ 0x1C88;    // Hardwired PEC Register
ECReg   HWPES           _at_ 0x1C89;    // Hardwired PEC Error Status
ECReg   SLVTPECC        _at_ 0x1C8A;    // Slave Transaction PEC Control

ECReg   SHWPECV_A       _at_ 0x1C8B;    // Slave Hardwired PEC VALUE A
ECReg   SHWPECV_B       _at_ 0x1C8C;    // Slave Hardwired PEC VALUE B
ECReg   SHWPECV_C       _at_ 0x1C8D;    // Slave Hardwired PEC VALUE C

ECReg   BTOIER          _at_ 0x1C8E;    // Bridge Timeout Interrupt Enabled
ECReg   ISFBCH_A        _at_ 0x1C90;    // I2C Shared FIFO Byte Count H A
ECReg   ISFBCH_B        _at_ 0x1C91;    // I2C Shared FIFO Byte Count H B
ECReg   ISFBCH_C        _at_ 0x1C92;    // I2C Shared FIFO Byte Count H C
ECReg   ISFBCH_D        _at_ 0x1C93;    // I2C Shared FIFO Byte Count H D
ECReg   ISFBCH_E        _at_ 0x1CA5;    // I2C Shared FIFO Byte Count H E
ECReg   ISFBCH_F        _at_ 0x1CB5;    // I2C Shared FIFO Byte Count H F

ECReg   SDSIC3          _at_ 0x1C99;    //SMBus Design Switch Interface Control 3
ECReg   MFTHEN2         _at_ 0x1C9C;    //Master Dedicated FIFO Threshold Enable 2
ECReg   MFTISTA2        _at_ 0x1C9D;    //Master Dedicated FIFO Threshold Interrupt Status 2
ECReg   HWPEC2          _at_ 0x1C9E;    //Hardwired PEC Register 2
ECReg   HWPES2          _at_ 0x1C9F;    //Hardwired PEC Error Status 2
ECReg   SCLKTS_E        _at_ 0x1CAB;    //SMCLK Timing Setting Register E
ECReg   SCLKTS_F        _at_ 0x1CBB;    //SMCLK Timing Setting Register F

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS)
//-----------------------------------------------------------------------------
ECReg   KSOL            _at_ 0x1D00;    // Keyboard Scan Out
ECReg   KSOH1           _at_ 0x1D01;    // Keyboard Scan Out
ECReg   KSOCTRL         _at_ 0x1D02;    // Keyboard Scan Out Control
ECReg   KSOH2           _at_ 0x1D03;    // Keyboard Scan Out
ECReg   KSI             _at_ 0x1D04;    // Keyboard Scan In
ECReg   KSICTRL         _at_ 0x1D05;    // Keyboard Scan In Control
ECReg   KSIGCTRLR       _at_ 0x1D06;    // Keyboard Scan In [7:0] GPIO Control
ECReg   KSIGOENR        _at_ 0x1D07;    // Keyboard Scan In [7:0] GPIO Output Enable
ECReg   KSIGDATR        _at_ 0x1D08;    // Keyboard Scan In [7:0] GPIO DATA
ECReg   KSIGDMRRR       _at_ 0x1D09;    // Keyboard Scan In [7:0] GPIO DATA Mirror
ECReg   KSOHGCTRLR      _at_ 0x1D0A;    // Keyboard Scan Out [15:8] GPIO Control
ECReg   KSOHGOENR       _at_ 0x1D0B;    // Keyboard Scan Out [15:8] GPIO Output Enable
ECReg   KSOHGDMRRR      _at_ 0x1D0C;    // Keyboard Scan Out [15:8] GPIO DATA Mirror
ECReg   KSOLGCTRLR      _at_ 0x1D0D;    // Keyboard Scan Out [7:0] GPIO Control
ECReg   KSOLGOENR       _at_ 0x1D0E;    // Keyboard Scan Out [7:0] GPIO Output Enable
ECReg   KSOLGDMRRR      _at_ 0x1D0F;    // Keyboard Scan Out [7:0] GPIO DATA Mirror
ECReg   KSO0LSDR        _at_ 0x1D10;    // KSO 0 Low Scan Data
ECReg   KSO1LSDR        _at_ 0x1D11;    // KSO 1 Low Scan Data
ECReg   KSO2LSDR        _at_ 0x1D12;    // KSO 2 Low Scan Data
ECReg   KSO3LSDR        _at_ 0x1D13;    // KSO 3 Low Scan Data
ECReg   KSO4LSDR        _at_ 0x1D14;    // KSO 4 Low Scan Data
ECReg   KSO5LSDR        _at_ 0x1D15;    // KSO 5 Low Scan Data
ECReg   KSO6LSDR        _at_ 0x1D16;    // KSO 6 Low Scan Data
ECReg   KSO7LSDR        _at_ 0x1D17;    // KSO 7 Low Scan Data
ECReg   KSO8LSDR        _at_ 0x1D18;    // KSO 8 Low Scan Data
ECReg   KSO9LSDR        _at_ 0x1D19;    // KSO 9 Low Scan Data
ECReg   KSO10LSDR       _at_ 0x1D1A;    // KSO 10 Low Scan Data
ECReg   KSO11LSDR       _at_ 0x1D1B;    // KSO 11 Low Scan Data
ECReg   KSO12LSDR       _at_ 0x1D1C;    // KSO 12 Low Scan Data
ECReg   KSO13LSDR       _at_ 0x1D1D;    // KSO 13 Low Scan Data
ECReg   KSO14LSDR       _at_ 0x1D1E;    // KSO 14 Low Scan Data
ECReg   KSO15LSDR       _at_ 0x1D1F;    // KSO 15 Low Scan Data
ECReg   KSO16LSDR       _at_ 0x1D20;    // KSO 16 Low Scan Data
ECReg   KSO17LSDR       _at_ 0x1D21;    // KSO 17 Low Scan Data
ECReg   SDC1R           _at_ 0x1D22;    // Scan Data Control 1
ECReg   SDC2R           _at_ 0x1D23;    // Scan Data Control 2
ECReg   SDC3R           _at_ 0x1D24;    // Scan Data Control 3
ECReg   SDSR            _at_ 0x1D25;    // Scan Data Control 4

ECReg   KSIGPODR        _at_ 0x1D26;    // Keyboard Scan In [7:0] GPIO Open-Drain Register
ECReg   KSOHGPODR       _at_ 0x1D27;    // Keyboard Scan Out [15:8] GPIO Open-Drain Register
ECReg   KSOLGPODR       _at_ 0x1D28;    // Keyboard Scan Out [7:0] GPIO Open-Drain Register

//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM)
//-----------------------------------------------------------------------------
ECReg   CGCTRL1R        _at_ 0x1E01;    // Clock Gating Control 1
ECReg   CGCTRL2R        _at_ 0x1E02;    // Clock Gating Control 2
ECReg   CGCTRL3R        _at_ 0x1E05;    // Clock Gating Control 3
ECReg   PLLCTRL         _at_ 0x1E03;    // PLL Control
ECReg   AUTOCG          _at_ 0x1E04;    // Auto Clock Gating
ECReg   PLLFREQR        _at_ 0x1E06;    // PLL Frequency
ECReg   PLLSSCR         _at_ 0x1E07;    // PLL Frequency
ECReg   PLLCSS          _at_ 0x1E08;    // PLL Clock Source Status
ECReg   CGCTRL4R        _at_ 0x1E09;    // Clock Gating Control 4

//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD)
//-----------------------------------------------------------------------------
ECReg   ETWCFG          _at_ 0x1F01;    // External Timer/WDT Configuration
ECReg   ET1PSR          _at_ 0x1F02;    // External Timer Prescaler
ECReg   ET1CNTLHR       _at_ 0x1F03;    // External Timer Counter High Byte
ECReg   ET1CNTLLR       _at_ 0x1F04;    // External Timer Counter Low Byte
ECReg   ETWCTRL         _at_ 0x1F05;    // External Timer/WDT Control
ECReg   EWDCNTLLR       _at_ 0x1F06;    // External WDT Counter Low Byte
ECReg   EWDKEYR         _at_ 0x1F07;    // External WDT Key
ECReg   EWDCNTLHR       _at_ 0x1F09;    // External WDT Counter High Byte

ECReg   ET2PSR          _at_ 0x1F0A;    // External Timer 2 Prescaler
ECReg   ET2CNTLHR       _at_ 0x1F0B;    // External Timer 2 Counter High Byte
ECReg   ET2CNTLLR       _at_ 0x1F0C;    // External Timer 2 Counter Low Byte
ECReg   ET2CNTLH2R      _at_ 0x1F0E;    // External Timer 2 Counter High Byte 2

ECReg   ET3PSR          _at_ 0x1F10;    // External Timer 3 Prescaler
ECReg   ET3CNTLHR       _at_ 0x1F11;    // External Timer 3 Counter High Byte
ECReg   ET3CNTLLR       _at_ 0x1F12;    // External Timer 3 Counter Low Byte
ECReg   ET3CNTLH2R      _at_ 0x1F13;    // External Timer 3 Counter High Byte 2

ECReg   ET4CNTLLR       _at_ 0x1F16;    // External Timer 4 Counter Low Byte

//-----------------------------------------------------------------------------
// General Control (GCTRL) (20xxh)
//-----------------------------------------------------------------------------
ECReg   ECHIPID1        _at_ 0x2000;    // Chip ID Byte 1
ECReg   ECHIPID2        _at_ 0x2001;    // Chip ID Byte 2
ECReg   ECHIPVER        _at_ 0x2002;    // Chip Version
ECReg   IDR             _at_ 0x2004;    // Identify Input
ECReg   RSTS            _at_ 0x2006;    // Reset Status
ECReg   RSTC1           _at_ 0x2007;    // Reset Control 1
ECReg   RSTC2           _at_ 0x2008;    // Reset Control 2
ECReg   RSTC3           _at_ 0x2009;    // Reset Control 3
ECReg   RSTC4           _at_ 0x2011;    // Reset Control 4
ECReg   RSTC6           _at_ 0x2029;    // Reset Control 6

ECReg   RSTDMMC         _at_ 0x2010;    // Reset Control DMMC
ECReg   BADRSEL         _at_ 0x200A;    // Base Address Select
ECReg   WNCKR           _at_ 0x200B;    // Wait Next Clock Rising
ECReg   SPCTRL5         _at_ 0x200C;    // Special Control 5
ECReg   SPCTRL1         _at_ 0x200D;    // Special Control 1
ECReg   RSTCH           _at_ 0x200E;    // Reset Control Host Side
ECReg   GENIRQ          _at_ 0x200F;    // Generate IRQ
ECReg   SPCTRL2         _at_ 0x2012;    // Special Control 2
ECReg   SPCTRL3         _at_ 0x2016;    // Special Control 3

ECReg   PI2ECH          _at_ 0x2014;    // Port I2EC High-Byte
ECReg   PI2ECL          _at_ 0x2015;    // Port I2EC Low-Byte
ECReg   BINTADDR0R      _at_ 0x2019;    // BRAM Interrupt Address 0
ECReg   BINTADDR1R      _at_ 0x201A;    // BRAM Interrupt Address 1
ECReg   BINTCTRLR       _at_ 0x201B;    // BRAM Interrupt Control
ECReg   SPCTRL4         _at_ 0x201C;    // Special Control 4
ECReg   REG_201D        _at_ 0x201D;

ECReg   SHA1HASHCTRLR   _at_ 0x202D;    // SHA1 Hash Control
ECReg   SHA1HBADDR      _at_ 0x202E;    // SHA1 Hash Base Address
ECReg   P80H81HSR       _at_ 0x2030;    // Port 80h/81h Status Register
ECReg   P80HDR          _at_ 0x2031;    // Port 80h Data Register
ECReg   P81HDR          _at_ 0x2032;    // Port 81h Data Register

//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC)
//-----------------------------------------------------------------------------
ECReg   EADDR           _at_ 0x2100;    // External GPIO Address
ECReg   EDAT            _at_ 0x2101;    // External GPIO Data
ECReg   ECNT            _at_ 0x2102;    // External GPIO Control
ECReg   ESTS            _at_ 0x2103;    // External GPIO Status

ECReg   EARCR           _at_ 0x2104;    // External GPIO Auto Read Control
ECReg   ERE1R           _at_ 0x2105;    // External GPIO Read Enable 1
ECReg   ERE2R           _at_ 0x2106;    // External GPIO Read Enable 2
ECReg   ERE3R           _at_ 0x2107;    // External GPIO Read Enable 3
ECReg   ERE4R           _at_ 0x2108;    // External GPIO Read Enable 4
ECReg   ERE5R           _at_ 0x2109;    // External GPIO Read Enable 5
ECReg   ESVR            _at_ 0x210A;    // External GPIO Status Vector
ECReg   ESCF1R          _at_ 0x2110;    // External GPIO Status Change Flag 1
ECReg   ESCF2R          _at_ 0x2111;    // External GPIO Status Change Flag 2
ECReg   ESCF3R          _at_ 0x2112;    // External GPIO Status Change Flag 3
ECReg   ESCF4R          _at_ 0x2113;    // External GPIO Status Change Flag 4
ECReg   ESCF5R          _at_ 0x2114;    // External GPIO Status Change Flag 5

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM)
//-----------------------------------------------------------------------------
ECReg   BRAM2[128]      _at_ 0x2200;    // 128 bytes ITE BRAM
ECReg   BRAM[64]        _at_ 0x2280;    // 64 bytes ITE BRAM

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR)
//-----------------------------------------------------------------------------
ECReg   C0DR            _at_ 0x2300;    // CIR Data
ECReg   C0MSTCR         _at_ 0x2301;    // CIR Master Control
ECReg   C0IER           _at_ 0x2302;    // CIR Interrupt Enable
ECReg   C0IIR           _at_ 0x2303;    // CIR Interrupt Identification
ECReg   C0CFR           _at_ 0x2304;    // CIR Carrier Frequency
ECReg   C0RCR           _at_ 0x2305;    // CIR Receive Control
ECReg   C0TCR           _at_ 0x2306;    // CIR Transmitter
ECReg   C0SCK           _at_ 0x2307;    // CIR for sleep mode
ECReg   C0BDLR          _at_ 0x2308;    // CIR Baud Rate Divisor Low Byte
ECReg   C0BDHR          _at_ 0x2309;    // CIR Baud Rate Divisor High Byte
ECReg   C0TFSR          _at_ 0x230A;    // CIR Transmitter FIFO Status
ECReg   C0RFSR          _at_ 0x230B;    // CIR Receiver FIFO Status
ECReg   C0WCSSR         _at_ 0x230C;    // CIR Wakeup Code Set Select
ECReg   C0WCL           _at_ 0x230D;    // CIR Wakeup Code Length
ECReg   C0WCR           _at_ 0x230E;    // CIR Wakeup Code Read/Write
ECReg   C0WPS           _at_ 0x230F;    // CIR Wakeup Code Power Control/Status
ECReg   CSCRR           _at_ 0x2310;    // CIR Scratch

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR)
//-----------------------------------------------------------------------------
ECReg   BKA1L           _at_ 0x2510;    // Trigger 1 Address Low Byte
ECReg   BKA1M           _at_ 0x2511;    // Trigger 1 Address Middle Byte
ECReg   BKA1H           _at_ 0x2512;    // Trigger 1 Address High Byte
ECReg   BKA2L           _at_ 0x2513;    // Trigger 2 Address Low Byte
ECReg   BKA2M           _at_ 0x2514;    // Trigger 2 Address Middle Byte
ECReg   BKA2H           _at_ 0x2515;    // Trigger 2 Address High Byte
ECReg   BKA3L           _at_ 0x2516;    // Trigger 3 Address Low Byte
ECReg   BKA3M           _at_ 0x2517;    // Trigger 3 Address Middle Byte
ECReg   BKA3H           _at_ 0x2518;    // Trigger 3 Address High Byte

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI)
//-----------------------------------------------------------------------------
ECReg   SPIDATA         _at_ 0x2600;    // SPI Data
ECReg   SPICTRL1        _at_ 0x2601;    // SPI Control 1
ECReg   SPICTRL2        _at_ 0x2602;    // SPI Control 2
ECReg   SPISTS          _at_ 0x2603;    // SPI Status
ECReg   SPICTRL3        _at_ 0x2604;    // SPI Control 3

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1)
//-----------------------------------------------------------------------------
ECReg   UART1_RBR       _at_ 0x2700;    // Receiver Buffer
ECReg   UART1_IER       _at_ 0x2701;    // Interrupt Enable
ECReg   UART1_IIR       _at_ 0x2702;    // Interrupt Identification
ECReg   UART1_LCR       _at_ 0x2703;    // Line Control
ECReg   UART1_MCR       _at_ 0x2704;    // Modem Control
ECReg   UART1_LSR       _at_ 0x2705;    // Line Status
ECReg   UART1_MSR       _at_ 0x2706;    // Modem Status
ECReg   UART1_SCR       _at_ 0x2707;    // Scratch Pad
ECReg   UART1_ECSPMR    _at_ 0x2708;    // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2)
//-----------------------------------------------------------------------------
ECReg   UART2_RBR       _at_ 0x2800;    // Receiver Buffer
ECReg   UART2_IER       _at_ 0x2801;    // Interrupt Enable
ECReg   UART2_IIR       _at_ 0x2802;    // Interrupt Identification
ECReg   UART2_LCR       _at_ 0x2803;    // Line Control
ECReg   UART2_MCR       _at_ 0x2804;    // Modem Control
ECReg   UART2_LSR       _at_ 0x2805;    // Line Status
ECReg   UART2_MSR       _at_ 0x2806;    // Modem Status
ECReg   UART2_SCR       _at_ 0x2807;    // Scratch Pad
ECReg   UART2_ECSPMR    _at_ 0x2808;    // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
ECReg   PRSC            _at_ 0x2900;    // TMR Prescaler
ECReg   GCSMS           _at_ 0x2901;    // Group Clock Source and Mode Select
ECReg   CTR_A0          _at_ 0x2902;    // A0 Cycle Time
ECReg   CTR_A1          _at_ 0x2903;    // A1 Cycle Time
ECReg   CTR_B0          _at_ 0x2904;    // B0 Cycle Time
ECReg   CTR_B1          _at_ 0x2905;    // B1 Cycle Time
ECReg   DCR_A0          _at_ 0x2906;    // A0 Duty Time
ECReg   DCR_A1          _at_ 0x2907;    // A1 Duty Time
ECReg   DCR_B0          _at_ 0x2908;    // B0 Duty Time
ECReg   DCR_B1          _at_ 0x2909;    // B1 Duty Time
ECReg   CCGSR           _at_ 0x290A;    // Channel Clock Group Select
ECReg   TMRCE           _at_ 0x290B;    // TMR Clock Enable
ECReg   TMEIE           _at_ 0x290C;    // TMR Interrupt Enable

//-----------------------------------------------------------------------------
// (2Exxh) Consumer Electronics Control (CEC)
//-----------------------------------------------------------------------------
ECReg   CECDR           _at_ 0x2E00;    // CEC Data
ECReg   CECFSTS         _at_ 0x2E01;    // CEC FIFO Status
ECReg   CECDLA          _at_ 0x2E02;    // CEC Device Logical Address
ECReg   CECCTRL         _at_ 0x2E03;    // CEC Control
ECReg   CECSTS          _at_ 0x2E04;    // CEC Status
ECReg   CECIE           _at_ 0x2E05;    // CEC Interrupt Enable
ECReg   CECOPSTS        _at_ 0x2E06;    // CEC Operation Status
ECReg   CECCRH          _at_ 0x2E07;    // CEC Received Header

//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
ECReg   HOSTAR          _at_ 0x3000;    // Host Status
ECReg   HOCTLR          _at_ 0x3001;    // Host Control
ECReg   HOCMDR          _at_ 0x3002;    // Host Command
ECReg   HOTRADDR        _at_ 0x3003;    // Host Target Address
ECReg   HOWRLR          _at_ 0x3004;    // Host Write Length
ECReg   HORDLR          _at_ 0x3005;    // Host Read Length
ECReg   HOWRDR          _at_ 0x3006;    // Host Write Data
ECReg   HORDDR          _at_ 0x3007;    // Host Read Data

ECReg   HOCTL2R         _at_ 0x3008;    // Host Control 2
ECReg   RWFCSV          _at_ 0x3009;    // Received Write FCS Value
ECReg   RRFCSV          _at_ 0x300A;    // Received Read FCS Value
ECReg   WFCSV           _at_ 0x300B;    // Write FCS Value
ECReg   RFCSV           _at_ 0x300C;    // Read FCS Value
ECReg   AWFCSV          _at_ 0x300D;    // Assured Write FCS Value
ECReg   PADCTLR         _at_ 0x300E;    // Pad Control

//-----------------------------------------------------------------------------
// (31xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
/* Device Identification 00h-03h */
ECReg   REG_3100        _at_ 0x3100;
ECReg   REG_3101        _at_ 0x3101;
ECReg   REG_3102        _at_ 0x3102;
ECReg   REG_3103        _at_ 0x3103;

/* General Capabilities and Configurations     04h-07h */
ECReg   REG_3104        _at_ 0x3104;
ECReg   REG_3105        _at_ 0x3105;
ECReg   REG_3106        _at_ 0x3106;
ECReg   REG_3107        _at_ 0x3107;

/* Channel 0 Capabilities and Configurations   08h-0Bh */
ECReg   REG_3108        _at_ 0x3108;
ECReg   REG_3109        _at_ 0x3109;
ECReg   REG_310A        _at_ 0x310A;
ECReg   REG_310B        _at_ 0x310B;

/* Channel 1 Capabilities and Configurations   0Ch-0Fh */
ECReg   REG_310C        _at_ 0x310C;
ECReg   REG_310D        _at_ 0x310D;
ECReg   REG_310E        _at_ 0x310E;
ECReg   REG_310F        _at_ 0x310F;

/* Channel 2 Capabilities and Configurations   10h-13h */
ECReg   REG_3110        _at_ 0x3110;
ECReg   REG_3111        _at_ 0x3111;
ECReg   REG_3112        _at_ 0x3112;
ECReg   REG_3113        _at_ 0x3113;

/* Channel 3 Capabilities and Configurations   14h-17h */
ECReg   REG_3114        _at_ 0x3114;
ECReg   REG_3115        _at_ 0x3115;
ECReg   REG_3116        _at_ 0x3116;
ECReg   REG_3117        _at_ 0x3117;

/* Channel 3 Capabilities and Configurations 2 18h-1Bh */
ECReg   REG_3118        _at_ 0x3118;
ECReg   REG_3119        _at_ 0x3119;
ECReg   REG_311A        _at_ 0x311A;
ECReg   REG_311B        _at_ 0x311B;

ECReg   ESPCTRL0        _at_ 0x3190;    //eSPI PC Control 0 (ESPCTRL0) 90h
ECReg   ESPCTRL1        _at_ 0x3191;    //eSPI PC Control 1 (ESPCTRL1) 91h
ECReg   ESPCTRL2        _at_ 0x3192;    //eSPI PC Control 2 (ESPCTRL2) 92h
ECReg   ESPCTRL3        _at_ 0x3193;    //eSPI PC Control 3 (ESPCTRL3) 93h
ECReg   ESPCTRL4        _at_ 0x3194;    //eSPI PC Control 4 (ESPCTRL4) 94h
ECReg   ESPCTRL5        _at_ 0x3195;    //eSPI PC Control 5 (ESPCTRL5) 95h
ECReg   ESPCTRL6        _at_ 0x3196;    //eSPI PC Control 6 (ESPCTRL6) 96h
ECReg   ESPCTRL7        _at_ 0x3197;    //eSPI PC Control 7 (ESPCTRL7) 97h
ECReg   ESPCTRL8        _at_ 0x3198;    //eSPI PC Control 8 (ESPCTRL8) 98h
ECReg   ESPCTRL9        _at_ 0x3199;    //eSPI PC Control 9 (ESPCTRL9) 99h

ECReg   ESGCTRL0        _at_ 0x31A0;    //eSPI General Control 0 (ESGCTRL0) A0h
ECReg   ESGCTRL1        _at_ 0x31A1;    //eSPI General Control 1 (ESGCTRL1) A1h
ECReg   ESGCTRL2        _at_ 0x31A2;    //eSPI General Control 2 (ESGCTRL2) A2h
ECReg   ESGCTRL3        _at_ 0x31A3;    //eSPI General Control 3 (ESGCTRL3) A3h

ECReg   ESUCTRL0        _at_ 0x31B0;    //eSPI Upstream Control 0 (ESUCTRL0) B0h
ECReg   ESUCTRL1        _at_ 0x31B1;    //eSPI Upstream Control 1 (ESUCTRL1) B1h
ECReg   ESUCTRL2        _at_ 0x31B2;    //eSPI Upstream Control 2 (ESUCTRL2) B2h
ECReg   ESUCTRL3        _at_ 0x31B3;    //eSPI Upstream Control 3 (ESUCTRL3) B3h
ECReg   ESUCTRL4        _at_ 0x31B4;    //eSPI Upstream Control 4 (ESUCTRL4) B4h
ECReg   ESUCTRL5        _at_ 0x31B5;    //eSPI Upstream Control 5 (ESUCTRL5) B5h
ECReg   ESUCTRL6        _at_ 0x31B6;    //eSPI Upstream Control 6 (ESUCTRL6) B6h
ECReg   ESUCTRL7        _at_ 0x31B7;    //eSPI Upstream Control 7 (ESUCTRL7) B7h
ECReg   ESUCTRL8        _at_ 0x31B8;    //eSPI Upstream Control 8 (ESUCTRL8) B8h

ECReg   ESOCTRL0        _at_ 0x31C0;    //eSPI OOB Control 0 (ESOCTRL0) C0h
ECReg   ESOCTRL1        _at_ 0x31C1;    //eSPI OOB Control 1 (ESOCTRL1) C1h
ECReg   ESOCTRL2        _at_ 0x31C2;    //eSPI OOB Control 2 (ESOCTRL2) C2h
ECReg   ESOCTRL3        _at_ 0x31C3;    //eSPI OOB Control 3 (ESOCTRL3) C3h
ECReg   ESOCTRL4        _at_ 0x31C4;    //eSPI OOB Control 4 (ESOCTRL4) C4h
ECReg   ESOCTRL5        _at_ 0x31C5;    //eSPI OOB Control 5 (ESOCTRL5) C5h
ECReg   ESOCTRL6        _at_ 0x31C6;    //eSPI OOB Control 6 (ESOCTRL6) C6h
ECReg   ESOCTRL7        _at_ 0x31C7;    //eSPI OOB Control 7 (ESOCTRL7) C7h

ECReg   ESPISAFSC0      _at_ 0x31D0;    //eSPI SAFS Control 0 (ESPISAFSC0)
ECReg   ESPISAFSC1      _at_ 0x31D1;    //eSPI SAFS Control 1 (ESPISAFSC1)
ECReg   ESPISAFSC2      _at_ 0x31D2;    //eSPI SAFS Control 2 (ESPISAFSC2)
ECReg   ESPISAFSC3      _at_ 0x31D3;    //eSPI SAFS Control 3 (ESPISAFSC3)
ECReg   ESPISAFSC4      _at_ 0x31D4;    //eSPI SAFS Control 4 (ESPISAFSC4)
ECReg   ESPISAFSC5      _at_ 0x31D5;    //eSPI SAFS Control 5 (ESPISAFSC5)
ECReg   ESPISAFSC6      _at_ 0x31D6;    //eSPI SAFS Control 6 (ESPISAFSC6)
ECReg   ESPISAFSC7      _at_ 0x31D7;    //eSPI SAFS Control 7 (ESPISAFSC7)

//-----------------------------------------------------------------------------
// (32xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
ECReg   VWIDX0          _at_ 0x3200;    //eSPI VW Index 0

ECReg   VWIDX2          _at_ 0x3202;    //eSPI VW Index 2
ECReg   VWIDX3          _at_ 0x3203;    //eSPI VW Index 3
ECReg   VWIDX4          _at_ 0x3204;    //eSPI VW Index 4
ECReg   VWIDX5          _at_ 0x3205;    //eSPI VW Index 5
ECReg   VWIDX6          _at_ 0x3206;    //eSPI VW Index 6
ECReg   VWIDX7          _at_ 0x3207;    //eSPI VW Index 7

ECReg   VWIDX40         _at_ 0x3240;    //eSPI VW Index 40
ECReg   VWIDX41         _at_ 0x3241;    //eSPI VW Index 41
ECReg   VWIDX42         _at_ 0x3242;    //eSPI VW Index 42
ECReg   VWIDX43         _at_ 0x3243;    //eSPI VW Index 43
ECReg   VWIDX44         _at_ 0x3244;    //eSPI VW Index 44
ECReg   VWIDX45         _at_ 0x3245;    //eSPI VW Index 45
ECReg   VWIDX46         _at_ 0x3246;    //eSPI VW Index 46
ECReg   VWIDX47         _at_ 0x3247;    //eSPI VW Index 47

ECReg   VWCTRL0         _at_ 0x3290;    //eSPI VW Contrl 0
ECReg   VWCTRL1         _at_ 0x3291;    //eSPI VW Contrl 1
ECReg   VWCTRL2         _at_ 0x3292;    //eSPI VW Contrl 2
ECReg   VWCTRL3         _at_ 0x3293;    //eSPI VW Contrl 3

ECReg   VWCTRL5         _at_ 0x3295;    //eSPI VW Contrl 5
ECReg   VWCTRL6         _at_ 0x3296;    //eSPI VW Contrl 6
ECReg   VWCTRL7         _at_ 0x3297;    //eSPI VW Contrl 7

ECReg   REG_32A6        _at_ 0x32A6;

//-----------------------------------------------------------------------------
// (33xxh) EC Interface Registers, eSI Queue 0 - PUT_PC DATA , PUT_OOB DATA
//-----------------------------------------------------------------------------
/* PUT_PC Data Byte 0-63 (PUTPCDB0-63) */
ECReg   PUT_PC_DATA[64]     _at_ 0x3300;    // 64 bytes PUT_PC_DATA buffer
/* PUT_OOB Data Byte 0-79 (PUTOOBDB0-79) */
ECReg   PUT_OOB_DATA[80]    _at_ 0x3380;    // 80 bytes PUT_OOB_DATA buffer

//-----------------------------------------------------------------------------
// (34xxh) EC Interface Registers, eSI Queue 1 - UPSTEAM DATA
//-----------------------------------------------------------------------------
/* Upstream Data Byte 0-79 (UDB0-79) 3400h-344Fh */
ECReg   UPSTREAM_DATA[80]   _at_ 0x3400;    // 80 bytes UPSTREAM_DATA buffer
/* PUT_FLASH_NP Data Byte 0-63 (PUTFLASHNPDB0-63) Address Offset: 80h-BFh */
ECReg   PUTFLASHNPDB[64]    _at_ 0x3480;

/*-----------------------------------------------------------------------------
 * End of CORE_CHIPREGS.C */