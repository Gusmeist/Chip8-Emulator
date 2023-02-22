#include "memory.h"

Memory::Memory(int size)
{
	uint8_t* _data = new uint8_t[size];
	data = _data;
	delete[] _data;

	int i = 0x050;
	for (auto value : fontData)
	{
		write(i, value);
		i++;
	}
}

Memory::~Memory()
{
	;
}

uint8_t Memory::read(uint16_t address)
{
	return data[(int)address];
}

void Memory::write(uint16_t address, uint8_t value)
{
	data[(int)address] = value;
}

void Memory::clear(uint16_t l_address, uint16_t u_address)
{
	for (int i = (int)l_address; i < (int)u_address; i++)
	{
		data[i] = 0;
	}
}

uint8_t* Memory::getData()
{
	return data;
}