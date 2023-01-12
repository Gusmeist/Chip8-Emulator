
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
#include <stdint.h>
#include <string>
#include <fstream>

#include "SDL.h"
#include "SDL_syswm.h"

#include "cpu.h"

int main(int argc, char* args[])
{

	CPU* _CPU = new CPU;
	
	bool isRunning = true;

	std::string filePath;
	std::ifstream inputFile;
	uint8_t loadBuffer;

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

		case SDL_SYSWMEVENT:
			if (mainEvent.syswm.msg->msg.win.msg == WM_COMMAND)
			{
				switch (LOWORD(mainEvent.syswm.msg->msg.win.wParam))
				{
				case ID_LOADROM:
					std::cout << "Enter file path for ROM: ";
					std::getline(std::cin, filePath);
					std::cout << '\n' << filePath;

					inputFile.open(filePath, std::ios::binary);
					while (inputFile.good())
					{
						loadBuffer = inputFile.get();
					}

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
	SDL_DestroyWindow(_CPU->screen->getWindow());
	SDL_Quit();
	return 0;
}