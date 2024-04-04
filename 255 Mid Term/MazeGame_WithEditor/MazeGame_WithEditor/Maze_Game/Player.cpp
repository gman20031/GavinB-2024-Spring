#include "Player.h"

#include "../SharedGameFiles/Prompting.h"
#include "Map.h"

/////////////////////////////////////////////////////////////////////
// this runs when something walks into the player
/////////////////////////////////////////////////////////////////////
void Player::Collide(Entity* collidedEntity)
{
	HitEnemy(collidedEntity->GetPosition(), collidedEntity);
	m_playerInitiated = false;
}

/////////////////////////////////////////////////////////////////////
// Hides the player and redraws the map.
// Then fully resets the map and waits for user input to continue
/////////////////////////////////////////////////////////////////////
void Player::Kill()
{
	m_displayFormat = TEXT_RGB(0,0,0);
	m_pCurrentMap->Draw();
	m_displayFormat = kDefaultDisplay;
	m_pCurrentMap->Reset();
	m_lives = kDefaultLives;
	printf("You died\n");
	Pause();
}

/////////////////////////////////////////////////////////////////////
// Saves all the information needed for when an entity collides
// with the player
/////////////////////////////////////////////////////////////////////
void Player::HitEnemy(Vector2 hitLocation, Entity* collidedEntity)
{
	m_collided = true;
	m_collidedEntity = collidedEntity;
	m_collideLocation = hitLocation;
}

/////////////////////////////////////////////////////////////////////
// reduces the players life, then kills player if <= 0
/////////////////////////////////////////////////////////////////////
void Player::FightEntity(Entity* otherEntity)
{
	if (m_invulnerable or (m_playerInitiated and m_hasSword) )
	{
		Vector2 entityPosition = otherEntity->GetPosition();
		otherEntity->Kill();
		m_pCurrentMap->ReplaceObject(entityPosition, GameObjectType::kEmpty);
		m_pCurrentMap->at(entityPosition)->Collide(this);
		return;
	}
	--m_lives;
	if (m_lives <= 0)
		Kill();
}

/////////////////////////////////////////////////////////////////////
// Checks to see if the entity player collided with is still at that 
// location, then fights that entity if true
/////////////////////////////////////////////////////////////////////
void Player::CheckCollisions()
{
	if (m_collided)
	{	
		// if still touching
		if (m_collidedEntity->GetPosition() == m_collideLocation)
			FightEntity(m_collidedEntity);
		else // this can only happen if player walks into enemy
			m_pCurrentMap->at(m_collideLocation)->Collide(this); 
	}
	m_collidedEntity = nullptr;
	m_collided = false;
	m_playerInitiated = true;
}

