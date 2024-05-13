
#include <iostream>

//#define NO_VERBOUS_LOG

#include "VerboseLog.h"
#include "CodeGeneration.h"

class TestClass
{
	PRIVATE_VARIABLE_WITH_PUBLIC_GETTER_AND_SETTER(int,TestInt)

};
#include <cstring>

#define TestDefine(str) define str 1

int main(int argc, char* argv)
{
	VERBOSE_LOG("testLog");

	TestClass myTest;

	myTest.SetTestInt(24);

	std::cout << myTest.GetTestInt() << '\n';

}