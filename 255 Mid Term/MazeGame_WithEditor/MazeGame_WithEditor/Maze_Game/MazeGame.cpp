#include "MazeGame.h"
#include "Enemies.h"
#include "assert.h"
#include "../SharedGameFiles/Prompting.h"
#include "../SharedGameFiles/MapFileLoader.h"

void MazeGame::ResetGame()
{
	m_gameFinished = false;
	m_currentIndex = 0;
	m_pCurrentMap = m_pAllMaps.at(0);
}

void MazeGame::DeleteGame()
{
	ResetGame();
	m_pAllMaps.clear();
	m_playerCharacter.reset();
	m_pCurrentMap = nullptr;
}

////////////////////////////////////////////////////////////////////////
// uses Push_back to add a new map to the map Vector
////////////////////////////////////////////////////////////////////////
void MazeGame::PushBackMap(Map* newMap)
{
	m_pAllMaps.push_back(newMap);
	if (m_pCurrentMap == nullptr)
		m_pCurrentMap = newMap;
}

////////////////////////////////////////////////////////////////////////
// Runs the MazeGame
////////////////////////////////////////////////////////////////////////
void MazeGame::Run()
{
	if (m_pCurrentMap == nullptr)
	{
		//throw probably, but I forget how
		std::cout << "no map files loaded";
		return;
	}
	for(;;)
	{
		PlayCurrentLevel();
		m_pCurrentMap->Reset();
		GotoNextLevel();
		if (m_gameFinished)
		{
			if (PromptToKeepPLaying())
				ResetGame();
			else
				break;
		}
	}

}

////////////////////////////////////////////////////////////////////////
// Level chaning functions
////////////////////////////////////////////////////////////////////////

void MazeGame::GotoNextLevel()
{
	++m_currentIndex;
	if ((m_currentIndex+1) > m_pAllMaps.size())
	{
		m_gameFinished = true;
		return;
	}
	GotoLevel(m_currentIndex);
}

void MazeGame::GotoLastLevel()
{
	--m_currentIndex;
	GotoLevel(m_currentIndex);
}

void MazeGame::GotoLevel(size_t index)
{
	m_currentIndex = index;
	m_pCurrentMap = m_pAllMaps.at(index);
}

////////////////////////////////////////////////////////////////////////
// Helper functions for when a level is completed
////////////////////////////////////////////////////////////////////////

static char GetYesNo()
{
	char input = '\0'; 

	while (input != 'Y' and input != 'N')
	{
		input = (char)toupper(_getch());
	}
	return input;
}

bool MazeGame::PromptToKeepPLaying()
{
	std::cout << "would you like to keep playing? y/n";
	char input = GetYesNo();

	if (input == 'Y')
		return true;
	return false;
}

void MazeGame::PlayCurrentLevel()
{
	printf(VT_ESC CSR_SHOW_OFF);

	while (!m_pCurrentMap->Finished())
	{
		m_pCurrentMap->Draw();
		m_pCurrentMap->GetPlayer()->Update();
		m_pCurrentMap->Update();
		m_pCurrentMap->GetPlayer()->CheckCollisions();
	}
	printf(VT_ESC CSR_SHOW_ON);

}