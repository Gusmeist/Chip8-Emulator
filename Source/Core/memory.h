#pragma once

#include "mystack.h"

// Custom typedefs for ease of reading/use
using Byte = unsigned char;
using Word = unsigned short;

struct Memory
{
	const int MEMORY_SIZE = 4 * 1024;

	const Word INIT_ADDRESS = 0x0200;
	const Word FONT_ADDRESS = 0x0050;

	Byte* Data = new Byte[MEMORY_SIZE];

	Stack stack;

	Memory();
	~Memory();

	void Reset();
};