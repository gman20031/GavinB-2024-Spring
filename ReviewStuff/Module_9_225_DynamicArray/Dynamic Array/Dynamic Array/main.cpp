#define TEST_MODE 1

#if TEST_MODE == 1
#include "Test.h"
#endif

#include "DynamicArray.h"
//#include "DynamicArray.cpp"

int main()
{
	DynamicArray<int> array(5);
	
#if TEST_MODE == 1
	TestIntegralDynamicArray<float>();
#endif

}


