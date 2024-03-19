#include "MazeGameMenuSystem.h"


#include "Prompting.h"
#include "MapFileLoader.h"
#include "../Maze_Game/Map.h"

static void DisplayIntro()
{
	std::cout << "Maze Game:\n"
		<< "0 : Play Levels\n"
		<< "1 : Edit Levels\n"
		<< "2 : Quit\n";
}

MazeGameStartMenu::MazeGameStartMenu()
	:m_editor()
	,m_game()
	,m_currentMap(nullptr)
{

}

void MazeGameStartMenu::StartEditingMenu()
{
	LevelEditor editor;

	std::cout <<
		"0 : edit existing\n"
	 << "1 : Create New\n"
	 << "2 : Go Back\n";

	int input = PromptAndGetInteger("Pick an option", 0, 2);
	system("cls");

	switch (input)
	{
	case 0:
		m_editor.Load();
		break;
	case 1:
		m_editor.Resize();
		break;
	default: return;
	}
	if(m_editor.IsRunning())
		m_editor.Run();
}

void MazeGameStartMenu::PickMapToPlay()
{
	const std::string directory = MapFileLoader::kdefaultFilePath;
	std::string fileName = ChooseFromFileDirectory(directory);
	std::string file = directory + fileName;
	m_currentMap = new Map(file.c_str());
	m_game.PushBackMap(m_currentMap);
}

void MazeGameStartMenu::StartPlayingMenu()
{
	PickMapToPlay();
	m_game.Run();
	m_game.ClearMaps();
	delete m_currentMap;
	m_currentMap = nullptr;
}

void MazeGameStartMenu::StartMazeGame()
{
	for(;;)
	{
		system("cls");
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