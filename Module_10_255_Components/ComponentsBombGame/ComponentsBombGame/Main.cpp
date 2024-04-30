 // Main.cpp
#include "Game/World.h"
#include <time.h>

int main()
{
	constexpr int kWorldWidth = 20;
	constexpr int kWorldHeight = 20;
	constexpr int kEnemyCount = 0;
	
	srand((unsigned int)time(nullptr));
	
	World world;
	// create the world
	world.Init(kWorldWidth, kWorldHeight);
	
	// create the player
	world.CreatePlayer();
	world.GenerateEnemies(kEnemyCount);
	
	// now that the player has been placed, generate the world
	world.GenerateWorld();
	
    // main game loop
    while (!world.IsGameOver())
    {
        world.Draw();
        world.Update();
    }

    return 0;
}

