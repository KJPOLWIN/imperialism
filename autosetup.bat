@echo off

REM Downloading SFML
PowerShell -command "Invoke-WebRequest https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip -OutFile '.\SFML.zip'"
PowerShell -command "Expand-Archive -Force .\SFML.zip .\   "

REM Checking if CMake is installed, and installing it
for /f %%I in ('cmake --version') DO set cmake=%%I

if "%cmake%"=="" (
  echo Installing CMake. Follow instructions in CMake installer.
  PowerShell -command "Invoke-WebRequest https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.msi -OutFile 'cmake.msi'"
  call .\cmake.msi
  del cmake.msi
	
) else (
  echo CMake already installed
)
