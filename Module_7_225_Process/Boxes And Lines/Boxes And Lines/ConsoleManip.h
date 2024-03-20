#pragma once
#include <Windows.h>
#include <iostream>

#define VT_RED "38;2;255;0;0m"
#define VT_GREEN "38;2;0;255;0m"
#define VT_DEF "0m"

// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#define VT_ESC "\x1b["
#define VT_CSI "\x1b]"

#define TEXT_FORMAT(n) #n "M" //Set the format of the screen and text as specified by <n>


// https://vt100.net/docs/vt220-rm/chapter2.html#T2-4

class ConsoleManip
{
	static bool& VTEnabled();
	//static HANDLE s_outputHandle;

public:
	static void PrintInColor(const char*, const char* colorMacro);
	static void PrintInColor(const char, const char* colorMacro);

	static bool EnableVTMode();
	static void ChangeConsoleTitle(const char* newTitle);
};
