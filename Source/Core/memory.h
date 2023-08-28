#pragma once

#include "mystack.h"

// Custom typedefs for ease of reading/use
using Byte = unsigned char;
using Word = unsigned short;

struct Memory
{
	static const int MEMORY_SIZE = 4 * 1024;
	Byte* Data = new Byte[MEMORY_SIZE];

	Stack stack;

	Memory();
	~Memory();

	void Reset();
};