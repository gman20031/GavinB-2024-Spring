
#include "Shapes.h"

#define ENABLE_TESTS 1

#ifdef ENABLE_TESTS

#include "Tests.h"

#endif

int main()
{

#ifdef ENABLE_TESTS
	RunTests();
#endif

	return 0;
}