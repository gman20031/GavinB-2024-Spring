#pragma once

#include "Entity.h"

////////////////////////////////////////////////////////////////
/// These are all sperate to make the factory work nicely.
/// Yes, the factory is nice, but makes issues like needing this.
/// I will rethink it next time
////////////////////////////////////////////////////////////////

class HorizontalEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kHorizontalEnemy)
private:

public:
	HorizontalEnemy();

	virtual void HitWall() override;
};

class VerticalEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kVerticalEnemy)
private:

public:
	VerticalEnemy();

	virtual void HitWall() override;
};

class RandEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kRandomEnemy)
private:

public:
	RandEnemy();
};

class DirectEnemy : public Entity
{
public:
	CREATE_CHAR(GameObjectType::kDirectEnemy)
private:

public:
	DirectEnemy();

};