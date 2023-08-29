#pragma once

#include "SDL.h"

#include "sdl_interface.h"

const int SCREEN_PIXEL_WIDTH = 64;
const int SCREEN_PIXEL_HEIGHT = 32;

struct Display
{
private:
	SDL_Rect pixel;

public:
	bool ScreenBuffer[SCREEN_PIXEL_WIDTH][SCREEN_PIXEL_HEIGHT] = { 0 };

	Display(SDLI& SDLInterface);
	~Display();

	void DrawBuffer(SDLI& SDLInterface);
};

