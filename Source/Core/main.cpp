
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
#include <cstring>

#include <vector>

#include <SDL.h>

#include "sdl_interface.h"

#include "memory.h"
#include "cpu.h"
#include "display.h"

int main(int argc, char* args[])
{
	// SDL Initialization and setup
	SDLI sdli;
	if (!sdli.init()) 
		return -1;
	
	// The CPU for the program.
	CPU cpu;

	// Variables for loading the file.
	std::string filePath;
	std::ifstream inputFile;

	std::cout << "\nEnter file name with the extension (Path assumes file is in the roms directory) - ";
	std::getline(std::cin, filePath);
	filePath = "roms\\" + filePath;

	// Load current file given to program.
	inputFile.open(filePath, std::ios::binary);

	// Copies all data into buffer, loads into memory.
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});
	cpu.Load(buffer);

	// Debug conditions
	cpu.steppingMode = false;	// Stops after each instruction, press key up to proceed to next instruction.

	// // // // // // // // // // //
	// Main loop for application  //
	// // // // // // // // // // //

	// Tracks if the program is still running.
	bool isRunning = true;
	bool isPaused = false;

	// The main event for the program, tracks if the application closed or resized.
	SDL_Event mainEvent;

	// Pointer to the keyboard states, later used to store the keyboard state into the program.
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
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

		// Sets each number of the chip8 keyboard state to the state of the emulated keyboard state of the physical keyboard.
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
		
		if (!isPaused)
		{
			// Runs when the program isn't paused.
			isRunning = cpu.Process();
			cpu.Render(sdli);
		}
		else
		{
			// Runs when the program is paused (Console commands).
			cpu.RenderNoTimers(sdli);
		}
		
		// Input logic
		while (SDL_PollEvent(&mainEvent))
		{
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
					case SDLK_ESCAPE:
						isPaused = !isPaused;
						break;
					case SDLK_0:
						cpu.steppingMode = !cpu.steppingMode;
						break;

				}
				break;
			}
		}
	}

	// Closing operations
	sdli.close();
	return 0;
}