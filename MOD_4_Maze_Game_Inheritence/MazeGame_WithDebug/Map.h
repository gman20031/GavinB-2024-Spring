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
	std::shared_ptr<Player> m_playerCharacter;

	size_t m_mapWidth;
	size_t m_mapHeight;
	size_t m_mapLength;
	Vector2 m_playerStart;
	bool m_mapFinished;

	char* ConvertMapFileToCString(const char* filePath);
	char* CleanMapCString(char* mapCString);
	bool FillMapVectorFromCString(char* mapCString);
	void EmplaceBackAndFill(char arrayCharacter, Vector2 mapVectorPosition);
	//bool InitOtherMembers(char* mapCString);

	//swap objects

public:
	Map(const char* filePath);
	 
	//std::vector<std::shared_ptr <VerticalEnemy>  >& AllVerticalEnemies() { return m_allVerticalEnemies; }
	//std::vector<std::shared_ptr <HorizontalEnemy>>& AllHorizontalEnemies() { return m_allHorizontalEnemies; }
	//Vector2 GetPlayerStart() const { return m_playerStart;}

	size_t GetMapWidth() const { return m_mapWidth; }
	size_t GetMapHeight() const { return m_mapHeight; }
	std::shared_ptr<Player> GetPlayer() const { return m_playerCharacter;}
	std::vector<std::vector< std::shared_ptr<GameObject> > >& GetMapVector() { return m_mapVector; }


	std::shared_ptr<GameObject>& at(Vector2 coordinatePair);
	void Draw();
	bool SwapObjects(Vector2 firstObject, Vector2 secondObject);
	void Reset();
	void WinLevel();
	bool Finished() const{ return m_mapFinished; }
};