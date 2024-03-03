#include "MazeGame.h"

void MazeGame::Run()
{
	system("pause");
	char map[]{
		'#','#','#','#','#','#','#','#',
		'#','@','.','#','.','.','.','#',
		'#','#','.','.','.','#','.','#',
		'#','#','#','#','.','#','.','#',
		'#','X','.','#','.','#','.','#',
		'#','#','.','#','#','#','.','#',
		'#','#','.','.','.','.','.','#',
		'#','#','#','#','#','#','#','#',
		'\0'
	};
	constexpr int mapWidth = 8;



	Player playerCharacter({0,0}, (char)ObjectCharacters::kPlayer);
	Map currentMap(mapWidth);
	playerCharacter.SetCurrentMapPointer(&currentMap);
	bool exitFound = false;

	while (!exitFound)
	{
		currentMap.DisplayMap();

		//todo make this a function
		int input = static_cast<int>(_getch());

		switch (input)
		{
		case 'q':
			return;
		case 'w':
			exitFound = playerCharacter.Move(Direction::kUp); break;
		case 's':
			exitFound = playerCharacter.Move(Direction::kDown); break;
		case 'a':
			exitFound = playerCharacter.Move(Direction::kLeft); break;
		case 'd':
			exitFound = playerCharacter.Move(Direction::kRight); break;
		}
	}

	return;
}
