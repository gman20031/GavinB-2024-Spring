#pragma once
#include <vector>

size_t RemoveEvens(std::vector<int>& vector)
{
	size_t count = 0;
	for (auto it = vector.begin() ; it != vector.end();)
	{
		if (*it % 2 == 0)
		{
			it = vector.erase(it);
			++count;
		}
		else
			++it;
	}
	return count;
}

size_t AddZeroBeforOdd(std::vector<int>& vector)
{
	size_t count = 0;
	for (auto it = vector.begin(); it != vector.end(); ++it )
	{
		if (*it % 2 != 0)
		{
			it = vector.insert( it , 0);
			++count;
			++it;
		}
	}
	return count;
}