#include <iostream>
#include <algorithm>

#include "vector2.h"
#include "Map.h"

Map::Map(int mapwidth = 8)
	: m_mapWidth(mapwidth)
	, m_mapHeight(0)
	, m_playerStart{ 0,0 }
{

	//char* mapPointer = mapArray;
	//m_mapVector.emplace_back();

	//for (int x = 0, y = 0; *mapPointer != '\0'; ++x)
	//{
	//	if (x >= m_mapWidth)
	//	{
	//		x = 0;
	//		++y;
	//		++m_mapHeight;
	//		m_mapVector.emplace_back();
	//	}

	//	if (*mapPointer == (char)ObjectCharacters::kPlayer)
	//	{
	//		m_playerStart = {x,y};
	//	}

	//	//m_mapVector.at(y).push_back(*mapPointer);
	//	++mapPointer;
	//}
}

/// <summary>
/// Write map onto the console.
/// </summary>
void Map::DisplayMap()
{
	std::cout << "map\n";

	/*system("cls");
	for (size_t y = 0 ; y < m_mapVector.size(); ++y)
	{
		for (size_t x = 0; x < m_mapVector.at(y).size(); ++x)
		{
			std::cout << m_mapVector.at(y).at(x) << ' ';
		}
		std::cout << '\n';
	}*/

}

GameObject& Map::at(Vector2 cordinates)
{
	cordinates.y = std::clamp(cordinates.y, 0, (m_mapHeight));
	cordinates.x = std::clamp(cordinates.x, 0, (m_mapWidth -1));
	return *m_mapVector.at(cordinates.y).at(cordinates.x);
}

