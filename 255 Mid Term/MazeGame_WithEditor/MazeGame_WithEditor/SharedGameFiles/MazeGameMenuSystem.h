#pragma once

#include "../Maze_Game/MazeGame.h"
#include "../Editor/LevelEditor.h"

class MazeGameStartMenu
{
	LevelEditor m_editor;
	MazeGame m_game;
	Map* m_currentMap;

	void StartEditingMenu();
	void StartPlayingMenu();


	void PickMapToPlay();
public:
	MazeGameStartMenu();
	~MazeGameStartMenu() { delete m_currentMap; }

	void StartMazeGame();
};