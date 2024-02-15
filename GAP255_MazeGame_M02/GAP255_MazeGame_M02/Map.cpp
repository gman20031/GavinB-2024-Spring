
#include "Map.h"
//#include "Player.h"

#include <iostream>
#include <algorithm>
Map::Map(Player& playerCharacter,char* mapArray, int mapwidth = 8)
	:m_playerCharacter(playerCharacter)
	,m_mapWidth(mapwidth)
{
	playerCharacter.SetCurrentMap(this);

	char* mapPointer = mapArray;
	m_mapVector.emplace_back();

	for (int x = 0, y = 0; *mapPointer != '\0'; ++x)
	{
		if (x >= m_mapWidth)
		{
			x = 0;
			++y;
			++m_mapHeight;
			m_mapVector.emplace_back();
		}

		if (*mapPointer == m_playerCharacter.GetDisplayCharacter())
		{
			m_playerCharacter.setPosition({ x,y });
		}
	
		m_mapVector.at(y).push_back(*mapPointer);
		++mapPointer;
	}
}


/// <summary>
/// Write map onto the console.
/// </summary>
void Map::DisplayMap()
{
	system("cls");
	for (size_t y = 0 ; y < m_mapVector.size(); ++y)
	{
		for (size_t x = 0; x < m_mapVector.at(y).size(); ++x)
		{
			std::cout << m_mapVector.at(y).at(x) << ' ';
		}
		std::cout << '\n';
	}

}

/// <summary>
/// returns a reference to the desired character in the 2d vector
/// clamps arguements to nearest coordinate
/// </summary>
char& Map::at(CooridinatePair coordinatePair)
{
	coordinatePair.x = std::clamp(coordinatePair.x, 0, m_mapHeight);
	coordinatePair.y = std::clamp(coordinatePair.y, 0, m_mapWidth);
	return m_mapVector.at(coordinatePair.y).at(coordinatePair.x);
}
