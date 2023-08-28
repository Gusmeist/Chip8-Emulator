#pragma once

namespace sdli
{
	// I don't know why this works.
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	// Screen dimension constants
	const int INIT_SCREEN_WIDTH = 640;
	const int INIT_SCREEN_HEIGHT = 480;

	bool init()
	{
		mainWindow = SDL_CreateWindow("Chip8Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

	void close()
	{
		SDL_DestroyRenderer(mainRenderer);
		mainRenderer = NULL;

		SDL_DestroyWindow(mainWindow);
		mainWindow = NULL;

		SDL_Quit();
	}
};