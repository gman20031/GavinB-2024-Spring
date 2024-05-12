#pragma once

#include <iostream>

#if RUN_MODE == DEBUG_MODE
#define DEBUG 1
#endif



#ifdef DEBUG
#define DEBUG_PRINT(str) std::cout << str << '\n';

static void Test()
{
	std::cout << "test Run\n";
}

#else

#define DEBUG_PRINT(str) void

#endif  // DEBUG
