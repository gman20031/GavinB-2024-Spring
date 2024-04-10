#include <iostream>
#include <vector>

#define TEST_MODE 1

#include "Unit.h"
#include "UnitFactory.h"
#include "Random.h"

#if TEST_MODE
#include "Testing.h"
#endif

int main()
{
	//Random::SeedWithTime();
#if TEST_MODE
	RunConsumablesTest();
	RunCreationTestSandbox();
#endif
    return 0;
}