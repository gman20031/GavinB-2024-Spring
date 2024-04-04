#pragma once

#include <vector>
#include <filesystem>

#include "../SharedGameFiles/Vector2.h"
#include "Enemies.h"
#include "Player.h"
#include "../SharedGameFiles/MapFileLoader.h"
#include "MapRenderer.h"

class GameObject;
using GameObjectPtr = std::shared_ptr <GameObject>;

class Map
{
	// these are all friend classes to reduce the number of public functions I need.
	friend class Entity;
	friend class MapRenderer;
	friend class ToggleTile;

	using GameObject2dVector = std::vector<std::vector< GameObjectPtr>>;

	MapRenderer m_mapRenderer;
	MapRenderer::playerVision m_visionMode = MapRenderer::playerVision::kSquare;
	static constexpr int kdrawDistance = 4;

	GameObject2dVector m_mapVector;
	const MapInformation m_mapStruct;

	size_t m_mapWidth;
	size_t m_mapHeight;
	size_t m_mapLength;
	size_t m_switchesOn;
	size_t m_switchCount;
	int m_enemyCount;
	int m_enemyStartCount;

	Vector2 m_playerStart;
	std::shared_ptr<Player> m_playerCharacter;
	bool m_doorsUnlocked = false;
	bool m_mapFinished;

	bool FillMapVectorFromCString(char* mapCString);
	void EmplaceBackAndFill(char arrayCharacter, Vector2 mapVectorPosition);
	void UpdateDoorState();
	void InitMap(const MapInformation& mapStruct);
public:
	Map(const char* filePath);

	std::shared_ptr<Player> GetPlayer() const { return m_playerCharacter;}

	GameObjectPtr& at(Vector2 coordinatePair);
	void Draw();
	void Update();
	bool ReplaceObject(Vector2 objectLocation, ObjectChar identifierChar);
	bool ChangeObjectAt(Vector2 objectLocation, GameObjectPtr newObject);
	bool SwapObjects(Vector2 firstObject, Vector2 secondObject);
	void Reset();
	bool DoorsUnlocked() const { return m_doorsUnlocked; }
	bool Finished() const{ return m_mapFinished; }
	
	//debug stuff
	void WinLevel();
	void UnlockAllDoors();
	void ToggleDoors();
};