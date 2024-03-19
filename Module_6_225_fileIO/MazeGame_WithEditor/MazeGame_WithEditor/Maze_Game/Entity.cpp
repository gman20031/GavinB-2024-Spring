#include "Entity.h"
#include "Map.h"

void Entity::Collide(Entity* collidedEntity)
{
	if (collidedEntity->IsPlayer())
	{
		m_pCurrentMap->Reset();
	}
}
