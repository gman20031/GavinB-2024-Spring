#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <initializer_list>
#include <limits.h>

static void PrintPrompt(const std::string& prompt)
{
	std::cout << prompt << '\n';
}

const std::string& PromptAndGetString(const std::string& prompt)
{
	PrintPrompt(prompt);
	static std::string input;
	std::getline(std::cin, input);
	return input;
}

char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList)
{
	char input;
	for(;;)
	{
		PrintPrompt(prompt);
		input = tolower((char)_getch());
		for (auto it = charList.begin(); it != charList.end(); ++it)
		{
			if (input == tolower(*it))
				return input;
		}
	}
}

int PromptAndGetInteger(const std::string& prompt, int min, int max)
{
	int input;
	PrintPrompt(prompt);
	for (;;)
	{
		std::cin.clear();
		std::cin >> input;
		if (input >= min and input <= max and std::cin.good() )
			return input;
	}
}


//GetString(number of words wanted)
//GetChar(AllowedChar, AllowdChar...)
//GetInteger(int min, int max)
