#include "Calculator/ModdableCalculator.h"
#include "Calculator/AdditionOperation.h"

int main()
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
	// multiplication
	// division
	// exponentation
	// Modulus

	calculator.Run();

	return 0;
}