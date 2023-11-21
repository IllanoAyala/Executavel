@echo off
setlocal

set "MyMaker=MyMaker"
set "url1=https://www.python.org/ftp/python/2.7.9/python-2.7.9.amd64.msi"
set "url2=https://www.python.org/ftp/python/2.7.9/python-2.7.9.msi"
set "start_py=.\MyMaker\DB4K-main\start.py"

mkdir "%MyMaker%"
set "dest_folder=%cd%\%MyMaker%"

powershell -Command "Expand-Archive -Path '.\DB4K-main.zip' -DestinationPath '.\%MyMaker%' -Force"

ping www.google.com -n 1 > nul

if %errorlevel% equ 0 (
    where python >nul 2>nul

    if %errorlevel% equ 0 (
        @REM Executar o start.py
        start %start_py%
    ) else (
        if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
            certutil -urlcache -split -f "%url1%" "%dest_folder%\python-2.7.9.amd64.msi"
            start "" "%dest_folder%\python-2.7.9.amd64.msi" /quiet
            del "%dest_folder%\python-2.7.9.amd64.msi"
        ) else if "%PROCESSOR_ARCHITECTURE%"=="x86" (
            certutil -urlcache -split -f "%url2%" "%dest_folder%\python-2.7.9.msi" /quiet
            start "" "%dest_folder%\python-2.7.9.msi"
            del "%dest_folder%\python-2.7.9.msi"        
        )
    ) 
) else (
    @REM Sem wifi
)

















@REM mkdir "%MyMaker%"
@REM set "dest_folder=%cd%\%MyMaker%"

@REM echo ....
@REM @REM powershell -Command "Add-Type -AssemblyName System.IO.Compression.FileSystem; [System.IO.Compression.ZipFile]::ExtractToDirectory('.\DB4K-main.zip', '.\%MyMaker%')"

@REM for /f %%a in ('powershell -Command "(Get-NetAdapter | Where-Object { $_.InterfaceDescription -like '*Wireless*' }).Name"') do (
@REM     set "wifi_found=true"
@REM )

@REM if %wifi_found%==false (
@REM     where python >nul 2>nul

@REM     if %errorlevel% equ 0 (
@REM         REM Executar o start.py
@REM         start %start_py%
@REM     ) else (
@REM         if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
@REM             certutil -urlcache -split -f "%url1%" "%dest_folder%\python-2.7.9.amd64.msi"
@REM             start "" "%dest_folder%\python-2.7.9.amd64.msi" /quiet
@REM         ) else if "%PROCESSOR_ARCHITECTURE%"=="x86" (
@REM             certutil -urlcache -split -f "%url2%" "%dest_folder%\python-2.7.9.msi" /quiet
@REM             REM start "" "%dest_folder%\python-2.7.9.msi"
@REM         )
@REM     ) 
@REM ) else ( 
@REM     echo Sem Wifi
@REM     @REM powershell -Command "Add-Type -AssemblyName System.IO.Compression.FileSystem; [System.IO.Compression.ZipFile]::ExtractToDirectory('.\Programs.zip', '.\%Programs%')"
@REM     if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
@REM         @REM start "" "%dest_folder%\python-2.7.9.amd64.msi"
@REM     ) else if "%PROCESSOR_ARCHITECTURE%"=="x86" (
@REM         @REM start "" "%dest_folder%\python-2.7.9.msi"
@REM     )
@REM )

@REM pause
