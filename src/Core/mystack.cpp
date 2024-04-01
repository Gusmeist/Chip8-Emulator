#include "mystack.h"

Stack::Stack()
{
	Reset();
}

Stack::~Stack()
{
	;
}

void Stack::Push(Word _Address)
{
	// If the address to access is above the STACK_SIZE,
	// stop push call.
	if (stackPos >= STACK_SIZE)
	{
		printf("Stack is full.");
		return;
	}

	// Store the incoming address to the current stack position,
	// then increment the stack position.
	data[stackPos] = _Address;
	stackPos++;
}

Word Stack::Pop()
{
	// If the address is less than 0, nothing to pop so it returns 0xFF
	// which is an invalid address in the chip8 address space.
	if (stackPos <= 0)
	{
		printf("Nothing to pop from stack.");
		return 0xFFFF;
	}

	// Decrement the stack pointer
	stackPos--;
	return data[stackPos];
}

void Stack::Reset()
{
	// Initialize stack data to 0.
	for (int i = 0; i < STACK_SIZE; i++)
	{
		data[i] = 0;
	}

	stackPos = 0;
}