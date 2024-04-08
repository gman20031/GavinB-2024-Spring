#pragma once

#include <time.h>
#include <random>

class Random
{
	using engineType = std::default_random_engine;
	using result_type = engineType::result_type;

	static engineType& GetEngine()
	{
		static engineType engine;
		return engine;
	}


public:
	static result_type GetRandomInRange(result_type min, result_type max)
	{
		return min + GetEngine()() % (max - min + 1);
	}
};
