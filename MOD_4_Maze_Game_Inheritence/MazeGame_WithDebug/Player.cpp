
#include "Player.h"

bool Player::SetCurrentMapPointer(Map* newMap) 
{
	m_pCurrentMap = newMap;
	m_position = newMap->GetPlayerStart();
	return true;
}

CooridinatePair& Player::GetPosition()
{
	return m_position;
}

void Player::setPosition(CooridinatePair newPosition)
{
	m_position = newPosition;
}

/////////////////////////////////////////////////////////
/// Character movement
/////////////////////////////////////////////////////////

bool Player::MoveX(int distance)
{
	CooridinatePair newPosition = m_position;
	newPosition.x += distance;
	return MoveCharacter(newPosition);
}

bool Player::MoveY(int distance)
{
	CooridinatePair newPosition = m_position;
	newPosition.y += distance;
	return MoveCharacter(newPosition);
}

bool Player::Move(GameObject::Direction direction)
{
	CooridinatePair newPosition = m_position;
	switch (direction)
	{
	case GameObject::Direction::kUp:    newPosition.y += kMoveSpeed;  break;
	case GameObject::Direction::kDown:  newPosition.y -= kMoveSpeed;  break;
	case GameObject::Direction::kRight: newPosition.x += kMoveSpeed;  break;
	case GameObject::Direction::kLeft:  newPosition.x -= kMoveSpeed;  break;
	}
	return MoveCharacter(newPosition);
}


bool Player::MoveCharacter(CooridinatePair newPosition)
{

#ifdef DEBUG
	if (m_noClip)
	{
		if (newPosition.x > (m_pCurrentMap->GetMapWidth()-1) or newPosition.x < 0 or
			newPosition.y >(m_pCurrentMap->GetMapHeight()) or newPosition.y < 0)
			return false;
		if (m_pCurrentMap->at(newPosition) == Map::k_exitCharacter)
			return true;
		char newStandingChar = m_pCurrentMap->at(newPosition);
		m_pCurrentMap->at(newPosition) = Map::k_playerCharacter;
		m_pCurrentMap->at(m_position) = m_standingOnCharacter;
		m_standingOnCharacter = newStandingChar;
		m_position = newPosition;
		return false;
	}
#endif // DEBUG

	switch (m_pCurrentMap->at(newPosition))
	{
	case Map::k_emptyCharacter:
		//m_standingOnCharacter = Map::k_emptyCharacter;
		m_pCurrentMap->at(newPosition) = Map::k_playerCharacter;
		m_pCurrentMap->at(m_position) = Map::k_emptyCharacter;
		m_position = newPosition;
		break;
	case Map::k_exitCharacter:
		return true;
	default:
		break;
	}
	return false;
}


#ifdef DEBUG
void Player::ToggleNoClip()
{
	if (m_noClip)
		m_noClip = false;
	else
		m_noClip = true;
}

bool Player::TeleportToLocation(CooridinatePair newLocation)
{
	bool tempClip = m_noClip;
	m_noClip = true;
	bool didWin = MoveCharacter(newLocation);
	m_noClip = tempClip;
	return didWin;
}
#endif