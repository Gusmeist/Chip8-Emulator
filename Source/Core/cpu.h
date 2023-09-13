#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>

#include "memory.h"
#include "display.h"
#include "time_keeper.h"
#include "sdl_interface.h"

using Byte = unsigned char;		// Declaration for one byte.
using Word = unsigned short;	// Declaration for one word (Two bytes).

typedef enum Instruction_Code	// Instruction code enum, used for decoding the first nibble into a full code.  Mainly just used for								
{								// Ease of readability.
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
	const int SCREEN_FPS = 60;													// Base screen fps and instructions per second.
	const int INSTRUCTIONS_PER_SECOND = 700;

	const double SECONDS_PER_FRAME = 1.0 / SCREEN_FPS;							// The time that needs to pass each frame, so that the fps will be
	const double MILLISECONDS_PER_FRAME = SECONDS_PER_FRAME * 1000;				// capped at 60 fps.

	const int INSTRUCTIONS_PER_FRAME = INSTRUCTIONS_PER_SECOND / SCREEN_FPS;	// The amount of instructions that can be processed each frame, rounded
	int currentInstructionCount;												// down to keep the amount each frame a constant, whole number.

	TimeKeeper timeKeeper;					// Keeps track of the time passed when processing cpu instructions.
	Display disp;							// An array and an interface to create a screen buffer, which is later drawn to the screen.

	Byte delayTimer;						// Counts down once per frame, until reaching 0.  Used for delays.  Can be set and read.
	Byte soundTimer;						// Counts down once per frame, until reaching 0.  Used for lengths of sound beeps.  Can be set.

	Word PC;								// Program counter.
											// Keeps track of the location of the next cpu instruction.

	Word I;									// Index register.
											// Typically the location of the next sprite to draw.

	Byte V[16] = { 0 };						// 16 variable registers, V[F] being used for an overflow bit usually.

	void _00EN(Byte Nibbles[]);				// Clear screen & subroutine return.
	void _1NNN(Word Instruction);			// Sets PC to the lower 3 nibbles.
	void _2NNN(Word Instruction);			// Push current PC to stack, set PC to lower 3 nibbles.
	void _3XNN(Byte Nibbles[]);				// Skip next instruction if lower byte equals V[X].
	void _4XNN(Byte Nibbles[]);				// Skip next instruction if lower byte is not equal to V[X].
	void _5XY0(Byte Nibbles[]);				// Skip next instruction if V[X] equals V[Y].
	void _6XNN(Byte Nibbles[]);				// Set V[X] to lower byte.
	void _7XNN(Byte Nibbles[]);				// Increment V[X] by lower byte.
	void _8XYN(Byte Nibbles[]);				// Various logical operations on V[X] and V[Y], based off the value of the least significant nibble.
	void _9XY0(Byte Nibbles[]);				// Skip next instruction if V[X] does not equal V[Y].
	void _ANNN(Word Instruction);			// Sets I to the lower 3 nibbles.
	void _BNNN(Word Instruction);			// Sets PC to V[0] plus the lower 3 nibbles.
	void _CXNN(Byte Nibbles[]);				// Sets V[X] to a random number (0-255) logical AND with the lower byte.
	void _DXYN(Byte Nibbles[]);				// The draw instruction (Read implementation).
	void _EXNN(Byte Nibbles[]);				// Based off the lowest nibble, will determine if the key number X is pressed or not pressed.  Skips instruction if condition met.
	void _FXNN(Byte Nibbles[]);				// Various operations based off X and the lower nibbles.

public:
	Memory mem;											// Memory allocation (4 KB).

	bool relevantKeyStates[17] = { false };
	
	CPU();												// Generic constructor and destructor.
	~CPU();

	void Load(std::vector<unsigned char>& InputBuffer);	// Load a vector that contains binary information from a file.

	bool Process();										// Called each time an instruction should be called, which decodes and exectues the next instruction.
	void Render(SDLI& SDLInterface);					// Called each frame, which decrements the timers and calls a display method.

public:
	bool steppingMode;					// Flags for special debugging modes.
};