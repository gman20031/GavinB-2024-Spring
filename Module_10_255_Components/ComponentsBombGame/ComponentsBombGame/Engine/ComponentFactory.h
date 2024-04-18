#pragma once

#include "Component.h"


class ConcreteComponentTest : public Component
{
	int value;
public:
	ConcreteComponentTest(int val) : value(val) {}

	void PrintValue() { std::cout << value; }
};

template <typename ... componentArgs>
class ComponentFactory
{
	using ComponentPtr = Component*;
	using FactoryKey = Component::IdType;
	typedef GameObject(*ComponentCreationFunction)(...);
};

