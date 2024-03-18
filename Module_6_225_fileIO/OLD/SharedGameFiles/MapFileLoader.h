#pragma once

#include <string>
#include <filesystem>

struct mapCharArray
{
	char* m_charArray = nullptr;
	int m_width = -1;
	int m_height = -1;
	int m_length = -1;
};

class MapFileLoader
{
private:
	static char* ConvertMapFileToCString(const char* filePath);
	static char* CleanMapCString(char* mapCString, mapCharArray& output);

public:
	static mapCharArray ConvertToCString(const char* filePath);
	static mapCharArray ConvertToCString(const std::string& filePath);
};