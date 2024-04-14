#pragma once

#define TEST_ARRAY 1

#include "DynamicArray.h"
#include <iostream>

static int g_testCount = 0;
static int g_passedTests = 0;

void Test(const char* pTestName, bool test)
{
	++g_testCount;
	if (test)
		++g_passedTests;
	std::cout << pTestName << ": " << (test ? "SUCCESS" : "FAILURE") << std::endl;
}

template <typename T>
bool AreSame(DynamicArray<T>* pDynamicArray , std::initializer_list<T> list)
{
	if (list.size() != pDynamicArray->GetSize())
		return false;
	int i = 0;
	for (const T& object : list)
	{
		if (object != (*pDynamicArray)[i] )
			return false;
		++i;
	}
	return true;
}

template <typename T>
bool AreSame( T* pArray1 , size_t array1Size, T* pArray2, size_t array2Size)
{
	if (array1Size != array2Size)
		return false;
	for (int i = 0; i < array1Size; ++i)
	{
		if (pArray1[i] != pArray2[i])
			return false;
	}
	return true;
}

template <typename T>
bool AreSame(T* pArray1, size_t array1Size, std::initializer_list<T> list)
{
	if (list.size() != array1Size)
		return false;
	int i = 0;
	for (const T& object : list)
	{
		if (object != pArray1[i])
			return false;
		++i;
	}
	return true;
}

template <typename TestType = int>
//using TestType = int;
void TestIntegralDynamicArray()
{

#if 1
	// default ctor
	std::cout << "Constructor tests\n";
	DynamicArray<TestType> testDefaultCtor;
	Test("default ctor size = 0", testDefaultCtor.GetSize() == 0);
	Test("default ctor capacity = 1", testDefaultCtor.GetCapacity() == 1);
	Test("default ctor Get(0) = 0", testDefaultCtor.Get(0) == 0);
	DynamicArray<TestType> testCtorStartSize(5);
	Test("constructor (5) size = 0", testCtorStartSize.GetSize() == 0);
	Test("constructor (5) capcaity = 5", testCtorStartSize.GetCapacity() == 5);
	Test("constructor (5) Get(0) = 0", testCtorStartSize.Get(0) == 0);
	DynamicArray<TestType> testCtorFull(5, 10);
	Test("constructor (5 , 10) size = 5", testCtorFull.GetSize() == 5);
	Test("constructor (5 , 10) capcaity = 5", testCtorFull.GetCapacity() == 5);
	Test("constructor (5 , 10) Get(0) = 10", testCtorFull.Get(0) == 10);
	Test("constructor (5 , 10) Get(4) = 10", testCtorFull.Get(4) == 10);
	std::cout << '\n';

	// access
	std::cout << "access tests\n";
	DynamicArray<TestType> acessTest(5, 5);
	Test("test(5,5) Get(0) = 5", acessTest.Get(0) == 5);
	Test("test(5,5) [1] = 5", acessTest[1] == 5);
	Test("test(5,5) Front() = 5", acessTest.Front() == 5);
	Test("test(5,5) Back() = 5", acessTest.Back() == 5);
	Test("test(5,5) Data() = {5,5,5,5,5}", AreSame<TestType>(acessTest.Data(), acessTest.GetSize(), { 5,5,5,5,5 }));
	std::cout << '\n';

	// comparison
	std::cout << "comparison tests\n";
	DynamicArray<TestType> comparisonTest1(5, 5);
	DynamicArray<TestType> comparisonTest2(5, 5);
	Test("ctor(5,5) == ctor(5,5)", (comparisonTest1 == comparisonTest2));
	DynamicArray<TestType> comparisonTest3(6, 6);
	Test("(6,6) != (5,5)", (comparisonTest3 != comparisonTest1));
	std::cout << '\n';

	// assignment
	std::cout << "assignment tests\n";
	DynamicArray<TestType> assignmentTest(5, 5);
	assignmentTest.assign(5, 10);
	Test("assign(5, 10) fully replaces array to 10", AreSame<TestType>(&assignmentTest, { 10,10,10,10,10 }));
	assignmentTest.assign(2, 20);
	Test("assign(2, 20) = { 20,20 }", AreSame<TestType>(&assignmentTest, { 20,20 }));
	Test("assign(2, 20) kept capacity the same", assignmentTest.GetCapacity() == 5);
	Test("assign(2, 20) reduced size to 2", assignmentTest.GetSize() == 2);
	assignmentTest.assign(8, 2);
	Test("assign(8, 2) = {2,2,2,2,2,2,2,2}", AreSame<TestType>(&assignmentTest, { 2,2,2,2,2,2,2,2 }));
	Test("assign(8, 2) doubled capcaity to 10", assignmentTest.GetCapacity() == 10);
	Test("assign(8, 2) increased size to 8", assignmentTest.GetSize() == 8);
	assignmentTest.assign({ 15,20,25 });
	Test("assign({15,20,25}) = {15,20,25}", AreSame<TestType>(&assignmentTest, { 15,20,25 }));
	Test("assign({15,20,25}) capcaity stayed at 10", assignmentTest.GetCapacity() == 10);
	Test("assign({15,20,25}) size reduced to 3", assignmentTest.GetSize() == 3);
	DynamicArray<TestType> assignmentTestTwo;
	assignmentTestTwo = assignmentTest;
	Test("Operator= copied capacity", assignmentTestTwo.GetCapacity() == assignmentTest.GetCapacity());
	Test("Operator= copied Size", assignmentTestTwo.GetSize() == assignmentTest.GetSize());
	Test("Operator= copied array", AreSame<TestType>(assignmentTestTwo.Data(), assignmentTestTwo.GetSize(), assignmentTest.Data(), assignmentTest.GetSize()));
	std::cout << '\n';

	// modifiers
	std::cout << "modifiers tests\n";
	DynamicArray<TestType> modifierTest(5, 5);
	modifierTest.PushBack(10);
	Test("pushBack(10) added 10 to end", modifierTest.Back() == 10);
	Test("pushBack(10) doubled capacity", modifierTest.GetCapacity() == 10);
	Test("pushBack(10) Increased size to 6", modifierTest.GetSize() == 6);
	DynamicArray<TestType> opperatorTest(5, 5);
	opperatorTest += 10;
	Test("ctor(5,5) += 10; Last element = 10", opperatorTest.Back() = 10);
	Test("ctor(5,5) += 10; size increased to 6", opperatorTest.GetSize() == 6);
	Test("ctor(5,5) += 10; capacity doubled to 10", opperatorTest.GetCapacity() == 10);
	modifierTest.Add(10, modifierTest.begin() + 1);
	Test("Add(10 , begin() + 1) added 10 to the second element", modifierTest[1] == 10);
	Test("Add(10 , begin() + 1) Increased size to 7", modifierTest.GetSize() == 7);
	Test("Add(10 , begin() + 1) capacity stayed 10", modifierTest.GetCapacity() == 10);
	modifierTest.AppendRange({ 1,2,3 });
	Test("AppendRange({ 1,2,3 }) last element - 0 = 3", *(modifierTest.end() - 1) == 3);
	Test("AppendRange({ 1,2,3 }) last element - 1 = 2", *(modifierTest.end() - 2) == 2);
	Test("AppendRange({ 1,2,3 }) last element - 2 = 1", *(modifierTest.end() - 3) == 1);
	Test("AppendRange({ 1,2,3 }) Increased size to 10", modifierTest.GetSize() == 10);
	Test("AppendRange({ 1,2,3 }) capacity stayed 10", modifierTest.GetCapacity() == 10);
	modifierTest.InsertRange({ 11,12,13 }, modifierTest.begin() + 1);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) second element = 11", modifierTest[1] == 11);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) third element = 12", modifierTest[2] == 12);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) fourth element = 13", modifierTest[3] == 13);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) last element - 0 = 3", *(modifierTest.end() - 1) == 3);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) last element - 1 = 2", *(modifierTest.end() - 2) == 2);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) last element - 2 = 1", *(modifierTest.end() - 3) == 1);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) Increased size to 13", modifierTest.GetSize() == 13);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) capacity doubled to 20", modifierTest.GetCapacity() == 20);
	Test("InsertRange( { 11,12,13 }, begin()+1 ) Full Array is correct", AreSame<TestType>(&modifierTest, { 5,11,12,13,10,5,5,5,5,10,1,2,3 }));
	modifierTest.Erase(3); // {5,11,12,10,5,5,5,5,10,1,2,3}
	Test("Erase(3) fourth element now 10", modifierTest[3] == 10);
	Test("Erase(3) size reduced to 12", modifierTest.GetSize() == 12);
	Test("Erase(3) Capacity stayed 20", modifierTest.GetCapacity() == 20);
	DynamicArray<TestType> opperatorTestTwo(5, 5);
	opperatorTestTwo = { 1,2,3,4,5 };
	opperatorTestTwo -= 4;
	Test("{1,2,3,4,5} -= 4; Last element = 4", opperatorTestTwo.Back() = 4);
	Test("{1,2,3,4,5} -= 4; size decreased to 4", opperatorTestTwo.GetSize() == 4);
	Test("{1,2,3,4,5} -= 4; capacity stayed at 5", opperatorTestTwo.GetCapacity() == 5);
	modifierTest.PopBack(); // {5,11,12,10,5,5,5,5,10,1,2}
	Test("PopBack() Last element = 2", modifierTest.Back() = 2);
	Test("PopBack() size reduced to 11", modifierTest.GetSize() == 11);
	Test("PopBack() capacity stayed 20", modifierTest.GetCapacity() == 20);
	modifierTest.Resize(10);// {5,11,12,10,5,5,5,5,10,1}
	Test("Resize(10) size is now 10", modifierTest.GetSize() == 10);
	Test("Resize(10) capacity is now 10", modifierTest.GetCapacity() == 10);
	Test("Resize(10) kept first 10 elements", AreSame<TestType>(&modifierTest, { 5,11,12,10,5,5,5,5,10,1 }));
	modifierTest.Resize(15);// {5,11,12,10,5,5,5,5,10,1}
	Test("Resize(15) size is the same", modifierTest.GetSize() == 10);
	Test("Resize(10) capacity is now 15", modifierTest.GetCapacity() == 15);
	Test("Resize(10) kept first 10 elements", AreSame<TestType>(&modifierTest, { 5,11,12,10,5,5,5,5,10,1 }));
	modifierTest.Swap(0, 9);// {1,11,12,10,5,5,5,5,10,5}
	Test("Swap(0,9) element 0 replaced with element 9", modifierTest.Front() = 1);
	Test("Swap(0,9) element 9 replaced with element 0", modifierTest.Back() = 5);
	modifierTest.Swap(modifierTest.begin(), modifierTest.end());// {5,11,12,10,5,5,5,5,10,1}
	Test("Swap(begin(),end()) first element replaced with last", modifierTest.Front() = 5);
	Test("Swap(begin(),end()) last element replaced with first", modifierTest.Back() = 1);
	modifierTest.Clear();
	Test("Clear() size = 0", modifierTest.GetSize() == 0);
	Test("Clear() capacity unchanged", modifierTest.GetCapacity() == 15);
	std::cout << '\n';

	// capacity
	std::cout << "Capacity tests\n";
	Test("Empty() returns true if size = 0 ", modifierTest.Empty());
	DynamicArray<TestType> capacityTest(5,5);
	Test("Empty() returns false if size = 5 ", (capacityTest.Empty() == false));
	capacityTest.Erase(0);
	capacityTest.ShrinkToFit();
	Test("ShrinkToFit() reduced capacity", capacityTest.GetCapacity() == 4);
	capacityTest.Reserve(10);
	Test("Reserve(10) allocated capacity 10", capacityTest.GetCapacity() == 10);
	capacityTest.Reserve(5);
	Test("Reserve(5) properly didnt reduce capacity", capacityTest.GetCapacity() == 10);
#endif
	std::cout << "\n\n";
	std::cout << g_passedTests << " / ";
	std::cout << g_testCount << " | Tests Passed\n";
	//std::cout << g_passedTests << " / " << g_testCount << " | Tests passed\n";
	if (g_testCount == g_passedTests)
		std::cout << " ALL TESTS PASSED\n";
	// iterator

}