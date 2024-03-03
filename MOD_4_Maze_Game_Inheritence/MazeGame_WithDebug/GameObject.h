#pragma once
#include <functional>

#include "Vector2.h"
#include "Map.h"
#include "iostream"

enum class ObjectCharacters
{
	kWall,
	kExit,
	kEmpty,
	kPlayer,
	kTrap,
	kHorizontalEnemy,
	kVerticalEnemy,
};

class map;

class GameObject
{
protected:
	Vector2 m_position = { 0,0 };
	Map* m_pCurrentMap = nullptr;

	const char m_displayCharacter = '\n';
	virtual void InteractWithPlayer() = 0;

public:
	GameObject() = default;
	GameObject(Vector2 position, const char displayCharacter);
	virtual ~GameObject() = default;

	Vector2 GetPosition() const;
	virtual void SetPosition(Vector2 newPosition);

	Map* GetMapPointer();
	virtual bool SetCurrentMapPointer(Map* newMap);
	
	char GetDisplayChar() const;

	virtual void draw();
};

// A factory to create instances of any derived class of Gameobject
class GameObjectFactory
{
public:
	//key for the map that stores all factory functions
	using key = ObjectCharacters;

	// the intended output of the factory
	using outputPtr = std::shared_ptr<GameObject>;

	// a function that returns a shared pointer of shapes with no parameters
	using createFunction = std::function< GameObject* (void) >;

	// This map will contain every function to create possible Shapes.
	std::unordered_map<key, createFunction> factoryFunctionRegister;

	outputPtr Create(key shapeName)
	{
		GameObject* instance = nullptr;

		auto it = factoryFunctionRegister.find(shapeName);
		if (it != factoryFunctionRegister.end())
			instance = it->second();

		if (instance != nullptr)
			return outputPtr(instance); //unsure how shared_ptr actually works, but hopefully since
		else							//I obfuscated the new call, this will allow me to not need to
			return nullptr;				//worry about deleting anything I create in this function.
	}

	void RegisterFactoryFunction(key name, createFunction function)
	{
		factoryFunctionRegister.insert({ name , function });
	}

	static GameObjectFactory& Instance()
	{
		static GameObjectFactory factory;
		return factory;
	}
};

// why does this need to be outside of the class?
template <typename _class>
class Registrar
{
public:
	Registrar(GameObjectFactory::key name)
	{
		GameObjectFactory::createFunction factoryFunction = [](void) -> GameObject* { return new _class(); };
		GameObjectFactory::Instance().RegisterFactoryFunction(name, factoryFunction);
	}
};