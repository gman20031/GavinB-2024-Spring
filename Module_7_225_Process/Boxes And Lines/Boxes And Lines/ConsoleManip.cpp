#include "ConsoleManip.h"

void ClearConsole()
{
	printf(VT_ESC "[2J");
	printf(VT_ESC "[0;0H");
}

void ConsoleManip::ChangeConsoleTitle(const char* newTitle)
{
	printf("\x1b]2;%s\7", newTitle);
}

bool& ConsoleManip::VTEnabled()
{
	static bool vtEnabled = false;
	return vtEnabled;
}

bool ConsoleManip::EnableVTMode()
{
	if (VTEnabled())
		return true;

	// Set output mode to handle virtual terminal sequences
	static HANDLE s_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(s_outputHandle, consoleMode))
	{
		return false;
	}

	VTEnabled() = true;
	return true;
}

void ConsoleManip::PrintInColor(const char* output, const char* colorMacro)
{
	printf(VT_ESC "%s%s" VT_ESC VT_DEF, colorMacro, output);
}

void ConsoleManip::PrintInColor(const char output, const char* colorMacro)
{
	printf(VT_ESC "%s%c" VT_ESC VT_DEF, colorMacro, output);
}