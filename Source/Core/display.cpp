#include "display.h"

Display::Display()
{
	pixel.x = 0;
	pixel.y = 0;
	pixel.w = INIT_SCREEN_WIDTH / SCREEN_PIXEL_WIDTH;
	pixel.h = INIT_SCREEN_HEIGHT / SCREEN_PIXEL_HEIGHT;

	screenBackground.x = INIT_H_WINDOW_BORDER;
	screenBackground.y = INIT_V_WINDOW_BORDER;
	screenBackground.h = INIT_SCREEN_HEIGHT;
	screenBackground.w = INIT_SCREEN_WIDTH;

	screenBorder.x = screenBackground.x - 1;
	screenBorder.y = screenBackground.y - 1;
	screenBorder.w = screenBackground.w + 2;
	screenBorder.h = screenBackground.h + 2;
}

Display::~Display()
{
}

void Display::DrawBuffer(SDLI& sdli)
{
	SDL_SetRenderDrawColor(sdli.mainRenderer, 0x20, 0x20, 0x20, 0xFF);
	SDL_RenderClear(sdli.mainRenderer);

	SDL_SetRenderDrawColor(sdli.mainRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(sdli.mainRenderer, &screenBackground);

	SDL_SetRenderDrawColor(sdli.mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(sdli.mainRenderer, &screenBorder);

	SDL_SetRenderDrawColor(sdli.mainRenderer, 0x00, 0xAA, 0x00, 0x50);

	pixel.x = 0;
	pixel.y = 0;

	for (int i = 0; i < SCREEN_PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_PIXEL_HEIGHT; j++)
		{
			if (ScreenBuffer[i][j])
			{
				pixel.x = pixel.w * i + sdli.HWindowBorder;
				pixel.y = pixel.h * j + sdli.VWindowBorder;
				SDL_RenderFillRect(sdli.mainRenderer, &pixel);
			}
		}
	}

	SDL_RenderPresent(sdli.mainRenderer);
}