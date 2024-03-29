/*-----------------------------------------------------------------------------
 * TITLE: CORE_CHIPSFR.H
 *
 * STD Special Function Registers (SFR) Declaration and Bit Definition.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 * ------------------------------------------------------------------------- */
#ifndef CORE_CHIPSFR_H
#define CORE_CHIPSFR_H

//-----------------------------------------------------------------
// Standard 8051 SFR
//-----------------------------------------------------------------
sfr P0   = 0x80;    //SFR@80 #Port 0 Register
sfr P1   = 0x90;    //SFR@90 #Port 1 Register
sfr P2   = 0xA0;    //SFR@A0 #Port 2 Register
sfr P3   = 0xB0;    //SFR@B0 #Port 3 Register
sfr PSW  = 0xD0;    //SFR@D0 #
sfr ACC  = 0xE0;    //SFR@E0 #
sfr B    = 0xF0;    //SFR@F0 #
sfr SP   = 0x81;    //SFR@81 #Stack Pointer Register
sfr DPL  = 0x82;    //SFR@82 #Data Pointer Low Register
sfr DPH  = 0x83;    //SFR@83 #Data Pointer High Register
sfr PCON = 0x87;    //SFR@87 #Power Control Register
sfr TCON = 0x88;    //SFR@88 #Timer Control Register
sfr TMOD = 0x89;    //SFR@89 #Timer Mode Register
sfr TL0  = 0x8A;    //SFR@8A #Timer 0 Low Byte Register
sfr TL1  = 0x8B;    //SFR@8B #Timer 1 Low Byte Register
sfr TH0  = 0x8C;    //SFR@8C #Timer 0 High Byte Register
sfr TH1  = 0x8D;    //SFR@8D #Timer 1 High Byte Register
sfr CKCON = 0x8E;   //SFR@8E #
sfr IE   = 0xA8;    //SFR@A8 #
sfr IP   = 0xB8;    //SFR@B8 #
sfr SCON = 0x98;    //SFR@98 #
sfr SBUF = 0x99;    //SFR@99 #

sfr T2CON  = 0xC8;  //SFR@C8 #
sfr T2MOD  = 0xC9;  //SFR@C9 #
sfr RCAP2L = 0xCA;  //SFR@CA #
sfr RCAP2H = 0xCB;  //SFR@CB #
sfr TL2    = 0xCC;  //SFR@CC #
sfr TH2    = 0xCD;  //SFR@CD #
sfr WDTCON = 0xD8;  //SFR@D8 #

sfr MPRECF = 0xF7;  //SFR@F7 #

//-----------------------------------------------------------------
// Bit register
//-----------------------------------------------------------------
sbit WDTEB  = 0xD9; //B51@D9 #Watch dog register
sbit WDTRST = 0xD8; //B51@D8

sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;       // PSW

sbit TF1  = 0x8F;
sbit TR1  = 0x8E;
sbit TF0  = 0x8D;
sbit TR0  = 0x8C;
sbit IE1  = 0x8B;
sbit IT1  = 0x8A;
sbit IE0  = 0x89;
sbit IT0  = 0x88;       // TCON

sbit EA   = 0xAF;
sbit ET2  = 0xAD;
sbit ES   = 0xAC;
sbit ET1  = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;       // IE

sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;       // IP

sbit RD   = 0xB7;
sbit WR   = 0xB6;
sbit T1   = 0xB5;
sbit T0   = 0xB4;
sbit INT1 = 0xB3;
sbit INT0 = 0xB2;
//sbit TXD  = 0xB1;
//sbit RXD  = 0xB0;

sbit SM0  = 0x9F;
sbit SM1  = 0x9E;
sbit SM2  = 0x9D;
sbit REN  = 0x9C;
sbit TB8  = 0x9B;
sbit RB8  = 0x9A;
sbit TI   = 0x99;
sbit RI   = 0x98;       // SCON

sbit TF2    = 0xCF;
sbit EXF2   = 0xCE;
sbit RCLK   = 0xCD;
sbit TCLK   = 0xCC;
sbit EXEN2  = 0xCB;
sbit TR2    = 0xCA;
sbit CT2    = 0xC9;
sbit CPRL2  = 0xC8;     // T2CON

#endif
