#include <iostream>
#include <algorithm>

#include "Map.h"

Map::Map(char* mapArray, int mapwidth = 8)
	:m_mapWidth(mapwidth)
{


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

		if (*mapPointer == k_playerCharacter)
		{
			m_playerStart = {x,y};
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
	coordinatePair.x = std::clamp(coordinatePair.x, 0, (m_mapWidth -1));
	coordinatePair.y = std::clamp(coordinatePair.y, 0, (m_mapHeight));
	return m_mapVector.at(coordinatePair.y).at(coordinatePair.x);
}

