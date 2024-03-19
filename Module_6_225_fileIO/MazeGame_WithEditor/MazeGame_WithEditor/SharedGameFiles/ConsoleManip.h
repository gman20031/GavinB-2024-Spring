#pragma once
#include <Windows.h>
#include <iostream>

#define CONSOLE_RED 4
#define CONSOLE_WHITE 7

class ConsoleManip
{
	static const HANDLE& GetConsoleHandle()
	{
		static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		return consoleHandle;
	}
public:

	static void ChangeConsoleColour(int newColour)
	{
		SetConsoleTextAttribute(GetConsoleHandle(), static_cast<WORD>(newColour) );
	}

	template<typename type>
	static void DrawToConsole(type output, int colour = CONSOLE_WHITE)
	{
		if (colour != CONSOLE_WHITE)
			ChangeConsoleColour(colour);
		
		std::cout << (output);

		if (colour != CONSOLE_WHITE)
			ChangeConsoleColour(CONSOLE_WHITE);
	}
};
