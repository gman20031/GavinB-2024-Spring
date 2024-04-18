#include "ConsoleManip.h"
#include "conio.h"

bool& ConsoleManip::VTEnabled()
{
	static bool vtEnabled = false;
	return vtEnabled;
}

/////////////////////////////////////////////////////////////////////
// Changes console color to the value specified
// TEXT_RGB macro to specify RGB values
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ChangeConsoleColour(const char* newColour)
{
	printf(VT_ESC "%s" , newColour);
}

/////////////////////////////////////////////////////////////////////
// Replaces console with ' ' characters, then places cursor at 1,1
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ClearConsole()
{
	printf(VT_ESC "1J");
	printf(VT_ESC "1;1H"); // DOESNT START AT 0,0??
}

/////////////////////////////////////////////////////////////////////
// Changes the title of the console to the specified Title
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ChangeConsoleTitle(const char* newTitle)
{
	printf(VT_CSI "2;%s\7", newTitle);
}


/////////////////////////////////////////////////////////////////////
// Draws the string to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::DrawToConsole(const char* output, const char* formatting)
{
	printf(VT_ESC "%s" "%s" VT_ESC TEXT_DEF, formatting, output);
}
/////////////////////////////////////////////////////////////////////
// Draws the char to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::DrawToConsole(const char output, const char* formatting)
{
	printf(VT_ESC "%s" "%c" VT_ESC TEXT_DEF, formatting, output);
}

/////////////////////////////////////////////////////////////////////
// Prints "press any key to continue..\n" then waits for user input
// input is then ignored and function closes.
/////////////////////////////////////////////////////////////////////
void Pause()
{
	std::cout << "press any key to continue..\n";
	[[maybe_unused]] int idk = _getwch();
}

/////////////////////////////////////////////////////////////////////
// Sets console mode to ENABLE_VIRTUAL_TERMINAL_PROCESSING;
/////////////////////////////////////////////////////////////////////
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