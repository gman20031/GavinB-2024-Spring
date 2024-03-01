#include <iostream>
#include <math.h>


int main(int argc, char* argv[])
{
	int const constant = 20;
	int _mutable = 10;

	//int* to const
	//int* pPointer = &constant; cannot target const ints with an int*
	const int* pPointerToConstInt = &constant;
	pPointerToConstInt = &_mutable;
	std::cout << *pPointerToConstInt << '\n';
	//(*pPointerToConstInt)++; // error: even though the target is mutable, because the pointer says it must be const, it behaves const.

	//pointer to const int*
	//int* const pConstPointerToInt = &constant; Error: cannot target constant ints with int*
	int* const pConstPointerToInt = &_mutable;
	(*pConstPointerToInt)++;
	std::cout << *pConstPointerToInt << '\n';

	// const* to const
	const int* const pConstantPointerToConstant = &constant;
	//pConstantPointerToConstant = &_mutable; //not allowed to retarget const <type> pointers
	//*pConstantPointerToConstant = 20; //not allowed

}// main end