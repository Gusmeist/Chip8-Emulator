#ifndef UTILITIES_H
#define UTILITIES_H

#include <Windows.h>

#include "SDL.h"
#include "SDL_syswm.h"

#define ID_LOADROM 1
#define ID_ABOUT 2
#define ID_EXIT 3
#define ID_CONTROLS 4

namespace utilities
{
	static HMENU hHelp;
	static HMENU hEdit;
	static HMENU hFile;
	static HMENU hMenuBar;

	//Function which retrieves the address/Handle of an SDL window
	//Also retrieves the specific subsystem used by SDL to create that window which is platform specific (Windows, MAC OS x, IOS, etc...)
	HWND getSDLWinHandle(SDL_Window* win);

	//Initializes the native windows drop down menu elements of the window
	void ActivateMenu(HWND windowRef);
}

#endif
