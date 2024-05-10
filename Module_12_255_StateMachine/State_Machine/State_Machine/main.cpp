//#include <filesystem>
//#include "../ComponentsBombGame/Game/ActorFactory.h"

#include <iostream>
#include "Mario.h"

template <class Type, class Checker> requires std::predicate<Checker, Type>
Type GetInput(Checker&& checker)
{
	Type input = {};

	std::cout << "\x1b[s"; // save cursor pos
	std::cin >> input;
	while ((!checker(input)) || !std::cin.good())
	{
		std::cout << "\x1b[u" << "\x1b[0J"; // reset cursor and clear everything after.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	return input;
}

template <class Type>
Type GetInput()
{
	return GetInput<Type>([]([[maybe_unused]] Type t) {return true; });
}

int main()
{
	Mario mario;

	int input = 0;
	bool keepPlaying = true;
	while (keepPlaying)
	{
		system("cls");

		std::cout << "Pick option\n"
			<< "0: Quit\n"
			<< "1: Eat mushroom\n"
			<< "2: Eat Fire FLower\n"
			<< "3: Get Hit\n"
			<< "4: Action\n"
			<< "5: Description\n" << '\n';

		input = GetInput<int>(
			[](int in) -> bool 
			{
			return (in < 6 && in >= 0);
			}
		);

		switch (input)
		{
		case 0: keepPlaying = false; break;
		case 1: mario.EatMushroom(); break;
		case 2: mario.EatFireFlower(); break;
		case 3: mario.GetHit(); break;
		case 4: mario.DoAction(); break;
		case 5: mario.PrintDescription(); break;
		}
		keepPlaying = !mario.Dead();
		system("pause");
	}

	return 0;
}