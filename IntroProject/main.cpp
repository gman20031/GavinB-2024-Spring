#include <iostream>
#include <windows.h>

#define CSR_MOVE_POSITION "%i;%iH" //Cursor moves to <x>; <y> coordinate within the viewport, where <x> is the column of the <y> line
#define VT_ESC "\x1b["

int main()
{
	for (int i = 0; i < 20; ++i)
	{
		std::cout << " 10 % " << i << " = " << (10 % i) << '\n';
	}

    return 0;
}