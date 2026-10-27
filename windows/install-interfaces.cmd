@echo off
setlocal
if "%~1"=="" (
  echo Usage: install-interfaces.cmd C:\path\to\InterfacesAndLibraries
  exit /b 1
)
set "PATH=%~dp0msys\usr\bin;%PATH%"
"%~dp0msys\usr\bin\bash.exe" "%~dp0share\retro68\install-interfaces.sh" "%~1"
