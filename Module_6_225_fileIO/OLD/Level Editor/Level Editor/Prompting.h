#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <initializer_list>
#include <limits.h>

static void PrintPrompt(const std::string& prompt);

const std::string& PromptAndGetString(const std::string& prompt);

char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList);

int PromptAndGetInteger(const std::string& prompt, int min, int max);

std::string ChooseFromFileDirectory(const std::string& directoryPath);

