#include <iostream>
#include <utility>

static constexpr int* AllocateElements(int* pos, size_t count, int* pArray, int arraySizeStart)
{
	//AddElements(count); makes end point to end of array
	int newSize = arraySizeStart + count;
	int* test = new int[newSize];
	for (int i = 0; i < arraySizeStart; ++i)
	{
		test[i] = pArray[i];
	}
	delete[] pArray;
	pArray = test;
	int* end = pArray + newSize;

	for (int* it = end - 1; it != (pos + count - 1); --it)
	{
		*(it) = *(it - count);
	}

	return pArray;
}

int main()
{
	constexpr int size = 10;
	int* test = new int[size]{ 0,1,2,3,4,5,6,7,8,9 };

	int* pos = &test[3]; // points to 2
	AllocateElements(pos, 2, test, size);

	for (int i = 0; i < size + 2; ++i)
		std::cout << test[i];
	std::cout << '\n';
    return 0;
}