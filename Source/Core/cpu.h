#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include <SDL.h>

#include "memory.h"
#include "display.h"

#include "utilities.h"

class CPU
{
private:
	
	
	// Timers
	uint8_t soundTimer;
	uint8_t delayTimer;
	double startTime;
	double currentTime;

	// Registers/PC
	int PC;

	uint8_t IRegister;
	uint8_t varRegister[16];

public:
	
	Memory* RAM;
	Display* screen;
	
	CPU();

	~CPU();
	
	void tick();

	uint16_t fetch();
	
	void decode(uint16_t _Instruction);

	void decrementTimers();
};

#endif