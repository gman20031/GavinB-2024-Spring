#include "Map.h"

#include <assert.h>
#include <fstream>
#include <filesystem>

#include "GameObject.h"
#include "GameObjectFactory.h"

Map::Map(const char* filePath)
{
	// take in file
	// convert file to cstring
	// clean the string of all ' ', '\n' and 'tabs'
	// convert cstring to GameObject vector

	char* mapCString = ConvertMapFileToCString(filePath);
	mapCString = CleanMapCString(mapCString);
	m_mapHeight = (int)m_mapLength / m_mapWidth;
	FillMapVectorFromCString(mapCString);
}

//bool Map::InitOtherMembers(char* mapCString)
//{
//	
//
//	
//}

bool Map::FillMapVectorFromCString(char* mapCString)
{
#define CreateObject(index) GameObjectFactory::Create(static_cast<ObjectCharacter>(index))

	for (size_t y = 0; y < m_mapHeight; ++y)
	{
		m_mapVector.emplace_back();
		for (size_t x = 0; x < m_mapWidth; ++x)	
		{
			size_t index = x + (y * 8);
			m_mapVector.at(y).emplace_back( CreateObject(mapCString[index]));
			if (m_mapVector.at(y).at(x)->m_displayCharacter == ObjectCharacter::kPlayer)
				m_playerStart = { (int)x,(int)y };
		}
	}


	return true;
}

char* Map::ConvertMapFileToCString(const char* filePath)
{
	m_mapLength = std::filesystem::file_size(filePath);
	char* MapCString = static_cast<char*>(malloc(m_mapLength));

	std::fstream mapFile;
	mapFile.open(filePath);
	assert(mapFile.is_open());
	mapFile.getline(MapCString, m_mapLength, '\0');
	mapFile.close();

	return MapCString;
}

char* Map::CleanMapCString(char* mapCString)
{
	constexpr char tab = '\t';
	constexpr char space = ' ';
	constexpr char endl = '\n';

	bool widthFound = false;
	int goodCharCount = 0;
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

	char* newMapCString = static_cast<char*>(malloc(m_mapLength));
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

// Write map onto the console.
void Map::Draw()
{
	system("cls");
	for (size_t y = 0 ; y < m_mapHeight; ++y)
	{
		for (size_t x = 0; x < m_mapWidth; ++x)
		{
			m_mapVector.at(y).at(x)->draw();
			std::cout << ' ';
		}
		std::cout << '\n';
	}

}

GameObject& Map::at(Vector2 cordinates)
{
	cordinates.y = std::clamp(cordinates.y, 0, (m_mapHeight));
	cordinates.x = std::clamp(cordinates.x, 0, (m_mapWidth -1));
	return *m_mapVector.at(cordinates.y).at(cordinates.x);
}

