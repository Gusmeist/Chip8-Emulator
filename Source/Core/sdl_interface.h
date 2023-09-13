#pragma once

#include <stdio.h>
#include <SDL.h>

const int INIT_SCREEN_WIDTH = 640;		// Screen dimension constants
const int INIT_SCREEN_HEIGHT = 320;
const int INIT_V_WINDOW_BORDER = 110;
const int INIT_H_WINDOW_BORDER = 160;

struct SDLI
{
	SDL_Window* mainWindow = NULL;		// Current window.
	SDL_Renderer* mainRenderer = NULL;	// Current renderer.

	int ScreenWidth;					// Custom vars for screen dimensions after resizing.
	int ScreenHeight;
	int VWindowBorder;
	int HWindowBorder;

	bool init();						// Initialize SDL and related things.
	void close();						// Delete SDL pointers and close everything.
};