#include <SDL.h>

#include "Engine/SDL_integration\SpriteSDL.h"
#include "Game/World.h"
#include "Game/PlayerComponents.h"

#include <time.h>
#include <filesystem>


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const char* title = "Hello, world";
	constexpr int kXPosition = 100;
	constexpr int kYPosition = 100;
	constexpr int kWidth = 750;
	constexpr int kHeight = 750;

	constexpr int kWorldWidth = 20;
	constexpr int kWorldHeight = 20;
	constexpr int kEnemyCount = 2;
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
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(pRenderer);

	World world(pRenderer);
	// create the world
	world.Init(kWorldWidth, kWorldHeight);

	// create the player
	world.CreatePlayer();
	world.GenerateEnemies(kEnemyCount);

	// now that the player has been placed, generate the world
	world.GenerateWorld();

	bool playerMoved = false;
	SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
	world.Draw();
	world.Update();
	SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows


	while (!world.IsGameOver())
	{
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_QUIT)
				return 0;
			else if(SdlEvent.type == SDL_KEYUP)
			{
				world.GetPlayerPointer()->GetComponent<PlayerMover>()->HandleKeyInput(SdlEvent);
				playerMoved = true;
			}
		}

		if (playerMoved)
		{
			// main game loop
			SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
			world.Update();
			world.Draw();
			SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
			playerMoved = false;
		}

	}
	SpriteSDL finalSprite("Game/Sprites/FinalScreen.bmp", pRenderer);
	finalSprite.Render(0,0,nullptr,0,nullptr, SDL_FLIP_NONE);
	SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
	SDL_Event SdlEvent;
	bool end = false;
	while (!end)
	{
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_KEYUP)
				end = true;
		}
	}
	
	return 0;
}
