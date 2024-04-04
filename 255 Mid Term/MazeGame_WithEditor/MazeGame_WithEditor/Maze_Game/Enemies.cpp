#include "Enemies.h"
#include "Map.h"

HorizontalEnemy::HorizontalEnemy()
	: Entity(s_displayCharacter, movementType::kBouncing, Direction::kRight)
{
	m_displayFormat = TEXT_RGB(210, 50, 50);
}

RandEnemy::RandEnemy()
	: Entity(s_displayCharacter, movementType::kRandom, Direction::kDown)
{
	m_displayFormat = TEXT_RGB(107, 148, 74);
}

VerticalEnemy::VerticalEnemy()
	: Entity(s_displayCharacter, movementType::kBouncing, Direction::kDown)
{
	m_displayFormat = TEXT_RGB(210, 50, 50);
}

DirectEnemy::DirectEnemy()
	: Entity(s_displayCharacter, movementType::kDirect, Direction::kDown)
{
	m_displayFormat = TEXT_RGB(210, 50, 50);
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
////////////////////////////////////////////////////////////////
/// as far as I know, this is the only place where hitWall is 
/// actually used. I still believe this is good however!
////////////////////////////////////////////////////////////////
void HorizontalEnemy::HitWall()
{
	m_currentDirection = ReverseDirection(m_currentDirection);
}

void VerticalEnemy::HitWall()
{
	m_currentDirection = ReverseDirection(m_currentDirection);
}