#include <SDL.h>
#include <iostream>
#include <assert.h>


uint32_t CallbackFunction(uint32_t interval, void* param )
{
	std::cout << "le timer has gone off" << SDL_GetTicks() << '\n';

	return interval; // 0 means done
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const char* title = "Sprite Animation Test";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width		= 500;
	constexpr int height	= 500;

	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	assert(SDL_Init(SDL_INIT_TIMER) == 0);


	SDL_Window*   pWindow	= SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, NULL, NULL);

	uint32_t timingStart = SDL_GetTicks();

	auto id = SDL_AddTimer(1'000, CallbackFunction, nullptr);

	bool keepRunning = true;
	while(keepRunning)
	{
		SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
		SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(pWindow);//honestly no idea
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_QUIT)
				keepRunning = false;
		}
	}
	SDL_RemoveTimer(id);

	return 0;

}

