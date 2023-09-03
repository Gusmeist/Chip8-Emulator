
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
#include <vector>

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
	
	CPU cpu;
	bool isRunning = true;

	std::string filePath;
	std::ifstream inputFile;

	std::cout << "Enter file path: " << '\n';
	std::getline(std::cin, filePath);

	inputFile.open(filePath, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});

	cpu.Load(buffer);

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
				case (SDLK_1):
					std::cout << "yes" << std::endl;
					break;
			}
		}

		cpu.Process();
		cpu.Render(sdli);
	}

	// Closing operations
	sdli.close();
	return 0;
}