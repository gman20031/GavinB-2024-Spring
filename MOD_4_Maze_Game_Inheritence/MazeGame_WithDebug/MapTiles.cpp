#include "MapTiles.h"
#include "Map.h"

void EmptyTile::Collide(Entity* collidedEntity)
{
	m_pCurrentMap->SwapObjects(m_position,collidedEntity->GetPosition());
}

void TrapTile::Collide(Entity* collidedEntity)
{
	if (collidedEntity->IsPlayer())
		m_pCurrentMap->Reset();
	else
		collidedEntity->HitWall();
}

void ExitTile::Collide(Entity* collidedEntity)
{	
	if (collidedEntity->IsPlayer())
		m_pCurrentMap->WinLevel();
	else
		collidedEntity->HitWall();
}

void WallTile::Collide(Entity* collidedEntity)
{
	collidedEntity->HitWall();
}