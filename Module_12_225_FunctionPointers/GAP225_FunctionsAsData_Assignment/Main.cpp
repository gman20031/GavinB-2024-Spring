#include "Tasks.h"
#include "SimpleIO.h"

int main()
{
	bool quit = false;

	while (!quit)
	{
		system("cls");
		std::cout << "0 quit\n"
			<< "1 calculator\n"
			<< "2 Loop Test\n"
			<< "3 Vector Sort\n";

		int input = CinIntegerInRange(0, 3);

		switch (input)
		{
		case 0: quit = true;		break;
		case 1: CalculatorTesting(); break;
		case 2: RunLoopTesting();	break;
		case 3: VectorSortTesting(); break;
		}
	}

	

	return 0;
}