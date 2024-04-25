#include "Console.h"

void ConsoleClear()
{
	printf("\x1b[1J");
	printf("\x1b[0;0H"); // DOESNT START AT 0,0??
}