#pragma once

#include <vector>

#include "Debugging.h"

class Map
{
	std::vector<std::vector<char>> m_mapVector;
	int m_mapWidth;
	int m_mapHeight = 0;
	CooridinatePair m_playerStart;

public:
	static constexpr char k_wallCharacter = '#';
	static constexpr char k_exitCharacter = 'X';
	static constexpr char k_emptyCharacter = '.';
	static constexpr char k_playerCharacter = '@';

	Map(char* mapArray, int mapWidth);
	 
	int GetMapWidth() const { return m_mapWidth; }
	int GetMapHeight() const { return m_mapHeight; }

	void DisplayMap();
	char& at(CooridinatePair coordinatePair);

	CooridinatePair GetPlayerStart() const { return m_playerStart;	}
};