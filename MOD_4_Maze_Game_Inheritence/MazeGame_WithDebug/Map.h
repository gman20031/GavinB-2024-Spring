#pragma once

#include <vector>
#include <filesystem>

#include "Vector2.h"
#include "Enemies.h"
#include "Player.h"

class GameObject;

class Map
{
	std::vector<std::vector< std::shared_ptr<GameObject> > > m_mapVector;

	std::vector<std::shared_ptr<VerticalEnemy>> m_allVerticalEnemies;
	std::vector<std::shared_ptr<HorizontalEnemy>> m_allHorizontalEnemies;
	std::shared_ptr<Player> m_playerCharacter;

	size_t m_mapWidth;
	size_t m_mapHeight;
	size_t m_mapLength;
	Vector2 m_playerStart;

	char* ConvertMapFileToCString(const char* filePath);
	char* CleanMapCString(char* mapCString);
	bool FillMapVectorFromCString(char* mapCString);
	//bool InitOtherMembers(char* mapCString);

	//swap objects

public:
	Map(const char* filePath);
	 
	std::vector<std::shared_ptr <VerticalEnemy>  >& AllVerticalEnemies() { return m_allVerticalEnemies; }
	std::vector<std::shared_ptr <HorizontalEnemy>>& AllHorizontalEnemies() { return m_allHorizontalEnemies; }

	size_t GetMapWidth() const { return m_mapWidth; }
	size_t GetMapHeight() const { return m_mapHeight; }
	std::shared_ptr<Player> GetPlayer() const { return m_playerCharacter;}

	std::shared_ptr<GameObject>& at(Vector2 coordinatePair);
	void Draw();
	bool SwapObjects(Vector2 firstObject, Vector2 secondObject);

};