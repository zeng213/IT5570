@ECHO OFF
REM ####################################################################
REM #* Filename: B.BAT
REM #* Function: The BATCH file for ITE Embedded Controller Firmware.
REM #* Copyright (c) 2011-2022, ITE Tech. Inc.
REM #* All Rights Reserved.
REM ####################################################################
SET OEMFOLDER=OEM
SET ITECFILENAME=ADL_N_MRD_EC_00_29.bin
SET EFIUPDFOLDER=UPD_ADL_N_MRD_EC_00_29
SET PDFWFILENAME=ITE_PD_FW.bin
SET ECPDFILENAME=ADL_N_MRD_EC_00_29_PD.bin
SET MIRRORCHKCRC=Y
SET PUASE=N

REM ####################################################################
REM #* START BUILD
REM ####################################################################
DEL /Q ROM\%ITECFILENAME% 
REM CALL BUILD %OEMFOLDER% ALL

REM ####################################################################
REM #* Add build target
REM ####################################################################


REM PnP test build 
if /I "%1" == "pnp" (

Echo Build Target: PnP

SET FILE_SUFFIX=_PnP
SET CCMacro="_SUPPORT_BATT_FAKE_INFO_"

)

REM release build 
if /I "%1" == "" (

Echo Build Target: Default
SET FILE_SUFFIX=""
SET CCMacro="_RELEASE_"

)

SET EFIUPDFOLDER=%EFIUPDFOLDER%%FILE_SUFFIX%
CALL BUILD %OEMFOLDER% ALL %CCMacro%

@ECHO OFF

CD ROM
IF NOT EXIST %OEMFOLDER%.BIN GOTO DONE
IF NOT EXIST "%OEMFOLDER%" MD "%EFIUPDFOLDER%"
RENAME %OEMFOLDER%.BIN %ITECFILENAME%

IF %MIRRORCHKCRC% == N  GOTO NOCRC
..\TOOLS\FU /WECRC %ITECFILENAME% 0 1FFFF 4A
:NOCRC

COPY %ITECFILENAME% ITEECNM.BIN
..\TOOLS\FU /CHECKSUM %ITECFILENAME% >Checksum.txt
REM COPY ..\PD_FW\%PDFWFILENAME% PD.BIN
REM COPY /Y /B %ITECFILENAME% /B + PD.BIN /B %ECPDFILENAME% /B
..\TOOLS\ITENM.exe
COPY ifu239.efi %EFIUPDFOLDER%
COPY /Y %ITECFILENAME% %EFIUPDFOLDER%\%ITECFILENAME%
CD  %EFIUPDFOLDER%
..\..\TOOLS\FU /CHECKSUM %ITECFILENAME% >Checksum.txt
CD..

REM ####################################################################
REM #* MAKE FEC64.NSH
REM ####################################################################
CD %EFIUPDFOLDER%
DEL FEC64.NSH
COPY ..\..\TOOLS\ifu239.efi
COPY ..\..\ReleaseNotes.txt

@ECHO OFF
ECHO.
ECHO    %date%  %time%
SET bdate=%date:~0,4%/%date:~5,2%/%date:~8,2%
SET btime=%time:~0,2%:%time:~3,2%:%time:~6,2%
ECHO.
ECHO ******************************************************************** >FEC64.NSH
ECHO *  ITE Tech. Inc.                               >>FEC64.NSH
ECHO *  PROJECT: Intel ADL_N MRD EC                  >>FEC64.NSH
ECHO *  UEFI Shell IT557xVG eFlash Update            >>FEC64.NSH
ECHO *  FILENAME: %ITECFILENAME%  >>FEC64.NSH
ECHO *  BUILD DAY: %bdate%-%btime%  >>FEC64.NSH
ECHO ******************************************************************** >>FEC64.NSH
ECHO mm 66 DD -w 1 -io >>FEC64.NSH
ECHO mm 66 DD -w 1 -io >>FEC64.NSH
ECHO ifu239 %ITECFILENAME% 0 /mi>>FEC64.NSH 
REM CLS
TYPE FEC64.NSH
IF %PUASE% == N  GOTO DONE
ECHO.
PAUSE
:DONE
CD..
