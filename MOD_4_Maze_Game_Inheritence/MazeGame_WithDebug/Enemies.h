#pragma once

#include "GameObject.h"

class HorizontalEnemy : public GameObject
{
	virtual void InteractWithPlayer() override { return; };
public:
	HorizontalEnemy() : GameObject() {}
	HorizontalEnemy(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kHorizontalEnemy)
	{
		m_displayCharacter;
	}
};

class VerticalEnemy : public GameObject
{
	virtual void InteractWithPlayer() override { return; };
public:
	VerticalEnemy() : GameObject() {}
	VerticalEnemy(Vector2 position)
		:GameObject(position, (char)ObjectCharacters::kVerticalEnemy)
	{
		m_displayCharacter;
	}
};