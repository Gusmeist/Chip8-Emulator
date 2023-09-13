#pragma once

#include <stdio.h>

using Byte = unsigned char;		// Declaration for a byte.
using Word = unsigned short;	// Declaration for a word (2 bytes).

const int STACK_SIZE = 16;		// The maximum amount of addresses to be stored in the stack.

struct Stack
{
private:
	Word data[STACK_SIZE];		// The stack data.
	int stackPos;				// The current highest position in the stack that is available.

public:
	Stack();							// Generic constructor and destructors.
	~Stack();

	Word Pop();							// Retrieve the top address, decrementing the stackPos.
	void Push(Word AddressToStore);		// Push an address to the top of the stack, incrementing the stackPos.

	void Reset();						// Set the stack to an initial state.
};