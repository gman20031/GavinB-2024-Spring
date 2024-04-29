#include "CollectorGame.h"
#include "ConsoleManip.h"

int main()
{
	ConsoleManip::ChangeConsoleTitle("Inventory Test thing");
	CollectorGame game{ 8, 8 };
	game.Play();
	return 0;
}