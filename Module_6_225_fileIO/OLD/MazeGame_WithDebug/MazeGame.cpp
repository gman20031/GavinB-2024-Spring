#include "MazeGame.h"
#include "Enemies.h"
#include "assert.h"
#include "../Level Editor/Level Editor/Prompting.h"


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
void MazeGame::PickMapToPlay()
{
	const std::string directory = "../../Map Files/";
	std::string fileName = ChooseFromFileDirectory(directory);
	std::string file = fileName + directory;
	Map chosenMap(file.c_str());
	PushBackMap(&chosenMap);
}

void MazeGame::ClearMaps()
{
	m_pAllMaps.clear();
}

void MazeGame::Run()
{
	PickMapToPlay();

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

	ClearMaps();
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

void MazeGame::ResetGame()
{
	m_gameFinished = false;
	m_currentIndex = 0;
	m_pCurrentMap = m_pAllMaps.at(0);
}

void MazeGame::PlayCurrentLevel()
{
	m_playerCharacter = m_pCurrentMap->GetPlayer();

	while (!m_pCurrentMap->Finished())
	{
		m_pCurrentMap->Draw();
		m_playerCharacter->Update();
		m_pCurrentMap->Update();
	}
}