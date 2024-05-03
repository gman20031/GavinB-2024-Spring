#pragma once

#include "Operation.h"

/////////////////////////////////////////////////////////////////
// Encapsulates an addition operation.
/////////////////////////////////////////////////////////////////
class AdditionOperation : public Operation
{
public:
	virtual std::string GetDescription() const override;
	virtual float operator()(float& left, float& right) const override;
};

