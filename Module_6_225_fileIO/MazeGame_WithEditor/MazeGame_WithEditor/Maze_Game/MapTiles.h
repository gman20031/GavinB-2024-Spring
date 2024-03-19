#pragma once

#include "GameObject.h"
#include "iostream"

//Tiles needed
// emtpy tiles
// wall tiles
// Trap tiles
// Exit tile

class EmptyTile: public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kEmpty)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	EmptyTile() : GameObject(s_displayCharacter) {}
};

class TrapTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kTrap)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	TrapTile() : GameObject(s_displayCharacter) {}
};

class ExitTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kExit)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	ExitTile() : GameObject(s_displayCharacter) {}
};

class WallTile : public GameObject
{
public:
	CREATE_CHAR(GameObjectType::kWall)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	WallTile() : GameObject(s_displayCharacter) {}
};

