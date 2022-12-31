
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
#include <stack>

#include "SDL.h"
#include "SDL_syswm.h"

#include "utilities.h"
#include "memory.h"

int main(int argc, char* args[])
{
	// // // // // //
	// Set up SDL  //
	// // // // // //
	
	// Initialize control variables
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	
	SDL_Event mainEvent;
	
	HWND windowHandler;

	bool isRunning = true;
	int i;

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

	// // // // // // // // // // // //
	// Initialize system components	 //
	// // // // // // // // // // // //

	// Initialize timers
	uint8_t delayT = 0;
	uint8_t soundT = 0;

	uint16_t initialTicks = 0;
	uint16_t endTicks = 0;

	// Initialize objects
	Memory* RAM = new Memory(4 * KILOBYTE);
	
	std::stack<uint16_t> Stack;

	// Create font array
	uint8_t font[] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};


	// Store font in desired location, then delete original array
	i = 0x050;
	for (auto value: font)
	{
		RAM->write(i, value);
		i++;
	}

	// // // // // // // // // // //
	// Main loop for application  //
	// // // // // // // // // // //
	while(isRunning)
	{
		// Timer setup
		initialTicks = SDL_GetTicks();

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

		// Manage timers
		if (delayT > 0)
		{
			delayT--;
		}

		if (soundT > 0)
		{
			soundT--;
		}

		endTicks = SDL_GetTicks();

		if ((endTicks - initialTicks < SCREEN_TICKS_PER_FRAME) && isRunning)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - (endTicks - initialTicks));
		}
	}

	// Closing operations
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}