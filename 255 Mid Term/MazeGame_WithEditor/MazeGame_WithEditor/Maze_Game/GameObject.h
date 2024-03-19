#pragma once

#include <functional>
#include <iostream>

#include "Vector2.h"
#include "../SharedGameFiles/GameCharacterInfo.h"


typedef ObjectChar GameObjectType;

#define CREATE_CHAR(_ObjectCharacter)											    \
	public:																			\
	inline static constexpr GameObjectType s_displayCharacter = _ObjectCharacter;	\
	private:

class Entity;
class Map;

class GameObject
{
protected:
	GameObjectType m_displayCharacter = GameObjectType::kBase;
	Vector2 m_position;
	Map* m_pCurrentMap ;

	void SetDisplayChar(GameObjectType newChar) { m_displayCharacter = newChar; }

public:
	inline static constexpr GameObjectType s_displayCharacter = GameObjectType::kBase;

	GameObject(GameObjectType newType);
	virtual ~GameObject() = default;

	Vector2 GetPosition() const;
	void SetPosition(Vector2 newPosition);

	Map* GetMapPointer();
	bool SetCurrentMapPointer(Map* newMap);

	void Draw();
	virtual void Collide(Entity* collidedEntity) = 0;
	virtual void Update() {};
	virtual bool IsPlayer() { return false; }
};

