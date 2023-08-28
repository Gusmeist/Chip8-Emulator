#pragma once

#include <stdio.h>

using Byte = unsigned char;
using Word = unsigned short;

const int STACK_SIZE = 16;

struct Stack
{
private:
	Word data[STACK_SIZE];
	int stackPos;

public:
	Stack();
	~Stack();

	Word Pop();
	void Push(Word AddressToStore);

	void Reset();
};