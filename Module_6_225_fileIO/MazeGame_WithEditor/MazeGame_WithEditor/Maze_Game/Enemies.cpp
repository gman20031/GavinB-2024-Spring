#include "Enemies.h"
#include "Map.h"

HorizontalEnemy::HorizontalEnemy()
	: Entity(s_displayCharacter)
	, m_currentDirection{ Direction::kRight }
{
}

RandEnemy::RandEnemy()
	: Entity(s_displayCharacter)
	, m_currentDirection{ Direction::kCount }
{
}

VerticalEnemy::VerticalEnemy()
	: Entity(s_displayCharacter)
	, m_currentDirection{ Direction::kDown }
{
}

void HorizontalEnemy::Update()
{
 	s_objectMover.MoveOnMap(m_pCurrentMap,m_currentDirection,this);
}

void VerticalEnemy::Update()
{
	s_objectMover.MoveOnMap(m_pCurrentMap, m_currentDirection, this);
}

void RandEnemy::Update()
{
	s_objectMover.MoveRandom(this);
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

void RandEnemy::HitWall()
{
	return;
}

