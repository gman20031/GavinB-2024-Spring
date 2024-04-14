#include <iostream>
#include <string>

#include "Vector3.h"

template<typename Type>
void Print(const Type& message);

template<typename Type>
void PrintArray(Type* pArray, const size_t size);

template<typename Type>
void Swap(Type& left, Type& right);

class foo
{
public:
	foo(int value) : m_value(value) {}
	int m_value;

};

class OverloadedFoo
{
public:
	OverloadedFoo(int value) : m_value(value) {}
	int m_value;

	friend std::ostream& operator<<(std::ostream& os , OverloadedFoo object)
	{
		os << object.m_value;
		return os;
	}

};

int main()
{
	std::cout << "Print Test\n";
	bool testBool = true;
	Print(testBool);

	char testChar = 'A';
	Print(testChar);

	int testInt = 5;
	Print(testInt);

	float testFLoat = 0.5;
	Print(testFLoat);

	std::string testString = "string";
	Print(testString);

	Vector3 testVector(1, 2, 3);
	Print(testVector);

	[[maybe_unused]] foo testFoo{ 1 };
	//Print(testFoo); //Doesnt compile : no operator << overloaded
	std::cout << "Print(testFoo); Doesnt compile : no operator << overloaded\n";

	OverloadedFoo testOverloadedFoo(1);
	Print(testOverloadedFoo);
	std::cout << "Print(testOverloadedFoo); compiles : operator << was overloaded\n";

	std::cout << "\nPrintArray Test\n";
	bool testBoolArray[2] = { true, false };
	PrintArray(testBoolArray , 2);

	char testCharArray[2] = { 'a','b' };
	PrintArray(testCharArray , 2);

	int testIntArray[2] = { 1,2 };
	PrintArray(testIntArray , 2);

	float testFLoatArray[2] = { 0.5 , 1.5 };
	PrintArray(testFLoatArray , 2);

	std::string testStringArray[2] = { "string" , "Baz" };
	PrintArray(testStringArray , 2);

	Vector3 testVectorArray[2] = { {1,2,3} , {4,5,6} };
	PrintArray(testVectorArray , 2);

	foo testFooArray[2] = { {1} , {5} };
	// PrintArray(testFooArray, 2); //Doesnt compile : no operator << overloaded
	std::cout << "PrintArray(testFooArray, 2); Doesnt compile : no operator << overloaded\n";

	OverloadedFoo testOverloadedFooArray[2] = { {1} , {5} };
	PrintArray(testOverloadedFooArray, 2);
	std::cout << "PrintArray(testOverloadedFoo); compiles : operator << was overloaded\n";

	std::cout << "\nSwap Test\n";
	bool testBoolTwo = false;
	Swap(testBool , testBoolTwo);

	char testCharTwo = 'B';
	Swap(testChar, testCharTwo);

	int testIntTwo = 10;
	Swap(testInt, testIntTwo);

	float testFLoatTwo = 2.f;
	Swap(testFLoat, testFLoatTwo);

	std::string testStringTwo = "Baz";
	Swap(testString, testStringTwo);

	Vector3 testVectorTwo(4, 5, 6);
	Swap(testVector, testVectorTwo);

	foo testFooTwo{ 5 };
	Swap(testFoo, testFooTwo); // Compiles because operator= is implicitly defaulted
	std::cout << "Swap(testFoo, testFooTwo); Compiles and works because operator= is implicitly defaulted\n";

	OverloadedFoo testOverloadedFoo2(5);
	Swap(testOverloadedFoo, testOverloadedFoo2); // Compiles and works because operator= is implicitly defaulted
	std::cout << "Swap(testOverloadedFoo, testOverloadedFoo2); Compiles and works because operator= is implicitly defaulted\n";

}

template<typename Type>
void Print(const Type& message)
{
	std::cout << message << '\n';
}

template<typename Type>
void PrintArray(Type* pArray, const size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << pArray[i] << ',';
	}
	std::cout << '\n';
}

template<typename Type>
void Swap(Type& left, Type& right)
{
	Type temp = left;
	left = right;
	right = temp;
}
