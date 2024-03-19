#pragma once

#include "time.h"
class Timing
{
	static constexpr bool randSeeded = false;
public:
	static bool SeedRandomWithTime()
	{
		if (!randSeeded)
			srand((unsigned int)time(0));
		return true;
	}
	static bool SeedRandomWith(unsigned int seed)
	{
		if (!randSeeded)
			srand(seed);
		return true;
	}

};