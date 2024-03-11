#include "Player.h"

#include <conio.h>

#include "Map.h"

void Player::Collide(Entity* collidedEntity)
{
	collidedEntity->GetMapPointer()->Reset();
	return;
}

 
/////////////////////////////////////////////////////////
/// Character movement
/////////////////////////////////////////////////////////
void Player::Update()
{
	char input = (char)_getch();

	MoveOnMap(m_pCurrentMap, static_cast<Direction>(input), this);
}


