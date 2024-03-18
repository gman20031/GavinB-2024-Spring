#pragma once
#include <Windows.h>

#define CONSOLE_RED 4
#define CONSOLE_WHITE 7

class ConsoleManip
{
public:
	static void ChangeConsoleColour(int newColour)
	{
		static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(newColour) );
	}
};

/*
* 	static constexpr int kRedColor = 4;
	static constexpr int kStandarColor = 7;
* 
	void Button::DisplayTextselected() const
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(consoleHandle, Menu::kRedColor);
		std::cout << m_displayText;
		SetConsoleTextAttribute(consoleHandle, Menu::kStandarColor);
	}
*/