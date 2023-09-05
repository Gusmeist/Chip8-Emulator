#include "cpu.h"

CPU::CPU()
{
	delayTimer = 0;
	soundTimer = 0;

	timeKeeper.Restart();

	currentInstructionCount = INSTRUCTIONS_PER_FRAME;

	PC = mem.INIT_ADDRESS;

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

void CPU::_1NNN(Word b)
{
	PC = b & 0x0FFF;
}

void CPU::_2NNN(Word b)
{
	mem.stack.Push(PC);
	PC = b & 0x0FFF;
}

void CPU::_3XNN(Byte n[])
{
	Byte val = (n[2] << 4) | n[3];
	if (val == V[n[1]])
		PC +=2;
}

void CPU::_4XNN(Byte n[])
{
	Byte val = (n[2] << 4) | n[3];
	if (val != V[n[1]])
		PC += 2;
}

void CPU::_5XY0(Byte n[])
{
	if (V[n[1]] == V[n[2]])
		PC += 2;
}

void CPU::_6XNN(Byte n[])
{
	Byte val = (n[2] << 4) | n[3];
	V[n[1]] = val;
}

void CPU::_7XNN(Byte n[])
{
	Byte val = (n[2] << 4) | n[3];
	V[n[1]] += val;
}

void CPU::_8XYN(Byte n[])
{
	Byte X = n[1];
	Byte Y = n[2];
	Word tmpResult;

	switch (n[3])
	{
		case 0x0:
			V[X] = V[Y];
			break;

		case 0x1:
			V[X] |= V[Y];
			break;

		case 0x2:
			V[X] &= V[Y];
			break;

		case 0x3:
			V[X] ^= V[Y];
			break;

		case 0x4:
			tmpResult = V[X] + V[Y];
			if (tmpResult > 0xFF)
				V[0xF] = 0x1;
			V[X] += V[Y];
			break;

		case 0x5:
			V[X] -= V[Y];
			V[0xF] = (V[X] > V[Y]);
			break;

		case 0x6:
			// optional V[X] = V[Y];
			V[0xF] = V[X] & 0b00000001;
			V[X] >>= 1;
			break;

		case 0x7:
			V[Y] -= V[X];
			V[0xF] = (V[Y] > V[X]);
			break;

		case 0xE:
			// optional V[X] = V[Y];
			V[0xF] = V[X] & 0b10000000;
			V[X] <<= 1;
			break;
	}
}

void CPU::_9XY0(Byte n[])
{
	if (V[n[1]] != V[n[2]])
		PC += 2;
}

void CPU::_ANNN(Word b)
{
	I = b & 0x0FFF;
}

void CPU::_BNNN(Word b)
{
	PC = V[0x0] + (b & 0x0FFF);
}

void CPU::_CXNN(Byte n[])
{
	V[n[1]] = (rand() % 0xFF) & ((n[3] << 4) | n[4]);
}

void CPU::_DXYN(Byte n[])
{
	Byte Y = V[n[2]] % SCREEN_PIXEL_HEIGHT;
	
	Byte rows = n[3];

	V[0xF] = 0b0;

	for (int i = 0; i < rows; i++)
	{
		Byte spriteByte = mem.Data[I + i];

		Byte X = V[n[1]] % SCREEN_PIXEL_WIDTH;

		for (int j = 0; j < 8; j++)
		{
			bool spriteBit = (spriteByte & (0b10000000 >> j));
			if(spriteBit)
				V[0xF] = 0b1;
			disp.ScreenBuffer[X][Y] = disp.ScreenBuffer[X][Y] ^ spriteBit;
			X++;
			if(X == SCREEN_PIXEL_WIDTH)
				break;
		}
		Y++;
		if(Y == SCREEN_PIXEL_HEIGHT)
			break;
	}
}

void CPU::_EXNN(Byte n[])
{
	if (n[3] == 1 && relevantKeyStates[V[n[1]]])
		PC += 2;
	else if (!relevantKeyStates[V[n[1]]])
		PC += 2;
}

void CPU::_FXNN(Byte n[])
{

}

void CPU::Load(std::vector<unsigned char> buffer)
{
	Word currentAddress = mem.INIT_ADDRESS;
	for (int i = 0; i < buffer.size(); i++)
	{
		mem.Data[currentAddress] = buffer[i];
		currentAddress++;
	}
}

void CPU::Process()
{
	while (currentInstructionCount > 0)
	{
		Word currentInstruction = (Word)(mem.Data[PC]) << 8;
		currentInstruction |= (Word)(mem.Data[PC + 1]);
		PC += 2;
		
		Byte nibble[4] = { 0 };

		nibble[0] = (currentInstruction & 0xF000) >> 12;
		nibble[1] = (currentInstruction & 0x0F00) >> 8;
		nibble[2] = (currentInstruction & 0x00F0) >> 4;
		nibble[3] = currentInstruction & 0x000F;

		switch ((currentInstruction & 0xF000) >> 12)
		{
		case ins::x00EN:
			_00EN(nibble);
			break;

		case ins::x1NNN:
			_1NNN(currentInstruction);
			break;

		case ins::x2NNN:
			_2NNN(currentInstruction);
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
			_ANNN(currentInstruction);
			break;

		case ins::xBNNN:
			_BNNN(currentInstruction);
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
		case ins::xFXNN:
			_FXNN(nibble);
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