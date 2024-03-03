#pragma once

#include "GameObject.h"
#include "Directions.h"



class Player : public GameObject
{
public:
	static constexpr size_t kMoveSpeed = 1;
	static constexpr char m_displayCharacter = '@';
private:
	bool MoveCharacter(Vector2 newPosition);
	virtual void InteractWithPlayer() override { return; }

public:
	Player() : GameObject() {}
	Player(Vector2 position, const char displayCharacter);
	virtual bool SetCurrentMapPointer(Map* newMap) override;

	bool Move(Direction direction);

};