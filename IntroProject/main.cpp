#include <iostream>

#include <unordered_map>
#include <windows.h>


int main()
{
	srand(0);

	for (int i = 0; i < 100; ++i)
	{
		std::cout << rand() % 2 << '\n';
	}

    return 0;
}