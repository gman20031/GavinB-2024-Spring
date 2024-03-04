#pragma once

#include <functional>

#include "Vector2.h"
#include "iostream"

class Map;

enum class ObjectCharacter
{
	kBase = '\0',
	kWall = '#',
	kExit = 'X',
	kEmpty = '.',
	kPlayer = '@',
	kTrap = '0',
	kHorizontalEnemy = '-',
	kVerticalEnemy = '|',
};

class GameObject
{
protected:
	Vector2 m_position;
	Map* m_pCurrentMap ;

	virtual void InteractWithPlayer() = 0;

public:
	inline static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kBase;
	 
	GameObject();
	virtual ~GameObject() = default;

	Vector2 GetPosition() const;
	virtual void SetPosition(Vector2 newPosition);

	Map* GetMapPointer();
	virtual bool SetCurrentMapPointer(Map* newMap);

	virtual void draw() = 0;
};


