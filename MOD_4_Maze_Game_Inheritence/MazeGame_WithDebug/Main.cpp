#include <conio.h>
#include <iostream>

#include "Map.h"
#include "Player.h"
#include "Debugging.h"

int main()
{
#ifdef DEBUG
	DebugMenu debugMenu;
#endif
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

	Player playerCharacter;
	Map currentMap(map, mapWidth);
	playerCharacter.SetCurrentMapPointer(&currentMap);
	bool exitFound = false;

    while(!exitFound)
    {
		currentMap.DisplayMap();

#ifdef DEBUG
		debugMenu.DrawDebugMenu();
		if (playerCharacter.GetNoClipValue())
			std::cout << "no clip enabled";
#endif
        char input = _getch();

        switch (input)
        {
			DEBUG_MENU_CASES;
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
