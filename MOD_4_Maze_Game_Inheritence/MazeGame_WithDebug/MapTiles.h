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
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kEmpty;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	virtual void InteractWithPlayer() override{ return; };
public:
	EmptyTile() : GameObject() {}
};

class TrapTile: public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kTrap;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	virtual void InteractWithPlayer() override{ return; };
public:
	TrapTile() : GameObject() {}
};

class ExitTile : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kExit;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	virtual void InteractWithPlayer() override{ return; };
public:
	ExitTile() : GameObject() {}
};

class WallTile : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kWall;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	virtual void InteractWithPlayer() override{ return; };
public:
	WallTile() : GameObject() {}
};