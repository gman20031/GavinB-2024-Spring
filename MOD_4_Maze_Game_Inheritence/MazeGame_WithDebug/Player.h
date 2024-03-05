#pragma once

#include "GameObject.h"
#include "Directions.h"

class Player : public GameObject
{
public:
	static constexpr size_t kMoveSpeed = 1;
	inline static constexpr ObjectCharacter m_displayCharacter = ObjectCharacter::kPlayer;
	virtual void draw() override { std::cout << static_cast<char>(m_displayCharacter); }
private:
	bool MoveCharacter(Vector2 newPosition);
	virtual void InteractWithPlayer() override { return; }

	//kill playeer()
	//sawp player with()

public:
	Player() : GameObject() {}
	virtual bool SetCurrentMapPointer(Map* newMap) override;

	bool Move(Direction direction);

};