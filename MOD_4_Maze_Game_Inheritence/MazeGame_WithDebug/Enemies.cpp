#include "Enemies.h"
#include "Map.h"

HorizontalEnemy::HorizontalEnemy()
	: GameObject()
	, currentDirection{ Direction::kRight }
{}

void HorizontalEnemy::Move() const
{
	Vector2 newPosition = m_position;
	
	switch (currentDirection)
	{
	case Direction::kRight: ++newPosition.x; break;
	case Direction::kLeft: --newPosition.x;	break;
	}

	auto& targetedObject = m_pCurrentMap->at(newPosition);
	if (targetedObject->m_displayCharacter == ObjectCharacter::kEmpty)
	{
		m_pCurrentMap->SwapObjects(m_position, newPosition);
	}

}

VerticalEnemy::VerticalEnemy()
	: GameObject()
	, currentDirection{Direction::kDown}
{}

void VerticalEnemy::Move() const
{
	Vector2 newPosition = m_position;

	switch (currentDirection)
	{
	case Direction::kDown: ++newPosition.y; break;
	case Direction::kUp: --newPosition.y;	break;
	}

	auto& targetedObject = m_pCurrentMap->at(newPosition);
	if (targetedObject->m_displayCharacter == ObjectCharacter::kEmpty)
	{
		m_pCurrentMap->SwapObjects(m_position, newPosition);
	}
}

