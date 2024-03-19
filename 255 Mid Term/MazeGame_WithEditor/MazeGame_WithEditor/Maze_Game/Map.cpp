#include "Map.h"

#include <assert.h>
#include <fstream>
#include <filesystem>

#include "GameObject.h"
#include "../SharedGameFiles/MapFileLoader.h"
#include "GameObjectFactory.h"

Map::Map(const char* filePath)
	:m_mapFinished(false)
{
	auto mapArray = MapFileLoader::ConvertToCString(filePath);
	char* mapCString =  mapArray.m_charArray;
	m_mapHeight = mapArray.m_height;
	m_mapLength = mapArray.m_length;
	m_mapWidth = mapArray.m_width;

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

	free(mapCString);
	m_playerStart = m_playerCharacter->GetPosition();
	return true;
}

void Map::EmplaceBackAndFill(char arrayCharacter, Vector2 mapVectorPosition)
{
#define CreateObject(index) GameObjectFactory::Create(static_cast<GameObjectType>(index))
	int x = mapVectorPosition.x;
	int y = mapVectorPosition.y;

	if (static_cast<GameObjectType>(arrayCharacter) == GameObjectType::kPlayer)
	{
		m_playerCharacter = std::make_shared<Player>();
		m_mapVector.at(y).emplace_back(m_playerCharacter);
	}
	else
	{
		m_mapVector.at(y).emplace_back(CreateObject(arrayCharacter));
	}
	m_mapVector.at(y).at(x)->SetCurrentMapPointer(this);
	m_mapVector.at(y).at(x)->SetPosition(mapVectorPosition);
	m_allObjects.emplace_back(m_mapVector.at(y).at(x));
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
// Resets player to start, resets finished flag
/////////////////////////////////////////////////////////
void Map::Reset()
{
	m_mapFinished = false;
	Vector2 currentPlayerPosition = m_playerCharacter->GetPosition();
	SwapObjects(currentPlayerPosition, m_playerStart);
}

/////////////////////////////////////////////////////////
// sets map finished to true
/////////////////////////////////////////////////////////
void Map::WinLevel()
{	
	m_mapFinished = true;
}

/////////////////////////////////////////////////////////
// Goes through every object to draw it to console
/////////////////////////////////////////////////////////
void Map::Draw()
{
	// THIS FUNCTION TAKES LIKE A THIRD SECOND TO COMPLETE
	// its probably a result of inheritance, all draw functions being virtual
	// must suck the life out of this somehow.

	// TODO: convert draw function to a renderer class,
	// this will allow for things like, chaning color, and not needing to inherit.

	system("cls");
	for (size_t y = 0 ; y < m_mapHeight; ++y)
	{
		for (size_t x = 0; x < m_mapWidth; ++x)
		{
			auto& object = m_mapVector.at(y).at(x);
			object->Draw();
			std::cout << ' ';
		}
		std::cout << '\n';
	}

}

/////////////////////////////////////////////////////////
// Goes through every object to Update it
/////////////////////////////////////////////////////////
void Map::Update()
{
	for (auto& entity : m_allObjects)
	{
		if(!entity->IsPlayer())
			entity->Update();
	}
}

/////////////////////////////////////////////////////////
// Get reference to object at cordinates
/////////////////////////////////////////////////////////
std::shared_ptr<GameObject>& Map::at(Vector2 cordinates)
{
	cordinates.y = std::clamp(cordinates.y, 0, (int)(m_mapHeight));
	cordinates.x = std::clamp(cordinates.x, 0, (int)(m_mapWidth -1));
	return m_mapVector.at(cordinates.y).at(cordinates.x);
}

