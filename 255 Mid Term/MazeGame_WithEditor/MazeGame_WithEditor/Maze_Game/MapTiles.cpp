#include "MapTiles.h"
#include "Map.h"

/////////////////////////////////////////////////////////////////////
/// calls the maps swapObjects function to change locations with the 
/// collided entity
/////////////////////////////////////////////////////////////////////
void EmptyTile::Collide(Entity* collidedEntity)
{
	m_pCurrentMap->SwapObjects(m_position,collidedEntity->GetPosition());
}

/////////////////////////////////////////////////////////////////////
/// Kils the entity that collided with this, and if it is not the
/// player it replaces them with a empty space
/////////////////////////////////////////////////////////////////////
void TrapTile::Collide(Entity* collidedEntity)
{
	collidedEntity->Kill();
	if(!collidedEntity->IsPlayer())
		m_pCurrentMap->ReplaceObject(collidedEntity->GetPosition(), GameObjectType::kEmpty);
}

/////////////////////////////////////////////////////////////////////
/// if the collided entity is a player, the map is won
/// otherwise acts as wall.
/////////////////////////////////////////////////////////////////////
void ExitTile::Collide(Entity* collidedEntity)
{	
	if (collidedEntity->IsPlayer())
		m_pCurrentMap->WinLevel();
	else
		collidedEntity->HitWall();
}

/////////////////////////////////////////////////////////////////////
/// Runs the hitWall() function on the collided Entity.
/////////////////////////////////////////////////////////////////////
void WallTile::Collide(Entity* collidedEntity)
{
	collidedEntity->HitWall();
}

/////////////////////////////////////////////////////////////////////
/// Runs the hitWall() function on the collided Entity.
/// toggles the button on or off when collided.
/////////////////////////////////////////////////////////////////////
void ToggleTile::Collide(Entity* collidedEntity)
{
	collidedEntity->HitWall();
	if (m_activated)
	{
		m_activated = false;
		m_displayFormat = kInactiveDisplayFormat;
		--m_pCurrentMap->m_switchesOn;
	}
	else
	{
		m_activated = true;
		m_displayFormat = kActiveDisplayFormat;
		++m_pCurrentMap->m_switchesOn;
	}
}
