#pragma once

#include <vector>
#include "cooridnatePair.h"
#include "Player.h"

class Player;

class Map
{
	std::vector<std::vector<char>> m_mapVector;
	int m_mapWidth;
	int m_mapHeight = 0;
	
	Player& m_playerCharacter;

public:
	static constexpr char k_wallCharacter = '#';
	static constexpr char k_exitCharacter = 'X';
	static constexpr char k_emptyCharacter = '.';
	
	
	Map(Player& playerCharacter,char* mapArray, int mapWidth);

	void DisplayMap();
	char& at(CooridinatePair coordinatePair);

};