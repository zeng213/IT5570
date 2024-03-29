@rem ---------------------------------------------------------------------------
@rem ***** PLEASE PUT AStyle Freeware at CODE ROOT FOLDER same path *****
@rem ---------------------------------------------------------------------------
SET OEMFOLDER=it557x_ADL_P-ec-v0.01
SET OEMNAME=OEM
SET OPTIONS=-A1 -s4 -p -Y -U -H -j -O -o -c -k3 -W3 -n -R -z1
cd..
cd AStyle
@rem -------------------------- 
@rem ***** INTEL PLATFORM *****
@rem -------------------------- 
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\INCLUDE\*.H
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\OEM_BANK0\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\OEM_BANK1\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\OEM_BANK2\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\OEM_BANK3\*.C

AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\USBC_PD\Cypress\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\USBC_PD\Cypress\*.H

AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\ITE_PREDEF\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\ITE_PREDEF\*.H
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\MPS2904\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\MPS2904\*.H
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\SAR231\*.C
AStyle.exe %OPTIONS% ..\%OEMFOLDER%\Code\OEM\%OEMNAME%\DEVICES\SAR231\*.H