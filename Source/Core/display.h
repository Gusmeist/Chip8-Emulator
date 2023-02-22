#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>

#include "SDL.h"
#include "SDL_syswm.h"

#include "utilities.h"

class Display
{
private:
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Event mainEvent;
	HWND windowHandler;



public:
	
	
	Display();

	~Display();

	SDL_Window* getWindow();
};

#endif