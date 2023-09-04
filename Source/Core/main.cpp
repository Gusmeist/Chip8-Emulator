
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
	
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// // // // // // // // // // //
	// Main loop for application  //
	// // // // // // // // // // //
	
	while(isRunning)
	{
		/*
		Original Keyboard Layout -

		1 2 3 C
		4 5 6 D
		7 8 9 E
		A 0 B F

		Mapped Modern Keyboard Layout -

		1 2 3 4
		Q W E R
		A S D F
		Z X C V
		*/

		cpu.relevantKeyStates['1'] = currentKeyStates[SDL_SCANCODE_1];
		cpu.relevantKeyStates['2'] = currentKeyStates[SDL_SCANCODE_2];
		cpu.relevantKeyStates['3'] = currentKeyStates[SDL_SCANCODE_3];
		cpu.relevantKeyStates['C'] = currentKeyStates[SDL_SCANCODE_4];
		cpu.relevantKeyStates['4'] = currentKeyStates[SDL_SCANCODE_Q];
		cpu.relevantKeyStates['5'] = currentKeyStates[SDL_SCANCODE_W];
		cpu.relevantKeyStates['6'] = currentKeyStates[SDL_SCANCODE_E];
		cpu.relevantKeyStates['D'] = currentKeyStates[SDL_SCANCODE_R];
		cpu.relevantKeyStates['7'] = currentKeyStates[SDL_SCANCODE_A];
		cpu.relevantKeyStates['8'] = currentKeyStates[SDL_SCANCODE_S];
		cpu.relevantKeyStates['9'] = currentKeyStates[SDL_SCANCODE_D];
		cpu.relevantKeyStates['E'] = currentKeyStates[SDL_SCANCODE_F];
		cpu.relevantKeyStates['A'] = currentKeyStates[SDL_SCANCODE_Z];
		cpu.relevantKeyStates['0'] = currentKeyStates[SDL_SCANCODE_X];
		cpu.relevantKeyStates['B'] = currentKeyStates[SDL_SCANCODE_C];
		cpu.relevantKeyStates['F'] = currentKeyStates[SDL_SCANCODE_V];
		
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