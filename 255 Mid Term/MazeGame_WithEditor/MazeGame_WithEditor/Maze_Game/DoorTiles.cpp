#include "DoorTiles.h"

#include "MapTiles.h"
#include "Entity.h"
#include "Map.h"
#include "GameObjectFactory.h"


//////////////////////////////////////////////////////
/// On collission logic
//////////////////////////////////////////////////////
void Door::Collide(Entity* collidedEnitity)
{
	if (m_unlocked)
	{
		// if holding nothing
		if (m_heldObject == nullptr)
		{
			m_heldObject = (m_pCurrentMap->at(collidedEnitity->GetPosition()));
			m_pCurrentMap->ReplaceObject(collidedEnitity->GetPosition(), ObjectChar::kEmpty);
			collidedEnitity->SetPosition(m_position);
			
			m_displayCharacter = m_heldObject->GetDisplayCharacater();
			m_displayFormat = m_heldObject->GetDisplayFormat();

			collidedEnitity->m_updated = false;
			m_updated = true;
		}
		// if holding anything
		else
		{
			//those entities need to collide
			m_heldObject->Collide(collidedEnitity);
		}
	}
	else
	{
		collidedEnitity->HitWall();
	}
}

//////////////////////////////////////////////////////
/// Unlocks the door for use
//////////////////////////////////////////////////////
void Door::Unlock()
{
	m_unlocked = true;
	m_displayFormat = kUnlockedFormat;
}

//////////////////////////////////////////////////////
/// Locks the door to act like wall
//////////////////////////////////////////////////////
void Door::Lock()
{
	if (m_heldObject != nullptr)
		m_heldObject->Kill();
	m_heldObject = nullptr;
	m_unlocked = false;
	m_displayFormat = m_defaultFormat;
}

//////////////////////////////////////////////////////
/// Update logic, will update containted object if needed
//////////////////////////////////////////////////////
void Door::Update()
{
	if (m_unlocked)
	{
		if (!m_pCurrentMap->DoorsUnlocked())
			Lock();
		else
			UpdateUnlocked();
	}
	else if (m_pCurrentMap->DoorsUnlocked())
		Unlock();
}

//////////////////////////////////////////////////////
/// Logic for when the object is unlocked and updated
//////////////////////////////////////////////////////
void Door::UpdateUnlocked()
{
	if (m_heldObject)
	{
		if (m_heldObject->IsPlayer() == false)
		{
			if (!m_heldObject->m_updated)
				m_heldObject->Update();
			m_heldObject->m_updated = true;
		}
		// if the object wanted to leave, it will change the position of THE DOOR
		// but will not update its own position data.
		if (m_heldObject->GetPosition() != m_position)
			RemoveHeldObject();
		else
			m_heldObject->m_updated = false;
	}
}

//////////////////////////////////////////////////////////////////////
/// Updates the held object where it wanted to move to, and replaces 
/// the pointer with nullptr 
//////////////////////////////////////////////////////////////////////
void Door::RemoveHeldObject()
{
	const Vector2 newLocation = m_position;
	const Vector2 DoorLocation = m_heldObject->GetPosition();

	m_pCurrentMap->SwapObjects(newLocation, DoorLocation); // switch back
	m_pCurrentMap->ChangeObjectAt(newLocation, m_heldObject);
	m_heldObject->SetPosition(newLocation);
	m_heldObject = nullptr;

	m_position = DoorLocation;
	m_displayCharacter = m_defaultDisplay;
	m_displayFormat = kUnlockedFormat;
}



Door::Door(GameObjectType objectType = GameObjectType::kClearDoor)
	: GameObject(objectType)
	, m_defaultDisplay(objectType)
{

}

ClearDoor::ClearDoor()
	: Door(s_displayCharacter)
{
	m_displayFormat = m_defaultFormat;
}

HiddenDoor::HiddenDoor()
	: Door(GameObjectType::kClearDoor)
{
	m_displayFormat = WallTile::s_displayFormat;
	m_defaultFormat = m_displayFormat;
}

