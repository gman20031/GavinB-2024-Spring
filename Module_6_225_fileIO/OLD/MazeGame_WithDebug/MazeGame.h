#pragma once

#include <conio.h>
#include <iostream>

#include "Map.h"
#include "Player.h"
#include "GameObject.h"

class MazeGame
{
private:
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
	void ResetGame();

	void PickMapToPlay();
public:
	Map* GetCurrentMapPointer() { return m_pCurrentMap; }

	//void FillMapsFromFolder(const std::string& folderPath) // automatically fills allmaps vector from folder
	void ClearMaps();
	void PushBackMap(Map* newMap);
	void Run();
};