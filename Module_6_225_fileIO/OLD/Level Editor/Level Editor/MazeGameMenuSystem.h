#pragma once

class LevelEditor;
class MazeGame;

class MazeGameStartMenu
{
	LevelEditor* m_editor;
	MazeGame* m_game;

	void StartEditingMenu();
	void StartPlayingMenu();
public:
	MazeGameStartMenu();
	~MazeGameStartMenu();

	void StartMazeGame();
};