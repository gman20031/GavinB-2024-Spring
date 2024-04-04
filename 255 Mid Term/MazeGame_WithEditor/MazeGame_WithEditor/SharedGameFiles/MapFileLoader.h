#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include "../SharedGameFiles/Vector2.h"

/////////////////////////////////////////////////////////////////////
// Contains
//    m_charArray
//    m_switchCount
//    m_enemyCount
//    m_width
//    m_height
//    m_length
//  Free's m_charArray with dtor
/////////////////////////////////////////////////////////////////////
struct MapInformation
{
	char* m_charArray = nullptr;
	int m_switchCount = -1;
	int m_enemyCount = -1;
	int m_width = -1;
	int m_height = -1;
	int m_length = -1;
	~MapInformation()
	{
		free(m_charArray);
	}
};

class MapFileLoader
{
private:
	static char* ConvertMapFileToCString(std::fstream& fileStream, const char* filePath);
	static char* CleanMapCString(char* mapCString, MapInformation& output);
	static void FillPreInformation(MapInformation& mapCharArray, std::fstream& fileStream);

public:
	inline static constexpr char kdefaultFilePath[] = "Map Files/";

	static MapInformation CreateMapInformation(const char* filePath);
	static MapInformation CreateMapInformation(const std::string& filePath);
};