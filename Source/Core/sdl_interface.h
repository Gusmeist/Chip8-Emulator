#pragma once

#include <stdio.h>
#include <SDL.h>

// Screen dimension constants
const int INIT_SCREEN_WIDTH = 640;
const int INIT_SCREEN_HEIGHT = 320;
const int INIT_V_WINDOW_BORDER = 110;
const int INIT_H_WINDOW_BORDER = 160;

struct SDLI
{
	SDL_Window* mainWindow = NULL;
	SDL_Renderer* mainRenderer = NULL;

	int ScreenWidth;
	int ScreenHeight;
	int VWindowBorder;
	int HWindowBorder;

	bool init();
	void close();
};