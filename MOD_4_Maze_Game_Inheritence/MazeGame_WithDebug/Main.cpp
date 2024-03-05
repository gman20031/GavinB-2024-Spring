
#include <conio.h>
#include <fstream>

#include "Player.h"
#include "GameObject.h"
#include "Map.h"
#include "MazeGame.h"

int main(int argc, char* argv[])
{

	Map mappy("MapFiles/LEVEL_1.txt");

	MazeGame game;
	game.m_pCurrentMap = &mappy;
	
	game.Run();
	

	// make player
	// gameobject at player start = my player
	// player.move(direction)
	// map.atPosition(player+direction).interact with player
	// 

	return 0;
}
