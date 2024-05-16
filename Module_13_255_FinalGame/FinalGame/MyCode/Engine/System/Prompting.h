#pragma once
#include <string>


std::string PromptAndGetString(const std::string& prompt);

char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList);

int PromptAndGetInteger(const std::string& prompt, int min, int max);

//returns empty if file directory empty
std::string ChooseFromFileDirectory(const std::string& directoryPath);
