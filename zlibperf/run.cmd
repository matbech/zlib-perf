@echo off

REM silesia corpus
REM http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia
REM webster: The 1913 Webster Unabridged Dictionary	(html)
REM mozilla: Tarred executables of Mozilla 1.0 (Tru64 UNIX edition)
SET dataset="silesia\mozilla" "silesia\webster"
REM 6=default level
SET levels=6
SET zlibperf=Release\zlibperf.exe
SET implementations="zlib-ori" "zlib-ori asm" "zlib-ng" "zlib matbech" "zlib dev" "fast_zlib"
SET platforms=x86 x64

(for %%l in (%levels%) do ( 
echo Level: %%l
echo.

(for %%d in (%dataset%) do ( 
echo Data : %%~d
echo.

(for %%p in (%platforms%) do (
   echo Platform: %%p
   echo =============
   
   (for %%i in (%implementations%) do (
		echo %%~i
		del Release\zlib1.dll 2>NUL
		
		if exist "..\%%~i\%%p\zlib1.dll" (
			xcopy "..\%%~i\%%p\zlib1.dll" Release\ /y >NUL
			%zlibperf% %%d -c %level%
		) else (
			echo skipping. zlib1.dll does not exist.
		)
		
		echo.   
   )) 

))
))
))

pause
