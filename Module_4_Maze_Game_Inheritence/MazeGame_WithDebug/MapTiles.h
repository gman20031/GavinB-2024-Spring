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
	CREATE_CHAR_DRAW(ObjectCharacter::kEmpty)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	EmptyTile() : GameObject() {}
};

class TrapTile : public GameObject
{
public:
	CREATE_CHAR_DRAW(ObjectCharacter::kTrap)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	TrapTile() : GameObject() {}
};

class ExitTile : public GameObject
{
public:
	CREATE_CHAR_DRAW(ObjectCharacter::kExit)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	ExitTile() : GameObject() {}
};

class WallTile : public GameObject
{
public:
	CREATE_CHAR_DRAW(ObjectCharacter::kWall)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	WallTile() : GameObject() {}
};

