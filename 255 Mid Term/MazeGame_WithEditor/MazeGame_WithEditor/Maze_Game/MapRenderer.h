#pragma once
#include "GameObject.h"


class MapRenderer
{
	friend class Map;
private:
	enum class playerVision
	{
		kFull,
		kSquare,
		//kCircle,
		//kToWall,
	};
public:
	void DrawSquare(int halfWidth, Map* currentMap);
	//void DrawCircle(int radius, Map* currentMap);
	//void DrawToWall(Map* currentMap);
	void DrawFull(Map* currentMap);

};
