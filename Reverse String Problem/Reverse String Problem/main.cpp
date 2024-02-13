#include <iostream>

void ReverseString(char* str, int strLength);

int main(int argc, char* argv)
{
	constexpr int stringLength = 6;
	char string[stringLength] = "Hello";

	ReverseString(string, stringLength);

	std::cout << string << '\n';

	return 0;
}


void ReverseString(char* str, int strLength)
{
	char* endPointer = str;
	char* startPointer= str;

	endPointer += (strLength - 2);

	while (endPointer != startPointer)
	{
		str[strLength-1] = *startPointer;
		*startPointer = *endPointer;
		*endPointer = str[strLength-1];
		
		--endPointer;
		++startPointer;
	}
	str[strLength-1] = '\0';


	return;
}