![imperialism](title.png)

A 4X turn-based strategy game.

# Compiling
## Linux
To compile this project on Linux you need to install:
- SFML 2.5.1 (instructions here: https://www.sfml-dev.org/tutorials/2.5/start-linux.php#introduction) 
- g++ compiler
- CMake 3.12 or higher

After that run `cmake .` command in project's directory and then `make`.
## Windows
To compile this project on Windows you need to install:
- SFML 2.5.1 for MinGW (DW2) 32-bit (available here: https://www.sfml-dev.org/download/sfml/2.5.1/)
- MinGW 7.3.0 compiler (available here: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/)
- CMake 3.12 or higher

Add paths to SFML and MinGW to `PATH` environment variable. Next run `cmake -G "MinGW Makefiles" .` command from project's directory. After that run `mingw32-make` to compile the project.
