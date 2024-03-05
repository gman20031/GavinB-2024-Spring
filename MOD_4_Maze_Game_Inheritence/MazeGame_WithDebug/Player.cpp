#include "Player.h"
#include "Map.h"

bool Player::SetCurrentMapPointer(Map* newMap)
{
	m_pCurrentMap = newMap;

	//m_position = newMap->GetPlayerStart();
	return true;
}
 
/////////////////////////////////////////////////////////
/// Character movement
/////////////////////////////////////////////////////////
bool Player::Move(Direction direction)
{
	Vector2 newPosition = m_position;
	switch (direction)
	{
	case Direction::kUp:    newPosition.y -= kMoveSpeed;  break;
	case Direction::kDown:  newPosition.y += kMoveSpeed;  break;
	case Direction::kRight: newPosition.x += kMoveSpeed;  break;
	case Direction::kLeft:  newPosition.x -= kMoveSpeed;  break;
	}
	return MoveCharacter(newPosition);
}


bool Player::MoveCharacter(Vector2 newPosition)
{
	auto& targetedObject = m_pCurrentMap->at(newPosition);
	if (targetedObject->m_displayCharacter == ObjectCharacter::kEmpty)
	{
		m_pCurrentMap->SwapObjects(m_position, newPosition);
	}

	return false;
}

