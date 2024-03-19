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
	s_objectMover.MovePlayer(this);
}


