#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>

#include "memory.h"
#include "display.h"
#include "time_keeper.h"
#include "sdl_interface.h"

// Custom typedefs for ease of reading/use
using Byte = unsigned char;
using Word = unsigned short;

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
	xEXNN,
	xFXNN
} ins;

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
	Byte V[16] = { 0 };

	void _00EN(Byte Nibbles[]);
	void _1NNN(Word Instruction);
	void _2NNN(Word Instruction);
	void _3XNN(Byte Nibbles[]);
	void _4XNN(Byte Nibbles[]);
	void _5XY0(Byte Nibbles[]);
	void _6XNN(Byte Nibbles[]);
	void _7XNN(Byte Nibbles[]);
	void _8XYN(Byte Nibbles[]);
	void _9XY0(Byte Nibbles[]);
	void _ANNN(Word Instruction);
	void _BNNN(Word Instruction);
	void _CXNN(Byte Nibbles[]);
	void _DXYN(Byte Nibbles[]);
	void _EXNN(Byte Nibbles[]);
	void _FXNN(Byte Nibbles[]);

public:
	Memory mem;

	bool relevantKeyStates[17] = { false };
	
	CPU();
	~CPU();

	void Load(std::vector<unsigned char>& InputBuffer);

	bool Process();
	void Render(SDLI& SDLInterface);

// Debug stuff
public:
	bool steppingMode;
};