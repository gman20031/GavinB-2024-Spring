#include <iostream>
#include <string>
#include <conio.h>
#include <cstdarg>

char InitLISTPromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList)
{
	std::cout << prompt << '\n';
	for (auto it = charList.begin(); it != charList.end(); ++it)
	{
		std::cout << *it << '\n';
	}
	return '0';
}


int main()
{

	InitLISTPromptAndGetChar("hello", { 'a', 'b' });

	return 0;

}


