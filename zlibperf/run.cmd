@echo off

REM silesia corpus
REM http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia
REM The 1913 Webster Unabridged Dictionary	(html)
SET data=silesia\webster
REM Tarred executables of Mozilla 1.0 (Tru64 UNIX edition)
REM SET data=silesia\mozilla
REM 6=default level
SET level=6

echo Data : %data%
echo Level: %level%
echo.
echo 32-bit
echo ======
echo zlib-ori
echo --------
xcopy "..\zlib-ori\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo zlib-ori asm
echo ------------
xcopy "..\zlib-ori asm\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo zlib-ng
echo -------
xcopy ..\zlib-ng\x86\zlib1.dll Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo matbech/zlib
echo -------------
xcopy "..\zlib matbech\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo zlib dev
echo --------
xcopy "..\zlib dev\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo fast_zlib
echo --------
xcopy "..\fast_zlib\x86\zlib1.dll" Release\ /y >NUL
Release\zlibperf.exe %data% -c %level%
echo.
echo 64-bit
echo ======
echo zlib-ori
echo --------
xcopy "..\zlib-ori\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%
echo.
echo zlib-ori asm
echo ------------
xcopy "..\zlib-ori asm\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%
echo.
echo zlib-ng
echo -------
xcopy ..\zlib-ng\x64\zlib1.dll x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%
echo.
echo matbech/zlib
echo -------------
xcopy "..\zlib matbech\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%
echo.
echo zlib dev
echo --------
xcopy "..\zlib dev\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%
echo.
echo fast_zlib
echo --------
xcopy "..\fast_zlib\x64\zlib1.dll" x64\Release\ /y >NUL
x64\Release\zlibperf.exe %data% -c %level%


pause
