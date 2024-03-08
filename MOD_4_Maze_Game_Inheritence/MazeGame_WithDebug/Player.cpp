#include "Player.h"

#include <conio.h>

#include "Map.h"

void Player::Collide(Entity* collidedEntity)
{
	m_pCurrentMap->Reset();

	return;
}

 
/////////////////////////////////////////////////////////
/// Character movement
/////////////////////////////////////////////////////////
void Player::Move()
{
	char input = (char)_getch();

	MoveOnMap(m_pCurrentMap, static_cast<Direction>(input), this);
}


