
#include <conio.h>
#include <fstream>

#include "Player.h"
#include "GameObject.h"
#include "Map.h"
#include "MazeGame.h"

int main()
{
	Map mappy("MapFiles/LEVEL_1.txt");

	MazeGame game;
	game.PushBackMap(&mappy);
	
	game.Run();

	return 0;
}
