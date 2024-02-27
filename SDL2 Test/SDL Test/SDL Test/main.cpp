#include "SDL.h"

int main(int argc, char* argv[])
{
	const int WIDTH = 640; // Width for window
	const int HEIGHT = 480; // height for window
	SDL_Window* window = NULL; // the current window I am showing

	window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	bool keepWindowOpen = true;
	while (keepWindowOpen)
	{
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			switch (SdlEvent.type)
			{
			case SDL_QUIT:
				keepWindowOpen = false;
				break;
			}

			SDL_UpdateWindowSurface(window);
		}
	}

	return 0;
}
