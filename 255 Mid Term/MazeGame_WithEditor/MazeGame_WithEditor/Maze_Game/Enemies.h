#pragma once

#include "Entity.h"

class HorizontalEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kHorizontalEnemy)
private:
	Direction m_currentDirection;
public:
	HorizontalEnemy();

	virtual void HitWall() override;
	virtual void Update() override;
};

class VerticalEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kVerticalEnemy)
private:
	Direction m_currentDirection;
public:
	VerticalEnemy();

	virtual void HitWall() override;
	virtual void Update() override;
};

class RandEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kRandomEnemy)
private:
	Direction m_currentDirection;
public:
	RandEnemy();

	virtual void HitWall() override;
	virtual void Update() override;
};