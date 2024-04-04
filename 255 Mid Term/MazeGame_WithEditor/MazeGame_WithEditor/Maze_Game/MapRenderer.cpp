#include "MapRenderer.h"

#include "Map.h"
#include "../SharedGameFiles/ConsoleManip.h"
#include "../SharedGameFiles/Vector2.h"
#include "Player.h"
/////////////////////////////////////////////////////////////////////
// draws to the console a square of the map
// centered on the player, with a halfwidth specified
/////////////////////////////////////////////////////////////////////
void MapRenderer::DrawSquare(int halfWidth, Map* currentMap)
{
	ConsoleManip::ClearConsole();
	Vector2 playerPosition = currentMap->GetPlayer()->GetPosition();

	int startX = playerPosition.x - halfWidth;
	int startY = playerPosition.y - halfWidth;
	int endX = playerPosition.x + halfWidth;
	int endY = playerPosition.y + halfWidth;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;

	if (endX > currentMap->m_mapWidth)
		endX = (int)currentMap->m_mapWidth;
	if (endY > currentMap-> m_mapHeight)
		endY = (int)currentMap->m_mapHeight;

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			auto& object = currentMap->m_mapVector[y][x];
			printf(VT_ESC CSR_MOVE_POSITION, y + 1, x + 1); // the x,y positions start at 1,1???
			object->Draw();
		}
	}
}

//void MapRenderer::DrawCircle(int radius, Map* currentMap)
//{
//}
//
//void MapRenderer::DrawToWall(Map* currentMap)
//{
//}

/////////////////////////////////////////////////////////////////////
// clears the console then draws the entire map top to bottom.
/////////////////////////////////////////////////////////////////////
void MapRenderer::DrawFull(Map* currentMap)
{
	ConsoleManip::ClearConsole();
	for (size_t y = 0; y < currentMap->m_mapHeight; ++y)
	{
		for (auto& object : currentMap->m_mapVector[y])
		{
			object->Draw();
			//std::cout << ' ';
		}
		std::cout << '\n';
	}
}
