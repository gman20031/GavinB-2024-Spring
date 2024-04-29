#include <conio.h>
#include <iostream>
#include <limits>

int main()
{

	std::cout << char(105);
	for (;;)
	{
		std::cout << (char)_getch() << '\n';
	}

	return 0;
} 