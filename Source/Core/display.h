#pragma once

#include "SDL.h"

#include "sdl_interface.h"

const int SCREEN_PIXEL_WIDTH = 64;		// Constant pixel width of screen.
const int SCREEN_PIXEL_HEIGHT = 32;		// Constant pixel height of screen.

struct Display
{
private:
	SDL_Rect pixel;						// Rectangle for the size of a Chip8 pixel on the actual screen.
	SDL_Rect screenBackground;			// Rectangle for the background of the Chip8 screen.
	SDL_Rect screenBorder;				// Rectangle for the border of the Chip8 screen.

public:
	bool ScreenBuffer[SCREEN_PIXEL_WIDTH][SCREEN_PIXEL_HEIGHT] = { 0 };		// A screen buffer, used to hold the screen data before it is drawn.

	Display();																// Generic constructor and destructor.
	~Display();

	void DrawBuffer(SDLI& SDLInterface);									// Draws the buffer to the screen.

	void Reset();
};

