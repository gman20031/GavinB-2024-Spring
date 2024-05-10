#pragma once

#include <iostream>
#include <type_traits>
#include <limits>
#include <functional>

int CinIntegerInRange(int min, int max);

template <class Type, class Checker> requires std::predicate<Checker, Type>
Type GetInput(Checker&& checker)
{
	Type input = {};

	std::cout << "\x1b[s"; // save cursor pos
	std::cin >> input;
	while ( (!checker(input)) || !std::cin.good())
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
	return GetInput<Type>( []( [[maybe_unused]] Type t ){return true;});
}