@echo off
setlocal

set "MyMaker=MyMaker"
set "start_py=.\MyMaker\DB4K-main\start.py"
mkdir "%MyMaker%"
set "dest_folder=%cd%\%MyMaker%"
set zipPath1=.\DB4K-main.zip
set zipPath2=.\Python.zip
set destinationPath=.\%MyMaker%

PowerShell -Command "Expand-Archive -Path '%zipPath1%' -DestinationPath '%destinationPath%'"
PowerShell -Command "Expand-Archive -Path '%zipPath2%' -DestinationPath '%destinationPath%'"

ping www.google.com -n 1 > nul

if %errorlevel% equ 0 (
    where python >nul 2>nul

    if %errorlevel% equ 0 (
        @REM Executar o start.py
        start %start_py%
    ) else (
        if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
            certutil -urlcache -split -f "%url1%" "%dest_folder%\python\python-2.7.9.amd64.msi"
            start "" "%dest_folder%\python\python-2.7.9.amd64.msi" /quiet
            del "%dest_folder%\python\python-2.7.9.amd64.msi"
        ) else if "%PROCESSOR_ARCHITECTURE%"=="x86" (
            certutil -urlcache -split -f "%url2%" "%dest_folder%\python\python-2.7.9.msi" /quiet
            start "" "%dest_folder%\python\python-2.7.9.msi"
            del "%dest_folder%\python\python-2.7.9.msi"        
        )
    ) 
) else (
    @REM Sem wifi
)