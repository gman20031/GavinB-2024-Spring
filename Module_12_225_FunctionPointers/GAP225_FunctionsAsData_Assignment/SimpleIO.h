#pragma once

#include <iostream>
#include <type_traits>
#include <limits>
#include <functional>

//// unsure how to keep this inline with the function
//template<class T>
//concept Number = std::is_arithmetic_v<T>;

int CinIntegerInRange(int min, int max);
[[nodiscard]] float GetFloatInput();

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

template <class T>
static bool DefaultChecker([[maybe_unused]] T val) { return true; }

template <class Type>
Type GetInput()
{
	return GetInput<Type>(&DefaultChecker<Type>);
}