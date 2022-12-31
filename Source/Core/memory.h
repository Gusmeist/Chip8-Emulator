#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <Windows.h>
#include <stdint.h>

class Memory
{
public:
	Memory(int size);

	~Memory();

	uint8_t read(uint16_t address);

	void write(uint16_t address, uint8_t value);

	void clear(uint16_t l_address, uint16_t u_address);

private:
	uint8_t* data;
};

#endif