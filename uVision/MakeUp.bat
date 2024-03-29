@ECHO OFF
SET FILENAME=EC_DEMO.BIN

REM ***************************************************************************
REM Setting
REM ***************************************************************************
REM ---------------------------------------------------------------------------
REM (64, 96, 128, and 160 are valid)
SET EC_ROM_SIZE=128

path=C:\Keil\C51\BIN;..\Tools;..\Tools\NMake;
REM ---------------------------------------------------------------------------
cd..
move .\KeilMisc\Obj\*.h* .\ROM
move .\KeilMisc\Obj\*.m51 .\KeilMisc\Map
del /q .\KeilMisc\Obj\*.b0*

cd rom
DEL /q *.BIN

REM ---------------------------------------------------------------------------
REM Common + Bank0 + Bank1 + Bank2 + Bank3 [160KB]
REM ---------------------------------------------------------------------------
Hex2bin -s 0x0000 -e b0 *.H00
FU /SIZE 64 ITEEC.b0 BANK0.BIN FF

Hex2bin -s 0x8000 -e b1 *.H01
FU /SIZE 32 ITEEC.b1 BANK1.BIN FF

Hex2bin -s 0x8000 -e b2 *.H02
FU /SIZE 32 ITEEC.b2 BANK2.BIN FF

Hex2bin -s 0x8000 -e b3 *.H03
FU /SIZE 32 ITEEC.b3 BANK3.BIN FF

COPY /b BANK0.BIN+BANK1.BIN+BANK2.BIN+BANK3.BIN ITEEC.ALL

FU /SIZE %EC_ROM_SIZE% ITEEC.ALL ITEEC.BIN FF

RENAME ITEEC.BIN %FILENAME%  

:Done
DEL /q *.H*
DEL /q *.b0
DEL /q *.b1
DEL /q *.b2
DEL /q *.b3
DEL /q BANK*.*

@echo on