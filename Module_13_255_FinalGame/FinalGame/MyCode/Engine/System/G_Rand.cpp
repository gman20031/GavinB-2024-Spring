#include "G_Rand.h"

// returns value between min and max, inclusive
uint64_t G_Rand::Mt_Rand(uint64_t min, uint64_t max)
{
	return (MT64()() % (max + 1) ) + min;
}

// returns value between min and max, inclusive
uint64_t G_Rand::SC_Rand(uint64_t min, uint64_t max)
{
	return (SC64()() % (max + 1 ) ) + min;
}

// returns value between min and max, inclusive
uint64_t G_Rand::C_Rand(uint64_t min, uint64_t max)
{
	return (rand() % (max + 1) ) + min;
}
