#include "cpu.h"

CPU::CPU()
{
	delayTimer = 0;
	soundTimer = 0;

	timeKeeper.Restart();

	currentInstructionCount = INSTRUCTIONS_PER_FRAME;

	PC = 0x200;

	I = 0;
}

CPU::~CPU()
{

}

void CPU::Process(Display& disp, Memory& mem)
{
	while (currentInstructionCount > 0)
	{
		Word currentInstruction = (Word)(mem.Data[PC]) << 8;
		currentInstruction |= (Word)(mem.Data[PC + 1]);
		PC += 2;
		
		Byte nibble[4];

		nibble[0] = currentInstruction & 0xF000 >> 8;
		nibble[1] = currentInstruction & 0x0F00 >> 8;
		nibble[2] = currentInstruction & 0x00F0;
		nibble[3] = currentInstruction & 0x000F;

		switch (currentInstruction & 0xF000 >> 12)
		{
		case ins::x00EN:
			if (nibble[3] == 0)
				// clear screen
				;
			else
				// Subroutine return
				;
			break;

		case ins::x1NNN:
			// Set PC to NNN
			break;


		}
	}
}

void CPU::Render(Display& disp, SDLI& sdli)
{
	while (timeKeeper.GetTime() < MILLISECONDS_PER_FRAME);

	if (delayTimer > 0)
		delayTimer--;
	if (soundTimer > 0)
		soundTimer--;

	disp.DrawBuffer(sdli);


	currentInstructionCount = INSTRUCTIONS_PER_FRAME;
	timeKeeper.Restart();
}