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

#define CREATE_CHAR_DRAW(_ObjectCharacter)									\
	public:																	\
	static constexpr ObjectCharacter m_displayCharacter = _ObjectCharacter;	\
	virtual void Draw() override											\
	{ 																		\
		std::cout << static_cast<char>(m_displayCharacter);					\
	}																		\
	private:


class Entity;

class GameObject
{
protected:
	Vector2 m_position;
	Map* m_pCurrentMap ;


public:
	inline static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kBase;
	//virtual ObjectCharacter GetType() = 0;

	GameObject();
	virtual ~GameObject() = default;

	Vector2 GetPosition() const;
	void SetPosition(Vector2 newPosition);

	Map* GetMapPointer();
	bool SetCurrentMapPointer(Map* newMap);

	virtual void Collide(Entity* collidedEntity) = 0;
	virtual void Draw() = 0;
};

