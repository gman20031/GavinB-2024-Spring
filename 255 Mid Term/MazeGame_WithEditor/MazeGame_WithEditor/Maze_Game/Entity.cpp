#include "Entity.h"
#include "Map.h"

void Entity::Update()
{
	using enum movementType; 
	switch (m_moveType)
	{
	case kPlayer: s_objectMover.MovePlayer(this); break;
	case kRandom: s_objectMover.MoveRandom(this); break;
	case kDirect: s_objectMover.MoveTowardsPlayer(this); break;
	case kBouncing: s_objectMover.MoveOnMap(m_pCurrentMap, m_currentDirection, this); break;
	default: break;
	}
}

void Entity::Collide(Entity* collidedEntity)
{
	//When the player walks into this entity
	if (collidedEntity->IsPlayer())
	{
		auto player = static_cast<Player*>(collidedEntity);
		player->HitEnemy(m_position, this);
	}
}

// What happens when the entity gets killed
void Entity::Kill()
{
	// this is never a player
	--m_pCurrentMap->m_enemyCount;
}
