#include "ConsoleManip.h"

bool& ConsoleManip::VTEnabled()
{
	static bool vtEnabled = false;
	return vtEnabled;
}

void ConsoleManip::ChangeConsoleColour(int newColour)
{
	SetConsoleTextAttribute(s_outputHandle, static_cast<WORD>(newColour));
}

void ClearConsole()
{
	printf(VT_ESC "[2J");
	printf(VT_ESC "[0;0H");
}

void ConsoleManip::ChangeConsoleTitle(const char* newTitle) const
{
	printf("\x1b]2;%s\7", newTitle);
}

/// changes the colour of the console to 'consoleColour',
/// uses the leftshift operator to draw 'output' to std::cin,
/// changes console colour back to white
template<typename type>
void ConsoleManip::DrawColourToConsole(type output, int consoleColour)
{
	if (colour != CONSOLE_WHITE)
		ChangeConsoleColour(colour);

	std::cout << (output);

	if (colour != CONSOLE_WHITE)
		ChangeConsoleColour(CONSOLE_WHITE);
}

bool ConsoleManip::EnableVTMode()
{
	if (VTEnabled())
		return true;

	// Set output mode to handle virtual terminal sequences
	s_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(s_outputHandle, consoleMode))
	{
		return false;
	}

	VTEnabled() = true;
	return true;
}