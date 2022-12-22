
/*
* 
*	
*		CHIP 8 EMULATOR MADE BY ME :D
* 
* 
* 
*/

#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "SDL.h"
#include "SDL_syswm.h"

#include "utilities.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// Initialize control variables
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	
	SDL_Event mainEvent;
	
	HWND windowHandler;

	bool isRunning = true;


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

	// Check if window failed
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(-1);
	}

	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(window);

	// Enable WinAPI Events Processing
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	// Main loop for application
	while(isRunning)
	{

		// Input logic
		SDL_PollEvent(&mainEvent);

		switch (mainEvent.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			mainEvent.type = SDL_QUIT;
			SDL_PushEvent(&mainEvent);
			break;

		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_SYSWMEVENT:
			if (mainEvent.syswm.msg->msg.win.msg == WM_COMMAND)
			{
				switch (LOWORD(mainEvent.syswm.msg->msg.win.wParam))
				{
				case ID_LOADROM:
					;
					break;

				case ID_CONTROLS:
					;
					break;

				case ID_ABOUT:
					;
					break;

				case ID_EXIT:
					isRunning = false;
					break;
				}
			}
		}
	}

	// Closing operations
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
