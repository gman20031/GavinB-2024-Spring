#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#define NO_DEBUG 1
#define DEBUG_MODE 2

#define RUN_MODE DEBUG_MODE
#include "Engine/Debug.h"


int main( [[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	const char* title = "Hello, world";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width = 500;
	constexpr int height = 500;

	assert ( SDL_Init(SDL_INIT_VIDEO) == 0);

	SDL_Window* pWindow = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, NULL , NULL);

	// hack to stay open
	bool keepRunning = true;
	while (keepRunning)
	{
		SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
		SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(pWindow);//honestly no idea
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if( SdlEvent.type == SDL_QUIT )
				keepRunning = false;
			
		}
	}
	return 0;
}

