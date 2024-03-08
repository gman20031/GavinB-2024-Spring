#include "Enemies.h"
#include "Map.h"

void HorizontalEnemy::Collide(Entity* collidedEntity)
{
	if (collidedEntity->IsPlayer())
	{
		m_pCurrentMap->Reset();
	}
}

void VerticalEnemy::Collide(Entity* collidedEntity)
{
	if (collidedEntity->IsPlayer())
	{
		m_pCurrentMap->Reset();
	}
}

HorizontalEnemy::HorizontalEnemy()
	: Entity()
	, m_currentDirection{ Direction::kRight }
{}

VerticalEnemy::VerticalEnemy()
	: Entity()
	, m_currentDirection{ Direction::kDown }
{}

void HorizontalEnemy::Move()
{
	MoveOnMap(m_pCurrentMap,m_currentDirection,this);
}


void VerticalEnemy::Move()
{
	MoveOnMap(m_pCurrentMap, m_currentDirection, this);
}

static Direction ReverseDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::kUp:    return (Direction::kDown);
	case Direction::kDown:  return (Direction::kUp);
	case Direction::kRight: return (Direction::kLeft);
	case Direction::kLeft:  return (Direction::kRight);
	}
	return direction;
}

void HorizontalEnemy::HitWall()
{
	m_currentDirection = ReverseDirection(m_currentDirection);

}

void VerticalEnemy::HitWall()
{
	m_currentDirection = ReverseDirection(m_currentDirection);

}