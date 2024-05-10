#include "SimpleIO.h"

int CinIntegerInRange(int min, int max)
{
	auto checker = [min, max](int input) -> bool
		{
			return (input >= min && input <= max);
		};

	return GetInput<int>(checker);
}

