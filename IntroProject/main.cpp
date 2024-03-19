#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <iostream>
#include <conio.h>

int main()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= -3;
    if (!SetConsoleMode(hOut, dwMode))
    {
        auto hello =  GetLastError();
    }

	// ESC ] 0; <string> <ST>
#define VT_ESC "\x1b["
#define VT_CSI "\x1b]"
#define VT_TITLE_START "2;"
#define VT_TITLE_END "\7"
	const char* newTitle = "yo mama so fat\0";

	//printf(VT_CSI VT_TITLE_START "%s" VT_TITLE_END, newTitle);
	//printf("\x1b]2;%s\7", newTitle);

	//printf(VT_ESC "2J"); // deletes every character in the window
	//printf(VT_ESC "2K"); // deletes every character in the Line
	//printf(VT_ESC "0;0H"); // cursor set to 0,0
	printf(VT_CSI"0; test\x07"); // changes the title of the cmd window

	printf("test\n");
	printf("test\n");
	printf("test\n");
	printf("\x1b[2J");
	//ESC[<y>; <x> H // for cursor positioning
	//SetCursorPos(0, 0);

#define VT_ESC "\x1b["
#define SET_CONSOLE_CURSOR(x,y) #x ";" #y "H"

	printf(VT_ESC "2J");
	printf(VT_ESC SET_CONSOLE_CURSOR(0, 0));
	


	for (;;)
	{
		std::cout << (char)_getch();
	}

    return 0;
}
