#pragma once

#include <time.h>
#include <random>

template<typename T>
concept G_Number = std::is_arithmetic_v<T>;

class G_Rand
{
private:
	static std::mt19937_64& MT64()
	{
		static std::mt19937_64 s_mt64(time(0) );
		return s_mt64;
	}

	static std::mt19937_64& SC64()
	{
		static std::mt19937_64 s_sc64(time(0) );
		return s_sc64;
	}

public:
	static uint64_t Mt_Rand(uint64_t min, uint64_t max);
	static uint64_t SC_Rand(uint64_t min, uint64_t max);
	static uint64_t C_Rand(uint64_t min, uint64_t max);
};
