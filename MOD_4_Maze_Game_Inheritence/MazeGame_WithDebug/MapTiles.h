#pragma once

#include "GameObject.h"

//Tiles needed
// emtpy tiles
// wall tiles
// Trap tiles
// Exit tile

class EmptyTile: public GameObject
{
	virtual void InteractWithPlayer() override{ return; };
public:
	EmptyTile() : GameObject() {}
	EmptyTile(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kEmpty)
	{
		m_displayCharacter;
	}
};

class TrapTile: public GameObject
{
	virtual void InteractWithPlayer() override{ return; };
public:
	TrapTile() : GameObject() {}
	TrapTile(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kTrap)
	{}
};

class ExitTile : public GameObject
{
	virtual void InteractWithPlayer() override{ return; };
public:
	ExitTile() : GameObject() {}
	ExitTile(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kExit)
	{}

};

class WallTile : public GameObject
{
	virtual void InteractWithPlayer() override{ return; };
public:
	WallTile() : GameObject() {}
	WallTile(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kWall)
	{}

};