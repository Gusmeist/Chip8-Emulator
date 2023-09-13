#pragma once

#include "SDL.h"

struct TimeKeeper
{
private:
	Uint32 markedTime;		// A point in time to remember.

public:
	TimeKeeper();			// Generic constructor and destructor.
	~TimeKeeper();

	Uint32 GetTime();		// Get the time passed since markedTime.
	void Restart();			// Set the markedTime to the current time.
};

