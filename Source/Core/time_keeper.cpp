#include "time_keeper.h"

TimeKeeper::TimeKeeper()
{
	markedTime = SDL_GetTicks();
}

TimeKeeper::~TimeKeeper()
{
	;
}

Uint32 TimeKeeper::GetTime()
{
	return SDL_GetTicks() - markedTime;
}

void TimeKeeper::Restart()
{
	markedTime = SDL_GetTicks();
}