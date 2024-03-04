#pragma once

#include "GameObject.h"

// std shared pointer to shape object
using GameObjectPtr = std::shared_ptr<GameObject>;

// Key for shape factory map
using GameObjectFactoryKey = ObjectCharacter;

// a function that returns a shared pointer of shapes with no parameters
typedef GameObjectPtr(*GameObjectFactoryFunction)();

// A factory to create instances of any derived class of Shapes
class GameObjectFactory
{
public:
	static GameObjectPtr Create(GameObjectFactoryKey ObjectName)
	{
		auto it = GetFactoryFunctionRegister().find(ObjectName);
		if (it != GetFactoryFunctionRegister().end())
			return it->second();
		return {};
	}

	template <typename Type>
	class Registrar
	{
	public:
		Registrar()
		{
			GetFactoryFunctionRegister().emplace(Type::m_displayCharacter, &Registrar::Create);
		}
	private:
		static GameObjectPtr Create() { return std::make_shared<Type>(); }
	};

private:
	static std::unordered_map< GameObjectFactoryKey, GameObjectFactoryFunction>& GetFactoryFunctionRegister()
	{
		static std::unordered_map< GameObjectFactoryKey, GameObjectFactoryFunction> FactoryFunctionRegister;
		return FactoryFunctionRegister;
	}
};

