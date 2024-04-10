// EndTile.cpp
#include "EndTile.h"
#include "World.h"
#include <iostream>

extern World* g_pWorld;  // let's us access a global variable declared in another CPP

void EndTile::Draw()
{
    std::cout << "H";
}

void EndTile::OnEnter([[maybe_unused]] Player* pPlayer)
{
    g_pWorld->EndGame();
}
