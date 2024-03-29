ECHO %date%
SET dddd=%date:~0,4%/%date:~5,2%/%date:~8,2%
ECHO %time%
SET tttt=%time:~0,2%:%time:~3,2%:%time:~6,2%
ECHO #define _BUILD_DATE    "%dddd%$" >OEM_TIME.H
ECHO #define _BUILD_TIME    "%tttt%$" >>OEM_TIME.H
MOVE /Y OEM_TIME.H ..\Code\Oem\Oem\Include\