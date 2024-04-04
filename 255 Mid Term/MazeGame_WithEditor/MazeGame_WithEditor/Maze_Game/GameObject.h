#pragma once

#include <functional>
#include <iostream>

#include "../SharedGameFiles/Vector2.h"
#include "../SharedGameFiles/GameCharacterInfo.h"
#include "../SharedGameFiles/ConsoleManip.h"


typedef ObjectChar GameObjectType;

// Creates a static constexpr ObjectChar of specified type for a class
#define CREATE_CHAR(_ObjectCharacter)											    \
	public:																			\
	inline static constexpr GameObjectType s_displayCharacter = _ObjectCharacter;	\
	private:

class Entity;
class Map;

class GameObject
{
protected:
	// display stuff could be its own class and or below could be struct.
	GameObjectType m_displayCharacter = GameObjectType::kBase;
	const char* m_displayFormat = TEXT_DEF;
	void SetDisplayChar(GameObjectType newChar) { m_displayCharacter = newChar; }
	inline static constexpr GameObjectType s_displayCharacter = GameObjectType::kBase;

	Vector2 m_position;
	Map* m_pCurrentMap ;
public:
	GameObject(GameObjectType newType);
	virtual ~GameObject() = default;

	Vector2 GetPosition() const;
	void SetPosition(Vector2 newPosition);

	Map* GetMapPointer();
	bool SetCurrentMapPointer(Map* newMap);

	// this should only be used to literally copy the display character for the doors.
	void SetDisplayFormat(const char* newFormat) { m_displayFormat = newFormat; }
	const char* GetDisplayFormat() { return m_displayFormat; }
	GameObjectType GetDisplayCharacater() const { return m_displayCharacter; } 

	void Draw();
	bool m_updated = false;
	virtual void Collide(Entity* collidedEntity) = 0;
	virtual void Update() { /* Walls,Floors,Traps all dont need updates */ };
	virtual bool IsPlayer() { return false; }
	virtual void Kill() {  /* Theres a better solution somewhere */ }
};

