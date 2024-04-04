#pragma once

#include "Directions.h"
#include "../SharedGameFiles/Vector2.h"

class Map;
class Entity;

class ObjectMover
{
public:
	ObjectMover() {};


	Vector2 GetNextPosition(Direction direction, Vector2 currentPosition) const;
	bool MoveOnMap(Map* currentMap, Direction direction, Entity* entity) const;

	bool MovePlayer(Entity* entity)const ;
	bool MoveRandom(Entity* entity)const ;
	bool MoveTowardsPlayer(Entity* entity)const;
};