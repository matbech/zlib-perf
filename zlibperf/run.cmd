@echo off

REM silesia corpus
REM http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia
REM The 1913 Webster Unabridged Dictionary	(html)
SET data=silesia\webster
REM Tarred executables of Mozilla 1.0 (Tru64 UNIX edition)
SET data=silesia\mozilla

echo 32-bit
echo ======
echo zlib-ng
echo -------
xcopy ..\zlib-ng\x86\zlib1.dll Release\ /y >NUL
Release\zlibperf.exe %data%
echo.
echo matbech/zlib
echo -------------
xcopy "..\zlib matbech\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data%
echo.
echo zlib-ori asm
echo ------------
xcopy "..\zlib-ori asm\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data%
echo.
echo zlib dev
echo --------
xcopy "..\zlib dev\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data%
echo.
echo 64-bit
echo ======
echo zlib-ng
echo -------
xcopy ..\zlib-ng\x64\zlib1.dll x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data%
echo.
echo matbech/zlib
echo -------------
xcopy "..\zlib matbech\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data%
echo.
echo zlib-ori asm
echo ------------
xcopy "..\zlib-ori asm\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data%
echo.
echo zlib dev
echo --------
xcopy "..\zlib dev\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data%

pause
