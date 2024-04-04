#include "Items.h"

#include "Entity.h"
#include "Map.h"

void Sword::Collide(Entity* collidedEntity)
{
	if (collidedEntity->IsPlayer())
	{
		m_pCurrentMap->GetPlayer()->CollectSword();
		m_pCurrentMap->SwapObjects(m_position, collidedEntity->GetPosition());
		m_pCurrentMap->ReplaceObject(m_position, GameObjectType::kEmpty);
	}
	else
		collidedEntity->HitWall();
}
