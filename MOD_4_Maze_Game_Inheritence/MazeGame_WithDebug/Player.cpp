#include "Player.h"


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

#if DONT
	switch (m_pCurrentMap->at(newPosition))
	{
	case ObjectCharacters::kEmpty:
		//m_standingOnCharacter = ObjectCharacters::k_empty;
		m_pCurrentMap->at(newPosition) = ObjectCharacters::kPlayer;
		m_pCurrentMap->at(m_position) = ObjectCharacters::kEmpty;
		m_position = newPosition;
		break;
	case ObjectCharacters::kExit:
		return true;
	default:
		break;
	}
#endif
	return false;
}

