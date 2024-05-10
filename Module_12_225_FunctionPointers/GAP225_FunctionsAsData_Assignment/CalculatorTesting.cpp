#include "Tasks.h"

#include <iostream>

#include "Calculator/ModdableCalculator.h"
#include "Calculator/AdditionOperation.h"

static float Exponentation(float& base, float& power)
{
	if (power == 0)
		return 1;

	bool negative = false;
	if (power < 0)
	{
		power = -power;
		negative = true;
	}

	float out = base;
	for (float i = power; i > 1; --i)
		out *= base; 

	if (negative)
		return (1 / out);
	return out;
}

void CalculatorTesting()
{
	ModdableCalculator calculator;

	// Create addition functor.
	AdditionOperation addition;

	// Pass the lambda along with the description of what it is.
	calculator.AddOperation(addition, addition.GetDescription());

	// NOTE: You don't have to use functors like I did!
	// Try different methods and see which one you like.

	//TODO: // Add:
	// subtraction
	calculator.AddOperation(
		[](float& lhs, float& rhs) -> float
		{
			return lhs - rhs;
		}
	, "Subtract two numbers.");
	// multiplication
	calculator.AddOperation(
		[](float& lhs, float& rhs) -> float
		{
			return lhs * rhs;
		}
	, "Multiple two numbers.");
	// division
	calculator.AddOperation(
		[](float& lhs, float& rhs) -> float
		{
			return lhs / rhs;
		}
	, "Divide two numbers.");
	// exponentation
	calculator.AddOperation(
		&Exponentation
		, "Raise one number to the power of another.");
	// Modulus
	calculator.AddOperation(
		[](float& lhs, float& rhs) -> float
		{
			return (float)((int)lhs % (int)rhs);
		}
	, "Modulo one number by another");


	calculator.Run();

}

