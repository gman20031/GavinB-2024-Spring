// 0 = unit test mode
// 1 = interactive sandbox mode
#define MODE 1

#if(MODE == 0)
#include "Tests.h"
#elif(MODE == 1)
#include "DeckSandbox.h";
#endif

#include <random>
#include <time.h>

int main()
{
	srand((unsigned)time(nullptr));

#if(MODE == 0)
	RunAllTests();
#elif(MODE == 1)
	DeckSandbox sandbox;
	sandbox.Run();
#endif

	return 0;
}