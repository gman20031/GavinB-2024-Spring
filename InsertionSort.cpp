
void InsertionSort(int* sortedArray, int arrayLength)
{
	for (int* it = sortedArray + 1; it < sortedArray + arrayLength; ++it)
	{
		// compare current integer selected to all earlier integers
		for (int* subIt = it; subIt > sortedArray; --subIt)
		{	
			// If this is smaller than the integer before, swap it.
			if (*(subIt) < *(subIt - 1))
			{
				int temp = *subIt;
				*(subIt) = *(subIt - 1);
				*(subIt - 1) = temp;
			}
		}
	}
}