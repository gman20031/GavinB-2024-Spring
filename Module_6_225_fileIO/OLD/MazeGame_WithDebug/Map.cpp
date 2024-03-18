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
	char* mapCString = ConvertMapFileToCString(filePath);
	mapCString = CleanMapCString(mapCString);
	m_mapHeight = (int)m_mapLength / m_mapWidth;
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
#define CreateObject(index) GameObjectFactory::Create(static_cast<ObjectCharacter>(index))
	int x = mapVectorPosition.x;
	int y = mapVectorPosition.y;

	if (static_cast<ObjectCharacter>(arrayCharacter) == ObjectCharacter::kPlayer)
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

char* Map::ConvertMapFileToCString(const char* filePath)
{
	m_mapLength = std::filesystem::file_size(filePath);
	char* MapCString = static_cast<char*>(malloc(m_mapLength));

	std::fstream mapFile;
	mapFile.open(filePath);
	assert(mapFile.is_open());
	mapFile.get(MapCString, m_mapLength, EOF);
	mapFile.close();

	return MapCString;
}

char* Map::CleanMapCString(char* mapCString)
{
	constexpr char tab = '\t';
	constexpr char space = ' ';
	constexpr char endl = '\n';

	bool widthFound = false;
	size_t goodCharCount = 0;
	for (char* it = mapCString; *it != '\0'; ++it)
	{
		switch (*it)
		{
		case endl:
			if (!widthFound)
			{
				m_mapWidth = goodCharCount;
				widthFound = true;
			}
			[[fallthrough]];
		case tab:
			*it = space; 
			[[fallthrough]];
		case space:
			break;
		default:
			++goodCharCount;
			break;
		}
	}
	m_mapLength = goodCharCount;

	char* newMapCString = static_cast<char*>(malloc(m_mapLength + 1));
	assert(newMapCString != nullptr && m_mapLength > 0);
	newMapCString[m_mapLength] = '\0';
	size_t i = 0;
	for (char* it = mapCString; *it != '\0'; ++it)
	{
		if (*it != space)
		{
			newMapCString[i] = *it;
			++i;
		}
	}
	

	free(mapCString);
	return newMapCString;
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
			m_mapVector.at(y).at(x)->Draw();
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

