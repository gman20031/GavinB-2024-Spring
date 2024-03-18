#include "MazeGameMenuSystem.h"

#include "../../SharedGameFiles/MazeGame.h"
#include "../../MazeGame_WithDebug/Map.h"
#include "Prompting.h"
#include "LevelEditor.h"

static void DisplayIntro()
{
	std::cout << "Maze Game:\n"
		<< "0 : Play Levels\n"
		<< "1 : Edit Levels\n";
}

MazeGameStartMenu::MazeGameStartMenu()
{
	m_editor = new LevelEditor;
	m_game = new MazeGame;
}

MazeGameStartMenu::~MazeGameStartMenu()
{
	delete m_editor;
	delete m_game;
}


void MazeGameStartMenu::StartEditingMenu()
{
	LevelEditor editor;

	std::cout <<
		"0 : edit existing\n"
	 << "1 : Create New'\n";

	int input = PromptAndGetInteger("Pick an option", 0, 2);
	system("cls");

	switch (input)
	{
	case 0:
		m_editor->Resize();
		break;
	case 1:
		m_editor->Load();
		break;
	default: return;
	}
	m_editor->Run();
}

void MazeGameStartMenu::StartPlayingMenu()
{
	m_game->Run();

	
}



void MazeGameStartMenu::StartMazeGame()
{
	for(;;)
	{
		DisplayIntro();
		int input = PromptAndGetInteger("Pick an option", 0, 2);
		system("cls");
		switch (input)
		{
		case 0:
			StartPlayingMenu();
			break;
		case 1:
			StartEditingMenu();
			break;
		case 2:
			return;
		default: break;
		}
	}

}