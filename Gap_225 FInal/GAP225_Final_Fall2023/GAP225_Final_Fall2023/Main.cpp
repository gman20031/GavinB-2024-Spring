#include <iostream>
#include "Game.h"

#include "Tasks.h"

static void PlayGame()
{
	Game game{ 8,8 };
	game.RunGameLoop();
}

void Tests()
{
	TestTaskOne();
	TestTaskFive();
	TestTaskSix();
}

int main()
{
	std::cout << "0   : play Game\n"
		<< "1   : Run Other Tests\n"
		<< "else : Quit\n";

	int input;
	std::cin >> input;
	switch (input) 
	{
	case 0: PlayGame(); break;
	case 1: Tests(); break;
	default: break;
	}



    return 0;
}