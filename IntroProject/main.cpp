#include <iostream>
#include <conio.h>

enum class Direction
{
	kUp = 'w',
	kDown = 's',

};

int main(int argc, char* argv[])
{
	char input;

	for (;;)
	{
		input = _getch();
		std::cout << input;
	}

	return 0;
}// main end