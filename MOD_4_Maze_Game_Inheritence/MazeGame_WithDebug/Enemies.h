#pragma once

#include "Entity.h"
#include "Directions.h"


// NOPE IM NOT DOING THIS WITH INHERITANCE
// NOPE IM NOT DOING THIS WITH INHERITANCE
// NOPE IM NOT DOING THIS WITH INHERITANCE

class HorizontalEnemy : public Entity
{
public:
	CREATE_CHAR_DRAW(ObjectCharacter::kHorizontalEnemy)
private:
	Direction m_currentDirection;
	virtual void Collide(Entity* collidedEntity);
public:
	HorizontalEnemy();

	virtual void HitWall() override;
	virtual void Move() override;
};

class VerticalEnemy : public Entity
{
public:
	CREATE_CHAR_DRAW(ObjectCharacter::kVerticalEnemy)
private:
	Direction m_currentDirection;
	virtual void Collide(Entity* collidedEntity);
public:
	VerticalEnemy();

	virtual void HitWall() override;
	virtual void Move() override;
};