#include "display.h"

Display::Display(SDLI& sdli)
{
	pixel.x = 0;
	pixel.y = 0;
	pixel.w = INIT_SCREEN_WIDTH / SCREEN_PIXEL_WIDTH;
	pixel.h = INIT_SCREEN_HEIGHT / SCREEN_PIXEL_HEIGHT;
}

Display::~Display()
{
}

void Display::DrawBuffer(SDLI& sdli)
{
	SDL_SetRenderDrawColor(sdli.mainRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(sdli.mainRenderer);

	SDL_SetRenderDrawColor(sdli.mainRenderer, 0x00, 0xAA, 0x00, 0xFF);

	pixel.x = 0;
	pixel.y = 0;

	for (int i = 0; i < SCREEN_PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_PIXEL_HEIGHT; j++)
		{
			if (ScreenBuffer[i][j])
			{
				pixel.x = pixel.w * i;
				pixel.y = pixel.h * j;
				SDL_RenderFillRect(sdli.mainRenderer, &pixel);
			}
		}
	}

	SDL_RenderPresent(sdli.mainRenderer);
}