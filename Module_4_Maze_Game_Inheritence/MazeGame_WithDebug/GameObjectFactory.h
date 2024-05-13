#pragma once

#include "GameObject.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectFactoryKey = ObjectCharacter;
typedef GameObjectPtr(*GameObjectFactoryFunction)();

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

