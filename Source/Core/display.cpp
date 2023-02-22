#include "display.h"

Display::Display()
{
	// Initialize SDL and main window variables
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(-1);
	}
	
	window = SDL_CreateWindow("TEST :D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);

	windowHandler = utilities::getSDLWinHandle(window);
	utilities::ActivateMenu(windowHandler);

	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);

	// Enable WinAPI Events Processing
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

Display::~Display()
{
	
}

SDL_Window* Display::getWindow()
{
	return window;
}