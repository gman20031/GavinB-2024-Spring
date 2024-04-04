#include "MapFileLoader.h"

#include <assert.h>

/////////////////////////////////////////////////////////////////////
// Reads rest of file stream and returns it as a char*
/////////////////////////////////////////////////////////////////////
char* MapFileLoader::ConvertMapFileToCString(std::fstream& fileStream, const char* filePath)
{
	int mapLength = (int)std::filesystem::file_size(filePath);
	char* MapCString = static_cast<char*>(malloc(mapLength));

	fileStream.get(MapCString, mapLength, EOF);

	return MapCString;
}

/////////////////////////////////////////////////////////////////////
// Cleans a C string of any tabs, spaces, or newLines
// returns the resultant char*
// deallocates the given string
/////////////////////////////////////////////////////////////////////
char* MapFileLoader::CleanMapCString(char* mapCString, MapInformation& output)
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
				output.m_width = goodCharCount;
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
	output.m_length = goodCharCount;
	output.m_height = goodCharCount / output.m_width;

	char* newMapCString = static_cast<char*>(malloc(goodCharCount + 1));
	assert(newMapCString != nullptr && goodCharCount > 0);
	newMapCString[goodCharCount] = '\0';
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

/////////////////////////////////////////////////////////////////////
// Reads the information stored in the file before the map
/////////////////////////////////////////////////////////////////////
void MapFileLoader::FillPreInformation(MapInformation& mapStruct, std::fstream& fileStream)
{
	fileStream >> mapStruct.m_enemyCount;
	fileStream.ignore(1); // ignore space
	fileStream >> mapStruct.m_switchCount;
	fileStream.ignore(std::numeric_limits<int>::max() , '\n'); // ignore till I get to the new line
}

/////////////////////////////////////////////////////////////////////
// Takes a file path an returnsa MapInformation struct containing
//    m_charArray
//    m_switchCount
//    m_enemyCount
//    m_width
//    m_height
//    m_length
/////////////////////////////////////////////////////////////////////
MapInformation MapFileLoader::CreateMapInformation(const char* filePath)
{
	MapInformation mapStruct;

	std::fstream mapFile;
	mapFile.open(filePath);
	assert(mapFile.is_open());

	FillPreInformation(mapStruct, mapFile);
	char* mapCString = ConvertMapFileToCString(mapFile, filePath);
	mapStruct.m_charArray = CleanMapCString(mapCString, mapStruct);

	mapFile.close();
	return mapStruct;
}

/////////////////////////////////////////////////////////////////////
// Takes a file path an returnsa MapInformation struct containing
//    m_charArray
//    m_switchCount
//    m_enemyCount
//    m_width
//    m_height
//    m_length
/////////////////////////////////////////////////////////////////////
MapInformation MapFileLoader::CreateMapInformation(const std::string& filePath)
{
	const char* fileName = filePath.c_str();
	return CreateMapInformation(fileName);
}
