#include "Entity.h"
#include "Map.h"


////////////////////////////////////////////////////////////////////////
// Gets the next position on the map in the direction specified
////////////////////////////////////////////////////////////////////////
Vector2 Entity::GetNextPosition(Direction direction, Vector2 currentPosition) const
{
	Vector2 newPosition = currentPosition;

	switch (direction)
	{
	case Direction::kRight: ++newPosition.x; break;
	case Direction::kLeft:  --newPosition.x; break;
	case Direction::kDown:  ++newPosition.y; break;
	case Direction::kUp:    --newPosition.y; break;
	default: break;
	}

	return newPosition;
}

////////////////////////////////////////////////////////////////////////
// Moves entity on map in the direction specified
////////////////////////////////////////////////////////////////////////
bool Entity::MoveOnMap(Map* currentMap, Direction direction, Entity* entity)
{
	Vector2 currentPosition = entity->GetPosition();
	Vector2 newPosition = GetNextPosition(direction, currentPosition);
	if (newPosition.x == currentPosition.x and newPosition.y == currentPosition.y)
	{
		return false;
	}

	auto& targetedObject = currentMap->at(newPosition);
	targetedObject->Collide(entity);
	return true;
}