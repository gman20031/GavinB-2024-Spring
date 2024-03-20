#include "DotsAndBoxesGame.h"
#include <iostream>


int main(int argc, char argv[])
{
	argc; //unused
	argv; //unused

	DotsAndBoxesGame game;
	if (!game.Start())
		std::cout << "error starting game\n";

	return 0;
}





