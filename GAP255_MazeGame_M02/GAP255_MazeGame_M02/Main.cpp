#include <conio.h>
#include <iostream>

#include "Map.h"
#include "Player.h"

int main()
{
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

	Player playerCharacter;
	Map currentMap(playerCharacter, map, mapWidth);
	bool exitFound = false;

    while(!exitFound)
    {
		currentMap.DisplayMap();

        char input = _getch();

        switch (input)
        {

        case 'q':
            return 0; 
        case 'w':
			exitFound = playerCharacter.MoveY(-1); break;
        case 's':
			exitFound = playerCharacter.MoveY(1); break;
		case 'a':
			exitFound = playerCharacter.MoveX(-1); break;
		case 'd':
			exitFound = playerCharacter.MoveX(1); break;
        }
    }

    return 0;
}
