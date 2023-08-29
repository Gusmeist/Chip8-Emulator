#pragma once

#include <stdio.h>
#include <SDL.h>

// Screen dimension constants
const int INIT_SCREEN_WIDTH = 640;
const int INIT_SCREEN_HEIGHT = 320;

struct SDLI
{
	SDL_Window* mainWindow = NULL;
	SDL_Renderer* mainRenderer = NULL;

	bool init();
	void close();
};