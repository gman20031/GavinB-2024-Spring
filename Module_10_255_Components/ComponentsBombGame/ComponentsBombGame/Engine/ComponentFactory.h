#pragma once

#include "Component.h"



template <class ComponentType, typename ... ArgTypes>
Component* CreateComponent(ArgTypes&& ... args)
{
	return new ComponentType(args...);
}

template <typename ... componentArgs>
class ComponentFactory
{
	using ComponentPtr = Component*;
	using FactoryKey = Component::IdType;
	typedef GameObject(*ComponentCreationFunction)(...);
};

