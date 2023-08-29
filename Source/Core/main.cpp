
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
#include <stdint.h>
#include <fstream>
#include <string>

#include <SDL.h>

#include "sdl_interface.h"

#include "memory.h"
#include "cpu.h"
#include "display.h"

int main(int argc, char* args[])
{
	SDLI sdli;
	// SDL Initialization and setup
	if (!sdli.init()) 
		return -1;

	Memory mem;
	CPU cpu;
	Display disp(sdli);
	bool isRunning = true;

	std::string filePath;
	std::ifstream inputFile;
	Byte loadBuffer;

	SDL_Event mainEvent;

	// // // // // // // // // // //
	// Main loop for application  //
	// // // // // // // // // // //
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
		case SDL_KEYDOWN:
			switch (mainEvent.key.keysym.sym)
			{
				;
			}
		}

		cpu.Render(disp, sdli);
	}

	// Closing operations
	sdli.close();
	return 0;
}