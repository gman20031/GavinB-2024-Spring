
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include <conio.h>

#include <fstream>

int main(int argc, char* argv[])
{

	Map mappy("MapFiles/LEVEL_1.txt");
	mappy.Draw();

	// make player
	// gameobject at player start = my player
	// player.move(direction)
	// map.atPosition(player+direction).interact with player
	// 

	return 0;
}
