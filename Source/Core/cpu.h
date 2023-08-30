#pragma once

#include <stdio.h>

#include "memory.h"
#include "display.h"
#include "time_keeper.h"
#include "sdl_interface.h"

// Custom typedefs for ease of reading/use
using Byte = unsigned char;
using Word = unsigned short;


struct CPU
{
private:
	const int SCREEN_FPS = 60;
	const int INSTRUCTIONS_PER_SECOND = 700;

	// This is used for capping the refresh rate to the desired FPS.
	const double SECONDS_PER_FRAME = 1.0 / SCREEN_FPS;
	const double MILLISECONDS_PER_FRAME = SECONDS_PER_FRAME * 1000;

	// This is used for capping the amount of instructions able to be executed each frame.
	const int INSTRUCTIONS_PER_FRAME = INSTRUCTIONS_PER_SECOND / SCREEN_FPS;
	int currentInstructionCount;

	TimeKeeper timeKeeper;
	Display disp;

	Byte delayTimer;
	Byte soundTimer;

	// Program counter.
	Word PC;

	// Index register.
	Word I;

	// General variable registrs.
	Byte V[15] = { 0 };

	void _00EN(Byte Nibbles[]);
	void _1NNN(Byte Nibbles[]);
	void _2NNN(Byte Nibbles[]);
	void _3XNN(Byte Nibbles[]);
	void _4XNN(Byte Nibbles[]);
	void _5XY0(Byte Nibbles[]);
	void _6XNN(Byte Nibbles[]);
	void _7XNN(Byte Nibbles[]);
	void _8XYN(Byte Nibbles[]);
	void _9XY0(Byte Nibbles[]);
	void _ANNN(Byte Nibbles[]);
	void _BNNN(Byte Nibbles[]);
	void _CXNN(Byte Nibbles[]);
	void _DXYN(Byte Nibbles[]);
	void _EXNN(Byte Nibbles[]);


public:
	Memory mem;
	
	CPU();
	~CPU();

	void Process(Memory& ActiveMemory);
	void Render(SDLI& SDLInterface);
};

typedef enum Instruction_Code
{
	x00EN = 0,
	x1NNN,
	x2NNN,
	x3XNN,
	x4XNN,
	x5XY0,
	x6XNN,
	x7XNN,
	x8XYN,
	x9XY0,
	xANNN,
	xBNNN,
	xCXNN,
	xDXYN,
	xEXNN
} ins;