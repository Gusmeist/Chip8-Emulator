#include "utilities.h"

void utilities::ActivateMenu(HWND windowRef)
{
    hMenuBar = CreateMenu();
    hFile = CreateMenu();
    hEdit = CreateMenu();
    hHelp = CreateMenu();

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, L"File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelp, L"Help");

    AppendMenu(hFile, MF_STRING, ID_LOADROM, L"Load ROM");
    AppendMenu(hFile, MF_STRING, ID_EXIT, L"Exit");

    AppendMenu(hEdit, MF_STRING, ID_CONTROLS, L"Configure Controls");

    AppendMenu(hHelp, MF_STRING, ID_ABOUT, L"About");

    SetMenu(windowRef, hMenuBar);
}

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
