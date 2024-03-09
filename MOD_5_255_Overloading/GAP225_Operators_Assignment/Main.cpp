#define UNIT_TEST_MODE 1

#include "Vector3.h"

#ifdef UNIT_TEST_MODE
#include "Tests.h"
#endif

int main()
{
#ifdef UNIT_TEST_MODE
	RunAllTests();
#endif

	return 0;
}