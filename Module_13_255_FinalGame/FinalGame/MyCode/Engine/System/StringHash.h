#pragma once
#include <string>


// from eastl string.h 
constexpr uint32_t StringHash(const char* cString)
{
	// kPrime = 16777619;
	// kOffset = 2166136261U
	unsigned int character, result = 2166136261U; // They implement an FNV-like string hash.
	while ((character = *(cString++)) != '\0')
		result = (result * 16777619) ^ character;
	return (uint32_t)result;
}