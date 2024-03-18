#include "MapFileLoader.h"

#include <fstream>
#include <assert.h>

char* MapFileLoader::ConvertMapFileToCString(const char* filePath)
{
	int mapLength = (int)std::filesystem::file_size(filePath);
	char* MapCString = static_cast<char*>(malloc(mapLength));

	std::fstream mapFile;
	mapFile.open(filePath);
	assert(mapFile.is_open());
	mapFile.get(MapCString, mapLength, EOF);
	mapFile.close();

	return MapCString;
}

char* MapFileLoader::CleanMapCString(char* mapCString, mapCharArray& output)
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

mapCharArray MapFileLoader::ConvertToCString(const char* filePath)
{
	mapCharArray MapStruct;

	char* mapCString = ConvertMapFileToCString(filePath);
	MapStruct.m_charArray = CleanMapCString(mapCString, MapStruct);
	return MapStruct;
}


mapCharArray MapFileLoader::ConvertToCString(const std::string& filePath)
{
	const char* fileName = filePath.c_str();
	return ConvertToCString(fileName);
}
