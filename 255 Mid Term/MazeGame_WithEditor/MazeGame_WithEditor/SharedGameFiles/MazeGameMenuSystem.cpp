#include "MazeGameMenuSystem.h"

#include <iostream>

#include "Prompting.h"
#include "MapFileLoader.h"
#include "../Maze_Game/Map.h"

/////////////////////////////////////////////////////////////////////
// Prints the intro sequence for the entire Game
/////////////////////////////////////////////////////////////////////
static void DisplayIntro()
{

	std::cout << "quick intro." << '\n'
	 << "you move around and naviagate menus with wasd" << '\n'
	 << "if you mistype something it will do nothing, waiting for a good response" << '\n'
	 << "e will interact with things in the level editor" << '\n'
	 << "8,9,0 are debug buttons you can cheat with in the game itself" << '\n'
	 << "thank you" << '\n';
	Pause();
	ConsoleManip::ClearConsole();
}

MazeGameStartMenu::MazeGameStartMenu()
	:m_game()
	,m_currentMap(nullptr)
{
	//
}

/////////////////////////////////////////////////////////////////////
// Prompts to either edit existing, create new, or go back
// then runs a level editor based on respone
/////////////////////////////////////////////////////////////////////
void MazeGameStartMenu::StartEditingMenu()
{
	LevelEditor editor;

	std::cout <<
		"0 : edit existing\n"
	 << "1 : Create New\n"
	 << "2 : Go Back\n";

	int input = PromptAndGetInteger("Pick an option", 0, 2);
	ConsoleManip::ClearConsole();

	switch (input)
	{
	case 0:
		editor.Load();
		break;
	case 1:
		editor.Resize();
		break;
	default: return;
	}
	if (editor.IsRunning())
		editor.Run();
}

/////////////////////////////////////////////////////////////////////
// Gets user to pick a map from the file directory to use
/////////////////////////////////////////////////////////////////////
void MazeGameStartMenu::PickMapToPlay()
{
	const std::string directory = MapFileLoader::kdefaultFilePath;
	std::string fileName = ChooseFromFileDirectory(directory);
	std::string file = directory + fileName;
	m_currentMap = new Map(file.c_str());
	m_game.PushBackMap(m_currentMap);
}


/////////////////////////////////////////////////////////////////////
// asks for map to play, then runs that map with m_game object
/////////////////////////////////////////////////////////////////////
void MazeGameStartMenu::StartPlayingMenu()
{
	PickMapToPlay();
	m_game.Run();
	m_game.DeleteGame();
	delete m_currentMap; // this should error?
	m_currentMap = nullptr;
}


/////////////////////////////////////////////////////////////////////
// asks user for what section of the game they want to go to,
// then runs the correct section, either playing or editing.
/////////////////////////////////////////////////////////////////////
void MazeGameStartMenu::StartMazeGame()
{
	DisplayIntro();
	//ConsoleManip::EnableVTMode();
	for(;;)
	{
		ConsoleManip::ClearConsole();
		std::cout << "Maze Game:\n"
			<< "0 : Play Levels\n"
			<< "1 : Edit Levels\n"
			<< "2 : Quit\n";
		int input = PromptAndGetInteger("Pick an option", 0, 2);
		ConsoleManip::ClearConsole();
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