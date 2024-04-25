#include "ConsoleManip.h"

static void AddTwo(int (&a))
{
	a += 2;
}

#define PRINTLN(str) std::cout << str << '\n';
int main()
{
	ConsoleManip::Printf("hello\n", TEXT_RGB(255, 0, 0));
	
	return 0;
}
