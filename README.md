![imperialism](title.png)

A 4X turn-based strategy game.

# Installation
## Using autosetup scripts 
### Linux
Script works only on Debian-based distros. Run `sudo ./autosetup.sh`. Script will automatically install SFML, g++ compiler and CMake. Make sure script is installing the correct version of SFML (2.5.1). After that run `cmake .` and `make`.
### Windows
Run `autosetup.bat` as regular user (not administrator). Script will automatically download and unpack SFML and install CMake. After that install MinGW 7.3.0 (available here: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/). Add path to MinGW\bin folder to `PATH` environment variable. Then run `cmake -G "MinGW Makefiles" -D SFML_DIR=.\SFML-2.5.1\lib\cmake\SFML .` and `mingw32-make`.
## Manual
### Linux
To compile this project on Linux you need to install:
- SFML 2.5.1 (instructions here: https://www.sfml-dev.org/tutorials/2.5/start-linux.php#introduction) 
- g++ compiler
- CMake 3.12 or higher

After that run `cmake .` command in project's directory and then `make`.
### Windows
To compile this project on Windows you need to install:
- SFML 2.5.1 for MinGW (DW2) 32-bit (available here: https://www.sfml-dev.org/download/sfml/2.5.1/)
- MinGW 7.3.0 compiler (available here: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/)
- CMake 3.12 or higher

Add path to MinGW\bin folder to `PATH` environment variable. Next run `cmake -G "MinGW Makefiles" -D SFML_DIR=path-to-sfml\SFML-2.5.1\lib\cmake\SFML .` command from project's directory. After that run `mingw32-make` to compile the project.
