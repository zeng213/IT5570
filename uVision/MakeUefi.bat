@ECHO OFF
REM ####################################################################
REM #* Filename: MakeUefi.bat
REM #* Function: The BATCH file for uVision ITE EC Firmware.
REM #* Copyright (c) 2011-2019, ITE Tech. Inc.
REM #* All Rights Reserved.
REM ####################################################################
SET OEMFOLDER=OEM
SET ITECFILENAME=EC_DEMO.bin
SET EFIUPDFOLDER=ITE_UPD

CD..
DEL /Q ROM\%EFIUPDFOLDER%\%ITECFILENAME%
CD ROM
COPY %ITECFILENAME% %EFIUPDFOLDER%\%ITECFILENAME%
COPY %ITECFILENAME% ITEECNM.BIN
..\TOOLS\FU /CHECKSUM %ITECFILENAME% >Checksum.txt
..\TOOLS\ITENM.exe

REM ####################################################################
REM #* MAKE FEC64.NSH
REM ####################################################################
CD %EFIUPDFOLDER%
DEL FEC64.NSH
COPY ..\..\TOOLS\ifu.efi

@ECHO OFF
ECHO.
ECHO    %date%  %time%
SET bdate=%date:~0,4%/%date:~5,2%/%date:~8,2%
SET btime=%time:~0,2%:%time:~3,2%:%time:~6,2%
ECHO.
ECHO ******************************************************************** >FEC64.NSH
ECHO *  ITE Tech. Inc.                              >>FEC64.NSH
ECHO *  PROJECT: ITE EC                             >>FEC64.NSH
ECHO *  UEFI Shell IT557xE eFlash Update            >>FEC64.NSH
ECHO *  FILENAME: %ITECFILENAME%  >>FEC64.NSH
ECHO *  BUILD DAY: %bdate%-%btime%  >>FEC64.NSH
ECHO ******************************************************************** >>FEC64.NSH
ECHO ifu %ITECFILENAME% >>FEC64.NSH
REM CLS
:DONE
CD..
