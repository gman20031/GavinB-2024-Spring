#pragma once
#include "GameObject.h"

/*
	kClearDoor = '~',
	kHiddenDoor = 'D',
*/

class Door : public GameObject
{
protected:
	using GameObjectPtr = std::shared_ptr <GameObject>;

	bool m_unlocked = false;
	GameObjectPtr m_heldObject = nullptr;

	inline static const char kUnlockedFormat[] = TEXT_RGB(255, 255, 255);
	const char* m_defaultFormat = TEXT_RGB(50, 50, 255) VT_ESC BACK_RGB(50, 50, 255);
	GameObjectType m_defaultDisplay;

	void UpdateUnlocked();
	void RemoveHeldObject();

public:
	Door(GameObjectType objectType);
	void Unlock();
	void Lock();
	virtual void Update() override;

	virtual void Collide(Entity* collidedEnitity);
};

////////////////////////////////////////////////////////////////
/// These are all sperate to make the factory work nicely.
/// Yes, the factory is nice, but makes issues like needing this.
/// I will rethink it next time
////////////////////////////////////////////////////////////////

class ClearDoor : public Door
{
	CREATE_CHAR(GameObjectType::kClearDoor)
private:

public:
	ClearDoor();
};

class HiddenDoor : public Door
{
	CREATE_CHAR(GameObjectType::kHiddenDoor)
private:

public:
	HiddenDoor();
};
