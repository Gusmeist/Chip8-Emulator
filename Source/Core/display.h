#pragma once

#include "SDL.h"

#include "sdl_interface.h"

const int SCREEN_PIXEL_WIDTH = 64;
const int SCREEN_PIXEL_HEIGHT = 32;

struct Display
{
private:
	SDL_Rect pixel;
	SDL_Rect screenBackground;
	SDL_Rect screenBorder;

public:
	bool ScreenBuffer[SCREEN_PIXEL_WIDTH][SCREEN_PIXEL_HEIGHT] = { 0 };

	Display();
	~Display();

	void DrawBuffer(SDLI& SDLInterface);
};

