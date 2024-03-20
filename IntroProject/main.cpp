#include <iostream>
#include <conio.h>

void InsertionSort(int* sortedArray, int arrayLength)
{
	for (int* it = sortedArray + 1; it < sortedArray + arrayLength; ++it)
	{
		// compare current integer selected to all earlier integers
		for (int* subIt = it; subIt > sortedArray; --subIt)
		{
			if (*(subIt) < *(subIt-1))
			{
				int temp = *subIt;
				*(subIt) = *(subIt - 1);
				*(subIt - 1) = temp;
			}
		}
	}
}


int main()
{
	int sortableArray[] = { 3,5,6,7,1,3,6,1,0 };
	InsertionSort(sortableArray, 9);
	for (size_t i = 0 ; i < 9; ++i)
	{
		std::cout << sortableArray[i] << '\n';
	}
	for (;;)
	{
		std::cout << (char)_getch();
	}

    return 0;
}
