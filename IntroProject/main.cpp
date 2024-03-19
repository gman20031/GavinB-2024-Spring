#include <iostream>
#include <string>
#include <conio.h>
#include <cstdarg>


int main()
{
	srand(0);
	int directionInteger;

	for(int i = 0 ; i< 100 ; ++i)
	{
		directionInteger = rand() % (4);
		std::cout << directionInteger <<'\n';
	}


	return 0;

}


