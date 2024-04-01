#pragma once

#include "mystack.h"

using Byte = unsigned char;		// Declaration for a byte.
using Word = unsigned short;	// Declatation for a word (2 bytes).

struct Memory
{
	const int MEMORY_SIZE = 4 * 1024;		// Memory size - 4KB.

	const Word INIT_ADDRESS = 0x0200;		// Initial PC address, first instruction to read.
	const Word FONT_ADDRESS = 0x0050;		// The address for the first byte in the font data.

	Byte* Data = new Byte[MEMORY_SIZE];		// The memory data, allocated as an array the size of the memory size.

	Stack stack;							// Stack for storing addresses.

	Memory();								// Generic constructor and destructor.
	~Memory();

	void Reset();							// Resets the memory to the initial state.
};