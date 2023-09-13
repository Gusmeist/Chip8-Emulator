#include "sdl_interface.h"

bool SDLI::init()
{
	mainWindow = SDL_CreateWindow("Chip8Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		ScreenWidth + HWindowBorder * 2, ScreenHeight + VWindowBorder * 2, SDL_WINDOW_SHOWN);

	if (mainWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mainRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(mainWindow);
		mainWindow = NULL;
		return false;
	}

	SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0x00);
	return true;
}

void SDLI::close()
{
	SDL_DestroyRenderer(mainRenderer);
	mainRenderer = NULL;

	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_Quit();
}