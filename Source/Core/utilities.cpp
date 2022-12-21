#include "utilities.h"

HWND utilities::getSDLWinHandle(SDL_Window* win)
{
    SDL_SysWMinfo infoWindow;
    SDL_VERSION(&infoWindow.version);
    if (!SDL_GetWindowWMInfo(win, &infoWindow))
    {
        return NULL;
    }
    return (infoWindow.info.win.window);
}

void utilities::ActivateMenu(HWND windowRef)
{
    // Initialize a menu for the main bar and each tab
    hMenuBar = CreateMenu();
    hFile = CreateMenu();
    hEdit = CreateMenu();
    hHelp = CreateMenu();

    // Add tabs to menu bar
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, L"File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelp, L"Help");

    // Add selections into each of the menus:
    // FILE
    AppendMenu(hFile, MF_POPUP, ID_LOADROM, L"Load ROM");
    AppendMenu(hFile, MF_STRING, ID_EXIT, L"Exit");

    // EDIT
    AppendMenu(hEdit, MF_STRING, ID_CONTROLS, L"Configure Controls");

    // HELP
    AppendMenu(hHelp, MF_STRING, ID_ABOUT, L"About");

    // Apply menu bar to window
    SetMenu(windowRef, hMenuBar);
}