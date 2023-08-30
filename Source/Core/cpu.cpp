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

void CPU::_00EN(Byte n[])
{
	// If the last nibble of the instruction, the command is meant to
	// clear the screen by setting all values to 0.
	if(n[3] == 0)
	{ 
		for (int i = 0; i < SCREEN_PIXEL_WIDTH; i++)
		{
			for (int j = 0; j < SCREEN_PIXEL_HEIGHT; j++)
			{
				disp.ScreenBuffer[i][j] = 0;
			}
		}
		return;
	}

	// Otherwise if the last nibble is not 0, it will set the PC to the top
	// item in the stack.

	PC = mem.stack.Pop();
}

void CPU::_1NNN(Byte n[])
{

}

void CPU::_2NNN(Byte n[])
{

}

void CPU::_3XNN(Byte n[])
{

}

void CPU::_4XNN(Byte n[])
{

}

void CPU::_5XY0(Byte n[])
{

}

void CPU::_6XNN(Byte n[])
{

}

void CPU::_7XNN(Byte n[])
{

}

void CPU::_8XYN(Byte n[])
{

}

void CPU::_9XY0(Byte n[])
{

}

void CPU::_ANNN(Byte n[])
{

}

void CPU::_BNNN(Byte n[])
{

}

void CPU::_CXNN(Byte n[])
{

}

void CPU::_DXYN(Byte n[])
{

}

void CPU::_EXNN(Byte n[])
{

}

void CPU::Process(Memory& mem)
{
	while (currentInstructionCount > 0)
	{
		Word currentInstruction = (Word)(mem.Data[PC]) << 8;
		currentInstruction |= (Word)(mem.Data[PC + 1]);
		PC += 2;
		
		Byte nibble[4] = { 0 };

		nibble[0] = currentInstruction & 0xF000 >> 12;
		nibble[1] = currentInstruction & 0x0F00 >> 8;
		nibble[2] = currentInstruction & 0x00F0 >> 4;
		nibble[3] = currentInstruction & 0x000F;

		switch (currentInstruction & 0xF000 >> 12)
		{
		case ins::x00EN:
			_00EN(nibble);
			break;

		case ins::x1NNN:
			_1NNN(nibble);
			break;

		case ins::x2NNN:
			_2NNN(nibble);
			break;

		case ins::x3XNN:
			_3XNN(nibble);
			break;

		case ins::x4XNN:
			_4XNN(nibble);
			break;

		case ins::x5XY0:
			_5XY0(nibble);
			break;

		case ins::x6XNN:
			_6XNN(nibble);
			break;

		case ins::x7XNN:
			_7XNN(nibble);
			break;

		case ins::x8XYN:
			_8XYN(nibble);
			break;

		case ins::x9XY0:
			_9XY0(nibble);
			break;

		case ins::xANNN:
			_ANNN(nibble);
			break;

		case ins::xBNNN:
			_BNNN(nibble);
			break;

		case ins::xCXNN:
			_CXNN(nibble);
			break;

		case ins::xDXYN:
			_DXYN(nibble);
			break;

		case ins::xEXNN:
			_EXNN(nibble);
			break;

		default:
			printf("Instruction unknown.");
		}

		currentInstructionCount--;
	}
}

void CPU::Render(SDLI& sdli)
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