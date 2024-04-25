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
	std::cout << VT_ESC << newColour;
	//printf(VT_ESC "%s" , newColour);
}

/////////////////////////////////////////////////////////////////////
// Replaces console with ' ' characters, then places cursor at 1,1
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ClearConsole()
{
	std::cout << VT_ESC << "1J" << VT_ESC << "0;0H";
	//printf(VT_ESC "1J"); // the Api says 2 should be used here, but 2J delets chars, not erase
	//printf(VT_ESC "0;0H"); // DOESNT START AT 0,0??
}

/////////////////////////////////////////////////////////////////////
// Changes the title of the console to the specified Title
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ChangeConsoleTitle(const char* newTitle)
{
	//printf(VT_CSI "2;%s\7", newTitle);
	std::cout << VT_CSI << "2;" << newTitle << "\7";
}


/////////////////////////////////////////////////////////////////////
// Draws the string to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::Printf(const char* output, const char* formatting)
{
	std::cout << VT_ESC << formatting << output << VT_ESC << TEXT_DEF;
}
/////////////////////////////////////////////////////////////////////
// Draws the char to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::Printf(const char output, const char* formatting)
{
	std::cout << VT_ESC << formatting << output << VT_ESC << TEXT_DEF;
}

/////////////////////////////////////////////////////////////////////
// Prints "press any key to continue..\n" then waits for user input
// input is then ignored and function closes.
/////////////////////////////////////////////////////////////////////
void ConsoleManip::Pause()
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