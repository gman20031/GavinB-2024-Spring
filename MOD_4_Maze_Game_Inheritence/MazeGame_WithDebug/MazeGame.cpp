#include "MazeGame.h"
#include "Enemies.h"

void MazeGame::StepAI()
{
	for (auto& horizontalEnemy : m_pCurrentMap->AllHorizontalEnemies())
	{
		horizontalEnemy->Move();
	}

	for (auto& verticalEnemy : m_pCurrentMap->AllVerticalEnemies())
	{
		verticalEnemy->Move();
	}

}

void MazeGame::MovePlayer()
{
	char input = _getch();
	Direction dir = static_cast<Direction>(input);
	m_playerCharacter->Move(dir);
}

void MazeGame::PushBackMap(Map* newMap)
{
	m_pAllMaps.push_back(newMap);

}

void MazeGame::Run()
{
	m_playerCharacter = m_pCurrentMap->GetPlayer();

	for (;;)
	{
		m_pCurrentMap->Draw();
		MovePlayer();
	}
}
