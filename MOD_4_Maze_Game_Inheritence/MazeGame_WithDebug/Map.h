#pragma once

#include <vector>

#include "Vector2.h"
#include "GameObject.h"

class GameObject;

class Map
{
	std::vector<std::vector< GameObject* > > m_mapVector;

	int m_mapWidth;
	int m_mapHeight;
	Vector2 m_playerStart;

public:
	Map(int mapWidth);
	 
	int GetMapWidth() const { return m_mapWidth; }
	int GetMapHeight() const { return m_mapHeight; }

	void DisplayMap();
	GameObject& at(Vector2 coordinatePair);

	Vector2 GetPlayerStart() const { return m_playerStart;	}
};