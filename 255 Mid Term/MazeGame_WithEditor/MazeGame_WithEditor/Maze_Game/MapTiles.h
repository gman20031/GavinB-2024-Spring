#pragma once

#include "GameObject.h"

class EmptyTile: public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kEmpty)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	EmptyTile() : GameObject(s_displayCharacter)
	{
		m_displayFormat = TEXT_FORMAT(30);
	}
};

class TrapTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kTrap)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	TrapTile() : GameObject(s_displayCharacter) 
	{
		m_displayFormat = TEXT_RGB(112,30,30);
	}
};

class ExitTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kExit)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	ExitTile() : GameObject(s_displayCharacter) 
	{
		m_displayFormat = TEXT_RGB(222,227,118);
	}
};

class WallTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kWall)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	inline static const char s_displayFormat[] = TEXT_RGB(139, 133, 255) VT_ESC BACK_RGB(139, 133, 255);
	WallTile() : GameObject(s_displayCharacter)
	{
		m_displayFormat = s_displayFormat;
	}
};

class ToggleTile : public GameObject
{
	CREATE_CHAR(GameObjectType::kTogglePlate)
private:
	virtual void Collide(Entity* collidedEntity) override;
	const char* kActiveDisplayFormat = TEXT_RGB(0, 255, 0);
	const char* kInactiveDisplayFormat = TEXT_DEF;
	bool m_activated = false;
public:
	inline static const char s_displayFormat[] = TEXT_DEF;
	ToggleTile() : GameObject(s_displayCharacter)
	{
		m_displayFormat = kInactiveDisplayFormat;
	}


};

