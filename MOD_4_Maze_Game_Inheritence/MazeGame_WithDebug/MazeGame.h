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

	void Update();
	void PlayCurrentLevel();
	void GotoNextLevel();
	void GotoLastLevel();
	void GotoLevel(size_t index);
	bool PromptToKeepPLaying();
	void ResetGame();

public:
	Map* GetCurrentMapPointer() { return m_pCurrentMap; }

	//void FillMapsFromFolder(const std::string& folderPath) // automatically fills allmaps vector from folder
	void PushBackMap(Map* newMap);
	void Run();
};