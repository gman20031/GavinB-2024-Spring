#include "Prompting.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <initializer_list>
#include <limits.h>
#include <filesystem>
#include <vector>

static void PrintPrompt(const std::string& prompt)
{
	std::cout << prompt << '\n';
}

/////////////////////////////////////////////////////////////////////
// Prints the given string then gets returns input string from user
/////////////////////////////////////////////////////////////////////
std::string PromptAndGetString(const std::string& prompt)
{
	std::string input = "NULL";
	PrintPrompt(prompt);
	std::getline(std::cin, input);
	if (input == "\n" or input.empty())
		std::getline(std::cin, input);
	return input;
}

/////////////////////////////////////////////////////////////////////
// Prints the prompt, then returns the next input from user matching
// the listed characters
/////////////////////////////////////////////////////////////////////
char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList)
{
	char input;
	for (;;)
	{
		PrintPrompt(prompt);
		input = (char)tolower(_getch());
		for (auto& it : charList)
		{
			if (input == tolower(it))
				return input;
		}
	}
}

/////////////////////////////////////////////////////////////////////
// Prints the prompt, then returns the next input from user between
// the minimum and maximum values
/////////////////////////////////////////////////////////////////////
int PromptAndGetInteger(const std::string& prompt, int min, int max)
{
	int input = 0;
	PrintPrompt(prompt);
	for (;;)
	{
		std::cin >> input;
		if (input >= min and input <= max and std::cin.good())
			return input;
	}
}

/////////////////////////////////////////////////////////////////////
// Prints out every file in the directory with numbers attached
// then asks user to pick one by typing a number
// returns the file the user specified
/////////////////////////////////////////////////////////////////////
std::string ChooseFromFileDirectory(const std::string& directoryPath)
{
	std::vector<std::string> allCurrentFiles;
	std::string chosenFile;

	for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		allCurrentFiles.emplace_back(entry.path().filename().string());
	}

	if (!allCurrentFiles.size() == 0)
	{
		size_t choiceCount = allCurrentFiles.size();
		for (size_t i = 0; i < choiceCount; ++i)
			std::cout << i << " : " << allCurrentFiles[i] << '\n';

		int input = PromptAndGetInteger("pick level", 0, (int)choiceCount - 1);
		chosenFile = allCurrentFiles[input];
	}
	return chosenFile;

}



//GetString(number of words wanted)
