#pragma once

#include <vector>
#include <filesystem>

#include "Vector2.h"

class GameObject;

class Map
{
	std::vector<std::vector< std::shared_ptr<GameObject> > > m_mapVector;

	int m_mapWidth;
	int m_mapHeight;
	size_t m_mapLength;
	Vector2 m_playerStart;

	char* ConvertMapFileToCString(const char* filePath);
	char* CleanMapCString(char* mapCString);
	bool FillMapVectorFromCString(char* mapCString);
	//bool InitOtherMembers(char* mapCString);

public:
	Map(const char* filePath);
	 
	int GetMapWidth() const { return m_mapWidth; }
	int GetMapHeight() const { return m_mapHeight; }

	void Draw();
	GameObject& at(Vector2 coordinatePair);

	Vector2 GetPlayerStart() const { return m_playerStart;	}
};