
#include <conio.h>
#include <fstream>

#include "Player.h"
#include "GameObject.h"
#include "Map.h"
#include "MazeGame.h"

// I want a timer class to figure out exactly why this is so slow
// 
//class PreciseTimer
//{
//	double counter = 0;
//
//public:
//
//	void StartTimer();
//	void StopTimer();
//	void PrintTimer();
//
//};

int main()
{
	//todo, just get all .map files from folder, 
	//order them sequentially
	Map mapp1("MapFiles/LEVEL_1.map");
	Map mapp2("MapFiles/LEVEL_2.map");

	MazeGame game;
	game.PushBackMap(&mapp1);
	game.PushBackMap(&mapp2);
	game.Run();
	
	return 0;
}