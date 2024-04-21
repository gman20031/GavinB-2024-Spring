#pragma once
#include <iostream>
#include <vector>
#include <cstdarg>
#include "Component.h"

class ConcreteComponentTest : public Component
{
	
	int value;

public:
	ConcreteComponentTest(int val) : value(val) {}

	void PrintValue() const { std::cout << value; }
};