#include "ObjectMover.h"

#include <conio.h>

#include "Map.h"
#include "../SharedGameFiles/Timing.h"
////////////////////////////////////////////////////////////////////////
// Gets the next position on the map in the direction specified
////////////////////////////////////////////////////////////////////////
Vector2 ObjectMover::GetNextPosition(Direction direction, Vector2 currentPosition) const
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
bool ObjectMover::MoveOnMap(Map* currentMap, Direction direction, Entity* entity) const
{
	Vector2 currentPosition = entity->GetPosition();
	Vector2 newPosition = GetNextPosition(direction, currentPosition);
	if (newPosition.x == currentPosition.x and newPosition.y == currentPosition.y)
	{
		return false;
	}

	currentMap->at(newPosition)->Collide(entity);
	return true;
}


////////////////////////////////////////////////////////////////////////
// Runs the logic for moving the player
////////////////////////////////////////////////////////////////////////
bool ObjectMover::MovePlayer(Entity* entity) const
{
	char input = (char)_getch();
	if (input == '0')
		entity->GetMapPointer()->WinLevel();
	if (input == '9')
		entity->GetMapPointer()->UnlockAllDoors();
	if(input == '8')
		entity->GetMapPointer()->ToggleDoors();

	MoveOnMap(entity->m_pCurrentMap, static_cast<Direction>(input), entity);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Runs the logic for moving a entity randomly
////////////////////////////////////////////////////////////////////////
bool ObjectMover::MoveRandom(Entity* entity) const
{
	if (!Timing::SeedRandomWithTime())
		return false;
	
	int directionInteger = (rand() % ((int)Direction::kCount));
	Direction moveDirection = Direction::kCount;
	switch (directionInteger)
	{
	case 0: moveDirection = Direction::kUp; break;
	case 1: moveDirection = Direction::kDown; break;
	case 2: moveDirection = Direction::kRight; break;
	case 3: moveDirection = Direction::kLeft; break;
	default: break;
	}
	MoveOnMap(entity->m_pCurrentMap, moveDirection, entity);
	return true;
}


////////////////////////////////////////////////////////////////////////
// Runs the logic for moving towards the player character
////////////////////////////////////////////////////////////////////////
bool ObjectMover::MoveTowardsPlayer(Entity* entity) const
{
	Direction moveDirection = Direction::kDown;
	Vector2 playerPosition = entity->GetMapPointer()->GetPlayer()->GetPosition();

	if (entity->m_position.y < playerPosition.y)
		moveDirection = Direction::kDown;
	if (entity->m_position.y > playerPosition.y)
		moveDirection = Direction::kUp;
	if (entity->m_position.x > playerPosition.x)
		moveDirection = Direction::kLeft;
	if (entity->m_position.x < playerPosition.x)
		moveDirection = Direction::kRight;

	MoveOnMap(entity->m_pCurrentMap, moveDirection, entity);
	return true;
}

