#pragma once

#include <iostream>

void Test(const char* pTestName, bool test)
{
	std::cout << pTestName << ": " << (test ? "SUCCESS" : "FAILURE") << std::endl;
}

void RunAllTests()
{
		//TIP: Use conditional compilation to remove tests that you haven't solved yet.
#if 1	// Move this below each test as you solve it, or set it to 1 to test everything.

	const Vector3 kZeroVector{};
	Test("Default ctor: assigns 0 to x", kZeroVector.GetX() == 0);
	Test("Default ctor: assigns 0 to y", kZeroVector.GetY() == 0);
	Test("Default ctor: assigns 0 to z", kZeroVector.GetZ() == 0);

	const Vector3 kConstTestVector{ 1, 2, 3 };
	Test("Parameterized ctor: first parameter assigns to x", kConstTestVector.GetX() == 1);
	Test("Parameterized ctor: first parameter assigns to x", kConstTestVector.GetY() == 2);
	Test("Parameterized ctor: first parameter assigns to x", kConstTestVector.GetZ() == 3);

	const Vector3 kUnitVector = Vector3::GenerateUnitVector();
	Test("GenerateUnitVector returns Vector{1,1,1}", kUnitVector.GetX() == kUnitVector.GetY() == kUnitVector.GetZ() == 1);

	Test("Comparison operator implemented", kUnitVector == kUnitVector);

	const Vector3 kTestVector1 = -kUnitVector;
	Test("Inversion operator implemented", kTestVector1 == Vector3{ -1,-1,-1 });

	Vector3 testVector2 = kUnitVector + kUnitVector;
	Test("Addition operator implemented", testVector2 == Vector3{ 2,2,2 });

	testVector2 += kUnitVector;
	Test("Addition assignment operator implemented", testVector2 == Vector3{ 3,3,3 });

	Vector3 testVector3 = kUnitVector - kUnitVector;
	Test("Subtraction operator implemented", testVector3 == kZeroVector);

	testVector3 -= kUnitVector;
	Test("Subtraction assignment operator implemented", testVector3 == Vector3{ -1,-1, -1 });

	Vector3 testVector4 = kUnitVector * 2;
	Test("Scalar multiplication operator implemented", testVector4 == Vector3{ 2,2,2 });

	Vector3 testVector5 = 2 * kUnitVector;
	Test("Scalar multiplication operator is transitive (the float can be first)", testVector5 == testVector4);

	testVector5 *= 2;
	Test("Scalar multiplication assignment operator implemented", testVector5 == Vector3{ 4,4,4 });

	Vector3 testVector6 = kUnitVector / 2;
	Test("Scalar division operator implemented", testVector6 == Vector3{ 0.5f, 0.5f, 0.5f });

	testVector6 /= 2;
	Test("Scalar division assignment operator implemented", testVector6 == Vector3{ 0.25f, 0.25f, 0.25f });

	// This won't be testable in a true unit test because it doesn't return a comparable value.
	// It succeeds if it prints this: Vector3{1,2,3}
	// (It should not include a newline character or std::endl.)
	std::cout << kConstTestVector << std::endl;

#endif
}