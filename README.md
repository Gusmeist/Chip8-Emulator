# Chip8 Emulator with C++

## Overview

This is a very basic emulator of the standard Chip8 instruction set.  It is capable of playing roms (No sound).  More features to come later.

## Setup

1. Clone the repository to your local machine.
2. In your CMAKE_PREFIX_PATH location, include an SDL2 package.
   - If needed, download the VS version of SDL2 from [here](https://github.com/libsdl-org/SDL).
   - If needed, download CMAKE from [here](https://cmake.org/).  Add CMake to windows path if desired.
   - If you do not have a custom CMAKE_PREFIX_PATH location, use a system location such as C:/Program Files/ and place the SDL2 folder there.
3. Run the following commands in cmd/powershell for building with CMake:
```
cd "{Path to project directory}"
mkdir build
cd build
cmake ../
cmake --build . --config {Release or Debug}
```
4. From your SDL2 download, in the folder ~/SDL2/bin/x86, copy SDL2.dll to the folder {Path to project directory}/build/{Debug or release}.
5. Run the executable.

## Usage

### Controls

The valid keys for interacting with the roms are currently:
```
    1 2 3 4
    q w e r
    a s d f
    z x c v 
```
DEBUG KEYS:
- 0: Toggle stepping mode.  Processes 1 instruction at a time.
  - UP ARROW: While in stepping mode, move forward one instruction.

### Loading ROMS

Currently only loads roms from a "roms" folder in the same directory as the executable.  When loading the program, type the name of a rom in the folder including the .ch8 extension.