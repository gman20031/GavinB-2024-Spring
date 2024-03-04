#pragma once

#include "GameObject.h"

class HorizontalEnemy : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kHorizontalEnemy;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:

	virtual void InteractWithPlayer() override { return; };
public:
	HorizontalEnemy() : GameObject() {}
};

class VerticalEnemy : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kVerticalEnemy;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:

	virtual void InteractWithPlayer() override { return; };
public:
	VerticalEnemy() : GameObject() {}
};