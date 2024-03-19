#include "Prompting.h"

#include <string>
#include <iostream>
#include <conio.h>
#include <initializer_list>
#include <limits.h>
#include <filesystem>
#include <vector>

//static void ResetCin()
//{
//	std::cin.clear();
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}

static void PrintPrompt(const std::string& prompt)
{
	std::cout << prompt << '\n';
}

std::string PromptAndGetString(const std::string& prompt)
{
	std::string input = "NULL";
	PrintPrompt(prompt);
	std::getline(std::cin, input);
	if(input == "\n" or input.empty())
		std::getline(std::cin, input);
	return input;
}

char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList)
{
	char input;
	for (;;)
	{
		PrintPrompt(prompt);
		input = (char)tolower(_getch());
		for (auto& it : charList )
		{
			if (input == tolower(it))
				return input;
		}
	}
}

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

//returns empty if file directory empty
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
//GetChar(AllowedChar, AllowdChar...)
//GetInteger(int min, int max)
