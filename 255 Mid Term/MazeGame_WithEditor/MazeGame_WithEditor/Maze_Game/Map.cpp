#include "Map.h"

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <filesystem>

#include "DoorTiles.h"
#include "GameObjectFactory.h"

Map::Map(const char* filePath)
	:m_mapFinished(false)
	,m_mapStruct(MapFileLoader::CreateMapInformation(filePath))
{
	InitMap(m_mapStruct);
}

void Map::InitMap(const MapInformation& mapStruct)
{
	m_mapVector.clear();

	char* mapCString = mapStruct.m_charArray;
	m_mapHeight = mapStruct.m_height;
	m_mapLength = mapStruct.m_length;
	m_mapWidth = mapStruct.m_width;
	m_switchCount = mapStruct.m_switchCount;
	m_enemyCount = mapStruct.m_enemyCount;
	m_enemyStartCount = mapStruct.m_enemyCount;

	FillMapVectorFromCString(mapCString);
}

/////////////////////////////////////////////////////////
// Converting map files to the actual Map object
/////////////////////////////////////////////////////////
bool Map::FillMapVectorFromCString(char* mapCString)
{

	for (int y = 0; y < m_mapHeight; ++y)
	{
		m_mapVector.emplace_back();
		for (int x = 0; x < m_mapWidth; ++x)
		{
			int index = x + (y * (int)m_mapWidth);
			EmplaceBackAndFill(mapCString[index], { x,y });
		}
	}

	m_playerStart = m_playerCharacter->GetPosition();
	return true;
}

void Map::EmplaceBackAndFill(char arrayCharacter, Vector2 mapVectorPosition)
{
#define CREATE_OBJECT(index) GameObjectFactory::Create(static_cast<GameObjectType>(index))
	int x = mapVectorPosition.x;
	int y = mapVectorPosition.y;

	if (static_cast<GameObjectType>(arrayCharacter) == GameObjectType::kPlayer)
	{
		m_playerCharacter = std::make_shared<Player>();
		m_mapVector[y].emplace_back(m_playerCharacter);
	}
	else
	{
		m_mapVector[y].emplace_back(CREATE_OBJECT(arrayCharacter));
	}
	m_mapVector[y][x]->SetCurrentMapPointer(this);
	m_mapVector[y][x]->SetPosition(mapVectorPosition);
	//m_allObjects.emplace_back(m_mapVector[y][x]);
}
/////////////////////////////////////////////////////////
// Swaps two objects, also updating their positions
/////////////////////////////////////////////////////////
bool Map::SwapObjects(Vector2 firstPosition, Vector2 secondPosition)
{
	std::shared_ptr<GameObject> tempObject = at(firstPosition);
	
	auto& firstObject = at(firstPosition);
	auto& secondObject = at(secondPosition);

	firstObject->SetPosition(secondPosition);
	secondObject->SetPosition(firstPosition);

	at(firstPosition) = secondObject;
	at(secondPosition) = tempObject;

	return true;
}

/////////////////////////////////////////////////////////
// Deletes object at location and replaces with object
/////////////////////////////////////////////////////////
bool Map::ReplaceObject(Vector2 objectLocation, ObjectChar identifierChar)
{
	if (identifierChar == ObjectChar::kPlayer)
	{
		m_playerCharacter = std::make_shared<Player>();
		at(objectLocation) = m_playerCharacter;
	}
	else
		at(objectLocation) = GameObjectFactory::Create(identifierChar);

	at(objectLocation)->SetCurrentMapPointer(this);
	at(objectLocation)->SetPosition(objectLocation);
	return true;
}

/////////////////////////////////////////////////////////
// Sets the object at location to the newObject, nothing more
/////////////////////////////////////////////////////////
bool Map::ChangeObjectAt(Vector2 objectLocation, GameObjectPtr newObject)
{
	at(objectLocation) = newObject;
	return true;
}

/////////////////////////////////////////////////////////
// resets finished flag
// then hard reloads the map as if initialized new
/////////////////////////////////////////////////////////
void Map::Reset()
{
	m_mapFinished = false;
	InitMap(m_mapStruct);
}

void Map::Draw()
{
	using enum MapRenderer::playerVision;
	switch (m_visionMode)
	{
	case kSquare: m_mapRenderer.DrawSquare(kdrawDistance, this); break;
	//case kCircle: m_mapRenderer.DrawCircle(kdrawDistance, this); break;
	//case kToWall: m_mapRenderer.DrawToWall(this); break;
	case kFull:	  m_mapRenderer.DrawFull(this);	break;
	}
}

/////////////////////////////////////////////////////////
// Goes through every object to Update it
/////////////////////////////////////////////////////////
void Map::Update()
{
	GameObjectPtr object = nullptr;
	for (size_t y = 0; y < m_mapHeight; ++y)
	{
		for (size_t x = 0; x < m_mapWidth; ++ x)
		{
			object = m_mapVector[y][x];
			if (!object->IsPlayer())
			{
				if (!object->m_updated)
					object->Update();
				if (at(object->GetPosition()) == object)
					object->m_updated = true;
			}
		}
	}
	for (size_t y = 0; y < m_mapHeight; ++y)
	{
		for (size_t x = 0; x < m_mapWidth; ++x)
		{
			m_mapVector[y][x]->m_updated = false;
		}
	}

	UpdateDoorState();

}

void Map::UpdateDoorState()
{
	if (m_enemyCount == 0 and m_enemyStartCount != 0)
		m_doorsUnlocked = true;
	if(m_switchCount > 0)
	{
		if (m_switchesOn == m_switchCount)
			m_doorsUnlocked = true;
		if (m_switchesOn != m_switchCount and m_doorsUnlocked)
			m_doorsUnlocked = false;
	}
}

/////////////////////////////////////////////////////////
// Get reference to object at cordinates
/////////////////////////////////////////////////////////
GameObjectPtr& Map::at(Vector2 cordinates)
{
	cordinates.y = std::clamp(cordinates.y, 0, (int)(m_mapHeight));
	cordinates.x = std::clamp(cordinates.x, 0, (int)(m_mapWidth -1));
	return m_mapVector.at(cordinates.y).at(cordinates.x);
}

//////////////////////////////  Debug //////////////////////////////

///////////////////////////////////////////////////////////
// sets map finished to true
/////////////////////////////////////////////////////////
void Map::WinLevel()
{
	m_mapFinished = true;
}

/////////////////////////////////////////////////////////
// Unlocks every door on the map
/////////////////////////////////////////////////////////
void Map::UnlockAllDoors()
{
	m_playerCharacter->CollectKey();
}

/////////////////////////////////////////////////////////
// Toggles Doors on the map
/////////////////////////////////////////////////////////
void Map::ToggleDoors()
{
	if (m_playerCharacter->HasKey())
		m_playerCharacter->DropKey();
	else
		m_playerCharacter->CollectKey();
}

