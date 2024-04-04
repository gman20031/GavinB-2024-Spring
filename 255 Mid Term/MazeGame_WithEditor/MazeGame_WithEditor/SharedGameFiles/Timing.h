#pragma once

#include "time.h"
class Timing
{
	static constexpr bool randSeeded = false;
public:
	// calls srand with current time, wont run if already seeded
	static bool SeedRandomWithTime()
	{
		if (!randSeeded)
			srand((unsigned int)time(0));
		return true;
	}
	// calls srand with seed, wont run if already seeded
	static bool SeedRandomWith(unsigned int seed)
	{
		if (!randSeeded)
			srand(seed);
		return true;
	}

};