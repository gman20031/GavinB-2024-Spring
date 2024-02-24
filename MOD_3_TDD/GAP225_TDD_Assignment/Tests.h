#pragma once

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////
// Runs a test to check if value1 is close enough to value2 to be considered the same.
// pTestName will print along with "SUCCESS" or "FAILURE" after the test.
//////////////////////////////////////////////////////////////////////////////////////
void TestFloats(const char* pTestName, float value1, float value2)
{
	constexpr float kCloseEnough = 0.01f;

	std::cout << pTestName << ": ";

	if (abs(value1 - value2) < kCloseEnough
		|| abs(value2 - value1) < kCloseEnough)
	{
		std::cout << "PASSED";
	}
	else
	{
		std::cout << "FAILED";
	}

	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////
// Runs a test to check if the function return and expected result are the same
// pTestName will print along with "SUCCESS" or "FAILURE" after the test.
//////////////////////////////////////////////////////////////////////////////////////
void TestBooleans(const char* pTestName, bool functionReturn, bool expectedResult)
{
	std::cout << pTestName << ": ";

	if(functionReturn == expectedResult)
		std::cout << "PASSED";
	else
		std::cout << "FAILED";

	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////
// Runs all the tests for this project.
//////////////////////////////////////////////////////////////////////////////////////
void RunTests()
{
	// PART ONE:
	// These are the tests that your code needs to pass.
	// You can change the '0' below to a '1' to test everything.
	// Or, you can move '#if 0' down as you go to test one thing at a time.

#if 1
	Vector2 vector1{ 0, 0 };
	TestFloats("vector1.x", vector1.GetX(), 0);
	TestFloats("vector1.y", vector1.GetY(), 0);

	Vector2 vector2{ 3, 0 };
	TestFloats("vector2.x", vector2.GetX(), 3);
	TestFloats("vector2.y", vector2.GetY(), 0);

	Vector2 vector3{ 3, 4 };
	TestFloats("vector3.x", vector3.GetX(), 3);
	TestFloats("vector3.y", vector3.GetY(), 4);

	Triangle triangle1{ vector1, vector2, vector3 };
	TestFloats("triangle1.GetSideLength(0)", triangle1.GetSideLength(0), 3);	// between points 0 and 1
	TestFloats("triangle1.GetSideLength(1)", triangle1.GetSideLength(1), 4);	// between points 1 and 2
	TestFloats("triangle1.GetSideLength(2)", triangle1.GetSideLength(2), 5);	// between points 0 and 2
	TestFloats("triangle1.GetPerimeter()", triangle1.GetPerimeter(), 12);
	TestFloats("triangle1.GetArea()", triangle1.GetArea(), 6);
	
	Triangle triangle2{ Vector2{0,0}, Vector2{0.5f,2}, Vector2{2,1} };
	TestFloats("triangle1.GetSideLength(0)", triangle2.GetSideLength(0), 2.062f);	// between points 0 and 1
	TestFloats("triangle1.GetSideLength(1)", triangle2.GetSideLength(1), 1.803f);	// between points 1 and 2
	TestFloats("triangle1.GetSideLength(2)", triangle2.GetSideLength(2), 2.236f);	// between points 0 and 2
	TestFloats("triangle1.GetPerimeter()", triangle2.GetPerimeter(), 6.101f);
	TestFloats("triangle1.GetArea()", triangle2.GetArea(), 1.75f);
	
	std::cout << std::endl;
	std::cout << std::endl;

#endif
#if 1
	// pi = 3.1415
	Vector2 centerpoint1{ 0,0 };
	Circle circle1(centerpoint1, 1.0f);
	TestFloats("circle1.GetDiameter()", circle1.GetDiameter(), 2.0f);
	TestFloats("circle1.GetCircumference()", circle1.GetCircumference(), 6.283f);
	TestFloats("circle1.GetArea()", circle1.GetArea(), 3.1415f);
	
	Vector2 centerpoint2{ 3,3 };
	Circle circle2(centerpoint2, 2.0f);
	TestFloats("circle2.GetDiameter()", circle2.GetDiameter(), 4.0f);
	TestFloats("circle2.GetCircumference()", circle2.GetCircumference(), 12.566f);
	TestFloats("circle2.GetArea()", circle2.GetArea(), 12.566f);

	Vector2 centerpoint3{ 0,-2 };
	Circle circle3(centerpoint3, 1.0f);
	TestFloats("circle3.GetDiameter()", circle3.GetDiameter(), 2.0f);
	TestFloats("circle3.GetCircumference()", circle3.GetCircumference(), 6.283f);
	TestFloats("circle3.GetArea()", circle3.GetArea(), 3.1415f);

	TestBooleans("circle1.CollidesWithCircle(&circle2)", circle1.CollidesWithCircle(&circle2), false);
	TestBooleans("circle2.CollidesWithCircle(&circle2)", circle2.CollidesWithCircle(&circle2), true);
	TestBooleans("circle1.CollidesWithCircle(&circle3)", circle1.CollidesWithCircle(&circle3) , true);
	TestBooleans("circle3.CollidesWithCircle(&circle2)", circle3.CollidesWithCircle(&circle2), false);
	TestBooleans("circle2.CollidesWithCircle(&circle3)", circle2.CollidesWithCircle(&circle3), false);



#endif

}