#pragma once

#include <vector>
#include <filesystem>

#include "Vector2.h"
#include "Enemies.h"
#include "Player.h"

class GameObject;

class Map
{
	std::vector< std::shared_ptr<GameObject> > m_allObjects;
	std::vector<std::vector< std::shared_ptr<GameObject> > > m_mapVector;

	std::shared_ptr<Player> m_playerCharacter;

	size_t m_mapWidth;
	size_t m_mapHeight;
	size_t m_mapLength;
	Vector2 m_playerStart;
	bool m_mapFinished;

	bool FillMapVectorFromCString(char* mapCString);
	void EmplaceBackAndFill(char arrayCharacter, Vector2 mapVectorPosition);
public:
	Map(const char* filePath);

	size_t GetMapWidth() const { return m_mapWidth; }
	size_t GetMapHeight() const { return m_mapHeight; }
	std::shared_ptr<Player> GetPlayer() const { return m_playerCharacter;}
	std::vector<std::vector< std::shared_ptr<GameObject> > >& GetMapVector() { return m_mapVector; }

	std::shared_ptr<GameObject>& at(Vector2 coordinatePair);
	void Draw();
	void Update();
	bool SwapObjects(Vector2 firstObject, Vector2 secondObject);
	void Reset();
	void WinLevel();
	bool Finished() const{ return m_mapFinished; }
};