#include "ConsoleManip.h"
#include "conio.h"

/////////////////////////////////////////////////////////////////////
// Changes console formatting to values given
// TEXT_RGB macro to specify RGB values
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ChangeConsoleFormatting(const char* newFormatting)
{
	m_pDefaultFormat = newFormatting;
	std::cout << VT_ESC << newFormatting;
}

/////////////////////////////////////////////////////////////////////
// Changes console formatting to default values
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ResetConsoleFormatting()
{
	m_pDefaultFormat = TEXT_DEF;
	std::cout << VT_ESC << TEXT_DEF;
}

/////////////////////////////////////////////////////////////////////
// Replaces console with ' ' characters, then places cursor at 1,1
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ClearConsole()
{
	std::cout << VT_ESC << "1J" << VT_ESC << "0;0H";
}


/////////////////////////////////////////////////////////////////////
// Calls  -- std::cout << VT_ESC << x << ";" << y << "H"; --
/////////////////////////////////////////////////////////////////////
void ConsoleManip::SetCursorPosition(int x, int y)
{
	std::cout << VT_ESC << x << ";" << y << "H";
}

/////////////////////////////////////////////////////////////////////
// Changes the title of the console to the specified Title
/////////////////////////////////////////////////////////////////////
void ConsoleManip::ChangeConsoleTitle(const char* newTitle)
{
	std::cout << VT_CSI << "2;" << newTitle << "\7";
}

/////////////////////////////////////////////////////////////////////
// Draws the string to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::Printf(const char* output, const char* formatting)
{
	Printf<const char*>(output, formatting);
}

/////////////////////////////////////////////////////////////////////
// Draws the char to the console with specified formatting
/////////////////////////////////////////////////////////////////////
void ConsoleManip::Printf(const char output, const char* formatting)
{
	Printf<const char>(output, formatting);
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
	return true;
}