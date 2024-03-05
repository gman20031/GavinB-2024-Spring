#pragma once

#include "GameObject.h"
#include "Directions.h"

class HorizontalEnemy : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kHorizontalEnemy;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	Direction currentDirection;
	virtual void InteractWithPlayer() override { return; };
public:
	HorizontalEnemy();

	void Move() const;
};

class VerticalEnemy : public GameObject
{
public:
	static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kVerticalEnemy;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	Direction currentDirection;
	virtual void InteractWithPlayer() override { return; };
public:
	VerticalEnemy();

	void Move() const;
};