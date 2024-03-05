#pragma once

#include <conio.h>
#include <iostream>

#include "Map.h"
#include "Player.h"
#include "GameObject.h"

class MazeGame
{
private:
	std::vector<Map*> m_pAllMaps;

	std::shared_ptr<Player> m_playerCharacter;

	void StepAI();
	void MovePlayer();

public:
	Map* m_pCurrentMap;
	

	void PushBackMap(Map* newMap);

	void Run();
};