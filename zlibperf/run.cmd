@echo off
setlocal enableDelayedExpansion

REM silesia corpus
REM http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia
REM webster: The 1913 Webster Unabridged Dictionary	(html)
REM mozilla: Tarred executables of Mozilla 1.0 (Tru64 UNIX edition)
SET dataset="silesia\mozilla" "silesia\webster"
REM 6=default level
SET levels=6
SET zlibperf=zlibperf.exe
REM -v = verify output
SET zlibperfoptions=-v
REM SET zlibperfoptions=
SET platforms=x64 x86
SET implementationfolder=..\implementations

for /F "skip=1 delims=" %%a in ('wmic cpu get name') do for /f "delims=" %%b in ("%%a") do echo CPU: %%b

::build "array" of implementations
set folderCount=0
for /f "eol=: delims=" %%F in ('dir /b /ad %implementationfolder%') do (
  set /a folderCount+=1
  set "folder!folderCount!=%%F"
)


(for %%l in (%levels%) do ( 
echo Level: %%l
echo.

(for %%d in (%dataset%) do ( 
echo Data : %%~d
echo.

(for %%p in (%platforms%) do (
   echo Platform: %%p
   echo =============

	 if %%p==x86 (
			set outputfolder=Release
		) else (
			set outputfolder=%%p\Release
		)	 
   
   (for /l %%i in (1 1 %folderCount%) do (
		echo !folder%%i!
		del "!outputfolder!\zlib1.dll" 2>NUL
		
		if exist "..\implementations\!folder%%i!\%%p\zlib1.dll" (
			xcopy "..\implementations\!folder%%i!\%%p\zlib1.dll" "!outputfolder!\" /y >NUL
			"!outputfolder!\%zlibperf%" %%d -c %%l %zlibperfoptions%
		) else (
			echo skipping. zlib1.dll does not exist.
		)
		
		echo.   
   )) 

))
))
))

pause
