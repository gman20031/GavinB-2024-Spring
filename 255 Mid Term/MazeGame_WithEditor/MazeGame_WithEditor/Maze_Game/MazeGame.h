#pragma once

#include <conio.h>
#include <iostream>

#include "Map.h"
#include "Player.h"

class MazeGame
{
private:
//  90% of this class is navigating between different maps that are loaded in. 
//  with the current iteration of maps being selected from a list, this is basically useless
//  but works perfectly from an old iteration, and will be used again if I had more time

	std::vector<Map*> m_pAllMaps;
	size_t m_currentIndex = 0;
	Map* m_pCurrentMap = nullptr;

	std::shared_ptr<Player> m_playerCharacter;
	bool m_gameFinished = false;
	bool m_levelFinished = false;

	void PlayCurrentLevel();
	void GotoNextLevel();			 
	void GotoLastLevel();			 // unused for now
	void GotoLevel(size_t index);    // unused for now
	bool PromptToKeepPLaying();

public:
	Map* GetCurrentMapPointer() { return m_pCurrentMap; }

	//void FillMapsFromFolder(const std::string& folderPath) // automatically fills allmaps vector from folder
	void ResetGame();
	void DeleteGame();
	void PushBackMap(Map* newMap);
	void Run();
};