// Main.cpp
#include "World.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>

const int k_worldWidth = 20;
const int k_worldHeight = 20;

World* g_pWorld = nullptr;

int main()
{
	srand((unsigned int)time(nullptr));

	// create the world
	g_pWorld = new World;
	g_pWorld->Init(k_worldWidth, k_worldHeight);

	// create the player
	g_pWorld->CreatePlayer();

	// now that the player has been placed, generate the world
	g_pWorld->GenerateWorld();

    // main game loop
    while (!g_pWorld->IsGameOver())
    {
        g_pWorld->Draw();
        g_pWorld->Update();
    }

    delete g_pWorld;
    g_pWorld = nullptr;
    
    return 0;
}

