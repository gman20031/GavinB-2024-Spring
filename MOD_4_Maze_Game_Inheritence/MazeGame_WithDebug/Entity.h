#pragma once
#include "GameObject.h"
#include "Directions.h"

class Entity : public GameObject
{
protected:
	Vector2 GetNextPosition(Direction direction, Vector2 currentPosition) const;
	bool MoveOnMap(Map* currentMap, Direction direction, Entity* entity);

public:
	Entity() : GameObject() {}


	virtual bool IsPlayer() { return false; }
	virtual void HitWall() {};
	virtual void Move() = 0;
};
