
/*
* 
*	
*		CHIP 8 EMULATOR MADE BY ME :D
* 
* 
* 
*/

#include <stdio.h>
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

	//std::cout << "Enter file path: " << '\n';
	//std::getline(std::cin, filePath);e
	{
		std::string debugRom = "C:\\Users\\knowl\\Downloads\\Tetris.ch8";
		filePath = debugRom;
	}
	

	inputFile.open(filePath, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});

	cpu.Load(buffer);

	cpu.steppingMode = false;

	SDL_Event mainEvent;

	TimeKeeper frameCounter;

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
		cpu.relevantKeyStates[0x1] = currentKeyStates[SDL_SCANCODE_1];
		cpu.relevantKeyStates[0x2] = currentKeyStates[SDL_SCANCODE_2];
		cpu.relevantKeyStates[0x3] = currentKeyStates[SDL_SCANCODE_3];
		cpu.relevantKeyStates[0xC] = currentKeyStates[SDL_SCANCODE_4];
		cpu.relevantKeyStates[0x4] = currentKeyStates[SDL_SCANCODE_Q];
		cpu.relevantKeyStates[0x5] = currentKeyStates[SDL_SCANCODE_W];
		cpu.relevantKeyStates[0x6] = currentKeyStates[SDL_SCANCODE_E];
		cpu.relevantKeyStates[0xD] = currentKeyStates[SDL_SCANCODE_R];
		cpu.relevantKeyStates[0x7] = currentKeyStates[SDL_SCANCODE_A];
		cpu.relevantKeyStates[0x8] = currentKeyStates[SDL_SCANCODE_S];
		cpu.relevantKeyStates[0x9] = currentKeyStates[SDL_SCANCODE_D];
		cpu.relevantKeyStates[0xE] = currentKeyStates[SDL_SCANCODE_F];
		cpu.relevantKeyStates[0xA] = currentKeyStates[SDL_SCANCODE_Z];
		cpu.relevantKeyStates[0x0] = currentKeyStates[SDL_SCANCODE_X];
		cpu.relevantKeyStates[0xB] = currentKeyStates[SDL_SCANCODE_C];
		cpu.relevantKeyStates[0xF] = currentKeyStates[SDL_SCANCODE_V];
		
		isRunning = cpu.Process();
		cpu.Render(sdli);

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
		}

		
	}

	// Closing operations
	sdli.close();
	return 0;
}