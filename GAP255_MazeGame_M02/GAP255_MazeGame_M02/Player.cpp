
#include "Player.h"
//#include "Map.h"

bool Player::SetCurrentMap(Map* newMap)
{
	m_pCurrentMap = newMap;
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

bool Player::MoveCharacter(CooridinatePair newPosition)
{
	switch (m_pCurrentMap->at(newPosition))
	{
	case Map::k_emptyCharacter:
		m_pCurrentMap->at(newPosition) = m_displayChar;
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
