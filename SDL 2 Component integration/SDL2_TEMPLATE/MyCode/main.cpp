#include "SDL.h"

#include "Engine/SDL_integration\SpriteSDL.h"
#include "Game/World.h"
#include <time.h>
#include <filesystem>

int GameMain();

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const char* title = "Hello, world";
	constexpr int kXPosition = 200;
	constexpr int kYPosition = 200;
	constexpr int kWidth = 1500;
	constexpr int kHeight = 1500;

	constexpr int kWorldWidth = 20;
	constexpr int kWorldHeight = 20;
	constexpr int kEnemyCount = 0;
	srand((unsigned int)time(nullptr));

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return -1;
	auto pWindow = SDL_CreateWindow(
		title,
		kXPosition,
		kYPosition,
		kWidth,
		kHeight,
		SDL_WINDOW_OPENGL|
		SDL_WINDOW_MOUSE_CAPTURE |
		SDL_WINDOW_RESIZABLE);

	auto pRenderer = SDL_CreateRenderer(pWindow, NULL, NULL);
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);
	SDL_RenderClear(pRenderer);

	World world(pRenderer);
	// create the world
	world.Init(kWorldWidth, kWorldHeight);

	// create the player
	world.CreatePlayer();
	world.GenerateEnemies(kEnemyCount);

	// now that the player has been placed, generate the world
	world.GenerateWorld();

	while (!world.IsGameOver())
	{
		// main game loop
		world.Draw();
		world.Update();

		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_QUIT)
				world.EndGame();
		}
		SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
		SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
	}
	GameMain();
	return 0;
}

static int GameMain()
{


	return 0;
}