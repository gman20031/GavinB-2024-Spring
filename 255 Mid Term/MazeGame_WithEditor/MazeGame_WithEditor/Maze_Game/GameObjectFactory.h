#pragma once

#include "GameObject.h"
#include "../SharedGameFiles/GameCharacterInfo.h"

class GameObjectFactory
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using GameObjectFactoryKey = ObjectChar;
	typedef GameObjectPtr(*GameObjectFactoryFunction)();
public:
	// uses objectKey as the key for a map for functions, runs that function if found.
	// returns std::shared_ptr<GameObject> with the contents being of the type specified by the key
	static GameObjectPtr Create(GameObjectFactoryKey objectKey)
	{
		auto entry = GetFactoryFunctionRegister().find(objectKey);
		if (entry != GetFactoryFunctionRegister().end())
			return entry->second();
		return {};
	}

	// Creating a Registrar<Type> instance will add a function to create std::shared_ptr<Type> to the factory's Map
	template <typename Type>
	class Registrar
	{
	public:
		Registrar()
		{
			GetFactoryFunctionRegister().emplace(Type::s_displayCharacter, &Registrar::Create);
		}
	private:
		static GameObjectPtr Create() { return std::make_shared<Type>(); }
	};

private:
	// Returns & to a statically allocated std::unordered_map keyed to ObjectChar filled with GameObjectFactoryFunctions
	static std::unordered_map< GameObjectFactoryKey, GameObjectFactoryFunction>& GetFactoryFunctionRegister()
	{
		static std::unordered_map< GameObjectFactoryKey, GameObjectFactoryFunction> FactoryFunctionRegister;
		return FactoryFunctionRegister;
	}
};

