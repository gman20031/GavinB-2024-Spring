#pragma once

#include <unordered_map>
#include <iostream>

#include "Component.h"
#include "ComponentImplementations.h"


template <typename ... ArgTypes>
class ComponentFactory
{
	using ComponentPtr = Component*;
	using FactoryKey = Component::IdType;
	typedef ComponentPtr (*ComponentCreationFunction)(ArgTypes...);
	using Registry = std::unordered_map<FactoryKey, ComponentCreationFunction>;

public:
	static ComponentPtr Create(FactoryKey key, ArgTypes... componentArgs)
	{
		auto entry = GetFunctionRegistry().find(key);
		if (entry == GetFunctionRegistry().end()) return nullptr;

		auto ptr = entry->second(componentArgs...);
		return ptr;
	}

	template <class RegisteredType>
	class Registrar
	{
	public:
		Registrar()
		{
			GetFunctionRegistry().emplace(RegisteredType::s_Id, &Registrar::Create);
		}
	private:
		static ComponentPtr Create(ArgTypes... componentArgs) { return new RegisteredType(componentArgs...); }
	};

private:

	static Registry& GetFunctionRegistry()
	{
		static Registry s_registry;
		return s_registry;
	}
};

//template <typename ... ArgTypes>
class ExampleInstationIntBool
{
	using ComponentPtr = Component*;
	using FactoryKey = Component::IdType;
	typedef ComponentPtr(*ComponentCreationFunction)(int , bool);
	using Registry = std::unordered_map<FactoryKey, ComponentCreationFunction>;

public:
	static ComponentPtr Create(FactoryKey key, int e1, bool e2)
	{
		auto entry = GetFunctionRegistry().find(key);
		if (entry == GetFunctionRegistry().end()) return nullptr;
		return entry->second(e1, e2);
	}

	template <class RegisteredType>
	class Registrar
	{
	public:
		Registrar()
		{
			GetFunctionRegistry().emplace(RegisteredType::s_Id, &Registrar::Create);
		}
	private:
		static ComponentPtr Create(int e1, bool e2) { return new RegisteredType(e1, e2); }
	};

private:

	static Registry& GetFunctionRegistry()
	{
		static Registry s_registry;
		return s_registry;
	}
};


class ExampleVariaticInt
{
	using ComponentPtr = Component*;
	using FactoryKey = Component::IdType;
	typedef ComponentPtr(*ComponentCreationFunction)(std::initializer_list<int>);
	using Registry = std::unordered_map<FactoryKey, ComponentCreationFunction>;

public:
	static ComponentPtr Create(FactoryKey key, std::initializer_list<int> iList)
	{
		auto entry = GetFunctionRegistry().find(key);
		if (entry == GetFunctionRegistry().end()) return nullptr;
		return entry->second(iList);
	}

	template <class RegisteredType>
	class Registrar
	{
	public:
		Registrar()
		{
			GetFunctionRegistry().emplace(RegisteredType::s_Id, &Registrar::Create);
		}
	private:
		static ComponentPtr Create(std::initializer_list<int> iList) { return new RegisteredType(iList); }
	};

private:

	static Registry& GetFunctionRegistry()
	{
		static Registry s_registry;
		return s_registry;
	}
};