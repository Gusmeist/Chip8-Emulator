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

	Byte delayTimer;
	Byte soundTimer;

	// Program counter.
	Word PC;

	// Index register.
	Word I;

	// General variable registrs.
	Byte V[15] = { 0 };


public:
	CPU();
	~CPU();

	void Process(Display& ActiveDisplay, Memory& ActiveMemory);
	void Render(Display& ActiveDisplay, SDLI& SDLInterface);
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