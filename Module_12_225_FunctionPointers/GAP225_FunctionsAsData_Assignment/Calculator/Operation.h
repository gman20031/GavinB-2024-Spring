#pragma once

#include <string>

/////////////////////////////////////////////////////////////////
// Encapsulates a (float, float)->float operation.
/////////////////////////////////////////////////////////////////
class Operation
{
public:
	// Returns a description of the operation.
	virtual std::string GetDescription() const = 0;

	// Executes the operation.
	virtual float operator()(float& left, float& right) const = 0;
};

