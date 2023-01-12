#include "cpu.h"

CPU::CPU()
{
	RAM = new Memory(4 * KILOBYTE);
	screen = new Display();
	soundTimer = 0;
	delayTimer = 0;

	startTime = 0.0;
	currentTime = 0.0;

	PC = 0;

	IRegister = 0b00000000;
	for (int i = 0; i < 16; i++)
	{
		varRegister[i] = 0b00000000;
	}
}

CPU::~CPU()
{
	;
}

void CPU::tick()
{
	startTime = SDL_GetTicks() / 1000.0;

	// stuff

	currentTime = SDL_GetTicks() / 1000.0;

	if (currentTime - startTime > SCREEN_TICKS_PER_FRAME)
	{
		// update display
	}

	currentTime = SDL_GetTicks() / 1000.0;;
	
	if (currentTime - startTime < TIME_PER_CPU_TICK)
	{
		SDL_Delay((TIME_PER_CPU_TICK - (currentTime - startTime)) * 1000.0);
	}
}

uint16_t CPU::fetch()
{
	return 0;
}

void CPU::decode(uint16_t _Instruction)
{
	;
}

void CPU::decrementTimers()
{
	if (soundTimer > 0)
	{
		soundTimer--;
	}
	if (delayTimer > 0)
	{
		delayTimer--;
	}
}