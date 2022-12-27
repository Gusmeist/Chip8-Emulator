#ifndef H_MEMORY
#define H_MEMORY

#include <stdio.h>
#include <Windows.h>

class memory
{
public:
	memory(int size);

	~memory();

private:
	byte[] test;
};

#endif