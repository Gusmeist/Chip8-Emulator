#pragma once

#include "SDL.h"

struct TimeKeeper
{
private:
	Uint32 markedTime;

public:
	TimeKeeper();
	~TimeKeeper();

	Uint32 GetTime();
	void Restart();
};

