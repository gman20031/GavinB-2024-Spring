#pragma once
#include <Windows.h>
#include <iostream>

#define CONSOLE_RED 4
#define CONSOLE_WHITE 7

//https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#define VT_ESC "\x1b["
#define VT_CSI "\x1b]"

#define CSR_BLINKING_ON "?12h" 	 // Text Cursor Enable Blinking 
#define CSR_BLINKING_OFF "?12l"	 // Text Cursor Disable Blinking 
#define CSR_SHOW_ON "?25h"		 // Text Cursor Enable Mode Show 
#define CSR_SHOW_OFF "?25l"		 // Text Cursor Enable Mode Hide 

#define CSR_SHAPE(n) #n " q"
	#define CSR_SHAPE_DEF		  CSR_SHAPE(0) 	 //User Shape		
	#define CSR_SHAPE_BLINK_BLOCK CSR_SHAPE(1)	 //Blinking Block	
	#define CSR_SHAPE_STEAD_BLOCK CSR_SHAPE(2)	 //Steady Block 	
	#define CSR_SHAPE_BLINK_UNDER CSR_SHAPE(3)	 //Blinking Underlin
	#define CSR_SHAPE_STEAD_UNDER CSR_SHAPE(4)	 //Steady Underline 
	#define CSR_SHAPE_BLINK_BAR   CSR_SHAPE(5)	 //Blinking Bar 	
	#define CSR_SHAPE_STEAD_BAR   CSR_SHAPE(6)	 //Steady Bar

#define CSR_MOVE_UP(n)		#n "A" 	//Cursor up by <n>
#define CSR_MOVE_DOWN(n)	#n "B" 	//Cursor down by <n>
#define CSR_MOVE_FORWARD(n)	#n "C" 	//Cursor forward (Right) by <n>
#define CSR_MOVE_BACK(n)	#n "D" 	//Cursor backward (Left) by <n>
#define CSR_MOVE_LINEDOWN(n)#n "E" 	//Cursor down <n> lines from current position
#define CSR_MOVE_LINEUP(n)	#n "F" 	//Cursor up <n> lines from current position
#define CSR_MOVE_COLLUMN(n)	#n "G" 	//Cursor moves to <n>th position horizontally in the current line
#define CSR_MOVE_LINE(n)	#n "d" 	//Cursor moves to the <n>th position vertically in the current column
#define CSR_MOVE_POSITION(x,y) #x ";" #y "H" //Cursor moves to <x>; <y> coordinate within the viewport, where <x> is the column of the <y> line

#define VIEW_SCROLL_UP(n)	#n "SU" //Scroll text up by <n>. Also known as pan down, new lines fill in from the bottom of the screen
#define VIEW_SCROLL_DOWN(n) #n "SD" //Scroll down by <n>. Also known as pan up, new lines fill in from the top of the screen

#define TEXT_INSERT(n)		 #n "@"  //Insert <n> spaces at the current cursor position, shifting all existing text to the right. Text exiting the screen to the right is removed.
#define TEXT_DELETE(n)		 #n "P"  //Delete <n> characters at the current cursor position, shifting in space characters from the right edge of the screen.
#define TEXT_ERASE(n)		 #n "X"  //Erase <n> characters from the current cursor position by overwriting them with a space character.
#define TEXT_INESERT_LINE(n) #n "L"  //Inserts <n> lines into the buffer at the cursor position. The line the cursor is on, and lines below it, will be shifted downwards.
#define TEXT_DELETE_LINE(n)  #n "M"  //Deletes <n> lines from the buffer, starting with the row the cursor is on.
#define TEXT_ERASE_DISPLAY(n)#n "J"	 //Replace all text in the current viewport/screen specified by <n> with space characters
#define TEXT_ERASE_LINE(n)	 #n "K"	 //Replace all text on the line with the cursor specified by <n> with space characters
	#define TEXT_ERASE_DISPLAY_UNTIL  TEXT_ERASE_DISPLAY(0)  //0 erases from the current cursor position (inclusive) to the end of the line/display
	#define TEXT_ERASE_DISPLAY_FROM	  TEXT_ERASE_DISPLAY(1)	 //1 erases from the beginning of the line/display up to and including the current cursor position
	#define TEXT_ERASE_DISPLAY_ALL    TEXT_ERASE_DISPLAY(2)	 //2 erases the entire line/display
	#define TEXT_ERASE_LINE_UNTIL	  TEXT_ERASE_LINE(0)
	#define TEXT_ERASE_LINE_FROM	  TEXT_ERASE_LINE(1)
	#define TEXT_ERASE_LINE_ALL		  TEXT_ERASE_LINE(2)

#define TEXT_FORMAT(n) #n "M" //Set the format of the screen and text as specified by <n>

/*
0 		Default 					Returns all attributes to the default state prior to modification
1 		Bold/Bright 				Applies brightness/intensity flag to foreground color
22 		No bold/bright 				Removes brightness/intensity flag from foreground color
4 		Underline 					Adds underline
24 		No underline 				Removes underline
7 		Negative 					Swaps foreground and background colors
27 		Positive (No negative)	 	Returns foreground/background to normal
30 		Foreground Black 			Applies non-bold/bright black to foreground
31 		Foreground Red 				Applies non-bold/bright red to foreground
32 		Foreground Green 			Applies non-bold/bright green to foreground
33 		Foreground Yellow 			Applies non-bold/bright yellow to foreground
34 		Foreground Blue 			Applies non-bold/bright blue to foreground
35 		Foreground Magenta 			Applies non-bold/bright magenta to foreground
36 		Foreground Cyan 			Applies non-bold/bright cyan to foreground
37 		Foreground White 			Applies non-bold/bright white to foreground
38 		Foreground Extended 		Applies extended color value to the foreground (see details below)
39 		Foreground Default 			Applies only the foreground portion of the defaults (see 0)
40 		Background Black 			Applies non-bold/bright black to background
41 		Background Red 				Applies non-bold/bright red to background
42 		Background Green 			Applies non-bold/bright green to background
43 		Background Yellow 			Applies non-bold/bright yellow to background
44 		Background Blue 			Applies non-bold/bright blue to background
45 		Background Magenta 			Applies non-bold/bright magenta to background
46 		Background Cyan 			Applies non-bold/bright cyan to background
47 		Background White 			Applies non-bold/bright white to background
48 		Background Extended 		Applies extended color value to the background (see details below)
49 		Background Default 			Applies only the background portion of the defaults (see 0)
90 		Bright Foreground Black 	Applies bold/bright black to foreground
91 		Bright Foreground Red		Applies bold/bright red to foreground
92 		Bright Foreground Green 	Applies bold/bright green to foreground
93 		Bright Foreground Yellow 	Applies bold/bright yellow to foreground
94 		Bright Foreground Blue		Applies bold/bright blue to foreground
95 		Bright Foreground Magenta 	Applies bold/bright magenta to foreground
96 		Bright Foreground Cyan		Applies bold/bright cyan to foreground
97 		Bright Foreground White 	Applies bold/bright white to foreground
100 	Bright Background Black 	Applies bold/bright black to background
101 	Bright Background Red 		Applies bold/bright red to background
102 	Bright Background Green 	Applies bold/bright green to background
103 	Bright Background Yellow 	Applies bold/bright yellow to background
104 	Bright Background Blue 		Applies bold/bright blue to background
105 	Bright Background Magenta 	Applies bold/bright magenta to background
106 	Bright Background Cyan		Applies bold/bright cyan to background
107 	Bright Background White 	Applies bold/bright white to background
*/



//https://vt100.net/docs/vt220-rm/chapter2.html#T2-4

class ConsoleManip
{
	bool& VTEnabled();
	static HANDLE s_outputHandle;

	bool EnableVTMode();
public:
	void ChangeConsoleTitle(const char* newTitle) const;

	static void ChangeConsoleColour(int newColour);

	template<typename type>
	static void DrawColourToConsole(type output, int colour = CONSOLE_WHITE);
};
